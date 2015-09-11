# Compile - WMR logger for Oregon Scientific USB protocol #

---


# Depended libs required: #

---

```

   - libhid (needed to install) http://libhid.alioth.debian.org/"
   - libusb (needed to install) http://www.libusb.org/"
   - libsqlite3 (needed to install)  http://www.sqlite.org/download.html"
```

# Compile: #

---


Enable full debug option, compile width added key -DDEBUG
Enable language support: LANG\_RU LANG\_EN
```
Run ./configure and select you support code page, or
edit ./Makefile.inc, CFLAGS +=  -DLANG_XXX_XXX -DDEBUG
```

Another method, create symlink to src/lang/lang\_ru.h
Before compile in langage support, please, select you
console code page and create symlink in directory src/lang/.
After edit ./Makefile.inc and change string -DLANG\_RU
Default symlink to file lang\_ru\_KOI8.h
```
example:
    rm -f src/lang/lang_ru.h
    ln -s src/lang/lang_ru_KOI8.h src/lang/lang_ru.h
    or:
    rm -f src/lang/lang_ru.h
    ln -s src/lang/lang_ru_UTF8.h src/lang/lang_ru.h
```
```
English code page support:
    - lang_en.h
```
```
Russian code page support:
    - CP1251: lang_ru_1251.h
    - CP866:  lang_ru_866.h
    - KOI8-R: lang_ru_KOI8.h
    - UTF-8:  lang_ru_UTF8.h
```
```
Other national language:
    - please, write and submit me...
      view to example: src/lang/lang_*
```
```
Run to compile shared library support:
    ./configure
    make
    make install
```
```
or run to compile singele file wmrd:
    ./configure
    make single
    make install-single
```


# Run: #

---

edit /etc/wmr/wmr.conf

```
run wmr-oregon:
    /usr/sbin/wmrd -c /etc/wmr/wmr.conf
```
```
or run wmr-oregon in daemon mode:
    /usr/sbin/wmrd -d -c /etc/wmr/wmr.conf
```


# ERROR question: #

---

if you have error on compile project, says:
```
"ld: errno: TLS definition in /lib64/libc.so.6 section .tbss
mismatches non-TLS reference in src/wmr_util.o
/lib64/libc.so.6: could not read symbols: Bad value
collect2: ld returned 1 exit status
make: *** [single] Error 1"
```

append flag -DGENTOO\_HACK to Makefile.inc
or run ./configure