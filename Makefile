#
#
COMPILE = i686

VERSION = 0.4

MAKEFLAGS	= --no-print-directory
## MAKEFLAGS	+= --version --print-data-base

ifeq ($(COMPILE),sh4)
##
## for sh4 (octagon,Openbox,SkyWay, e.t.c.) toolchain
##
DDD = compile for sh4 toolchain
PLATFORM = ST
TOOLCHAINPATH = /var/INSTALL/toolchain/sh4
TOOLCHAINSYS = ${COMPILE}
PLATFORM = sh4-octagon-
BINNAME = sh4-linux-
CROSS_COMPILE = ${TOOLCHAINPATH}/bin/${BINNAME}
LIBPATHL = -Wl,-rpath,/var/lib/wmr -L.
#
CC	= ${TOOLCHAINPATH}/bin/${BINNAME}gcc
CPP	= ${TOOLCHAINPATH}/bin/${BINNAME}cpp
ARCH	= ${TOOLCHAINPATH}/bin/${BINNAME}ar
LD	= ${TOOLCHAINPATH}/bin/${BINNAME}ld
CFLAGS	= -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include -I${TOOLCHAINPATH}/target/usr/include
CFLAGS	+= -std=gnu99 -Wall -O2 -D_GNU_SOURCE
LIBS	= -L/usr/local/lib/${TOOLCHAINSYS} -L${TOOLCHAINPATH}/lib -L${TOOLCHAINPATH}/target/usr/lib
LDFLAGS	= -lusb -lhid -lsqlite3 -lpthread -lm
CPPFLAGS = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include -I${TOOLCHAINPATH}/target/usr/include
endif

ifeq ($(COMPILE),i386)
##
## for i386 OpenWRT toolchain
##
DDD = compile for i386 OpenWRT toolchain
TOOLCHAINPATH=/var/INSTALL/toolchain/openwrt/staging_dir/toolchain-i386_gcc4.1.2
TOOLCHAINSYS=${COMPILE}
PLATFORM = i386-openwrt-
BINNAME = i386-linux-uclibc-
CROSS_COMPILE = ${TOOLCHAINPATH}/bin/${BINNAME}
LIBPATHL = -Wl,-rpath,/usr/lib/wmr -L.
#
CC      = ${TOOLCHAINPATH}/bin/gcc
CPP	= ${TOOLCHAINPATH}/bin/${BINNAME}cpp
ARCH	= ${TOOLCHAINPATH}/bin/${BINNAME}ar
LD	= ${TOOLCHAINPATH}/bin/${BINNAME}ld
CFLAGS  = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include 
CFLAGS += -std=gnu99 -O2 -Wall -D_GNU_SOURCE
LIBS    = -L/usr/local/lib/${TOOLCHAINSYS} -L/usr/lib/wmr -L${TOOLCHAINPATH}/lib
LDFLAGS = -lusb -lhid -lsqlite3 -lpthread -lm
CPPFLAGS = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include -I${TOOLCHAINPATH}/target/usr/include
endif

ifeq ($(COMPILE),win32)
##
## for Win32 mingw
##
DDD = compile for Win32 mingw
TOOLCHAINPATH=/var/INSTALL/toolchain/mingw
TOOLCHAINSYS=win32
PLATFORM = i386-mingw32-
LIBPATHL = -Wl,-rpath,/usr/lib/wmr -L.
CC	= ${TOOLCHAINPATH}/bin/gcc
CFLAGS  = -I${TOOLCHAINPATH}/include -I/usr/local/lib/${TOOLCHAINSYS}/include
CFLAGS += -std=gnu99 -Wall -D_GNU_SOURCE
LIBS    = -L/usr/local/lib/${TOOLCHAINSYS} -L/usr/lib/wmr -L${TOOLCHAINPATH}/lib
LDFLAGS = -lusb -lhid -lsqlite3
CPPFLAGS = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include -I${TOOLCHAINPATH}/target/usr/include
endif

ifeq ($(COMPILE),i686)
##
## for i686 Linux
##
DDD = compile for i686 Linux
TOOLCHAINPATH=/usr
TOOLCHAINSYS=i686
PLATFORM = i686-linux-
LIBPATHL = -Wl,-rpath,/usr/lib/wmr -L.
CC      = gcc
LIBS	= -L/usr/local/lib/${TOOLCHAINSYS} -L/usr/lib
CFLAGS  = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include
CFLAGS	+= -std=gnu99 -Wall -O2 -D_GNU_SOURCE
LDFLAGS = -lusb -lhid -lsqlite3 -lpthread
CPPFLAGS = -I/usr/local/lib/${TOOLCHAINSYS}/_include_ -I${TOOLCHAINPATH}/include

