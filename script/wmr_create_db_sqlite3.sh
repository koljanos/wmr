#!/bin/sh
# Create Database and table SQLITE3 for Weather SQL Logger 

rm -f weather.db
sqlite3 weather.db < ../contrib/wmr.sql

mkdir -p /var/weather
mv -f /var/weather/weather.db /var/weather/weather.db.`date '+%d%m%Y%H%M%S'`
cp -f weather.db /var/weather/weather.db
mv -f weather.db /var/weather/weather.db.TMPL
