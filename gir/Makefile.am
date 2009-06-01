include $(top_srcdir)/common.mk

CHECKGIRS =
BUILT_GIRSOURCES = 
CLEANFILES =
EXTRA_DIST = 

BASE_GIRSOURCES = 		\
	cairo-1.0.gir 		\
	fontconfig-2.0.gir	\
	freetype2-2.0.gir	\
	GL-1.0.gir		\
	libxml2-2.0.gir		\
	xft-2.0.gir 		\
	xlib-2.0.gir 		\
	xfixes-4.0.gir
EXTRA_DIST += $(BASE_GIRSOURCES)

# glib
GLIB_INCLUDEDIR=`pkg-config --variable=includedir glib-2.0`/glib-2.0
GLIB_LIBDIR=`pkg-config --variable=libdir glib-2.0`

if OS_WIN32
GLIB_LIBRARY=libglib-2.0-0
else
GLIB_LIBRARY=glib-2.0
endif

GLib-2.0.gir: $(SCANNER_BIN) $(SCANNER_LIBS) Makefile glib-2.0.c
	$(SCANNER) \
	    --namespace GLib --nsversion=2.0 \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
	    --libtool="$(SHAVE_SAVED_LIBTOOL)" \
	    --c-include="glib.h" \
	    --library=$(GLIB_LIBRARY) \
	    --pkg glib-2.0 \
	    $(CPPFLAGS) \
	    -I$(GLIB_INCLUDEDIR) \
	    -I$(GLIB_LIBDIR)/glib-2.0/include \
	    -DGETTEXT_PACKAGE=Dummy \
	    -D__G_I18N_LIB_H__ \
	    $(GLIB_LIBDIR)/glib-2.0/include/glibconfig.h \
	    $(srcdir)/glib-2.0.c \
	    $(GLIB_INCLUDEDIR)/glib/*.h
	$(SCANNER) $(SCANNER_ARGS) \
	    --xpath-assertions=$(srcdir)/GLib-2.0.xpath GLib-2.0.gir
BUILT_GIRSOURCES += GLib-2.0.gir
EXTRA_DIST += glib-2.0.c GLib-2.0.xpath

# gobject
GOBJECT_INCLUDEDIR=`pkg-config --variable=includedir gobject-2.0`/glib-2.0
GOBJECT_LIBDIR=`pkg-config --variable=libdir gobject-2.0`

if OS_WIN32
GOBJECT_LIBRARY=libgobject-2.0-0
else
GOBJECT_LIBRARY=gobject-2.0
endif

GObject-2.0.gir: GLib-2.0.gir $(SCANNER_BIN) $(SCANNER_LIBS) Makefile
	$(SCANNER) \
	    --namespace GObject --nsversion=2.0 \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
	    --libtool="$(SHAVE_SAVED_LIBTOOL)" \
	    --c-include="glib-object.h" \
	    --include=GLib-2.0 \
	    --library=$(GOBJECT_LIBRARY) \
	    -I$(GOBJECT_INCLUDEDIR) \
	    -I$(GOBJECT_LIBDIR)/glib-2.0/include \
	    -DGOBJECT_COMPILATION \
	    --pkg gobject-2.0 \
	    $(srcdir)/gobject-2.0.c \
	    $(GLIB_INCLUDEDIR)/gobject/*.h
	$(SCANNER) $(SCANNER_ARGS) \
	    --xpath-assertions=$(srcdir)/GObject-2.0.xpath GObject-2.0.gir
BUILT_GIRSOURCES += GObject-2.0.gir
EXTRA_DIST += GObject-2.0.xpath

# gmodule
GMODULE_INCLUDEDIR=`pkg-config --variable=includedir gmodule-2.0`/glib-2.0
GMODULE_LIBDIR=`pkg-config --variable=libdir gmodule-2.0`

if OS_WIN32
GMODULE_LIBRARY=libgmodule-2.0-0
else
GMODULE_LIBRARY=gmodule-2.0
endif

GModule-2.0.gir: GLib-2.0.gir $(SCANNER_BIN) $(SCANNER_LIBS)
	$(SCANNER) \
	    --namespace GModule --nsversion=2.0 \
	    --add-include-path=. \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
	    --libtool="$(SHAVE_SAVED_LIBTOOL)" \
	    --c-include="gmodule.h" \
	    --include=GLib-2.0 \
	    --library=$(GMODULE_LIBRARY) \
	    -I$(GMODULE_INCLUDEDIR) \
	    -I$(GMODULE_LIBDIR)/glib-2.0/include \
	    --pkg gmodule-2.0 \
	    $(GLIB_INCLUDEDIR)/gmodule.h
BUILT_GIRSOURCES += GModule-2.0.gir

# gio
GIO_INCLUDEDIR=`pkg-config --variable=includedir gio-2.0`/glib-2.0
GIO_LIBDIR=`pkg-config --variable=libdir gio-2.0`

if OS_WIN32
GIO_LIBRARY=libgio-2.0-0
else
GIO_LIBRARY=gio-2.0
endif

if HAVE_GIO_UNIX
GIO_UNIX_HDRS=`pkg-config --variable=includedir gio-unix-2.0`/gio-unix-2.0/gio/*.h
else
GIO_UNIX_HDRS=
endif

Gio-2.0.gir: GObject-2.0.gir $(SCANNER_BIN) $(SCANNER_LIBS) Makefile $(srcdir)/gio-2.0.c
	$(SCANNER) \
	    --namespace Gio --nsversion=2.0 \
	    --add-include-path=. \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
		--libtool="$(SHAVE_SAVED_LIBTOOL)" \
		--c-include="gio/gio.h" \
		--include=GObject-2.0 \
	    --library=$(GIO_LIBRARY) \
	    -I$(GIO_INCLUDEDIR) \
	    -I$(GIO_LIBDIR)/glib-2.0/include \
	    -DGIO_COMPILATION \
        --pkg gio-2.0 \
	    $(srcdir)/gio-2.0.c \
	    $(GLIB_INCLUDEDIR)/gio/*.h \
	    $(GIO_UNIX_HDRS)
BUILT_GIRSOURCES += Gio-2.0.gir
EXTRA_DIST += gio-2.0.c

# girepository
GIREPOSITORY_FILES = \
	$(top_srcdir)/girepository/girepository.c \
	$(top_srcdir)/girepository/girepository.h

GIRepository-2.0.gir: GObject-2.0.gir $(SCANNER_BIN) $(SCANNER_LIBS) $(GIREPOSITORY_FILES)
	$(SCANNER) \
	    --namespace GIRepository --nsversion=2.0 \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
		--libtool="$(SHAVE_SAVED_LIBTOOL)" \
		--c-include="girepository.h" \
		--include=GObject-2.0 \
	    --library=girepository-1.0 \
	    -I$(srcdir)/girepository \
		--pkg glib-2.0 \
		--pkg gobject-2.0 \
	    $(GIREPOSITORY_FILES)
BUILT_GIRSOURCES += GIRepository-2.0.gir

LT_CURRENT = 1
LT_REVISION = 0
LT_AGE = 0
LT_VERSION = $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
TYPELIB_VERSION = $(LT_CURRENT).0

lib_LTLIBRARIES = libgirepository-everything-1.0.la

libgirepository_everything_1_0_la_SOURCES = $(srcdir)/everything.c $(srcdir)/everything.h
libgirepository_everything_1_0_la_CFLAGS = $(GOBJECT_CFLAGS)
libgirepository_everything_1_0_la_LDFLAGS = -version-info $(LT_VERSION)
libgirepository_everything_1_0_la_LIBADD = $(GOBJECT_LIBS)

if OS_WIN32
libgirepository_everything_1_0_la_LDFLAGS += -no-undefined
endif

Everything-$(TYPELIB_VERSION).gir: libgirepository-everything-1.0.la everything.c everything.h $(SCANNER_BIN) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) \
	--include=GObject-2.0 \
        --libtool="$(SHAVE_SAVED_LIBTOOL)" \
	--library=girepository-everything-1.0 \
	--namespace=Everything --nsversion=$(TYPELIB_VERSION) \
	--pkg gobject-2.0 \
	$(srcdir)/everything.h $(srcdir)/everything.c \
	--output $@
BUILT_GIRSOURCES += Everything-$(TYPELIB_VERSION).gir
CHECKGIRS += Everything-$(TYPELIB_VERSION)-expected.gir

# Generic rules
CLEANFILES += $(BUILT_GIRSOURCES)

GIRSOURCES = 			\
	$(BASE_GIRSOURCES)	\
	$(BUILT_GIRSOURCES)

girdir = $(GIR_DIR)
dist_gir_DATA = $(GIRSOURCES)

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT)
	LD_LIBRARY_PATH=$${LD_LIBRARY_PATH:+$$LD_LIBRARY_PATH:}:$(top_builddir)/girepository/.libs $(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) --includedir=. $(G_IR_COMPILER_OPTS) $< -o $@

typelibsdir = $(libdir)/girepository-1.0
typelibs_DATA = $(GIRSOURCES:.gir=.typelib)

CLEANFILES += $(typelibs_DATA)

%.gir.check: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "  TEST  $*.gir"

check-local: $(CHECKGIRS)

# Check that typelib -> gir -> typelib transformation is lossless.
# Comparing gir files is relatively fragile (whitespace, attribute default
# values, etc.) but the typelibs should identical as long as the gir files are
# semantically equivalent.

%.test.gir: %.typelib $(top_builddir)/tools/g-ir-generate$(EXEEXT)
	$(DEBUG) $(top_builddir)/tools/g-ir-generate$(EXEEXT) --includedir=. $< -o $@

testlib-%: %.test.gir $(top_builddir)/tools/g-ir-generate$(EXEEXT)
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) --includedir=. $(G_IR_COMPILER_OPTS) $< -o $*.test.typelib
	cmp $*.typelib $*.test.typelib && rm $*.test.typelib

testgir-%: %.test.gir
	diff -u $*.gir $< && rm $<

CLEANFILES += $(typelibs_DATA:%.typelib=%.test.gir)
CLEANFILES += $(typelibs_DATA:%.typelib=%.test.typelib)

#check-local: $(typelibs_DATA:%.typelib=testlib-%)
check-gir: $(typelibs_DATA:%.typelib=testgir-%)
