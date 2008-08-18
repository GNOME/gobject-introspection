BUILT_SOURCES = 

G_IR_SCANNER = $(top_srcdir)/tools/g-ir-scanner
G_IR_SCANNER_FILES = $(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la

# glib
GLIB_INCLUDEDIR=`pkg-config --variable=includedir glib-2.0`/glib-2.0
GLIB_LIBDIR=`pkg-config --variable=libdir glib-2.0`
glib-2.0.gir: $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	$(G_IR_SCANNER) -v --namespace GLib \
	    --output $@ \
	    --strip-prefix=g \
	    -I$(GLIB_INCLUDEDIR) \
	    -I$(GLIB_LIBDIR)/glib-2.0/include \
	    -DGETTEXT_PACKAGE=Dummy \
	    -D__G_I18N_LIB_H__ \
	    $(GLIB_INCLUDEDIR)/glib/*.h
BUILT_SOURCES += glib-2.0.gir

# gobject
GOBJECT_INCLUDEDIR=`pkg-config --variable=includedir gobject-2.0`/glib-2.0
GOBJECT_LIBDIR=`pkg-config --variable=libdir gobject-2.0`
gobject-2.0.gir: $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	$(G_IR_SCANNER) -v --namespace GObject \
	    --output $@ \
	    --strip-prefix=g \
            --include=$(builddir)/glib-2.0.gir \
	    --library=$(GOBJECT_LIBDIR)/libgobject-2.0.so \
	    -I$(GOBJECT_INCLUDEDIR) \
	    -I$(GOBJECT_LIBDIR)/glib-2.0/include \
	    -DGOBJECT_COMPILATION \
            --pkg glib-2.0 \
	    $(GLIB_INCLUDEDIR)/gobject/*.h
BUILT_SOURCES += gobject-2.0.gir
CLEANFILES = $(BUILT_SOURCES)

# gio
GIO_INCLUDEDIR=`pkg-config --variable=includedir gio-2.0`/glib-2.0
GIO_LIBDIR=`pkg-config --variable=libdir gio-2.0`
gio-2.0.gir: $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	$(G_IR_SCANNER) -v --namespace Gio \
	    --output $@ \
	    --strip-prefix=g \
            --include=$(builddir)/glib-2.0.gir \
            --include=$(builddir)/gobject-2.0.gir \
	    --library=$(GIO_LIBDIR)/libgio-2.0.so \
	    -I$(GIO_INCLUDEDIR) \
	    -I$(GIO_LIBDIR)/glib-2.0/include \
	    -DGIO_COMPILATION \
            --pkg glib-2.0 \
            --pkg gobject-2.0 \
	    $(GLIB_INCLUDEDIR)/gio/*.h
BUILT_SOURCES += gio-2.0.gir
CLEANFILES = $(BUILT_SOURCES)

girdir=$(datadir)/gir
dist_gir_DATA = $(BUILT_SOURCES)

EXTRA_DIST = glib-2.0-good.gir gobject-2.0-good.gir gobject-2.0-gio.gir
