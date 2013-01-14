/**
 * Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol. Tested on wmrs200.
 *
 * Copyright:
 * 2009 Barnaby Gray <barnaby@pickle.me.uk>
 * 2012 Den68 <idg68@yandex.ru>
 * Latest download URL: http://www.nkl.ru/support/wmr/
 * Global download URL: http://code.google.com/p/wmr/
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <libhid/hid.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sqlite3.h>
#include "wmr_build.h"
#include "wmr_version.h"
#include "wmr_struct.h"
#include "wmr_rrdtool.h"
#include "wmr_convert.h"
#include "wmr.h"

int run;
WMR *wmr = NULL;

void dump_packet(unsigned char *packet, int len)
{
    int i;

    sprintf (err_string, "Receive packet len %d: ", len);
    syslog_msg (wmr->syslogEn, err_string);
    for(i = 0; i < len; ++i)
    {
	sprintf (err_string, "%02x ", (int)packet[i]);
	syslog_msg (wmr->syslogEn, err_string);
    }
    sprintf (err_string, "\n");
    syslog_msg (wmr->syslogEn, err_string);
}

/****************************
  WMR methods
 ****************************/

WMR *wmr_new() 
{
    WMR *wmr = malloc(sizeof(WMR));
    wmr->remain = 0;
    wmr->buffer = malloc(BUF_SIZE);
    if (wmr->buffer == NULL) 
    {
      free(wmr);
      return NULL;
    }
    wmr->data_fh = NULL;
    wmr->data_filename 	= malloc(CNF_PATH_SIZE);
    wmr->db_name 	= malloc(CNF_PATH_SIZE);
    wmr->conf_path 	= malloc(CNF_PATH_SIZE);
    strcpy(wmr->conf_path,  WMR_CONFG_FILE );
    wmr->rrdtool_exec_path = malloc(CNF_PATH_SIZE);
    wmr->rrdtool_save_path = malloc(CNF_PATH_SIZE);
    wmr->logrotate_path = malloc(CNF_PATH_SIZE);
    wmr->alarm_path = malloc(CNF_PATH_SIZE);
    wmr->lock_file = malloc(CNF_PATH_SIZE);

    wmr->syslogEn	= 0;
    wmr->viewEn		= 0;
    wmr->daemonEn	= 0;
    wmr->daemonRun	= 0;
    wmr->daemonKill	= 0;

    wmr->sens_temp[0]=0;
    wmr->sens_temp[1]=0;
    wmr->sens_temp[2]=0;
    wmr->sens_temp[3]=0;
    wmr->sens_temp[4]=0;
    wmr->sens_temp[5]=0;
    wmr->sens_temp[6]=0;
    wmr->sens_temp[7]=0;
    wmr->sens_temp[8]=0;
    wmr->sens_temp[9]=0;
    wmr->sens_temp[10]=0;

    wmr->sens_humidity[0]=0;
    wmr->sens_humidity[1]=0;
    wmr->sens_humidity[2]=0;
    wmr->sens_humidity[3]=0;
    wmr->sens_humidity[4]=0;
    wmr->sens_humidity[5]=0;
    wmr->sens_humidity[6]=0;
    wmr->sens_humidity[7]=0;
    wmr->sens_humidity[8]=0;
    wmr->sens_humidity[9]=0;
    wmr->sens_humidity[10]=0;

    wmr->sens_water[0]=0;
    wmr->sens_water[1]=0;
    wmr->sens_water[2]=0;
    wmr->sens_water[3]=0;
    wmr->sens_water[4]=0;

    wmr->sens_pressure = 0;
    wmr->sens_wind = 0;
    wmr->sens_rain = 0;
    wmr->sens_uv = 0;

    wmr->alarm_temp[0][0]=0;
    wmr->alarm_temp[0][1]=0;
    wmr->alarm_temp[1][0]=0;
    wmr->alarm_temp[1][1]=0;
    wmr->alarm_temp[2][0]=0;
    wmr->alarm_temp[2][1]=0;
    wmr->alarm_temp[3][0]=0;
    wmr->alarm_temp[3][1]=0;
    wmr->alarm_temp[4][0]=0;
    wmr->alarm_temp[4][1]=0;
    wmr->alarm_temp[5][0]=0;
    wmr->alarm_temp[5][1]=0;
    wmr->alarm_temp[6][0]=0;
    wmr->alarm_temp[6][1]=0;
    wmr->alarm_temp[7][0]=0;
    wmr->alarm_temp[7][1]=0;
    wmr->alarm_temp[8][0]=0;
    wmr->alarm_temp[8][1]=0;
    wmr->alarm_temp[9][0]=0;
    wmr->alarm_temp[9][1]=0;
    wmr->alarm_temp[10][0]=0;
    wmr->alarm_temp[10][1]=0;

    wmr->alarm_humidity[0][0]=0;
    wmr->alarm_humidity[0][1]=0;
    wmr->alarm_humidity[1][0]=0;
    wmr->alarm_humidity[1][1]=0;
    wmr->alarm_humidity[2][0]=0;
    wmr->alarm_humidity[2][1]=0;
    wmr->alarm_humidity[3][0]=0;
    wmr->alarm_humidity[3][1]=0;
    wmr->alarm_humidity[4][0]=0;
    wmr->alarm_humidity[4][1]=0;
    wmr->alarm_humidity[5][0]=0;
    wmr->alarm_humidity[5][1]=0;
    wmr->alarm_humidity[6][0]=0;
    wmr->alarm_humidity[6][1]=0;
    wmr->alarm_humidity[7][0]=0;
    wmr->alarm_humidity[7][1]=0;
    wmr->alarm_humidity[8][0]=0;
    wmr->alarm_humidity[8][1]=0;
    wmr->alarm_humidity[9][0]=0;
    wmr->alarm_humidity[9][1]=0;
    wmr->alarm_humidity[10][0]=0;
    wmr->alarm_humidity[10][1]=0;

    wmr->alarm_water[0][0]=0;
    wmr->alarm_water[0][1]=0;
    wmr->alarm_water[1][0]=0;
    wmr->alarm_water[1][1]=0;
    wmr->alarm_water[2][0]=0;
    wmr->alarm_water[2][1]=0;
    wmr->alarm_water[3][0]=0;
    wmr->alarm_water[3][1]=0;
    wmr->alarm_water[4][0]=0;
    wmr->alarm_water[4][1]=0;

    wmr->alarm_pressure[0]=0;
    wmr->alarm_pressure[1]=0;
    wmr->alarm_pressure[2]=0;
    wmr->alarm_wind[0]=0;
    wmr->alarm_wind[1]=0;
    wmr->alarm_wind[2]=0;
    wmr->alarm_rain[0]=0;
    wmr->alarm_rain[1]=0;
    wmr->alarm_rain[2]=0;
    wmr->alarm_uv[0]=0;
    wmr->alarm_uv[1]=0;
    wmr->alarm_uv[2]=0;

    wmr->sv_temp = 0;
    wmr->sv_pressure = 5;
    wmr->sv_wind = 0;
    wmr->sv_water = 0;
    wmr->sv_rain = 0;
    wmr->sv_uv = 0;

return wmr;
}

