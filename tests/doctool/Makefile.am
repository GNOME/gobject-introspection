include $(top_srcdir)/common.mk

GIRepository-2.0.gir:
	cp ../../GIRepository-2.0.gir .

GIRS = GIRepository-2.0.gir
CHECKXML = $(GIRS:.gir=-C.xml.check) $(GIRS:.gir=-Python.xml.check)
DOCBOOKFILES = $(GIRS:.gir=-C.xml) $(GIRS:.gir=-Python.xml)
EXPECTEDDOCBOOKFILES = $(DOCBOOKFILES:.xml=-expected.xml)
CLEANFILES = $(DOCBOOK_FILES)
BUILT_SOURCES = $(DOCBOOK_FILES)
EXTRA_DIST = $(EXPECTEDDOCBOOKFILES)

%-C.xml: %.gir
	$(INTROSPECTION_DOCTOOL) --language C $*.gir -o $*-C.xml && echo "  GEN  $*-C.xml"

%-Python.xml: %.gir
	$(INTROSPECTION_DOCTOOL) --language Python $*.gir -o $*-Python.xml && echo "  GEN  $*-Python.xml"

%-C.xml.check: %-C.xml
	@diff -u -U 10 $(srcdir)/$*-C-expected.xml $*-C.xml && echo "  TEST  $*-C.xml"

%-Python.xml.check: %-Python.xml
	@diff -u -U 10 $(srcdir)/$*-Python-expected.xml $*-Python.xml && echo "  TEST  $*-Python.xml"

check-local: $(CHECKXML)
