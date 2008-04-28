testlib_LTLIBRARIES = libfoo.la libutility.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed

libfoo_la_SOURCES = foo.c foo-object.h
libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

libutility_la_SOURCES = utility.c utility.h
libutility_la_CFLAGS = $(GOBJECT_CFLAGS)
libutility_la_LDFLAGS = -module -avoid-version
libutility_la_LIBADD = $(GOBJECT_LIBS)

CLEANFILES = utility.gir Foo.gir 
EXTRA_DIST = utility-expected.gir Foo-expected.gir 

SCANNER = $(top_builddir)/tools/g-ir-scanner
utility.gir: libutility.la utility.h $(SCANNER)
	@PYTHONPATH=$(top_srcdir) $(SCANNER) -v \
	--include=$(top_srcdir)/gidl/gobject-2.0.gidl \
	--library=libutility.la \
	--namespace=utility \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) --output $@

Foo.gir: libfoo.la foo-object.h $(SCANNER)
	@PYTHONPATH=$(top_srcdir) $(SCANNER) -v \
	--include=$(top_srcdir)/gidl/gobject-2.0.gidl \
	--include=$(srcdir)/utility.gir \
	--namespace=Foo \
	--library=libfoo.la \
	--pkg gobject-2.0 \
	$(libfoo_la_SOURCES) \
	 --output $@

check-%.gir: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "* $*.gir"

pre-check:
	@echo "Running parser checks..."

check-local: pre-check check-utility.gir check-Foo.gir 
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="

.PHONY: utility.gir Foo.gir 
