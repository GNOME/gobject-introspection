SCANNER_BIN = $(top_srcdir)/tools/g-ir-scanner
SCANNER_PYTHONPATH = $(top_builddir):$(top_srcdir):$$PYTHONPATH
SCANNER_ENV = env PYTHONPATH=$(SCANNER_PYTHONPATH) \
	UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
	UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir)
SCANNER_ARGS = -v --add-include-path=$(top_builddir)/gir --add-include-path=.
SCANNER = $(SCANNER_ENV) $(SCANNER_BIN) $(SCANNER_ARGS)
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la \
	$(top_builddir)/girepository/libgirepository.la
