# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = libfoo.la libutility.la
testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo-object.h
libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libutility_la_CFLAGS = $(GOBJECT_CFLAGS)
libutility_la_LDFLAGS = -module -avoid-version
libutility_la_LIBADD = $(GOBJECT_LIBS)

CLEANFILES = utility.gir Foo.gir 
EXTRA_DIST = utility-expected.gir Foo-expected.gir 

SCANNER = $(top_srcdir)/tools/g-ir-scanner

utility.gir: libutility.la utility.h $(SCANNER)
	@PYTHONPATH=$(top_builddir) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/gobject-2.0.gir \
	--library=libutility.la \
	--namespace=utility \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) \
	--output $@

Foo.gir: libfoo.la foo-object.h $(SCANNER)
	@PYTHONPATH=$(top_builddir) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/gobject-2.0.gir \
	--include=$(top_builddir)/tests/parser/utility.gir \
	--library=libfoo.la \
	--namespace=Foo \
	--pkg gobject-2.0 \
	$(libfoo_la_SOURCES) \
	 --output $@

check-%.gir: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "* $*.gir"

pre-check:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   cp $(top_srcdir)/giscanner/*.py $(top_builddir)/giscanner; \
	fi
	@echo "Running parser checks..."

check-local: pre-check check-utility.gir check-Foo.gir 
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   rm -f $(top_builddir)/giscanner/*.py*; \
	fi

.PHONY: utility.gir Foo.gir 
