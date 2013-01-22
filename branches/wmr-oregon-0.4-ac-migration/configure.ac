#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([wmr-oregon], [0.4], [idg68@yandex.ru], [], [http://code.google.com/p/wmr/])
AC_CANONICAL_SYSTEM # for cross-compile
AC_CONFIG_SRCDIR([src/wmr.c])
AC_CONFIG_HEADERS([config.h])

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
		[disable support data logging to SQLite3])],
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
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero gettimeofday inet_ntoa memset munmap regcomp socket strncasecmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo "
  $PACKAGE_NAME version $PACKAGE_VERSION
  Prefix.........: $prefix
  Debug Build....: $debug
  C Compiler.....: $CC $CFLAGS $CPPFLAGS
  Linker.........: $LD $LDFLAGS $LIBS
"

