scanner_test_env = environment()
scanner_test_env.prepend('PYTHONPATH', test_env_common_pypath)
if test_env_common_path.length() > 0
    scanner_test_env.prepend('PATH', test_env_common_path)
endif

scanner_test_files = [
  'test_ccompiler.py',
  'test_shlibs.py',
  'test_sourcescanner.py',
  'test_transformer.py',
  'test_xmlwriter.py',
  'test_pkgconfig.py',
  'test_docwriter.py',
]

foreach f : scanner_test_files 
  test(f, python, args: files(f), env: scanner_test_env, depends: [giscanner_pymod])
endforeach

subdir('annotationparser')
