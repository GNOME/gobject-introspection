#!/bin/bash

set -e

pacman --noconfirm -Suy

pacman --noconfirm -S --needed \
    git \
    base-devel \
    ${MINGW_PACKAGE_PREFIX}-toolchain \
    ${MINGW_PACKAGE_PREFIX}-ccache \
    ${MINGW_PACKAGE_PREFIX}-meson \
    ${MINGW_PACKAGE_PREFIX}-python \
    ${MINGW_PACKAGE_PREFIX}-python-pip \
    ${MINGW_PACKAGE_PREFIX}-python-packaging \
    ${MINGW_PACKAGE_PREFIX}-python-mako \
    ${MINGW_PACKAGE_PREFIX}-python-markdown \
    ${MINGW_PACKAGE_PREFIX}-libffi \
    ${MINGW_PACKAGE_PREFIX}-pkgconf \
    ${MINGW_PACKAGE_PREFIX}-cairo \
    ${MINGW_PACKAGE_PREFIX}-pcre2 \
    ${MINGW_PACKAGE_PREFIX}-zlib \
    ${MINGW_PACKAGE_PREFIX}-gettext

export CCACHE_BASEDIR="${CI_PROJECT_DIR}"
export CCACHE_DIR="${CCACHE_BASEDIR}/_ccache"

pip3 install --upgrade --user meson==1.4.2 flake8 mypy==0.931 types-Markdown
export PATH="$HOME/.local/bin:$PATH"

meson setup \
        -Dwerror=true \
        -Dglib:werror=false \
        -Dcairo=enabled \
        -Ddoctool=enabled \
        --buildtype debug \
        _build

.gitlab-ci/show-git-commits.sh || true

meson compile -C _build

meson test \
        --print-errorlogs \
        --suite=gobject-introspection \
        --no-suite=glib \
        -C _build

python3 -m flake8 --count
python3 -m mypy _build
