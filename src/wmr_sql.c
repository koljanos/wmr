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
#include <string.h>
#include <unistd.h>
#define GENERAL_TABLES 1
#define GENERAL_SQL 1
#include "wmr_ext.h"

void wmr_sqldb_create(sqlite3 **db, int tbln, int syslogEn, int debugEn)
{

    if ( sqlite3_exec(*db, WMR_SQL_CREATE[tbln], 0,0,0) != SQLITE_OK )
    {
	if( debugEn > 0 )
	{
	    sprintf (err_string, WMR_SQL_C_TXT_1, TABLES[tbln], sqlite3_errmsg(*db));
	    syslog_msg (syslogEn, err_string);
	}
    }
}

void wmr_sqldb_log(sqlite3 **db, char * curtime, char *msgs, int tbln, int syslogEn, int debugEn )
{
    char msg[200];

    sprintf ( msg, WMR_TMPL_SQL_INSERT, TABLES[tbln], curtime, msgs );

    if( debugEn > 2 )
    {
	sprintf (err_string, "SQL[%s]:%s\n", curtime, msg);
	syslog_msg (syslogEn, err_string);
    }

    if ( sqlite3_exec(*db, msg, 0, 0, 0) != SQLITE_OK )
    {
	if( debugEn > 0 )
	{
	    sprintf (err_string, WMR_SQL_C_TXT_2, sqlite3_errmsg(*db));
	    syslog_msg (syslogEn, err_string);
	}
    }
}

int wmr_sqldb_init(sqlite3 **db, char * db_name, int syslogEn, int debugEn)
{

    if( sqlite3_open( db_name, *&db) )
    {
	if( debugEn > 0 )
	{
	    sprintf (err_string, WMR_SQL_C_TXT_3, sqlite3_errmsg(*db));
	    syslog_msg (syslogEn, err_string);
	    return WMR_EXIT_NORMAL;
	}
    }
	if( debugEn > 1 )
	{
    	    sprintf (err_string, WMR_SQL_C_TXT_4, db_name);
	    syslog_msg (syslogEn, err_string);
	}

return WMR_EXIT_SUCCESS;
}

void wmr_sqldb_close(sqlite3 **db)
{
	sqlite3_close(*db);
}

