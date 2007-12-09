testlib_LTLIBRARIES = libfoo.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed

libfoo_la_SOURCES = foo.c

libfoo_la_CFLAGS = $(GOBJECT_CFLAGS)
libfoo_la_LDFLAGS = -module -avoid-version
libfoo_la_LIBADD = $(GOBJECT_LIBS)

BUILT_SOURCES = Foo.gidl
CLEANFILES = Foo.gidl

Foo.gidl: libfoo.la foo-object.h $(top_builddir)/src/gen-introspect
	$(top_builddir)/src/gen-introspect --namespace=Foo \
	--include-idl=$(top_srcdir)/gidl/GLib.gidl \
	`pwd`/foo-object.h -I. -U__GNUC__ $(GOBJECT_CFLAGS) \
	libfoo.la > $@

check-local:
	diff -u Foo-expected.gidl Foo.gidl
