include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

EXPECTEDGIRS =
BUILT_GIRSOURCES =
CLEANFILES =
EXTRA_DIST =

BASE_GIRSOURCES =               \
        cairo-1.0.gir           \
        fontconfig-2.0.gir      \
        freetype2-2.0.gir       \
        GL-1.0.gir              \
        libxml2-2.0.gir         \
        xft-2.0.gir             \
        xlib-2.0.gir            \
        xfixes-4.0.gir          \
        xrandr-1.3.gir
EXTRA_DIST += $(BASE_GIRSOURCES)

INTROSPECTION_GIRS =

# glib
GLIB_INCLUDEDIR=$(shell pkg-config --variable=includedir glib-2.0)/glib-2.0
GLIB_LIBDIR=$(shell pkg-config --variable=libdir glib-2.0)

if OS_WIN32
GLIB_LIBRARY=libglib-2.0-0
else
GLIB_LIBRARY=glib-2.0
endif

GLib_2_0_gir_LIBS = $(GLIB_LIBRARY)
GLib_2_0_gir_SCANNERFLAGS = --noclosure --strip-prefix=g --c-include="glib.h"
GLib_2_0_gir_PACKAGES = glib-2.0
GLib_2_0_gir_CFLAGS = $(CPPFLAGS) \
            -I$(GLIB_INCLUDEDIR) \
            -I$(GLIB_LIBDIR)/glib-2.0/include \
            -DGETTEXT_PACKAGE=Dummy \
            -DGLIB_COMPILATION \
            -D__G_I18N_LIB_H__
