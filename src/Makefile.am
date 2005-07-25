## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libgirepository.la
bin_PROGRAMS = g-idl-compiler g-idl-generate


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
