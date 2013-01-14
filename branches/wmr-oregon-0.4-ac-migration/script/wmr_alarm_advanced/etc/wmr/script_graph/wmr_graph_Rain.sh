#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

${2} graph ${4}/Rain-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
-u 0 \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Осадки: мм" \
DEF:rainrate=${3}/RAIN_0.rrd:RainRate:AVERAGE \
DEF:raintotal=${3}/RAIN_0.rrd:RainAll:AVERAGE \
DEF:rainday=${3}/RAIN_0.rrd:RainDay:AVERAGE \
DEF:rainhour=${3}/RAIN_0.rrd:RainHour:AVERAGE \
CDEF:rain_by_16=raintotal,16,/ \
AREA:rain_by_16#659EC700 \
AREA:rain_by_16#659EC711::STACK \
AREA:rain_by_16#659EC722::STACK \
AREA:rain_by_16#659EC733::STACK \
AREA:rain_by_16#659EC744::STACK \
AREA:rain_by_16#659EC755::STACK \
AREA:rain_by_16#659EC766::STACK \
AREA:rain_by_16#659EC777::STACK \
AREA:rain_by_16#659EC788::STACK \
AREA:rain_by_16#659EC799::STACK \
AREA:rain_by_16#659EC7aa::STACK \
AREA:rain_by_16#659EC7bb::STACK \
AREA:rain_by_16#659EC7cc::STACK \
AREA:rain_by_16#659EC7dd::STACK \
AREA:rain_by_16#659EC7ee::STACK \
AREA:rain_by_16#659EC7ff::STACK \
LINE:rainhour#0000C0:"Осадков в час\:" \
GPRINT:rainhour:LAST:"тек\:%5.2lf" \
GPRINT:rainhour:AVERAGE:"сред\:%5.2lf" \
GPRINT:rainhour:MIN:"мин\:%5.2lf" \
GPRINT:rainhour:MAX:"макс\:%5.2lf\n" \
LINE1:rainday#008000:"Осадков в день\:" \
GPRINT:rainday:LAST:"тек\:%5.2lf" \
GPRINT:rainday:AVERAGE:"сред\:%5.2lf" \
GPRINT:rainday:MIN:"мин\:%5.2lf" \
GPRINT:rainday:MAX:"макс\:%5.2lf\n" \
LINE2:raintotal#659EC7:"Осадки итог (мм)\:" \
GPRINT:raintotal:LAST:"тек\:%5.2lf" \
GPRINT:raintotal:AVERAGE:"сред\:%5.2lf" \
GPRINT:raintotal:MIN:"мин\:%5.2lf" \
GPRINT:raintotal:MAX:"макс\:%5.2lf\n" \
LINE3:rainrate#254117:"Уровень осадков (мм/час)\:" \
GPRINT:rainrate:LAST:"тек\:%5.2lf" \
GPRINT:rainrate:AVERAGE:"сред\:%5.2lf" \
GPRINT:rainrate:MIN:"мин\:%5.2lf" \
GPRINT:rainrate:MAX:"макс\:%5.2lf\n" \
VRULE:1356584400#ff0000 \
VRULE:1356670800#ff0000

