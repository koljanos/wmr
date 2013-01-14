#ifndef _RRD_GENERIC_H_
#define _RRD_GENERIC_H_

#define RRD_COOKIE		"RRD"
#define RRD_COOKIE_FLOAT	8.642135E130
#define RRD_VERSION		"0003"

#define RRD_LOCK(x)		(flock((x)->fd, LOCK_EX))
#define RRD_UNLOCK(x)		(flock((x)->fd, LOCK_UN))
#define RRD_SYNC(x)		(fsync((x)))

#define RRD_XLOCK(x)		{					\
					struct flock	fl;		\
					fl.l_type	= F_WRLCK;	\
					fl.l_len	= 0;		\
					fl.l_start	= 0;		\
					fl.l_whence	= SEEK_SET;	\
					fcntl((x)->fd, F_SETLKW, &fl);	\
				}

#define IFDNAN(X,Y)		(isnan(X) ? (Y) : (X))

struct rrd_db {
	int			fd;
	u_int32_t		filesize;
	void *			mmap;

	/* Pointers to important headers within the RRD file */
	struct rrd_header *	header;
	struct rrd_ds_def *	ds_def;
	struct rrd_rra_def *	rra_def;
	struct timeval *	lastupdate;
	struct rrd_pdp_prep *	pdp_prep;
	struct rrd_cdp_prep *	cdp_prep;
	u_int32_t *		rra_ptr;
	rrd_value_t *		rrd_value;
};

struct rrd_db *rrd_open(char *);
int rrd_close(struct rrd_db *);

#endif
