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

// todo: move this here
#define GENERAL_TABLES 1
#define GENERAL_ALARM 1
#include "wmr.h"


int alarm_sig (char *alarm_path, int cevent, int csensor, int cstatus, int battery, int min, int max, int alarmEn, int syslogEn, int debugEn)
{
    int alarm_status=0;
    char msg[1024];

    if(min != 0 )
    {
	if(min > cstatus)
	{
	    sprintf ( msg, WMR_TMPL_ALARM, alarm_path, TABLES[cevent], csensor, cstatus, SENS_ALARM[0] ); 
	    alarm_status=1;
	}
    }

    if(max != 0 )
    {
	if(max < cstatus)
	{
	    sprintf ( msg, WMR_TMPL_ALARM, alarm_path, TABLES[cevent], csensor, cstatus, SENS_ALARM[1] ); 
	    alarm_status=1;
	}
    }

    if(battery != 0 )
    {
	sprintf ( msg, WMR_TMPL_ALARM, alarm_path, SENS_ALARM[3], csensor, cstatus, TABLES[cevent] ); 
	alarm_status=1;
    }

    if (alarm_status == 0)
    {
	return WMR_EXIT_SUCCESS;
    }

    if(system (msg) != 0)
    {
        sprintf ( err_string, WMR_ALARM_C_TXT_1, msg);
	syslog_msg (syslogEn, err_string);
	alarmEn = 0;
	return WMR_EXIT_NORMAL; 
    } else {

	if( debugEn > 0)         
        {
		sprintf ( err_string, WMR_ALARM_C_TXT_2, msg);
		syslog_msg (syslogEn, err_string);
        }
    }


return WMR_EXIT_SUCCESS;
}
