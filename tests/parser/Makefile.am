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

CLEANFILES = utility.gidl Foo.gidl 
EXTRA_DIST = utility-expected.gidl Foo-expected.gidl 

utility.gidl: libutility.la utility.h $(top_builddir)/tools/g-idl-scanner
	G_DEBUG=fatal_warnings $(top_builddir)/tools/g-idl-scanner -v \
	--namespace=utility \
	$(libutility_la_SOURCES) -I$(srcdir) $(GOBJECT_CFLAGS) \
	libutility.la --output $@

Foo.gidl: libfoo.la foo-object.h $(top_builddir)/tools/g-idl-scanner
	G_DEBUG=fatal_warnings $(top_builddir)/tools/g-idl-scanner -v \
	--namespace=Foo \
	--include-idl=$(top_srcdir)/gidl/gobject-2.0.gidl \
	--include-idl=$(srcdir)/utility.gidl \
	$(libfoo_la_SOURCES) -I$(srcdir) $(GOBJECT_CFLAGS) \
	libfoo.la --output $@

check-local: utility.gidl Foo.gidl 
	@diff -u -U 10 $(srcdir)/utility-expected.gidl utility.gidl && echo "utility.gidl"
	@diff -u -U 10 $(srcdir)/Foo-expected.gidl Foo.gidl && echo "Foo.gidl"
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="

.PHONY: Foo.gidl
