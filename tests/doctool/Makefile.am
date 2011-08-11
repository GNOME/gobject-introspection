include $(top_srcdir)/common.mk

Regress-1.0.gir:
	cp ../scanner/Regress-1.0.gir .

GIRS = Regress-1.0.gir
CHECKXML = $(GIRS:.gir=.xml.check)
DOCBOOKFILES = $(GIRS:.gir=.xml)
EXPECTEDDOCBOOKFILES = $(DOCBOOKFILES:.xml=-expected.xml)
CLEANFILES = $(DOCBOOK_FILES)
BUILT_SOURCES = $(DOCBOOK_FILES)
EXTRA_DIST = $(EXPECTEDDOCBOOKFILES)

%.xml: %.gir
	@g-ir-doc-tool $*.gir -o $*.xml

%.xml.check: %.xml
	@diff -u -U 10 $(srcdir)/$*-expected.xml $*.xml && echo "  TEST  $*.xml"

check-local: $(CHECKXML) $(TYPELIBS)
