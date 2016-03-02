# NMake Makefile to build Introspection Files for G-I

# Change or pass in as a variable/env var if needed
# The main DLLs that are used to build introspection files that are "installed"
!if "$(CAIROGOBJECT_DLLNAME)" == ""
!if "$(USE_LIBTOOL_NAME)" == "1"
CAIROGOBJECT_DLLNAME = libcairo-gobject-2.dll
!else
CAIROGOBJECT_DLLNAME = cairo-gobject-vs$(VSVER).dll
!endif
!endif

# Please do not change anything after this line

!include gi-build-common-msvc.mak

# The .gir's that are in $(srcroot)/gir, applicable to Windows
# cairo-1.0.gir is not listed as it needs to be processed first
bundled_girs =	\
	win32-1.0.gir	\
	fontconfig-2.0.gir	\
	freetype2-2.0.gir	\
	GL-1.0.gir	\
	libxml2-2.0.gir

# The .typelib's that are build from the .gir's bundled with the
# G-I package, applicable to Windows
bundled_typelibs =	\
	cairo-1.0.typelib	\
	fontconfig-2.0.typelib	\
	freetype2-2.0.typelib	\
	GL-1.0.typelib	\
	libxml2-2.0.typelib	\
	win32-1.0.typelib

# The .gir's for GLib/G-I that are built and "installed"
built_install_girs =	\
	GLib-$(GLIB_APIVERSION).gir	\
	GModule-$(GLIB_APIVERSION).gir	\
	GObject-$(GLIB_APIVERSION).gir	\
	Gio-$(GLIB_APIVERSION).gir	\
	GIRepository-$(GLIB_APIVERSION).gir

# The .typelib's for GLib/G-I that are built and "installed"
built_install_typelibs =	\
	GLib-$(GLIB_APIVERSION).typelib	\
	GModule-$(GLIB_APIVERSION).typelib	\
	GObject-$(GLIB_APIVERSION).typelib	\
	Gio-$(GLIB_APIVERSION).typelib	\
	GIRepository-$(GLIB_APIVERSION).typelib

!if "$(BUILD_INTROSPECTION)" == "TRUE"
all: setgirbuildenv $(built_install_girs) $(built_install_typelibs) $(bundled_girs) $(bundled_typelibs) msg_cairo

!include gi-setenv-msvc.mak

glib_list:
	@-echo Generating file list for GLib...
	@-echo $(PREFIX)\lib\glib-2.0\include\glibconfig.h> $@
	@-for /f %%a in ('dir /b $(PREFIX)\include\glib-2.0\glib\*.h') do @echo $(PREFIX)\include\glib-2.0\glib\%%a>> $@
	@-echo $(PREFIX)\include\glib-2.0\gobject\glib-types.h>> $@
	@-echo $(TOP_SRCDIR)\gir\glib-2.0.c>> $@

gobject_list:
	@-echo Generating file list for GObject...
	@-type NUL > $@
	@-for /f %%a in ('dir /b $(PREFIX)\include\glib-2.0\gobject\*.h') do @if not %%a == glib-types.h @echo $(PREFIX)\include\glib-2.0\gobject\%%a>> $@
	@-echo $(TOP_SRCDIR)\gir\gobject-2.0.c>> $@

gio_list:
	@-echo Generating file list for GIO...
	@-type NUL > $@
	@-for /f %%a in ('dir /b $(PREFIX)\include\gio-win32-2.0\gio\*.h') do @echo $(PREFIX)\include\gio-win32-2.0\gio\%%a>> $@
	@-for /f %%a in ('dir /b $(PREFIX)\include\glib-2.0\gio\*.h') do @if not %%a == gsettingsbackend.h @echo $(PREFIX)\include\glib-2.0\gio\%%a>> $@
	@-echo $(TOP_SRCDIR)\gir\gio-2.0.c>> $@

