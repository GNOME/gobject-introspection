## this one is commonly used with AM_PATH_PYTHONDIR ...
dnl a macro to check for ability to create python extensions
dnl  AM_CHECK_PYTHON_HEADERS([ACTION-IF-POSSIBLE], [ACTION-IF-NOT-POSSIBLE])
dnl function also defines PYTHON_INCLUDES
AC_DEFUN([AM_CHECK_PYTHON_HEADERS],
[AC_REQUIRE([AM_PATH_PYTHON])
AC_MSG_CHECKING(for headers required to compile python extensions)
dnl deduce PYTHON_INCLUDES
py_prefix=`$PYTHON -c "import sys; print sys.prefix"`
py_exec_prefix=`$PYTHON -c "import sys; print sys.exec_prefix"`
if test "x$PYTHON_INCLUDES" == x; then
  PYTHON_INCLUDES="-I${py_prefix}/include/python${PYTHON_VERSION}"
  if test "$py_prefix" != "$py_exec_prefix"; then
    PYTHON_INCLUDES="$PYTHON_INCLUDES -I${py_exec_prefix}/include/python${PYTHON_VERSION}"
  fi
fi
AC_SUBST(PYTHON_INCLUDES)
dnl check if the headers exist:
save_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $PYTHON_INCLUDES"
AC_TRY_CPP([#include <Python.h>],dnl
[AC_MSG_RESULT(found)
$1],dnl
[AC_MSG_RESULT(not found)
$2])
CPPFLAGS="$save_CPPFLAGS"
])

dnl a macro to check for ability to link against libpython
dnl  AM_CHECK_PYTHON_LIBS([ACTION-IF-POSSIBLE], [ACTION-IF-NOT-POSSIBLE])
dnl function also defines PYTHON_LIBS
AC_DEFUN([AM_CHECK_PYTHON_LIBS],
[AC_REQUIRE([AM_CHECK_PYTHON_HEADERS])
AC_MSG_CHECKING(for libraries required to link against libpython)
dnl deduce PYTHON_LIBS
if test "x$PYTHON_LIBS" == x; then
	PYTHON_LIBS="-L${py_prefix}/lib -lpython${PYTHON_VERSION}"
fi
if test "x$PYTHON_LIB_LOC" == x; then
	PYTHON_LIB_LOC="${py_prefix}/lib"
fi
AC_SUBST(PYTHON_LIBS)
AC_SUBST(PYTHON_LIB_LOC)
dnl check if libpython exist:
save_LIBS="$LIBS"
LIBS="$LIBS $PYTHON_LIBS"
AC_TRY_LINK_FUNC(Py_Initialize, dnl
         [LIBS="$save_LIBS"; AC_MSG_RESULT(found); $1], dnl
         [LIBS="$save_LIBS"; AC_MSG_RESULT(not found); $2])

])
