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
#define GENERAL_SENSOR 1
#include "wmr_wmr.h"
#include "wmr_weather.h"
#include "wmr_convert.h"
#include "wmr_ext.h"


// HANDLE SENSOR

void wmr_handle_temp(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int sensor, st, smiley, trend, humidity, battery;
    float temp, dewpoint;
    char *smileyTxt = "";
    char *trendTxt = "";
    char msg[200];
    double rrdupd[3];

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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->temp[sensor].battery	=	battery;
	weather->temp[sensor].sensor	=	sensor;
	weather->temp[sensor].humidity	=	humidity;
	weather->temp[sensor].temp	=	temp;
	weather->temp[sensor].dewpoint	=	dewpoint;
	weather->temp[sensor].smiley	=	smiley;

	memcpy(&weather->temp[sensor].trendTxt, trendTxt, 3);
	memcpy(&weather->temp[sensor].smileyTxt, smileyTxt, 5);
	memcpy(&weather->temp[sensor].tm, wmr->curtime, STR_TIME_SIZE);
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr->alarm_path, 0, sensor, (int)temp, battery, wmr->alarm_temp[sensor][0], wmr->alarm_temp[sensor][1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn);
	alarm_sig (wmr->alarm_path, 7, sensor, humidity, 0, wmr->alarm_humidity[sensor][0], wmr->alarm_humidity[sensor][1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[0], battery, sensor, smiley, trendTxt, temp, humidity, dewpoint);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[0].tables == 0 ) && ( wmr->sqlt[0].sensor[sensor] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 0, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[0].tables = 1;
	    wmr->sqlt[0].sensor[sensor] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[0], battery, sensor, smiley, trendTxt, temp, humidity, dewpoint);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 0, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = temp;
	    rrdupd[1] = dewpoint;
	    rrdupd[2] = humidity;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 0, sensor, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[0], temp, dewpoint, humidity);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 0, sensor, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}

void wmr_handle_pressure(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int pressure, forecast, alt_pressure, alt_forecast;
    int maxpressure = 2816;
    char msg[200];
    double rrdupd[2];

    pressure = (((data[3] & 0x0f) * 256) + data[2]);
    forecast = data[3] >> 4;
    alt_pressure = (((data[5] & 0x0f) * 256) + data[4]);
    alt_forecast = data[5] >> 4;

    if (pressure == maxpressure)
    {
	syslog_msg (wmr->syslogEn, WMR_SENSOR_C_TXT_1 );
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

	if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
	{
	    weather->pressure.pressure		=	pressure;
	    weather->pressure.forecast		=	forecast;
	    weather->pressure.alt_pressure	=	alt_pressure;
	    weather->pressure.alt_forecast	=	alt_forecast;

	    memcpy(&weather->pressure.tm, wmr->curtime, STR_TIME_SIZE);
	}

	if( wmr->alarmEn == 1)
	{          
	    alarm_sig (wmr->alarm_path, 1, 0, pressure, 0, wmr->alarm_pressure[0], wmr->alarm_pressure[1],wmr->alarmEn, wmr->syslogEn, wmr->debugEn);
	}

	if(wmr->fileEn == 1)
	{
	sprintf ( msg, WMR_TMPL_TXT[1], pressure, forecast, alt_pressure, alt_forecast);
	wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
	}         

        if(wmr->sqlEn == 1)
	{
	    if (( wmr->sqlt[1].tables == 0 ) && ( wmr->sqlt[1].sensor[0] == 0 ))
	    {
		wmr_sqldb_create( &wmr->db, 1, wmr->syslogEn, wmr->debugEn);
		wmr->sqlt[1].tables = 1;
		wmr->sqlt[1].sensor[0] = 1;
	    }

	sprintf ( msg, WMR_TMPL_SQL[1], pressure, forecast, alt_pressure, alt_forecast);
	wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 1, wmr->syslogEn, wmr->debugEn );
	}

	if(wmr->rrdEn == 1)
	{
	    if(wmr->rrdEmb == 1)
	    {
		rrdupd[0] = pressure;
		rrdupd[1] = alt_pressure;
		rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 1, 0, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	    } else {
		sprintf ( msg, WMR_RRD_UPDATE[1], pressure, alt_pressure);
		rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 1, 0, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	    }
	}
    }

}

