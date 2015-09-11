# Install - WMR logger for Oregon Scientific USB protocol #

---

Before install or compile development library: libhid, libusb 0.x, libsqlite3
After, check path to development library in Makefile, and run make this project:

```
          make clean ; make all ; make install
```
or:
```
	  make single ; make install
```
this mode compile one binary wmrd, witchout dynamic linked library,
latter:
```
        vi /etc/wmr/wmr.conf
        lsmod | grep usbhid
        /usr/bin/wmrd -d -s -c /etc/wmr/wmr.conf
```

---

[See the Compile WMR page](Compile.md)