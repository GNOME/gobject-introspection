## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_srcdir)/girepository
BUILT_SOURCES = 		\
	glibconfig-scanner.h	\
	scannerparser.c		\
	scannerparser.h 	\
	scannerlexer.c 		\
	scannerlexer.h

CLEANFILES = 		\
	glibconfig-scanner.h	\
	scannerparser.c		\
	scannerparser.h 	\
	scannerlexer.c 		\
	scannerlexer.h
AM_YFLAGS = -d -t

# Why do I have to do this automake?
scannerlexer.h: scannerlexer.c

noinst_LTLIBRARIES = libgiscanner.la

libgiscanner_la_SOURCES = \
	sourcescanner.c				\
	sourcescanner.h				\
	scannerlexer.l				\
	scannerparser.y				\
	grealpath.h
libgiscanner_la_LIBADD = $(GOBJECT_LIBS)
libgiscanner_la_CFLAGS = $(GOBJECT_CFLAGS)

GCOVSOURCES = $(libgiscanner_la_SOURCES)

# Python module
pkgpyexecdir = $(pyexecdir)/giscanner
pkgpyexec_LTLIBRARIES = _giscanner.la
pkgpyexec_PYTHON = 		\
	__init__.py		\
	ast.py			\
	cgobject.py		\
	gidlparser.py		\
	gidlwriter.py		\
	girparser.py		\
	girwriter.py		\
	glibast.py		\
	glibtransformer.py 	\
	odict.py		\
	sourcescanner.py	\
	transformer.py		\
	utils.py		\
	xmlwriter.py

_giscanner_la_CFLAGS = \
	$(PYTHON_INCLUDES) \
	$(GOBJECT_CFLAGS) \
	-I$(top_srcdir)/giscanner
_giscanner_la_LIBADD = $(GOBJECT_LIBS) libgiscanner.la
_giscanner_la_LDFLAGS = \
	-module -avoid-version -export-symbols-regex init_giscanner
_giscanner_la_SOURCES = giscannermodule.c

BUILT_SOURCES += _giscanner.so
CLEANFILES += _giscanner.so

# Yuck, ugly but...
_giscanner.so: _giscanner.la
	ln -sf .libs/_giscanner.so .

GLIBCONFIG=`pkg-config --variable=libdir glib-2.0`/glib-2.0/include/glibconfig.h
glibconfig-scanner.h:
	cat $(GLIBCONFIG) \
	| sed s/__G_LIBCONFIG_H__/__G_LIBCONFIG_SCANNER_H__/g \
	| sed s/define\ G_HAVE_ISO_VARARGS\ 1/define\ G_HAVE_ISO_VARARGS\ 0/g \
	| sed s/define\ G_HAVE_GNUC_VARARGS\ 1/define\ G_HAVE_GNUC_VARARGS\ 0/g \
        > $(top_builddir)/giscanner/$@

gidir = $(includedir)/gobject-introspection-1.0/
gi_HEADERS = glibconfig-scanner.h

include $(top_srcdir)/gcov.mak
