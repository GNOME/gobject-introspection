CLEANFILES = 
EXTRA_DIST =

# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = 		\
	libannotation.la 	\
	libdrawable.la 		\
	libfoo.la 		\
	libutility.la
testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

libannotation_la_SOURCES = $(srcdir)/annotation.c $(srcdir)/annotation.h
libannotation_la_CFLAGS = $(GOBJECT_CFLAGS)
libannotation_la_LDFLAGS = -module -avoid-version
libannotation_la_LIBADD = $(GOBJECT_LIBS)

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

GIRS = utility.gir annotation.gir foo.gir
EXTRA_DIST += $(GIRS:.gir=-expected.gir)

SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la

annotation.gir: libannotation.la annotation.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GLib.gir \
	--include=$(top_srcdir)/gir/GObject.gir \
	--library=libannotation.la \
	--namespace=test \
	--pkg gobject-2.0 \
	$(libannotation_la_SOURCES) \
	 --output $@

drawable.gir: libdrawable.la drawable.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GLib.gir \
	--include=$(top_srcdir)/gir/GObject.gir \
	--library=libdrawable.la \
	--namespace=test \
	--pkg gobject-2.0 \
	$(libdrawable_la_SOURCES) \
	 --output $@

foo.gir: utility.gir libfoo.la foo.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GLib.gir \
	--include=$(top_srcdir)/gir/GObject.gir \
	--include=$(top_builddir)/tests/scanner/utility.gir \
	--library=libfoo.la \
	--namespace=foo \
	--pkg gobject-2.0 \
	$(libfoo_la_SOURCES) \
	 --output $@

utility.gir: libutility.la utility.h $(SCANNER) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GLib.gir \
	--include=$(top_srcdir)/gir/GObject.gir \
	--library=libutility.la \
	--namespace=utility \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) \
	--output $@

check-%.gir: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "* $*.gir"

%.typelib: %.gir
	$(top_builddir)/tools/g-ir-compiler $< --raw -o $@
	$(SCANNER) --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml

check-%.typelib: %.typelib


TYPELIBS = $(GIRS:.gir=.typelib)
CLEANFILES += $(TYPELIBS)

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

check-local: pre-check
check-local: check-utility.gir check-annotation.gir check-drawable.gir 
check-local: check-foo.gir
check-local: $(TYPELIBS)
check-local: post-check

.PHONY: annotation.gir drawable.gir foo.gir utility.gir 
