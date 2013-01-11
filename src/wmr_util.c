/**
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
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define GENERAL_UTIL 1
#include "wmr_wmr.h"
#include "wmr_weather.h"
#include "wmr_ext.h"

/****************************
  WEATHER methods
 ****************************/

WEATHER *weather_new( int seln, key_t shm_key, char * fname, int debugEn )
{
    int shmID;
    WEATHER *weather = NULL;
    key_t shmKey;
    struct shmid_ds shmstat;

    switch(seln)
    {
        case 0:
		if ( (int) ( shmKey = ftok("./", 1) )  < 0 )
		{
    		    printf (WMR_UTIL_C_TXT_1 );
		    perror("- ftok ");
		    exit(WMR_EXIT_FAILURE);
		}
                if ( (shmID = shmget( shmKey, sizeof(WEATHER), 0666 | IPC_CREAT )) < 0 )
                // if ( (shmID = shmget( shmKey, sizeof(WEATHER), 0666 | IPC_CREAT | IPC_EXCL )) < 0 )
                {
                    printf (WMR_UTIL_C_TXT_2, seln, shmKey, shmID );
		    perror("- shmget ");

		    if ( shmID == -1 )
		    {
			printf (WMR_UTIL_C_TXT_3, shmID);
			shmctl( shmget(shmKey, 0, 0666), IPC_RMID, NULL);
		    }

                    exit(WMR_EXIT_FAILURE);
                }
                if ( (int) ( weather = shmat(shmID, NULL, 0) ) == -1 )
                {
                    printf (WMR_UTIL_C_TXT_4, shm_key );
		    perror("- shmat ");
                    exit(WMR_EXIT_FAILURE);
                }
                memset(weather, 0, sizeof(WEATHER));
                weather->run.shmid = shmKey;
		weather->run.shmhn[seln] = shmID;
                break;
        case 1:
                if ( shm_key <= 0 )
                {
                    printf (WMR_UTIL_C_TXT_5);
                    exit(WMR_EXIT_FAILURE);
                }
                if ( (shmID = shmget( shm_key, sizeof(WEATHER), 0666 )) < 0 )
                //if ( (shmID = shmget( shm_key, 0, 0666 )) < 0 )
                {
                    printf (WMR_UTIL_C_TXT_6, seln, shm_key, shmID);
		    perror("- shmget ");
                    exit(WMR_EXIT_FAILURE);
                }
                if ( (int) ( weather = shmat(shmID, NULL, 0) ) == -1 )
                {
                    printf (WMR_UTIL_C_TXT_7, shm_key );
		    perror("- shmat ");
                    exit(WMR_EXIT_FAILURE);
                }

		weather->run.shmhn[seln] = shmID;
                break;
    }


    if ( debugEn > 3 )
    {
	shmctl(shmID, IPC_STAT, &shmstat);
	printf( WMR_UTIL_C_TXT_8, \
    		seln, \
		shmID, \
    		(int) shmstat.shm_nattch, \
    		shmstat.shm_cpid, \
    		shmstat.shm_lpid \
    		);
    }

return weather;
}

int weather_close(WEATHER *weather, key_t shmID, pid_t MAINpid, int seln, int syslogEn, int debugEn )
{
    int shmHN;
    struct shmid_ds shmstat;

    if( MAINpid != getpid() )
    {
	seln = 1;
    }

    shmHN = weather->run.shmhn[seln];

    if ( debugEn > 3 )
    {
	printf (WMR_UTIL_C_TXT_9, getpid(), MAINpid, seln );

	shmctl(shmHN, IPC_STAT, &shmstat);
	printf( WMR_UTIL_C_TXT_8, \
    		seln, \
		shmHN, \
    		(int) shmstat.shm_nattch, \
    		shmstat.shm_cpid, \
    		shmstat.shm_lpid \
    		);
    }

    if( (shmdt((void *) weather)) == -1)
    {
	if ( debugEn > 0 )
	{
    	    printf ( WMR_UTIL_C_TXT_11, seln, errno, shmID, shmHN );
	    perror("- shmdt ");
	}
    } else {
	if ( debugEn > 2 )
	{
    	    printf ( WMR_UTIL_C_TXT_12, seln, shmID, shmHN );
	}
    }

    switch(seln)
    {
        case 0:
                if( (shmctl(shmHN, IPC_RMID, (struct shmid_ds *) NULL)) == -1)
		{
		    if ( debugEn > 0 )
		    {
    			printf ( WMR_UTIL_C_TXT_13, seln, errno, shmID, shmHN );
			perror("- shmctl ");
		    }
		} else {
		    if ( debugEn > 2 )
		    {
    			printf ( WMR_UTIL_C_TXT_14, seln, shmID, shmHN );
		    }
		}
                break;
        case 1:
                break;

    }

return WMR_EXIT_SUCCESS;
}

