#! /bin/sh -x
#
SIMPLE_TESTS="enum.test struct.test constant.test union.test array.test types.test boxed.test errors.test function.test interface.test object.test xref1.test xref2.test"

for i in $SIMPLE_TESTS; do
	../tools/g-idl-compiler -o $i.c $srcdir/$i
	$LIBTOOL --tag=CC --mode=compile $CC -c $GIREPO_CFLAGS -I$srcdir/../girepository $i.c
	$LIBTOOL --tag=CC --mode=link $CC -module -avoid-version -rpath /tmp -o $i.la $i.lo ../girepository/libgirepository.la $GIREPO_LIBS
	../tools/g-idl-generate $i.la > $i.res; 
	diff -u $srcdir/$i $i.res || exit 1; 
	rm -f $i.res $i.la $i.lo $i.o $i.c
done
