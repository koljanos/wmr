# Use - WMR logger for Oregon Scientific USB protocol #

---


To run:
```
	/usr/bin/wmrd -c /etc/wmr/wmr.conf
```

> flag -c /path/name.ext = path and name to config file [/etc/wmr/wmr.conf](WMRConfigFile.md),
> > default [/etc/wmr/wmr.conf](WMRConfigFile.md), or:

---


```
	/usr/bin/wmrd -l /tmp/wmr/lock
```


> flag -l 

&lt;value&gt;

 = path directory to lock file /tmp/wmr, name of lock file
> > generated automation, default: wmrd.lock
> > default: /var/lock
> > for get pid of runing programm, use:
> > cat /var/lock/wmrd.lock


---


```
	/usr/bin/wmrd -d -c /etc/wmr/wmr.conf
```


> flag -d = start is a daemon server mode. (loging only syslog)
> > flag -s automatic enable.


---


```
	/usr/bin/wmrd -s -c /etc/wmr/wmr.conf
```


> flag -s = print all info & debug info to local syslog server.


---


```
	/usr/bin/wmrd -v
```

> flag -v = print all config token from config file,
> > this options require flag -c <path/to/config/name.ext>
> > before.


---


```
	/usr/bin/wmrd -k
```


> flag -k = kill memory copy programm wmrd running in daemon mode.
> > Analog: kill -TERM `pidof wmrd`


---


To autostart:
```
	cp contrib/wmr.init /etc/rc.d/init.d/
	ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc3.d/S95wmr
	ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc5.d/S95wmr
```


---


To reread config file, send:
```
	kill -HUP `pidof wmrd
```


---


To reread config file and re init USB device, send:
```
	kill -USR1 `pidof wmrd`
```


---


To logrotate data file - log/sql/rrd, send:
```
	kill -USR2 `pidof wmrd`
```

> - run & see script/wmr\_logrotate.sh


---


To stop wmrd in daemon mode, send:
```
	kill -TERM `pidof wmrd`
	or:
	/usr/bin/wmrd -k
```


---


To update internet weather hosting, support:
```
	www.pwsweather.com, 
	www.pywws.com,
	www.wunderground.com 
```
> - see script/update\_weather/README, **.sh**


---


To generate Web graphical file from RRD database:
```
	for every 10 minute create new image, 
	insert cron job new line:

   0/10 0 * * * * /usr/bin/wmr_create_graph_rrd.sh

```


---
