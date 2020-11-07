#!/bin/bash

set -e

export PATH="/c/msys64/$MSYSTEM/bin:$PATH"
if [[ "$MSYSTEM" == "MINGW32" ]]; then
    export MSYS2_ARCH="i686"
else
    export MSYS2_ARCH="x86_64"
fi

pacman --noconfirm -Suy

pacman --noconfirm -S --needed \
    git \
    base-devel \
    mingw-w64-$MSYS2_ARCH-toolchain \
    mingw-w64-$MSYS2_ARCH-ccache \
    mingw-w64-$MSYS2_ARCH-meson \
    mingw-w64-$MSYS2_ARCH-python3 \
    mingw-w64-$MSYS2_ARCH-python3-pip \
    mingw-w64-$MSYS2_ARCH-python3-mako \
    mingw-w64-$MSYS2_ARCH-python3-markdown \
    mingw-w64-$MSYS2_ARCH-libffi \
    mingw-w64-$MSYS2_ARCH-pkg-config \
    mingw-w64-$MSYS2_ARCH-cairo \
    mingw-w64-$MSYS2_ARCH-pcre \
    mingw-w64-$MSYS2_ARCH-zlib \
    mingw-w64-$MSYS2_ARCH-gettext

export CCACHE_BASEDIR="${CI_PROJECT_DIR}"
export CCACHE_DIR="${CCACHE_BASEDIR}/_ccache"

pip3 install --upgrade --user meson==0.50.1 flake8 mypy
export PATH="$HOME/.local/bin:$PATH"

export CFLAGS="-Werror"
meson -Dcairo=enabled -Ddoctool=enabled --buildtype debug _build
cd _build
ninja

meson test --print-errorlogs --suite=gobject-introspection --no-suite=glib
cd ..

python3 -m flake8 --count
python3 -m mypy .