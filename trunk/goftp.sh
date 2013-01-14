#!/bin/sh
# Put from ftp to router

#
exit

SRV="192.168.220.100"
UN="root"
PW="den68"
DIR1="/usr/bin"
DIR2="/usr/lib/wmr"
DIR3="/weather"

ftp -d -n $SRV <<End-Of-Session
user $UN $PW
binary
cd $DIR1
put wmrd
chmod 777 wmrd
put ../shm shm
chmod 777 shm
mkdir $DIR2
cd $DIR2
put libwmr-alarm.so
put libwmr-file.so
put libwmr-rrd.so
put libwmr-snmp.so
put libwmr-sql.so
put libwmr-upd.so
cd $DIR3
delete weather.db
delete weather.db.TMPL
delete weather.db-journal
delete weather.log
ls
bye
End-Of-Session

rm -f libwmr-*.so
rm -f wmrd

# put contrib/weather.db weather.db
# put contrib/weather.db.TMPL weather.db.TMPL
#delete MAIN_0.rrd
#delete PRESSURE_0.rrd
#delete TEMP_0.rrd
#delete TEMP_1.rrd
#delete UV_0.rrd
#delete WIND_0.rrd
