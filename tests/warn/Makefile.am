include $(top_srcdir)/common.mk

TESTS = warntestrunner

alltests = \
	annotationparser.h \
	callback-invalid-scope.h \
	callback-missing-scope.h \
	return-gobject.h \
	invalid-array.h \
	invalid-closure.h \
	invalid-constructor.h \
	invalid-element-type.h \
	invalid-method.h \
	invalid-option.h \
	invalid-out.h \
	invalid-transfer.h \
	missing-element-type.h \
	unknown-parameter.h \
	unresolved-type.h

EXTRA_DIST = warningtester.py warntestrunner $(alltests) common.h $(TESTS)

TESTS_ENVIRONMENT = PYTHONPATH=$(top_builddir):$(top_srcdir) TOP_BUILDDIR=$(top_builddir) UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) PYTHON=$(PYTHON) srcdir=$(srcdir) alltests="$(alltests)"
