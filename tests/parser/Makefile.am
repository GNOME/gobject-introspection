testlib_LTLIBRARIES = libfoo.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed

libfoo_la_SOURCES = foo.c

libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

BUILT_SOURCES = Foo.gidl
CLEANFILES = Foo.gidl

SCAN_SOURCES = foo-object.h

Foo.gidl: libfoo.la foo-object.h $(top_builddir)/src/g-idl-scanner
	G_DEBUG=fatal_warnings $(top_builddir)/src/g-idl-scanner -v --namespace=Foo \
	--include-idl=$(top_srcdir)/gidl/GLib.gidl \
	$(SCAN_SOURCES) -I. $(GOBJECT_CFLAGS) \
	libfoo.la --output $@

check-local:
	@diff -u Foo-expected.gidl Foo.gidl && echo "Foo.gidl"
	@echo "======================="
	@echo "All parser tests passed"
	@echo "======================="

.PHONY: Foo.gidl
