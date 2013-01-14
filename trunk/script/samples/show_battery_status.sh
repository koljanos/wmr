#!/bin/sh
WDB="/var/weather/weather.db"
SENS=`sqlite3 ${WDB} "select DISTINCT(sensor) from TEMP"`

echo ""
echo "If battery or powered = 0 - is Good state, 1 >... neede chande battery..."

echo ""
echo "Main station:"
sqlite3 -line ${WDB} "select battery,powered from CLOCK ORDER BY tdate DESC LIMIT 1"

for i in ${SENS}
do
echo ""
echo "Temperature sensor: #${i}"
sqlite3 -line ${WDB} "select battery from TEMP where sensor = ${i} ORDER BY tdate DESC LIMIT 1"
done


echo ""
echo "Wind sensor:"
sqlite3 -line ${WDB} "select battery from WIND ORDER BY tdate DESC LIMIT 1"

echo ""
echo "RAIN sensor:"
sqlite3 -line ${WDB} "select battery from RAIN ORDER BY tdate DESC LIMIT 1"

echo ""
echo "UV sensor:"
sqlite3 -line ${WDB} "select battery from UV ORDER BY tdate DESC LIMIT 1"

echo ""
