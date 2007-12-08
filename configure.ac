#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gobject-introspection, 0.1, http://bugzilla.gnome.org/enter_bug.cgi?product=glib)
AM_INIT_AUTOMAKE([1.7])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/ginvoke.c])
AC_CONFIG_HEADER([config.h])

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
AC_CHECK_LIB([dl], [dlopen])

PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])

LIBFFI_DEP=""
AC_SUBST(LIBFFI_DEP)
PKG_CHECK_MODULES(GIREPO, [glib-2.0 gobject-2.0 gmodule-2.0 gthread-2.0 libffi],
                  [have_libffi=true], [have_libffi=false])

if $have_libffi; then
   AC_DEFINE(HAVE_LIBFFI,[],[Defined if libffi was found])
   LIBFFI_DEP=libffi
else
   dnl if libffi is not found, g_function_info_invoke is not available,
   dnl but everything else still works
   PKG_CHECK_MODULES(GIREPO, [glib-2.0 gobject-2.0 gmodule-2.0 gthread-2.0])
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memchr strchr strspn strstr strtol strtoull])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile
                 tests/invoke/Makefile
                 tests/parser/Makefile
                 gobject-introspection.pc])
AC_OUTPUT
