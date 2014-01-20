EXTRA_DIST = \
	gobject-introspection.sln	\
	gi-build-defines.vsprops	\
	gi-extra-paths.vsprops	\
	gi-gen-srcs.vsprops	\
	gi-install.vspropsin	\
	gi-install.vsprops	\
	gi-version-paths.vsprops	\
	gi-prebuild.vcproj	\
	girepository.vcprojin	\
	annotation.vcproj	\
	cmph-bdz-test.vcproj	\
	cmph.vcprojin	\
	foo.vcproj	\
	g-ir-compiler.vcprojin	\
	g-ir-generate.vcproj	\
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

gi-install.vsprops: $(top_srcdir)/build/win32/vs9/gi-install.vspropsin gir.vs9.install
	$(CPP) -P - <$(top_srcdir)/build/win32/vs9/gi-install.vspropsin >$@
	rm gir.vs9.install

CLEANFILES = gir-install.vsprops
