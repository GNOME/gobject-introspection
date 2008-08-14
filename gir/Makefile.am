BUILT_SOURCES = 

G_IR_SCANNER = $(top_srcdir)/tools/g-ir-scanner

# glib
GLIB_INCLUDEDIR=`pkg-config --variable=includedir glib-2.0`/glib-2.0
GLIB_LIBDIR=`pkg-config --variable=libdir glib-2.0`
glib-2.0.gir: $(G_IR_SCANNER)
	$(G_IR_SCANNER) -v --namespace GLib \
	    --output $@ \
	    --strip-prefix=g \
	    -I$(GLIB_INCLUDEDIR) \
	    -I$(GLIB_LIBDIR)/glib-2.0/include \
	    -DGETTEXT_PACKAGE=Dummy \
	    $(GLIB_INCLUDEDIR)/glib/*.h
BUILT_SOURCES += glib-2.0.gir

# gobject
GOBJECT_LIBDIR=`pkg-config --variable=libdir gobject-2.0`
gobject-2.0.gir: $(G_IR_SCANNER)
	$(G_IR_SCANNER) -v --namespace GObject \
	    --output $@ \
	    --strip-prefix=g \
            --include=glib-2.0.gir \
	    -I$(GLIB_INCLUDEDIR) \
	    -I$(GLIB_LIBDIR)/glib-2.0/include \
	    -DGOBJECT_COMPILATION \
            --pkg glib-2.0 \
	    $(GLIB_INCLUDEDIR)/gobject/*.h
BUILT_SOURCES += gobject-2.0.gir

girdir=$(datadir)/gir
dist_gir_DATA = $(BUILT_SOURCES)