include $(top_srcdir)/common.mk

GIRepository-2.0.gir:
	cp ../../GIRepository-2.0.gir .

GIRS = GIRepository-2.0.gir
CHECK_TARGETS = $(GIRS:.gir=-C.page.check) $(GIRS:.gir=-Python.page.check)
MALLARD_DIRS = $(GIRS:.gir=-C) $(GIRS:.gir=-Python)
EXPECTED_MALLARD_DIRS = $(MALLARD_DIRS:=-expected)
CLEANFILES = $(MALLARD_DIRS)
BUILT_SOURCES = $(MALLARD_DIRS)
EXTRA_DIST = $(EXPECTED_MALLARD_DIRS)

%-C: %.gir
	mkdir $*-C && $(INTROSPECTION_DOCTOOL) --language C --format mallard $*.gir -o $*-C/index.page && echo "  GEN  $*-C/index.page"

%-Python: %.gir
	mkdir $*-Python && $(INTROSPECTION_DOCTOOL) --language Python --format mallard $*.gir -o $*-Python/index.page && echo "  GEN  $*-Python/index.page"

%-C.page.check: %-C
	@diff -u -U 10 $(srcdir)/$*-C-expected $*-C && echo "  TEST  $*-C"

%-Python.page.check: %-Python
	@diff -u -U 10 $(srcdir)/$*-Python-expected $*-Python && echo "  TEST  $*-Python"

check-local: $(CHECK_TARGETS)
