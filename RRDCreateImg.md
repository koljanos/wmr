# Create graphical image from RRD database #

---

Web & wmr graphical image file create in directory
defined from wmr.conf: GRAPHPATH, default directory
is /var/www, if other, edit this.

---

rrdtool use to create graphical image, this image needed
to php web interface, or visual view weather statistic.
Use /usr/bin/wmr\_create\_graph\_rrd.sh to create web graphical image.
```
 for every 10 minute create new image, insert cron job new line:
   0/10 0 * * * * /usr/bin/wmr_create_graph_rrd.sh
```

---

Example graphical file generate WMR:

---


![![](http://www.nkl.ru/support/wmr/oregon_img/a1-m.png)](http://www.nkl.ru/support/wmr/oregon_img/a1-l.png)

---

![![](http://www.nkl.ru/support/wmr/oregon_img/a2-m.png)](http://www.nkl.ru/support/wmr/oregon_img/a2-l.png)

---

![![](http://www.nkl.ru/support/wmr/oregon_img/a4-m.png)](http://www.nkl.ru/support/wmr/oregon_img/a4-l.png)

---

![![](http://www.nkl.ru/support/wmr/oregon_img/a6-m.png)](http://www.nkl.ru/support/wmr/oregon_img/a6-l.png)

---
