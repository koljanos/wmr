#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

if [ "${1}" == "3" ]; then

${2} graph ${4}/Temperature-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Температура C" \
DEF:temp1=${3}/TEMP_0.rrd:Temp:AVERAGE \
DEF:dew1=${3}/TEMP_0.rrd:DewPoint:AVERAGE \
DEF:temp2=${3}/TEMP_1.rrd:Temp:AVERAGE \
DEF:dew2=${3}/TEMP_1.rrd:DewPoint:AVERAGE \
DEF:wchill=${3}/WIND_0.rrd:WindChill:AVERAGE \
CDEF:temp1_by_16=temp1,16,/ \
AREA:temp1_by_16#F1F28E00 \
AREA:temp1_by_16#F1F28E11::STACK \
AREA:temp1_by_16#F1F28E22::STACK \
AREA:temp1_by_16#F1F28E33::STACK \
AREA:temp1_by_16#F1F28E44::STACK \
AREA:temp1_by_16#F1F28E55::STACK \
AREA:temp1_by_16#F1F28E66::STACK \
AREA:temp1_by_16#F1F28E77::STACK \
AREA:temp1_by_16#F1F28E88::STACK \
AREA:temp1_by_16#F1F28E99::STACK \
AREA:temp1_by_16#F1F28Eaa::STACK \
AREA:temp1_by_16#F1F28Ebb::STACK \
AREA:temp1_by_16#F1F28Ecc::STACK \
AREA:temp1_by_16#F1F28Edd::STACK \
AREA:temp1_by_16#F1F28Eee::STACK \
AREA:temp1_by_16#F1F28Eff::STACK \
CDEF:temp2_by_16=temp2,16,/ \
AREA:temp2_by_16#659EC700 \
AREA:temp2_by_16#659EC711::STACK \
AREA:temp2_by_16#659EC722::STACK \
AREA:temp2_by_16#659EC733::STACK \
AREA:temp2_by_16#659EC744::STACK \
AREA:temp2_by_16#659EC755::STACK \
AREA:temp2_by_16#659EC766::STACK \
AREA:temp2_by_16#659EC777::STACK \
AREA:temp2_by_16#659EC788::STACK \
AREA:temp2_by_16#659EC799::STACK \
AREA:temp2_by_16#659EC7aa::STACK \
AREA:temp2_by_16#659EC7bb::STACK \
AREA:temp2_by_16#659EC7cc::STACK \
AREA:temp2_by_16#659EC7dd::STACK \
AREA:temp2_by_16#659EC7ee::STACK \
AREA:temp2_by_16#659EC7ff::STACK \
LINE:temp1#B0B200:"В доме " \
GPRINT:temp1:LAST:"посл\: %5.1lf C" \
GPRINT:temp1:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp1:MIN:"мин\: %5.1lf C" \
GPRINT:temp1:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE1:temp2#000080:"На улице " \
GPRINT:temp2:LAST:"посл\: %5.1lf C" \
GPRINT:temp2:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp2:MIN:"мин\: %5.1lf C" \
GPRINT:temp2:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE2:wchill#000000:"Охлаждение ветром\:" \
GPRINT:wchill:LAST:"тек\: %5.1lf C" \
GPRINT:wchill:AVERAGE:"сред\: %5.1lf C" \
GPRINT:wchill:MIN:"мин\: %5.1lf C" \
GPRINT:wchill:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE3:dew1#A80000:"Точка росы\: дом " \
GPRINT:dew1:LAST:"тек\: %5.1lf C" \
LINE4:dew2#008000:"Точка росы\: улица " \
GPRINT:dew2:LAST:"тек\: %5.1lf C" \
COMMENT:"\n" \
VRULE:1293858000#ff0000 \
VRULE:1325394000#ff0000

elif [ "${1}" == "2" ]; then

