include $(top_srcdir)/common.mk

GIRepository-2.0.gir:
	cp ../../GIRepository-2.0.gir .

GIRS = GIRepository-2.0.gir
CHECKXML = $(GIRS:.gir=-C.page.check) $(GIRS:.gir=-Python.page.check)
MALLARDFILES = $(GIRS:.gir=-C.page) $(GIRS:.gir=-Python.page)
EXPECTEDMALLARDFILES = $(MALLARDFILES:.page=-expected.page)
CLEANFILES = $(MALLARD_FILES)
BUILT_SOURCES = $(MALLARD_FILES)
EXTRA_DIST = $(EXPECTEDMALLARDFILES)

%-C.page: %.gir
	$(INTROSPECTION_DOCTOOL) --language C --format mallard $*.gir -o $*-C.page && echo "  GEN  $*-C.page"

%-Python.page: %.gir
	$(INTROSPECTION_DOCTOOL) --language Python --format mallard $*.gir -o $*-Python.page && echo "  GEN  $*-Python.page"

%-C.page.check: %-C.page
	@diff -u -U 10 $(srcdir)/$*-C-expected.page $*-C.page && echo "  TEST  $*-C.page"

%-Python.page.check: %-Python.page
	@diff -u -U 10 $(srcdir)/$*-Python-expected.page $*-Python.page && echo "  TEST  $*-Python.page"

check-local: $(CHECKXML)
