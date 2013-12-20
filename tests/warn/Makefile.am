include $(top_srcdir)/common.mk

TESTS = \
	annotationparser.h \
	callback-invalid-scope.h \
	callback-missing-scope.h \
	invalid-array.h \
	invalid-closure.h \
	invalid-constructor.h \
	invalid-element-type.h \
	invalid-method.h \
	invalid-option.h \
	invalid-out.h \
	invalid-transfer.h \
	missing-element-type.h \
	return-gobject.h \
	unknown-parameter.h \
	unresolved-type.h

TESTS_ENVIRONMENT = PYTHONPATH=$(top_builddir):$(top_srcdir) TOP_BUILDDIR=$(top_builddir) UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
	$(PYTHON) $(srcdir)/warningtester.py

EXTRA_DIST = warningtester.py common.h $(TESTS)
