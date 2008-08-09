#! /bin/sh

set -x
set -e

TESTFILES=$(echo *.test)

for i in $TESTFILES; do
	${CHECK_DEBUG} ../tools/g-ir-compiler --raw $i > $i.1; 
	${CHECK_DEBUG} ../tools/g-ir-generate --raw $i.1 > $i.2; 
	diff -u $srcdir/$i $i.2 || exit 1; 
	rm $i.1 $i.2
done

#../tools/g-ir-compiler --raw --module=Foo $srcdir/object.test $srcdir/gobject.test > object.test.1
#../tools/g-ir-generate --raw object.test.1 > object.test.2
#diff -u $srcdir/object.test object.test.2 || exit 1
#rm object.test.1 object.test.2

#../tools/g-ir-compiler --raw --module=Foo $srcdir/xref1.test $srcdir/xref2.test > xref1.test.1
#../tools/g-ir-generate --raw xref1.test.1 > xref1.test.2
#diff -u $srcdir/xref1.test xref1.test.2 || exit 1
#rm xref1.test.1 xref1.test.2

#../tools/g-ir-compiler --raw --module=Bar $srcdir/xref1.test $srcdir/xref2.test > xref2.test.1
#../tools/g-ir-generate --raw xref2.test.1 > xref2.test.2
#diff -u $srcdir/xref2.test xref2.test.2 || exit 1
#rm xref2.test.1 xref2.test.2
