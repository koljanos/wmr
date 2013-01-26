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

#define __USE_GNU
//#define _GNU_SOURCE

#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define GENERAL_MAIN 1
#include "wmr.h"
//
#include "wmr_updexec.h" // aggregare with wmr.h?

int run;
pthread_mutex_t job_mutex;

void dump_packet(unsigned char *packet, int len, int syslogEn)
{
    int i;

    sprintf (err_string, WMR_C_TXT_1, len);
    syslog_msg (syslogEn, err_string);
    for(i = 0; i < len; ++i)
    {
	sprintf (err_string, "%02x ", (int)packet[i]);
	syslog_msg (syslogEn, err_string);
    }
    syslog_msg (syslogEn, "\n" );
}

int wmr_send_packet_init(WMR *wmr) {
    int ret;

    ret = hid_set_output_report(wmr->hid, PATH_IN, PATHLEN, (char*)INIT_PACKET1, sizeof(INIT_PACKET1));
    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_2, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}

    return WMR_EXIT_NORMAL;
    }

return WMR_EXIT_SUCCESS;
}

int wmr_send_packet_ready(WMR *wmr) {
    int ret;
    
    ret = hid_set_output_report(wmr->hid, PATH_IN, PATHLEN, (char*)INIT_PACKET2, sizeof(INIT_PACKET2));
    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_2, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}

    return WMR_EXIT_NORMAL;
    }

return WMR_EXIT_SUCCESS;
}

int wmr_init(WMR *wmr) 
{
    hid_return ret;
    HIDInterfaceMatcher matcher = { WMR_VENDOR_ID, WMR_PRODUCT_ID, NULL, NULL, 0 };
    int retries;

    /* see include/debug.h for possible values */
    /*hid_set_debug(HID_DEBUG_ALL);*/
    /*hid_set_debug_stream(stderr);*/
    /* passed directly to libusb */
    /*hid_set_usb_debug(0);*/

    ret = hid_init();
    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_4, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}

    return WMR_EXIT_NORMAL;
    }

    wmr->hid = hid_new_HIDInterface();
    if (wmr->hid == 0) 
    {
	if( wmr->debugEn > 0 )
	{
	    syslog_msg (wmr->syslogEn, WMR_C_TXT_5 );
	}

    return WMR_EXIT_NORMAL;
    }

    retries = 5;
    while(retries > 0) 
    {
        ret = hid_force_open(wmr->hid, 0, &matcher, 10);
	if (ret == HID_RET_SUCCESS) break;

	if( wmr->debugEn > 0 )
	{
	    syslog_msg (wmr->syslogEn, WMR_C_TXT_6 );
	}
	sleep(5);

	--retries;
    }

    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_7, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}

    return WMR_EXIT_NORMAL;
    }

    ret = hid_write_identification(stdout, wmr->hid);
    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_8, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}

    return WMR_EXIT_NORMAL;
    }

    if ( wmr_send_packet_init(wmr) != 0 )  { return WMR_EXIT_NORMAL; }
    if ( wmr_send_packet_ready(wmr) != 0 ) { return WMR_EXIT_NORMAL; }

    return WMR_EXIT_SUCCESS;
}

int wmr_read_packet(WMR *wmr)
{
    int ret, len;

    ret = hid_interrupt_read(wmr->hid,
			     USB_ENDPOINT_IN + 1,
			     (char*)wmr->buffer,
			     RECV_PACKET_LEN,
			     0);

    if (ret != HID_RET_SUCCESS) 
    {
	if( wmr->debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_9, ret);
	    syslog_msg (wmr->syslogEn, err_string);
	}
	//exit(WMR_EXIT_FAILURE);
	run = RR_WMR_PREEXIT;

    return(WMR_EXIT_FAILURE);
    }
    
    len = wmr->buffer[0];
    if (len > 7) len = 7; /* limit */
    wmr->pos = 1;
    wmr->remain = len;
    
    if( wmr->debugEn > 3 )
    {
	dump_packet(wmr->buffer + 1, wmr->remain, wmr->syslogEn);
    }

