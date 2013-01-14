#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

${2} graph ${4}/Pressure-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--upper-limit 800 \
--lower-limit 700 \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Давление мм рт. ст." \
DEF:dispressure=${3}/PRESSURE_0.rrd:Pressure:AVERAGE \
CDEF:pressure_by_16=dispressure,700,-,16,/ \
LINE1:700#FFFFFF: \
AREA:pressure_by_16#659EC711::STACK \
AREA:pressure_by_16#659EC722::STACK \
AREA:pressure_by_16#659EC733::STACK \
AREA:pressure_by_16#659EC744::STACK \
AREA:pressure_by_16#659EC755::STACK \
AREA:pressure_by_16#659EC766::STACK \
AREA:pressure_by_16#659EC777::STACK \
AREA:pressure_by_16#659EC788::STACK \
AREA:pressure_by_16#659EC799::STACK \
AREA:pressure_by_16#659EC7aa::STACK \
AREA:pressure_by_16#659EC7bb::STACK \
AREA:pressure_by_16#659EC7cc::STACK \
AREA:pressure_by_16#659EC7dd::STACK \
AREA:pressure_by_16#659EC7ee::STACK \
AREA:pressure_by_16#659EC7ff::STACK \
AREA:pressure_by_16#659EC7ff::STACK \
LINE2:dispressure#659EC7:"Барометр (давление)" \
GPRINT:dispressure:LAST:"тек\: %5.1lf" \
GPRINT:dispressure:AVERAGE:"сред\: %5.1lf" \
GPRINT:dispressure:MIN:"мин\: %5.1lf" \
GPRINT:dispressure:MAX:"макс\: %5.1lf\n" \
COMMENT:"\n" \
VRULE:1356584400#ff0000 \
VRULE:1356670800#ff0000

