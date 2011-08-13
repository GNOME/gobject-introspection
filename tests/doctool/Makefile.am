include $(top_srcdir)/common.mk

GIRepository-2.0.gir:
	cp ../../GIRepository-2.0.gir .

GIRS = GIRepository-2.0.gir
CHECKXML = $(GIRS:.gir=.xml.check)
DOCBOOKFILES = $(GIRS:.gir=.xml)
EXPECTEDDOCBOOKFILES = $(DOCBOOKFILES:.xml=-expected.xml)
CLEANFILES = $(DOCBOOK_FILES)
BUILT_SOURCES = $(DOCBOOK_FILES)
EXTRA_DIST = $(EXPECTEDDOCBOOKFILES)

%.xml: %.gir
	$(INTROSPECTION_DOCTOOL) $*.gir -o $*.xml && echo "  GEN  $*.xml"

%.xml.check: %.xml
	@diff -u -U 10 $(srcdir)/$*-expected.xml $*.xml && echo "  TEST  $*.xml"

check-local: $(CHECKXML) $(TYPELIBS)
