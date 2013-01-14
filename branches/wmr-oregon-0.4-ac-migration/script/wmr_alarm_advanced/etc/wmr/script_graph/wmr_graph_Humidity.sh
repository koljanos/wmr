#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

if [ "${1}" == "2" ]; then

${2} graph ${4}/Humidity-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Влажность: %%" \
DEF:hum0=${3}/TEMP_0.rrd:Humidity:AVERAGE \
DEF:hum1=${3}/TEMP_1.rrd:Humidity:AVERAGE \
CDEF:humid_by_16=hum1,16,/ \
AREA:humid_by_16#659EC700 \
AREA:humid_by_16#659EC711::STACK \
AREA:humid_by_16#659EC722::STACK \
AREA:humid_by_16#659EC733::STACK \
AREA:humid_by_16#659EC744::STACK \
AREA:humid_by_16#659EC755::STACK \
AREA:humid_by_16#659EC766::STACK \
AREA:humid_by_16#659EC777::STACK \
AREA:humid_by_16#659EC788::STACK \
AREA:humid_by_16#659EC799::STACK \
AREA:humid_by_16#659EC7aa::STACK \
AREA:humid_by_16#659EC7bb::STACK \
AREA:humid_by_16#659EC7cc::STACK \
AREA:humid_by_16#659EC7dd::STACK \
AREA:humid_by_16#659EC7ee::STACK \
AREA:humid_by_16#659EC7ff::STACK \
LINE:hum0#B0B200:"В доме " \
GPRINT:hum0:LAST:"посл\: %1.0lf %%" \
GPRINT:hum0:AVERAGE:"сред\: %1.0lf %%" \
GPRINT:hum0:MIN:"мин\: %1.0lf %%" \
GPRINT:hum0:MAX:"макс\: %1.0lf %%\n" \
COMMENT:"\n" \
LINE1:hum1#000080:"На улице " \
GPRINT:hum1:LAST:"посл\: %1.0lf %%" \
GPRINT:hum1:AVERAGE:"сред\: %1.0lf %%" \
GPRINT:hum1:MIN:"мин\: %1.0lf %%" \
GPRINT:hum1:MAX:"макс\: %1.0lf %%\n" \
COMMENT:"\n" \
VRULE:1356584400#ff0000 \
VRULE:1356670800#ff0000

elif [ "${1}" == "2" ] ; then

${2} graph ${4}/Humidity-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Влажность: %%" \
DEF:hum1=${3}/TEMP_0.rrd:Humidity:AVERAGE \
CDEF:humid_by_16=hum1,16,/ \
AREA:humid_by_16#659EC700 \
AREA:humid_by_16#659EC711::STACK \
AREA:humid_by_16#659EC722::STACK \
AREA:humid_by_16#659EC733::STACK \
AREA:humid_by_16#659EC744::STACK \
AREA:humid_by_16#659EC755::STACK \
AREA:humid_by_16#659EC766::STACK \
AREA:humid_by_16#659EC777::STACK \
AREA:humid_by_16#659EC788::STACK \
AREA:humid_by_16#659EC799::STACK \
AREA:humid_by_16#659EC7aa::STACK \
AREA:humid_by_16#659EC7bb::STACK \
AREA:humid_by_16#659EC7cc::STACK \
AREA:humid_by_16#659EC7dd::STACK \
AREA:humid_by_16#659EC7ee::STACK \
AREA:humid_by_16#659EC7ff::STACK \
LINE1:hum1#000080:"В доме " \
GPRINT:hum1:LAST:"посл\: %1.0lf %%" \
GPRINT:hum1:AVERAGE:"сред\: %1.0lf %%" \
GPRINT:hum1:MIN:"мин\: %1.0lf %%" \
GPRINT:hum1:MAX:"макс\: %1.0lf %%\n" \
COMMENT:"\n" \
VRULE:1356584400#ff0000 \
VRULE:1356670800#ff0000

fi
