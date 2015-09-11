# Зачем это? #

WMR-Oregon предназначен собирать данные с погодной станции и сохранять их для последующей выборки, обработки, визуализации и прогнозов.

# Особенности #

В отличии от немногочисленных "собратьев" работающих с погодными станциями Oregon Scientific под linux -  имеет преимущества:
```
- позволяет корректировать погрешность датчиков,
- позволяет сохранять данные в различных метрических стандартах,
- компактный (подходит для установки на роутерах), 
- умеет работать демоном, использовать syslog,
- данные пишет в различных форматах удобных для обработки. 
- для построения визуальных графиков использует rrd-tool.
- поддерживает события (alarm), при наступлении исполняет скрипт. 
```

http://www.nkl.ru/support/wmr/wmr-oregon-latest.tar.gz
[Подробнее про события (alarm)](C2000CP1controlling4LineRU.md)

Подходит для установки на роутеры, требует библиотек:
```
*libusb*, 
*libhid*, 
*libsqlite3*
*rrd-toots* (опционально)
```

Поддерживаемые форматы хранения данных:
```
*ASCII* - текстовой формат
*SQL* - использует sqlite3
*RRD* - необходим установленный пакет rrd-tools
```

На сайте есть готовая сборка под OpenWRT для RouteBoard 2xx (i386)
http://www.nkl.ru/support/wmr/wmr-oregon-OpenWrt_i386_bin.tar.gz
и сборка под SH4 платформу (OpenBox,SkayWay,Octagon etc)
http://www.nkl.ru/support/wmr/wmr-0.4.sh4.tar.gz

# Поддерживает железо #

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