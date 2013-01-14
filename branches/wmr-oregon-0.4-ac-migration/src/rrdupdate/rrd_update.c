#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/time.h>
#include "rrd_format.h"
#include "rrd_generic.h"
#include "rrd_misc.h"
#include "rrd_update.h"

inline static int rrd_update_cdp(struct rrd_db *, double *, time_t, time_t);

int rrd_update(struct rrd_db *rrd, struct timeval timestamp, double *updates, int update_cnt)
{
	time_t	timestep_prev, timestep_curr, timestep_diff;
	double	interval, interval_pre, interval_post;
	double	rate[update_cnt], cdp[update_cnt];
	int	i;

	/* Error checking */
	if (rrd == NULL)
		return -1;

	if (update_cnt != rrd->header->ds_cnt) {
		printf("Incorrect number of DS updates, expecting %d, received %d.\n",
			rrd->header->ds_cnt, update_cnt);
		return -1;
	}

	if (timestamp.tv_sec <= rrd->lastupdate->tv_sec) {
		printf("Minimum one second step, last update time %ld, current time %ld\n",
			rrd->lastupdate->tv_sec, timestamp.tv_sec);
		return -1;
	}


	/* Calculate the time steps and intervals for prev and curr updates */
	timestep_prev	 = rrd->lastupdate->tv_sec - (rrd->lastupdate->tv_sec % rrd->header->pdp_step);
	timestep_curr	 = timestamp.tv_sec - (timestamp.tv_sec % rrd->header->pdp_step);
	timestep_diff	 = timestep_curr - timestep_prev;
	interval	 = timestamp.tv_sec - rrd->lastupdate->tv_sec;
	interval	+= (timestamp.tv_usec - rrd->lastupdate->tv_usec) / 1000000.0;

	if (timestep_curr > timestep_prev) {
		interval_pre	= timestep_curr - rrd->lastupdate->tv_sec;
		interval_pre	-= (double)rrd->lastupdate->tv_usec / 1000000.0;
		interval_post	= timestamp.tv_sec % rrd->header->pdp_step;
		interval_post	+= (double)timestamp.tv_usec / 1000000.0;
	} else {
		interval_pre	= interval;
		interval_post	= 0.0;
	}


	/******************************************************************/
        /* Prepare the new data *******************************************/
        /******************************************************************/
	for (i = 0; i < rrd->header->ds_cnt; ++i) 
	{
		struct rrd_ds_def	*ds = rrd->ds_def+i;
		double			data = DNAN;
		int			ds_type;

		ds_type	= rrd_convert_ds(ds->ds_type);
		rate[i]	= DNAN;

		switch (ds_type) 
		{
		    case DS_TYPE_COUNTER:
		    case DS_TYPE_DERIVE:
			if (rrd->pdp_prep[i].last_ds[0] == 'U')
				break;

			data	= (double) ((long long)updates[i] -  strtoll(rrd->pdp_prep[i].last_ds, NULL, 10));

			if (ds_type == DS_TYPE_COUNTER) 
			{
				/* Ghetto hack for handling 2^32 or 2^64 counter rollovers */
				if (data < (double)0.0)
					data	+= (double)4294967296.0;		/* 2^32 */
				if (data < (double)0.0)
					data	+= (double)18446744069414584320.0;	/* 2^64 - 2^32 */
			}

			rate[i]	= data / interval;
			break;
		    case DS_TYPE_ABSOLUTE:
			data	= updates[i];
			rate[i]	= updates[i] / interval;
			break;
		    case DS_TYPE_GAUGE:
			data	= updates[i] * interval;
			rate[i]	= updates[i];
			break;
		    default:
			printf("Unknown data type in RRD file, aborting.\n");
			return -1;
		}

		/* Error and range checking */
		if (!isnan(ds->params[PARAM_DS_MIN_VALUE].decimal))
			if (rate[i] < ds->params[PARAM_DS_MIN_VALUE].decimal)
				rate[i]	= DNAN;
		if (!isnan(ds->params[PARAM_DS_MAX_VALUE].decimal))
			if (rate[i] > ds->params[PARAM_DS_MAX_VALUE].decimal)
				rate[i]	= DNAN;

	//free(ds);

#if 0
		printf("DEBUG: %d value %g rate %g\n", i, data, rate[i]);
#endif
	}

#if 0
	printf("DEBUG: lastupdate:    %ld.%ld\n", rrd->lastupdate->tv_sec, rrd->lastupdate->tv_usec);
	printf("DEBUG: timestamp:     %ld.%ld\n", timestamp.tv_sec, timestamp.tv_usec);
	printf("DEBUG: timestep_prev: %ld\n", (u_long)timestep_prev);
	printf("DEBUG: timestep_curr: %ld\n", (u_long)timestep_curr);
	printf("DEBUG: interval_pre: %f interval_post: %f\n", interval_pre, interval_post);
#endif


	/******************************************************************/
        /* Update the RRD Database ****************************************/
        /******************************************************************/
	RRD_LOCK(rrd);

	/* Set the new last updated time */
	gettimeofday(rrd->lastupdate, NULL);
	rrd->lastupdate->tv_usec = 0;

	for (i = 0; i < rrd->header->ds_cnt; ++i) 
	{
		int	ds_type;

		ds_type	= rrd_convert_ds(rrd->ds_def[i].ds_type);

		if (isnan(rate[i]))
			rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer += interval_pre;
		else
			rrd->pdp_prep[i].scratch[PARAM_PDP_VALUE].decimal += rate[i] * interval_pre;

		/* If necessary, write the new LAST_DS value to the DB */
		if (ds_type == DS_TYPE_COUNTER || ds_type == DS_TYPE_DERIVE)
			snprintf(rrd->pdp_prep[i].last_ds, SIZE_PDPPREP_LASTDS, "%lld", (long long)updates[i]);
	}

	/* If we've crossed a timestep, we're now responsible for calculating
	 * new CDPs and pushing data into the RRAs... This is the hard part. */
	if (timestep_curr > timestep_prev) 
	{
		for (i = 0; i < rrd->header->ds_cnt; ++i) 
		{
			/* Calculate our consolidated data point for each DS */
			cdp[i] = rrd->pdp_prep[i].scratch[PARAM_PDP_VALUE].decimal / ((double)(timestep_diff - rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer));
#if 0
			printf("DEBUG: %d cdp: %f\n", i, cdp[i]);
#endif
			/* If too much data is unknown, set this CDP value to NaN */
			if (rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer > rrd->ds_def[i].params[PARAM_DS_MIN_HEARTBEAT].integer)
				cdp[i]	= DNAN;
			if (timestep_diff <= rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer)
				cdp[i]	= DNAN;

			/* Update pdp_prep with new values for the next run */
			if (isnan(rate[i])) {
				rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer = interval_post;
				rrd->pdp_prep[i].scratch[PARAM_PDP_VALUE].decimal = 0.0;
			} else {
				rrd->pdp_prep[i].scratch[PARAM_PDP_UNKNOWN_SEC_COUNT].integer = 0;
				rrd->pdp_prep[i].scratch[PARAM_PDP_VALUE].decimal = rate[i] * interval_post;
			}
		}

		rrd_update_cdp(rrd, cdp, timestep_prev, timestep_diff);
	}

	RRD_UNLOCK(rrd);

	return 0;
}

