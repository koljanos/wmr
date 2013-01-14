#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
//#include "wmr_struct.h"

void syslog_msg ( int syslogEn, char *msg_string) 
{
	switch(syslogEn)
	{
		case 0:
			printf( msg_string );
			break;
		case 1:
			openlog ("wmr-oregon", LOG_PID | LOG_CONS, LOG_DAEMON);
			syslog (LOG_NOTICE, msg_string);
			closelog();
			break;
	}
}
