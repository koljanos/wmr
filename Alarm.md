# Alarm event - WMR logger for Oregon Scientific USB protocol #

---

Edit section alarm in [config file](WMRConfigFile.md). For event alarming, wmr-oregon runing
script. Default: /usr/bin/wmr\_alarm.sh
- see script/wmr\_alarm.sh & edit for you job.
- see script/controlling/C2000-CP1.php for controling 4 line from [C2000-CP1](C2000CP1controlling4LineRU.md) [Bolid(C)trademark](http://www.bolid.ru/production/devices/devices_48.html)
```
Format command line send to wmr_alarm.sh:
    /path/to/script/wmr_alarm.sh 'TYPE SENSOR' 'NUM SENSOR' 'VALUE SENSOR' 'TYPE ALARM MIN/MAX'
    sample:
    /path/to/script/wmr_alarm.sh TEMP 1 -22 MIN
    /path/to/script/wmr_alarm.sh PRESSURE 0 778 MAX
    /path/to/script/wmr_alarm.sh HUMIDITY 3 12 MIN
    ... etc
If sensor type = BATTERY, format command:
    /path/to/script/wmr_alarm.sh BATTERY 'NUM SENSOR' 'VALUE SENSOR' 'TYPE SENSOR'
    sample:
    /path/to/script/wmr_alarm.sh BATTERY 1 7 TEMP
    /path/to/script/wmr_alarm.sh BATTERY 0 11 MAIN
Valid type of sensor:
    All data sensor: "TEMP", "HUMIDITY", "PRESSURE", "WIND", "RAIN", "UV"
    Battery check sensor: "MAIN", "WATER", "TEMP", "WIND", "RAIN", "UV"
```
Default to install advanced alarm script in /usr/bin/wmr\_alarm.sh
Sub user edit script default locate in /etc/wmr/script\_alarm
```
Locate in: script/wmr_alarm_advanced/ - see for detail ...
```