include $(top_srcdir)/common.mk

GIRS = GIRepository-2.0.gir
CHECK_TARGETS = $(GIRS:.gir=-C.page.check) $(GIRS:.gir=-Python.page.check)
MALLARD_DIRS = $(GIRS:.gir=-C) $(GIRS:.gir=-Python)
EXPECTED_MALLARD_DIRS = $(MALLARD_DIRS:=-expected)
CLEANFILES = $(GIRS)
BUILT_SOURCES = $(MALLARD_DIRS)
EXTRA_DIST = $(EXPECTED_MALLARD_DIRS)

%.gir:
	cp ../../$*.gir .

%-C: %.gir
	mkdir $*-C ; rm $*-C/*.page ; $(INTROSPECTION_DOCTOOL) --language C $*.gir -o $*-C/index.page && echo "  GEN  $*-C/index.page"

%-Python: %.gir
	mkdir $*-Python ; rm $*-Python/*.page ; $(INTROSPECTION_DOCTOOL) --language Python $*.gir -o $*-Python/index.page && echo "  GEN  $*-Python/index.page"

%-C.page.check: %-C
	@diff -u -U 10 $(srcdir)/$*-C-expected $*-C && echo "  TEST  $*-C" && rm -rf $*-C

%-Python.page.check: %-Python
	@diff -u -U 10 $(srcdir)/$*-Python-expected $*-Python && echo "  TEST  $*-Python" && rm -rf $*-Python

check-local: $(CHECK_TARGETS)

clean-local:
	@rm -rf $(MALLARD_DIRS)
