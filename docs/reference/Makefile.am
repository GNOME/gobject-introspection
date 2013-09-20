AUTOMAKE_OPTIONS = 1.6

# The name of the module.
DOC_MODULE=gi

# The top-level SGML file.
DOC_MAIN_SGML_FILE=gi-docs.sgml

# The directory containing the source code. Relative to $(srcdir)
DOC_SOURCE_DIR=$(top_srcdir)/girepository

# Extra options to supply to gtkdoc-scan
SCAN_OPTIONS=

# Extra options to supply to gtkdoc-mkdb
MKDB_OPTIONS=--sgml-mode --output-format=xml --name-space=g --ignore-files=cmph

# Used for dependencies
HFILE_GLOB=$(top_srcdir)/girepository/*.h
CFILE_GLOB=$(top_srcdir)/girepository/*.c

# Headers to ignore
IGNORE_HFILES= \
    girnode.h	    \
    ginfo.h	    \
    girparser.h	    \
    girwriter.h	    \
    girmodule.h

AM_CPPFLAGS=$(GIREPO_CFLAGS) -I$(top_srcdir)
GTKDOC_LIBS = $(GIREPO_LIBS) $(top_builddir)/libgirepository-1.0.la $(top_builddir)/libgirepository-internals.la

content_files = \
    gi-gir-reference.xml    \
    gi-gir.sgml		    \
    gi-overview.xml	    \
    gi-struct-hierarchy.xml

HTML_IMAGES = \
    $(srcdir)/images/overview.png

# Extra options to supply to gtkdoc-fixref
FIXXREF_OPTIONS=

# include common portion ...
include $(top_srcdir)/gtk-doc.make
# Other files to distribute
EXTRA_DIST += version.xml.in

gtk-docs-clean:
	rm -fr html tmpl xml

clean-local: gtk-docs-clean

########################################################################

dist-hook-local: $(BUILT_EXTRA_DIST)
	files='$(BUILT_EXTRA_DIST)';				\
	for f in $$files; do					\
	  if test -f $$f; then d=.; else d=$(srcdir); fi;	\
	  cp $$d/$$f $(distdir) || exit 1; done
