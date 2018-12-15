repository_tests = [
  'gitestrepo',
  'giteststructinfo',
  'gitestthrows',
  # FIXME: Requires Regress typelib which is not yet ported to meson.
  # 'gitypelibtest',
]

repository_test_env = environment()
repository_test_env.append(
  'GI_TYPELIB_PATH',
  join_paths(meson.build_root(), 'gir'),
  join_paths(meson.build_root(), 'tests')
)

custom_c_args = cc.get_supported_arguments([
  '-Wno-unused-parameter',
])
if glib_dep.type_name() == 'pkgconfig'
  foreach test_name : repository_tests
    source = files(test_name + '.c')
    exe = executable(test_name, source,
      dependencies: [girepo_dep],
      c_args: custom_c_args)
    test(test_name, exe, env: repository_test_env)
  endforeach
endif
