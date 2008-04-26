## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_srcdir)/girepository
BUILT_SOURCES = scannerparser.c scannerparser.h scannerlexer.c scannerlexer.h

CLEANFILES = scannerparser.c scannerparser.h scannerlexer.c scannerlexer.h
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
	gidlast.py		\
	gidlparser.py		\
	gidlwriter.py		\
	girwriter.py		\
	glibtransformer.py 	\
	odict.py		\
	sourcescanner.py	\
	transformer.py		\
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


include $(top_srcdir)/gcov.mak