int wmr_send_packet_init(WMR *wmr) {
    int ret;

    ret = hid_set_output_report(wmr->hid, PATH_IN, PATHLEN, (char*)INIT_PACKET1, sizeof(INIT_PACKET1));
    if (ret != HID_RET_SUCCESS) 
    {
	sprintf (err_string, "hid_set_output_report failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
    }

return WMR_EXIT_SUCCESS;
}

int wmr_send_packet_ready(WMR *wmr) {
    int ret;
    
    ret = hid_set_output_report(wmr->hid, PATH_IN, PATHLEN, (char*)INIT_PACKET2, sizeof(INIT_PACKET2));
    if (ret != HID_RET_SUCCESS) 
    {
	sprintf (err_string, "hid_set_output_report failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
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
	sprintf (err_string, "hid_init failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
    }

    wmr->hid = hid_new_HIDInterface();
    if (wmr->hid == 0) 
    {
	sprintf (err_string, "hid_new_HIDInterface() failed, out of memory?\n");
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
    }

    retries = 5;
    while(retries > 0) 
    {
        ret = hid_force_open(wmr->hid, 0, &matcher, 10);
	if (ret == HID_RET_SUCCESS) break;

	sprintf (err_string, "Open failed, sleeping 5 seconds before retrying..\n");
	syslog_msg (wmr->syslogEn, err_string);
	sleep(5);

	--retries;
    }

    if (ret != HID_RET_SUCCESS) 
    {
	sprintf (err_string, "hid_force_open failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
    }

    ret = hid_write_identification(stdout, wmr->hid);
    if (ret != HID_RET_SUCCESS) 
    {
	sprintf (err_string, "hid_write_identification failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
    }

    if ( wmr_send_packet_init(wmr) != 0 )  { return WMR_EXIT_NORMAL; }
    if ( wmr_send_packet_ready(wmr) != 0 ) { return WMR_EXIT_NORMAL; }

    return WMR_EXIT_SUCCESS;
}

void wmr_print_state(WMR *wmr) 
{
  sprintf (err_string, "- WMR->HID: %08x\n", (unsigned int)wmr->hid);
  syslog_msg (wmr->syslogEn, err_string);
}

int wmr_close(WMR *wmr) 
{
    hid_return ret;

    if(wmr->hid)
    {
	ret = hid_close(wmr->hid);
	if (ret != HID_RET_SUCCESS) 
	{
	sprintf (err_string, "hid_close failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
	}

	hid_delete_HIDInterface(&wmr->hid);
	wmr->hid = NULL;

	ret = hid_cleanup();
	if (ret != HID_RET_SUCCESS) 
	{
	sprintf (err_string, "hid_cleanup failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL;
	}
    }

free(wmr);
return WMR_EXIT_SUCCESS;
}

void wmr_read_packet(WMR *wmr)
{
    int ret, len;

    ret = hid_interrupt_read(wmr->hid,
			     USB_ENDPOINT_IN + 1,
			     (char*)wmr->buffer,
			     RECV_PACKET_LEN,
			     0);

    if (ret != HID_RET_SUCCESS) 
    {
	sprintf (err_string, "hid_interrupt_read failed with return code %d\n", ret);
	syslog_msg (wmr->syslogEn, err_string);
	// exit(WMR_EXIT_FAILURE);
	return;
    }
    
    len = wmr->buffer[0];
    if (len > 7) len = 7; /* limit */
    wmr->pos = 1;
    wmr->remain = len;
    
    /* dump_packet(wmr->buffer + 1, wmr->remain); */
}

int wmr_read_byte(WMR *wmr)
{
    while(wmr->remain == 0) {
	wmr_read_packet(wmr);
    }
    wmr->remain--;

    return wmr->buffer[wmr->pos++];
}

int verify_checksum(unsigned char * buf, int len) {
    int i, ret = 0, chk;
    for (i = 0; i < len -2; ++i) {
	ret += buf[i];
    }
    chk = buf[len-2] + (buf[len-1] << 8);

    if (ret != chk) {
	sprintf (err_string, "Bad checksum: %d / calc: %d\n", ret, chk);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_FAILURE;
    }
    return WMR_EXIT_SUCCESS;
}

int wmr_log_open(WMR *wmr) 
{

    /* check for rolled log or not open */
    if (!access(wmr->data_filename, F_OK) == 0 || wmr->data_fh == NULL) 
    {
	if (wmr->data_fh != NULL) 
	{
	    fclose(wmr->data_fh);
	}

        wmr->data_fh = fopen(wmr->data_filename, "a+");

        if (wmr->data_fh == NULL) 
	{
		wmr->data_fh = stderr;
		return WMR_EXIT_FAILURE;
        }
    }

return WMR_EXIT_SUCCESS;
}

void wmr_log_close(WMR *wmr) 
{
    if (wmr->data_fh && wmr->data_fh != stdout) 
    {
	fclose(wmr->data_fh);
	wmr->data_fh = NULL;
    }
}

void wmr_log_data(WMR *wmr, char *msg)
{
    char outstr[200];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = gmtime(&t);

    strftime(outstr, sizeof(outstr), "%Y%m%d%H%M%S", tmp);

    fprintf ( wmr->data_fh, "DATA[%s]:%s\n", outstr, msg);
    fflush(wmr->data_fh);

    if( wmr->debugEn == 1)
    {
	sprintf (err_string, "LOG[%s]:%s\n", outstr, msg);
	syslog_msg (wmr->syslogEn, err_string);
    }

}

void wmr_log_sql(WMR *wmr, char *msgs, int tbln )
{
    char tmpd[200];
    char msg[200];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = gmtime(&t);

    strftime(tmpd, sizeof(tmpd), "%Y%m%d%H%M%S", tmp);

    sprintf ( msg, WMR_TMPL_SQL_INSERT, TABLES[tbln], tmpd, msgs );

    if( wmr->debugEn == 1)
    {
	sprintf (err_string, "SQL[%s]:%s\n", tmpd, msg);
	syslog_msg (wmr->syslogEn, err_string);
    }

    if ( sqlite3_exec(wmr->db, msg, 0, 0, 0) != SQLITE_OK )
    {
	sprintf (err_string, "SQL not INSERT data!: %s\n", sqlite3_errmsg(wmr->db));
	syslog_msg (wmr->syslogEn, err_string);
    }

}

int alarm_sig (WMR *wmr, int cevent, int csensor, int cstatus, int battery, int min, int max)
{
    int alarm_status=0;
    char msg[1024];

    if(min != 0 )
    {
	if(min > cstatus)
	{
	    sprintf ( msg, WMR_TMPL_ALARM, wmr->alarm_path, SENS_TYPE[cevent], csensor, cstatus, SENS_ALARM[0] ); 
	    alarm_status=1;
	}
    }

    if(max != 0 )
    {
	if(max < cstatus)
	{
	    sprintf ( msg, WMR_TMPL_ALARM, wmr->alarm_path, SENS_TYPE[cevent], csensor, cstatus, SENS_ALARM[1] ); 
	    alarm_status=1;
	}
    }

    if(battery != 0 )
    {
	sprintf ( msg, WMR_TMPL_ALARM, wmr->alarm_path, SENS_ALARM[3], csensor, cstatus, SENS_TYPE[cevent] ); 
	alarm_status=1;
    }

    if (alarm_status == 0)
    {
	return WMR_EXIT_SUCCESS;
    }

    if(system (msg) != 0)
    {
        sprintf ( err_string, "ALARM: error execute command: (%s)\nDisable alarm engine, please, solved this problem and reload config\n", msg);
	syslog_msg (wmr->syslogEn, err_string);
	wmr->alarmEn = 0;
	return WMR_EXIT_NORMAL; 
    } else {

	if( wmr->debugEn == 1)         
        {
		sprintf ( err_string, "ALARM OK: exec (%s)\n", msg);
		syslog_msg (wmr->syslogEn, err_string);
        }
    }


return WMR_EXIT_SUCCESS;
}


void wmr_handle_temp(WMR *wmr, unsigned char *data, int len)
{
    int sensor, st, smiley, trend, humidity, battery;
    float temp, dewpoint;
    char *smileyTxt = "";
    char *trendTxt = "";
    char msg[200];


    battery = (data[0] & 0x40) >> 2;
    sensor = data[2] & 0x0f;
    st = data[2] >> 4;
    smiley = st >> 2;
    trend = st & 0x03;

    if (smiley <= 3) smileyTxt = SMILIES[smiley];
    if (trend <= 2) trendTxt = TRENDS[trend];

    temp = (data[3] + ((data[4] & 0x0f) << 8)) / 10.0;
    if ((data[4] >> 4) == 0x8) temp = -temp;
    
    humidity = data[5];

    dewpoint = (data[6] + ((data[7] & 0x0f) << 8)) / 10.0;
    if ((data[7] >> 4) == 0x8) dewpoint = -dewpoint;

    if(wmr->sens_temp[sensor] != 0 )
    {
	if( temp > 0 )
	{
	    temp	+= wmr->sens_temp[sensor];
	} else {
	    temp	+= (wmr->sens_temp[sensor] * (-1));
	}

	if( dewpoint > 0 )
	{
	    dewpoint	+= wmr->sens_temp[sensor];
	} else {
	    dewpoint	+= (wmr->sens_temp[sensor] * (-1));
	}
    }

	switch(wmr->sv_temp)
	{
		case 0:
			break;
		case 1:
			cnv_c_f(temp);
			cnv_c_f(dewpoint);
			break;
	}

    if(wmr->sens_humidity[sensor] != 0 )
    {
	humidity  += wmr->sens_humidity[sensor];
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr, 0, sensor, (int)temp, battery, wmr->alarm_temp[sensor][0], wmr->alarm_temp[sensor][1]);
	alarm_sig (wmr, 1, sensor, humidity, 0, wmr->alarm_humidity[sensor][0], wmr->alarm_humidity[sensor][1]);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[0], battery, sensor, smiley, trendTxt, temp, humidity, dewpoint);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf ( msg, WMR_TMPL_SQL[0], battery, sensor, smiley, trendTxt, temp, humidity, dewpoint);
    wmr_log_sql(wmr, msg, 0);
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[0], temp, dewpoint, humidity);
    rrdtool_exec ( wmr, 0, sensor, msg );
    }

}

void wmr_handle_pressure(WMR *wmr, unsigned char *data, int len)
{
    int pressure, forecast, alt_pressure, alt_forecast;
    int maxpressure = 2816;
    char msg[200];

    pressure = (((data[3] & 0x0f) * 256) + data[2]);
    forecast = data[3] >> 4;
    alt_pressure = (((data[5] & 0x0f) * 256) + data[4]);
    alt_forecast = data[5] >> 4;

    if (pressure == maxpressure)
    {
	sprintf (err_string, "- Barometer overflow: max measurement value 1050 exceeded, reporting as 1051\n");
	syslog_msg (wmr->syslogEn, err_string);
    } else {

	if(wmr->sens_pressure != 0 )
	{
	pressure  += wmr->sens_pressure;
	alt_pressure  += wmr->sens_pressure;
	}

	switch(wmr->sv_pressure)
	{
		case 0:
			break;
		case 1:
			cnv_def_psi(pressure);
			cnv_def_psi(alt_pressure);
			break;
		case 2:
			cnv_def_bar(pressure);
			cnv_def_bar(alt_pressure);
			break;
		case 3:
			cnv_def_mbar(pressure);
			cnv_def_mbar(alt_pressure);
			break;
		case 4:
			cnv_def_mpa(pressure);
			cnv_def_mpa(alt_pressure);
			break;
		case 5:
			cnv_def_mmhg(pressure);
			cnv_def_mmhg(alt_pressure);
			break;
		case 6:
			cnv_def_inhg(pressure);
			cnv_def_inhg(alt_pressure);
			break;
	}

	if( wmr->alarmEn == 1)
	{          
	    alarm_sig (wmr, 2, 0, pressure, 0, wmr->alarm_pressure[0], wmr->alarm_pressure[1]);
	}

	if(wmr->fileEn == 1)
	{
	sprintf ( msg, WMR_TMPL_TXT[1], pressure, forecast, alt_pressure, alt_forecast);
	wmr_log_data(wmr, msg);
	}         

        if(wmr->sqlEn == 1)
	{
	sprintf ( msg, WMR_TMPL_SQL[1], pressure, forecast, alt_pressure, alt_forecast);
	wmr_log_sql(wmr, msg, 1);
	}

	if(wmr->rrdEn == 1)
	{
	sprintf ( msg, WMR_RRD_UPDATE[1], pressure, alt_pressure);
	rrdtool_exec ( wmr, 1, 0, msg );
	}
    }

}

void wmr_handle_wind(WMR *wmr, unsigned char *data, int len)
{
    int wind_dir, power, low_speed, high_speed, battery;
    char *wind_str;
    float wind_speed, avg_speed;
    char msg[200];

    battery = (data[0] & 0x40) >> 2;
    wind_dir = data[2] & 0xf;
    wind_str = WINDIES[wind_dir];
    power = data[2] >> 4;
    
    wind_speed = data[4] / 10.0;

    low_speed = data[5] >> 4;
    high_speed = data[6] << 4;
    avg_speed = (high_speed + low_speed) / 10.0;

    if(wmr->sens_wind != 0 )
    {
	wind_speed  += wmr->sens_wind;
	avg_speed   += wmr->sens_wind;
    }

	switch(wmr->sv_wind)
	{
		case 0:
			break;
		case 1:
			cnv_ms_mps(wind_speed);
			cnv_ms_mps(avg_speed);
			cnv_ms_mps(low_speed);
			cnv_ms_mps(high_speed);
			break;
		case 2:
			cnv_ms_mph(wind_speed);
			cnv_ms_mph(avg_speed);
			cnv_ms_mph(low_speed);
			cnv_ms_mph(high_speed);
			break;
	}

    if( wmr->alarmEn == 1)
    {          
        alarm_sig (wmr, 3, 0, (int)wind_speed, battery, wmr->alarm_wind[0], wmr->alarm_wind[1]);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[2], battery, power, wind_str, wind_speed, avg_speed, low_speed, high_speed);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf ( msg, WMR_TMPL_SQL[2], battery, power, wind_str, wind_speed, avg_speed, low_speed, high_speed);
    wmr_log_sql(wmr, msg, 2);
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[2], wind_speed, avg_speed);
    rrdtool_exec ( wmr, 2, 0, msg );
    }

}

void wmr_handle_rain(WMR *wmr, unsigned char *data, int len)
{
    int sensor, power, rate, battery;
    float hour, day, total;
    int smi, sho, sda, smo, syr;
    char msg[200];
    
    battery = (data[0] & 0x40) >> 2;
    sensor = data[2] & 0x0f;
    power = data[2] >> 4;
    rate = data[3];
    
    hour = ((data[5] << 8) + data[4]) * 25.4 / 100.0; /* mm */
    day = ((data[7] << 8) + data[6]) * 25.4 / 100.0; /* mm */
    total = ((data[9] << 8) + data[8]) * 25.4 / 100.0; /* mm */

    smi = data[10];
    sho = data[11];
    sda = data[12];
    smo = data[13];
    syr = data[14] + 2000;

    if(wmr->sens_rain != 0 )
    {
	rate  += wmr->sens_rain;
	hour  += wmr->sens_rain;
	day   += wmr->sens_rain;
	total += wmr->sens_rain;
    }

	switch(wmr->sv_rain)
	{
		case 0:
			break;
		case 1:
			cnv_mm_inch(rate);
			cnv_mm_inch(hour);
			cnv_mm_inch(day);
			cnv_mm_inch(total);
			break;
	}

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr, 4, 0, rate, battery, wmr->alarm_rain[0], wmr->alarm_rain[1]);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[3], battery, sensor, power, rate, hour, day, total, syr, smo, sda, sho, smi);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf (msg, WMR_TMPL_SQL[3], battery, sensor, power, rate, hour, day, total, syr, smo, sda, sho, smi);
    wmr_log_sql(wmr, msg, 3 );
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[3], rate, hour, day, total);
    rrdtool_exec ( wmr, 3, sensor, msg );
    }

}

