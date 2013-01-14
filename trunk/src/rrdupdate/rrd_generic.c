#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include "rrd_format.h"
#include "rrd_generic.h"

struct rrd_db *rrd_open(char *filename)
{
	struct rrd_db *rrd;

	if ((rrd = malloc(sizeof(struct rrd_db))) == NULL)
	{
	    return NULL;
	}

	if ((rrd->fd = open(filename, O_RDWR)) < 0) 
	{
	    free(rrd);
	    return NULL;
	}

	rrd->filesize = lseek(rrd->fd, 0, SEEK_END);

	if ((rrd->mmap = mmap(NULL, rrd->filesize, PROT_READ|PROT_WRITE, MAP_SHARED, rrd->fd, 0)) == MAP_FAILED)
	{
	    close(rrd->fd);
	    free(rrd);
	    return NULL;
	}

	/* Populate pointers to the important locations within the RRD file */
	rrd->header	= (struct rrd_header *)   (rrd->mmap       + 0);
	rrd->ds_def	= (struct rrd_ds_def *)   (rrd->header     + 1);
	rrd->rra_def	= (struct rrd_rra_def *)  (rrd->ds_def     + rrd->header->ds_cnt);
	rrd->lastupdate	= (struct timeval *)      (rrd->rra_def    + rrd->header->rra_cnt);
	rrd->pdp_prep	= (struct rrd_pdp_prep *) (rrd->lastupdate + 1);
	rrd->cdp_prep	= (struct rrd_cdp_prep *) (rrd->pdp_prep   + rrd->header->ds_cnt);
	rrd->rra_ptr	= (u_int32_t *)           (rrd->cdp_prep   + rrd->header->rra_cnt * rrd->header->ds_cnt);
	rrd->rrd_value  = (rrd_value_t *)         (rrd->rra_ptr    + rrd->header->rra_cnt);

	/* Validation checks */
	if (strncmp(rrd->header->cookie, RRD_COOKIE, sizeof(RRD_COOKIE))) 
	{
		close(rrd->fd);
		free(rrd);
		return NULL;
	}

	if (strncmp(rrd->header->version, RRD_VERSION, sizeof(RRD_VERSION))) 
	{
		close(rrd->fd);
		free(rrd);
		return NULL;
	}

	return rrd;
}

int rrd_close(struct rrd_db *rrd)
{
int ret;

    (void) munmap(rrd->mmap, rrd->filesize);
    ret = close(rrd->fd);
    free(rrd);

return ret;
}
