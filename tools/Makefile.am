## Process this file with automake to produce Makefile.in

INCLUDES = -DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\""
BUILT_SOURCES = scannerparser.c scannerparser.h scannerlexer.c scannerlexer.h
CLEANFILES = scannerparser.c scannerparser.h scannerlexer.c scannerlexer.h
AM_YFLAGS = -d

# Why do I have to do this automake?
scannerlexer.h: scannerlexer.c

noinst_LTLIBRARIES = libgirepository-parser.la
bin_PROGRAMS = g-idl-compiler g-idl-generate g-idl-scanner

libgirepository_parser_la_SOURCES =		\
	gidlmodule.c				\
	gidlmodule.h				\
	gidlnode.c				\
	gidlnode.h				\
	gidlparser.c				\
	gidlparser.h
libgirepository_parser_la_CFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository

g_idl_compiler_SOURCES = compiler.c	
g_idl_compiler_CFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
g_idl_compiler_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la libgirepository-parser.la

g_idl_generate_SOURCES = generate.c
g_idl_generate_CFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
g_idl_generate_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

g_idl_scanner_SOURCES =				\
	scanner.c				\
	scanner.h				\
	scannerlexer.l				\
	scannerparser.y				\
	gidlwriter.c				\
	gidlwriter.h
g_idl_scanner_CFLAGS = $(GIREPO_CFLAGS) $(SCANNER_CFLAGS) -I$(top_srcdir)/girepository
g_idl_scanner_LDADD = $(GIREPO_LIBS) $(SCANNER_LIBS) $(top_builddir)/girepository/libgirepository.la libgirepository-parser.la
