# NMake Makefile to build Introspection Files for G-I

# Change or pass in as a variable/env var if needed
# The main DLLs that are used to build introspection files that are "installed"
GI_DLLNAME = girepository-1-vs$(VSVER)
GLIB_DLLNAME = glib-2-vs$(VSVER)
GMODULE_DLLNAME = gmodule-2-vs$(VSVER)
GOBJECT_DLLNAME = gobject-2-vs$(VSVER)
GIO_DLLNAME = gio-2-vs$(VSVER)
CAIROGOBJECT_DLLNAME= cairo-gobject-vs$(VSVER)

# Please do not change anything after this line

!include detectenv_msvc.mak

GI_APIVERSION = 1.0
GLIB_APIVERSION = 2.0

CHECK_PACKAGE = gio-$(GLIB_APIVERSION)

!include introspection-msvc.mak

BINDIR = ..\build\win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin
G_IR_SCANNER_CURRENT = ..\tools\g-ir-scanner
G_IR_COMPILER_CURRENT = $(BINDIR)\g-ir-compiler.exe

!if "$(PLAT)" == "x64"
TIME_T_DEFINE = -Dtime_t=long long
!else
TIME_T_DEFINE = -Dtime_t=long
!endif

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

!include introspection-msvc.mak

!if "$(BUILD_INTROSPECTION)" == "TRUE"
all: setgirbuildnev $(built_install_girs) $(built_install_typelibs) $(bundled_girs) $(bundled_typelibs)

setgirbuildnev:
	@set CC=$(CC)
	@set PYTHONPATH=..;$(BINDIR)
	@set PATH=$(BINDIR);$(BASEDIR)\bin;$(PATH);$(MINGWDIR)\bin
	@set PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)
	@set LIB=win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin;$(BASEDIR)\lib;$(LIB)
	@set UNINSTALLED_INTROSPECTION_SRCDIR=..

glib_list:
	@-echo Generating file list for GLib...
	@-echo $(BASEDIR)\lib\glib-2.0\include\glibconfig.h> $@
	@-for /f %%a in ('dir /b $(BASEDIR)\include\glib-2.0\glib\*.h') do @echo $(BASEDIR)\include\glib-2.0\glib\%%a>> $@
	@-echo $(BASEDIR)\include\glib-2.0\gobject\glib-types.h>> $@
	@-echo ..\gir\glib-2.0.c>> $@

gobject_list:
	@-echo Generating file list for GObject...
	@-type NUL > $@
	@-for /f %%a in ('dir /b $(BASEDIR)\include\glib-2.0\gobject\*.h') do @if not %%a == glib-types.h @echo $(BASEDIR)\include\glib-2.0\gobject\%%a>> $@
	@-echo ..\gir\gobject-2.0.c>> $@

gio_list:
	@-echo Generating file list for GIO...
	@-type NUL > $@
	@-for /f %%a in ('dir /b $(BASEDIR)\include\gio-win32-2.0\gio\*.h') do @echo $(BASEDIR)\include\gio-win32-2.0\gio\%%a>> $@
	@-for /f %%a in ('dir /b $(BASEDIR)\include\glib-2.0\gio\*.h') do @if not %%a == gsettingsbackend.h @echo $(BASEDIR)\include\glib-2.0\gio\%%a>> $@
	@-echo ..\gir\gio-2.0.c>> $@

gi_list:
	@-echo Generating file list for girepository...
	@-echo ..\girepository\girepository.h > $@
	@-echo ..\girepository\girepository.c >> $@
	@-for /f %%a in ('dir /b ..\girepository\gi*info.c') do @echo ..\girepository\%%a >> $@
	@-for /f %%a in ('dir /b ..\girepository\gi*info.h') do @echo ..\girepository\%%a >> $@
	@-echo ..\girepository\gitypelib.h >> $@
	@-echo ..\girepository\gitypes.h >> $@

# Make a copy of girepository-1.0.lib to girepository-2.0.lib for use
# during the linking stage of the dump binary, in the generation
# of GIRepository-2.0.gir (the resulting binary will still be
# linked and referring to the original girepository DLL)
win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin\girepository-$(GLIB_APIVERSION).lib: win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin\girepository-$(GI_APIVERSION).lib
	@-copy /b win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin\girepository-$(GI_APIVERSION).lib $@

# Generated .gir files for GLib/GModule/GObject/Gio/GIRepository
GLib-$(GLIB_APIVERSION).gir: glib_list
	@-echo Generating $@...
	$(PYTHON2) $(G_IR_SCANNER_CURRENT) --verbose -I.. --add-include-path=..	\
	--add-include-path=..\gir --add-include-path=. --namespace=GLib --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --pkg=glib-$(GLIB_APIVERSION) --include=win32-$(GI_APIVERSION) --library=$(GLIB_DLLNAME) --library=$(GOBJECT_DLLNAME)	\
	--external-library --reparse-validate --identifier-prefix=G --symbol-prefix=g	\
	--symbol-prefix=glib --c-include="glib.h" -I$(BASEDIR)\include\glib-$(GLIB_APIVERSION)	\
	-I$(BASEDIR)\lib\glib-2.0\include -I$(BASEDIR)\include -DGETTEXT_PACKAGE=Dummy	\
	-DGLIB_COMPILATION -D__G_I18N_LIB_H__ --filelist=glib_list -o $@

