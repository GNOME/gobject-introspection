# NMake Makefile to build The Tests for G-I

# Please do not change anything after this line

!include gi-build-common-msvc.mak

BASE_GLIB_LIBS = gio-$(GLIB_APIVERSION).lib gobject-$(GLIB_APIVERSION).lib gmodule-$(GLIB_APIVERSION).lib glib-$(GLIB_APIVERSION).lib
CFLAGS = $(CFLAGS_ADD) /I$(TOP_SRCDIR) /W3 /we4013 /FImsvc_recommended_pragmas.h /DHAVE_CONFIG_H
LDFLAGS = /link $(LDFLAGS_ARCH) $(BASE_GLIB_LIBS)
LDFLAGS_DLL = /link $(LDFLAGS_ARCH) /DLL /out:$@ /implib:$*-$(GI_APIVERSION).lib $(BASE_GLIB_LIBS)

# Special CFLAGS for Regress test
REGRESS_CFLAGS = -DREGRESS_PRINT_PREVIEW_COMMAND="evince --unlink-tempfile --preview --print-settings %s %f" -DREGRESS_SOME_CHAR='c'

# The test .gir's for G-I that are built
built_test_girs = 	\
	GIMarshallingTests-$(GI_APIVERSION).gir	\
	Everything-$(GI_APIVERSION).gir	\
	Offsets-$(GI_APIVERSION).gir	\
	SLetter-$(GI_APIVERSION).gir	\
	Utility-$(GI_APIVERSION).gir	\
	GtkFrob-$(GI_APIVERSION).gir	\
	GetType-$(GI_APIVERSION).gir	\
	WarnLib-$(GI_APIVERSION).gir	\
	Typedefs-$(GI_APIVERSION).gir	\
	Regress-$(GI_APIVERSION).gir	\
	Bar-$(GI_APIVERSION).gir	\
	Headeronly-$(GI_APIVERSION).gir	\
	Identfilter-$(GI_APIVERSION).gir

built_test_typelibs =	\
	GIMarshallingTests-$(GI_APIVERSION).typelib	\
	Everything-$(GI_APIVERSION).typelib	\
	Offsets-$(GI_APIVERSION).typelib	\
	SLetter-$(GI_APIVERSION).typelib	\
	Utility-$(GI_APIVERSION).typelib	\
	GtkFrob-$(GI_APIVERSION).typelib	\
	GetType-$(GI_APIVERSION).typelib	\
	WarnLib-$(GI_APIVERSION).typelib	\
	Typedefs-$(GI_APIVERSION).typelib	\
	Regress-$(GI_APIVERSION).typelib	\
	Bar-$(GI_APIVERSION).typelib	\
	Headeronly-$(GI_APIVERSION).typelib	\
	Identfilter-$(GI_APIVERSION).typelib

test_programs =	\
	gitestrepo.exe	\
	gitestthrows.exe	\
	gitypelibtest.exe	\
	gitestoffsets.exe

built_doc_tests =	\
	Regress-$(GI_APIVERSION)-C	\
	Regress-$(GI_APIVERSION)-Python	\
	Regress-$(GI_APIVERSION)-Gjs	\
	Regress-$(GI_APIVERSION)-sections.txt

!if "$(BUILD_INTROSPECTION)" == "TRUE"
all: setgirbuildenv $(built_test_girs) $(built_test_typelibs) $(test_programs) $(built_doc_tests) warn_tests_log.txt

!include gi-setenv-msvc.mak

# Rules for building the test DLLs
gimarshallingtests.dll: $(TOP_SRCDIR)\tests\gimarshallingtests.c
	$(CC) $(CFLAGS) $(TOP_SRCDIR)\tests\gimarshallingtests.c $(LDFLAGS_DLL)
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;2

everything.dll: everything.c everything.h
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\tests everything.c $(LDFLAGS_DLL)
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;2

offsets.dll: $(TOP_SRCDIR)\tests\offsets\offsets.c
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\tests /I$(TOP_SRCDIR)\tests\offsets $(TOP_SRCDIR)\tests\offsets\offsets.c $(LDFLAGS_DLL)
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;2

