testlib_LTLIBRARIES = libfoo.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed

libfoo_la_SOURCES = foo.c foo-object.h

libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

CLEANFILES = Foo.gidl
EXTRA_DIST = Foo-expected.gidl

SCANSOURCES = $(srcdir)/foo-object.h

Foo.gidl: libfoo.la foo-object.h $(top_builddir)/tools/g-idl-scanner
	G_DEBUG=fatal_warnings $(top_builddir)/tools/g-idl-scanner -v \
	--namespace=Foo \
	--include-idl=$(top_srcdir)/gidl/GLib.gidl \
	$(SCANSOURCES) -I$(srcdir) $(GOBJECT_CFLAGS) \
	libfoo.la --output $@

check-local: Foo.gidl
	@diff -u $(srcdir)/Foo-expected.gidl Foo.gidl && echo "Foo.gidl"
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="

.PHONY: Foo.gidl