void wmr_handle_wind(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int wind_dir, power, low_speed, high_speed, battery;
    float wind_speed, avg_speed, wind_chill;
    char msg[200];
    double rrdupd[4];

    battery = (data[0] & 0x40) >> 2;
    wind_dir = data[2] & 0xf;
    power = data[2] >> 4;
    wind_speed = data[4] / 10.0;
    

    low_speed = data[5] >> 4;
    high_speed = data[6] << 4;
    avg_speed = (high_speed + low_speed) / 10.0;
    wind_chill = 0.0;


    if (( low_speed >= 0 ) && ( high_speed >= 0 ))
    {
	wind_chill = (((data[6] << 8) | data[5]) - 320) * (5.0 / 90.0);
	// wind_chill *= -1.0;
	// wind_chill = data[7] << 8;
    } else {
        wind_chill = 0.0;
    }

    if ((avg_speed < 0) || (avg_speed > 250) || (high_speed < 0) || (high_speed > 250) || (low_speed < 0) || (low_speed > 250))
    {
	if( wmr->debugEn > 0 )
	{
        // packet is bogus:
            syslog_msg (wmr->syslogEn, WMR_SENSOR_C_TXT_2);
	}

    return;
    }


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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->wind.battery		=	battery;
	weather->wind.power		=	power;
	weather->wind.wind_dir		=	wind_dir;
	weather->wind.wind_speed	=	wind_speed;
	weather->wind.avg_speed		=	avg_speed;
	weather->wind.low_speed		=	low_speed;
	weather->wind.high_speed	=	high_speed;
	weather->wind.wind_chill	=	wind_chill;

	memcpy(&weather->wind.tm, wmr->curtime, STR_TIME_SIZE );
    }

    if( wmr->alarmEn == 1)
    {          
        alarm_sig (wmr->alarm_path, 2, 0, (int)wind_speed, battery, wmr->alarm_wind[0], wmr->alarm_wind[1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->fileEn == 1)
    {
    char *wind_str;
    wind_str = WINDIES[wind_dir];

    sprintf ( msg, WMR_TMPL_TXT[2], battery, power, wind_str, wind_speed, avg_speed, low_speed, high_speed, wind_chill);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[2].tables == 0 ) && ( wmr->sqlt[2].sensor[0] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 2, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[2].tables = 1;
	    wmr->sqlt[2].sensor[0] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[2], battery, power, wind_dir, wind_speed, avg_speed, low_speed, high_speed, wind_chill);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 2, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = wind_speed;
	    rrdupd[1] = avg_speed;
	    rrdupd[2] = wind_dir;
	    rrdupd[3] = wind_chill;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 2, 0, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[2], wind_speed, avg_speed, wind_dir, wind_chill);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 2, 0, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}

void wmr_handle_rain(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int sensor, power, rate, battery;
    float hour, day, total;
    int smi, sho, sda, smo, syr;
    char msg[200];
    double rrdupd[4];
    
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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->rain.battery	=	battery;
	weather->rain.power	=	power;
	weather->rain.rate	=	rate;
	weather->rain.hour	=	hour;
	weather->rain.day	=	day;
	weather->rain.total	=	total;

	memcpy(&weather->rain.tm, wmr->curtime, STR_TIME_SIZE );
	sprintf ( msg, WMR_TMPL_MAIN, syr, smo, sda, sho, smi);
        memcpy(&weather->rain.stm, msg, 16);
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr->alarm_path, 3, 0, rate, battery, wmr->alarm_rain[0], wmr->alarm_rain[1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[3], battery, sensor, power, rate, hour, day, total, syr, smo, sda, sho, smi);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[3].tables == 0 ) && ( wmr->sqlt[3].sensor[sensor] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 3, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[3].tables = 1;
	    wmr->sqlt[3].sensor[sensor] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[3], battery, sensor, power, rate, hour, day, total, syr, smo, sda, sho, smi);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 3, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = rate;
	    rrdupd[1] = hour;
	    rrdupd[2] = day;
	    rrdupd[3] = total;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 3, sensor, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[3], rate, hour, day, total);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 3, sensor, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}