void wmr_handle_uv(WMR *wmr, unsigned char *data, int len)
{
    int uvindex, battery;
    char msg[200];

    battery = (data[0] & 0x40) >> 2;
    uvindex = data[3] >> 4;

    if(wmr->sens_uv != 0 )
    {
	uvindex  += wmr->sens_uv;
    }

    switch(wmr->sv_uv)
    {
	case 0:
		break;
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr, 5, 0, uvindex, battery, wmr->alarm_uv[0], wmr->alarm_uv[1]);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[5], battery, uvindex);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf ( msg, WMR_TMPL_SQL[5], battery, uvindex);
    wmr_log_sql(wmr, msg, 5);
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[5], uvindex);
    rrdtool_exec ( wmr, 5, 0, msg );
    }

}


void wmr_handle_water(WMR *wmr, unsigned char *data, int len)
{
    int sensor,battery;
    float temp;
    char msg[200];

    battery = (data[0] & 0x40) >> 2;
    sensor = data[2] & 0x0f;

    temp = (data[3] + ((data[4] & 0x0f) << 8)) / 10.0;
    if ((data[4] >> 4) == 0x8)
    {
	temp = -temp;
    }

    if(wmr->sens_water[sensor] != 0 )
    {
	if( temp > 0 )
	{
	    temp	+= wmr->sens_water[sensor];
	} else {
	    temp	+= (wmr->sens_water[sensor] * (-1));
	}
    }

    switch(wmr->sv_water)
    {
	case 0:
		break;
	case 1:
		cnv_c_f(temp);
		break;
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr, 7, sensor, (int)temp, battery, wmr->alarm_water[sensor][0], wmr->alarm_water[sensor][1]);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[4], battery, sensor, temp);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf ( msg, WMR_TMPL_SQL[4], battery, sensor, temp);
    wmr_log_sql(wmr, msg, 4);
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[4], temp);
    rrdtool_exec ( wmr, 4, sensor, msg );
    }

}

