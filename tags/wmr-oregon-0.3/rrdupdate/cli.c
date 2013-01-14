#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "rrd_format.h"
#include "rrd_generic.h"
#include "rrd_update.h"

/* A very quick and dirty wrapper around the C API to enable testing */
int main(int argc, char *argv[])
{
	struct rrd_db *		rrd;
	double			updates[128];
	struct timeval 		now;
	int			i;

	gettimeofday(&now, NULL);

/*
	if ((rrd = rrd_open(argv[1])) == NULL) {
		printf("Unable to open RRD file, aborting.\n");
		exit(-1);
	}
*/
	for(i = 2; i < sizeof(argc); i++)
		updates[i-2] = (double)strtoll(argv[i], (char **)NULL, 10);


printf("(%.1f) %d\n", updates[0], argc-2);
return 0;

	if (rrd_update(rrd, now, updates, argc-2) < 0) {
		printf("rrd_update() error\n");
		exit(-1);
	}

	rrd_close(rrd);

	return 0;
}
