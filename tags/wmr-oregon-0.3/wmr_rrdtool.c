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

#include <libhid/hid.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "wmr_struct.h"
#include "wmr_rrdtool.h"
//#include "rrdupdate/rrd_update.h"


void rrdtool_exec ( WMR *wmr, int table, int sensor, char *msg )
{
FILE *fd1, *fd2;
char buf[1024];


    if( wmr->debugEn == 1)
    {
	sprintf ( err_string, "RRDTOOL: for (%s) sensor:(%d)\n", TABLES[table], sensor);
	syslog_msg (wmr->syslogEn, err_string);
    }

    fd1 = fopen(wmr->rrdtool_exec_path, "r");

    if (!fd1) 
    {
	sprintf ( err_string, "rrdtool executable not found in path: (%s)\nno RRD graphical created & update", wmr->rrdtool_exec_path);
	syslog_msg (wmr->syslogEn, err_string);
	wmr->rrdEn = 0;
	return;
    } else {
	sprintf (buf, WMR_RRD_OUT_FILE, wmr->rrdtool_save_path, TABLES[table], sensor);
		
	fd2 = fopen(buf, "r");
		
	if (!fd2)
	{
	    if( wmr->debugEn == 1)
	    {
		sprintf ( err_string, "RRDTOOL: file %s not found, Create!\n", buf);
		syslog_msg (wmr->syslogEn, err_string);
	    }

	    sprintf (buf, WMR_RRD_CREATE[table], wmr->rrdtool_exec_path, wmr->rrdtool_save_path, TABLES[table], sensor);
	    if(system (buf) != 0)
	    {
		sprintf ( err_string, "RRDTOOL create: error execute command: (%s)\n", buf);
		syslog_msg (wmr->syslogEn, err_string);
	    }
	} else {
	    fclose (fd2);
	}

	sprintf (buf, WMR_RRD_UPDATE_FILE, wmr->rrdtool_exec_path, wmr->rrdtool_save_path, TABLES[table], sensor, msg);
	if(system (buf) != 0)
	{
	    sprintf ( err_string, "RRDTOOL update: error execute command: (%s)\n", buf);
	    syslog_msg (wmr->syslogEn, err_string);
	} else {
	    if( wmr->debugEn == 1)
	    {
		sprintf ( err_string, "RRDTOOL: exec: %s\n", buf);
		syslog_msg (wmr->syslogEn, err_string);
	    }
	}


	fclose (fd1);
	} //if (!fd1)

} 