void wmr_handle_clock(WMR *wmr, unsigned char *data, int len)
{
    int power, powered, battery, rf, level, mi, hr, dy, mo, yr;
    char msg[200];

    power = data[0] >> 4;
    powered = (power & 0x8) >> 3;
    battery = (power & 0x4) >> 2;
    rf = (power & 0x2) >> 1;
    level = power & 0x1;

    mi = data[4];
    hr = data[5];
    dy = data[6];
    mo = data[7];
    yr = data[8] + 2000;

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr, 6, 0, 0, battery, 0, 0);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[6], battery, powered, yr, mo, dy, hr, mi, rf, level);
    wmr_log_data(wmr, msg);
    }

    if(wmr->sqlEn == 1)
    {
    sprintf ( msg, WMR_TMPL_SQL[6], battery, powered, yr, mo, dy, hr, mi, rf, level);
    wmr_log_sql(wmr, msg, 6);
    }

    if(wmr->rrdEn == 1)
    {
    sprintf ( msg, WMR_RRD_UPDATE[6], battery, powered, level);
    rrdtool_exec ( wmr, 6, 0, msg );
    }

}

void wmr_handle_packet(WMR *wmr, unsigned char *data, int len)
{
    if (wmr->debugEn == 1)
    {
	dump_packet(data, len);
    }
    
    switch(data[1]) {
    case 0x41:
	wmr_handle_rain(wmr, data, len);
	break;
    case 0x42:
	wmr_handle_temp(wmr, data, len);
	break;
    case 0x44:
	wmr_handle_water(wmr, data, len);
	break;
    case 0x46:
	wmr_handle_pressure(wmr, data, len);
	break;
    case 0x47:
	wmr_handle_uv(wmr, data, len);
	break;
    case 0x48:
	wmr_handle_wind(wmr, data, len);
	break;
    case 0x60:
	wmr_handle_clock(wmr, data, len);
	break;
    }    
}

