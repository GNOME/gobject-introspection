include $(top_srcdir)/common.mk

TESTS = \
	test_parser.py \
	test_patterns.py

TESTS_ENVIRONMENT = env builddir=$(builddir) top_builddir=$(top_builddir) srcdir=$(srcdir) top_srcdir=$(top_srcdir) \
	PYTHON=$(PYTHON) UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir)
LOG_COMPILER = $(PYTHON) $(top_srcdir)/tests/gi-tester

EXTRA_DIST = \
	$(TESTS)				\
	README					\
	tests.xsd				\
	gi/annotation_allow_none.xml		\
	gi/annotation_array.xml		\
	gi/annotation_attributes.xml		\
	gi/annotation_closure.xml		\
	gi/annotation_constructor.xml		\
	gi/annotation_destroy.xml		\
	gi/annotation_element_type.xml		\
	gi/annotation_foreign.xml		\
	gi/annotation_get_value_func.xml	\
	gi/annotation_in.xml			\
	gi/annotation_in_out.xml		\
	gi/annotation_method.xml		\
	gi/annotation_not_nullable.xml		\
	gi/annotation_out.xml			\
	gi/annotation_ref_func.xml		\
	gi/annotation_rename_to.xml		\
	gi/annotation_scope.xml		\
	gi/annotation_set_value_func.xml	\
	gi/annotation_skip.xml			\
	gi/annotation_transfer.xml		\
	gi/annotation_type.xml			\
	gi/annotation_unref_func.xml		\
	gi/annotation_value.xml		\
	gi/annotation_virtual.xml		\
	gi/annotations.xml			\
	gi/identifier.xml			\
	gi/identifier_section.xml		\
	gi/identifier_symbol.xml		\
	gi/parameter.xml			\
	gi/parameter_varargs.xml		\
	gi/syntax.xml				\
	gi/syntax_indentation.xml		\
	gi/syntax_multiline_annotations.xml	\
	gi/syntax_nested_tags.xml		\
	gi/syntax_paragraph_breaks.xml		\
	gi/syntax_whitespace.xml		\
	gi/tag.xml				\
	gi/tag_deprecated.xml			\
	gi/tag_description.xml			\
	gi/tag_returns.xml			\
	gi/tag_since.xml			\
	gi/tag_stability.xml			\
	gtkdoc/gobject/gtypes.h.xml		\
	gtkdoc/gobject/gtypes.c.xml		\
	gtkdoc/gobject/giface.h.xml		\
	gtkdoc/gobject/giface.c.xml		\
	gtkdoc/fail/tester.h.xml		\
	gtkdoc/fail/tester.c.xml		\
	gtkdoc/empty/tester.c.xml		\
	gtkdoc/bugs/tester.h.xml		\
	gtkdoc/bugs/tester.c.xml		\
	gtkdoc/annotations/tester.h.xml	\
	gtkdoc/annotations/tester.c.xml	\
	gtkdoc/gobject/gobject.h.xml		\
	gtkdoc/gobject/gobject.c.xml		\
	meson.build
