
```
#----------------------------------------------------------------------#
# WMR config file for
# Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol.
# Global download URL: http://code.google.com/p/wmr/
# Latest download URL: http://www.nkl.ru/support/wmr/
#----------------------------------------------------------------------#
```
```
#
# To run, comand line, use flags:
#	-c <value> 	= path and name to config file, sample /etc/wmr.conf .
#	-l <value>	= path directory to lock file /tmp/wmr, name of lock file
#			  generated automation, default: wmrd.lock 
#			  default: /var/lock
#			  for get pid of runing programm, use:
#			  cat /var/lock/wmrd.lock
#	-s		= print all info & debug info to local syslog server.
#	-d		= start is a daemon server mode (loging only syslog).
#			  flag -s automatic enable.
#	-k		= kill memory copy programm wmrd running in daemon mode.
#			  analog: kill -TERM `pidof wmrd`
#	-v 		= print all config token from this config file.
#			  this options require flag -c <path/to/config/name.ext>
#			  before.
#
```
```
#----------------------------------------------------------------------#
# Select where to print all info & debug info.
# Command line options -s, overwrite this value.
# 0 - current terminal screen
# 1 - to local syslog server
# 2 - stderr stream
#----------------------------------------------------------------------#
#
```
```
SYSLOG 0
```
```
#
#----------------------------------------------------------------------#
# Allows entry into the database sqlite3 information from a weather station
# Enable: 1 Disable: 0
#----------------------------------------------------------------------#
#
```
```
SQLENABLE 1
```
```
#
# The full path to the database sqlite3, including file name
# /path/to/file/base.db
#
```
```
SQLBASEPATH /var/weather/weather.db
```
```
#
#----------------------------------------------------------------------#
# Allows entry into the data log file, save in txt format 
# information from a weather station
# Enable: 1 Disable: 0
#----------------------------------------------------------------------#
#
```
```
FILENABLE 0
```
```
#
# The full path to the log file, including file name
# /path/to/file/file.log
#
```
```
FILEPATH /var/weather/weather.log
```
```
#
#----------------------------------------------------------------------#
# Recording weather statistics in a graphical format, use rrdtools
# Enable: 1 Disable: 0
#----------------------------------------------------------------------#
#
```
```
RRDENABLE 1
```
```
#
# The full path to executable binary app rrdtool, including file name
# /path/to/file/rrdtool
# If not install rrdtool you platform - use RRDUPDEMBD 1
#
```
```
RRDEXECPATH /usr/bin/rrdtool
```
```
#
# If not install rrdtool you platform - use value 1, use embended procedure 
# rrd database update, and no function automatic create database. 
# Please, manual create rrd data base. 
# This option use if not rrdtool install from you platform, or increase 
# speed insert data to rrd database. 
# Good idea always use this value is enable.
#
# Create rrd database is manualy from script/mr_create_db_rrd.sh,
# or use generated template contrib/weather/*.rrd, copy to /var/weather
#
# Enable: 1 Disable: 0
# 1 - use embended procedure rrd database update
# 0 - use rrdtool binary to rrd database update
#
```
```
RRDUPDEMBD 1
```
```
#
# The full path to save directory statistic in .rrd format
# /path/to/savepath
#
RRDSAVEPATH /var/weather
#
# Path to save graphical file generate from rrdtool,
# needed for web interface, path to web server shared directory
#
#----------------------------------------------------------------------#
# Web & wmr graph image create defenition of sensor 
# this use rrdtool graph create & php web interface
# value: /path/to/save/image
#
# use /usr/bin/wmr_create_graph_rrd.sh to create web graphical image.
# for every 10 minute create new image, insert cron job new line:
#   0/10 0 * * * * /usr/bin/wmr_create_graph_rrd.sh
#----------------------------------------------------------------------#
#
# Path to generate sensor name graphical image file
# Default: /etc/wmr/script_graph
#
```
```
GRAPHEXECPATH /etc/wmr/script_graph
```
```
#
# Path to save graphical image file
# value: /path/to/save/image
#
```
```
GRAPHIMGPATH /var/www
```
```
#
# Period for date generate graphical image file
# sample value: 
# XXh - XX hour 
# 1w - One week
# 1m - One month
# 1y - One year
#
```
```
GRAPHPERIOD "24h 72h 1w 1m 1y"
```
```
#
# Large size image: /web/path/xxx-l-xx.png
#
```
```
IMGWSIZEL 780
IMGHSIZEL 500
```
```
#
# Smale size image: /web/path/xxx-s-xx.png
#
```
```
IMGWSIZES 500
IMGHSIZES 150
```
```
#
#----------------------------------------------------------------------#
#
# Update weather data to www, ftp, or another...
# Run all script '*.sh' in directory "UPDEXECPATH" in regular time "UPDTIME"
# See /etc/wmr/script_update/README
# ! Do NOT put this directory any other files if extention is .sh !
#
#----------------------------------------------------------------------#
#
```
```
UPDENABLE 1
```
```
#
# Update sleep time, in minute
# default: 10
#
```
```
UPDTIME 10
```
```
#
# Path to exec update weather script '*.sh'
# default: /etc/wmr/script_update
#
```
```
UPDEXECPATH /etc/wmr/script_update
```
```
#
#----------------------------------------------------------------------#
#
# Logrotate weather data log format ASCII/SQL/RRD
#
# The full path to script rotating log/sql/rrd files
# To logrotate, type: wmr_logrotate.sh -logrotate
# or, insert cron job new line:
# for every day:
# 0 0 * * * * /usr/bin/wmr_logrotate.sh -logrotate
# for every month:
# 0 0 1 * * * /usr/bin/wmr_logrotate.sh -logrotate
# for every year:
# 0 0 1 1 * * /usr/bin/wmr_logrotate.sh -logrotate
#----------------------------------------------------------------------#
#
```
```
LOGROTATEBIN /usr/bin/wmr_logrotate.sh
```
```
#
#----------------------------------------------------------------------#
# Allows Alarm event check enable or disable 
# Enable: 1 Disable: 0
#----------------------------------------------------------------------#
#
```
```
ALARMENABLE 1
```
```
#
# The full path to script alarm sensor execute
# for detail - see script/wmr_alarm.sh
# Format string send to script: 
# /path/to/script//wmr_alarm.sh 'SENSOR TYPE' 'NUM OF SENSOR' 'CURENT STATUS'
# See script/controlling/C2000-CP1.php for controling 4 line from 'C2000-CP1'
# 'Bolid' trademark (http://www.bolid.ru/production/devices/devices_48.html)
#
```
```
ALARMBIN /usr/bin/wmr_alarm.sh
```
```
#
#----------------------------------------------------------------------#
# SNMP Server agent defenition
# snmp v.1 read-only released 
# Enable: 1 Disable: 0
#----------------------------------------------------------------------#
#
```
```
SNMPENABLE 1
```
```
#
# SNMP port ( default 161 )
#
```
```
SNMPPORT 161
```
```
#
# SNMP read-only community ( default public )
#
```
```
SNMPCOMMUNITY public
```
```
#
# Other SNMP contact info for connect user to you server
#
```
```
SNMPLOCATION 195220,Russia,Sainkt-Petersburg,ul.Lermontova
SNMPLATITUDE 60.00
SNMPLONGTITUDE 30.38
SNMPCONTACTEMAIL my@email.ru
SNMPCONTACTPHONE 78120000000
SNMPCONTACTSKYPE myweather
SNMPCONTACTICQ 12345678
SNMPCONTACTWWW www.myweather.com
```
```
#
#----------------------------------------------------------------------#
# DEBUG - More info print for running wmrd
# Disable:		0
# Enable critical:	1 
# Enable info:		2 
# Enable debug:		3 
# Enable full dump:	4 
#----------------------------------------------------------------------#
#
```
```
DEBUGENABLE 1
```
```
#
#----------------------------------------------------------------------#
# Store & View convertion data 
# allowed as english metric (pindosia) and standart 
#----------------------------------------------------------------------#
#
# Temperature sensor (THGN801,THGR810) store data in standart:
# 0 - C (default)
# 1 - F
#
```
```
SV_TEMP 0
```
```
#
# Pressure sensor (main unit) store data in standart:
# 0 - gPa (default)
# 1 - psi
# 2 - bar
# 3 - mBar
# 4 - mpa
# 5 - mmHg
# 6 - inHg
#
```
```
SV_PRESSURE 5
```
```
#
# Rain sensor gidrometr (PCR800,RGR126) store data in standart:
# 0 - mm (default)
# 1 - cm
#
```
```
SV_RAIN 0
```
```
#
# Wind sensor (WGR800) store data in standart:
# 0 - ms (default)
# 1 - mps
# 2 - mph
#
```
```
SV_WIND 0
```
```
#
# Water temperature sensor (THWR288) store data in standart:
# 0 - C (default)
# 1 - F
#
```
```
SV_WATER 0
```
```
#
# UV sensor (UVN800) store data in standart:
# 0 - (default)
#
```
```
SV_UV 0
```
```
#
#----------------------------------------------------------------------#
# Correction of sensor 
# allowed as positive, or negative, for example: 2 or -3
#----------------------------------------------------------------------#
#
# Main station indoor temperature/humidity sensor
#
```
```
SENS_TEMP0 0
SENS_HUMIDITY0 0
```
```
#
# Complected Outdoor temperature/humidity sensor
#
```
```
SENS_TEMP1 -2
SENS_HUMIDITY1 0
```
```
#
# Other outdoor/indoor temperature/humidity sensor
#
```
```
SENS_TEMP2 0
SENS_HUMIDITY2 0
```
```
#
```
```
SENS_TEMP3 0
SENS_HUMIDITY3 0
```
```
#
```
```
SENS_TEMP4 0
SENS_HUMIDITY4 0
```
```
#
```
```
SENS_TEMP5 0
SENS_HUMIDITY5 0
```
```
#
```
```
SENS_TEMP6 0
SENS_HUMIDITY6 0
```
```
#
```
```
SENS_TEMP7 0
SENS_HUMIDITY7 0
```
```
#
```
```
SENS_TEMP8 0
SENS_HUMIDITY8 0
```
```
#
```
```
SENS_TEMP9 0
SENS_HUMIDITY9 0
```
```
#
# Other sensor data alarm
#
```
```
SENS_PRESSURE 0
SENS_WIND 0
SENS_RAIN 0
SENS_UV 0
```
```
#
# Water temperature sensor (THWR288)
#
```
```
SENS_WATER0 0
SENS_WATER1 0
SENS_WATER2 0
SENS_WATER3 0
```
```
#
#----------------------------------------------------------------------#
# Alarm of sensor 
# allowed as positive, or negative, for example: 28 or -9
#----------------------------------------------------------------------#
#
# Main station Indoor temperature/humidity sensor
#
```
```
ALARM_MIN_TEMP0 0
ALARM_MAX_TEMP0 0
ALARM_MIN_HUMIDITY0 0
ALARM_MAX_HUMIDITY0 0
```
```
#
# Complected Outdoor temperature/humidity sensor
#
```
```
ALARM_MIN_TEMP1 0
ALARM_MAX_TEMP1 0
ALARM_MIN_HUMIDITY1 0
ALARM_MAX_HUMIDITY1 0
```
```
#
# Other outdoor/indoor temperature/humidity sensor
# [max 8 sensor, all 10 sensor]
#
```
```
ALARM_MIN_TEMP2 0
ALARM_MAX_TEMP2 0
ALARM_MIN_HUMIDITY2 0
ALARM_MAX_HUMIDITY2 0
```
```
#
```
```
ALARM_MIN_TEMP3 0
ALARM_MAX_TEMP3 0
ALARM_MIN_HUMIDITY3 0
ALARM_MAX_HUMIDITY3 0
```
```
#
```
```
ALARM_MIN_TEMP4 0
ALARM_MAX_TEMP4 0
ALARM_MIN_HUMIDITY4 0
ALARM_MAX_HUMIDITY4 0
```
```
#
```
```
ALARM_MIN_TEMP5 0
ALARM_MAX_TEMP5 0
ALARM_MIN_HUMIDITY5 0
ALARM_MAX_HUMIDITY5 0
```
```
#
```
```
ALARM_MIN_TEMP6 0
ALARM_MAX_TEMP6 0
ALARM_MIN_HUMIDITY6 0
ALARM_MAX_HUMIDITY6 0
```
```
#
```
```
ALARM_MIN_TEMP7 0
ALARM_MAX_TEMP7 0
ALARM_MIN_HUMIDITY7 0
ALARM_MAX_HUMIDITY7 0
```
```
#
```
```
ALARM_MIN_TEMP8 0
ALARM_MAX_TEMP8 0
ALARM_MIN_HUMIDITY8 0
ALARM_MAX_HUMIDITY8 0
```
```
#
```
```
ALARM_MIN_TEMP9 0
ALARM_MAX_TEMP9 0
ALARM_MIN_HUMIDITY9 0
ALARM_MAX_HUMIDITY9 0
```
```
#
# Other sensor data alarm
#
```
```
ALARM_MIN_PRESSURE 0
ALARM_MAX_PRESSURE 0
ALARM_MIN_WIND 0
ALARM_MAX_WIND 0
ALARM_MIN_RAIN 0
ALARM_MAX_RAIN 0
ALARM_MIN_UV 0
ALARM_MAX_UV 0
```
```
#
# Water temperature sensor [max 4 sensor]
#
```
```
ALARM_MIN_WATER0 0
ALARM_MAX_WATER0 0
```
```
#
```
```
ALARM_MIN_WATER1 0
ALARM_MAX_WATER1 0
```
```
#
```
```
ALARM_MIN_WATER2 0
ALARM_MAX_WATER2 0
```
```
#
```
```
ALARM_MIN_WATER3 0
ALARM_MAX_WATER3 0
```#```