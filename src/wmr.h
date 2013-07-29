/**
 * Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol. Tested on wmrs200.
 *
 * Copyrights:
 * 2009 Barnaby Gray <barnaby@pickle.me.uk>
 * 2012-2013 Den68 <idg68@yandex.ru> 
 * Contributors:
 * 2013 Ald <alexdu.com.ae@gmail.com>
 * Latest download URL: http://www.nkl.ru/support/wmr/
 * Global download URL: http://code.google.com/p/wmr/
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef _WMR_H
#define _WMR_H

// WMR-wide standard headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

// bits from autoconf
#include "config.h"

// libHID is out there?
#ifdef HAVE_HID_H
#	include <hid.h>
#else
#	ifdef HAVE_LIBHID_HID_H
#		include <libhid/hid.h>
#	endif
#endif

// SQLite is available?
#ifdef HAVE_LIBSQLITE3
#	include <sqlite3.h>
#endif



/* structure WMR */
typedef struct _WMR {
    int pos;
    int sqlEn;
    int fileEn;
    int rrdEn;
    int rrdEmb;
    int debugEn;
    int syslogEn;
    int alarmEn;
    int viewEn;
    int snmpEn;
    int updEn;
    int updTime;
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
#ifdef HAVE_LIBSQLITE3
    sqlite3 *db;;
    char * db_name;
    struct
    {
	int tables;
	int sensor[10];
    } sqlt[7];
#endif
    char * rrdtool_exec_path;
    char * rrdtool_save_path;
    char * logrotate_path;
    char * alarm_path;
    char * lock_file;
    char * upd_exec_path;
    char * curtime;
    long long exectime;


    struct
    {
	key_t shmid;
	int shmhn;
	pid_t MAINpid;
    } run;

} WMR;

// Extra header (may be should be merged here?)
#include "wmr_ext.h"

#endif
