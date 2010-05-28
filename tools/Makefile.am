INCLUDES = \
	-DGIREPO_DEFAULT_SEARCH_PATH="\"$(libdir)\"" \
	-I$(top_srcdir)/girepository

bin_PROGRAMS = g-ir-compiler g-ir-generate
bin_SCRIPTS = g-ir-scanner
EXTRA_DIST = g-ir-scanner.in

g-ir-scanner: g-ir-scanner.in Makefile
	$(AM_V_GEN) sed -e s,@libdir\@,$(libdir), -e s,@PYTHON\@,$(PYTHON), $< > $@.tmp && mv $@.tmp $@
	@chmod a+x $@

g_ir_compiler_SOURCES = compiler.c	
g_ir_compiler_CFLAGS = $(GIREPO_CFLAGS)
g_ir_compiler_LDADD = \
	$(top_builddir)/girepository/libgirepository-parser.la \
	$(top_builddir)/girepository/libgirepository-1.0.la \
	$(GIREPO_LIBS)

g_ir_generate_SOURCES = generate.c
g_ir_generate_CFLAGS = $(GIREPO_CFLAGS)
g_ir_generate_LDADD = \
	$(top_builddir)/girepository/libgirepository-1.0.la \
	$(GIREPO_LIBS)

GCOVSOURCES =					\
	$(g_ir_compiler_SOURCES)		\
	$(g_ir_generate_SOURCES)

CLEANFILES=g-ir-scanner
