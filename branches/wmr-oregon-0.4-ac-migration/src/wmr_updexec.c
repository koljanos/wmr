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

//#include <stdio.h>
//#include <stdlib.h>
#include <syslog.h>
//#include <sys/types.h>
#include <signal.h>
//#include <unistd.h>
#include <dirent.h>
//#include <string.h>
#include <fnmatch.h>
#include <pthread.h>
// #include "wmr_wmr.h"
#define GENERAL_UPD 1
#include "wmr.h"
//#include "wmr_ext.h"
//#include "wmr_weather.h"
#include "wmr_updexec.h"

int UPDrun = 1;
int UPDpid;

void upd_scan_dir(WEATHER * weather, char * udir, int syslogEn, int debugEn)
{
    DIR *dp;
    char tmp_string[2048];
    struct dirent *fp;

    //pthread_mutex_lock(&job_mutex);    
    dp = opendir(udir);

    if (dp != NULL)
    {
	while ( (fp = readdir(dp)) != NULL )
	{
	    // if(fp->d_type == 4)
	    // {

    		if (( fnmatch( "*.sh", fp->d_name, 0) ) == 0)
    		{
		    if( debugEn > 2 )
		    {
			sprintf (tmp_string, WMR_UPDEXEC_C_TXT_1, fp->d_name, fp->d_type, fp->d_reclen);
            	        syslog_msg (syslogEn, tmp_string);
		    }

		    sprintf (tmp_string,"%s/%s", udir,fp->d_name); 

		    if(system (tmp_string) != 0)
        	    {
			if( debugEn > 0 )
			{
            	    	    sprintf (tmp_string, WMR_UPDEXEC_C_TXT_2, fp->d_name);
            	    	    syslog_msg (syslogEn, tmp_string);
			}
        	    } else {

			if( debugEn > 2 )
			{
    			    sprintf (tmp_string, WMR_UPDEXEC_C_TXT_3, udir, fp->d_name, fp->d_type);
            	    	    syslog_msg (syslogEn, tmp_string);
			}
		    }

		}
	    //}
	}

    closedir(dp);
    } else {

	if( debugEn > 0 )
	{
	    sprintf (tmp_string, WMR_UPDEXEC_C_TXT_4, udir);
            syslog_msg (syslogEn, tmp_string);
	}
    }

    //pthread_mutex_unlock(&job_mutex);
//  end
}

/*
void __cleanup(int sig_num)
{
    int pidstatus;
    int ttpid;
    int tpid = getpid();
    UPDrun = 0;
    //weather->run.UPD[0] = 0;

    printf(WMR_UPDEXEC_C_TXT_5, sig_num, tpid, getppid());
    // exit(WMR_EXIT_SUCCESS);
    // kill( UPDpid, 9);

    while ( (ttpid = waitpid( UPDpid, &pidstatus, WNOHANG)) > 0 )
    {
	printf( WMR_UPDEXEC_C_TXT_6, tpid, ttpid, getpid(), sig_num, pidstatus );
    }
}

*/

int upd_exec_handle ( key_t shmID, char * udir, char * lock_file, int syslogEn, int debugEn )
{
    int pid;
    WEATHER *weather = NULL;
    char tmp_string[4096];

/*
    if (weather == NULL)
    {
	if( debugEn > 0 )
	{
    	    syslog_msg (syslogEn,WMR_UPDEXEC_C_TXT_10);
	}

    exit(WMR_EXIT_FAILURE);
    }
*/

 // signal(SIGINT,  __cleanup);
 // signal(SIGTERM, __cleanup);

  pid = fork();

    if (pid == 0)
    {

    //pthread_mutex_lock(&job_mutex);    
    weather = weather_new( 1, shmID, "", debugEn );

    if( debugEn > 1 )
    {
	sprintf (tmp_string, WMR_UPDEXEC_C_TXT_7, pid, getpid(), weather->run.UPD[0], weather->run.updTime);
    	syslog_msg (syslogEn, tmp_string);
    }

	UPDrun = weather->run.UPD[0];

	while( UPDrun )
	{
	      //sleep( weather->run.updTime );
	      sleep( 60 );

printf("\n\n--- UPDrun %d %d ---\n\n", UPDrun, weather->run.UPD[0] );
	    if( UPDpid == 0 ) { break; }

	    if( debugEn > 2 )
	    {
                    sprintf (tmp_string, WMR_TMPL_UPD_EXEC_DEBUG, \
					    weather->run.shmid, \
                                            "MAIN UPD:", \
                                            weather->temp[0].humidity, \
                                            weather->temp[0].temp, \
                                            weather->temp[0].dewpoint, \
                                            weather->temp[0].smiley, \
                                            weather->temp[0].trendTxt, \
                                            weather->temp[0].smileyTxt, \
                                            weather->temp[1].humidity, \
                                            weather->temp[1].temp, \
                                            weather->temp[1].dewpoint, \
                                            weather->temp[1].smiley, \
                                            weather->temp[1].trendTxt, \
                                            weather->temp[1].smileyTxt, \
                                            weather->water[0].temp, \
                                            weather->uv.uvindex, \
                                            weather->pressure.pressure, \
                                            weather->pressure.forecast, \
                                            weather->rain.rate, \
                                            weather->rain.hour, \
                                            weather->rain.day, \
                                            weather->rain.total, \
                                            weather->wind.wind_dir, \
                                            weather->wind.low_speed, \
                                            weather->wind.high_speed, \
                                            weather->wind.wind_speed, \
                                            weather->wind.avg_speed, \
                                            weather->wind.wind_chill \
                                            );

    		syslog_msg (syslogEn, WMR_UPDEXEC_C_TXT_11);
            	syslog_msg (syslogEn, tmp_string);
    		syslog_msg (syslogEn, "\n");
	    }

	UPDrun = weather->run.UPD[0];
	}

	if( debugEn > 1 )
	{
            sprintf (tmp_string, WMR_UPDEXEC_C_TXT_8, pid, getpid(), getppid(), weather->run.UPD[0] );
            syslog_msg (syslogEn, tmp_string);
	}

	//weather->run.UPD[0] = 0;
	//weather_close( weather, shmID, weather->run.MAINpid, 1, syslogEn, debugEn );
	//pthread_mutex_unlock(&job_mutex);

	//exit (WMR_EXIT_SUCCESS);
	return (WMR_EXIT_SUCCESS);

    } else if (pid > 0) {
        
	weather->run.UPDpid = pid;
	UPDpid = pid;

	if( debugEn > 1 )
	{
	    sprintf (tmp_string, WMR_UPDEXEC_C_TXT_9, pid, getpid(), getppid(), weather->run.UPD[0] );
            syslog_msg (syslogEn, tmp_string);
	}

	//pthread_mutex_unlock(&job_mutex);
	//exit (WMR_EXIT_NORMAL);
	return (WMR_EXIT_NORMAL);

     } else {

	if( debugEn > 0 )
	{
         syslog_msg (syslogEn,WMR_UPDEXEC_C_TXT_12);
	}

     //weather->run.UPD[0] = 0;
     //weather_close( weather, shmID, weather->run.MAINpid, 1, syslogEn, debugEn );
     }


return (WMR_EXIT_FAILURE);
}
