GENERATED_ITEMS = \
	cmph.vcproj		\
	girepository.vcproj	\
	g-ir-compiler.vcproj	\
	gi-install.vsprops

EXTRA_DIST = \
	gobject-introspection.sln	\
	gi-build-defines.vsprops	\
	gi-extra-paths.vsprops	\
	gi-gen-srcs.vsprops	\
	gi-install.vspropsin	\
	gi-version-paths.vsprops	\
	gi-prebuild.vcproj	\
	girepository.vcprojin	\
	cmph-bdz-test.vcproj		\
	cmph.vcprojin		\
	g-ir-compiler.vcprojin	\
	g-ir-generate.vcproj	\
	glib-print.vcproj	\
	gi-install.vcproj	\
	_giscanner.vcproj	\
	README.txt	\
	$(GENERATED_ITEMS)

gi-install.vsprops: $(top_srcdir)/build/win32/vs9/gi-install.vspropsin girepository.headers giscanner.scripts
	$(CPP) -P - <$(top_srcdir)/build/win32/vs9/gi-install.vspropsin >$@
	rm girepository.headers
	rm giscanner.scripts

DISTCLEANFILES = $(GENERATED_ITEMS)
