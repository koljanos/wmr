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

#ifndef _WMR_LOGGER_STRUCT_WEATHER_H
#define _WMR_LOGGER_STRUCT_WEATHER_H

#define STR_TIME_SIZE 16

typedef struct _WEATHER
{

struct _run
{
    key_t shmid;
    int shmhn[3];
    int updTime;
    pid_t UPDpid;
    pid_t SNMPpid;
    pid_t MAINpid;
    int UPD[4];
    int SNMP[4];
} run;

struct _snmp
{
    int Port;
    //float Ip[5];
    char Community[10];

    char Location[100];
    char Longtitude[10];
    char Latitude[10];
    char ContactPhone[50];
    char ContactEmail[50];
    char ContactSkype[50];
    char ContactICQ[20];
    char ContactWWW[100];
} snmp;

struct _temp
{
    // 0
    char tm[STR_TIME_SIZE];
    int battery;
    int sensor;
    int humidity;
    int smiley;
    float temp;
    float dewpoint;
    char trendTxt[3];
    char smileyTxt[5];

} temp[10];

struct _pressure
{
    // 1
    char tm[STR_TIME_SIZE];
    int pressure; 
    int forecast;
    int alt_pressure; 
    int alt_forecast;

} pressure;

struct _wind
{
    // 2
    char tm[STR_TIME_SIZE];
    int battery;
    int power;
    int wind_dir;
    int low_speed; 
    int high_speed;
    float wind_speed;
    float avg_speed;
    float wind_chill;
} wind;

struct _rain
{
    // 3
    char tm[STR_TIME_SIZE];
    int battery;
    int power;
    int rate;
    float hour;
    float day;
    float total;
    char stm[STR_TIME_SIZE];
    // int syr, smo, sda, sho, smi;

} rain;

struct _water
{
    // 4
    char tm[STR_TIME_SIZE];
    int battery;
    int sensor;
    float temp;

} water[4];

struct _uv
{
    // 5
    char tm[STR_TIME_SIZE];
    int battery;
    int uvindex;

} uv;

struct _main
{
    // 6
    char tm[STR_TIME_SIZE];
    int power;
    int powered;
    int battery; 
    int rf;
    int level;
    char stm[STR_TIME_SIZE];
    // int syr, smo, sda, sho, smi;

} main;


} WEATHER;

#endif
