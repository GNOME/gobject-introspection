pkglibdir = join_paths(get_option('libdir'), meson.project_name())
giscannerdir = join_paths(pkglibdir, 'giscanner')
install_data([
  '__init__.py',
  'annotationmain.py',
  'annotationparser.py',
  'ast.py',
  'cachestore.py',
  'ccompiler.py',
  'codegen.py',
  'docmain.py',
  'docwriter.py',
  'dumper.py',
  'introspectablepass.py',
  'girparser.py',
  'girwriter.py',
  'gdumpparser.py',
  'libtoolimporter.py',
  'maintransformer.py',
  'message.py',
  'msvccompiler.py',
  'shlibs.py',
  'scannermain.py',
  'sectionparser.py',
  'sourcescanner.py',
  'testcodegen.py',
  'transformer.py',
  'utils.py',
  'xmlwriter.py',
], install_dir: giscannerdir)

install_data([
  'collections/__init__.py',
  'collections/counter.py',
  'collections/ordereddict.py',
], install_dir: join_paths(giscannerdir, 'collections'))

install_subdir('doctemplates', install_dir: giscannerdir)

flex = find_program('flex')
bison = find_program('bison')

scannerparser = custom_target('scannerparser',
    input: 'scannerparser.y',
   output: ['scannerparser.c', 'scannerparser.h'],
  command: [bison, '@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']

)

scannerlexer = custom_target('scannerlexer',
    input: 'scannerlexer.l',
   output: 'scannerlexer.c',
  command: [flex, '-o', '@OUTPUT@', '@INPUT@']
)

giscanner_lib = static_library('giscanner',
  sources: [
    'sourcescanner.c',
    scannerparser,
    scannerlexer,
  ],
  dependencies: gio_dep,
)

# TODO: -export-symbols-regex "init_giscanner|PyInit__giscanner"
py3.extension_module('_giscanner', 'giscannermodule.c',
  link_with: giscanner_lib,
  dependencies: [
    gobject_dep,
    dependency('python3'),
  ],
  install: true,
  install_dir: giscannerdir,
)
