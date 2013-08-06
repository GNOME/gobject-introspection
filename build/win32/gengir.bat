@echo off

setlocal EnableDelayedExpansion

rem Needed environmental variables:
rem PLAT: Windows platform-Win32 (i.e. x86) or x64 (i.e. x86-64)
rem CONF: Configuration Type, Release or Debug
rem VSVER: Visual C++ version used

rem Check the environemental variables...
if /i "%PLAT%" == "Win32" goto PLAT_OK
if /i "%PLAT%" == "x64" goto PLAT_OK
if /i "%PLAT%" == "x86" (
   set PLAT=Win32
   goto PLAT_OK
)
if /i "%PLAT%" == "x86-64" (
   set PLAT=x64
   goto PLAT_OK
)
goto ERR_PLAT
:PLAT_OK
if %VSVER% == 9 goto VSVER_OK
if %VSVER% == 10 goto VSVER_OK
if %VSVER% == 11 goto VSVER_OK
goto ERR_VSVER
:VSVER_OK
if /i "%CONF%" == "Release" goto CONF_OK
if /i "%CONF%" == "Debug" goto CONF_OK
goto ERR_CONF
:CONF_OK
if "%BASEDIR%" == "" goto ERR_BASEDIR
if not exist %BASEDIR% goto ERR_BASEDIR


set BINDIR=..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\bin
set PATH=%BINDIR%;%PATH%
set PYTHONPATH=..\..;%BINDIR%

set UNINSTALLED_INTROSPECTION_SRCDIR=..\..
echo Setup .bat for generating GLib .gir's...

rem =====================================================
rem Feed the "installed" GLib headers into a listing file
rem =====================================================
echo %BASEDIR%\lib\glib-2.0\include\glibconfig.h> glib_list
for /f %%a in ('dir /b %BASEDIR%\include\glib-2.0\glib\*.h') do (
   echo %BASEDIR%\include\glib-2.0\glib\%%a>> glib_list
)
echo %BASEDIR%\include\glib-2.0\gobject\glib-types.h>> glib_list
echo ..\..\gir\glib-2.0.c>> glib_list

rem ========================================================
rem Feed the "installed" GObject headers into a listing file
rem ========================================================

if exist gobject_list del gobject_list
for /f %%a in ('dir /b %BASEDIR%\include\glib-2.0\gobject\*.h') do (
   if not %%a == glib-types.h (
      echo %BASEDIR%\include\glib-2.0\gobject\%%a>> gobject_list
   )
)
echo ..\..\gir\gobject-2.0.c>> gobject_list

rem =====================================================
rem Feed the "installed" Gio headers into a listing file
rem =====================================================

for /f %%a in ('dir /b %BASEDIR%\include\gio-win32-2.0\gio\*.h') do (
   echo %BASEDIR%\include\gio-win32-2.0\gio\%%a> gio_list
)

for /f %%a in ('dir /b %BASEDIR%\include\glib-2.0\gio\*.h') do (
   if not %%a == gsettingsbackend.h (
      echo %BASEDIR%\include\glib-2.0\gio\%%a>> gio_list
   )
)
echo ..\..\gir\gio-2.0.c>> gio_list

rem =================================================================================================
rem Begin setup of glib_gir.bat to create GLib-2.0.gir
rem (The ^^ is necessary to span the command to multiple lines on Windows cmd.exe!)
rem =================================================================================================

echo echo Generating GLib-2.0.gir...> glib_gir.bat
echo @echo on>> glib_gir.bat
echo.>> glib_gir.bat
rem ================================================================
rem Setup the command line flags to g-ir-scanner for GLib-2.0.gir...
rem ================================================================
echo python ..\..\tools\g-ir-scanner --verbose -I..\.. --add-include-path=..\.. ^^>> glib_gir.bat
echo --add-include-path=..\..\gir --add-include-path=. --namespace=GLib --nsversion=2.0 ^^>> glib_gir.bat
echo --no-libtool --pkg=glib-2.0 --include=win32-1.0 --library=glib-2-vs%VSVER% --library=gobject-2-vs%VSVER% ^^>> glib_gir.bat
echo --external-library --reparse-validate --identifier-prefix=G --symbol-prefix=g ^^>> glib_gir.bat
echo --symbol-prefix=glib --c-include="glib.h" -I%BASEDIR%\include\glib-2.0 ^^>> glib_gir.bat
echo -I%BASEDIR%\lib\glib-2.0\include -I%BASEDIR%\include -DGETTEXT_PACKAGE=Dummy ^^>> glib_gir.bat
echo -DGLIB_COMPILATION -D__G_I18N_LIB_H__ ^^>> glib_gir.bat
echo --filelist=glib_list ^^>> glib_gir.bat
echo -o GLib-2.0.gir>> glib_gir.bat
echo.>> glib_gir.bat

echo Completed setup of .bat for generating GLib-2.0.gir.
echo.>> glib_gir.bat

rem ===================================================
rem Finish setup of glib_gir.bat to create GLib-2.0.gir
rem ===================================================