GLib_2_0_gir_ASSERTIONS = GLib-2.0.xpath
GLib_2_0_gir_FILES =  \
                $(GLIB_LIBDIR)/glib-2.0/include/glibconfig.h \
	$(GLIB_INCLUDEDIR)/glib/*.h \
                glib-2.0.c

INTROSPECTION_GIRS += GLib-2.0.gir
EXTRA_DIST += glib-2.0.c GLib-2.0.xpath

# gobject
GOBJECT_INCLUDEDIR=$(shell pkg-config --variable=includedir gobject-2.0)/glib-2.0
GOBJECT_LIBDIR=$(shell pkg-config --variable=libdir gobject-2.0)

if OS_WIN32
GOBJECT_LIBRARY=libgobject-2.0-0
else
GOBJECT_LIBRARY=gobject-2.0
endif

GObject-2.0.gir: GLib-2.0.gir

GObject_2_0_gir_LIBS = $(GOBJECT_LIBRARY)
GObject_2_0_gir_SCANNERFLAGS = --noclosure --strip-prefix=g --c-include="glib-object.h" --add-include-path=.
GObject_2_0_gir_PACKAGES = gobject-2.0
GObject_2_0_gir_INCLUDES = GLib-2.0
GObject_2_0_gir_CFLAGS = \
            -DGOBJECT_COMPILATION \
                -I$(GOBJECT_INCLUDEDIR) \
            -I$(GOBJECT_LIBDIR)/glib-2.0/include
GObject_2_0_gir_ASSERTIONS = GObject-2.0.xpath
GObject_2_0_gir_FILES = $(GLIB_INCLUDEDIR)/gobject/*.h gobject-2.0.c

INTROSPECTION_GIRS += GObject-2.0.gir
EXTRA_DIST += gobject-2.0.c GObject-2.0.xpath

# gmodule
GMODULE_INCLUDEDIR=$(shell pkg-config --variable=includedir gmodule-2.0)/glib-2.0
GMODULE_LIBDIR=$(shell pkg-config --variable=libdir gmodule-2.0)

if OS_WIN32
GMODULE_LIBRARY=libgmodule-2.0-0
else
GMODULE_LIBRARY=gmodule-2.0
endif

GModule-2.0.gir: GLib-2.0.gir

GModule_2_0_gir_LIBS = $(GMODULE_LIBRARY)
GModule_2_0_gir_SCANNERFLAGS = --noclosure --strip-prefix=g --c-include="gmodule.h" --add-include-path=.
GModule_2_0_gir_PACKAGES = gmodule-2.0
GModule_2_0_gir_INCLUDES = GLib-2.0
GModule_2_0_gir_CFLAGS = \
            -I$(GMODULE_INCLUDEDIR) \
            -I$(GMODULE_LIBDIR)/glib-2.0/include
GModule_2_0_gir_FILES = $(GLIB_INCLUDEDIR)/gmodule.h

INTROSPECTION_GIRS += GModule-2.0.gir

# gio
GIO_INCLUDEDIR=$(shell pkg-config --variable=includedir gio-2.0)/glib-2.0
GIO_LIBDIR=$(shell pkg-config --variable=libdir gio-2.0)

if OS_WIN32
GIO_LIBRARY=libgio-2.0-0
else
GIO_LIBRARY=gio-2.0
endif

if HAVE_GIO_UNIX
GIO_UNIX_HDRS=$(shell pkg-config --variable=includedir gio-unix-2.0)/gio-unix-2.0/gio/*.h
GIO_UNIX_PACKAGES = gio-unix-2.0
else
GIO_UNIX_HDRS=
GIO_UNIX_PACKAGES =
endif

Gio-2.0.gir: GObject-2.0.gir

Gio_2_0_gir_LIBS = $(GIO_LIBRARY)
Gio_2_0_gir_SCANNERFLAGS = --noclosure --strip-prefix=g --c-include="gio/gio.h" --add-include-path=.
Gio_2_0_gir_PACKAGES = gio-2.0 $(GIO_UNIX_PACKAGES)
Gio_2_0_gir_INCLUDES = GObject-2.0
Gio_2_0_gir_CFLAGS = \
            -DGIO_COMPILATION \
            -I$(GIO_LIBDIR)/glib-2.0/include
Gio_2_0_gir_FILES = \
            $(GIO_UNIX_HDRS) \
            $(GIO_INCLUDEDIR)/gio/*.h \
            gio-2.0.c

INTROSPECTION_GIRS += Gio-2.0.gir
EXTRA_DIST += gio-2.0.c

# girepository
GIRepository-2.0.gir: GObject-2.0.gir $(top_builddir)/girepository/libgirepository-1.0.la

GIRepository_2_0_gir_LIBS = girepository-1.0
GIRepository_2_0_gir_SCANNERFLAGS = \
        --noclosure \
        --strip-prefix=g \
        --c-include="girepository.h" \
        --pkg-export gobject-introspection-1.0 \
        --add-include-path=.
GIRepository_2_0_gir_PACKAGES = gobject-2.0
GIRepository_2_0_gir_INCLUDES = GObject-2.0
GIRepository_2_0_gir_CFLAGS = \
    -I$(top_srcdir)/girepository -I$(top_srcdir) \
    -DGI_COMPILATION
GIRepository_2_0_gir_FILES = \
        $(top_srcdir)/girepository/gibaseinfo.c \
        $(top_srcdir)/girepository/gibaseinfo.h \
        $(top_srcdir)/girepository/gitypelib.h \
        $(top_srcdir)/girepository/gitypes.h \
        $(top_srcdir)/girepository/girepository.c \
        $(top_srcdir)/girepository/girepository.h

INTROSPECTION_GIRS += GIRepository-2.0.gir

# everything
LT_CURRENT = 1
LT_REVISION = 0
LT_AGE = 0
LT_VERSION = $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
TYPELIB_VERSION = $(LT_CURRENT).0

lib_LTLIBRARIES =

libgirepository_everything_1_0_la_SOURCES = everything.c everything.h
libgirepository_everything_1_0_la_CFLAGS = $(GOBJECT_CFLAGS) $(CAIRO_CFLAGS)
libgirepository_everything_1_0_la_LDFLAGS = -version-info $(LT_VERSION)
libgirepository_everything_1_0_la_LIBADD = $(GOBJECT_LIBS) $(CAIRO_LIBS)

if OS_WIN32
libgirepository_everything_1_0_la_LDFLAGS += -no-undefined
endif

if BUILD_TESTS
Everything-1.0.gir: Gio-2.0.gir libgirepository-everything-1.0.la

Everything_1_0_gir_LIBS = libgirepository-everything-1.0.la
Everything_1_0_gir_PACKAGES = gobject-2.0 cairo gio-2.0
Everything_1_0_gir_INCLUDES = GObject-2.0 cairo-1.0 Gio-2.0
Everything_1_0_gir_FILES = everything.h everything.c

if HAVE_CAIRO
INTROSPECTION_GIRS += Everything-$(TYPELIB_VERSION).gir
EXPECTEDGIRS += Everything-$(TYPELIB_VERSION)-expected.gir
lib_LTLIBRARIES += libgirepository-everything-1.0.la
endif


# marshalling tests
lib_LTLIBRARIES += libgirepository-gimarshallingtests-1.0.la

libgirepository_gimarshallingtests_1_0_la_SOURCES = gimarshallingtests.c gimarshallingtests.h
libgirepository_gimarshallingtests_1_0_la_CFLAGS = $(GOBJECT_CFLAGS)
libgirepository_gimarshallingtests_1_0_la_LDFLAGS = -version-info $(LT_VERSION)
libgirepository_gimarshallingtests_1_0_la_LIBADD = $(GOBJECT_LIBS)

if OS_WIN32
libgirepository_gimarshallingtests_1_0_la_LDFLAGS += -no-undefined
endif

GIMarshallingTests-1.0.gir: libgirepository-gimarshallingtests-1.0.la GObject-2.0.gir

GIMarshallingTests_1_0_gir_LIBS = libgirepository-gimarshallingtests-1.0.la
GIMarshallingTests_1_0_gir_PACKAGES = gobject-2.0
GIMarshallingTests_1_0_gir_INCLUDES = GObject-2.0
GIMarshallingTests_1_0_gir_FILES = gimarshallingtests.h gimarshallingtests.c

INTROSPECTION_GIRS += GIMarshallingTests-$(TYPELIB_VERSION).gir
EXPECTEDGIRS += GIMarshallingTests-$(TYPELIB_VERSION)-expected.gir

endif

# Generic rules
CLEANFILES += $(INTROSPECTION_GIRS)

GIRSOURCES =                    \
        $(BASE_GIRSOURCES)      \
        $(INTROSPECTION_GIRS)

girdir = $(GIR_DIR)
gir_DATA = $(GIRSOURCES)

typelibsdir = $(libdir)/girepository-1.0
typelibs_DATA = $(GIRSOURCES:.gir=.typelib)

CLEANFILES += $(typelibs_DATA)

%.gir.check: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "  TEST  $*.gir"

CHECKGIRS = $(EXPECTEDGIRS:-expected.gir=.gir.check)
check-local: $(CHECKGIRS)

# Check that typelib -> gir -> typelib transformation is lossless.
# Comparing gir files is relatively fragile (whitespace, attribute default
# values, etc.) but the typelibs should identical as long as the gir files are
# semantically equivalent.

%.test.gir: %.typelib $(top_builddir)/tools/g-ir-generate$(EXEEXT)
	$(DEBUG) $(top_builddir)/tools/g-ir-generate$(EXEEXT) --includedir=. $< -o $@

testlib-%: %.test.gir $(top_builddir)/tools/g-ir-generate$(EXEEXT)
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) --includedir=. $< -o $*.test.typelib
	cmp $*.typelib $*.test.typelib && rm $*.test.typelib

testgir-%: %.test.gir
	diff -u $*.gir $< && rm $<

CLEANFILES += $(typelibs_DATA:%.typelib=%.test.gir)
CLEANFILES += $(typelibs_DATA:%.typelib=%.test.typelib)

#check-local: $(typelibs_DATA:%.typelib=testlib-%)
check-gir: $(typelibs_DATA:%.typelib=testgir-%)

EXTRA_DIST += $(EXPECTEDGIRS)
