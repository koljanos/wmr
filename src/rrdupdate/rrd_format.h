#ifndef _RRD_FORMAT_H_
#define _RRD_FORMAT_H_

#define DNAN				((double)(0.0/0.0))
#define DINF				((double)(1.0/0.0))

typedef union rrd_value {
	u_int32_t			integer;
	double				decimal;
} rrd_value_t;

#define DS_TYPE_COUNTER			0
#define DS_TYPE_ABSOLUTE		1
#define DS_TYPE_GAUGE			2
#define DS_TYPE_DERIVE			3

#define	CF_TYPE_AVERAGE			0
#define CF_TYPE_MINIMUM			1
#define CF_TYPE_MAXIMUM			2
#define CF_TYPE_LAST			3
#define CF_TYPE_HWPREDICT		4
#define CF_TYPE_SEASONAL		5
#define CF_TYPE_DEVPREDICT		6
#define CF_TYPE_DEVSEASONAL		7
#define CF_TYPE_FAILURES		8

/* RRD database file structures */
#define SIZE_HEADER_COOKIE		4
#define SIZE_HEADER_VERSION		5
#define SIZE_HEADER_PARAMS		10
#define SIZE_DSDEF_DSNAME		20
#define SIZE_DSDEF_DSTYPE		20
#define SIZE_DSDEF_PARAMS		10
#define SIZE_RRADEF_CFNAME		20
#define SIZE_RRADEF_PARAMS		10
#define SIZE_PDPPREP_LASTDS		30
#define SIZE_PDPPREP_PARAMS		10
#define SIZE_CDPPREP_PARAMS		10

#define PARAM_DS_MIN_HEARTBEAT		0
#define PARAM_DS_MIN_VALUE		1
#define PARAM_DS_MAX_VALUE		2
#define PARAM_DS_CDEF			3

#define PARAM_RRA_CDP_XFF_VALUE		0
#define PARAM_RRA_HW_ALPHA		1
#define PARAM_RRA_HW_BETA		2
#define PARAM_RRA_DEPENDENT_RRA_INDEX	3
#define PARAM_RRA_SEASONAL_SMOOTH_INDEX	4
#define PARAM_RRA_DELTA_POS		5
#define PARAM_RRA_DELTA_NEG		6
#define PARAM_RRA_WINDOW_LENGTH		7

#define PARAM_PDP_UNKNOWN_SEC_COUNT	0
#define PARAM_PDP_VALUE			1

#define PARAM_CDP_VALUE			0
#define PARAM_CDP_UNKNOWN_PDP_COUNT	1
#define PARAM_CDP_HW_INTERCEPT		2
#define PARAM_CDP_HW_LAST_INTERCEPT	3
#define PARAM_CDP_HW_SLOPE		4
#define PARAM_CDP_HW_LAST_SLOPE		5
#define PARAM_CDP_NULL_COUNT		6
#define PARAM_CDP_LAST_NULL_COUNT	7
#define PARAM_CDP_PRIMARY_VALUE		8
#define PARAM_CDP_SECONDARY_VALUE	9

struct rrd_header {
	char				cookie[SIZE_HEADER_COOKIE];
	char				version[SIZE_HEADER_VERSION];
	double				cookie_float;
	u_int32_t			ds_cnt;
	u_int32_t			rra_cnt;
	u_int32_t			pdp_step;
	rrd_value_t			params[SIZE_HEADER_PARAMS];
};

struct rrd_ds_def {
	char				ds_name[SIZE_DSDEF_DSNAME];
	char				ds_type[SIZE_DSDEF_DSTYPE];
	rrd_value_t			params[SIZE_DSDEF_PARAMS];
};

struct rrd_rra_def {
	char				cf_name[SIZE_RRADEF_CFNAME];
	u_int32_t			row_cnt;
	u_int32_t			pdp_cnt;
	rrd_value_t			params[SIZE_RRADEF_PARAMS];
};

struct rrd_pdp_prep {
	char				last_ds[SIZE_PDPPREP_LASTDS];
	rrd_value_t			scratch[SIZE_PDPPREP_PARAMS];
};

struct rrd_cdp_prep {
	rrd_value_t			scratch[SIZE_CDPPREP_PARAMS];
};

#endif
