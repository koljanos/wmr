# Logrotate weather data file - WMR logger for Oregon Scientific USB protocol #

---

For logrotate data LOG/SQL/RRD file, copy contrib/wmr\_logrotate.sh
to /usr/bin/wmr\_logrotate.sh, or edit config file path to logrotae
script:
```
	wmr_logrotate.sh (default: /usr/bin/wmr_logrotate.sh).
```
Run - type: /usr/bin/wmr\_logrotate.sh -logrotate
or, insert cron job new line:

---

> for every day:
```
   0 0 * * * * /usr/bin/wmr_logrotate.sh -logrotate
```

> for every month:
```
   0 0 1 * * * /usr/bin/wmr_logrotate.sh -logrotate
```

> for every year:
```
   0 0 1 1 * * /usr/bin/wmr_logrotate.sh -logrotate
```