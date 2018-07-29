#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl the gi version number
m4_define(gi_major_version, 1)
m4_define(gi_minor_version, 57)
m4_define(gi_micro_version, 2)
m4_define(gi_version, gi_major_version.gi_minor_version.gi_micro_version)

AC_PREREQ([2.63])
AC_INIT([gobject-introspection],
        [gi_version],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gobject-introspection],
        [gobject-introspection])

AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.11 tar-ustar dist-xz no-dist-gzip foreign -Wno-portability parallel-tests subdir-objects])
AM_MAINTAINER_MODE([enable])

AM_SILENT_RULES([yes])

# Used in docs/reference/version.xml
GI_VERSION=gi_version
AC_SUBST(GI_VERSION)

# Check for Win32
AC_CANONICAL_HOST
case "$host" in
*-*-mingw*)
	os_win32=yes
	;;
*)
	os_win32=no
	;;
esac
AM_CONDITIONAL(OS_WIN32, [test "x$os_win32" = "xyes"])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_MKDIR_P

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT

PKG_PROG_PKG_CONFIG

AC_PROG_LEX
if test "$LEX" = :; then
	AC_MSG_ERROR([flex not found but required])
fi

AC_CHECK_PROGS(YACC, 'bison -y', :)
if test "$YACC" = :; then
	AC_MSG_ERROR([bison not found but required])
fi

# Default compiler warnings
m4_ifndef([AX_COMPILER_FLAGS], [AC_MSG_ERROR(['autoconf-archive' missing])])
AX_COMPILER_FLAGS(,, [yes])
# These get triggered a lot, not worth it imo, but feel free to fix them
AX_APPEND_COMPILE_FLAGS([-Wno-duplicated-branches -Wno-switch-enum])
# FIXME: Fix the warnings and remove the flags
AX_APPEND_COMPILE_FLAGS([-Wno-redundant-decls -Wno-switch-default -Wno-deprecated-declarations])

WARN_CFLAGS_PYTHON="$WARN_CFLAGS"
AX_APPEND_COMPILE_FLAGS([-Wno-discarded-qualifiers], [WARN_CFLAGS_PYTHON])
AC_SUBST(WARN_CFLAGS_PYTHON)

WARN_CFLAGS_FLEX="$WARN_CFLAGS"
AX_APPEND_COMPILE_FLAGS([-Wno-sign-compare], [WARN_CFLAGS_FLEX])
AC_SUBST(WARN_CFLAGS_FLEX)

# Checks for libraries.
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

PKG_CHECK_MODULES(GLIB, [glib-2.0 >= 2.57.2])

PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])
PKG_CHECK_MODULES(GMODULE, [gmodule-2.0])
PKG_CHECK_MODULES(GIO, [gio-2.0])
PKG_CHECK_MODULES(GIO_UNIX, [gio-unix-2.0], have_gio_unix=true, have_gio_unix=false)
AM_CONDITIONAL(HAVE_GIO_UNIX, test x$have_gio_unix = xtrue)

# Prefer cairo-gobject if we have it
AC_ARG_WITH(cairo,
	    AS_HELP_STRING([--with-cairo], [Use cairo @<:@default=maybe@:>@]),
	    [], [with_cairo=maybe])

AS_IF([test x${with_cairo} != xno], [
  PKG_CHECK_MODULES(CAIRO, [cairo cairo-gobject], have_cairo=yes, have_cairo=no)
  AS_IF([ test x$have_cairo = xno && test x$with_cairo = xyes ], [
    AC_MSG_ERROR([cairo enabled but not found])
  ])
])
AM_CONDITIONAL(HAVE_CAIRO, test x$have_cairo = xyes)

case "$host" in
  *-*-darwin*)
    CAIRO_SHARED_LIBRARY="libcairo-gobject.2.dylib"
    ;;
  *-*-mingw*)
    CAIRO_SHARED_LIBRARY="libcairo-gobject-2.dll"
    ;;
  *-*-openbsd*)
    CAIRO_SHARED_LIBRARY="libcairo-gobject.so"
    ;;
  *)
    CAIRO_SHARED_LIBRARY="libcairo-gobject.so.2"
    ;;
