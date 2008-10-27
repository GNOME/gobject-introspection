BUILT_SOURCES =
EXTRA_DIST = 

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

GLib-2.0.gir: $(G_IR_SCANNER) $(G_IR_SCANNER_FILES) Makefile glib-2.0.c
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace GLib --nsversion=2.0 \
	    --add-include-path=. \
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
	    $(srcdir)/glib-2.0.c \
	    $(GLIB_INCLUDEDIR)/glib/*.h
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(G_IR_SCANNER) \
	    --xpath-assertions=GLib-2.0.xpath GLib-2.0.gir	
BUILT_SOURCES += GLib-2.0.gir
EXTRA_DIST += GLib-2.0.xpath

# gobject
GOBJECT_INCLUDEDIR=`pkg-config --variable=includedir gobject-2.0`/glib-2.0
GOBJECT_LIBDIR=`pkg-config --variable=libdir gobject-2.0`

if OS_WIN32
GOBJECT_LIBRARY=libgobject-2.0-0
else
GOBJECT_LIBRARY=gobject-2.0
endif

GObject-2.0.gir: GLib-2.0.gir $(G_IR_SCANNER) $(G_IR_SCANNER_FILES) Makefile
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace GObject --nsversion=2.0 \
	    --add-include-path=. \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
            --include=GLib-2.0 \
	    --library=$(GOBJECT_LIBRARY) \
	    -I$(GOBJECT_INCLUDEDIR) \
	    -I$(GOBJECT_LIBDIR)/glib-2.0/include \
	    -DGOBJECT_COMPILATION \
            --pkg glib-2.0 \
	    $(GLIB_INCLUDEDIR)/gobject/*.h
BUILT_SOURCES += GObject-2.0.gir

# gmodule
GMODULE_INCLUDEDIR=`pkg-config --variable=includedir gmodule-2.0`/glib-2.0
GMODULE_LIBDIR=`pkg-config --variable=libdir gmodule-2.0`

if OS_WIN32
GMODULE_LIBRARY=libgmodule-2.0-0
else
GMODULE_LIBRARY=gmodule-2.0
endif

GModule-2.0.gir: GLib-2.0.gir $(G_IR_SCANNER) $(G_IR_SCANNER_FILES)
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace GModule --nsversion=2.0 \
	    --add-include-path=. \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
            --include=GLib-2.0 \
	    --library=$(GMODULE_LIBRARY) \
	    -I$(GMODULE_INCLUDEDIR) \
	    -I$(GMODULE_LIBDIR)/glib-2.0/include \
            --pkg glib-2.0 \
	    $(GLIB_INCLUDEDIR)/gmodule.h
BUILT_SOURCES += GModule-2.0.gir

# gio
GIO_INCLUDEDIR=`pkg-config --variable=includedir gio-2.0`/glib-2.0
GIO_LIBDIR=`pkg-config --variable=libdir gio-2.0`

if OS_WIN32
GIO_LIBRARY=libgio-2.0-0
else
GIO_LIBRARY=gio-2.0
endif

Gio-2.0.gir: GObject-2.0.gir $(G_IR_SCANNER) $(G_IR_SCANNER_FILES) Makefile $(srcdir)/gio-2.0.c
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(G_IR_SCANNER) \
	    -v --namespace Gio --nsversion=2.0 \
	    --add-include-path=. \
	    --noclosure \
	    --output $@ \
	    --strip-prefix=g \
            --include=GObject-2.0 \
	    --library=$(GIO_LIBRARY) \
	    -I$(GIO_INCLUDEDIR) \
	    -I$(GIO_LIBDIR)/glib-2.0/include \
	    -DGIO_COMPILATION \
            --pkg glib-2.0 \
            --pkg gobject-2.0 \
	    $(srcdir)/gio-2.0.c \
	    $(GLIB_INCLUDEDIR)/gio/*.h
BUILT_SOURCES += Gio-2.0.gir
CLEANFILES = $(BUILT_SOURCES)

girdir=$(datadir)/gir
dist_gir_DATA = $(BUILT_SOURCES)

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) --includedir=. $(G_IR_COMPILER_OPTS) $< -o $@

typelibsdir = $(libdir)/girepository
typelibs_DATA = GLib-2.0.typelib GModule-2.0.typelib GObject-2.0.typelib Gio-2.0.typelib
CLEANFILES += $(typelibs_DATA)

# Check that typelib -> gir -> typelib transformation is lossless.
# Comparing gir files is relatively fragile (whitespace, attribute default
# values, etc.) but the typelibs should identical as long as the gir files are
# semantically equivalent.

%.test.gir: %.typelib $(top_builddir)/tools/g-ir-generate$(EXEEXT) Makefile
	$(DEBUG) $(top_builddir)/tools/g-ir-generate$(EXEEXT) --includedir=. $< -o $@

testlib-%: %.test.gir $(top_builddir)/tools/g-ir-generate$(EXEEXT) Makefile
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler$(EXEEXT) --includedir=. $(G_IR_COMPILER_OPTS) $< -o $*.test.typelib
	cmp $*.typelib $*.test.typelib && rm $*.test.typelib

testgir-%: %.test.gir
	diff -u $*.gir $< && rm $<

CLEANFILES += $(typelibs_DATA:%.typelib=%.test.gir)
CLEANFILES += $(typelibs_DATA:%.typelib=%.test.typelib)

#check-local: $(typelibs_DATA:%.typelib=testlib-%)
check-gir: $(typelibs_DATA:%.typelib=testgir-%)
