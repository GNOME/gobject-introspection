python_path = py3.find_python().path()

tools = [
  ['g-ir-scanner', 'scannermain', 'scanner_main'],
  ['g-ir-annotation-tool', 'annotationmain', 'annotation_main'],
]
if get_option('doctool')
  tools += [['g-ir-doc-tool', 'docmain', 'doc_main']]
endif

tool_output = []
foreach tool : tools
  tools_conf = configuration_data()
  tools_conf.set('libdir', gi_libdir)
  tools_conf.set('datarootdir', gi_datadir)
  tools_conf.set('PYTHON', python_path)

  tools_conf.set('TOOL_MODULE', tool[1])
  tools_conf.set('TOOL_FUNCTION', tool[2])
  tool_output += configure_file(
    input: 'g-ir-tool-template.in',
    output: tool[0],
    configuration: tools_conf,
    install: true,
    install_dir: get_option('bindir'),
  )
endforeach

girscanner = tool_output[0]

gircompiler = executable('g-ir-compiler', 'compiler.c',
  c_args: '-DGIREPO_DEFAULT_SEARCH_PATH="@0"'.format(libdir_abs),
  dependencies: [
    girepo_internals_dep,
    girepo_dep,
  ],
  install: true,
)

girgenerate = executable('g-ir-generate', 'generate.c',
  c_args: '-DGIREPO_DEFAULT_SEARCH_PATH="@0"'.format(libdir_abs),
  dependencies: [
    girepo_internals_dep,
    girepo_dep,
  ],
  install: true,
)

girinspect = executable('g-ir-inspect', 'g-ir-inspect.c',
  dependencies: girepo_dep,
  install: true,
)
