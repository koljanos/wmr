#
# Ald
# Makefile.am for source dir
#

#SUBDIRS = rrdupdate

sbin_PROGRAMS = wmrd
wmrd_SOURCES = wmr_sql.c wmr.c wmr_rrdtool.c wmr_syslog.c wmr_util.c wmr_alarm.c \
	wmr_conf.c wmr_file.c wmr_sensor.c wmr_updexec.c \
	rrdupdate/rrd_generic.c rrdupdate/rrd_misc.c rrdupdate/rrd_update.c \
	snmp/oiddb.c snmp/snmp.c snmp/debug.c
#wmrd_SOURCES = *.c

wmrd_LDADD = $(LIBOBJS)

