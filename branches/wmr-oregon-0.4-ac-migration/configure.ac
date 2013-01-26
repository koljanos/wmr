#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([wmr-oregon], [0.4], [Den68 <idg68@yandex.ru>], [], [http://code.google.com/p/wmr/ http://www.nkl.ru/support/wmr/])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CANONICAL_SYSTEM # for cross-compile
AC_CONFIG_SRCDIR([src/wmr.c])
AC_CONFIG_HEADERS([build/config.h])
AM_INIT_AUTOMAKE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])
AC_SUBST(ACLOCAL_AMFLAGS, [\${ACLOCAL_FLAGS}])

# libtool init
AC_DISABLE_STATIC
LT_INIT([win32-dll])
#AC_PROG_LIBTOOL

# Checks for programs.
#AC_PROG_AWK
AC_PROG_CC
AC_PROG_INSTALL
#AC_PROG_LN_S

AC_LANG([C])

# Checks for libraries.
AC_CHECK_LIB([hid], [hid_init])
AC_CHECK_LIB([m], [sqrt])
#AC_CHECK_LIB([posix4], [main])
AC_CHECK_LIB([pthread], [pthread_join])
AC_CHECK_LIB([usb], [usb_init])

# Check for optional libraries.
AC_ARG_WITH([sqlite3],
	[AS_HELP_STRING([--without-sqlite3],
		[disable data logging to SQLite3 support])],
	[],
	[AS_IF([test "x$with_sqlite3" != xno],
		[AC_CHECK_LIB([sqlite3], [sqlite3_initialize])])]
)


# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/file.h sys/socket.h \
	sys/time.h syslog.h unistd.h hid.h libhid/hid.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_FORK
#AC_FUNC_MALLOC
AC_FUNC_MMAP
#AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero gettimeofday inet_ntoa memset munmap regcomp socket strncasecmp])

# Generate build version
AC_ARG_ENABLE([build-user],
	[AS_HELP_STRING([--enable-build-user=name],
		[specify the name of the builder [login name]])],
	[pkg_build_ver="$enable_build_user"],
	[pkg_build_ver="`id -un`"]
)
pkg_build_ver+=" ASCII"
[[ "${LIBS/*sqlite*/}" ]] || pkg_build_ver+="/SQL"
# temp
pkg_build_ver+="/RRD/SNMP"
[[ "${LIBS/*pthread*/}" ]] || pkg_build_ver+=" PTHREAD"
pkg_build_ver+=" "`date`
AC_DEFINE_UNQUOTED([PACKAGE_BUILD], ["$pkg_build_ver"], [Package build version and date])

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
AC_OUTPUT

echo "
  $PACKAGE_NAME version $PACKAGE_VERSION build $pkg_build_ver
  Prefix.........: $prefix
  Debug Build....: $debug
  C Compiler.....: $CC $CFLAGS $CPPFLAGS
  Linker.........: $LD $LDFLAGS $LIBS
"

