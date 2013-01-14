/*
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
#include <syslog.h>
//#include "wmr_wmr.h"

void syslog_msg ( int syslogEn, char *msg_string) 
{
	switch(syslogEn)
	{
		case 0:
			printf( msg_string );
			break;
		case 1:
			openlog ("wmrd", LOG_PID | LOG_CONS, LOG_DAEMON);
			syslog (LOG_NOTICE, msg_string);
			closelog();
			break;
		case 2:
			fprintf(stderr, msg_string );
			fflush(stderr);
			break;
	}
}
