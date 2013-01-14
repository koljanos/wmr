#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

${2} graph ${4}/Water_${1}-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Температура воды C" \
DEF:temp1=${3}/WATER_${1}.rrd:Water:AVERAGE \
CDEF:temp1_by_16=temp1,16,/ \
AREA:temp1_by_16#659EC700 \
AREA:temp1_by_16#659EC711::STACK \
AREA:temp1_by_16#659EC722::STACK \
AREA:temp1_by_16#659EC733::STACK \
AREA:temp1_by_16#659EC744::STACK \
AREA:temp1_by_16#659EC755::STACK \
AREA:temp1_by_16#659EC766::STACK \
AREA:temp1_by_16#659EC777::STACK \
AREA:temp1_by_16#659EC788::STACK \
AREA:temp1_by_16#659EC799::STACK \
AREA:temp1_by_16#659EC7aa::STACK \
AREA:temp1_by_16#659EC7bb::STACK \
AREA:temp1_by_16#659EC7cc::STACK \
AREA:temp1_by_16#659EC7dd::STACK \
AREA:temp1_by_16#659EC7ee::STACK \
AREA:temp1_by_16#659EC7ff::STACK \
LINE:temp1#000080:"В бассейне " \
GPRINT:temp1:LAST:"посл\: %5.1lf C" \
GPRINT:temp1:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp1:MIN:"мин\: %5.1lf C" \
GPRINT:temp1:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
VRULE:1293858000#ff0000 \
VRULE:1325394000#ff0000
