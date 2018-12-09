annotationparser_test_env = environment()
annotationparser_test_env.append('PYTHONPATH', join_paths(meson.current_build_dir(), '../../../'))

annotationparser_test_files = [
  'test_patterns.py',
]

# FIXME: MSVC
#   from giscanner._giscanner import SourceScanner as CSourceScanner
#   ImportError: DLL load failed: The specified module could not be found.
if cc.get_id() != 'msvc'
  annotationparser_test_files += [
    'test_parser.py',
  ]
endif

foreach f : annotationparser_test_files
  test(f, python, args: files(f), env: annotationparser_test_env)
endforeach

