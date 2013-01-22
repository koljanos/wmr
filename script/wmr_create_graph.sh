#!/bin/sh
#
# Script generate graphic image from wmr-oregon weather logger RRD datbase 
# (c) 2012 Den68 <idg68@yandex.ru>
# Latest download URL: http://www.nkl.ru/support/wmr/
# Global download URL: http://code.google.com/p/wmr/
#

# Path to wmr.conf
wmrconf=${wmrconf:-/etc/wmr/wmr.conf}

        if [ ! -f ${wmrconf} ]; then
                echo "Error: '(" ${wmrconf} " not found)'"
                exit 1
        fi

        RRDSAVEPATH=`cat $wmrconf | grep RRDSAVEPATH | awk '{ print $2 }'`

        if [ ! -d "${RRDSAVEPATH}" ]; then
            echo "Error: '(rrd data base save path - give from wmr.conf not found)'"
            exit
        fi

	GRAPHIMGPATH=`cat $wmrconf | grep GRAPHIMGPATH | awk '{ print $2 }'`

        if [ ! -d "${GRAPHIMGPATH}" ]; then
            echo "Error: '(rrd graphic file save path - give from wmr.conf not found)'"
            exit
        fi

	GRAPHEXECPATH=`cat $wmrconf | grep GRAPHEXECPATH | awk '{ print $2 }'`

        if [ ! -d "${GRAPHEXECPATH}" ]; then
            echo "Error: '(script exec path - give from wmr.conf not found)'"
            exit
        fi

	GRAPHPERIOD=`cat $wmrconf | grep GRAPHPERIOD | awk -F'\"' '{ print $2 }'`

        if [ "${GRAPHPERIOD}" == "" ]; then
            echo "Error: '(period to create graphic file - give from wmr.conf not found)'"
            exit
        fi

	IMGWSIZEL=`cat $wmrconf | grep IMGWSIZEL | awk '{ print $2 }'`

        if [ "${IMGWSIZEL}" == "" ]; then
            echo "Error: '(width image size for large graphic file - give from wmr.conf not found)'"
            exit
        fi


	IMGHSIZEL=`cat $wmrconf | grep IMGHSIZEL | awk '{ print $2 }'`

        if [ "${IMGHSIZEL}" == "" ]; then
            echo "Error: '(height image size for large graphic file - give from wmr.conf not found)'"
            exit
        fi


	IMGWSIZES=`cat $wmrconf | grep IMGWSIZES | awk '{ print $2 }'`

        if [ "${IMGWSIZES}" == "" ]; then
            echo "Error: '(width image size for smale graphic file - give from wmr.conf not found)'"
            exit
        fi


	IMGHSIZES=`cat $wmrconf | grep IMGHSIZES | awk '{ print $2 }'`

        if [ "${IMGHSIZES}" == "" ]; then
            echo "Error: '(height image size for smale graphic file - give from wmr.conf not found)'"
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

IMGCSIZE="l s"
WATERSENSOR="0 1 2 3 4"
TEMPSENSOR="0 1 2 3 4 5 6 7 8 9"
WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

for n in ${GRAPHPERIOD}
do

	for i in ${IMGCSIZE}
	do
		IMGWSIZE=""
		IMGHSIZE=""

 		if [ "$i" == "s" ] ; then
			IMGWSIZE=${IMGWSIZES}
			IMGHSIZE=${IMGHSIZES}
		elif [ "$i" == "l" ] ; then
			IMGWSIZE=${IMGWSIZEL}
			IMGHSIZE=${IMGHSIZEL}
		fi

		###############
		### Humidity
		###############
		if [ -f "${RRDSAVEPATH}/TEMP_0.rrd" ] && [ -f "${RRDSAVEPATH}/TEMP_1.rrd" ] ;
		then
			${GRAPHEXECPATH}/wmr_graph_Humidity_all.sh 2 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		else
			${GRAPHEXECPATH}/wmr_graph_Humidity_all.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		###############
		### Temperature
		###############
		if [ -f "${RRDSAVEPATH}/TEMP_0.rrd" ] && [ -f "${RRDSAVEPATH}/TEMP_1.rrd" ] && [ -f "${RRDSAVEPATH}/WIND_0.rrd" ] ; then
			${GRAPHEXECPATH}/wmr_graph_Temperature_all.sh 3 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		elif [ -f "${RRDSAVEPATH}/TEMP_0.rrd" ] && [ -f "${RRDSAVEPATH}/TEMP_1.rrd" ] ; then
			${GRAPHEXECPATH}/wmr_graph_Temperature_all.sh 2 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		elif [ -f "${RRDSAVEPATH}/TEMP_0.rrd" ] ; then
			${GRAPHEXECPATH}/wmr_graph_Temperature_all.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		for z in ${TEMPSENSOR}
		do
			if [ -f "${RRDSAVEPATH}/TEMP_${z}.rrd" ] ;
			then 
				${GRAPHEXECPATH}/wmr_graph_TempHum.sh ${z} ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
			fi
		done

		###############
		### Wind
		###############
		if [ -f "${RRDSAVEPATH}/WIND_0.rrd" ] ;
		then 
			${GRAPHEXECPATH}/wmr_graph_Wind.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		###############
		### Rain
		###############
		if [ -f "${RRDSAVEPATH}/RAIN_0.rrd" ] ;
		then 
			${GRAPHEXECPATH}/wmr_graph_Rain.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		###############
		### Pressure
		###############
		if [ -f "${RRDSAVEPATH}/PRESSURE_0.rrd" ] ;
		then 
			${GRAPHEXECPATH}/wmr_graph_Pressure.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		###############
		### UV
		###############
		if [ -f "${RRDSAVEPATH}/UV_0.rrd" ] ;
		then 
			${GRAPHEXECPATH}/wmr_graph_UV.sh 1 ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
		fi

		###############
		### Water
		###############
		for z in ${WATERSENSOR}
		do
			if [ -f "${RRDSAVEPATH}/WATER_${z}.rrd" ] ;
			then 
				${GRAPHEXECPATH}/wmr_graph_Water.sh ${z} ${RRDEXECPATH} ${RRDSAVEPATH} ${GRAPHIMGPATH} ${i} ${n} ${IMGWSIZE} ${IMGHSIZE} ${i}
			fi
		done

	done
done

exit 0