/****************************
  WMR methods
 ****************************/
WMR *wmr_new( void )
{

    WMR *wmr = malloc(sizeof(WMR));
    if (wmr == NULL)
    {
        return NULL;
    }

    memset(wmr, 0, sizeof(WMR));

    wmr->remain = 0;
    wmr->buffer = malloc(BUF_SIZE);
    if (wmr->buffer == NULL)
    {
      free(wmr);
      return NULL;
    }

    wmr->data_fh                = NULL;
    wmr->data_filename          = malloc(CNF_PATH_SIZE);
    wmr->db_name                = malloc(CNF_PATH_SIZE);
    wmr->conf_path              = malloc(CNF_PATH_SIZE);
    wmr->rrdtool_exec_path      = malloc(CNF_PATH_SIZE);
    wmr->rrdtool_save_path      = malloc(CNF_PATH_SIZE);
    wmr->logrotate_path         = malloc(CNF_PATH_SIZE);
    wmr->alarm_path             = malloc(CNF_PATH_SIZE);
    wmr->lock_file              = malloc(CNF_PATH_SIZE);
    wmr->curtime                = malloc(STR_TIME_SIZE);
    wmr->upd_exec_path          = malloc(CNF_PATH_SIZE);

    strcpy(wmr->conf_path,  WMR_CONFG_FILE );

return wmr;
}