gi_list:
	@-echo Generating file list for girepository...
	@-echo $(TOP_SRCDIR)\girepository\girepository.h > $@
	@-echo $(TOP_SRCDIR)\girepository\girepository.c >> $@
	@-for /f %%a in ('dir /b $(TOP_SRCDIR)\girepository\gi*info.c') do @echo $(TOP_SRCDIR)\girepository\%%a >> $@
	@-for /f %%a in ('dir /b $(TOP_SRCDIR)\girepository\gi*info.h') do @echo $(TOP_SRCDIR)\girepository\%%a >> $@
	@-echo $(TOP_SRCDIR)\girepository\gitypelib.h >> $@
	@-echo $(TOP_SRCDIR)\girepository\gitypes.h >> $@

# Generated .gir files for GLib/GModule/GObject/Gio/GIRepository
GLib-$(GLIB_APIVERSION).gir: glib_list
	@-echo Generating $@...
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --verbose -I$(TOP_SRCDIR) --add-include-path=$(TOP_SRCDIR)	\
	--add-include-path=$(TOP_SRCDIR)\gir --add-include-path=. --namespace=GLib --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --pkg=gio-windows-$(GLIB_APIVERSION) --pkg=glib-$(GLIB_APIVERSION)	\
	--include=win32-$(GI_APIVERSION) --library=glib-2.0 --library=gobject-2.0	\
	--external-library --reparse-validate --identifier-prefix=G --symbol-prefix=g	\
	--symbol-prefix=glib --c-include="glib.h" -I$(PREFIX)\include\glib-$(GLIB_APIVERSION)	\
	-I$(PREFIX)\lib\glib-2.0\include -I$(PREFIX)\include -DGETTEXT_PACKAGE=Dummy	\
	-DGLIB_COMPILATION -D__G_I18N_LIB_H__ --filelist=glib_list -o $@

GModule-$(GLIB_APIVERSION).gir: GLib-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --verbose -I$(TOP_SRCDIR) --add-include-path=$(TOP_SRCDIR)	\
	--add-include-path=$(TOP_SRCDIR)\gir --add-include-path=. --namespace=GModule --nsversion=2.0	\
	--no-libtool --include=GLib-$(GLIB_APIVERSION) --pkg=gmodule-$(GLIB_APIVERSION) --library=gmodule-2.0	\
	--external-library --reparse-validate --identifier-prefix=G --c-include="gmodule.h"	\
	-I$(PREFIX)\include\glib-2.0 -I$(PREFIX)\lib\glib-2.0\include -I$(PREFIX)\include	\
	$(PREFIX)\include\glib-2.0\gmodule.h $(TOP_SRCDIR)\gir\gmodule-2.0.c -o $@

GObject-$(GLIB_APIVERSION).gir: gobject_list GModule-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --verbose -I$(TOP_SRCDIR) --add-include-path=$(TOP_SRCDIR)	\
	--add-include-path=$(TOP_SRCDIR)\gir --add-include-path=. --namespace=GObject --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --include=GLib-$(GLIB_APIVERSION) --pkg=gobject-$(GLIB_APIVERSION) --library=gobject-2.0	\
	--external-library --reparse-validate --identifier-prefix=G --c-include="glib-gobject.h"	\
	-I$(PREFIX)/include/glib-2.0 -I$(PREFIX)/lib/glib-2.0/include -I$(PREFIX)/include	\
	-DGOBJECT_COMPILATION --filelist=gobject_list -o $@

Gio-$(GLIB_APIVERSION).gir: gio_list GObject-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --verbose -I$(TOP_SRCDIR) --add-include-path=$(TOP_SRCDIR)	\
	--add-include-path=$(TOP_SRCDIR)\gir --add-include-path=. --namespace=Gio --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --pkg=gio-$(GLIB_APIVERSION) --pkg=gio-windows-$(GLIB_APIVERSION) --include=GObject-$(GLIB_APIVERSION)	\
	--library=gio-2.0 --external-library --reparse-validate --warn-all	\
	--identifier-prefix=G --include=GLib-$(GLIB_APIVERSION) --c-include="gio/gio.h" -DGIO_COMPILATION	\
	-I$(PREFIX)\include\glib-2.0 -I$(PREFIX)\lib\glib-2.0\include	\
	-I$(PREFIX)\include --filelist=gio_list -o $@

