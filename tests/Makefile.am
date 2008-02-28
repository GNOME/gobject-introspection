SUBDIRS = invoke parser

EXTRA_DIST = \
	roundtrips.sh	\
	array.test	\
	boxed.test	\
	constant.test	\
	enum.test	\
	errors.test	\
	function.test	\
	gobject.test	\
	interface.test	\
	object.test	\
	struct.test	\
	types.test	\
	union.test	\
	xref1.test	\
	xref2.test

TESTS_ENVIRONMENT = \
	LIBTOOL="$(LIBTOOL)" \
	GIREPO_CFLAGS="$(GIREPO_CFLAGS)" \
	GIREPO_LIBS="$(GIREPO_LIBS)" \
	CC="$(CC)" \
	GIREPOPATH="."

TESTS = roundtrips.sh
