# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = libdrawable.la libfoo.la libutility.la
testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

libdrawable_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libdrawable_la_CFLAGS = $(GOBJECT_CFLAGS)
libdrawable_la_LDFLAGS = -module -avoid-version
libdrawable_la_LIBADD = $(GOBJECT_LIBS)

libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo.h
libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libutility_la_CFLAGS = $(GOBJECT_CFLAGS)
libutility_la_LDFLAGS = -module -avoid-version
libutility_la_LIBADD = $(GOBJECT_LIBS)

CLEANFILES = utility.gir foo.gir
EXTRA_DIST = utility-expected.gir foo-expected.gir

SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la

utility.gir: libutility.la utility.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/glib-2.0.gir \
	--include=$(top_srcdir)/gir/gobject-2.0.gir \
	--library=libutility.la \
	--namespace=utility \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) \
	--output $@

foo.gir: libfoo.la foo.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/glib-2.0.gir \
	--include=$(top_srcdir)/gir/gobject-2.0.gir \
	--include=$(top_builddir)/tests/scanner/utility.gir \
	--library=libfoo.la \
	--namespace=foo \
	--pkg gobject-2.0 \
	$(libfoo_la_SOURCES) \
	 --output $@

drawable.gir: libdrawable.la drawable.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/glib-2.0.gir \
	--include=$(top_srcdir)/gir/gobject-2.0.gir \
	--library=libdrawable.la \
	--namespace=test \
	--pkg gobject-2.0 \
	$(libdrawable_la_SOURCES) \
	 --output $@

check-%.gir: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "* $*.gir"

pre-check:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   cp $(top_srcdir)/giscanner/*.py $(top_builddir)/giscanner; \
	fi
	@echo "Running scanner checks..."

check-local: pre-check check-utility.gir check-drawable.gir check-foo.gir
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   rm -f $(top_builddir)/giscanner/*.py*; \
	fi

.PHONY: utility.gir drawable.gir foo.gir
