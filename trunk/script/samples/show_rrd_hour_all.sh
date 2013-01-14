#!/bin/sh

END=`date +%s`
START=`echo $END-3600 | bc` # over the hour

for i in `find /var/weather/ -name "*.rrd"` 
do 
    rrdtool fetch /var/weather/${i}.rrd AVERAGE start $START end $END
done
