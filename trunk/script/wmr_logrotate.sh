#!/bin/sh

if [ "$1" == "" ] 
then
    echo "Logrotate data file for wmr-oregon weather logger"
    echo "(c) 2012 Den68 <idg68@yandex.ru>"
    echo "Global download URL: http://code.google.com/p/wmr/"
    echo ""
    echo "Please, type: $0 -logrotate"
    echo "or, insert cron job new line:"
    echo " for every day:"
    echo "   0 0 * * * * /usr/bin/wmr_logrotate.sh -logrotate"
    echo " for every month:"
    echo "   0 0 1 * * * /usr/bin/wmr_logrotate.sh -logrotate"
    echo " for every year:"
    echo "   0 0 1 1 * * /usr/bin/wmr_logrotate.sh -logrotate"
    echo ""
    exit
fi

if [ "$1" == "-logrotate" ] 
then
    echo "Logrotate ..."
    kill -USR2 `pidof wmr-oregon`
    exit
fi

### Format: (1/0 LOG) /weather/weather.log (1/0 SQL) /weather/weather.db (1/0 RRD) /weather
### Sttring: 1 weather/weather.log  1 weather/weather.db  1 weather

RDATA=`date '+%Y-%m-%d'`

###########################################################
#
# rotate log file
#
###########################################################

if [ "$1" == "1" ] 
then
    mv -f ${2} `echo ${2} | awk -F"." '{ print $1 }'`-${RDATA}.`echo ${2} | awk -F"." '{ print $2 }'`
fi

###########################################################
#
# rotate SQLite3 file
#
###########################################################

if [ "$3" == "1" ] 
then
    mv -f ${4}  `echo ${4} | awk -F"." '{ print $1 }'`-${RDATA}.`echo ${4} | awk -F"." '{ print $2 }'`
    cp ${4}.TMPL ${4}
fi

###########################################################
#
# rotate RRD file ? not needed ? exit, - else, remove exit
#
###########################################################
#
 exit
#

if [ "$5" == "1" ] 
then

    DIRF=`ls -1 ${6}/*.rrd`

    for i in ${DIRF}
    do
	mv -f ${i}  `echo ${i} | awk -F"." '{ print $1 }'`-${RDATA}.`echo ${i} | awk -F"." '{ print $2 }'`
    done
fi
