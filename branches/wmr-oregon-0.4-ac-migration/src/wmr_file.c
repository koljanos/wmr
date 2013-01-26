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

#include <signal.h> // merge with wmr.h?
#include <time.h>   // --"-- ?
#include "wmr.h"

int wmr_file_open(FILE ** data_fh, char * data_filename ) 
{
    /* check for rolled log or not open */
    if (!access(data_filename, F_OK) == 0 || *data_fh == NULL) 
    {
	if (*data_fh != NULL) 
	{
	    fclose(*data_fh);
	}

        *data_fh = fopen(data_filename, "a+");

        if (*data_fh == NULL) 
	{
		*data_fh = stderr;
		return WMR_EXIT_FAILURE;
        }
    }

return WMR_EXIT_SUCCESS;
}

void wmr_file_close(FILE ** data_fh) 
{
    if (*data_fh && *data_fh != stdout) 
    {
	fclose(*data_fh);
	*&data_fh = NULL;
    }
}

void wmr_file_data(FILE ** data_fh, char *msg, char *curtime, int syslogEn, int debugEn)
{

    fprintf ( *data_fh, "DATA[%s]:%s\n", curtime, msg);
    fflush  ( *data_fh);

    if( debugEn > 2 )
    {
	sprintf (err_string, "FILE[%s]:%s\n", curtime, msg);
	syslog_msg (syslogEn, err_string);
    }

}