return(WMR_EXIT_SUCCESS);
}

int wmr_read_byte(WMR *wmr)
{
    while(wmr->remain == 0) 
    {
	if(wmr_read_packet(wmr) == WMR_EXIT_FAILURE) { return(WMR_EXIT_FAILURE); }
    }
    wmr->remain--;

return wmr->buffer[wmr->pos++];
}

int verify_checksum(unsigned char * buf, int len, int syslogEn, int debugEn ) 
{
    int i, ret = 0, chk;
    for (i = 0; i < len -2; ++i)
    {
	ret += buf[i];
    }
    chk = buf[len-2] + (buf[len-1] << 8);

    if (ret != chk) 
    {
	if( debugEn > 0 )
	{
	    sprintf (err_string, WMR_C_TXT_10, ret, chk);
	    syslog_msg (syslogEn, err_string);
	}

    return WMR_EXIT_FAILURE;
    }

return WMR_EXIT_SUCCESS;
}

void wmr_handle_packet(WMR * wmr, WEATHER *weather, unsigned char *data, int len)
{
    if ( wmr->debugEn > 3 )
    {
	dump_packet(data, len, wmr->syslogEn);
    }
    
    switch(data[1]) {
    case 0x41:
	wmr_handle_rain( wmr, weather, data, len );
	break;
    case 0x42:
	wmr_handle_temp( wmr, weather, data, len );
	break;
    case 0x44:
	wmr_handle_water( wmr, weather, data, len );
	break;
    case 0x46:
	wmr_handle_pressure( wmr, weather, data, len );
	break;
    case 0x47:
	wmr_handle_uv( wmr, weather, data, len );
	break;
    case 0x48:
	wmr_handle_wind( wmr, weather, data, len );
	break;
    case 0x60:
	wmr_handle_mainu( wmr, weather, data, len );
	break;
    }    
}

void wmr_read_data(WMR *wmr, WEATHER *weather)
{
    int i, j, unk1, type, data_len;
    unsigned char *data;

    /* search for 0xff marker */
    i = wmr_read_byte(wmr);
    if ( i == WMR_EXIT_FAILURE) { run = RR_WMR_PREEXIT; return; }

    while(i != 0xff) 
    {
	i = wmr_read_byte(wmr);
    }

    /* search for not 0xff */
    i = wmr_read_byte(wmr);
    while(i == 0xff) 
    {
	i = wmr_read_byte(wmr);
    }
    unk1 = i;

    /* read data type */
    type = wmr_read_byte(wmr);

    /* read rest of data */
    data_len = 0;
    switch(type) 
    {
    case 0x41:
	data_len = 17;
	break;
    case 0x42:
	data_len = 12;
	break;
    case 0x44:
	data_len = 7;
	break;
    case 0x46:
	data_len = 8;
	break;
    case 0x47:
	data_len = 6;
	break;
    case 0x48:
	data_len = 11;
	break;
    case 0x60:
	data_len = 12;
	break;
    default:
	if( wmr->debugEn > 3 )
	{
	    sprintf (err_string, WMR_C_TXT_11, type);
	    syslog_msg (wmr->syslogEn, err_string);
	}
    }

    if (data_len > 0) 
    {
	data = malloc(data_len);
	data[0] = unk1;
	data[1] = type;
	for (j = 2; j < data_len; ++j) 
	{
	    data[j] = wmr_read_byte(wmr);
	}

	if (verify_checksum(data, data_len, wmr->syslogEn, wmr->debugEn) == 0) 
	{
	    get_curtime( &wmr->curtime );
	    wmr_handle_packet(wmr, weather, data, data_len);
	}

	free(data);
    }

    /* send ack */
    wmr_send_packet_ready(wmr);
}

void _reinitwmr() 	{ run = RR_WMR_REINIT; }
void _cleanup() 	{ run = RR_WMR_PREEXIT; }
void _sighup() 		{ run = RR_WMR_RCONF; }
void _logrotate () 	{ run = RR_WMR_LROTATE; }

