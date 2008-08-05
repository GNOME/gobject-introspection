## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\"" \
	-I$(top_srcdir)/girepository \
	-I$(top_srcdir)/giscanner

EXTRA_DIST = g-ir-scanner

noinst_LTLIBRARIES = libgirepository-parser.la
bin_PROGRAMS = g-ir-compiler g-ir-generate
bin_SCRIPTS = g-ir-scanner

libgirepository_parser_la_SOURCES =		\
	girmodule.c				\
	girmodule.h				\
	girnode.c				\
	girnode.h				\
	girparser.c				\
	girparser.h
libgirepository_parser_la_CFLAGS = $(GIREPO_CFLAGS)

g_ir_compiler_SOURCES = compiler.c	
g_ir_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_ir_compiler_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la libgirepository-parser.la

g_ir_generate_SOURCES = generate.c
g_ir_generate_CFLAGS = $(GIREPO_CFLAGS)
g_ir_generate_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

GCOVSOURCES =					\
	$(libgirepository_la_SOURCES)		\
	$(g_ir_compiler_SOURCES)		\
	$(g_ir_generate_SOURCES)

include $(top_srcdir)/gcov.mak
