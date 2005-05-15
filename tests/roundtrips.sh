#! /bin/sh

SIMPLE_TESTS="array.test boxed.test enum.test errors.test function.test interface.test union.test"

for i in $SIMPLE_TESTS; do
	echo $i
	../src/g-idl-compiler --raw $i > $i.1; 
	../src/g-idl-generate --raw $i.1 > $i.2; 
	diff -u $i $i.2 || exit 1; 
	rm $i.1 $i.2
done

../src/g-idl-compiler --raw --module=Foo object.test gobject.test > object.test.1
../src/g-idl-generate --raw object.test.1 > object.test.2
diff -u object.test object.test.2 || exit 1
rm object.test.1 object.test.2

../src/g-idl-compiler --raw --module=Foo xref1.test xref2.test > xref1.test.1
../src/g-idl-generate --raw xref1.test.1 > xref1.test.2
diff -u xref1.test xref1.test.2 || exit 1
rm xref1.test.1 xref1.test.2

../src/g-idl-compiler --raw --module=Bar xref1.test xref2.test > xref2.test.1
../src/g-idl-generate --raw xref2.test.1 > xref2.test.2
diff -u xref2.test xref2.test.2 || exit 1
rm xref2.test.1 xref2.test.2
