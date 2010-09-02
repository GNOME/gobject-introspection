include $(top_srcdir)/common.mk

warning_tests = \
	return-gobject.h \
	unresolved-type.h

EXTRA_DIST = warningtester.py common.h $(warning_tests)

check-local:
	@PYTHONPATH=$(top_builddir):$(top_srcdir) $(PYTHON) $(srcdir)/warningtester.py $(warning_tests)
