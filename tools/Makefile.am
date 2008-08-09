include $(top_srcdir)/gcov.mak

INCLUDES = \
	-DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\"" \
	-I$(top_srcdir)/girepository

bin_PROGRAMS = g-ir-compiler g-ir-generate
bin_SCRIPTS = g-ir-scanner

g_ir_compiler_SOURCES = compiler.c	
g_ir_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_ir_compiler_LDADD = \
	$(GIREPO_LIBS) \
	$(top_builddir)/girepository/libgirepository.la \
	$(top_builddir)/girepository/libgirepository-parser.la

g_ir_generate_SOURCES = generate.c
g_ir_generate_CFLAGS = $(GIREPO_CFLAGS)
g_ir_generate_LDADD = \
	$(GIREPO_LIBS) \
	$(top_builddir)/girepository/libgirepository.la

GCOVSOURCES =					\
	$(g_ir_compiler_SOURCES)		\
	$(g_ir_generate_SOURCES)