sletter.dll utility.dll gtkfrob.dll gettype.dll warnlib.dll typedefs.dll:
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\tests $(TOP_SRCDIR)\tests\scanner\$*.c $(LDFLAGS_DLL)
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;2

regress.dll:
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\tests	\
	$(REGRESS_CFLAGS)	\
	$(TOP_SRCDIR)\tests\scanner\regress.c	\
	$(TOP_SRCDIR)\tests\scanner\annotation.c	\
	$(TOP_SRCDIR)\tests\scanner\foo.c	\
	$(TOP_SRCDIR)\tests\scanner\drawable.c	\
	$(LDFLAGS_DLL) cairo-gobject.lib cairo.lib
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;2

# Rules for test programs
gitestrepo.exe gitestthrows.exe gitypelibtest.exe:
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\girepository $(TOP_SRCDIR)\tests\repository\$*.c $(LDFLAGS) girepository-$(GI_APIVERSION).lib
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;1

barapp.exe:
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\girepository -I$(TOP_SRCDIR)\tests $(TOP_SRCDIR)\tests\scanner\$*.c $(LDFLAGS) girepository-$(GI_APIVERSION).lib
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;1

gitestoffsets.exe: gitestoffsets.c
	$(CC) $(CFLAGS) /I$(TOP_SRCDIR)\girepository /I$(TOP_SRCDIR)\tests\offsets /I$(TOP_SRCDIR)\tests $*.c $(LDFLAGS) girepository-$(GI_APIVERSION).lib
	@-if exist $@.manifest @mt /manifest $@.manifest /outputresource:$@;1
	@set GI_TYPELIB_PATH=.
	@-$@ offsets.compiled offsets.introspected
	@-fc offsets.compiled offsets.introspected > gitestoffsets.log

# Rules for building the .gir's
GIMarshallingTests-$(GI_APIVERSION).gir: gimarshallingtests.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --warn-error --reparse-validate	\
	--namespace=GIMarshallingTests --symbol-prefix=gi_marshalling_tests --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)	\
	--add-include-path=. --include=Gio-$(GLIB_APIVERSION)	\
	--library=$* --output=$@	\
	--c-include="tests/gimarshallingtests.h"	\
	$(TOP_SRCDIR)\tests\gimarshallingtests.h $(TOP_SRCDIR)\tests\gimarshallingtests.c

Everything-$(GI_APIVERSION).gir: everything.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --warn-error --reparse-validate	\
	--namespace=Everything --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR) -I$(TOP_SRCDIR)\tests	\
	--add-include-path=. --include=Gio-$(GLIB_APIVERSION)	\
	--library=$* --output=$@	\
	everything.h everything.c

Offsets-$(GI_APIVERSION).gir: offsets.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --warn-error --reparse-validate	\
	--namespace=Offsets --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR) -I$(TOP_SRCDIR)\tests\offsets -I$(TOP_SRCDIR)\tests	\
	--pkg=gobject-$(GLIB_APIVERSION) --add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--library=$* --output=$@	\
	$(TOP_SRCDIR)\tests\offsets\offsets.h $(TOP_SRCDIR)\tests\offsets\offsets.c

SLetter-$(GI_APIVERSION).gir: sletter.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=SLetter --nsversion=$(GI_APIVERSION) \
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR)	\
	--add-include-path=. --include=Gio-$(GLIB_APIVERSION)	\
	--identifier-prefix=S --c-include="sletter.h" --warn-error	\
	--library=$* --output=$@	\
	$(TOP_SRCDIR)\tests\scanner\sletter.h $(TOP_SRCDIR)\tests\scanner\sletter.c

Utility-$(GI_APIVERSION).gir: utility.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=Utility --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR) --pkg=gobject-$(GLIB_APIVERSION)	\
	--add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--c-include="utility.h" --warn-error	\
	--library=$* --output=$@ \
	$(TOP_SRCDIR)\tests\scanner\utility.h $(TOP_SRCDIR)\tests\scanner\utility.c

