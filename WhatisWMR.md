![http://www.nkl.ru/support/wmr/oregon_img/i.jpg](http://www.nkl.ru/support/wmr/oregon_img/i.jpg)

# Introduction #

WMR is a Oregon Scientific WMR/RMS/I series Linux/FreeBSD data reader - logger
OpenWRT project support.

# Support: #

---

```
Oregon Scientific LW301
Oregon Scientific WMR88
Oregon Scientific WMR100
Oregon Scientific WMR200
Oregon Scientific WMRS200
Oregon Scientific RMS300
Oregon Scientific RMS600
Oregon Scientific I300
Oregon Scientific I600
```

# Features #

---

`*`SQL sqlite3 database support for store data from weather station.

---

`*`Store data from weather station to log file in txt format.

---

`*`Correct all data from sensor (temperature, pressure, rain, wind).

---

`*`Build graphical statistic from sql data (rrd-tools).

---

`*`Posted to popularity weather web site weather data.

---



# Introduction #

---


The WMR/RMS/I series from Oregon Scientific, use a proprietary protocol for
their USB connection. It's very useful for enthusiasts running a headless
Linux box to collect and analyze data from this link, but unfortunately the
protocol isn't openly documented, nor are clients provided for this platform.

This  C program handles the USB protocol of the WMRxxx, or RMSxxx, or Ixxx,
and translates it an ASCII/SQLite3/RRD format, easy for parsing/analysing.
See directory sripts/ for example.

You'll need to setup the udev rules (see udev/README).

This is due to how libhid accesses the USB ports.

# SQLite #

---

First run script/wmr\_create\_db\_sqlite3.sh, this create sqlite3 DB structure
in /var/weather/weather.db
See structure sql database: conrib/wmr.sql

# Use #

---


To run:
> /usr/bin/wmr-oregon -c /etc/wmr.conf

> flag -c 

&lt;value&gt;

 = path and name to config file /etc/wmr.conf,
> > default ./wmr.conf, or:

---



> /usr/bin/wmr-oregon -d -c /etc/wmr.conf

> flag -d = start is a daemon server mode. (loging only syslog)
> > flag -s automatic enable.


---



> /usr/bin/wmr-oregon -s -c /etc/wmr.conf

> flag -s = print all info & debug info to local syslog server.


---


> /usr/bin/wmr-oregon -v

> flag -v = print all config token from config file,
> > this options require flag -c <path/to/config/name.ext>
> > before.


---


To autostart:

> cp contrib/wmr.init /etc/rc.d/init.d/
> ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc3.d/S95wmr
> ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc5.d/S95wmr


---


To reread config file, send:
> kill -HUP `pidof wmr-oregon


---


To reread config file and re init USB device, send:
> kill -USR1 `pidof wmr-oregon`


---


To logrotate data file - log/sql/rrd, send:
> kill -USR2 `pidof wmr-oregon`
> - run & see script/wmr\_logrotate.sh


---


To stop wmr-oregon in daemon mode, send:
> kill -TERM `pidof wmr-oregon`


---


To update internet weather hosting, support:
> www.pwsweather.com,
> www.pywws.com,
> www.wunderground.com
> - see script/update\_weather/README, **.sh**


---
