#define WMR_C_TXT_1 "- Receive packet len %d: "
#define WMR_C_TXT_2 "- hid_set_output_report failed with return code %d\n"
#define WMR_C_TXT_4 "- hid_init failed with return code %d\n"
#define WMR_C_TXT_5 "- hid_new_HIDInterface() failed, out of memory?\n"
#define WMR_C_TXT_6 "- Open failed, sleeping 5 seconds before retrying..\n"
#define WMR_C_TXT_7 "- hid_force_open failed with return code %d\n"
#define WMR_C_TXT_8 "- hid_write_identification failed with return code %d\n"
#define WMR_C_TXT_9 "- hid_interrupt_read failed with return code %d\n"
#define WMR_C_TXT_10 "- Bad checksum: %d / calc: %d\n"
#define WMR_C_TXT_11 "- Unknown packet type: %02x, skipping\n"
#define WMR_C_TXT_12 "- Exec: updEn: %d run.UPD[0]: %d run.UPD[1]: %d Key: %d\n"
#define WMR_C_TXT_13 "- MAIN: Child exit ! pid: %d\n"
#define WMR_C_TXT_14 "- MAIN: Parent exit ! pid: %d\n"
#define WMR_C_TXT_15 "- ReInit WMR USB device...\n"
#define WMR_C_TXT_16 "- WMR reinitialization failed\n\n"
#define WMR_C_TXT_17 "- Exit if pid: %d main pid: %d\n"
#define WMR_C_TXT_18 "- Child wait. pid: %d (%d) status: %d\n"
#define WMR_C_TXT_19 "- One more child dead. pid: %d status: %d\n"
#define WMR_C_TXT_20 "- Caught signal, cleaning up\n\n"
#define WMR_C_TXT_21 "\n- %s EXIT Succesfull\n"
#define WMR_C_TXT_22 "- USB: Opening Oregon Scientific USB device...\n"
#define WMR_C_TXT_23 "- USB: Failed to init device, exiting.\n\n"
#define WMR_C_TXT_24 "- USB: Device found on: %s\n"
#define WMR_C_TXT_25 "- CONFIG: Cannot read config file (%s), exiting.\n"
#define WMR_C_TXT_26 "- CONFIG: Read config file (%s), done.\n"
#define WMR_C_TXT_27 "- SQL: Error - exit\n\n"
#define WMR_C_TXT_28 "- FILE: Error: Couldn't open data log - exit\n\n"
#define WMR_C_TXT_29 "- DAEMON: Error - Couldn't fork - exit\n\n"
#define WMR_C_TXT_30 "- DAEMON: mode started...\n\n"
#define WMR_C_TXT_31 "- DAEMON: Error - Couldn't set sid - exit\n\n"
#define WMR_C_TXT_32 "- DAEMON: Error - Couldn't chdir - exit\n\n"
#define WMR_C_TXT_33 "- Requesting DAEMON %s exit ...\n\n"
#define WMR_C_TXT_34 "- Closed SQL\n"
#define WMR_C_TXT_35 "- Closed Log data\n"
#define WMR_C_TXT_36 "- Closed WMR\n"
#define WMR_C_TXT_37 "- WMR: (wmr data) initialization failed\n\n"
#define WMR_C_TXT_38 "- WMR: (weather data) initialization failed\n\n"
#define WMR_C_TXT_39 "- MAIN command: \n\n"
#define WMR_C_TXT_40 "- PID remove OK\n"
#define WMR_ALARM_C_TXT_1 "ALARM: error execute command: (%s)\nDisable alarm engine, please, solved this problem and reload config\n"
#define WMR_ALARM_C_TXT_2 "ALARM: OK - exec (%s)\n"
#define WMR_SQL_C_TXT_1 "- SQL: not CREATE table: %s! %s\n"
#define WMR_SQL_C_TXT_2 "- SQL: not INSERT data!: %s\n"
#define WMR_SQL_C_TXT_3 "- SQL: error: Can't open database: %s\n"
#define WMR_SQL_C_TXT_4 "- SQL: open database %s done.\n"
#define WMR_RRDTOOL_C_TXT_1 "RRD UPDATE INTERNAL: file %s not found, disable update!\n"
#define WMR_RRDTOOL_C_TXT_2 "RRD UPDATE INTERNAL: - file: %s update error: %d! update num value: %d\n"
#define WMR_RRDTOOL_C_TXT_3 "RRD UPDATE INTERNAL: - num: %d cur: %d value: %f\n"
#define WMR_RRDTOOL_C_TXT_4 "RRD UPDATE INTERNAL: - file: %s update: %d\n"
#define WMR_RRDTOOL_C_TXT_5 "RRD UPDATE INTERNAL: error close rrd file, code: %d (%d)\n"
#define WMR_RRDTOOL_C_TXT_6 "RRDTOOL: for (%s) sensor:(%d)\n"
#define WMR_RRDTOOL_C_TXT_7 "RRDTOOL: rrdtool executable not found in path: (%s)\nno RRD graphical created & update"
#define WMR_RRDTOOL_C_TXT_8 "RRDTOOL: file %s not found, Create!\n"
#define WMR_RRDTOOL_C_TXT_9 "RRDTOOL: create: error execute command: (%s)\n"
#define WMR_RRDTOOL_C_TXT_10 "RRDTOOL: update: error execute command: (%s)\n"
#define WMR_RRDTOOL_C_TXT_11 "RRDTOOL: exec: %s\n"
#define WMR_SENSOR_C_TXT_1 "- WMR: Barometer overflow: max measurement value 1050 exceeded, reporting as 1051\n"
#define WMR_SENSOR_C_TXT_2 "- WMR: wind packet is bogus!\n"
#define WMR_UTIL_C_TXT_1 "- WMR: (weather identifer shared memory) initialization failed\n\n"
#define WMR_UTIL_C_TXT_2 "- WMR: (weather data shared memory) initialization failed\n- Primary process: %d shm key: %d shm id: %d\n\n"
#define WMR_UTIL_C_TXT_3 "- WMR: shmID = %d\nRestart please ...\n\n"
#define WMR_UTIL_C_TXT_4 "- WMR: (weather data shared memory) attached failed\n- Primary shm key %d\n\n"
#define WMR_UTIL_C_TXT_5 "- WMR: (weather data shared memory) bad initialization key\n\n"
#define WMR_UTIL_C_TXT_6 "- WMR: (weather data shared memory) initialization failed\n- Child process: %d shm key %d shm id: %d\n\n"
#define WMR_UTIL_C_TXT_7 "- WMR: (weather data shared memory) attached failed\n- Child shm key %d\n\n"
#define WMR_UTIL_C_TXT_8 "- WMR: [%d/%d] (shared memory) Attach: %d Creator: %d LastConnected: %d\n"
#define WMR_UTIL_C_TXT_9 "- WMR: weather_close, pid: %d MAINpid: %d selN: %d\n"
#define WMR_UTIL_C_TXT_10 "- WMR: [%d/%d] (shared memory) Attach: %d Creator: %d LastConnected: %d\n"
#define WMR_UTIL_C_TXT_11 "- WMR: (weather data shared memory) [%d] detached failed %d - key %d/%d\n"
#define WMR_UTIL_C_TXT_12 "- WMR: (weather data shared memory) [%d] detached OK - key %d/%d\n"
#define WMR_UTIL_C_TXT_13 "- WMR: (weather data shared memory) [%d] delete segment failed %d - shm key %d/%d\n"
#define WMR_UTIL_C_TXT_14 "- WMR: (weather data shared memory) [%d] delete segment OK - shm key %d/%d\n"
#define WMR_UTIL_C_TXT_15 "- WMR: hid_close failed with return code %d\n"
#define WMR_UTIL_C_TXT_16 "- WMR: hid_cleanup failed with return code %d\n"
#define WMR_UTIL_C_TXT_17 "LOGROTATE: error execute command: (%s)\n"
#define WMR_UTIL_C_TXT_18 "LOGROTATE: OK - exec (%s)\n"
#define WMR_UTIL_C_TXT_19 "\t- Another executable is running: (%s)\n\tExit this programm, run kill -TERM `pidof wmrd`\n\tExit ...\n\n"
#define WMR_UTIL_C_TXT_20 "- CREATE LOCK FILE OK: %s\n"
#define WMR_UTIL_C_TXT_21 "- CREATE LOCK FILE ERROR: %s\n- Exit...\n"
#define WMR_UTIL_C_TXT_22 "- ERROR: Can't remove LOCK FILE: %s\n"
#define WMR_UTIL_C_TXT_23 "- REMOVE LOCK FILE OK: %s\n"
#define WMR_UTIL_C_TXT_24 "- ADDED PID to LOCK FILE OK: %s\n"
#define WMR_UTIL_C_TXT_25 "- ADDED PID to LOCK FILE ERROR: %s\n- Exit...\n"
#define WMR_UTIL_C_TXT_26 "- ADDED child proccess PID %d to LOCK FILE OK: %s\n"
#define WMR_UTIL_C_TXT_27 "- ADDED child proccess PID %d to LOCK FILE ERROR: %s\n"
#define WMR_UTIL_C_TXT_28 "- ERROR: can`t read lockfile %s\n\n"
#define WMR_UTIL_C_TXT_29 "- ERROR: can`t STOP daemon PID %d\n\n"
#define WMR_UPDEXEC_C_TXT_1 "- UPD exec file: %s (%d) [%d]\n"
#define WMR_UPDEXEC_C_TXT_2 "- UPD exec error: execute file: (%s)\n"
#define WMR_UPDEXEC_C_TXT_3 "- UPD exec file: OK (%s/%s) [%d]\n"
#define WMR_UPDEXEC_C_TXT_4 "- UPD exec error: Couldn't open the directory %s\n"
#define WMR_UPDEXEC_C_TXT_5 "- Child caught signal, UPD module cleaning up (%d) pid: %d ppid: %d\n"
#define WMR_UPDEXEC_C_TXT_6 "- Child white pid: %d / %d / %d status: %d signal: %d\n"
#define WMR_UPDEXEC_C_TXT_7 "- UPD exec: Child process, pid: %d cpid: %d run: %d wait time: %d\n"
#define WMR_UPDEXEC_C_TXT_8 "- UPD exec: Exiting Child proccess (in child), pid: %d cpid: %d ppid: %d run: %d\n"
#define WMR_UPDEXEC_C_TXT_9 "- UPD exec: Exiting parent proccess, pid: %d cpid: %d ppid: %d run: %d\n"
#define WMR_UPDEXEC_C_TXT_10 "- WMR (weather data) initialization failed\n\n"
#define WMR_UPDEXEC_C_TXT_11 "- UPD exec command: \n\n"
#define WMR_UPDEXEC_C_TXT_12 "- UPD exec error: unable to fork, retry .....\n"
#define WMR_CONF_C_TXT_1 "\nConfig (%s) defenition:\n" \
            		"- Daemon mode:\t\t%d\n" \
            		"- SysLog Enable:\t%d\n" \
            		"- Lock file path:\t%s\n" \
            		"- SQL Enable:\t\t%d\n" \
            		"- SQL Base path:\t%s\n" \
            		"- File Log Enable:\t%d\n" \
            		"- File Log path:\t%s\n" \
            		"- RRD graphic Enable:\t%d\n" \
            		"- RRD exec path:\t%s\n" \
            		"- RRD save path:\t%s\n" \
            		"- UPD Enable:\t\t%d\n" \
            		"- UPD time:\t\t%d\n" \
            		"- UPD exec path:\t%s\n" \
            		"- Rotate exec path:\t%s\n" \
            		"- Alarm Enable:\t\t%d\n" \
            		"- Alarm exec path:\t%s\n" \
            		"- SNPM Enable:\t\t%d\n" \
            		"- Debug Enable:\t\t%d\n\n" \
            		"- Sensor correct:\n" \
        	        "\t\ttemp:\t\t%d %d %d %d %d %d %d %d %d %d\n" \
            		"\t\thumidity:\t%d %d %d %d %d %d %d %d %d %d\n" \
        	        "\t\twater:\t\t%d %d %d %d\n" \
    		        "\t\tpressure:\t%d\n" \
            		"\t\twind:\t\t%d\n" \
            		"\t\train:\t\t%d\n" \
            		"\t\tuv:\t\t%d\n" \
            		"- Sensor alarm (min/max):\n" \
    			"\t\ttemp min:\t%d %d %d %d %d %d %d %d %d %d\n" \
            		"\t\ttemp max:\t%d %d %d %d %d %d %d %d %d %d\n" \
            		"\t\thumidity min:\t%d %d %d %d %d %d %d %d %d %d\n" \
            		"\t\thumidity max:\t%d %d %d %d %d %d %d %d %d %d\n" \
            		"\t\twater min:\t%d %d %d %d\n" \
            		"\t\twater max:\t%d %d %d %d\n" \
            		"\t\tpressure:\t%d/%d\n" \
            		"\t\twind:\t\t%d/%d\n" \
            		"\t\train:\t\t%d/%d\n" \
            		"\t\tuv:\t\t%d/%d\n" \
    		        "- Sensor data standart:\n" \
            		"\t\ttemp:\t\t%d\n" \
    		        "\t\tpressure:\t%d\n" \
        	        "\t\twind:\t\t%d\n" \
            		"\t\train:\t\t%d\n" \
    		        "\t\twater:\t\t%d\n" \
        	        "\t\tuv:\t\t%d\n"
