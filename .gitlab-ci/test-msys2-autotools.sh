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
    mingw-w64-$MSYS2_ARCH-python3 \
    mingw-w64-$MSYS2_ARCH-libffi \
    mingw-w64-$MSYS2_ARCH-pkg-config \
    mingw-w64-$MSYS2_ARCH-cairo \
    mingw-w64-$MSYS2_ARCH-pcre \
    mingw-w64-$MSYS2_ARCH-zlib \
    mingw-w64-$MSYS2_ARCH-gettext

export CCACHE_BASEDIR="${CI_PROJECT_DIR}"
export CCACHE_DIR="${CCACHE_BASEDIR}/_ccache"

sed -i 's|\[glib-2\.0 >= [0-9.]*\]|[glib-2.0 >= 1.0]|' configure.ac
./autogen.sh --with-python=python3
make -j4
make check
