#!/bin/sh

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ] || [ "$4" == "" ] || [ "$5" == "" ] || [ "$6" == "" ] || [ "$7" == "" ] || [ "$8" == "" ] ;
then
	echo "Don't run is manual..."
	echo "Exec /usr/bin/wmr_graph_rrd.sh"
	exit	
fi

WATERMARKOREGON="WMR Oregon Scientific USB weather data logger (c)created http://code.google.com/p/wmr/"

${2} graph ${4}/Wind-${5}-${6}.gif \
--width ${7} \
--height ${8} \
--start -${6} \
--end now \
--lower-limit 0 \
--rigid \
--slope-mode \
--watermark "${WATERMARKOREGON}" \
--vertical-label "Ветер метров в секунду" \
DEF:speed=${3}/WIND_0.rrd:WindSpeed:AVERAGE \
DEF:direction=${3}/WIND_0.rrd:WindDir:LAST \
CDEF:NNE=direction,0,4,LIMIT,UN,UNKN,INF,IF \
CDEF:ENE=direction,4,9,LIMIT,UN,UNKN,INF,IF \
CDEF:ESE=direction,9,13,LIMIT,UN,UNKN,INF,IF \
CDEF:SSE=direction,13,18,LIMIT,UN,UNKN,INF,IF \
CDEF:SSW=direction,18,22,LIMIT,UN,UNKN,INF,IF \
CDEF:WSW=direction,22,27,LIMIT,UN,UNKN,INF,IF \
CDEF:WNW=direction,27,31,LIMIT,UN,UNKN,INF,IF \
CDEF:NNW=direction,31,36,LIMIT,UN,UNKN,INF,IF \
COMMENT:"\n" \
AREA:NNE#0000FF55:"Север-северо-восток" \
AREA:ENE#C0C0C055:"Восток-северо-восток" \
AREA:ESE#FFFF0055:"Восток-юго-восток"  \
AREA:SSE#FF000055:"Юг-юго-восток" \
AREA:SSW#40000055:"Юг-юго-запад" \
AREA:WSW#FF40FF55:"Запад-юго-запад" \
AREA:WNW#40FFFF55:"Запад-северо-запад" \
AREA:NNW#038D8B55:"Север-северо-запад" \
COMMENT:"\n" \
GPRINT:direction:LAST:"Направление ветра\: тек\:%5.2lf°" \
GPRINT:direction:AVERAGE:"усредненная\:%5.2lf°\n" \
COMMENT:"\n" \
LINE:speed#0000C0:"Скорость ветра\:" \
GPRINT:speed:LAST:"тек\:%5.2lf м/с" \
GPRINT:speed:AVERAGE:"сред\:%5.2lf м/с" \
GPRINT:speed:MIN:"мин\:%5.2lf м/с" \
GPRINT:speed:MAX:"макс\:%5.2lf м/с\n"