void wmr_read_data(WMR *wmr)
{
    int i, j, unk1, type, data_len;
    unsigned char *data;

    /* search for 0xff marker */
    i = wmr_read_byte(wmr);
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
	sprintf (err_string, "Unknown packet type: %02x, skipping\n", type);
	syslog_msg (wmr->syslogEn, err_string);
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

	if (verify_checksum(data, data_len) == 0) 
	{
	    wmr_handle_packet(wmr, data, data_len);
	}

	free(data);
    }

    /* send ack */
    wmr_send_packet_ready(wmr);
}

void _reinitwmr()
{
run = RR_WMR_REINIT;
}

void _cleanup()
{
run = RR_WMR_PREEXIT;
}

void _sighup()
{
run = RR_WMR_RCONF;
}

void _logrotate ()
{
 run = RR_WMR_LROTATE;
}

int logrotate (WMR *wmr)
{
    char msg[1024];

    sprintf ( msg, WMR_TMPL_LOGROTATE,  wmr->logrotate_path, wmr->sqlEn,  wmr->data_filename,  wmr->fileEn,  wmr->db_name, wmr->rrdEn,  wmr->rrdtool_save_path ); 

    if ((wmr->sqlEn == 1 ) && ( wmr->db )) 
    {
	sqlite3_close(wmr->db);
    }

    if ((wmr->fileEn == 1 ) && ( wmr->data_fh ))
    { 
	wmr_log_close(wmr); 
    }


    if(system (msg) != 0)
    {
        sprintf ( err_string, "LOGROTATE: error execute command: (%s)\n", msg);
	syslog_msg (wmr->syslogEn, err_string);
	return WMR_EXIT_NORMAL; 
    } else {

	if( wmr->debugEn == 1)         
        {
		sprintf ( err_string, "LOGROTATE OK: exec (%s)\n", msg);
		syslog_msg (wmr->syslogEn, err_string);
        }
    }


return WMR_EXIT_SUCCESS;
}

