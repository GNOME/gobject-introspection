@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
@echo on

py -3 -c "import urllib.request, sys; urllib.request.urlretrieve(*sys.argv[1:])" "https://github.com/lexxmark/winflexbison/releases/download/v2.5.14/win_flex_bison-2.5.14.zip" win_flex_bison.zip
py -3 -m zipfile -e win_flex_bison.zip win_flex_bison

py -3 -c "import urllib.request, sys; urllib.request.urlretrieve(*sys.argv[1:])" "https://sourceforge.net/projects/pkgconfiglite/files/0.28-1/pkg-config-lite-0.28-1_bin-win32.zip/download" pkg-config-lite-0.28-1.zip
py -3 -m zipfile -e pkg-config-lite-0.28-1.zip .

SET PATH=%CD%\pkg-config-lite-0.28-1\bin;%CD%\win_flex_bison;%PATH%

pip3 install --upgrade --user meson==0.48.2 || goto :error
meson _build || goto :error
ninja -C _build || goto :error

meson test -C _build --suite=gobject-introspection || goto :error

goto :EOF
:error
exit /b 1
