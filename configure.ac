AC_INIT([LibCachebusting], [0.1], [ingo.walz@googlemail.com], [cachebusting], [])
AC_PREREQ([2.61])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 foreign])
AC_LANG([C])
LT_INIT([disable-static])
AC_HEADER_STDC
AC_TYPE_SIZE_T

if test x"$DEJAGNU" = x
then
	DEJAGNU="\$(top_srcdir)/tests/global-conf.exp"
fi
AC_SUBST(DEJAGNU)

RUNTESTDEFAULTFLAGS="--tool \$\$tool"
AC_SUBST(RUNTESTDEFAULTFLAGS)

AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_LDFLAGS])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile tests/libcachebusting.tests/Makefile tests/lib/Makefile tests/config/Makefile])
AC_OUTPUT
