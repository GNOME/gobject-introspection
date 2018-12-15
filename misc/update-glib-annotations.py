#!/usr/bin/env python3
# Scan glib sources.
#
# meson _build
# ninja -C _build
# ./misc/update-glib-annotations.py <path-to-glib-git-checkout>

import os
import sys
import subprocess


SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
SRC_DIR = os.path.realpath(os.path.join(SCRIPT_DIR, ".."))


def get_build_dir():
    build_dir = os.path.join(SRC_DIR, "_build")
    if not os.path.isdir(build_dir):
        raise SystemExit(
            "build dir not found: "
            "build with meson in %r first" % build_dir)
    return build_dir


def get_tool_path():
    build_dir = get_build_dir()
    tool_path = os.path.join(build_dir, "tools", "g-ir-annotation-tool")
    if not os.path.isfile(tool_path):
        raise SystemExit(
            "g-ir-annotation-tool not found: "
            "build with meson in %r first" % build_dir)
    return tool_path


def extract_annotations(module_name, glib_srcdir, outfile):
    sources = []

    glib_subdir = os.path.join(glib_srcdir, module_name)
    for sourcename in sorted(os.listdir(glib_subdir), reverse=True):
        if sourcename.endswith('.c'):
            sources.append(os.path.join(glib_subdir, sourcename))

    env = os.environ.copy()
    env['PYTHONPATH'] = os.path.join(get_build_dir(), 'giscanner')

    tool_args = [get_tool_path(), '--extract'] + sources
    return subprocess.check_call(tool_args, stdout=outfile, env=env)


def update_module(module_name, glib_src_dir, target_path):
    tmpname = target_path + '.tmp'

    if os.path.isfile(tmpname):
        os.unlink(tmpname)
    with open(tmpname, 'wb') as target:
        extract_annotations(module_name, glib_src_dir, target)
    if os.path.isfile(target_path):
        os.unlink(target_path)
    os.rename(tmpname, target_path)

    print("Updated '%s'" % (target_path, ))


def main(argv):
    if len(argv) != 2:
        print("only pass the glib src dir")
    glib_src_dir = argv[1]
    if not os.path.exists(os.path.join(glib_src_dir, "glib.doap")):
        raise SystemExit("%s isn't the glib source dir" % glib_src_dir)

    print("Using source directory: '%s' build directory: '%s'" % (
        glib_src_dir, get_build_dir()))

    gir_dir = os.path.join(SRC_DIR, "gir")
    modules = {
        'glib': os.path.join(gir_dir, 'glib-2.0.c'),
        'gmodule': os.path.join(gir_dir, 'gmodule-2.0.c'),
        'gobject': os.path.join(gir_dir, 'gobject-2.0.c'),
        'gio': os.path.join(gir_dir, 'gio-2.0.c'),
    }

    for module_name, target_path in modules.items():
        update_module(module_name, glib_src_dir, target_path)

    print("Done; run \"git diff\" to see any changes.")


if __name__ == '__main__':
    main(sys.argv)