esac
CAIRO_GIR_PACKAGE="cairo-gobject"

AC_SUBST(CAIRO_SHARED_LIBRARY)
AC_SUBST(CAIRO_GIR_PACKAGE)


PKG_CHECK_MODULES(SCANNER, [gobject-2.0 gio-2.0])

dnl libffi
PKG_CHECK_MODULES(FFI, [libffi >= 3.0.0 ], have_ffi_pkgconfig=yes, have_ffi_pkgconfig=no)
FFI_PC_CFLAGS=""
FFI_PC_LIBS=""
FFI_PC_PACKAGES=""
if test x"$have_ffi_pkgconfig" = xyes ; then
    FFI_PC_PACKAGES="libffi"
else
  AC_MSG_CHECKING(for ffi.h)

  AC_PREPROC_IFELSE([AC_LANG_SOURCE([[#include <ffi.h>]])],
                    [have_ffi_h=yes],[have_ffi_h=no])
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

AC_CHECK_SIZEOF(char)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)

PKG_CHECK_MODULES(GIREPO, [glib-2.0 >= 2.24.0 gobject-2.0 gmodule-2.0 gio-2.0])

# if we ever remove manual check for ffi and require .pc file, then
# just put libffi in the PKG_CHECK_MODULES(GIREPO) deps
GIREPO_LIBS="$GIREPO_LIBS $GCOV_LIBS $FFI_LIBS"
GIREPO_CFLAGS="$GIREPO_CFLAGS $FFI_CFLAGS"

GIREPO_CFLAGS="$GIREPO_CFLAGS $GCOV_CFLAGS"

# gtk-doc
# gtkdocize greps for ^GTK_DOC_CHECK and parses it, so you need to have
# it on it's own line.
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.19], [--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC],[false])
])

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
# option to specify python interpreter to use; this just sets $PYTHON, so that
# we will fallback to reading $PYTHON if --with-python is not given, and
# python.m4 will get the expected input
AC_ARG_WITH(python,
  AS_HELP_STRING([--with-python=PATH],[Path to Python interpreter; searches $PATH if only a program name is given; if not given, searches for a few standard names such as "python3" or "python2"]),
  [PYTHON="$withval"], [])
if test x"$PYTHON" = xyes; then
    AC_MSG_ERROR([--with-python option requires a path or program argument])
fi
if test -n "$PYTHON" && ! which "$PYTHON"; then
    AC_MSG_ERROR([Python interpreter $PYTHON does not exist])
fi

AM_PATH_PYTHON([2.7])
case "$host" in
*-*-mingw*)
	# Change backslashes to forward slashes in pyexecdir to avoid
	# quoting issues
	pyexecdir=`echo $pyexecdir | tr '\\\\' '/'`
	;;
esac
AM_CHECK_PYTHON_HEADERS(, AC_MSG_ERROR([Python headers not found]))
if test "x$os_win32" = "xyes"; then
  AM_CHECK_PYTHON_LIBS(, AC_MSG_ERROR([Python libs not found. Windows requires Python modules to be explicitly linked to libpython.]))
fi

PYTHON_SO=`$PYTHON -c "import sysconfig, sys; get = sysconfig.get_config_var; sys.stdout.write(get('EXT_SUFFIX') or get('SO') or '.so');"`
AC_SUBST(PYTHON_SO)

dnl Not enabled by default until 3.6 cycle when we can propose mako as
dnl an external dependency
AC_ARG_ENABLE(doctool,[  --disable-doctool           disable g-ir-doc-tool ],,enable_doctool=auto)
AS_IF([ test x$enable_doctool != xno], [
   AM_CHECK_PYMOD(mako,,have_python_mako=yes,have_python_mako=no)
])
AS_IF([ test x$enable_doctool = xauto && test x$have_python_mako = xyes ],
      [ enable_doctool=yes ],
      [ test x$enable_doctool = xauto && test x$have_python_mako = xno ],
      [ enable_doctool=no ],
      [ test x$enable_doctool = xyes && test x$have_python_mako = xno ],
      [ AC_MSG_ERROR([Python mako module not found]) ])
