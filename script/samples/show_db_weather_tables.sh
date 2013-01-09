#!/bin/sh
WDB="/var/weather/weather.db"

# sqlite3 -line ${WDB} "SHOW TABLES LIKE 'TABLE'"
sqlite3 -line ${WDB} "SELECT name FROM sqlite_master WHERE type = 'table'"

