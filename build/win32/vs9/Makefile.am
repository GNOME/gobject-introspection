EXTRA_DIST = \
	gobject-introspection.sln	\
	girepository.vcprojin	\
	gir.vspropsin	\
	gir.vsprops	\
	annotation.vcproj	\
	cmph-bdz-test.vcproj	\
	cmph.vcprojin	\
	everything.vcproj	\
	foo.vcproj	\
	g-ir-compiler.vcprojin	\
	g-ir-generate.vcproj	\
	generate_typelibs.vcproj	\
	gettype.vcproj	\
	gimarshallingtests.vcproj	\
	glib-print.vcproj	\
	gtkfrob.vcproj	\
	install.vcproj	\
	regress.vcproj	\
	sletter.vcproj	\
	testinherit.vcproj	\
	utility.vcproj	\
	_giscanner.vcproj	\
	README.txt

gir.vsprops: $(top_srcdir)/build/win32/vs9/gir.vspropsin gir.vs9.install
	$(CPP) -P - <$(top_srcdir)/build/win32/vs9/gir.vspropsin >$@
	rm gir.vs9.install

CLEANFILES = gir.vsprops
