#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] ; 
then
    echo "Alarm file for wmr-oregon weather logger"
    echo "(c) 2012 Den68 <idg68@yandex.ru>"
    echo "Global download URL: http://code.google.com/p/wmr/"
    echo ""
    echo "Use format:"
    echo "(SENSOR TYPE) (NUM OF SENSOR) (CURENT STATUS) (ALARM STATUS)"
    echo "Examle:"
    echo "TEMP 1 -7 MIN"
    echo "TEMP 1 28 MAX"
    echo "Run only wmr-oregon software is alarm enabled"
    echo "cpopy & edit all sensor named script in ./etc/wmr/script/ to /etc/wmr/script/"
    echo "copy this script to /usr/bin/wmr_alarm.sh"
    echo "edit /etc/wmr/wmr.conf - lines: ALARMENABLE 1 & ALARMBIN /usr/bin/wmr_alarm.sh"
    exit
fi

if [ "$1" == "TEMP" ] || [ "$1" == "HUMIDITY" ] ; then
    /etc/wmr/script_alarm/WMR_${1}_${2}_${4}.sh $3
    exit
elif [ "$1" == "PRESSURE" ] || [ "$1" == "RAIN" ] || [ "$1" == "WIND" ] || [ "$1" == "UV" ] || [ "$1" == "WATER" ] ; then
    /etc/wmr/script_alarm/WMR_${1}_${4}.sh $3
    exit
elif [ "$1" == "BATTERY" ] ; then
    /etc/wmr/script_alarm/WMR_${1}.sh ${4} ${2} ${3}
fi

exit 0
