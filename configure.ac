#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gobject-introspection, 0.1, http://bugzilla.gnome.org/enter_bug.cgi?product=glib)
AM_INIT_AUTOMAKE([1.7])
AM_MAINTAINER_MODE
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
PKG_CHECK_MODULES(FFI, libffi, have_ffi_pkgconfig=yes, have_ffi_pkgconfig=no)

if test x"$have_ffi_pkgconfig" = xno ; then
  AC_MSG_CHECKING(for ffi.h)

  AC_TRY_CPP([#include <ffi.h>], have_ffi_h=yes, have_ffi_h=no)
  if test x"$have_ffi_h" = x"yes"; then

    save_LIBS=$LIBS
    if test x"$with_ffi" = x"yes" || test x"$with_ffi" = x"auto"; then
      other_LIBS=
    else
      other_LIBS=$with_ffi
    fi

    AC_SEARCH_LIBS(ffi_call,ffi,,AC_MSG_ERROR([libffi not found]),$other_LIBS)
    if test x"$ac_cv_search_ffi_call" = x"none required" ; then
      FFI_LIBS=$other_LIBS
    else
      FFI_LIBS="$ac_cv_search_ffi_call $other_LIBS"
    fi

    LIBS=$save_LIBS
  fi
  if test x"$have_ffi_h" != x"yes" ; then
    AC_MSG_ERROR([ffi.h not found])
  fi

  FFI_CFLAGS=

  AC_MSG_RESULT([$have_ffi_h])
  AC_SUBST(FFI_LIBS)
  AC_SUBST(FFI_CFLAGS)
fi

PKG_CHECK_MODULES(GIREPO, [glib-2.0 gobject-2.0 gmodule-2.0])

# if we ever remove manual check for ffi and require .pc file, then 
# just put libffi in the PKG_CHECK_MODULES(GIREPO) deps
GIREPO_LIBS="$GIREPO_LIBS $GCOV_LIBS $FFI_LIBS"
GIREPO_CFLAGS="$GIREPO_CFLAGS $FFI_CFLAGS"

GIREPO_CFLAGS="$GIREPO_CFLAGS $GCOV_CFLAGS"

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memchr strchr strspn strstr strtol strtoull])

# Python

AC_MSG_CHECKING([whether Python support is requested])

AM_PATH_PYTHON([2.5])
AM_CHECK_PYTHON_HEADERS

AC_CONFIG_FILES([Makefile
                 gidl/Makefile
                 girepository/Makefile
                 giscanner/Makefile
                 m4/Makefile
                 tools/Makefile
                 tests/Makefile
                 tests/invoke/Makefile
                 tests/parser/Makefile
                 gobject-introspection.pc])
AC_OUTPUT
