AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -module -avoid-version
LIBS = $(GOBJECT_LIBS)

noinst_PROGRAMS = gitestrepo gitestthrows

gitestrepo_SOURCES = $(srcdir)/gitestrepo.c
gitestrepo_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestrepo_LDADD = $(top_builddir)/girepository/libgirepository-1.0.la $(GIREPO_LIBS)

gitestthrows_SOURCES = $(srcdir)/gitestthrows.c
gitestthrows_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestthrows_LDADD = $(top_builddir)/girepository/libgirepository-1.0.la $(GIREPO_LIBS)

TESTS = gitestrepo gitestthrows
TESTS_ENVIRONMENT=env top_builddir="$(top_builddir)" \
   XDG_DATA_DIRS="$(top_srcdir)/gir:$(XDG_DATA_DIRS)" $(DEBUG)