// MAIN
int main(int argc, char *argv[])
{
    pid_t pid, sid, tpid;
    int pidstatus;
    char *fbname;
    WMR *wmr = NULL;
    WEATHER *weather = NULL;

#ifdef DEBUG
    char tmp_string[2048];
#endif

pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
pthread_mutex_init(&job_mutex, &attr);

    fbname = malloc(CNF_PATH_SIZE);
    if ( fbname == NULL)
    {
      syslog_msg (0, WMR_C_TXT_3);
      pthread_mutex_unlock(&job_mutex);
      exit(WMR_EXIT_FAILURE);
    }

// warning: cast to pointer from integer of different size
//
//    fbname =  (char *) basename( (char **) argv[0]);
    // fbname =  (char *) basename( (const char *) argv[0]);
    //memcpy(fbname, (char *) basename(argv[0]), strlen( basename(argv[0]) ) );

    wmr = wmr_new();
    if (wmr == NULL) 
    {
	syslog_msg (0,WMR_C_TXT_37);
        pthread_mutex_unlock(&job_mutex);
	exit(WMR_EXIT_FAILURE);
    }

#ifdef DEBUG
    weather = weather_new( 0,0,argv[0], 4);
#else
    weather = weather_new( 0,0,argv[0], 1);
#endif

    if (weather == NULL) 
    {
	syslog_msg (0,WMR_C_TXT_38);
        pthread_mutex_unlock(&job_mutex);
	exit(WMR_EXIT_FAILURE);
    }

    sprintf ( err_string, "/var/lock/%s.lock", fbname );
    memcpy(wmr->lock_file, err_string, strlen(err_string));

//    sprintf (err_string,  WMR_HEADER_INFO, PACKAGE_VERSION, DATA_VERSION );
    sprintf (err_string,  WMR_HEADER_INFO, PACKAGE_VERSION, PACKAGE_BUILD );
    syslog_msg (0, err_string);

    signal(SIGINT,  _cleanup);
    signal(SIGTERM, _cleanup);
    signal(SIGHUP,  _sighup);
    signal(SIGUSR1, _reinitwmr);
    signal(SIGUSR2, _logrotate);

    weather->run.MAINpid = getpid();

run = RR_WMR_ARGV; 



//////////////////
//
    while(true)
    {

    	switch(run) 
	{
    	case RR_WMR_DATA:
		wmr_read_data(wmr,weather);
		pthread_mutex_unlock(&job_mutex);

/*
		printf("- Exec: updEn: %d run.UPD[0]: %d run.UPD[1]: %d Key: %d\n", wmr->updEn, weather->run.UPD[0], weather->run.UPD[1], weather->run.shmid );
		if(( wmr->updEn == 1 ) && ( weather->run.UPD[0] == 0 ) && ( weather->run.UPD[1] == 0 ) )
		{
		    weather->run.UPD[0] = 1;
		    weather->run.UPD[1] = 1;
		    weather->run.updTime = ( wmr->run.updTime * 60 );

		    if( upd_exec_handle ( weather->run.shmid, wmr->upd_exec_path, wmr->lock_file, wmr->syslogEn, wmr->debugEn ) == 0 )
		    {
			//weather->run.UPD[0] = 0;
			//pthread_mutex_unlock(&job_mutex);
			printf( WMR_C_TXT_13, weather->run.UPDpid );
			run = RR_WMR_PREEXIT;
		    } else {
			printf( WMR_C_TXT_14, weather->run.UPDpid );
		    }
 
		}
*/
///
#ifdef DEBUG
                    sprintf (tmp_string, WMR_TMPL_UPD_EXEC_DEBUG, \
					    weather->run.shmid, \
                                            "MAIN EXEC:", \
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

                    if(wmr->debugEn > 2)
                    {
                        syslog_msg (wmr->syslogEn, WMR_C_TXT_39);
                        syslog_msg (wmr->syslogEn, tmp_string);
                        syslog_msg (wmr->syslogEn, "\n\n");
                    }

#endif

		break;
    	case RR_WMR_REINIT:
		syslog_msg (wmr->syslogEn, WMR_C_TXT_15 );
		if (wmr != NULL) { wmr_close(wmr); }
		wmr = wmr_new();
		if (wmr == NULL) 
		{
    		    printf (WMR_C_TXT_16);
		    lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 1, 0);
		    pthread_mutex_unlock(&job_mutex);
    		    exit(WMR_EXIT_FAILURE);
		    break;
		}
		run = RR_WMR_INIT_USB;
		break;
    	case RR_WMR_LROTATE:
		if (logrotate ( &wmr->db, &wmr->data_fh, wmr->logrotate_path, wmr->fileEn, wmr->data_filename, wmr->sqlEn, wmr->db_name, wmr->rrdEn, wmr->rrdtool_save_path, wmr->syslogEn, wmr->debugEn ) != 0 ) 
		{ 
		    run = RR_WMR_PREEXIT;
		    break;
		}
		run = RR_WMR_INIT_DATA;
		break;
	case RR_WMR_PREEXIT:
		if( weather->run.MAINpid != getpid() ) { run = RR_WMR_EXIT; break; }
		printf(WMR_C_TXT_17, weather->run.MAINpid, getpid());
		//weather->run.UPD[0] = 0;
		//weather->run.updTime = 0;
		sleep(3); // ?????????? to-do

		while ( (tpid = waitpid( weather->run.UPDpid, &pidstatus, WNOHANG)) > 0 )
		{
		     printf( WMR_C_TXT_18, tpid, weather->run.UPDpid, pidstatus );
		}

		while ( (tpid = waitpid( -1, &pidstatus, 0)) > 0 )
		{
		     printf( WMR_C_TXT_19, tpid, pidstatus );
		}

		syslog_msg (wmr->syslogEn, WMR_C_TXT_20 );
		run = RR_WMR_EXIT;
		break;
	case RR_WMR_EXIT:
		if ((wmr->fileEn == 1 ) && ( wmr->data_fh ))	{ wmr_file_close(&wmr->data_fh); }
		if ((wmr->sqlEn  == 1 ) && ( wmr->db )) 	{ wmr_sqldb_close(&wmr->db); }
		if (lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 1, 0) == WMR_EXIT_SUCCESS ) { syslog_msg (wmr->syslogEn, WMR_C_TXT_40); }
		if (weather != NULL) 				{ weather_close(weather, weather->run.shmid, weather->run.MAINpid, 0, wmr->syslogEn, wmr->debugEn );  }
		if (wmr->daemonKill != 1 )			{ printf(WMR_C_TXT_21, argv[0]); }
		if (wmr != NULL) 				{ wmr_close(wmr); }
		pthread_mutex_destroy(&job_mutex);
		exit(WMR_EXIT_SUCCESS);
		break;
	case RR_WMR_ARGV:
		switch(read_arguments(wmr, weather, argc, argv, fbname))
		{
		    case WMR_EXIT_SUCCESS:
				run = RR_WMR_INIT_USB;
				break;
		    case WMR_EXIT_NORMAL:
				run = RR_WMR_EXIT;
				break;
		    case WMR_EXIT_KILL:
				run = RR_WMR_KILL;
				break;
		}
		break;
	case RR_WMR_INIT_USB:
		if ( wmr->daemonKill   == WMR_EXIT_NORMAL )	{ run = RR_WMR_EXIT; break; }
		if ( lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 0, 0) == WMR_EXIT_NORMAL )
		    { run = RR_WMR_EXIT; break; }
		syslog_msg (0, WMR_C_TXT_22 );
    		if ( wmr_init(wmr) != 0) 
    		{
			syslog_msg (0, WMR_C_TXT_23 );
			run = RR_WMR_PREEXIT;
    		} else {
			sprintf (err_string, WMR_C_TXT_24, wmr->hid->id);
			syslog_msg (0, err_string);

// warning: cast from pointer to integer of different size
//
//			wmr_print_state( (unsigned int) wmr->hid, 1 );
			wmr_print_state( wmr->hid, 1 );
			run = RR_WMR_RCONF;
		}	
		break;
	case RR_WMR_RCONF:
		if( read_cnfile(wmr,weather) != 0)
		{
			sprintf (err_string, WMR_C_TXT_25, wmr->conf_path );
			syslog_msg (0, err_string);
			if (wmr != NULL) { wmr_close(wmr); }
			run = RR_WMR_PREEXIT;
    		} else {
			sprintf (err_string, WMR_C_TXT_26, wmr->conf_path );
			syslog_msg (wmr->syslogEn, err_string);
			run = RR_WMR_INIT_DATA;
    		}
		break;
	case RR_WMR_INIT_DATA:
		if (wmr->sqlEn == 1 )
		{
			if ( wmr->db )
			{
				wmr_sqldb_close(&wmr->db);
			}
			if ( wmr_sqldb_init(&wmr->db, wmr->db_name, wmr->syslogEn, wmr->debugEn) != 0 ) 
			{ 
				syslog_msg (wmr->syslogEn, WMR_C_TXT_27 );
				run = RR_WMR_PREEXIT;
				break;
			}

		}
		if (wmr->fileEn == 1 )
		{
			if( wmr->data_fh )
			{ 
				wmr_file_close(&wmr->data_fh); 
			}
			if( wmr_file_open( &wmr->data_fh, wmr->data_filename ) )
			{
				syslog_msg (wmr->syslogEn, WMR_C_TXT_28 );
				run = RR_WMR_PREEXIT;
				break;
			}
		}
		if (wmr->daemonRun == 0 )
		{
			run = RR_WMR_DAEMON;
			break;
		} else {
			run = RR_WMR_DATA;
			break;
		}
		break;
    	case RR_WMR_DAEMON:
		if (wmr->daemonEn == 1 ) 
		{ 
			pid = fork();
			if (pid < 0) 
			{
				syslog_msg (wmr->syslogEn, WMR_C_TXT_29 );
				lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 1, 0);
				pthread_mutex_unlock(&job_mutex);
        			exit(WMR_EXIT_FAILURE);
			} else if (pid > 0) 
			{
				weather->run.MAINpid = getpid();
				printf ( WMR_C_TXT_30 );
				run = RR_WMR_PREEXIT;
				break;
				//exit(WMR_EXIT_SUCCESS);				
			}

			umask(0);
			sid = setsid();
			if (sid < 0) 
			{
				syslog_msg (wmr->syslogEn, WMR_C_TXT_31 );
				pthread_mutex_unlock(&job_mutex);
				exit(WMR_EXIT_FAILURE);
			}

			if ((chdir("/")) < 0) 
			{
				syslog_msg (wmr->syslogEn, WMR_C_TXT_32 );
				pthread_mutex_unlock(&job_mutex);
				exit(WMR_EXIT_FAILURE);
			}

		lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 2, 0);
		wmr->syslogEn  = 1;
		wmr->daemonRun = 1;
		}
		run = RR_WMR_DATA;
		break;
	case RR_WMR_KILL:
		if ( kill_prog(wmr->lock_file, wmr->syslogEn, wmr->debugEn) == 0 )
		{
		    sprintf (err_string, WMR_C_TXT_33, argv[0]);
		    syslog_msg (wmr->syslogEn, err_string );
		}
		run = RR_WMR_EXIT;
		break;

	}
    } // while
//
//////////////////

    if (wmr->sqlEn == 1 )
    {
	if ( wmr->db ) { wmr_sqldb_close(&wmr->db); }
	syslog_msg (wmr->syslogEn, WMR_C_TXT_34 );
    }

    if (wmr->fileEn == 1 )
    {
	if( wmr->data_fh ) { wmr_file_close(&wmr->data_fh); }
	syslog_msg (wmr->syslogEn, WMR_C_TXT_35 );
    }

    lock_state( wmr->lock_file, wmr->daemonKill, wmr->syslogEn, wmr->debugEn, 1, 0);

    syslog_msg (wmr->syslogEn, WMR_C_TXT_36 );
    wmr_close(wmr);
    pthread_mutex_destroy(&job_mutex);

    exit(WMR_EXIT_SUCCESS);
}

