#!/bin/sh
WDB="/var/weather/weather.db"
SENS=`sqlite3 ${WDB} "select DISTINCT(sensor) from TEMP"`

echo ""

for i in ${SENS}
do
echo ""
echo "Temperature sensor: #${i}"
sqlite3 -line ${WDB} "select MAX(temp), MIN(temp), AVG(temp), MAX(humidity), MIN(humidity),AVG(humidity) from TEMP where sensor = ${i}"
echo "Current:"
sqlite3 -line ${WDB} "select temp,humidity from TEMP where sensor = ${i} ORDER BY tdate DESC LIMIT 1"
done

echo ""
echo "Pressure sensor:"
sqlite3 -line ${WDB} "select MAX(pressure), MIN(pressure), AVG(pressure), MAX(altpressure), MIN(altpressure),AVG(altpressure) from PRESSURE"
echo "Current:"
sqlite3 -line ${WDB} "select pressure from PRESSURE ORDER BY tdate DESC LIMIT 1"

echo ""
echo "Wind sensor:"
sqlite3 -line ${WDB} "select MAX(speed), MIN(speed), AVG(speed), MAX(avgspeed), MIN(avgspeed),AVG(avgspeed) from WIND"
echo "Current:"
sqlite3 -line ${WDB} "select speed,dir from WIND ORDER BY tdate DESC LIMIT 1"

echo ""
echo "RAIN sensor:"
sqlite3 -line ${WDB} "select MAX(rate), MIN(rate), AVG(rate), MAX(hour_total), MIN(hour_total), AVG(hour_total), MAX(day_total), MIN(day_total), AVG(day_total), MAX(all_total), MIN(all_total),AVG(all_total) from RAIN"
echo "Current:"
sqlite3 -line ${WDB} "select rate from RAIN ORDER BY tdate DESC LIMIT 1"

echo ""
echo "UV sensor:"
sqlite3 -line ${WDB} "select MAX(uvindex), MIN(uvindex), AVG(uvindex) from UV"
echo "Current:"
sqlite3 -line ${WDB} "select uvindex from UV ORDER BY tdate DESC LIMIT 1"

echo ""