GModule-$(GLIB_APIVERSION).gir: GLib-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON2) $(G_IR_SCANNER_CURRENT) --verbose -I.. --add-include-path=..	\
	--add-include-path=..\gir --add-include-path=. --namespace=GModule --nsversion=2.0	\
	--no-libtool --include=GLib-$(GLIB_APIVERSION) --pkg=gmodule-$(GLIB_APIVERSION) --library=$(GMODULE_DLLNAME)	\
	--external-library --reparse-validate --identifier-prefix=G --c-include="gmodule.h"	\
	-I$(BASEDIR)\include\glib-2.0 -I$(BASEDIR)\lib\glib-2.0\include -I$(BASEDIR)\include	\
	$(BASEDIR)\include\glib-2.0\gmodule.h ..\gir\gmodule-2.0.c -o $@

GObject-$(GLIB_APIVERSION).gir: gobject_list GModule-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON2) $(G_IR_SCANNER_CURRENT) --verbose -I.. --add-include-path=..	\
	--add-include-path=..\gir --add-include-path=. --namespace=GObject --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --include=GLib-$(GLIB_APIVERSION) --pkg=gobject-$(GLIB_APIVERSION) --library=$(GOBJECT_DLLNAME)	\
	--external-library --reparse-validate --identifier-prefix=G --c-include="glib-gobject.h"	\
	-I$(BASEDIR)/include/glib-2.0 -I$(BASEDIR)/lib/glib-2.0/include -I$(BASEDIR)/include	\
	-DGOBJECT_COMPILATION --filelist=gobject_list -o $@

Gio-$(GLIB_APIVERSION).gir: gio_list GObject-$(GLIB_APIVERSION).gir
	@-echo Generating $@...
	$(PYTHON2) $(G_IR_SCANNER_CURRENT) --verbose -I.. --add-include-path=..	\
	--add-include-path=..\gir --add-include-path=. --namespace=Gio --nsversion=$(GLIB_APIVERSION)	\
	--no-libtool --pkg=gio-$(GLIB_APIVERSION) --pkg=gio-windows-$(GLIB_APIVERSION) --include=GObject-$(GLIB_APIVERSION)	\
	--library=$(GIO_DLLNAME) --external-library --reparse-validate --warn-all	\
	--identifier-prefix=G --include=GLib-$(GLIB_APIVERSION) --c-include="gio/gio.h" -DGIO_COMPILATION	\
	-I$(BASEDIR)\include\glib-2.0 -I$(BASEDIR)\lib\glib-2.0\include	\
	-I$(BASEDIR)\include --filelist=gio_list -o $@

GIRepository-$(GLIB_APIVERSION).gir: gi_list GObject-$(GLIB_APIVERSION).gir win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin\girepository-$(GLIB_APIVERSION).lib
	@-echo Generating $@...
	$(PYTHON2) $(G_IR_SCANNER_CURRENT) --verbose --warn-all	\
	--add-include-path=..\gir --add-include-path=. --namespace=GIRepository --nsversion=$(GLIB_APIVERSION)	\
	--identifier-prefix=GI --symbol-prefix=g --c-include="girepository.h" --add-include-path=.	\
	--no-libtool --pkg=gobject-$(GLIB_APIVERSION) --include=GObject-$(GLIB_APIVERSION)	\
	--library=$(GI_DLLNAME) -I..\girepository -I.. -I%BASEDIR%\include 	\
	-I%BASEDIR%\include\glib-2.0 -I%BASEDIR%\lib\glib-2.0\include --filelist=gi_list	\
	-DGI_COMPILATION -o $@

# Bundled cairo-1.0.gir.in processing
cairo-1.0.gir: ..\gir\cairo-1.0.gir.in
	@-echo Generating and copying $@ from $*.gir.in...
	@-if not exist ..\gir\$*.gir $(PYTHON2) gen-cairo-gir.py --dllname=$(CAIROGOBJECT_DLLNAME).dll
	@-copy ..\gir\$*.gir $@

# Copy the .gir's bundled with G-I to this folder
$(bundled_girs): ..\gir\win32-1.0.gir ..\gir\fontconfig-2.0.gir ..\gir\freetype2-2.0.gir ..\gir\GL-1.0.gir ..\gir\libxml2-2.0.gir
	@-echo Copying the bundled $*.gir that came with the GobjectIntrospection package...
	@-copy ..\gir\$*.gir $@

# Generate .typelib's from generated .gir's
$(built_install_typelibs): $(built_install_girs)
	@-echo Compiling $*.typelib...
	@-$(G_IR_COMPILER_CURRENT) --includedir=. --debug --verbose $*.gir -o $@

# Generate .typelib's from bundled .gir's
$(bundled_typelibs): cairo-1.0.gir $(bundled_girs)
	@-echo Compiling the bundled $*.gir that came with the GobjectIntrospection package...
	@-$(G_IR_COMPILER_CURRENT) --includedir=. --debug --verbose $*.gir -o $@

install-introspection: setgirbuildnev $(built_install_girs) $(built_install_typelibs) $(bundled_girs) cairo-1.0.gir $(bundled_typelibs)
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
	@-del /f/q ..\gir\cairo-$(GI_APIVERSION).gir
	@-del /f/q *.typelib
	@-del /f/q *.gir
	@-del /f/q win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin\girepository-$(GLIB_APIVERSION).lib
	@-del /f/q gi_list
	@-del /f/q gio_list
	@-del /f/q gobject_list
	@-del /f/q glib_list
	@-del /f/q *.pyc
