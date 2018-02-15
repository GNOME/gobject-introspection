giscanner_files = [
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
  'pkgconfig.py',
  'shlibs.py',
  'scannermain.py',
  'sectionparser.py',
  'sourcescanner.py',
  'testcodegen.py',
  'transformer.py',
  'utils.py',
  'xmlwriter.py',
]

pkglibdir = join_paths(get_option('libdir'), meson.project_name())
giscannerdir = join_paths(pkglibdir, 'giscanner')

giscanner_built_files = []
giscanner_conf_data = configuration_data()
giscanner_conf_data.set('VERSION', meson.project_version())
giscanner_built_files += configure_file(input: '_version.py.in',
                                        output: '_version.py',
                                        install : true,
                                        install_dir : giscannerdir,
                                        configuration: giscanner_conf_data)
foreach f : giscanner_files
  giscanner_built_files += configure_file(input : f, output : f,
                                          install : true,
                                          install_dir : giscannerdir,
                                          configuration : giscanner_conf_data)
endforeach

install_subdir('doctemplates', install_dir: giscannerdir)

flex = find_program('flex', 'win_flex')
bison = find_program('bison', 'win_bison')

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

giscanner_args = []
if not cc.has_header('unistd.h')
  giscanner_args += '-DYY_NO_UNISTD_H'
endif

giscanner_lib = static_library('giscanner',
  sources: [
    'sourcescanner.c',
    scannerparser,
    scannerlexer,
  ],
  c_args: giscanner_args,
  include_directories : configinc,
  dependencies: [glib_dep, gobject_dep, gio_dep, gmodule_dep],
)

giscanner_pymod = python.extension_module('_giscanner', ['giscannermodule.c'],
  link_with: giscanner_lib,
  c_args: [gi_hidden_visibility_cflags],
  include_directories : configinc,
  dependencies: [glib_dep, gobject_dep, gio_dep, gmodule_dep,
                 python.dependency()],
  install: true,
  install_dir: giscannerdir,
)