inline static int rrd_update_cdp(struct rrd_db *rrd, double *cdp, time_t timestep_prev, time_t timestep_diff)
{
	time_t	timestep_dcnt = timestep_diff / rrd->header->pdp_step;
	int	i, j;

	for (i = 0; i < rrd->header->rra_cnt; ++i) 
	{
		int cf_type = rrd_convert_cf(rrd->rra_def[i].cf_name);
		u_long pdp_offset, rra_cnt;

		pdp_offset = rrd->rra_def[i].pdp_cnt - (timestep_prev / rrd->header->pdp_step) % rrd->rra_def[i].pdp_cnt;

		if (pdp_offset <= timestep_dcnt)
			rra_cnt = (timestep_dcnt - pdp_offset) / rrd->rra_def[i].pdp_cnt + 1;
		else
			rra_cnt = 0;

#if 0
		printf("DEBUG: pdp_offset %lu   rra_step_cnt %lu\n", (u_long)pdp_offset, rra_cnt);
#endif

		if (cf_type == CF_TYPE_SEASONAL || cf_type == CF_TYPE_DEVSEASONAL) {
			//unsupported
		}

		if (++(rrd->rra_ptr[i]) >= rrd->rra_def[i].row_cnt)
			rrd->rra_ptr[i] = 0;

		/* Update CDP PREP areas */
		for(j = 0; j < rrd->header->ds_cnt; ++j) 
		{
			int rra_index = (i * rrd->header->ds_cnt) + j;
			rrd_value_t *cdp_prep_param = rrd->cdp_prep[rra_index].scratch;

			/* Handle bulk updates */
			if ((rrd->rra_def[i].pdp_cnt <= 1) && (timestep_dcnt > 2)) {
				switch (cf_type) {
				    case CF_TYPE_AVERAGE:
				    default:
					cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cdp[j];
					cdp_prep_param[PARAM_CDP_SECONDARY_VALUE].decimal = cdp[j];
					break;
				    case CF_TYPE_SEASONAL:
				    case CF_TYPE_DEVSEASONAL:
					//unsupported
					break;
				    case CF_TYPE_HWPREDICT:
					cdp_prep_param[PARAM_CDP_NULL_COUNT].integer += timestep_dcnt;
					cdp_prep_param[PARAM_CDP_LAST_NULL_COUNT].integer += timestep_dcnt - 1;
					/* fall through */
				    case CF_TYPE_DEVPREDICT:
					cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal	= DNAN;
					cdp_prep_param[PARAM_CDP_SECONDARY_VALUE].decimal = DNAN;
					break;
				    case CF_TYPE_FAILURES:
					cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal	= 0.0;
					cdp_prep_param[PARAM_CDP_SECONDARY_VALUE].decimal = 0.0;
					break;
				}
				continue;
			}

			if (rra_cnt > 0) {
				if (isnan(cdp[j])) {
					cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer += pdp_offset;
					cdp_prep_param[PARAM_CDP_SECONDARY_VALUE].decimal = DNAN;
				} else
					cdp_prep_param[PARAM_CDP_SECONDARY_VALUE].decimal = cdp[j];

				/* Check if unknown data exceeds fudge factor */
				if (cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer > (rrd->rra_def[i].pdp_cnt * rrd->rra_def[i].params[PARAM_RRA_CDP_XFF_VALUE].decimal)) {
					cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = DNAN;

					if (cf_type == CF_TYPE_AVERAGE) {
						if (isnan(cdp[j]))
							cdp_prep_param[PARAM_CDP_VALUE].decimal = DNAN;
						else
							cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j] * ((timestep_dcnt - pdp_offset) % rrd->rra_def[i].pdp_cnt);
					} else
						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
				} else {
					double cum_val, cur_val;

					switch (cf_type) {
					    case CF_TYPE_AVERAGE:
						cum_val = IFDNAN(cdp_prep_param[PARAM_CDP_VALUE].decimal, 0.0);
						cur_val = IFDNAN(cdp[j], 0.0);

						cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = (cum_val + (cur_val * pdp_offset)) / (rrd->rra_def[i].pdp_cnt - cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer);

						if (isnan(cdp[j]))
							cdp_prep_param[PARAM_CDP_VALUE].decimal = DNAN;
						else
							cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j] * ((timestep_dcnt - pdp_offset) % rrd->rra_def[i].pdp_cnt);
						break;
					    case CF_TYPE_MAXIMUM:
						cum_val = IFDNAN(cdp_prep_param[PARAM_CDP_VALUE].decimal, -DINF);
						cur_val = IFDNAN(cdp[j], -DINF);

						if (cur_val > cum_val)
							cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cur_val;
						else
							cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cum_val;

						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					    case CF_TYPE_MINIMUM:
						cum_val = IFDNAN(cdp_prep_param[PARAM_CDP_VALUE].decimal, DINF);
						cur_val = IFDNAN(cdp[j], DINF);

						if (cur_val < cum_val)
							cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cur_val;
						else
							cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cum_val;

						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					    case CF_TYPE_LAST:
					    default:
						cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal = cdp[j];
						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					}
				}

				if (isnan(cdp[j]))
					cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer = (timestep_dcnt - pdp_offset) % rrd->rra_def[i].pdp_cnt;
				else
					cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer = 0;

				/* Write the RRD data */
				rrd->rrd_value[rrd->rra_ptr[i]+j].decimal = cdp_prep_param[PARAM_CDP_PRIMARY_VALUE].decimal;

			} else {
				if (isnan(cdp[j]))
					cdp_prep_param[PARAM_CDP_UNKNOWN_PDP_COUNT].integer += timestep_dcnt;
				else if (isnan(cdp_prep_param[PARAM_CDP_VALUE].decimal)) {
					if (cf_type == CF_TYPE_AVERAGE)
						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j] * timestep_dcnt;
					else
						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
				} else {
					switch (cf_type) {
					    case CF_TYPE_AVERAGE:
						cdp_prep_param[PARAM_CDP_VALUE].decimal += cdp[j] * timestep_dcnt;
						break;
					    case CF_TYPE_MINIMUM:
						if (cdp[j] < cdp_prep_param[PARAM_CDP_VALUE].decimal)
							cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					    case CF_TYPE_MAXIMUM:
						if (cdp[j] > cdp_prep_param[PARAM_CDP_VALUE].decimal)
							cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					    case CF_TYPE_LAST:
					    default:
						cdp_prep_param[PARAM_CDP_VALUE].decimal = cdp[j];
						break;
					}
				}
			}
		}
	}

	return 0;
}