GtkFrob-$(GI_APIVERSION).gir: gtkfrob.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=GtkFrob --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR) --pkg=gobject-$(GLIB_APIVERSION)	\
	--add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--identifier-prefix=Gtk --symbol-prefix=gtk_frob --warn-error	\
	--library=$* --output=$@ \
	$(TOP_SRCDIR)\tests\scanner\gtkfrob.h $(TOP_SRCDIR)\tests\scanner\gtkfrob.c

GetType-$(GI_APIVERSION).gir: gettype.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=GetType --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR) --pkg=gobject-$(GLIB_APIVERSION)	\
	--add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--c-include="gettype.h" --identifier-prefix=GetType --symbol-prefix=gettype	\
	--library=$* --output=$@ \
	$(TOP_SRCDIR)\tests\scanner\gettype.h $(TOP_SRCDIR)\tests\scanner\gettype.c

Typedefs-$(GI_APIVERSION).gir: typedefs.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=Typedefs --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR) --pkg=gobject-$(GLIB_APIVERSION)	\
	--add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--c-include="typedefs.h" --identifier-prefix=Typedefs --symbol-prefix=typedefs	\
	--library=$* --output=$@ \
	$(TOP_SRCDIR)\tests\scanner\typedefs.h $(TOP_SRCDIR)\tests\scanner\typedefs.c

WarnLib-$(GI_APIVERSION).gir: warnlib.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=WarnLib --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR)	\
	--add-include-path=. --include=Gio-$(GLIB_APIVERSION)	\
	--c-include="warnlib.h" --symbol-prefix=warnlib_	\
	--library=$* --output=$@ \
	$(TOP_SRCDIR)\tests\scanner\warnlib.h $(TOP_SRCDIR)\tests\scanner\warnlib.c

Regress-$(GI_APIVERSION).gir: Utility-$(GI_APIVERSION).gir regress.dll
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all	\
	--namespace=Regress --nsversion=$(GI_APIVERSION)	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR)	\
	--add-include-path=. --include=Gio-$(GLIB_APIVERSION)	\
	--include=Utility-$(GI_APIVERSION) --include=cairo-$(GI_APIVERSION)	\
	--c-include="regress.h" --warn-error	\
	--library=$* --output=$@	\
	$(REGRESS_CFLAGS)	\
	$(TOP_SRCDIR)\tests\scanner\regress.c $(TOP_SRCDIR)\tests\scanner\regress.h	\
	$(TOP_SRCDIR)\tests\scanner\annotation.c $(TOP_SRCDIR)\tests\scanner\annotation.h	\
	$(TOP_SRCDIR)\tests\scanner\foo.c $(TOP_SRCDIR)\tests\scanner\foo.h	\
	$(TOP_SRCDIR)\tests\scanner\drawable.c $(TOP_SRCDIR)\tests\scanner\drawable.h

Bar-$(GI_APIVERSION).gir: Utility-$(GI_APIVERSION).gir barapp.exe
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all	\
	--namespace=Bar --nsversion=$(GI_APIVERSION)	\
	--program=barapp	\
	--no-libtool -I$(TOP_SRCDIR)\tests -I$(TOP_SRCDIR) --pkg=gobject-$(GLIB_APIVERSION)	\
	--add-include-path=. --include=GObject-$(GLIB_APIVERSION)	\
	--accept-unprefixed	\
	--output=$@	\
	$(TOP_SRCDIR)\tests\scanner\barapp.c $(TOP_SRCDIR)\tests\scanner\barapp.h

Headeronly-$(GI_APIVERSION).gir:
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all	\
	--warn-error --reparse-validate --namespace=Headeronly --nsversion=$(GI_APIVERSION)	\
	--header-only --output=$@ $(TOP_SRCDIR)\tests\scanner\headeronly.h

Identfilter-$(GI_APIVERSION).gir:
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --warn-all --reparse-validate	\
	--namespace=Identfilter --accept-unprefixed --nsversion=1.0 --header-only	\
	--identifier-filter-cmd="$(PYTHON) $(TOP_SRCDIR)\tests\scanner\identfilter.py"	\
	--output=$@ $(TOP_SRCDIR)\tests\scanner\identfilter.h