GIRepository-$(GLIB_APIVERSION).gir: gi_list GObject-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON) $(G_IR_SCANNER_CURRENT) --verbose --warn-all	\
	--add-include-path=$(TOP_SRCDIR)\gir --add-include-path=. --namespace=GIRepository --nsversion=$(GLIB_APIVERSION)	\
	--identifier-prefix=GI --symbol-prefix=g --c-include="girepository.h" --add-include-path=.	\
	--no-libtool --pkg=gobject-$(GLIB_APIVERSION) --include=GObject-$(GLIB_APIVERSION)	\
	--library=girepository-1.0 -I$(TOP_SRCDIR)\girepository -I$(TOP_SRCDIR) -I$(PREFIX)\include 	\
	-I$(PREFIX)\include\glib-2.0 -I$(PREFIX)\lib\glib-2.0\include --filelist=gi_list	\
	-DGI_COMPILATION -o $@

# Bundled cairo-1.0.gir.in processing
cairo-1.0.gir: $(TOP_SRCDIR)\gir\cairo-1.0.gir.in
	@-echo Generating $@ from $*.gir.in...
	@-$(PYTHON) gen-win32-cairo-gir.py --dllname=$(CAIROGOBJECT_DLLNAME)

# Copy the .gir's bundled with G-I to this folder
$(bundled_girs): $(TOP_SRCDIR)\gir\win32-1.0.gir $(TOP_SRCDIR)\gir\fontconfig-2.0.gir $(TOP_SRCDIR)\gir\freetype2-2.0.gir $(TOP_SRCDIR)\gir\GL-1.0.gir $(TOP_SRCDIR)\gir\libxml2-2.0.gir
	@-echo Copying the bundled $*.gir that came with the GobjectIntrospection package...
	@-copy $(TOP_SRCDIR)\gir\$*.gir $@

# Generate .typelib's from generated .gir's
$(built_install_typelibs): $(bundled_girs) $(built_install_girs)
	@-echo Compiling $*.typelib...
	@-$(G_IR_COMPILER_CURRENT) --includedir=. --debug --verbose $*.gir -o $@

# Generate .typelib's from bundled .gir's
$(bundled_typelibs): cairo-1.0.gir $(bundled_girs)
	@-echo Compiling the bundled $*.gir that came with the GobjectIntrospection package...
	@-$(G_IR_COMPILER_CURRENT) --includedir=. --debug --verbose $*.gir -o $@

msg_cairo:
	@-echo.
	@-echo ************* Note ***********************************
	@-echo The cairo-1.0.gir links to $(CAIROGOBJECT_DLLNAME),
	@-echo please ensure that this is the correct DLL where the
	@-echo cairo-gobject symbols can be loaded, which needs to
	@-echo found when running programs or scripts that would
	@-echo be using cairo-1.0.typelib.
	@-echo.
	@-echo If not, please clean the build and redo the build
	@-echo specifying the correct DLL by passing in
	@-echo CAIROGOBJECT_DLLNAME^=^<your DLL full filename^> when
	@-echo invoking this NMake Makefile

install-introspection: all
	@-mkdir $(G_IR_INCLUDEDIR)
	@-mkdir $(G_IR_TYPELIBDIR)
	@-copy cairo-1.0.gir $(G_IR_INCLUDEDIR)
	@-for %a in ($(built_install_girs)) do @copy %a $(G_IR_INCLUDEDIR)
	@-for %b in ($(built_install_typelibs)) do @copy %b $(G_IR_TYPELIBDIR)
	@-for %c in ($(bundled_girs)) do @copy %c $(G_IR_INCLUDEDIR)
	@-for %d in ($(bundled_typelibs)) do @copy %d $(G_IR_TYPELIBDIR)

!else
all: install-introspection

install-introspection:
	@-echo $(ERROR_MSG)
!endif

clean:
	@-del /f/q *.typelib
	@-del /f/q *.gir
	@-del /f/q gi_list
	@-del /f/q gio_list
	@-del /f/q gobject_list
	@-del /f/q glib_list
	@ if exist __pycache__ rmdir /s /q __pycache__
	@-del /f/q *.pyc
