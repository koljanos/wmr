/**
 * Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol. Tested on wmrs200.
 * Config & Command line control
 * Copyright:
 * 2012 Den68 <idg68@yandex.ru>
 * Latest download URL: http://www.nkl.ru/support/wmr/
 * Global download URL: http://code.google.com/p/wmr/
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <libhid/hid.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "wmr_struct.h"
#include "wmr_build.h"
#include "wmr_version.h"

void view_cnfile(WMR *wmr)
{

	printf ( "Config (%s) defenition:\n" \
		"- Daemon mode:\t\t%d\n" \
		"- SysLog Enable:\t%d\n" \
		"- SQL Enable:\t\t%d\n" \
		"- SQL Base path:\t%s\n" \
		"- File Log Enable:\t%d\n" \
		"- File Log path:\t%s\n" \
		"- RRD graphic Enable:\t%d\n" \
		"- RRD exec path:\t%s\n" \
		"- RRD save path:\t%s\n" \
		"- Rotate exec path:\t%s\n" \
		"- Alarm Enable:\t\t%d\n" \
		"- Alarm exec path:\t%s\n" \
		"- Debug Enable:\t\t%d\n\n" \
		"- Sensor correct:\n" \
		"\t\ttemp:\t\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\thumidity:\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\twater:\t%d %d %d %d\n" \
		"\t\tpressure:\t%d\n" \
		"\t\twind:\t\t%d\n" \
		"\t\train:\t\t%d\n" \
		"\t\tuv:\t\t%d\n" \
		"- Sensor alarm (min/max):\n" \
		"\t\ttemp min:\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\ttemp max:\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\thumidity min:\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\thumidity max:\t%d %d %d %d %d %d %d %d %d %d\n" \
		"\t\twater min:\t%d %d %d %d\n" \
		"\t\twater max:\t%d %d %d %d\n" \
		"\t\tpressure:\t%d/%d\n" \
		"\t\twind:\t\t%d/%d\n" \
		"\t\train:\t\t%d/%d\n" \
		"\t\tuv:\t\t%d/%d\n" \
		"- Sensor data standart:\n" \
		"\t\ttemp:\t\t%d\n" \
		"\t\tpressure:\t%d\n" \
		"\t\twind:\t\t%d\n" \
		"\t\train:\t\t%d\n" \
		"\t\twater:\t\t%d\n" \
		"\t\tuv:\t\t%d\n" \
		,wmr->conf_path, \
		wmr->daemonEn, \
		wmr->syslogEn, \
		wmr->sqlEn, \
		wmr->db_name, \
		wmr->fileEn, \
		wmr->data_filename, \
		wmr->rrdEn, \
		wmr->rrdtool_exec_path, \
		wmr->rrdtool_save_path, \
		wmr->logrotate_path, \
		wmr->alarmEn, \
		wmr->alarm_path, \
		wmr->debugEn,  \
		wmr->sens_temp[0],  \
		wmr->sens_temp[1],  \
		wmr->sens_temp[2],  \
		wmr->sens_temp[3],  \
		wmr->sens_temp[4],  \
		wmr->sens_temp[5],  \
		wmr->sens_temp[6],  \
		wmr->sens_temp[7],  \
		wmr->sens_temp[8],  \
		wmr->sens_temp[9],  \
		wmr->sens_humidity[0],  \
		wmr->sens_humidity[1],  \
		wmr->sens_humidity[2],  \
		wmr->sens_humidity[3],  \
		wmr->sens_humidity[4],  \
		wmr->sens_humidity[5],  \
		wmr->sens_humidity[6],  \
		wmr->sens_humidity[7],  \
		wmr->sens_humidity[8],  \
		wmr->sens_humidity[9],  \
		wmr->sens_water[0],  \
		wmr->sens_water[1],  \
		wmr->sens_water[2],  \
		wmr->sens_water[3],  \
		wmr->sens_pressure, \
		wmr->sens_wind, \
		wmr->sens_rain, \
		wmr->sens_uv, \
		wmr->alarm_temp[0][0],  \
		wmr->alarm_temp[1][0],  \
		wmr->alarm_temp[2][0],  \
		wmr->alarm_temp[3][0],  \
		wmr->alarm_temp[4][0],  \
		wmr->alarm_temp[5][0],  \
		wmr->alarm_temp[6][0],  \
		wmr->alarm_temp[7][0],  \
		wmr->alarm_temp[8][0],  \
		wmr->alarm_temp[9][0],  \
		wmr->alarm_temp[0][1],  \
		wmr->alarm_temp[1][1],  \
		wmr->alarm_temp[2][1],  \
		wmr->alarm_temp[3][1],  \
		wmr->alarm_temp[4][1],  \
		wmr->alarm_temp[5][1],  \
		wmr->alarm_temp[6][1],  \
		wmr->alarm_temp[7][1],  \
		wmr->alarm_temp[8][1],  \
		wmr->alarm_temp[9][1],  \
		wmr->alarm_humidity[0][0],  \
		wmr->alarm_humidity[1][0],  \
		wmr->alarm_humidity[2][0],  \
		wmr->alarm_humidity[3][0],  \
		wmr->alarm_humidity[4][0],  \
		wmr->alarm_humidity[5][0],  \
		wmr->alarm_humidity[6][0],  \
		wmr->alarm_humidity[7][0],  \
		wmr->alarm_humidity[8][0],  \
		wmr->alarm_humidity[9][0],  \
		wmr->alarm_humidity[0][1],  \
		wmr->alarm_humidity[1][1],  \
		wmr->alarm_humidity[2][1],  \
		wmr->alarm_humidity[3][1],  \
		wmr->alarm_humidity[4][1],  \
		wmr->alarm_humidity[5][1],  \
		wmr->alarm_humidity[6][1],  \
		wmr->alarm_humidity[7][1],  \
		wmr->alarm_humidity[8][1],  \
		wmr->alarm_humidity[9][1],  \
		wmr->alarm_water[0][0],  \
		wmr->alarm_water[1][0],  \
		wmr->alarm_water[2][0],  \
		wmr->alarm_water[3][0],  \
		wmr->alarm_water[0][1],  \
		wmr->alarm_water[1][1],  \
		wmr->alarm_water[2][1],  \
		wmr->alarm_water[3][1],  \
		wmr->alarm_pressure[0], \
		wmr->alarm_pressure[1], \
		wmr->alarm_wind[0], \
		wmr->alarm_wind[1], \
		wmr->alarm_rain[0], \
		wmr->alarm_rain[1], \
		wmr->alarm_uv[0], \
		wmr->alarm_uv[1], \
		wmr->sv_temp, \
		wmr->sv_pressure, \
		wmr->sv_wind, \
		wmr->sv_rain, \
		wmr->sv_water, \
		wmr->sv_uv \
		);

}

int read_cnfile(WMR *wmr)
{
  FILE	*fp;
  char	temp[180];
  char	*ptr;

  if( ( fp = fopen( wmr->conf_path, "r" ) ) == NULL )
  {
    sprintf ( err_string, "No conf file %s to read, NOT storing loging information!\n", wmr->conf_path );
    syslog_msg (wmr->syslogEn, err_string);

    wmr->sqlEn		= 0;
    wmr->fileEn		= 0;
    wmr->rrdEn		= 0;
    wmr->alarmEn	= 0;
    wmr->debugEn	= 1;

    strcpy(wmr->db_name, "./weather.db" );
    strcpy(wmr->data_filename, "./weather.log" );
    strcpy(wmr->rrdtool_exec_path, "/usr/bin/rrdtool" );
    strcpy(wmr->rrdtool_save_path, "./" );
    strcpy(wmr->logrotate_path, "/usr/bin/wmr_logrotate.sh" );
    return WMR_EXIT_NORMAL;
  }

  while( fgets( temp, 180, fp ) != 0 )
  {

    if( (temp[0] == '\n') || (temp[0] == '#') )
    {
	continue;
    }
      
    ptr = strtok( temp, " \t\n" );

    if( strncasecmp( "SQLENABLE", ptr, 9 ) == 0 )
    {
      ptr = strtok( NULL, " \t\n" );
      wmr->sqlEn = atoi(ptr);
      continue;
    } else if( strncasecmp( "SQLBASEPATH", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->db_name, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "FILENABLE", ptr, 9 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->fileEn = atoi(ptr);
      continue;
    } else if( strncasecmp( "FILEPATH", ptr, 8 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->data_filename, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "RRDENABLE", ptr, 9 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->rrdEn = atoi(ptr);
      continue;
    } else if( strncasecmp( "RRDEXECPATH", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->rrdtool_exec_path, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "RRDSAVEPATH", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->rrdtool_save_path, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "LOGROTATEBIN", ptr, 12 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->logrotate_path, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "ALARMENABLE", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarmEn = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARMBIN", ptr, 8 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      strncpy(wmr->alarm_path, ptr, strlen(ptr));
      continue;
    } else if( strncasecmp( "DEBUGENABLE", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->debugEn = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP0", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP1", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP2", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[2] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP3", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[3] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP4", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[4] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP5", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[5] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP6", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[6] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP7", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[7] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP8", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[8] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_TEMP9", ptr, 10 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_temp[9] = atoi(ptr);
      continue;

    } else if( strncasecmp( "SENS_HUMIDITY0", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY1", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY2", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[2] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY3", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[3] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY4", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[4] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY5", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[5] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY6", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[6] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY7", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[7] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY8", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[8] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_HUMIDITY9", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_humidity[9] = atoi(ptr);
      continue;

    } else if( strncasecmp( "SENS_WATER0", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_water[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_WATER1", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_water[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_WATER2", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_water[2] = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_WATER3", ptr, 11 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_water[3] = atoi(ptr);
      continue;

    } else if( strncasecmp( "SENS_PRESSURE", ptr,13  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_pressure = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_WIND", ptr, 9 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_wind = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_RAIN", ptr, 9 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_rain = atoi(ptr);
      continue;
    } else if( strncasecmp( "SENS_UV", ptr, 7 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sens_uv = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MIN_TEMP0", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[0][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP1", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[1][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP2", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[2][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP3", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[3][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP4", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[4][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP5", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[5][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP6", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[6][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP7", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[7][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP8", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[8][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_TEMP9", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[9][0] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MIN_HUMIDITY0", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[0][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY1", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[1][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY2", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[2][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY3", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[3][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY4", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[4][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY5", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[5][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY6", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[6][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY7", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[7][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY8", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[8][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_HUMIDITY9", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[9][0] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MIN_WATER0", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[0][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_WATER1", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[1][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_WATER2", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[2][0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_WATER3", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[3][0] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MAX_WATER0", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[0][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_WATER1", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[1][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_WATER2", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[2][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_WATER3", ptr, 16 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_water[3][1] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MIN_PRESSURE", ptr,18  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_pressure[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_WIND", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_wind[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_RAIN", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_rain[0] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MIN_UV", ptr, 12 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_uv[0] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MAX_TEMP0", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[0][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP1", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[1][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP2", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[2][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP3", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[3][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP4", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[4][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP5", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[5][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP6", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[6][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP7", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[7][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP8", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[8][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_TEMP9", ptr, 15 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_temp[9][1] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MAX_HUMIDITY0", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[0][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY1", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[1][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY2", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[2][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY3", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[3][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY4", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[4][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY5", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[5][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY6", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[6][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY7", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[7][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY8", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[8][1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_HUMIDITY9", ptr, 19 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_humidity[9][1] = atoi(ptr);
      continue;

    } else if( strncasecmp( "ALARM_MAX_PRESSURE", ptr,18  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_pressure[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_WIND", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_wind[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_RAIN", ptr, 14 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_rain[1] = atoi(ptr);
      continue;
    } else if( strncasecmp( "ALARM_MAX_UV", ptr, 12 ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->alarm_uv[1] = atoi(ptr);
      continue;

    } else if( strncasecmp( "SV_TEMP", ptr,7  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_temp = atoi(ptr);
      continue;
    } else if( strncasecmp( "SV_PRESSURE", ptr,11  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_pressure = atoi(ptr);
      continue;
    } else if( strncasecmp( "SV_WIND", ptr,7  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_wind = atoi(ptr);
      continue;
    } else if( strncasecmp( "SV_WATER", ptr,8  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_water = atoi(ptr);
      continue;
    } else if( strncasecmp( "SV_RAIN", ptr,7  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_rain = atoi(ptr);
      continue;
    } else if( strncasecmp( "SV_UV", ptr,7  ) == 0 ) {
      ptr = strtok( NULL, " \t\n");
      wmr->sv_uv = atoi(ptr);
      continue;

    } else {
      sprintf ( err_string, "Error reading %s file, line (%s)\n", wmr->conf_path, ptr );
      syslog_msg (wmr->syslogEn, err_string);

      fclose( fp );
      exit(WMR_EXIT_NORMAL);
    }
  }

  fclose( fp ); 

    if( ( wmr->debugEn == 1) && ( wmr->viewEn != 1) )
    {
	view_cnfile(wmr);
    }

  return WMR_EXIT_SUCCESS;
}

int read_arguments(WMR *wmr, int argc, char ** argv)
{
        int c, i=0;

        while ((c = getopt (argc, argv, "cdhsklv")) != -1)
        {
                switch (c)
                {
                        case 'c':       // Config file
				if (argv[i + 2])
				{
					strcpy(wmr->conf_path,  argv[i + 2] );
				} else {
					sprintf ( err_string, "Path to configuration file NOT defained!\nUsed default: /etc/wmr/wmr.conf \nUse:\n\t\t%s -c </path/to/config.file>\tPath to configuration file\n", argv[0] );
					syslog_msg (wmr->syslogEn, err_string);
				}
         			break;
                        case 'l':       // Lock file
				if (argv[i + 2])
				{
					sprintf ( err_string, "%s/%s.lock", argv[i + 2], argv[0] );
					strcpy(wmr->lock_file,  err_string );
				} else {
					sprintf ( err_string, "Path to lock file NOT defained!\nUsed default: /var/lock/%s.lock \nUse:\n\t\t%s -l </path/to/lock/file>\tPath to lock file\n", argv[0], argv[0] );
					syslog_msg (wmr->syslogEn, err_string);
				}
         			break;
                        case 's':       // Syslog log file
                                wmr->syslogEn = 1;
         			break;
                        case 'd':       // Daemon mode enable & syslog auto enable
                                wmr->daemonEn = 1;
         			break;
                        case 'v':       // View config file
				wmr->viewEn	= 1;
				wmr->syslogEn	= 0;
				if ( read_cnfile(wmr) == 0 )
				{
				    view_cnfile(wmr);
				}
				return WMR_EXIT_NORMAL;
         			break;
                        case 'k':       // Kill daemon
				wmr->viewEn	= 0;
				wmr->syslogEn	= 0;
				wmr->daemonKill	= 1;
				return WMR_EXIT_KILL;
         			break;
                        case 'h':       // Help
                                printf ( "\n");
                                printf ( "Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600/RMS300 USB Station Reader\n\n");
                                printf ( "(C) 2012 Den68 <idg68@yandex.ru>\n");
                                printf ( "Credits to Barnaby Gray <barnaby@pickle.me.uk> (initial 2009)\n");
                                printf ( "See http://www.nkl.ru/support/wmr/ for more information\n\n");
                                printf ( "Options:\n");
                                printf ( " -s Enable SysLog storing job logger info\n");
                                printf ( " -c </path/to/config.file>\tPath to configuration file\n");
                                printf ( " -v View config file statment info\n");
                                printf ( " -k Kill daemon, exit programm\n");
                                printf ( " -h\t\t\t\tThis help\n\n");
                                return WMR_EXIT_NORMAL;
				break;
                        default:
                                return WMR_EXIT_SUCCESS;
                }
	    i++;
        }

return WMR_EXIT_SUCCESS;
}
