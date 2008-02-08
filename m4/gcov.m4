AC_DEFUN([GI_ENABLE_GCOV],
[
  AC_ARG_ENABLE(gcov,
    AC_HELP_STRING([--enable-gcov],
      [compile with coverage profiling instrumentation (gcc only)]),
    enable_gcov=$enableval,
    enable_gcov=no)
  if test x$enable_gcov = xyes ; then
    if test "x$GCC" != "xyes"
    then
      AC_MSG_ERROR([gcov only works if gcc is used])
    fi

    AS_COMPILER_FLAG(["-fprofile-arcs"],
      [GCOV_CFLAGS="$GCOV_CFLAGS -fprofile-arcs"],
      true)
    AS_COMPILER_FLAG(["-ftest-coverage"],
      [GCOV_CFLAGS="$GCOV_CFLAGS -ftest-coverage"],
      true)
    dnl libtool 1.5.22 and lower strip -fprofile-arcs from the flags
    dnl passed to the linker, which is a bug; -fprofile-arcs implicitly
    dnl links in -lgcov, so we do it explicitly here for the same effect
    GCOV_LIBS=-lgcov
    AC_SUBST(GCOV_CFLAGS)
    AC_SUBST(GCOV_LIBS)
    GCOV=`echo $CC | sed s/gcc/gcov/g`
    AC_SUBST(GCOV)

    GI_GCOV_ENABLED=yes
    AC_DEFINE_UNQUOTED(GI_GCOV_ENABLED, 1,
      [Defined if gcov is enabled to force a rebuild due to config.h changing])
    dnl if gcov is used, we do not want default -O2 CFLAGS
    if test "x$GI_GCOV_ENABLED" = "xyes"
    then
      CFLAGS="-g -O0"
      AC_SUBST(CFLAGS)
      CXXFLAGS="-g -O0"
      AC_SUBST(CXXFLAGS)
      FFLAGS="-g -O0"
      AC_SUBST(FFLAGS)
      CCASFLAGS="-g -O0"
      AC_SUBST(CCASFLAGS)
      AC_MSG_NOTICE([gcov enabled, setting CFLAGS and friends to $CFLAGS])
    fi
  fi
  AM_CONDITIONAL(GI_GCOV_ENABLED, test x$enable_gcov = xyes)
])
