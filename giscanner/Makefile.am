## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_srcdir)/girepository
BUILT_SOURCES = 		\
	scannerparser.c		\
	scannerparser.h 	\
	scannerlexer.c 		\
	scannerlexer.h

CLEANFILES = 		\
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

# Python module
pkgpyexecdir = $(pkglibdir)/giscanner
pkgpyexec_LTLIBRARIES = _giscanner.la
pkgpyexec_PYTHON = 		\
	__init__.py		\
	annotationparser.py	\
	ast.py			\
	cachestore.py		\
	config.py		\
	dumper.py		\
	girparser.py		\
	girwriter.py		\
	glibast.py		\
	glibtransformer.py 	\
	libtoolimporter.py	\
	minixpath.py		\
	odict.py		\
	shlibs.py		\
	scannermain.py		\
	sourcescanner.py	\
	transformer.py		\
	utils.py		\
	xmlwriter.py

_giscanner_la_CFLAGS = \
	$(PYTHON_INCLUDES) \
	$(GOBJECT_CFLAGS) \
	-I$(top_srcdir)/giscanner
_giscanner_la_LIBADD = libgiscanner.la $(GOBJECT_LIBS)

_giscanner_la_LDFLAGS = \
	-module -avoid-version -export-symbols-regex init_giscanner

if OS_WIN32
# Yuck. Probably there is a way to get this from Python, but I don't
# know how. Use -Wl to avoid libtool crack.
_giscanner_la_LDFLAGS += -Wl,$(pyexecdir)/../../libs/libpython25.a -no-undefined
endif

_giscanner_la_SOURCES = giscannermodule.c

if OS_WIN32
BUILT_SOURCES += _giscanner.pyd
CLEANFILES += _giscanner.pyd

_giscanner.pyd: _giscanner.la
	cp .libs/_giscanner.dll $@

install-exec-hook:
	mv $(pkgpyexecdir)/_giscanner.dll $(pkgpyexecdir)/_giscanner.pyd
	rm $(pkgpyexecdir)/_giscanner.dll.a
	rm $(pkgpyexecdir)/_giscanner.la
endif