# Rules for doc (Mallard) tests
Regress-$(GI_APIVERSION)-C: Regress-$(GI_APIVERSION).gir
	@-if exist $@ @rmdir /s /q $@
	$(PYTHON) $(G_IR_DOC_TOOL_CURRENT) --add-include-path=. --language C .\Regress-$(GI_APIVERSION).gir -o .\$@\

Regress-$(GI_APIVERSION)-Python: Regress-$(GI_APIVERSION).gir
	@-if exist $@ @rmdir /s /q $@
	$(PYTHON) $(G_IR_DOC_TOOL_CURRENT) --add-include-path=. --language Python .\Regress-$(GI_APIVERSION).gir -o .\$@\

Regress-$(GI_APIVERSION)-Gjs: Regress-$(GI_APIVERSION).gir
	@-if exist $@ @rmdir /s /q $@
	$(PYTHON) $(G_IR_DOC_TOOL_CURRENT) --add-include-path=. --language Gjs .\Regress-$(GI_APIVERSION).gir -o .\$@\

Regress-$(GI_APIVERSION)-sections.txt: Regress-$(GI_APIVERSION).gir
	$(PYTHON) $(G_IR_DOC_TOOL_CURRENT) --add-include-path=. --write-sections-file .\Regress-$(GI_APIVERSION).gir -o $@

# Run warn tests
warn_tests_log.txt:
	@-echo Runinng warn tests...
	@-copy GObject-$(GLIB_APIVERSION).gir $(TOP_SRCDIR)\gir
	@-copy GLib-$(GLIB_APIVERSION).gir $(TOP_SRCDIR)\gir
	@-for %a in ($(TOP_SRCDIR)\tests\warn\*.h) do if not "%a" == "$(TOP_SRCDIR)\tests\warn\common.h" $(PYTHON) $(TOP_SRCDIR)\tests\warn\warningtester.py %a >> $@
	@-del $(TOP_SRCDIR)\gir\GObject-$(GLIB_APIVERSION).gir
	@-del $(TOP_SRCDIR)\gir\GLib-$(GLIB_APIVERSION).gir

# Rules for source code generation
everything.c everything.h:
	$(PYTHON) $(G_IR_SCANNER_CURRENT) -I$(TOP_SRCDIR) \
	--generate-typelib-tests=Everything,everything.h,everything.c	\
	--function-decoration=_GI_TEST_EXTERN	\
	--include-first-in-src=config.h	\
	--include-last-in-header=gitestmacros.h

gitestoffsets.c: Offsets-$(GI_APIVERSION).typelib
	$(PYTHON) $(TOP_SRCDIR)\tests\offsets\gen-gitestoffsets $(TOP_SRCDIR)\tests\offsets\offsets.h > $@

# Generate .typelib's from generated .gir's
$(built_test_typelibs): $(built_test_girs)
	@-echo Compiling $*.typelib...
	@-$(G_IR_COMPILER_CURRENT) --includedir=. --debug --verbose $*.gir -o $@

!else
all: install-introspection

install-introspection:
	@-echo $(ERROR_MSG)
!endif

clean:
	@-del /f/q warn_tests_log.txt
	@-del /f/q gitestoffsets.log
	@-del /f/q Regress-$(GI_APIVERSION)-sections.txt
	@-rmdir /s /q Regress-$(GI_APIVERSION)-Gjs
	@-rmdir /s /q Regress-$(GI_APIVERSION)-Python
	@-rmdir /s /q Regress-$(GI_APIVERSION)-C
	@-for %a in ($(built_test_typelibs)) do @del %a
	@-for %a in ($(built_test_girs)) do @del %a
	@-del /f/q *.lib
	@-del /f/q *.exp
	@-del /f/q *.dll
	@-del /f/q *.exe
	@-for %a in (*.manifest) do @del /f/q %a
	@-del /f/q *.pdb
	@-del /f/q *.obj
	@-del /f/q everything.c everything.h gitestoffsets.c
	@-del offsets.compiled offsets.introspected
	@-del /f/q *.pyc