AM_CONDITIONAL(BUILD_DOCTOOL, test x$enable_doctool != xno)

# Glib documentation

GLIBSRC=
AC_MSG_CHECKING([for glib source directory to use for documentation])

AC_ARG_WITH(glib-src,
	[  --with-glib-src=PATH    Source directory for glib - needed to add docs to gir],
	GLIBSRC=$withval
)
AM_CONDITIONAL(WITH_GLIBSRC, test x"$GLIBSRC" != x)
AC_SUBST(GLIBSRC)
AC_MSG_RESULT([$GLIBSRC])

dnl
dnl Check for -fvisibility=hidden to determine if we can do GNU-style
dnl visibility attributes for symbol export control
dnl
GI_HIDDEN_VISIBILITY_CFLAGS=""
case "$host" in
  *-*-mingw*)
    dnl on mingw32 we do -fvisibility=hidden and __declspec(dllexport)
    AC_DEFINE([_GI_EXTERN], [__attribute__((visibility("default"))) __declspec(dllexport) extern],
              [defines how to decorate public symbols while building])
    CFLAGS="${CFLAGS} -fvisibility=hidden"
    ;;
  *)
    dnl on other compilers, check if we can do -fvisibility=hidden
    SAVED_CFLAGS="${CFLAGS}"
    CFLAGS="-fvisibility=hidden"
    AC_MSG_CHECKING([for -fvisibility=hidden compiler flag])
    AC_TRY_COMPILE([], [return 0],
                   AC_MSG_RESULT(yes)
                   enable_fvisibility_hidden=yes,
                   AC_MSG_RESULT(no)
                   enable_fvisibility_hidden=no)
    CFLAGS="${SAVED_CFLAGS}"

    AS_IF([test "${enable_fvisibility_hidden}" = "yes"], [
      AC_DEFINE([_GI_EXTERN], [__attribute__((visibility("default"))) extern],
                [defines how to decorate public symbols while building])
      GI_HIDDEN_VISIBILITY_CFLAGS="-fvisibility=hidden"
    ])
    ;;
esac
AC_SUBST(GI_HIDDEN_VISIBILITY_CFLAGS)

dnl
dnl Check for -Bsymbolic-functions linker flag used to avoid
dnl intra-library PLT jumps, if available.
dnl
AC_ARG_ENABLE(Bsymbolic,
              [AS_HELP_STRING([--disable-Bsymbolic],
                              [avoid linking with -Bsymbolic])],,
              [SAVED_LDFLAGS="${LDFLAGS}"
               AC_MSG_CHECKING([for -Bsymbolic-functions linker flag])
               LDFLAGS=-Wl,-Bsymbolic-functions
               AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[return 0]])],
                              [AC_MSG_RESULT(yes)
                               enable_Bsymbolic=yes],
                              [AC_MSG_RESULT(no)
                               enable_Bsymbolic=no])
               LDFLAGS="${SAVED_LDFLAGS}"])

if test "x${enable_Bsymbolic}" = "xyes"; then
  EXTRA_LINK_FLAGS=-Wl,-Bsymbolic-functions
fi

AC_SUBST(EXTRA_LINK_FLAGS)

dnl
dnl Check whether MSVC toolset is explicitly set
dnl
AM_CONDITIONAL(MSVC_BASE_NO_TOOLSET_SET, [test x$MSVC_BASE_TOOLSET = x])
AM_CONDITIONAL(MSVC_NO_TOOLSET_SET, [test x$MSVC_TOOLSET = x])

AC_CONFIG_FILES([
Makefile
tests/Makefile
tests/offsets/Makefile
tests/scanner/Makefile
tests/scanner/annotationparser/Makefile
tests/repository/Makefile
tests/warn/Makefile
docs/Makefile
docs/reference/Makefile
docs/reference/version.xml
giscanner/_version.py
gobject-introspection-1.0.pc
gobject-introspection-no-export-1.0.pc])
AC_OUTPUT
