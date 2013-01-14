#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

${2} graph ${4}/UV-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--upper-limit 10 \
--lower-limit 0 \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Ультрафиолетовое излучение:" \
DEF:uv=${3}/UV_0.rrd:UV:AVERAGE \
CDEF:uv_by_16=uv,1,/ \
AREA:uv_by_16#A8000011::STACK \
AREA:uv_by_16#A8000022::STACK \
AREA:uv_by_16#A8000033::STACK \
AREA:uv_by_16#A8000044::STACK \
AREA:uv_by_16#A8000055::STACK \
AREA:uv_by_16#A8000066::STACK \
AREA:uv_by_16#A8000077::STACK \
AREA:uv_by_16#A8000088::STACK \
AREA:uv_by_16#A8000099::STACK \
AREA:uv_by_16#A80000aa::STACK \
AREA:uv_by_16#A80000bb::STACK \
AREA:uv_by_16#A80000cc::STACK \
AREA:uv_by_16#A80000dd::STACK \
AREA:uv_by_16#A80000ee::STACK \
AREA:uv_by_16#A80000ff::STACK \
AREA:uv_by_16#A80000ff::STACK \
LINE:uv#A80000:"УФ излучение\: " \
GPRINT:uv:LAST:"тек\: %5.1lf" \
GPRINT:uv:AVERAGE:"сред\: %5.1lf" \
GPRINT:uv:MIN:"мин\: %5.1lf" \
GPRINT:uv:MAX:"макс\: %5.1lf\n" \
COMMENT:"\n" \
VRULE:1356584400#A80000 \
VRULE:1356670800#A80000

