#!/usr/bin/env bash

if [ ! -d "$1/meson-logs" ]; then
  echo "Usage: $0 <meson-build-dir>"
  exit 1
fi

builddir=$1
scanner_path=$(dirname "$0")

LANGUAGES=(C Gjs Python)
BINDINGS=()

for binding in "$scanner_path"/*-expected.gir; do
  BINDINGS+=("$(basename "$binding" -expected.gir)")
done

scanner_builddir=$builddir/tests/scanner

for binding in "${BINDINGS[@]}"; do
  binding_prefix=$scanner_builddir/$binding
  cp -v "$binding_prefix.gir" \
    "$scanner_path/$binding-expected.gir"

  cp -v "$binding_prefix-sections.txt" \
    "$scanner_path/$binding-sections-expected.txt"

  for l in "${LANGUAGES[@]}"; do
    if [ -d "$binding_prefix-$l" ]; then
      cp -v "$binding_prefix-$l"/* \
        "$scanner_path/$binding-$l-expected/"
    fi
  done
done
