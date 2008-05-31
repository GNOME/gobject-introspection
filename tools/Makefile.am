## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\"" \
	-I$(top_srcdir)/girepository \
	-I$(top_srcdir)/giscanner

EXTRA_DIST = g-ir-scanner

noinst_LTLIBRARIES = libgirepository-parser.la
noinst_PROGRAMS = g-idl-compiler g-idl-generate
bin_SCRIPTS = g-ir-scanner

libgirepository_parser_la_SOURCES =		\
	gidlmodule.c				\
	gidlmodule.h				\
	gidlnode.c				\
	gidlnode.h				\
	gidlparser.c				\
	gidlparser.h
libgirepository_parser_la_CFLAGS = $(GIREPO_CFLAGS)

g_idl_compiler_SOURCES = compiler.c	
g_idl_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_idl_compiler_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la libgirepository-parser.la

g_idl_generate_SOURCES = generate.c
g_idl_generate_CFLAGS = $(GIREPO_CFLAGS)
g_idl_generate_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

GCOVSOURCES =					\
	$(libgirepository_la_SOURCES)		\
	$(g_idl_compiler_SOURCES)		\
	$(g_idl_generate_SOURCES)

include $(top_srcdir)/gcov.mak
