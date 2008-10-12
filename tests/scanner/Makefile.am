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

if OS_WIN32
AM_LDFLAGS += -no-undefined
endif

GIRS =
SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la
TYPELIBS = $(GIRS:.gir=.typelib)
TXMLS = $(GIRS:.gir=.gir.txml)
CHECKGIRS = $(GIRS:.gir=.gir.check)
EXPECTEDGIRS = $(GIRS:.gir=-expected.gir)
CLEANFILES = $(TYPELIBS) $(TXMLS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(TXMLS) $(GIRS)
EXTRA_DIST = $(EXPECTEDGIRS)

annotation-1.0.gir: libannotation.la annotation.c annotation.h utility-1.0.gir $(SCANNER) $(SCANNER_LIBS) Makefile
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject-2.0.gir \
	--include=$(top_builddir)/tests/scanner/utility-1.0.gir \
	--library=annotation \
	--namespace=annotation \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/annotation.h $(srcdir)/annotation.c \
	 --output $@
GIRS += annotation-1.0.gir

drawable-1.0.gir: libdrawable.la drawable.c drawable.h utility-1.0.gir $(SCANNER) $(SCANNER_LIBS) Makefile
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject-2.0.gir \
	--include=$(top_builddir)/tests/scanner/utility-1.0.gir \
	--library=drawable \
	--namespace=drawable \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/drawable.h $(srcdir)/drawable.c \
	 --output $@
GIRS += drawable-1.0.gir

foo-1.0.gir: libfoo.la foo.c foo.h utility-1.0.gir $(SCANNER) $(SCANNER_LIBS) Makefile
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject-2.0.gir \
	--include=$(top_builddir)/tests/scanner/utility-1.0.gir \
	--library=foo \
	--namespace=foo \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/foo.h $(srcdir)/foo.c \
	 --output $@
GIRS += foo-1.0.gir

utility-1.0.gir: libutility.la utility.h $(SCANNER) $(SCANNER_LIBS) Makefile
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject-2.0.gir \
	--library=utility \
	--namespace=utility \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(libutility_la_SOURCES) \
	--output $@
GIRS += utility-1.0.gir

pre-check:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   cp -f $(top_srcdir)/giscanner/*.py $(top_builddir)/giscanner; \
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

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@
	$(SCANNER) --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml

check-local: pre-check
check-local: $(CHECKGIRS) $(TYPELIBS)
check-local: post-check
