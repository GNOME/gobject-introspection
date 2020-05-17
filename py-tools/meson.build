libdir_abs = join_paths(get_option('prefix'), get_option('libdir'))
datadir_abs = join_paths(get_option('prefix'), get_option('datadir'))

tools = [
  ['g-ir-scanner', 'scannermain', 'scanner_main'],
  ['g-ir-annotation-tool', 'annotationmain', 'annotation_main'],
]
if with_doctool
  tools += [['g-ir-doc-tool', 'docmain', 'doc_main']]
endif

if cc.get_id() == 'msvc'
  python_cmd = '/usr/bin/env ' + python.path()
else
  python_cmd = '/usr/bin/env python@0@'.format(python.language_version().split('.')[0])
endif

tool_output = []
foreach tool : tools
  tools_conf = configuration_data()
  tools_conf.set('libdir', libdir_abs)
  tools_conf.set('datarootdir', datadir_abs)
  tools_conf.set('gir_dir_prefix', gir_dir_prefix)
  tools_conf.set('PYTHON_CMD', python_cmd)

  tools_conf.set('TOOL_MODULE', tool[1])
  tools_conf.set('TOOL_FUNCTION', tool[2])
  tool_bin = configure_file(
    input: 'g-ir-tool-template.in',
    output: tool[0],
    configuration: tools_conf,
    install_dir: get_option('bindir'),
  )
  tool_output += tool_bin
  # Provide tools for others when we're a subproject and they use the Meson GNOME module
  if not get_option('gi_cross_use_prebuilt_gi')
    meson.override_find_program(tool[0], tool_bin)
  endif
endforeach

girscanner = tool_output[0]
has_girdoctool = false
if with_doctool
  girdoctool = tool_output[-1]
  has_girdoctool = true
endif

subdir('giscanner')