include Makefile.inc

endif

ifeq ($(LANG),EN)
CFLAGS  += -DLANG_ENG
endif

ifeq ($(LANG),1251)
CFLAGS  += -DLANG_1251
endif

ifeq ($(LANG),866)
CFLAGS  += -DLANG_866
endif

ifeq ($(LANG),KOI8)
CFLAGS  += -DLANG_KOI8
endif

ifeq ($(LANG),UTF8)
CFLAGS  += -DLANG_UTF8
endif

PATH	:= ${TOOLCHAINPATH}/bin:/usr/local/lib/${TOOLCHAINSYS}/_bin_:$(PATH)

OBJS		=	src/wmr.o src/wmr_conf.o src/wmr_syslog.o src/wmr_util.o src/wmr_sensor.o
OBJSLIBRRD	=	src/wmr_rrdtool.o src/rrdupdate/rrd_update.o src/rrdupdate/rrd_misc.o src/rrdupdate/rrd_generic.o
OBJSLIBFILE	=	src/wmr_file.o 
OBJSLIBSQL	=	src/wmr_sql.o 
OBJSLIBALARM	=	src/wmr_alarm.o
OBJSLIBSNMP	=	src/snmp/oiddb.o src/snmp/snmp.o src/snmp/debug.o
OBJSLIBUPD	=	src/wmr_updexec.o
OBJSSHM		=	src/debug/shm.o


# -----------------------------------------------------------------------
# Sort out what operating system is being run and modify CFLAGS and LIBS
#
# If you add a new OSTYPE here please email it to me so that I can add
# it to the distribution in the next release
# -----------------------------------------------------------------------
SYSTYPE := $(shell uname -s)

ifeq ($(SYSTYPE), Linux)
  CFLAGS += -DLINUX
endif

ifeq ($(SYSTYPE), SunOS)
  CFLAGS += -DSOLARIS
  LIBS   += -lposix4
endif

ifeq ($(SYSTYPE), FreeBSD)
  CFLAGS += -DFREEBSD
endif

ifeq ($(SYSTYPE), AIX)
  CFLAGS += -DAIX
endif

# Build the Linux executable
all:		clean lib prog

lib:		libalarm librrd libsql libfile libsnmp libupd

libalarm:	$(OBJSLIBALARM)
		$(CC) -shared -fPIC $(OBJSLIBALARM) -o libwmr-alarm.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBALARM)

librrd:		$(OBJSLIBRRD)
		$(CC) -shared -fPIC $(OBJSLIBRRD) -o libwmr-rrd.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBRRD)

libsql:		$(OBJSLIBSQL)
		$(CC) -shared -fPIC $(OBJSLIBSQL) -o libwmr-sql.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBSQL)

libfile:	$(OBJSLIBFILE)
		$(CC) -shared -fPIC $(OBJSLIBFILE) -o libwmr-file.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBFILE)

libsnmp:	$(OBJSLIBSNMP)
		$(CC) -shared -fPIC $(OBJSLIBSNMP) -o libwmr-snmp.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBSNMP)

libupd:		$(OBJSLIBUPD)
		$(CC) -shared -fPIC $(OBJSLIBUPD) -o libwmr-upd.so $(LIBS) ${LDFLAGS} 2>_compile.log
		@rm -f $(OBJSLIBUPD)


prog:		$(OBJS)
		@echo '#define DATA_VERSION "'Den68 ASCII/SQL/RRD/SNMP - building: `date` '"' >src/wmr_build.h
		$(CC) -MMD $(OBJS) -o wmrd $(LIBS) ${LDFLAGS} ${LIBPATHL} -lwmr-alarm -lwmr-rrd -lwmr-sql -lwmr-file -lwmr-upd 2>_compile.log
		@rm -f $(OBJS)
		@echo "See comile log: _compile.log"
		@cat _compile.log
		@${TOOLCHAINPATH}/bin/strip wmrd
		@./goftp.sh

debug:		clean setdebug single

setdebug:	
                CFLAGS += -g -O0 -DDEBUG