int sqldb_init(WMR *wmr)
{

    if( sqlite3_open( wmr->db_name, &wmr->db) )
    {
        sprintf (err_string, "SQL error: Can't open database: %s\n", sqlite3_errmsg(wmr->db));
	syslog_msg (wmr->syslogEn, err_string);
        return WMR_EXIT_NORMAL;
    }
        sprintf (err_string, "- SQL OK: Open database %s done.\n", wmr->db_name);
	syslog_msg (wmr->syslogEn, err_string);

return WMR_EXIT_SUCCESS;
}

int lock_state(WMR * wmr, int run)
{
    FILE *fdt;

    switch(run)
    {
    case 0:

	if ( wmr->daemonKill == 0 )
	{
	    fdt = fopen( wmr->lock_file, "r");
	    if ( fdt )
	    {
    		sprintf ( err_string, "\t- Another executable is running: (%s)\n\tExit this programm, run kill -TERM `pidof wmr-oregon`\n\tExit ...\n\n", wmr->lock_file);
    	        syslog_msg (wmr->syslogEn, err_string);
		fclose (fdt);
	        return (WMR_EXIT_NORMAL);
	        break;

	    } else {

		fdt = fopen( wmr->lock_file, "w");
		if ( fdt )
		{
		    fprintf (fdt, "%d\n", getpid());
		    fclose (fdt);

		    if( wmr->debugEn == 1)         
    		    {
			sprintf ( err_string, "- CREATE LOCK FILE OK: %s\n", wmr->lock_file);
			syslog_msg (wmr->syslogEn, err_string);
    		    }
		} else {         

		    sprintf ( err_string, "- CREATE LOCK FILE ERROR: %s\n- Exit...\n", wmr->lock_file);
		    syslog_msg (wmr->syslogEn, err_string);
		    return (WMR_EXIT_NORMAL);
		    break;
    		}
	    }

	}
	return WMR_EXIT_SUCCESS;
	break;

    case 1:

	if ( wmr->daemonKill == 0 )
	{
	    if (unlink (wmr->lock_file)) 
	    {

		sprintf ( err_string, "- ERROR: Can't remove LOCK FILE: %s\n", wmr->lock_file);
		syslog_msg (wmr->syslogEn, err_string );
		return (WMR_EXIT_NORMAL);
		break;

	    } else {

		if( wmr->debugEn == 1)         
    		{
		    sprintf ( err_string, "- REMOVE LOCK FILE OK: %s\n", wmr->lock_file);
		    syslog_msg (wmr->syslogEn, err_string);
    		}

	    return WMR_EXIT_SUCCESS;
	    }
	}
	break;
    case 2:
	if ( wmr->daemonKill == 0 )
	{
	    if ( (fdt = fopen( wmr->lock_file, "w")) )
	    {
		fprintf (fdt, "%d\n", getpid());
		fclose (fdt);

		if( wmr->debugEn == 1)         
    		{
		    sprintf ( err_string, "- ADDED PID to LOCK FILE OK: %s\n", wmr->lock_file);
		    syslog_msg (wmr->syslogEn, err_string);
    		}
	    } else {         

		    sprintf ( err_string, "- ADDED PID to LOCK FILE ERROR: %s\n- Exit...\n", wmr->lock_file);
		    syslog_msg (wmr->syslogEn, err_string);
		    return (WMR_EXIT_NORMAL);
		    break;
    	    }
	}
	break;
    }

return WMR_EXIT_SUCCESS;
}

