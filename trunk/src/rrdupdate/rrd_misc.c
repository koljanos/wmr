#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rrd_format.h"
#include "rrd_misc.h"

int rrd_convert_ds(char *input)
{
	/* Correct some very badly chosen RRD file datatypes */

	if (!strncmp(input, "COUNTER", SIZE_DSDEF_DSTYPE))
		return DS_TYPE_COUNTER;
	else if (!strncmp(input, "ABSOLUTE", SIZE_DSDEF_DSTYPE))
		return DS_TYPE_ABSOLUTE;
	else if (!strncmp(input, "GAUGE", SIZE_DSDEF_DSTYPE))
		return DS_TYPE_GAUGE;
	else if (!strncmp(input, "DERIVE", SIZE_DSDEF_DSTYPE))
		return DS_TYPE_DERIVE;

	return -1;
}

int rrd_convert_cf(char *input)
{
	/* Correct some very badly chosen RRD file datatypes */

	if (!strncmp(input, "AVERAGE", SIZE_RRADEF_CFNAME))
		return CF_TYPE_AVERAGE;
	else if (!strncmp(input, "MINIMUM", SIZE_RRADEF_CFNAME))
		return CF_TYPE_MINIMUM;
	else if (!strncmp(input, "MAXIMUM", SIZE_RRADEF_CFNAME))
		return CF_TYPE_MAXIMUM;
	else if (!strncmp(input, "LAST", SIZE_RRADEF_CFNAME))
		return CF_TYPE_LAST;
	else if (!strncmp(input, "HWPREDICT", SIZE_RRADEF_CFNAME))
		return CF_TYPE_HWPREDICT;

	return -1;
}