int wmr_close( WMR *wmr )
{
    hid_return ret;

    if(wmr->hid)
    {
        ret = hid_close(wmr->hid);
        if (ret != HID_RET_SUCCESS)
        {
        sprintf (err_string, WMR_UTIL_C_TXT_15, ret);
        syslog_msg (wmr->syslogEn, err_string);
        return WMR_EXIT_NORMAL;
        }

        hid_delete_HIDInterface(&wmr->hid);
        wmr->hid = NULL;

        ret = hid_cleanup();
        if (ret != HID_RET_SUCCESS)
        {
        sprintf (err_string, WMR_UTIL_C_TXT_16, ret);
        syslog_msg (wmr->syslogEn, err_string);
        return WMR_EXIT_NORMAL;
        }
    }

free(wmr);
return WMR_EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////

void get_curtime( char ** curtime )
{
    char tstr[16];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = gmtime(&t);
    strftime(tstr, sizeof(tstr), "%Y%m%d%H%M%S", tmp);
    memcpy( *curtime, tstr, STR_TIME_SIZE);

}

void wmr_print_state( unsigned int usb_hid, int syslogEn )
{
  sprintf (err_string, "- WMR->HID: %08x\n", usb_hid);
  syslog_msg (syslogEn, err_string);
}

int logrotate ( sqlite3 ** db, FILE ** data_fh, char *logrotate_path, int fileEn,  char *data_filename, int sqlEn, char * db_name, int rrdEn, char * rrdtool_save_path, int syslogEn, int debugEn )
{
    char msg[1024];


    if ((sqlEn == 1 ) && ( *db )) 
    {
	wmr_sqldb_close(*&db);
    }

    if ((fileEn == 1 ) && ( *data_fh ))
    { 
	wmr_file_close( *&data_fh);
    }

    sprintf ( msg, WMR_TMPL_LOGROTATE,  logrotate_path, fileEn,  data_filename,  sqlEn,  db_name, rrdEn,  rrdtool_save_path ); 

    if(system (msg) != 0)
    {
        sprintf ( err_string, WMR_UTIL_C_TXT_17, msg);
	syslog_msg (syslogEn, err_string);
	return WMR_EXIT_NORMAL; 

    } else {

	if( debugEn > 0)         
        {
		sprintf ( err_string, WMR_UTIL_C_TXT_18, msg);
		syslog_msg (syslogEn, err_string);
        }
    }


return WMR_EXIT_SUCCESS;
}

int lock_state( char * lock_file, int daemonKill, int syslogEn, int debugEn, int run, int rpid )
{
    FILE *fdt;

    switch(run)
    {
    case 0:

	if ( daemonKill == 0 )
	{
	    fdt = fopen( lock_file, "r");
	    if ( fdt )
	    {
    		sprintf ( err_string, WMR_UTIL_C_TXT_19, lock_file);
    	        syslog_msg (syslogEn, err_string);
		fclose (fdt);
	        return (WMR_EXIT_NORMAL);
	        break;

	    } else {

		fdt = fopen( lock_file, "w");
		if ( fdt )
		{
		    fprintf (fdt, "%d\n", getpid());
		    fclose (fdt);

		    if( debugEn > 0)         
    		    {
			sprintf ( err_string, WMR_UTIL_C_TXT_20, lock_file);
			syslog_msg (syslogEn, err_string);
    		    }
		} else {         

		    sprintf ( err_string, WMR_UTIL_C_TXT_21, lock_file);
		    syslog_msg (syslogEn, err_string);
		    return (WMR_EXIT_NORMAL);
		    break;
    		}
	    }

	}
	return WMR_EXIT_SUCCESS;
	break;

    case 1:

	if ( daemonKill == 0 )
	{
	    if (unlink (lock_file)) 
	    {

		sprintf ( err_string, WMR_UTIL_C_TXT_22, lock_file);
		syslog_msg (syslogEn, err_string );
		return (WMR_EXIT_NORMAL);
		break;

	    } else {

		if( debugEn > 0)         
    		{
		    sprintf ( err_string, WMR_UTIL_C_TXT_23, lock_file);
		    syslog_msg (syslogEn, err_string);
    		}

	    return WMR_EXIT_SUCCESS;
	    }
	}
	break;

    case 2:

	if ( daemonKill == 0 )
	{
	    if ( (fdt = fopen( lock_file, "w")) )
	    {
		fprintf (fdt, "%d\n", getpid());
		fclose (fdt);

		if( debugEn > 0)         
    		{
		    sprintf ( err_string, WMR_UTIL_C_TXT_24, lock_file);
		    syslog_msg (syslogEn, err_string);
    		}
	    } else {         

		    sprintf ( err_string, WMR_UTIL_C_TXT_25, lock_file);
		    syslog_msg (syslogEn, err_string);
		    return (WMR_EXIT_NORMAL);
		    break;
    	    }
	}
	break;

    case 3:
		fdt = fopen( lock_file, "a");
		if ( fdt )
		{
		    fprintf (fdt, "%d\n", rpid);
		    fclose (fdt);

		    if( debugEn > 2 )         
    		    {
			sprintf ( err_string, WMR_UTIL_C_TXT_26, rpid, lock_file);
			syslog_msg (syslogEn, err_string);
    		    }
		} else {         

		    if( debugEn > 0 )         
    		    {
			sprintf ( err_string, WMR_UTIL_C_TXT_27, rpid, lock_file);
		        syslog_msg (syslogEn, err_string);
		    }
		    return (WMR_EXIT_NORMAL);
		    break;
    		}
    break;

    case 4:
		if (unlink (lock_file)) 
		{
		    if( debugEn > 0 )         
    		    {
			sprintf ( err_string, WMR_UTIL_C_TXT_22, lock_file);
			syslog_msg (syslogEn, err_string );
		    }
		    return (WMR_EXIT_NORMAL);
		    break;
		} else {
		    if( debugEn > 0 )         
    		    {
			sprintf ( err_string, WMR_UTIL_C_TXT_23, lock_file);
			syslog_msg (syslogEn, err_string );
		    }
		}

    break;
    }

return WMR_EXIT_SUCCESS;
}

int kill_prog( char * lock_file, int syslogEn, int debugEn )
{
    FILE *fdl;
    char lock_pid[16];
    int	 daemon_pid;

    if (!(fdl = fopen (lock_file, "r"))) 
    {
	if( debugEn > 0 )         
    	{
	    sprintf ( err_string, WMR_UTIL_C_TXT_28, lock_file);
	    syslog_msg (syslogEn, err_string);
	}
	return (WMR_EXIT_NORMAL);			
    }
	
    fgets(lock_pid, 15, fdl);
    daemon_pid = atoi(lock_pid);
    fclose (fdl);

    if (killpg(daemon_pid, SIGTERM) == -1)
    {
	if( debugEn > 0 )         
    	{
	    sprintf (err_string, WMR_UTIL_C_TXT_29, daemon_pid );
	    syslog_msg (syslogEn, err_string );
	}
	return (WMR_EXIT_NORMAL);			
    }
	    
return (WMR_EXIT_SUCCESS);
}
