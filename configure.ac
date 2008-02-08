#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gobject-introspection, 0.1, http://bugzilla.gnome.org/enter_bug.cgi?product=glib)
AM_INIT_AUTOMAKE([1.7])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([girepository/ginvoke.c])
AC_CONFIG_HEADER([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG

AC_PROG_LEX
if test "$LEX" = :; then
	AC_MSG_ERROR([flex not found but required])
fi

AC_CHECK_PROGS(YACC, 'bison -y' byacc yacc, :)
if test "$YACC" = :; then
	AC_MSG_ERROR([bison not found but required])
fi

# Checks for libraries.
GI_ENABLE_GCOV

AC_CHECK_LIB([dl], [dlopen])

PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])

PKG_CHECK_MODULES(SCANNER, [gobject-2.0 gthread-2.0])

dnl libffi
AC_MSG_CHECKING(for ffi.h)
AC_ARG_WITH(libffi,
  AC_HELP_STRING([--without-ffi], [Disable libffi support]),
  with_ffi=$withval,
  with_ffi=auto)
if test x"$with_ffi" = xno ; then
  have_ffi_h=disabled
else
  AC_TRY_CPP([#include <ffi.h>], have_ffi_h=yes, have_ffi_h=no)
  if test $have_ffi_h = yes; then
    AC_DEFINE(HAVE_FFI_H,1,[Have ffi.h include file])
    save_LIBS=$LIBS
    if test x"$with_ffi" = xyes || test x"$with_ffi" = xauto; then
      other_LIBS=
    else
      other_LIBS=$with_ffi
    fi
    AC_SEARCH_LIBS(ffi_call,ffi,,AC_MSG_ERROR([libffi not found]),$other_LIBS)
    if test x$"ac_cv_search_ffi_call" = x"none required" ; then
      FFI_LIBS=$other_LIBS
    else
      FFI_LIBS="$ac_cv_search_ffi_call $other_LIBS"
    fi
    LIBS=$save_LIBS
  fi
fi
if test x"$with_ffi" != xauto && test x"$have_ffi_h" != xyes ; then
  AC_MSG_ERROR([libffi requested, but ffi.h not found])
fi
AC_MSG_RESULT([$have_ffi_h])
AM_CONDITIONAL(HAVE_LIBFFI, test "$have_ffi_h" = "yes")
AC_SUBST(FFI_LIBS)

dnl if libffi is not found, g_function_info_invoke is not available,
dnl but everything else still works

PKG_CHECK_MODULES(GIREPO, [glib-2.0 gobject-2.0 gmodule-2.0])

if test "$have_ffi_h" = "yes"; then
   GIREPO_LIBS="$GIREPO_LIBS $FFI_LIBS"
fi

GIREPO_CFLAGS="$GIREPO_CFLAGS $GCOV_CFLAGS"

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memchr strchr strspn strstr strtol strtoull])


AC_CONFIG_FILES([Makefile
                 gidl/Makefile
                 girepository/Makefile
                 m4/Makefile
                 tools/Makefile
                 tests/Makefile
                 tests/invoke/Makefile
                 tests/parser/Makefile
                 gobject-introspection.pc])
AC_OUTPUT
