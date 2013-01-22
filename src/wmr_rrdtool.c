/*
 * Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol. Tested on wmrs200.
 *
 * Copyright:
 * 2009 Barnaby Gray <barnaby@pickle.me.uk>
 * 2012-2013 Den68 <idg68@yandex.ru>
 * Latest download URL: http://www.nkl.ru/support/wmr/
 * Global download URL: http://code.google.com/p/wmr/
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h> 
#define GENERAL_RRD 1
#define GENERAL_TABLES 1
#include "wmr_ext.h"
//
#include "rrdupdate/rrd_format.h"
#include "rrdupdate/rrd_generic.h"
#include "rrdupdate/rrd_update.h"

void rrd_update_int( char *rrdtool_exec_path, char *rrdtool_save_path, int table, int sensor, double *updates, int num, int * rrdEn, int syslogEn, int debugEn )
{
	char buf[1024];
        struct rrd_db *         rrd;
        struct timeval          tnow;
        int                     i, rrdend;

        gettimeofday(&tnow, NULL);

	sprintf (buf, WMR_RRD_OUT_FILE, rrdtool_save_path, TABLES[table], sensor);
        if (( rrd = rrd_open(buf)) == NULL) 
	{
	    if( debugEn > 0 )
	    {
		// wmr->rrdEn = 0; ???
		sprintf ( err_string, WMR_RRDTOOL_C_TXT_1, buf);
		syslog_msg (syslogEn, err_string);
		rrdEn = 0;
		return;
	    }
        }

	if (rrd_update(rrd, tnow, updates, num ) < 0) 
	{
		if( debugEn > 0 )
		{
		    sprintf ( err_string, WMR_RRDTOOL_C_TXT_2, buf, errno, num );
		    syslog_msg (syslogEn, err_string);
		}

    	} else {

	    if( debugEn > 3 )
	    {
    		for(i = 0; i <= (num - 1); i++)
		{
		    sprintf ( err_string, WMR_RRDTOOL_C_TXT_3, num, i, updates[i] );
		    syslog_msg (syslogEn, err_string);
		}
	    }

	    if( debugEn > 2 )
	    {
		sprintf ( err_string, WMR_RRDTOOL_C_TXT_4, buf, num );
		syslog_msg (syslogEn, err_string);
	    }

	}


    if((rrdend = rrd_close(rrd)) != 0)
    {
	    if( debugEn > 0 )
	    {
		sprintf ( err_string, WMR_RRDTOOL_C_TXT_5, rrdend, errno);
		syslog_msg (syslogEn, err_string);
	    }
    }

return;
}

int rrdtool_check(char *rrdtool_exec_path)
{
FILE *fd1;

    if (!(fd1 = fopen(rrdtool_exec_path, "r"))) 
    {
	return(WMR_EXIT_FAILURE);
    }
    fclose (fd1);

return(WMR_EXIT_SUCCESS);
}

void rrdtool_exec ( char *rrdtool_exec_path, char *rrdtool_save_path, int table, int sensor, char *msg, int * rrdEn, int syslogEn, int debugEn )
{
FILE *fd1;
char buf[1024];

    if (rrdtool_check(rrdtool_exec_path) != WMR_EXIT_SUCCESS)
    {
        if( debugEn > 0 )
        {
            sprintf ( err_string, WMR_RRDTOOL_C_TXT_7, rrdtool_exec_path);
            syslog_msg (syslogEn, err_string);
        }

    return;
    }
    
    if( debugEn > 2 )
    {
	sprintf ( err_string, WMR_RRDTOOL_C_TXT_6, TABLES[table], sensor);
	syslog_msg (syslogEn, err_string);
    }

    sprintf (buf, WMR_RRD_OUT_FILE, rrdtool_save_path, TABLES[table], sensor);
		
    if (!(fd1 = fopen(buf, "r")))
    {
	if( debugEn > 1 )
	{
	    sprintf ( err_string, WMR_RRDTOOL_C_TXT_8, buf);
	    syslog_msg (syslogEn, err_string);
	}

	sprintf (buf, WMR_RRD_CREATE_PAR[table], rrdtool_exec_path, rrdtool_save_path, TABLES[table], sensor, WMR_RRD_CREATE_BASE);
	if(system (buf) != 0)
	{
	    sprintf ( err_string, WMR_RRDTOOL_C_TXT_9, buf);
	    syslog_msg (syslogEn, err_string);
	    return;
	}

    } else {
        fclose (fd1);
    }

	sprintf (buf, WMR_RRD_UPDATE_FILE, rrdtool_exec_path, rrdtool_save_path, TABLES[table], sensor, msg);
	if(system (buf) != 0)
	{
	    sprintf ( err_string, WMR_RRDTOOL_C_TXT_10, buf);
	    syslog_msg (syslogEn, err_string);
	} else {
	    if( debugEn > 2 )
	    {
		sprintf ( err_string, WMR_RRDTOOL_C_TXT_11, buf);
		syslog_msg (syslogEn, err_string);
	    }
	}


} 

