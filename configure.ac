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
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])

PKG_CHECK_MODULES(GIREPO, glib-2.0 gobject-2.0 gmodule-2.0 libffi)


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
                 gobject-introspection.pc])
AC_OUTPUT
