#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl the gi version number
m4_define(gi_major_version, 0)
m4_define(gi_minor_version, 6)
m4_define(gi_micro_version, 14)
m4_define(gi_version, gi_major_version.gi_minor_version.gi_micro_version)

AC_PREREQ(2.59)
AC_INIT(gobject-introspection, gi_version,
        http://bugzilla.gnome.org/enter_bug.cgi?product=glib&component=introspection)
AM_INIT_AUTOMAKE([1.7 -Wno-portability])
AM_MAINTAINER_MODE

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],)

AC_CONFIG_HEADER([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Check for Win32
AC_CANONICAL_HOST
AC_MSG_CHECKING([for Win32])
case "$host" in
*-*-mingw*)
	os_win32=yes
	;;
*)
	os_win32=no
	;;
esac
AC_MSG_RESULT([$os_win32])
AM_CONDITIONAL(OS_WIN32, [test "$os_win32" = "yes"])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG

AC_PROG_LEX
if test "$LEX" = :; then
	AC_MSG_ERROR([flex not found but required])
fi

AC_CHECK_PROGS(YACC, 'bison -y', :)
if test "$YACC" = :; then
	AC_MSG_ERROR([bison not found but required])
fi


changequote(,)dnl
ensureflag() {
  flag="$1"; shift
  result="$@"

  case " ${result} " in
  *[\ \	]${flag}[\ \	]*) ;;
  *) result="${flag} ${result}" ;;
  esac

  echo ${result}
}
changequote([,])dnl

if test "$GCC" = "yes"; then
    for flag in -Wall -Wchar-subscripts -Wmissing-declarations \
        -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wcast-align \
        -Wsign-compare -fno-strict-aliasing;
    do
        CFLAGS="$(ensureflag $flag $CFLAGS)"
    done
fi

# Checks for libraries.
GI_ENABLE_GCOV

AC_CHECK_LIB([dl], [dlopen])

AC_MSG_CHECKING(for the suffix of shared libraries)
# libtool variables are immediately available since 2.0, prior to that we need
# to call libtool --config explicitly
if test "x$shrext_cmds" = x; then
    shrext_cmds=`SED=$SED ./libtool --config | grep '^shrext_cmds='`
    eval $shrext_cmds
