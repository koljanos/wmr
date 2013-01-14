#!/bin/sh
# Create  RRD Database for Weather TXT/SQL/RRD/SNMP Logger 

wmrconf=${wmrconf:-/etc/wmr/wmr.conf}

        if [ ! -f $wmrconf ]; then
                echo "Error: '(" $wmrconf " not found)'"
                exit 1
        fi

	RRDSAVEPATH=`cat $wmrconf | grep RRDSAVEPATH | awk '{ print $2 }'`

	if [ ! -x "${RRDSAVEPATH}" ]; then
            echo "Error: '(rrd data base save path - give from wmr.conf not found)'"
	    exit
	fi

        if [ ! -x "`which rrdtool`" ]; then
                echo "Error: '(rrdtool not found)'"
		RRDEXECPATH==`cat $wmrconf | grep RRDEXECPATH | awk '{ print $2 }'`

		if [ ! -x "${RRDEXECPATH}" ]; then
            	    echo "Error: '(rrdtool in path from wmr.conf not found)'"
		    exit
		fi
	else
	    RRDEXECPATH=`which rrdtool`
        fi

CREATE_TABLE="TEMP WATER PRESSURE RAIN WIND UV MAIN"
WMR_RRD_CREATE_BASE="RRA:AVERAGE:0.5:1:4320 RRA:AVERAGE:0.5:15:2880 RRA:AVERAGE:0.5:120:2160 RRA:AVERAGE:0.5:720:1440 RRA:MIN:0.5:1:4320 RRA:MIN:0.5:15:2880 RRA:MIN:0.5:120:2160 RRA:MIN:0.5:720:1440 RRA:MAX:0.5:1:4320 RRA:MAX:0.5:15:2880 RRA:MAX:0.5:120:2160 RRA:MAX:0.5:720:1440 RRA:LAST:0.5:1:4320 RRA:LAST:0.5:15:2880 RRA:LAST:0.5:120:2160 RRA:LAST:0.5:720:1440"


for i in ${CREATE_TABLE}
do 

    if [ "$i" == "TEMP" ] ; then
	for n in 0 1 2 3
	do
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_${n}.rrd --step 150 DS:Temp:GAUGE:240:-50:150 DS:DewPoint:GAUGE:240:-50:150 DS:Humidity:GAUGE:240:0:100 ${WMR_RRD_CREATE_BASE}
	done
    elif [ "$i" == "WATER" ] ; then
	for n in 0 1 2 3
	do
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_${n}.rrd --step 150 DS:Water:GAUGE:240:-50:150 ${WMR_RRD_CREATE_BASE}
	done
    elif [ "$i" == "PRESSURE" ] ; then
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_0.rrd --step 150 DS:Pressure:GAUGE:240:700:800 DS:PressureAlt:GAUGE:240:700:800 ${WMR_RRD_CREATE_BASE}
    elif [ "$i" == "RAIN" ] ; then
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_0.rrd --step 150 DS:RainRate:GAUGE:240:0:100 DS:RainHour:GAUGE:240:0:100 DS:RainDay:GAUGE:240:0:100 DS:RainAll:GAUGE:240:0:100 ${WMR_RRD_CREATE_BASE}
    elif [ "$i" == "WIND" ] ; then
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_0.rrd --step 150 DS:WindSpeed:GAUGE:240:0:200 DS:WindAwg:GAUGE:240:0:200 DS:WindDir:GAUGE:240:0:200 DS:WindChill:GAUGE:240:-100:100 ${WMR_RRD_CREATE_BASE}
    elif [ "$i" == "UV" ] ; then
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_0.rrd --step 150 DS:UV:GAUGE:240:0:15 ${WMR_RRD_CREATE_BASE}
    elif [ "$i" == "MAIN" ] ; then
	    ${RRDEXECPATH} create ${RRDSAVEPATH}/${i}_0.rrd --step 150 DS:MainBattery:GAUGE:240:0:1 DS:ExtPower:GAUGE:240:0:1 DS:Level:GAUGE:240:0:100 ${WMR_RRD_CREATE_BASE}
    fi

done

exit 0
