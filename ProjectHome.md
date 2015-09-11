![http://www.nkl.ru/support/wmr/oregon_img/WMR-READER-LOGGER.jpg](http://www.nkl.ru/support/wmr/oregon_img/WMR-READER-LOGGER.jpg)

---

[Supports](WMRSupportHardware.md) [Features](WhatisWMR.md) [Download](http://www.nkl.ru/support/wmr/wmr-oregon.tar.gz) [About WMR(RU)](WMRAboutRU.md) [Usage(RU)](WMRUsageRU.md) [Controlling 4 Line(RU)](C2000CP1controlling4LineRU.md) [Visualisation to Web](RRDCreateImg.md)

---


# [Supports](WMRSupportHardware.md) #

---

```
Oregon Scientific LW301
Oregon Scientific WMR88
Oregon Scientific WMR100
Oregon Scientific WMR200
Oregon Scientific WMRS200
Oregon Scientific RMS300A
Oregon Scientific RMS600
Oregon Scientific I300
Oregon Scientific I600
```


---

# Requisites #

---


Developer lib:
```
- [libhid] package installed.
- [libusb 0.x] package installed.
- [libsqlite3] package installed.
- [rrdtool] needed to weather grapher. 
```


---

# [Features](WhatisWMR.md) #

---

```
`*`SQL sqlite3 database support for store data from weather station.
`*`Store data from weather station to log data file in txt format.
`*`Correct all data from sensor (temperature, pressure, rain, wind).
`*`Alarm method from all sensor (temperature, pressure, rain, wind).
`*`Build graphical statistic from RRD data (rrd-tools).
`*`Posted to popularity weather web site weather data.
```


---


# [Introduction](WMRdebugScreenshot.md) #

---

```
The WMR/RMS/I series from Oregon Scientific, use a proprietary protocol for 
their USB connection. It's very useful for enthusiasts running a headless 
Linux box to collect and analyze data from this link, but unfortunately the 
protocol isn't openly documented, nor are clients provided for this platform. 

This  C program handles the USB protocol of the WMRxxx, or RMSxxx, or Ixxx, 
and translates it an ASCII/SQLite3/RRD format, easy for parsing/analysing. 
See directory sripts/ for example.

You'll need to setup the udev rules (see udev/README). 

This is due to how libhid accesses the USB ports. 
```

---


# [WMR Web Interface](http://www.nkl.ru/support/wmr/wmr-web-demo/) #

---

[![](http://www.nkl.ru/support/wmr/oregon_img/webscrshoot.png)](http://www.nkl.ru/support/wmr/wmr-web-demo/)

[Download WMR Web interface](http://www.nkl.ru/support/wmr/wmr-web-interface.tar.gz)

---

# [Features](WhatisWMR.md) [(RU)](WMRAboutRU.md) #
# [Supports](WMRSupportHardware.md) #

---

# [Download](http://www.nkl.ru/support/wmr/wmr-oregon.tar.gz) #
# [Compile](Compile.md) #
# [Install](Install.md) #
# [Use](Use.md) [(RU)](WMRUsageRU.md) #
# [Statment in wmr.conf](WMRConfigFile.md) #

---

# [Logrotate data LOG/SQL/RRD](Logrotate.md) #
# [SQLite](SQLite.md) #
# [Alarm event](Alarm.md) #

---

# [Create graphical image from RRD database](RRDCreateImg.md) #
# [MUNIN integrate support](Munin.md) [(RU)](WMRMuninRU.md) #
# [CACTI integrate support](Cacti.md) [(RU)](WMRCactiRU.md) #
# [C-2000-CP1 controlling 4 line (RU)](C2000CP1controlling4LineRU.md) #
