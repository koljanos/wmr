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

#ifndef _WMR_LOGGER_EXT_H
#define _WMR_LOGGER_EXT_H

#define WMR_EXIT_FAILURE	-1
#define WMR_EXIT_NORMAL		1
#define WMR_EXIT_SUCCESS	0
#define WMR_EXIT_KILL		9

#include "wmr_weather.h"

/*
 Gentoo header hack
*/

#if defined(GENTOO_HACK)
extern int errno;
#endif

#include <errno.h>

#if defined(GENTOO_HACK)
extern int error_intr;
#endif

char err_string[1024];

#if defined(GENERAL_MAIN)
// wmr.c
#define WMR_HEADER_INFO "- Weather Logger for (c) Oregon Scientific USB protocol\n- Version: %s %s\n- For help, type -h.\n\n"

#define RR_WMR_DATA             0
#define RR_WMR_REINIT           1
#define RR_WMR_LROTATE          2
#define RR_WMR_EXIT             3
#define RR_WMR_ARGV             4
#define RR_WMR_INIT_USB         5
#define RR_WMR_RCONF            6
#define RR_WMR_INIT_DATA        7
#define RR_WMR_DAEMON           8
#define RR_WMR_KILL             9
#define RR_WMR_PREEXIT          10

#define WMR_VENDOR_ID  0x0fde
#define WMR_PRODUCT_ID 0xca01

int const RECV_PACKET_LEN	= 8;
unsigned char const PATHLEN	= 2;
int const PATH_IN[]		= { 0xff000001, 0xff000001 };
int const PATH_OUT[]		= { 0xff000001, 0xff000002 };
unsigned char const INIT_PACKET1[] = { 0x20, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00 };
unsigned char const INIT_PACKET2[] = { 0x01, 0xd0, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00 };

    // CONFIG FILE & COMMAND LINE
    extern int read_cnfile ( WMR *, WEATHER * );
    extern int read_arguments( WMR *, WEATHER *, int, char **, char * );
    extern void view_cnfsnmp( WEATHER * );
    // FILE LOG
    extern int  wmr_file_open (FILE **, char *  );
    // SQL LOG
    extern int  wmr_sqldb_init(sqlite3 **, char *, int, int );
    // UPDATE EXEC
    extern int upd_exec_handle ( key_t, char *, char *, int, int );
    extern void upd_scan_dir   ( WEATHER *, char *, int, int );
    // UTILs
    extern WMR *wmr_new( void );
    extern int wmr_close( WMR * );