rem ====================================================================
rem Next, begin the setup for the glib_gir.bat to create GModule-2.0.gir
rem ====================================================================
echo echo Generating GModule-2.0.gir...>> glib_gir.bat
echo.>> glib_gir.bat

rem ===================================================================
rem Setup the command line flags to g-ir-scanner for GModule-2.0.gir...
rem ===================================================================

echo python ..\..\tools\g-ir-scanner --verbose -I..\.. --add-include-path=..\.. ^^>> glib_gir.bat
echo --add-include-path=..\..\gir --add-include-path=. --namespace=GModule --nsversion=2.0 ^^>> glib_gir.bat
echo --no-libtool --include=GLib-2.0 --pkg=gmodule-2.0 --library=gmodule-2-vs%VSVER% ^^>> glib_gir.bat
echo --external-library --reparse-validate --identifier-prefix=G --c-include="gmodule.h" ^^>> glib_gir.bat
echo -I%BASEDIR%\include\glib-2.0 -I%BASEDIR%\lib\glib-2.0\include -I%BASEDIR%\include ^^>> glib_gir.bat
echo %BASEDIR%\include\glib-2.0\gmodule.h -o GModule-2.0.gir>> glib_gir.bat
echo.>> glib_gir.bat

echo Completed setup of .bat for generating GModule-2.0.gir.
echo.>> glib_gir.bat

rem ======================================================
rem Finish setup of glib_gir.bat to create GModule-2.0.gir
rem ======================================================

rem ====================================================================
rem Next, begin the setup for the glib_gir.bat to create GObject-2.0.gir
rem ====================================================================

echo echo Generating GObject-2.0.gir...>> glib_gir.bat
echo.>> glib_gir.bat

rem ===================================================================
rem Setup the command line flags to g-ir-scanner for GObject-2.0.gir...
rem ===================================================================

echo python ..\..\tools\g-ir-scanner --verbose -I..\.. --add-include-path=..\.. ^^>> glib_gir.bat
echo --add-include-path=..\..\gir --add-include-path=. --namespace=GObject --nsversion=2.0 ^^>> glib_gir.bat
echo --no-libtool --include=GLib-2.0 --pkg=gobject-2.0 --library=gobject-2-vs%VSVER% ^^>> glib_gir.bat
echo --external-library --reparse-validate --identifier-prefix=G --c-include="glib-gobject.h" ^^>> glib_gir.bat
echo -I%BASEDIR%/include/glib-2.0 -I%BASEDIR%/lib/glib-2.0/include -I%BASEDIR%/include ^^>> glib_gir.bat
echo -DGOBJECT_COMPILATION ^^>> glib_gir.bat
echo --filelist=gobject_list -o GObject-2.0.gir>> glib_gir.bat
echo.>> glib_gir.bat

echo Completed setup of .bat for generating GObject-2.0.gir.
echo.>> glib_gir.bat
rem ======================================================
rem Finish setup of glib_gir.bat to create GObject-2.0.gir
rem ======================================================

rem ================================================================
rem Next, begin the setup for the glib_gir.bat to create Gio-2.0.gir
rem ================================================================
echo echo Generating Gio-2.0.gir...>> glib_gir.bat
echo.>> glib_gir.bat

rem ===============================================================
rem Setup the command line flags to g-ir-scanner for Gio-2.0.gir...
rem ===============================================================
echo python ..\..\tools\g-ir-scanner --verbose -I..\.. --add-include-path=..\.. ^^>> glib_gir.bat
echo --add-include-path=..\..\gir --add-include-path=. --namespace=Gio --nsversion=2.0 ^^>> glib_gir.bat
echo --no-libtool --pkg=gio-2.0 --pkg=gio-windows-2.0 --include=GObject-2.0 ^^>> glib_gir.bat
echo --library=gio-2-vs%VSVER% --external-library --reparse-validate --warn-all ^^>> glib_gir.bat
echo --identifier-prefix=G --include=GLib-2.0 --c-include="gio/gio.h" -DGIO_COMPILATION ^^>> glib_gir.bat
echo -I%BASEDIR%\include\glib-2.0 -I%BASEDIR%\lib\glib-2.0\include ^^>> glib_gir.bat
echo -I%BASEDIR%\include ^^>> glib_gir.bat
echo --filelist=gio_list ^^>> glib_gir.bat
echo -o Gio-2.0.gir>> glib_gir.bat
echo.>> glib_gir.bat

echo Completed setup of .bat for generating Gio-2.0.gir.
echo.>> glib_gir.bat
rem ==================================================
rem Finish setup of glib_gir.bat to create Gio-2.0.gir
rem ==================================================

rem =========================================================================
rem Next, begin the setup for the glib_gir.bat to create GIRepository-2.0.gir
rem =========================================================================
copy /b %BINDIR%\girepository-1.0.lib %BINDIR%\girepository-2.0.lib
echo echo Generating GIRepository-2.0.gir...>> glib_gir.bat
echo.>> glib_gir.bat