static:         $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM)
		@echo '#define DATA_VERSION "'Den68 ASCII/SQL/RRD/SNMP - building: ${PLATFORM}`date` '"' >src/wmr_build.h
		$(CC) -MMD --static $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM) -o wmrd $(LIBS) ${LDFLAGS} ${LIBPATHL} 2>_compile.log
		@rm -f $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM)
		@echo "See comile log: _compile.log"
		@cat _compile.log
		@${TOOLCHAINPATH}/bin/strip wmrd
		@./goftp.sh

single:         $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM)
		@echo '#define DATA_VERSION "'Den68 ASCII/SQL/RRD/SNMP - building: ${PLATFORM}`date` '"' >src/wmr_build.h
		$(CC) -MMD $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM) -o wmrd $(LIBS) ${LDFLAGS} ${LIBPATHL} 2>_compile.log
		@rm -f $(OBJS) $(OBJSLIBUPD) $(OBJSLIBSNMP) $(OBJSLIBFILE) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM)
		@echo "See comile log: _compile.log"
		@cat _compile.log
		@${TOOLCHAINPATH}/bin/strip wmrd
		@./goftp.sh

shm:		$(OBJSSHM)
		$(CC) $(OBJSSHM) -o shm 2>_compile.log
		@rm -f $(OBJSSHM)

# Clean up the object files and the sub-directory for distributions
clean:
		@echo ${DDD}
		@rm -f *~
		@rm -f $(OBJS) $(OBJSLIBSNMP) $(OBJSLIBSQL) $(OBJSLIBRRD) $(OBJSLIBALARM) $(OBJSLIBFILE) ${OBJSLIBUPD} ${OBJSSHM}
		@rm -f core *.asc 
		@rm -rf wmrd
		@rm -rf *.so

help:
	@gcc -v
	@echo "  SYSTYPE = $(SYSTYPE)"
	@echo "  CFLAGS = $(CFLAGS)"
	@echo "  LIBS   = $(LIBS)"
	@echo ""
	@echo " "

# Install wmrd into /usr/sbin
install:	install-shared install-single

install-shared:
		@mkdir -p /usr/lib/wmr
		install -b -o root -g bin ./libwmr-alarm.so /usr/lib/wmr
		install -b -o root -g bin ./libwmr-file.so /usr/lib/wmr
		install -b -o root -g bin ./libwmr-rrd.so /usr/lib/wmr
		install -b -o root -g bin ./libwmr-snmp.so /usr/lib/wmr
		install -b -o root -g bin ./libwmr-sql.so /usr/lib/wmr
		install -b -o root -g bin ./libwmr-upd.so /usr/lib/wmr

install-single:
		install -b -o root -g bin wmrd /usr/sbin
		install -b -o root -g bin script/wmr_alarm.sh /usr/sbin
		install -b -o root -g bin script/wmr_sendms_sms.ru.sh /usr/sbin
		install -b -o root -g bin script/wmr_create_db_sqlite3.sh /usr/sbin
		install -b -o root -g bin script/wmr_create_db_rrd.sh /usr/sbin
		install -b -o root -g bin script/wmr_create_graph_rrd.sh /usr/sbin
		install -b -o root -g bin script/wmr_logrotate.sh /usr/sbin
		install -b -o root -g bin contrib/wmr.init /etc/rc.d/init.d
		ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc3.d/S95wmr
		ln -s /etc/rc.d/init.d/wmr.init /etc/rc.d/rc5.d/S95wmr
		@mkdir -P /etc/wmr
		install -b -o root -g bin contrib/wmr.conf /etc/wmr
		@mkdir -P /etc/wmr/script_alarm
		@mkdir -P /etc/wmr/script_update
		@mkdir -P /etc/wmr/script_graph
		@cp -f -R script/wmr_etc/etc/wmr/script_alarm /etc/wmr/script_alarm
		@cp -f -R script/wmr_etc/etc/wmr/script_graph /etc/wmr/script_graph
		@cp -f -R script/wmr_etc/etc/wmr/script_update /etc/wmr/script_update
		@mkdir -p /var/weather
		@script/wmr_create_db_sqlite3.sh
		@script/wmr_create_db_rrd.sh
		@echo "Enjoy! edit /etc/wmr/wmr.conf, attach USB weather station and run /usr/sbin/wmrd"

