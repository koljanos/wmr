#!/bin/sh
WDB="/var/weather/weather.db"
SENS=`sqlite3 ${WDB} "select DISTINCT(sensor) from TEMP"`

echo ""

for i in ${SENS}
do
echo ""
echo "Temperature sensor: #${i}"
sqlite3 -line ${WDB} "select temp,humidity from TEMP where sensor = ${i} ORDER BY tdate DESC LIMIT 1"
done

echo ""
echo "Pressure sensor:"
sqlite3 -line ${WDB} "select pressure from PRESSURE ORDER BY tdate DESC LIMIT 1"

echo ""
echo "Wind sensor:"
sqlite3 -line ${WDB} "select speed,dir from WIND ORDER BY tdate DESC LIMIT 1"

echo ""
echo "RAIN sensor:"
sqlite3 -line ${WDB} "select rate from RAIN ORDER BY tdate DESC LIMIT 1"

echo ""
echo "UV sensor:"
sqlite3 -line ${WDB} "select uvindex from UV ORDER BY tdate DESC LIMIT 1"

echo ""