void wmr_handle_water(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int sensor,battery;
    float temp;
    char msg[200];
    double rrdupd[1];

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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->water[sensor].battery	=	battery;
	weather->water[sensor].sensor	=	sensor;
	weather->water[sensor].temp	=	temp;

	memcpy(&weather->water[sensor].tm, wmr->curtime, STR_TIME_SIZE );
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr->alarm_path, 4, sensor, (int)temp, battery, wmr->alarm_water[sensor][0], wmr->alarm_water[sensor][1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[4], battery, sensor, temp);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[4].tables == 0 ) && ( wmr->sqlt[4].sensor[sensor] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 4, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[4].tables = 1;
	    wmr->sqlt[4].sensor[sensor] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[4], battery, sensor, temp);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 4, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = temp;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 4, sensor, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[4], temp);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 4, sensor, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}

void wmr_handle_uv(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int uvindex, battery;
    char msg[200];
    double rrdupd[1];

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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->uv.battery		=	battery;
	weather->uv.uvindex		=	uvindex;

	memcpy(&weather->uv.tm, wmr->curtime, STR_TIME_SIZE );
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig (wmr->alarm_path, 5, 0, uvindex, battery, wmr->alarm_uv[0], wmr->alarm_uv[1], wmr->alarmEn, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[5], battery, uvindex);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if(wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[5].tables == 0 ) && ( wmr->sqlt[5].sensor[0] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 5, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[5].tables = 1;
	    wmr->sqlt[5].sensor[0] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[5], battery, uvindex);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 5, wmr->syslogEn, wmr->debugEn );
    }

    if(wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = uvindex;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 5, 0, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[5], uvindex);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 5, 0, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}


void wmr_handle_mainu(WMR *wmr, WEATHER *weather, unsigned char *data, int len)
{
    int power, powered, battery, rf, level, mi, hr, dy, mo, yr;
    char msg[200];
    double rrdupd[3];

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

    if(( wmr->snmpEn == 1) || ( wmr->updEn == 1))
    {
	weather->main.battery	=	battery;
	weather->main.power	=	power;
	weather->main.powered	=	powered;
	weather->main.rf	=	rf;
	weather->main.level	=	level;

	sprintf ( msg, WMR_TMPL_MAIN, yr, mo, dy, hr, mi);
	memcpy(&weather->main.stm, msg, STR_TIME_SIZE );
	memcpy(&weather->main.tm, wmr->curtime, STR_TIME_SIZE );
    }

    if( wmr->alarmEn == 1)
    {          
	alarm_sig ( wmr->alarm_path, 6, 0, 0, battery, 0, 0, wmr->alarmEn, wmr->syslogEn, wmr->debugEn );
    }

    if( wmr->fileEn == 1)
    {
    sprintf ( msg, WMR_TMPL_TXT[6], battery, powered, yr, mo, dy, hr, mi, rf, level);
    wmr_file_data( &wmr->data_fh, msg, wmr->curtime, wmr->syslogEn, wmr->debugEn);
    }

    if( wmr->sqlEn == 1)
    {
	if (( wmr->sqlt[6].tables == 0 ) && ( wmr->sqlt[6].sensor[0] == 0 ))
	{
	    wmr_sqldb_create( &wmr->db, 6, wmr->syslogEn, wmr->debugEn);
	    wmr->sqlt[6].tables = 1;
	    wmr->sqlt[6].sensor[0] = 1;
	}

    sprintf ( msg, WMR_TMPL_SQL[6], battery, powered, yr, mo, dy, hr, mi, rf, level);
    wmr_sqldb_log( &wmr->db, wmr->curtime, msg, 6, wmr->syslogEn, wmr->debugEn );
    }

    if( wmr->rrdEn == 1)
    {
	if(wmr->rrdEmb == 1)
	{
	    rrdupd[0] = battery;
	    rrdupd[1] = powered;
	    rrdupd[2] = level;
	    rrd_update_int ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 6, 0, rrdupd, ( sizeof(rrdupd) / sizeof(double) ), &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	} else {
	    sprintf ( msg, WMR_RRD_UPDATE[6], battery, powered, level);
	    rrdtool_exec ( wmr->rrdtool_exec_path, wmr->rrdtool_save_path, 6, 0, msg, &wmr->rrdEn, wmr->syslogEn, wmr->debugEn );
	}
    }

}
