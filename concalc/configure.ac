#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT(concalc, 0.9.0)
AM_INIT_AUTOMAKE(concalc, 0.9.0)
AC_CONFIG_SRCDIR([src/concalc.cpp])
AC_CONFIG_HEADER([config.h])



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

#Long double check
AC_CHECK_DECL(atanhl,
  [AC_CHECK_LIB(m,atanhl,,[CFLAGS="$CFLAGS -DNO_LONG_DOUBLE"] [CPPFLAGS="$CPPFLAGS -DNO_LONG_DOUBLE"])], [CPPFLAGS="$CPPFLAGS -DNO_LONG_DOUBLE"],[#include <math.h>])


# Checks for library functions.
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([gettimeofday mkdir pow])

LDFLAGS="$LDFLAGS -lm"
AC_OUTPUT([Makefile src/Makefile man/Makefile])