${2} graph ${4}/Temperature-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Температура C" \
DEF:temp1=${3}/TEMP_0.rrd:Temp:AVERAGE \
DEF:dew1=${3}/TEMP_0.rrd:DewPoint:AVERAGE \
DEF:temp2=${3}/TEMP_1.rrd:Temp:AVERAGE \
DEF:dew2=${3}/TEMP_1.rrd:DewPoint:AVERAGE \
CDEF:temp1_by_16=temp1,16,/ \
AREA:temp1_by_16#F1F28E00 \
AREA:temp1_by_16#F1F28E11::STACK \
AREA:temp1_by_16#F1F28E22::STACK \
AREA:temp1_by_16#F1F28E33::STACK \
AREA:temp1_by_16#F1F28E44::STACK \
AREA:temp1_by_16#F1F28E55::STACK \
AREA:temp1_by_16#F1F28E66::STACK \
AREA:temp1_by_16#F1F28E77::STACK \
AREA:temp1_by_16#F1F28E88::STACK \
AREA:temp1_by_16#F1F28E99::STACK \
AREA:temp1_by_16#F1F28Eaa::STACK \
AREA:temp1_by_16#F1F28Ebb::STACK \
AREA:temp1_by_16#F1F28Ecc::STACK \
AREA:temp1_by_16#F1F28Edd::STACK \
AREA:temp1_by_16#F1F28Eee::STACK \
AREA:temp1_by_16#F1F28Eff::STACK \
CDEF:temp2_by_16=temp2,16,/ \
AREA:temp2_by_16#659EC700 \
AREA:temp2_by_16#659EC711::STACK \
AREA:temp2_by_16#659EC722::STACK \
AREA:temp2_by_16#659EC733::STACK \
AREA:temp2_by_16#659EC744::STACK \
AREA:temp2_by_16#659EC755::STACK \
AREA:temp2_by_16#659EC766::STACK \
AREA:temp2_by_16#659EC777::STACK \
AREA:temp2_by_16#659EC788::STACK \
AREA:temp2_by_16#659EC799::STACK \
AREA:temp2_by_16#659EC7aa::STACK \
AREA:temp2_by_16#659EC7bb::STACK \
AREA:temp2_by_16#659EC7cc::STACK \
AREA:temp2_by_16#659EC7dd::STACK \
AREA:temp2_by_16#659EC7ee::STACK \
AREA:temp2_by_16#659EC7ff::STACK \
LINE:temp1#B0B200:"В доме " \
GPRINT:temp1:LAST:"посл\: %5.1lf C" \
GPRINT:temp1:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp1:MIN:"мин\: %5.1lf C" \
GPRINT:temp1:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE1:temp2#000080:"На улице " \
GPRINT:temp2:LAST:"посл\: %5.1lf C" \
GPRINT:temp2:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp2:MIN:"мин\: %5.1lf C" \
GPRINT:temp2:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE2:dew1#A80000:"Точка росы\: дом " \
GPRINT:dew1:LAST:"тек\: %5.1lf C" \
LINE3:dew2#008000:"Точка росы\: улица " \
GPRINT:dew2:LAST:"тек\: %5.1lf C" \
COMMENT:"\n" \
VRULE:1293858000#ff0000 \
VRULE:1325394000#ff0000

elif [ "${1}" == "1" ]; then

${2} graph ${4}/Temperature-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Температура C" \
DEF:temp1=${3}/TEMP_0.rrd:Temp:AVERAGE \
DEF:dew1=${3}/TEMP_0.rrd:DewPoint:AVERAGE \
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
LINE:temp1#000080:"В доме " \
GPRINT:temp1:LAST:"посл\: %5.1lf C" \
GPRINT:temp1:AVERAGE:"сред\: %5.1lf C" \
GPRINT:temp1:MIN:"мин\: %5.1lf C" \
GPRINT:temp1:MAX:"макс\: %5.1lf C\n" \
COMMENT:"\n" \
LINE1:dew1#A80000:"Точка росы\: дом " \
GPRINT:dew1:LAST:"тек\: %5.1lf C" \
COMMENT:"\n" \
VRULE:1293858000#ff0000 \
VRULE:1325394000#ff0000

fi

