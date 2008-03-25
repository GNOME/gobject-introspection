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

include $(top_srcdir)/gcov.mak
