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

#ifndef _WMR_LOGGER_STRUCT_H
#define _WMR_LOGGER_STRUCT_H

#define WMR_EXIT_FAILURE	-1
#define WMR_EXIT_NORMAL		1
#define WMR_EXIT_SUCCESS	0
#define WMR_EXIT_KILL		9

#define WMR_HEADER_INFO "- Weather Logger for (c) Oregon Scientific USB protocol\n- Version: %s %s\n- For help, type -h.\n\n"

static char *const TABLES[] 	= { "TEMP", "PRESSURE", "WIND", "RAIN", "WATER", "UV", "CLOCK", "HUMIDITY" };
char err_string[1024];

/* structure */
typedef struct _WMR {
    int pos;
    int sqlEn;
    int fileEn;
    int rrdEn;
    int debugEn;
    int syslogEn;
    int alarmEn;
    int viewEn;
    int daemonEn;
    int daemonRun;
    int daemonKill;
    int sens_temp[10];
    int sens_humidity[10];
    int sens_water[5];
    int sens_pressure;
    int sens_wind;
    int sens_rain;
    int sens_uv;
    int alarm_temp[10][3];
    int alarm_humidity[10][3];
    int alarm_water[5][3];
    int alarm_pressure[3];
    int alarm_wind[3];
    int alarm_rain[3];
    int alarm_uv[3];
    int sv_temp;
    int sv_pressure;
    int sv_wind;
    int sv_rain;
    int sv_water;
    int sv_uv;
    int remain;
    unsigned char* buffer;
    HIDInterface *hid;
    char *conf_path;
    FILE *data_fh;
    char *data_filename;
    sqlite3 *db;;
    char * db_name;
    char * rrdtool_exec_path;
    char * rrdtool_save_path;
    char * logrotate_path;
    char * alarm_path;
    char * lock_file;
} WMR;

void syslog_msg( int, char *);

#endif
