## Process this file with automake to produce Makefile.in

INCLUDES = -DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\""
BUILT_SOURCES = cparser.h
AM_YFLAGS = -d

noinst_LTLIBRARIES = libgirepository-parser.la
lib_LTLIBRARIES = libgirepository.la
bin_PROGRAMS = g-idl-compiler g-idl-generate g-idl-scanner

libgirepository_la_SOURCES =			\
	girepository.c				\
	gmetadata.c				\
	ginfo.c					\
	ginvoke.c
libgirepository_la_CFLAGS = $(GIREPO_CFLAGS)

libgirepository_parser_la_SOURCES =		\
	gidlmodule.c				\
	gidlnode.c				\
	gidlparser.c
libgirepository_parser_la_CFLAGS = $(GIREPO_CFLAGS)

g_idl_compiler_SOURCES = compiler.c	
g_idl_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_idl_compiler_LDADD = $(GIREPO_LIBS) libgirepository.la libgirepository-parser.la

g_idl_generate_SOURCES = generate.c
g_idl_generate_CFLAGS = $(GIREPO_CFLAGS)
g_idl_generate_LDADD = $(GIREPO_LIBS) libgirepository.la

g_idl_scanner_SOURCES =				\
	clexer.l				\
	cparser.y				\
	gen-introspect.c			\
	gen-introspect.h
g_idl_scanner_CFLAGS = $(GIREPO_CFLAGS) $(SCANNER_CFLAGS)
g_idl_scanner_LDADD = $(GIREPO_LIBS) $(SCANNER_LIBS) libgirepository.la libgirepository-parser.la

girepodir = $(includedir)/glib-2.0/gobject-introspection
girepo_HEADERS = girepository.h
