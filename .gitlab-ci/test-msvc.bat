@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
@echo on

pip3 install --upgrade --user meson==0.47.0  || goto :error
meson _build || goto :error
ninja -C _build || goto :error

meson test -C _build --suite=gobject-introspection || goto :error

goto :EOF
:error
exit /b 1