fi
eval std_shrext=$shrext_cmds
# chop the initial dot
SHLIB_SUFFIX=${std_shrext#.}
AC_MSG_RESULT(.$SHLIB_SUFFIX)
# any reason it may fail?
if test "x$SHLIB_SUFFIX" = x; then
        AC_MSG_ERROR(Cannot determine shared library suffix from libtool)
fi
AC_DEFINE_UNQUOTED([SHLIB_SUFFIX], "$SHLIB_SUFFIX", [Define to the platform's shared library suffix])

# Copied from dbus configure.in
#### find the actual value for $prefix that we'll end up with
##   (I know this is broken and should be done in the Makefile, but
##    that's a major pain and almost nobody actually seems to care)
AS_AC_EXPAND(EXPANDED_LOCALSTATEDIR, "$localstatedir")
AS_AC_EXPAND(EXPANDED_SYSCONFDIR, "$sysconfdir")
AS_AC_EXPAND(EXPANDED_BINDIR, "$bindir")
AS_AC_EXPAND(EXPANDED_LIBDIR, "$libdir")
AS_AC_EXPAND(EXPANDED_LIBEXECDIR, "$libexecdir")
AS_AC_EXPAND(EXPANDED_DATADIR, "$datadir")

#### Directory to install the libexec binaries
GOBJECT_INTROSPECTION_LIBDIR="$EXPANDED_LIBDIR"
AC_SUBST(GOBJECT_INTROSPECTION_LIBDIR)
AC_DEFINE_UNQUOTED(GOBJECT_INTROSPECTION_LIBDIR,"$GOBJECT_INTROSPECTION_LIBDIR", [Directory prefix for typelib installation])

#### Directory to install the gir files
GIR_SUFFIX="gir-1.0"
AC_SUBST(GIR_SUFFIX)
AC_DEFINE_UNQUOTED(GIR_SUFFIX, "$GIR_SUFFIX", [Name of the gir directory])

GIR_DIR="$EXPANDED_DATADIR/$GIR_SUFFIX"
AC_SUBST(GIR_DIR)
AC_DEFINE_UNQUOTED(GIR_DIR, "$GIR_DIR", [Director prefix for gir installation])

PKG_CHECK_MODULES(GOBJECT, [gobject-2.0 gio-2.0])
PKG_CHECK_MODULES(GTHREAD, [gthread-2.0])
PKG_CHECK_MODULES(GIO_UNIX, [gio-unix-2.0], have_gio_unix=true, have_gio_unix=false)
AM_CONDITIONAL(HAVE_GIO_UNIX, test x$have_gio_unix = xtrue)

AC_ARG_ENABLE(tests,[  --disable-tests           disable test libraries ], enable_tests=$enableval,enable_tests=yes)
have_cairo=no
if test x$enable_tests != xno; then
  PKG_CHECK_MODULES(CAIRO, [cairo], have_cairo=yes, have_cairo=no)
  if test x$have_cairo != xyes; then
    AC_MSG_ERROR([Tests enabled but cairo not found; pass --disable-tests or install cairo])
  fi
fi
AM_CONDITIONAL(BUILD_TESTS, test x$enable_tests != xno)
AM_CONDITIONAL(HAVE_CAIRO, test x$have_cairo != xno)

PKG_CHECK_MODULES(SCANNER, [gobject-2.0 gthread-2.0 gio-2.0])

dnl libffi
PKG_CHECK_MODULES(FFI, libffi, have_ffi_pkgconfig=yes, have_ffi_pkgconfig=no)
FFI_PC_CFLAGS=""
FFI_PC_LIBS=""
FFI_PC_PACKAGES=""
if test x"$have_ffi_pkgconfig" = xyes ; then
    FFI_PC_PACKAGES="libffi"
else
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

  FFI_PC_LIBS=$FFI_LIBS
  FFI_PC_CFLAGS=$FFI_CFLAGS
  FFI_CFLAGS=
  AC_MSG_RESULT([$have_ffi_h])
  AC_SUBST(FFI_LIBS)
  AC_SUBST(FFI_CFLAGS)
fi
AC_SUBST(FFI_PC_CFLAGS)
AC_SUBST(FFI_PC_LIBS)
AC_SUBST(FFI_PC_PACKAGES)

AC_CHECK_SIZEOF(time_t, [], [#include <time.h>])

PKG_CHECK_MODULES(GIREPO, [glib-2.0 gobject-2.0 gmodule-2.0 gio-2.0])

# if we ever remove manual check for ffi and require .pc file, then 
# just put libffi in the PKG_CHECK_MODULES(GIREPO) deps
GIREPO_LIBS="$GIREPO_LIBS $GCOV_LIBS $FFI_LIBS"
GIREPO_CFLAGS="$GIREPO_CFLAGS $FFI_CFLAGS"

GIREPO_CFLAGS="$GIREPO_CFLAGS $GCOV_CFLAGS"

# gtk-doc
GTK_DOC_CHECK([1.12])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memchr strchr strspn strstr strtol strtoull])
AC_CHECK_FUNCS([backtrace backtrace_symbols])

# Python

AC_MSG_CHECKING([whether Python support is requested])

AM_PATH_PYTHON([2.5])
case "$host" in
*-*-mingw*)
	# Change backslashes to forward slashes in pyexecdir to avoid
	# quoting issues
	pyexecdir=`echo $pyexecdir | tr '\\\\' '/'`
	;;
esac
AM_CHECK_PYTHON_HEADERS(,AC_MSG_ERROR([Python headers not found]))

AC_CONFIG_FILES([
Makefile
gir/Makefile
girepository/Makefile
giscanner/Makefile
giscanner/config.py
m4/Makefile
tools/Makefile
tests/Makefile
tests/invoke/Makefile
tests/offsets/Makefile
tests/scanner/Makefile
tests/repository/Makefile
examples/Makefile
docs/Makefile
docs/reference/Makefile
gobject-introspection-1.0.pc
gobject-introspection-no-export-1.0.pc])
AC_OUTPUT
