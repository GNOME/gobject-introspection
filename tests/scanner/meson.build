
scanner_test_env = environment()
scanner_test_env.append('PYTHONPATH', join_paths(meson.current_build_dir(), '../../'))

scanner_test_files = [
  'test_shlibs.py',
  'test_transformer.py',
]

# FIXME: MSVC
if cc.get_id() != 'msvc'
  scanner_test_files += ['test_sourcescanner.py']
endif

foreach f : scanner_test_files 
  test(f, python, args: files(f), env: scanner_test_env)
endforeach