#define WMR_CONF_C_TXT_2 "\nConfig SNMP defenition:\n" \
            		"- Server port:\t\t%d\n" \
    			"- Cmmunity:\t\t%s\n" \
    	    	        "- Location:\t\t%s\n" \
	        	"- Longtitude:\t\t%s\n" \
            	        "- Latitude:\t\t%s\n" \
            		"- Contact E-mail:\t\t%s\n" \
        	        "- Contact Phone:\t%s\n" \
    	        	"- Contact Skype:\t%s\n" \
                	"- Contact ICQ:\t\t%s\n" \
	    	        "- Contact WWW:\t\t%s\n\n"
#define WMR_CONF_C_TXT_3 "No conf file %s to read, NOT storing loging information!\n"
#define WMR_CONF_C_TXT_4 "Error reading %s file, line (%s)\n"
#define WMR_CONF_C_TXT_5 "Path to the configuration file NOT defained!\nUsed default: /etc/wmr/wmr.conf \nUse:\n\t\t%s -c </path/to/config.file>\tPath to configuration file\n"
#define WMR_CONF_C_TXT_7 "Path to the lock file NOT defained!\nUsed default: /var/lock/%s.lock \nUse:\n\t\t%s -l </path/to/lock/file>\tPath to lock file\n"
#define WMR_CONF_C_TXT_8 "Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600/RMS300 USB Station Reader\n\n" \
			 "(C) 2012-2013 Den68 <idg68@yandex.ru>\n" \
			 "Credits to Barnaby Gray <barnaby@pickle.me.uk> (initial 2009)\n" \
			 "See http://www.nkl.ru/support/wmr/ for more information\n\n" \
			 "Options:\n" \
			 " -s Enable SysLog storing job logger info\n" \
			 " -c </path/to/config.file>\tPath to configuration file\n" \
			 " -l </path/to/lock/file/>\tPath to lock file\n" \
			 " -v View config file statment info\n" \
			 " -k Kill daemon, exit programm\n" \
			 " -h This help\n\n"

