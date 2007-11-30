## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libgirepository.la
bin_PROGRAMS = g-idl-compiler g-idl-generate gen-introspect


libgirepository_la_SOURCES =			\
	girepository.c				\
	gmetadata.c				\
	ginfo.c					\
	ginvoke.c
libgirepository_la_CFLAGS = $(GIREPO_CFLAGS)


g_idl_compiler_SOURCES =			\
	gidlparser.c				\
	gidlmodule.c				\
	gidlnode.c				\
	gmetadata.c				\
	compiler.c	
g_idl_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_idl_compiler_LDADD = -ldl $(GIREPO_LIBS)


g_idl_generate_SOURCES = generate.c
g_idl_generate_CFLAGS = $(GIREPO_CFLAGS)
g_idl_generate_LDADD = -ldl $(GIREPO_LIBS) libgirepository.la

girepodir = $(includedir)/glib-2.0/gobject-introspection
girepo_HEADERS = girepository.h

BUILT_SOURCES = cparser.h
AM_YFLAGS = -d

gen_introspect_SOURCES =			\
	clexer.l				\
	cparser.y				\
	gidlmodule.c				\
	gidlnode.c				\
	gen-introspect.c			\
	gen-introspect.h
gen_introspect_CFLAGS = $(GIREPO_CFLAGS)
gen_introspect_LDADD = -ldl $(GIREPO_LIBS)

