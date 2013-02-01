include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

INTROSPECTION_SCANNER_ARGS += --warn-all --warn-error -I.

check_LTLIBRARIES = \
	libdocexamples.la

AM_CFLAGS = $(GOBJECT_CFLAGS)
LIBS = $(GOBJECT_LIBS)

libdocexamples_la_SOURCES = $(srcdir)/doc-examples-obj.c $(srcdir)/doc-examples-obj.h

GIRS = 
TYPELIBS = $(GIRS:.gir=.typelib)
INTROSPECTION_GIRS = $(GIRS)
CHECK_TARGETS = $(GIRS:.gir=-C.page.check) $(GIRS:.gir=-Python.page.check) $(GIRS:.gir=-Gjs.page.check)
MALLARD_DIRS = $(GIRS:.gir=-C) $(GIRS:.gir=-Python) $(GIRS:.gir=-Gjs)
EXPECTED_MALLARD_DIRS = $(MALLARD_DIRS:=-expected)
CLEANFILES = $(TYPELIBS) $(GIRS)
BUILT_SOURCES = $(MALLARD_DIRS)
EXTRA_DIST = $(EXPECTED_MALLARD_DIRS)

DocExamples-1.0.gir: $(top_builddir)/Gio-2.0.gir libdocexamples.la
DocExamples_1_0_gir_LIBS = libdocexamples.la
DocExamples_1_0_gir_INCLUDES = cairo-1.0 Gio-2.0
DocExamples_1_0_gir_FILES = $(libdocexamples_la_SOURCES)
#DocExamples_1_0_gir_SCANNERFLAGS = --c-include="regress.h"
GIRS += DocExamples-1.0.gir

%-C: %.gir
	$(AM_V_GEN)
	$(AM_V_at)$(MKDIR_P) $*-C
	$(AM_V_at)rm -f $*-C/*.page
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) --language C $*.gir -o $*-C/

%-Python: %.gir
	$(AM_V_GEN)
	$(AM_V_at)$(MKDIR_P) $*-Python
	$(AM_V_at)rm -f $*-Python/*.page
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) --language Python $*.gir -o $*-Python/

%-Gjs: %.gir
	$(AM_V_GEN)
	$(AM_V_at)$(MKDIR_P) $*-Gjs
	$(AM_V_at)rm -f $*-Gjs/*.page
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) --language Gjs $*.gir -o $*-Gjs/

%-C.page.check: %-C
	@diff -u -w -B -U 10 $(srcdir)/$*-C-expected $*-C && echo "  TEST  $*-C"

%-Python.page.check: %-Python
	@diff -u -w -B -U 10 $(srcdir)/$*-Python-expected $*-Python && echo "  TEST  $*-Python"

%-Gjs.page.check: %-Gjs
	@diff -u -w -B -U 10 $(srcdir)/$*-Gjs-expected $*-Gjs && echo "  TEST  $*-Gjs"

check-local: $(CHECK_TARGETS) $(TYPELIBS)
clean-local:
	@rm -rf $(MALLARD_DIRS)
