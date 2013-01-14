/*
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

#define WMR_CONFG_FILE "/etc/wmr/wmr.conf"
#define WMR_VENDOR_ID  0x0fde
#define WMR_PRODUCT_ID 0xca01

#define WMR_TMPL_SQL_INSERT	"INSERT INTO %s VALUES( \'%s\',%s )"
#define WMR_TMPL_LOGROTATE	"%s %d %s %d %s %d %s"
#define WMR_TMPL_ALARM		"%s %s %d %d %s"

#define RR_WMR_DATA		0
#define RR_WMR_REINIT		1
#define RR_WMR_LROTATE		2
#define RR_WMR_EXIT		3
#define RR_WMR_ARGV		4
#define RR_WMR_INIT_USB		5
#define RR_WMR_RCONF		6
#define RR_WMR_INIT_DATA	7
#define RR_WMR_DAEMON		8
#define RR_WMR_KILL		9
#define RR_WMR_PREEXIT		10

/* constants */
static char *const WMR_TMPL_SQL[] = { "\'%d\',\'%d\',\'%d\',\'%s\',\'%.1f\',\'%d\',\'%.1f\'","\'%d\',\'%d\',\'%d\',\'%d\'","\'%d\',\'%d\',\'%s\',\'%.1f\',\'%.1f\',\'%.1f\',\'%.1f\'","\'%d\',\'%d\',\'%d\',\'%d\',\'%.2f\',\'%.2f\',\'%.2f\',\'%04d%02d%02d%02d%02d\'","\'%d\',\'%d\',\'%.1f\'","\'%d\',\'%d\'","\'%d\',\'%d\',\'%04d%02d%02d%02d%02d\',\'%d\',\'%d\'" };
static char *const WMR_TMPL_TXT[] = { "type=TEMP,battery=%d,sensor=%d,smile=%d,trend=%s,temp=%.1f,humidity=%d,dewpoint=%.1f","type=PRESSURE,pressure=%d,forecast=%d,altpressure=%d,altforecast=%d","type=WIND,battery=%d,power=%d,dir=%s,speed=%.1f,avgspeed=%.1f,low_speed=%.1f,high_speed=%.1f","type=RAIN,battery=%d,sensor=%d,power=%d,rate=%d,hour_total=%.2f,day_total=%.2f,all_total=%.2f,since=%04d%02d%02d%02d%02d","type=WATER,battery=%d,sensor=%d,temp=%.1f","type=UV,battery=%d,uvindex=%d","type=CLOCK,battery=%d,powered=%d,at=%04d%02d%02d%02d%02d,rf=%d,level=%d" };

int const RECV_PACKET_LEN   = 8;
int const BUF_SIZE = 255;
int const CNF_PATH_SIZE = 255;
unsigned char const PATHLEN = 2;
int const PATH_IN[]  = { 0xff000001, 0xff000001 };
int const PATH_OUT[] = { 0xff000001, 0xff000002 };
unsigned char const INIT_PACKET1[] = { 0x20, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00 };
unsigned char const INIT_PACKET2[] = { 0x01, 0xd0, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00 };

static char *const SENS_TYPE[] 	= { "TEMP", "HUMIDITY", "PRESSURE", "WIND", "RAIN", "UV", "MAIN", "WATER" };
static char *const SENS_ALARM[] = { "MIN", "MAX", "NORMAL", "BATTERY" };
static char *const WINDIES[] 	= { "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NWN" };
static char *const FORECAST[] 	= { "PartlyCloudy", "Rainy", "Cloudy", "Sunny", "Snowy" };
static char *const SMILIES[] 	= { "  ", ":D", ":(", ":|" };
static char *const TRENDS[] 	= { "-", "U", "D" };

extern int read_cnfile ( WMR * );
extern int read_arguments( WMR *, int, char ** );
void rrdtool_exec ( WMR *, int, int, char * );