rem ========================================================================
rem Setup the command line flags to g-ir-scanner for GIRepository-2.0.gir...
rem ========================================================================
echo python ..\..\tools\g-ir-scanner --verbose --warn-all ^^>> glib_gir.bat
echo --add-include-path=..\..\gir --add-include-path=. --namespace=GIRepository --nsversion=2.0 ^^>> glib_gir.bat
echo --identifier-prefix=GI --symbol-prefix=g --c-include="girepository.h" --add-include-path=. ^^>> glib_gir.bat
echo --no-libtool --pkg=gobject-2.0 --include=GObject-2.0 ^^>> glib_gir.bat
echo --library=girepository-1-vs%VSVER% -I..\..\girepository -I..\.. -I%BASEDIR%\include  ^^>> glib_gir.bat
echo -I%BASEDIR%\include\glib-2.0 -I%BASEDIR%\lib\glib-2.0\include -DGI_COMPILATION ^^>> glib_gir.bat
echo ..\..\girepository\girepository.h ^^>> glib_gir.bat
echo ..\..\girepository\girepository.c ^^>> glib_gir.bat

for /f %%a in ('dir /b ..\..\girepository\gi*info.c') do (
   echo ..\..\girepository\%%a ^^>> glib_gir.bat
)

for /f %%a in ('dir /b ..\..\girepository\gi*info.h') do (
   echo ..\..\girepository\%%a ^^>> glib_gir.bat
)

echo ..\..\girepository\gitypelib.h ^^>> glib_gir.bat
echo ..\..\girepository\gitypes.h ^^>> glib_gir.bat
echo -o GIRepository-2.0.gir>> glib_gir.bat
echo.>> glib_gir.bat

echo Completed setup of .bat for generating GIRepository-2.0.gir.
echo.>> glib_gir.bat
rem ===========================================================
rem Finish setup of glib_gir.bat to create GIRepository-2.0.gir
rem ===========================================================

rem =======================
rem Now generate the .gir's
rem =======================
CALL glib_gir.bat

@echo off
rem =======
rem Cleanup
rem =======
rem del %BINDIR%\girepository-2.0.lib
del gio_list
del gobject_list
del glib_list
del glib_gir.bat
goto DO_COMPILE_GIR
:ERR_PLAT
echo You need to specify a valid Platform [set PLAT=Win32 or PLAT=x64]
goto DONE
:ERR_VSVER
echo You need to specify your Visual Studio version [set VSVER=9 or VSVER=10 or VSVER=11]
goto DONE
:ERR_CONF
echo You need to specify a valid Configuration [set CONF=Release or CONF=Debug]
goto DONE
:ERR_BASEDIR
echo You need to specify a valid BASEDIR.
goto DONE
:DO_COMPILE_GIR
rem Now compile the generated .gir files
g-ir-compiler --includedir=. --includedir=..\..\gir --debug --verbose GLib-2.0.gir -o GLib-2.0.typelib
g-ir-compiler --includedir=. --includedir=..\..\gir --debug --verbose GModule-2.0.gir -o GModule-2.0.typelib
g-ir-compiler --includedir=. --includedir=..\..\gir --debug --verbose GObject-2.0.gir -o GObject-2.0.typelib
g-ir-compiler --includedir=. --includedir=..\..\gir --debug --verbose Gio-2.0.gir -o Gio-2.0.typelib
g-ir-compiler --includedir=. --includedir=..\..\gir --debug --verbose GIRepository-2.0.gir -o GIRepository-2.0.typelib

rem Now process the bundled .gir files
python create_nonglib_gir.py --vsver=%VSVER%
set CURRDIR=%CD%
cd ..\..\gir
g-ir-compiler --includedir=. --debug --verbose cairo-1.0.gir -o cairo-1.0.typelib
g-ir-compiler --includedir=. --debug --verbose freetype2-2.0.gir -o freetype2-2.0.typelib
g-ir-compiler --includedir=. --debug --verbose GL-1.0.gir -o GL-1.0.typelib
g-ir-compiler --includedir=. --debug --verbose libxml2-2.0.gir -o libxml2-2.0.typelib
g-ir-compiler --includedir=. --debug --verbose win32-1.0.gir -o win32-1.0.typelib
cd %CURRDIR%

rem Copy the generated .girs and .typelibs to their appropriate places

mkdir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0
move /y *.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\
copy /y ..\..\gir\freetype2-2.0.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\
copy /y ..\..\gir\GL-1.0.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\
copy /y ..\..\gir\libxml2-2.0.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\
copy /y ..\..\gir\cairo-1.0.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\
copy /y ..\..\gir\win32-1.0.gir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\share\gir-1.0\

mkdir ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\lib\girepository-1.0
move /y *.typelib ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\lib\girepository-1.0\
move /y ..\..\gir\*.typelib ..\..\build\win32\vs%VSVER%\%CONF%\%PLAT%\lib\girepository-1.0\
:DONE

