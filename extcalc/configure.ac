#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(extcalc, 0.5.0)
AM_INIT_AUTOMAKE(extcalc, 0.5.0)
AC_CONFIG_SRCDIR([src/extcalc.cpp])
AC_CONFIG_HEADER([config.h])



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h sys/time.h unistd.h])

# Checks for QT
AC_MSG_CHECKING([whether QTDIR environment variable is set])
if test "x$QTDIR" = "x"; then
  AC_MSG_RESULT([no])
  AC_MSG_CHECKING([the location of QT]) 
  for X in /usr/share/qt3 /usr/lib/qt3 /usr/local/lib/qt3 /usr/lib64/qt3 /usr/local/lib64/qt3 /usr/local/share/qt3 /usr/local/share/qt /usr/local/lib/qt /usr/lib/qt /usr/local/lib64/qt /usr/lib64/qt /usr/share/qt; do
    if test -e $X/include; then
      export QTDIR=$X
    fi
  done	
  if test "x$QTDIR" = "x"; then  
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([QT not found. QTDIR must be properly set.])
  else 
    AC_MSG_RESULT([$QTDIR]) 
  fi
else
  AC_MSG_RESULT([$QTDIR])
fi


for X in /usr/local/lib/ /usr/lib/ /usr/X11R6/lib/ $QTDIR $QTDIR/lib/ $QTDIR/lib64/ /usr/lib64/ /usr/X11R6/lib64/ /usr/local/lib64/ ; do
  if test -e $X; then
    LDFLAGS="$LDFLAGS -L$X"
  fi
done
echo $LDFLAGS

LDFLAGS="$LDFLAGS -lqt-mt -lXext -lXft -lX11 -lm -lpthread"


#LDFLAGS="$(LDFLAGS) -L/usr/local/lib -L/usr/lib/ -L/usr/X11R6/lib/ -L$(QTDIR)/lib/ -L$(QTDIR)/lib64/ -L/usr/lib64/ -L/usr/X11R6/lib64/ -lqt-mt -lXext -lXft -lX11 -lm -lpthread"

CFLAGS="$CFLAGS -I$QTDIR/include -I/usr/local/include -D_REENTRANT -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT"
CPPFLAGS="$CPPFLAGS -I$QTDIR/include -I/usr/local/include -D_REENTRANT -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT"
LIBS="-L$QTDIR/lib"
for X in qt qt3; do
  if test -d $QTDIR/include/$X; then
    CFLAGS="$CFLAGS -I$QTDIR/include/$X"
    CPPFLAGS="$CPPFLAGS -I$QTDIR/include/$X"
fi
done

dnl Checks for Qt library.

if test "x$ac_qtlib" = "x"; then
   AC_CHECK_LIB(qt-mt, main, [ac_qtlib=$X])
fi

if test "x$ac_qtlib" = "x"; then
  AC_MSG_ERROR([Qt library not found. Maybe QTDIR isn't properly set.])
fi
AC_SUBST(ac_qtlib)

AC_SUBST(ac_thread)

AC_CACHE_CHECK([for Qt library version >= 3.1.1],
  ac_qtlib_version, [
  AC_TRY_LINK([#include "qglobal.h"], [
#if QT_VERSION < 0x030101
#error Qt library 3.1.1 or greater required.
#endif
    ],
    ac_qtlib_version="yes", [
      echo "no; Qt 3.1.1 or greater is required"
      exit
    ])
])

#Long double check
AC_CHECK_DECL(atanhl,
  [AC_CHECK_LIB(m,atanhl,,[CFLAGS="$CFLAGS -DNO_LONG_DOUBLE"] [CPPFLAGS="$CPPFLAGS -DNO_LONG_DOUBLE"])], [CPPFLAGS="$CPPFLAGS -DNO_LONG_DOUBLE"],[#include <math.h>])




# Checks for OpenGL
AC_CHECK_LIB(GL, glBegin,, AC_MSG_ERROR(Extcalc requires OpenGL))
LDFLAGS="$LDFLAGS -lGL -lGLU"

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([gettimeofday mkdir pow])


# Installpath
CFLAGS="$CFLAGS -DINSTALLDIR=\"\\\"$datadir/extcalc\\\"\""
CPPFLAGS="$CPPFLAGS -DINSTALLDIR=\"\\\"$datadir/extcalc\\\"\""

# Language
AC_MSG_CHECKING([for chosen language])
AC_ARG_ENABLE(language_de,[Set the install-laguage],[CFLAGS="$CFLAGS -DLANGUAGE_DE"]
[CPPFLAGS="$CPPFLAGS -DLANGUAGE_DE"]
[AC_MSG_RESULT([german])]
,[CFLAGS="$CFLAGS -DLANGUAGE_EN"]
[CPPFLAGS="$CPPFLAGS -DLANGUAGE_EN"]
[AC_MSG_RESULT([english])])

AC_OUTPUT([Makefile src/Makefile doc/Makefile share/Makefile])
