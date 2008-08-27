BUILT_SOURCES =

G_IR_SCANNER = $(top_srcdir)/tools/g-ir-scanner
G_IR_SCANNER_FILES = $(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la

# glib
GLIB_INCLUDEDIR=`pkg-config --variable=includedir glib-2.0`/glib-2.0
GLIB_LIBDIR=`pkg-config --variable=libdir glib-2.0`

if OS_WIN32
GLIB_LIBRARY=libglib-2.0-0
else
GLIB_LIBRARY=glib-2.0
endif

GLib.gir: $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	PYTHONPATH=$(top_srcdir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace GLib \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
	    --library=$(GLIB_LIBRARY) \
	    $(CPPFLAGS) \
	    -I$(GLIB_INCLUDEDIR) \
	    -I$(GLIB_LIBDIR)/glib-2.0/include \
	    -DGETTEXT_PACKAGE=Dummy \
	    -D__G_I18N_LIB_H__ \
	    $(GLIB_LIBDIR)/glib-2.0/include/glibconfig.h \
	    $(GLIB_INCLUDEDIR)/glib/*.h
BUILT_SOURCES += GLib.gir

# gobject
GOBJECT_INCLUDEDIR=`pkg-config --variable=includedir gobject-2.0`/glib-2.0
GOBJECT_LIBDIR=`pkg-config --variable=libdir gobject-2.0`

if OS_WIN32
GOBJECT_LIBRARY=libgobject-2.0-0
else
GOBJECT_LIBRARY=gobject-2.0
endif

GObject.gir: GLib.gir $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	PYTHONPATH=$(top_srcdir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace GObject \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
            --include=$(top_builddir)/gir/GLib.gir \
	    --library=$(GOBJECT_LIBRARY) \
	    -I$(GOBJECT_INCLUDEDIR) \
	    -I$(GOBJECT_LIBDIR)/glib-2.0/include \
	    -DGOBJECT_COMPILATION \
            --pkg glib-2.0 \
	    $(GLIB_INCLUDEDIR)/gobject/*.h
BUILT_SOURCES += GObject.gir

# gio
GIO_INCLUDEDIR=`pkg-config --variable=includedir gio-2.0`/glib-2.0
GIO_LIBDIR=`pkg-config --variable=libdir gio-2.0`

if OS_WIN32
GIO_LIBRARY=libgio-2.0-0
else
GIO_LIBRARY=gio-2.0
endif

Gio.gir: GObject.gir $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	PYTHONPATH=$(top_srcdir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace Gio \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
            --include=$(top_builddir)/gir/GObject.gir \
	    --library=$(GIO_LIBRARY) \
	    -I$(GIO_INCLUDEDIR) \
	    -I$(GIO_LIBDIR)/glib-2.0/include \
	    -DGIO_COMPILATION \
            --pkg glib-2.0 \
            --pkg gobject-2.0 \
	    $(GLIB_INCLUDEDIR)/gio/*.h
BUILT_SOURCES += Gio.gir
CLEANFILES = $(BUILT_SOURCES)

girdir=$(datadir)/gir
dist_gir_DATA = $(BUILT_SOURCES)

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT)
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) $< -o $@

typelibsdir = $(datadir)/girepository
typelibs_DATA = GLib.typelib GObject.typelib Gio.typelib
CLEANFILES += $(typelibs_DATA)

EXTRA_DIST = glib-2.0-good.gir gobject-2.0-good.gir gobject-2.0-gio.gir
