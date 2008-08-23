# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = \
	libannotation.la \
	libdrawable.la \
	libfoo.la \
	libutility.la
testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -module -avoid-version
LIBS = $(GOBJECT_LIBS)

libannotation_la_SOURCES = $(srcdir)/annotation.c $(srcdir)/annotation.h
libdrawable_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo.h
libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h

GIRS =
SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la
TYPELIBS = $(GIRS:.gir=.typelib)
TXMLS = $(GIRS:.gir=.gir.txml)
CHECKGIRS = $(GIRS:.gir=.gir.check)
CLEANFILES = $(TYPELIBS) $(TXMLS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(TXMLS) $(GIRS)

%.gir: lib%.la %.c %.h utility.gir $(SCANNER) $(SCANNER_LIBS) Makefile
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject.gir \
	--include=$(top_builddir)/tests/scanner/utility.gir \
	--library=$< \
	--namespace=$* \
	--pkg gobject-2.0 \
	$(srcdir)/$*.h $(srcdir)/$*.c \
	 --output $@
GIRS += annotation.gir
GIRS += drawable.gir
GIRS += foo.gir

utility.gir: libutility.la utility.h $(SCANNER) $(SCANNER_LIBS) Makefile
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject.gir \
	--library=$< \
	--namespace=utility \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) \
	--output $@
GIRS += utility.gir

pre-check:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   cp $(top_srcdir)/giscanner/*.py $(top_builddir)/giscanner; \
	fi
	@echo "Running scanner checks..."

post-check:
	@echo "========================"
	@echo "All scanner tests passed"
	@echo "========================"
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   rm -f $(top_builddir)/giscanner/*.py*; \
	fi

%.gir.check: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "* $*.gir"

%.typelib: %.gir
	$(top_builddir)/tools/g-ir-compiler $< -o $@
	$(SCANNER) --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml

check-local: pre-check
check-local: $(CHECKGIRS) $(TYPELIBS)
check-local: post-check
