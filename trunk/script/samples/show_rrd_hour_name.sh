#!/bin/sh

if [ "$1" == "" ] 
then
    echo "Please, enter name of .rrd file, no file extension!"
fi

END=`date +%s`
START=`echo $END-3600 | bc` # over the hour
rrdtool fetch /var/weather/$1.rrd AVERAGE start $START end $END