int kill_prog(WMR *wmr)
{
    FILE *fdl;
    char lock_pid[16];
    int	 daemon_pid;

    if (!(fdl = fopen (wmr->lock_file, "r"))) 
    {
	sprintf ( err_string, "- ERROR: can`t read lockfile %s\n\n", wmr->lock_file);
	syslog_msg (wmr->syslogEn, err_string);
	return (WMR_EXIT_NORMAL);			
    }
	
    fgets(lock_pid, 15, fdl);
    daemon_pid = atoi(lock_pid);
    fclose (fdl);

    if (killpg(daemon_pid, SIGTERM) == -1)
    {
	sprintf (err_string, "- ERROR: can`t STOP daemon PID %d\n\n", daemon_pid );
	syslog_msg (wmr->syslogEn, "- ERROR: can`t STOP daemon\n\n" );
	return (WMR_EXIT_NORMAL);			
    }
	    
return (WMR_EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    pid_t pid, sid;

    wmr = wmr_new();
    if (wmr == NULL) 
    {
      printf ("- WMR initialization failed\n\n");
      exit(WMR_EXIT_FAILURE);
    }

    sprintf (err_string,  WMR_HEADER_INFO, NUM_VERSION, DATA_VERSION );
    syslog_msg (wmr->syslogEn, err_string);

    sprintf ( err_string, "/var/lock/%s.lock",argv[0]);
    strncpy(wmr->lock_file, err_string, strlen(err_string));


    signal(SIGINT,  _cleanup);
    signal(SIGTERM, _cleanup);
    signal(SIGHUP,  _sighup);
    signal(SIGUSR1, _reinitwmr);
    signal(SIGUSR2, _logrotate);


run = RR_WMR_ARGV; 

//////////////////
//
    while(true)
    {

    	switch(run) 
	{
    	case RR_WMR_DATA:
		wmr_read_data(wmr);
		break;
    	case RR_WMR_REINIT:
		sprintf (err_string, "- ReInit WMR USB device...\n");
		syslog_msg (wmr->syslogEn, err_string);
		if (wmr != NULL) { wmr_close(wmr); }
		wmr = wmr_new();
		if (wmr == NULL) 
		{
    		    printf ("- WMR reinitialization failed\n\n");
		    lock_state(wmr,1);
    		    exit(WMR_EXIT_FAILURE);
		    break;
		}
		run = RR_WMR_INIT_USB;
		break;
    	case RR_WMR_LROTATE:
		if (logrotate(wmr) != 0 ) 
		{ 
		    run = RR_WMR_PREEXIT;
		    break;
		}
		run = RR_WMR_INIT_DATA;
		break;
	case RR_WMR_PREEXIT:
		sprintf (err_string, "- Caught signal, cleaning up\n\n");
		syslog_msg (wmr->syslogEn, err_string);
		if ((wmr->fileEn == 1 ) && ( wmr->data_fh ))	{ wmr_log_close(wmr); }
		if ((wmr->sqlEn  == 1 ) && ( wmr->db )) 	{ sqlite3_close(wmr->db); }
		if (lock_state(wmr,1) == WMR_EXIT_SUCCESS )	{ syslog_msg (wmr->syslogEn, "- PID remove OK\n"); }
		run = RR_WMR_EXIT;
		break;
	case RR_WMR_EXIT:
		if (wmr != NULL) 				{ wmr_close(wmr); wmr = NULL; }
		printf("\n- %s EXIT Succesfull\n", argv[0]);
		exit(WMR_EXIT_SUCCESS);
		break;
	case RR_WMR_ARGV:
		switch(read_arguments(wmr, argc, argv))
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
		if ( lock_state(wmr,0) == WMR_EXIT_NORMAL ) 	{ run = RR_WMR_EXIT; break; }
		sprintf (err_string, "- Opening WMR USB device...\n");
		syslog_msg (wmr->syslogEn, err_string);
    		if ( wmr_init(wmr) != 0) 
    		{
			sprintf (err_string, "- Failed to init USB device, exiting.\n\n");
			syslog_msg (wmr->syslogEn, err_string);
			run = RR_WMR_PREEXIT;
    		} else {
			sprintf (err_string, "- Found on USB: %s\n", wmr->hid->id);
			syslog_msg (wmr->syslogEn, err_string);
			wmr_print_state(wmr);
			run = RR_WMR_RCONF;
		}	
		break;
	case RR_WMR_RCONF:
		if( read_cnfile(wmr) != 0)
		{
			sprintf (err_string, "- Cannot read config file (%s), exiting.\n", wmr->conf_path );
			syslog_msg (wmr->syslogEn, err_string);
			if (wmr != NULL) { wmr_close(wmr); wmr = NULL; }
			run = RR_WMR_PREEXIT;
    		} else {
			sprintf (err_string, "- Read config file (%s), done.\n", wmr->conf_path );
			syslog_msg (wmr->syslogEn, err_string);
			run = RR_WMR_INIT_DATA;
    		}
		break;
	case RR_WMR_INIT_DATA:
		if (wmr->sqlEn == 1 )
		{
			if ( wmr->db )
			{
				sqlite3_close(wmr->db);
			}
			if ( sqldb_init(wmr) != 0 ) 
			{ 
				sprintf (err_string, "- SQL Error - exit\n\n");  
				syslog_msg (wmr->syslogEn, err_string);
				run = RR_WMR_PREEXIT;
				break;
			}

		}
		if (wmr->fileEn == 1 )
		{
			if( wmr->data_fh )
			{ 
				wmr_log_close(wmr); 
			}
			if( wmr_log_open(wmr) )
			{
				sprintf (err_string, "- FILE Error: Couldn't open data log - exit\n\n");
				syslog_msg (wmr->syslogEn, err_string);
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
				sprintf (err_string, "- DAEMON Error: Couldn't fork - exit\n\n");
				syslog_msg (wmr->syslogEn, err_string);
				lock_state(wmr,1);
        			exit(WMR_EXIT_FAILURE);
			} else if (pid > 0) 
			{
				printf ("- DAEMON mode started...\n\n");
				exit (WMR_EXIT_SUCCESS);				
			}

			umask(0);
			sid = setsid();
			if (sid < 0) 
			{
				sprintf (err_string, "- DAEMON Error: Couldn't set sid - exit\n\n");
				syslog_msg (wmr->syslogEn, err_string);
				exit(WMR_EXIT_FAILURE);
			}

			if ((chdir("/")) < 0) 
			{
				sprintf (err_string, "- DAEMON Error: Couldn't chdir - exit\n\n");
				syslog_msg (wmr->syslogEn, err_string);
				exit(WMR_EXIT_FAILURE);
			}

		lock_state(wmr,2);
		wmr->syslogEn  = 1;
		wmr->daemonRun = 1;
		}
		run = RR_WMR_DATA;
		break;
	case RR_WMR_KILL:
		if ( kill_prog(wmr) == 0 )
		{
		    sprintf (err_string, "- Requesting DAEMON %s exit ...\n\n", argv[0]);
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
	if ( wmr->db ) { sqlite3_close(wmr->db); }
	sprintf (err_string, "- Closed SQL\n");
	syslog_msg (wmr->syslogEn, err_string);
    }

    if (wmr->fileEn == 1 )
    {
	if( wmr->data_fh ) { wmr_log_close(wmr); }
	sprintf (err_string, "- Closed Log data\n");
	syslog_msg (wmr->syslogEn, err_string);
    }

    lock_state(wmr,1);

    sprintf (err_string, "- Closed WMR\n");
    syslog_msg (wmr->syslogEn, err_string);
    wmr_close(wmr);

    exit (WMR_EXIT_SUCCESS);
}

