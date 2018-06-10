=====================
Autotools Integration
=====================

Checklist
---------

Checklist for making a GObject based library using autotools provide
introspection support. It's not comprehensive, you'll need to adapt this for
the library you're adding introspection support to.

There are 2 ways to add introspection support, one adds the introspection m4
to the distribution, and the library will still build even if introspection is
not installed. The other method will add a build dependency on introspection
(you will need introspection installed to run ./autogen or ./configure)

Method 1 - Recommended - most portable
--------------------------------------

* copy the m4 file into your distribution (check your distribution to see
  where m4 files normally go, this may be 'common' in some applications

  .. code-block:: none

    Create an m4 directory in the root
    copy gobject-introspection/m4/introspection.m4 to m4/
    or 
    copy /usr/share/aclocal/introspection.m4 to m4/

* configure.ac (or configure.in if no .ac file is used)

  .. code-block:: none

    #-- these may be in the file already, or you may need to modify the existing lines.
    AC_PREREQ(2.62)
    AM_INIT_AUTOMAKE([-Wno-portability])

    #
    # Gobject Introspection
    #
    #-- add the correct m4 directory location.
    AC_CONFIG_MACRO_DIR([m4])

    #-- any typos here, and you will end up with a message about HAVE_INTROSPECTION not being defined
    GOBJECT_INTROSPECTION_CHECK([1.30.0])

* Makefile.am (modify these variables in the file, you may have to add them to
  existing definitions, make sure m4 location is correct)

  .. code-block:: none

    ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
    DISTCHECK_CONFIGURE_FLAGS = --enable-introspection
    EXTRA_DIST = m4/introspection.m4
    SUBDIRS = m4 ...

Method 2 - Add a build dependency on Introspection
--------------------------------------------------

Introspection will be required to build the library, however you will not have
to update the m4 files in the future.

* configure.ac (or configure.in if no .ac file is used)

  .. code-block:: none

     GOBJECT_INTROSPECTION_CHECK([1.30.0])

* Makefile.am

  .. code-block:: none

    DISTCHECK_CONFIGURE_FLAGS = --enable-introspection

  or just add to the existing DISTCHECK_CONFIGURE_FLAGS 

Method 1 and Method 2
---------------------

* foo/Makefile.am - must be near the end (after CLEANFILES has been set)

  .. code-block:: none

    -include $(INTROSPECTION_MAKEFILE)
    INTROSPECTION_GIRS =
    INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
    INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

    if HAVE_INTROSPECTION
    introspection_sources = $(libfoo_1_0_la_SOURCES)

    Foo-1.0.gir: libfoo-1.0.la
    Foo_1_0_gir_INCLUDES = GObject-2.0
    Foo_1_0_gir_CFLAGS = $(INCLUDES)
    Foo_1_0_gir_LIBS = libfoo-1.0.la
    Foo_1_0_gir_FILES = $(introspection_sources)
    INTROSPECTION_GIRS += Foo-1.0.gir

    girdir = $(datadir)/gir-1.0
    gir_DATA = $(INTROSPECTION_GIRS)

    typelibdir = $(libdir)/girepository-1.0
    typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

    CLEANFILES += $(gir_DATA) $(typelib_DATA)
    endif

  You can also check out a complete example at
  http://git.gnome.org/cgit/gtk+/tree/gtk/Makefile.am#n962

Makefile variable documentation
-------------------------------

``INTROSPECTION_GIRS`` is the entry point, you should list all the gir files
you want to build there in the XXX-Y.gir format where X is the name of the gir
(for example Gtk) and Y is the version (for example 2.0).

If output is Gtk-2.0.gir then you should name the variables like
``Gtk_2_0_gir_NAMESPACE``, ``Gtk_2_0_gir_VERSION`` etc.

* Required variables:

  * ``FILES`` - C sources and headers which should be scanned 

* One of these variables are required:

  * ``LIBS`` - Library where the symbol represented in the gir can be found
  * ``PROGRAM`` - Program where the symbol represented in the gir can be found 

* Optional variables, commonly used:

  * ``INCLUDES`` - Gir files to include without the .gir suffix, for instance
    GLib-2.0, Gtk-2.0. This is needed for all libraries which you depend on
    that provides introspection information.
  * ``SCANNERFLAGS`` - Flags to pass in to the scanner, see g-ir-scanner(1)
    for a list
  * ``PACKAGES`` - list of pkg-config names which cflags are required to parse
    the headers of this gir. Note that ``INCLUDES`` will already fetch the
    packages and thus the cflags for all dependencies.
  * ``EXPORT_PACKAGES`` - List of pkg-config names which are provided by this
    Gir.
  * ``CFLAGS`` - Flags to pass in to the parser when scanning headers.
    Normally ``INCLUDES`` and ``PACKAGES`` will fetch the cflags for all
    dependencies. This is normally used for project specific CFLAGS.
  * ``LDFLAGS`` - Linker flags used by the scanner. Normally ``INCLUDES`` and
    ``PACKAGES`` will fetch the ldflags for all dependencies. This is normally
    used for project-specific LDFLAGS (for instance if you're building several
    libraries and typelibs).

* Optional variables, seldomly used:

  * ``NAMESPACE`` - Namespace of the gir, first letter capital, rest should be
    lower case, for instance: 'Gtk', 'Clutter', 'ClutterGtk'. If not present
    the namespace will be fetched from the gir filename, the part before the
    first dash. For 'Gtk-2.0', namespace will be 'Gtk'.
  * ``VERSION`` - Version of the gir, if not present, will be fetched from gir
    filename, the part after the first dash. For 'Gtk-2.0', version will be
    '2.0'.
