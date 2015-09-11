# MUNIN integrate WMR support #

---

Install WMR plugin for munin:
```
1. Check & edit path to wmr.conf in plugin from this direcory.
2. Place the plugin in the /etc/munin/plugins/ directory, and make it executable.
3. Restart munin
```

# MUNIN PLUGIN LIST: #

```
    * wmr_temp		- Temperature sensor (indoor / outdor), for more default 2 sensor,
                          include insert THGN801,THGR810 or other, edit plugin and add
                          new sensor graphic.  
    * wmr_humidity	- Humidity sensor (indoor / outdor), for more default 2 sensor,
                          include insert THGN801,THGR810 or other, edit plugin and add
                          new sensor graphic.
    * wmr_pressure	- Pressure sensor in main unit.
    * wmr_wind		- Wind sensor (WGR800)
    * wmr_rain		- Rain sensor (PCR800,RGR126) or other ...
    * wmr_uv		- UV sensor (UVN800)
    * wmr_water		- Water temperature sensor (THWR288)
```

See script/munin/README.**for more info.

---

[Download latest wmr-munin](http://www.nkl.ru/support/wmr/wmr-munin.tar.gz)**

[Munin - visualisation monitor](http://sourceforge.net/projects/munin/files/)