//    extern void wmr_print_state( unsigned int, int );
    extern void wmr_print_state( HIDInterface *, int );
    extern void get_curtime( char ** );
    extern int logrotate ( sqlite3 **, FILE **, char *, int, char *, int, char *, int, char *, int, int );
    extern int kill_prog(char *, int, int );
    // SENSOR
    extern void wmr_handle_temp		(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_pressure	(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_wind		(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_rain		(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_uv		(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_water	(WMR *, WEATHER *, unsigned char *, int);
    extern void wmr_handle_mainu	(WMR *, WEATHER *, unsigned char *, int);

#else
    // none
    extern pthread_mutex_t job_mutex;
#endif
    extern int errno;
    // SYSLOG INFO DEBUG
    extern void syslog_msg( int, char *);

/*
    National language defenition
*/
#if defined(LANG_RU)
    #include "lang/lang_ru.h"
#elif defined(LANG_RU_CP1251)
    #include "lang/lang_ru_1251.h"
#elif defined(LANG_RU_CP866)
    #include "lang/lang_ru_866.h"
#elif defined(LANG_RU_KOI8)
    #include "lang/lang_ru_KOI8.h"
#elif defined(LANG_RU_UTF8)
    #include "lang/lang_ru_UTF8.h"
#elif defined(LANG_ENG)
    #include "lang/lang_en.h"
#else
    #include "lang/lang_en.h"
#endif

//#include "lang/lang_en.h"

#if defined(GENERAL_TABLES)
    static char *const TABLES[] 	= { "TEMP", "PRESSURE", "WIND", "RAIN", "WATER", "UV", "MAIN", "HUMIDITY" };
#endif

#if defined(GENERAL_SQL)
    #include <sqlite3.h>
    #define WMR_TMPL_SQL_INSERT     "INSERT INTO %s VALUES( \'%s\',%s )"

static char *const WMR_SQL_CREATE[] = { \
"CREATE TABLE IF NOT EXISTS TEMP ( tdate datetime PRIMARY KEY UNIQUE, battery int(2), sensor int, smile int, trend char(2), temp float(5), humidity int(3), dewpoint float(5) )", \
"CREATE TABLE IF NOT EXISTS PRESSURE ( tdate datetime PRIMARY KEY UNIQUE, pressure float(8), forecast int, altpressure float(8), altforecast int )", \
"CREATE TABLE IF NOT EXISTS WIND ( tdate datetime PRIMARY KEY UNIQUE, battery int, power int, dir char(5), speed float(5), avgspeed float(5), low_speed float(5), high_speed float(5), wind_chill float(5) )", \
"CREATE TABLE IF NOT EXISTS RAIN ( tdate datetime PRIMARY KEY UNIQUE, battery int, sensor int, power int, rate int, hour_total float(8), day_total float(8), all_total float(8), since datetime )", \
"CREATE TABLE IF NOT EXISTS WATER ( tdate datetime PRIMARY KEY UNIQUE, battery int, sensor int, temp float(8) )", \
"CREATE TABLE IF NOT EXISTS UV ( tdate datetime PRIMARY KEY UNIQUE, battery int, uvindex int )", \
"CREATE TABLE IF NOT EXISTS MAIN ( tdate datetime PRIMARY KEY UNIQUE, battery int(2), powered int(2), ddate datetime, rf int(2), level int(2) )" \
};

#endif

#if defined(GENERAL_SENSOR)

    // ALARM EXEC
    extern int alarm_sig(char *, int, int, int, int, int, int, int, int, int);
    // FILE LOG
    extern void wmr_file_data (FILE **, char *, char *, int, int);
    // SQL LOG
    extern void wmr_sqldb_log(sqlite3 **, char *, char *, int, int, int);
    extern void wmr_sqldb_create(sqlite3 **, int, int, int);
    // RRD LOG
    extern void rrdtool_exec   ( char *, char *, int, int, char *, int *, int, int );
    extern void rrd_update_int ( char *, char *, int, int, double *, int, int *, int, int );

static char *const WMR_TMPL_SQL[] = { \
"\'%d\',\'%d\',\'%d\',\'%s\',\'%.1f\',\'%d\',\'%.1f\'", \
"\'%d\',\'%d\',\'%d\',\'%d\'", \
"\'%d\',\'%d\',\'%d\',\'%.1f\',\'%.1f\',\'%d\',\'%d\',\'%.1f\'", \
"\'%d\',\'%d\',\'%d\',\'%d\',\'%.2f\',\'%.2f\',\'%.2f\',\'%04d%02d%02d%02d%02d\'", \
"\'%d\',\'%d\',\'%.1f\'","\'%d\',\'%d\'","\'%d\',\'%d\',\'%04d%02d%02d%02d%02d\',\'%d\',\'%d\'" \
};

static char *const WMR_TMPL_TXT[] = { \
"type=TEMP,battery=%d,sensor=%d,smile=%d,trend=%s,temp=%.1f,humidity=%d,dewpoint=%.1f", \
"type=PRESSURE,pressure=%d,forecast=%d,altpressure=%d,altforecast=%d", \
"type=WIND,battery=%d,power=%d,dir=%d,speed=%.1f,avgspeed=%.1f,low_speed=%d,high_speed=%d,wind_chill=%.1f", \
"type=RAIN,battery=%d,sensor=%d,power=%d,rate=%d,hour_total=%.2f,day_total=%.2f,all_total=%.2f,since=%04d%02d%02d%02d%02d", \
"type=WATER,battery=%d,sensor=%d,temp=%.1f","type=UV,battery=%d,uvindex=%d", \
"type=CLOCK,battery=%d,powered=%d,at=%04d%02d%02d%02d%02d,rf=%d,level=%d" \
};

static char *const WMR_RRD_UPDATE[] = { \
"Temp:DewPoint:Humidity N:%.1f:%.1f:%d", \
"Pressure:PressureAlt N:%d:%d",\
"WindSpeed:WindAwg:WindDir:WindChill N:%.1f:%.1f:%d:%.1f", \
"RainRate:RainHour:RainDay:RainAll N:%d:%.2f:%.2f:%.2f", \
"Water N:%.1f", \
"UV N:%d", \
"MainBattery:ExtPower:Level N:%d:%d:%d" \
};

static char *const WMR_TMPL_MAIN = "%04d%02d%02d%02d%02d";

static char *const WINDIES[] 	= { "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NWN" };
static char *const FORECAST[] 	= { "PartlyCloudy", "Rainy", "Cloudy", "Sunny", "Snowy" };
static char *const SMILIES[] 	= { "  ", ":D", ":(", ":|" };
static char *const TRENDS[] 	= { "-", "U", "D" };

#endif

#if defined(GENERAL_UTIL)
    #include <sqlite3.h>
    #define WMR_TMPL_LOGROTATE      "%s %d %s %d %s %d %s"
    #define WMR_CONFG_FILE "/etc/wmr/wmr.conf"
#endif

#if defined(GENERAL_UPD)
    //
#endif

#if defined(GENERAL_RRD)
#define WMR_RRD_OUT_FILE		"%s/%s_%d.rrd"
#define WMR_RRD_UPDATE_FILE		"%s update %s/%s_%d.rrd --template %s"

static char *const WMR_RRD_CREATE_PAR[] = { \
"%s create %s/%s_%d.rrd --step 150 DS:Temp:GAUGE:240:-100:100 DS:DewPoint:GAUGE:240:-100:100 DS:Humidity:GAUGE:240:0:100 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:Pressure:GAUGE:240:700:800 DS:PressureAlt:GAUGE:240:700:800 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:WindSpeed:GAUGE:240:0:200 DS:WindAwg:GAUGE:240:0:200 DS:WindDir:GAUGE:240:0:200 DS:WindChill:GAUGE:240:-100:100 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:RainRate:GAUGE:240:0:100 DS:RainHour:GAUGE:240:0:100 DS:RainDay:GAUGE:240:0:100 DS:RainAll:GAUGE:240:0:100 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:Water:GAUGE:240:-100:100 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:UV:GAUGE:240:0:15 %s", \
"%s create %s/%s_%d.rrd --step 150 DS:MainBattery:GAUGE:240:0:1 DS:ExtPower:GAUGE:240:0:1 DS:Level:GAUGE:240:0:100 %s" \
};

#define WMR_RRD_CREATE_BASE "RRA:AVERAGE:0.5:1:4320 RRA:AVERAGE:0.5:15:2880 RRA:AVERAGE:0.5:120:2160 RRA:AVERAGE:0.5:720:1440 RRA:MIN:0.5:1:4320 RRA:MIN:0.5:15:2880 RRA:MIN:0.5:120:2160 RRA:MIN:0.5:720:1440 RRA:MAX:0.5:1:4320 RRA:MAX:0.5:15:2880 RRA:MAX:0.5:120:2160 RRA:MAX:0.5:720:1440 RRA:LAST:0.5:1:4320 RRA:LAST:0.5:15:2880 RRA:LAST:0.5:120:2160 RRA:LAST:0.5:720:1440"
#define WMR_RRD_GRAPH_WATERMARK "WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

extern int rrdtool_check(char *);

/*
// "TEMP", "PRESSURE", "WIND", "RAIN", "WATER", "UV", "MAIN", "HUMIDITY" };
#define WMR_RRD_GRAPH_TSENS[] = { \
"Humidity"

// %s %s %s %d %d %s %s %s
static char *const WMR_RRD_GRAPH_PAR[] = { \
"%s graph %s/%s.gif --width %d --height %d --start -%s --end now --rigid --slope-mode --watermark \"%s\" --vertical-label \"%s\"", \
"DEF:param%d=%s/%s_%d.rrd:%s:AVERAGE " \
"CDEF:param%d_by_16=param%d,16,/ " \
"AREA:param%d_by_16#%s%d%s " \
""
};
*/

#endif

#if defined(GENERAL_ALARM)
    #define WMR_TMPL_ALARM          "%s %s %d %d %s"
    static char *const SENS_ALARM[] = { "MIN", "MAX", "NORMAL", "BATTERY" };
#endif

#if defined(GENERAL_MAIN) || defined(GENERAL_UPD)
    // Init all structure
    extern WEATHER *weather_new( int , key_t, char *, int );
    extern int weather_close(WEATHER *, key_t, pid_t, int, int, int );
    // UTILs : LOCK FILE PIDs ADD ...
    extern int lock_state( char *, int, int, int, int, int );
#endif

#if defined(GENERAL_MAIN) || defined(GENERAL_UTIL)
    #define CNF_PATH_SIZE 255
    #define BUF_SIZE 255
    // SQL LOG
    extern void wmr_sqldb_close(sqlite3 **);
    // FILE LOG
    extern void wmr_file_close(FILE ** );
#endif

#endif
