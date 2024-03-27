scanner_test_env = environment()
scanner_test_env.prepend('PYTHONPATH', test_env_common_pypath)
if test_env_common_path.length() > 0
  scanner_test_env.prepend('PATH', test_env_common_path)
endif

# Needed on Windows for Python 3.8.x+ if project is configured with
# --pkg-config-path or -Dpkg_config_path
if pkg_config_path_win.length() > 0
  scanner_test_env.prepend('PKG_CONFIG_PATH', pkg_config_path_win)
endif

scanner_test_files = [
  'test_ccompiler.py',
  'test_shlibs.py',
  'test_sourcescanner.py',
  'test_transformer.py',
  'test_xmlwriter.py',
  'test_pkgconfig.py',
  'test_docwriter.py',
  'test_scanner.py',
  'test_maintransformer.py',
]

foreach f : scanner_test_files 
  test(f, python, args: files(f), env: scanner_test_env, depends: [giscanner_pymod])
endforeach

test_girs = []
test_typelibs = []

custom_c_args = []
if cc.get_id() != 'msvc'
  custom_c_args = cc.get_supported_arguments([
    '-Wno-unused-parameter',
  ])
endif

gitests_inc = include_directories('../../gobject-introspection-tests')

typedef_lib = shared_library('typedef-1.0',
  sources: ['typedefs.c'],
  include_directories : [configinc, gitests_inc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

sletter_lib = shared_library('sletter-1.0',
  sources: ['sletter.c'],
  include_directories : [configinc, gitests_inc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gio_dep],
)

warnlib_lib = shared_library('warnlib-1.0',
  sources: ['../../gobject-introspection-tests/warnlib.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gio_dep],
)

utility_lib = shared_library('utility-1.0',
  sources: ['../../gobject-introspection-tests/utility.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

gtkfrob_lib = shared_library('gtkfrob-1.0',
  sources: ['gtkfrob.c'],
  include_directories : [configinc, gitests_inc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

gettype_lib = shared_library('gettype-1.0',
  sources: ['gettype.c'],
  include_directories : [configinc, gitests_inc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

barapp_lib = shared_library('barapp-1.0',
  sources: ['barapp.c'],
  include_directories : [configinc, gitests_inc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep, girepo_dep],
)

if cc.get_id() != 'msvc'
  custom_c_args = cc.get_supported_arguments([
    '-Wno-unused-parameter',
    '-Wno-old-style-definition',
    '-Wno-missing-field-initializers',
  ])
endif

if cairo_deps_found
  regress_deps = [cairo_dep, cairo_gobject_dep]
  regress_c_args = []
else
  regress_deps = []
  regress_c_args = ['-DGI_TEST_DISABLE_CAIRO']
endif

regress_lib = shared_library('regress-1.0',
  sources: [
    '../../gobject-introspection-tests/annotation.c',
    '../../gobject-introspection-tests/drawable.c',
    '../../gobject-introspection-tests/foo.c',
    '../../gobject-introspection-tests/regress-unix.c',
    '../../gobject-introspection-tests/regress.c',
    '../../gobject-introspection-tests/regressextra.c',
  ],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + regress_c_args + custom_c_args,
  dependencies: [gobject_dep, gio_dep] + regress_deps,
)

python_path = run_command(python, ['-c', 'import sys; sys.stdout.write(sys.executable)'], check: true).stdout()

gircompiler_command = [
  test_gircompiler, '-o', '@OUTPUT@', '@INPUT@',
  '--includedir', join_paths(build_root, 'gir'),
  '--includedir', meson.current_build_dir(),
]

if (glib_dep.type_name() == 'pkgconfig' and
    get_option('build_introspection_data') == true)
  typedef_gir = custom_target('gir-typedef',
    input: ['typedefs.c', 'typedefs.h'],
    output: 'Typedefs-1.0.gir',
    depends: [typedef_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--warn-all',
      '--warn-error',
      '--namespace=Typedefs',
      '--nsversion=1.0',
      '--symbol-prefix=typedefs',
      '--identifier-prefix=Typedefs',
      '--include=GObject-2.0',
      '--pkg=gobject-2.0',
      '--library=typedef-1.0',
      '--c-include=typedefs.h',
      '--doc-format=gtk-doc-markdown',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '-I', join_paths(source_root, 'gobject-introspection-tests'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += typedef_gir

  test_typelibs += custom_target(
    'generate-typelib-typedef',
    input: typedef_gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir],
    command: gircompiler_command,
  )

  bar_gir = custom_target('gir-bar',
    input: ['barapp.c', 'barapp.h'],
    output: 'Bar-1.0.gir',
    depends: [barapp_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--warn-all',
      '--warn-error',
      '--namespace=Bar',
      '--nsversion=1.0',
      '--include=GObject-2.0',
      '--pkg=gobject-2.0',
      '--library=barapp-1.0',
      '--accept-unprefixed',
      '--doc-format=gi-docgen',
      '-L', meson.current_build_dir(),
      '-L', join_paths(build_root, 'girepository'),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '-I', join_paths(source_root, 'gobject-introspection-tests'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += bar_gir

  test_typelibs += custom_target(
    'generate-typelib-bar',
    input: bar_gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir],
    command: gircompiler_command,
  )

  sletter_gir = custom_target('gir-sletter',
    input: ['sletter.c', 'sletter.h'],
    output: 'SLetter-1.0.gir',
    depends: [sletter_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--warn-all',
      '--warn-error',
      '--namespace=SLetter',
      '--nsversion=1.0',
      '--identifier-prefix=S',
      '--include=Gio-2.0',
      '--library=sletter-1.0',
      '--c-include=sletter.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '-I', join_paths(source_root, 'gobject-introspection-tests'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += sletter_gir

  test_typelibs += custom_target(
    'generate-typelib-sletter',
    input: sletter_gir,
    output: '@BASENAME@.typelib',
    depends: [gio_gir],
    command: gircompiler_command,
  )

  warnlib_gir = custom_target('gir-warnlib',
    input: [
      '../../gobject-introspection-tests/warnlib.c',
      '../../gobject-introspection-tests/warnlib.h',
    ],
    output: 'WarnLib-1.0.gir',
    depends: [warnlib_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--namespace=WarnLib',
      '--nsversion=1.0',
      '--include=Gio-2.0',
      '--library=warnlib-1.0',
      '--symbol-prefix=warnlib_',
      '--c-include=warnlib.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += warnlib_gir

  test_typelibs += custom_target(
    'generate-typelib-warnlib',
    input: warnlib_gir,
    output: '@BASENAME@.typelib',
    depends: [gio_gir],
    command: gircompiler_command,
  )

  utility_gir = custom_target('gir-utility',
    input: [
      '../../gobject-introspection-tests/utility.c',
      '../../gobject-introspection-tests/utility.h',
    ],
    output: 'Utility-1.0.gir',
    depends: [utility_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--warn-all',
      '--warn-error',
      '--namespace=Utility',
      '--nsversion=1.0',
      '--include=GObject-2.0',
      '--pkg=gobject-2.0',
      '--library=utility-1.0',
      '--c-include=utility.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += utility_gir

  test_typelibs += custom_target(
    'generate-typelib-utility',
    input: utility_gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir],
    command: gircompiler_command,
  )

  gtkfrob_gir = custom_target('gir-gtkfrob',
    input: ['gtkfrob.c', 'gtkfrob.h'],
    output: 'GtkFrob-1.0.gir',
    depends: [gtkfrob_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--warn-all',
      '--warn-error',
      '--namespace=GtkFrob',
      '--nsversion=1.0',
      '--identifier-prefix=Gtk',
      '--symbol-prefix=gtk_frob',
      '--include=GObject-2.0',
      '--pkg=gobject-2.0',
      '--library=gtkfrob-1.0',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '-I', join_paths(source_root, 'gobject-introspection-tests'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += gtkfrob_gir

  test_typelibs += custom_target(
    'generate-typelib-gtkfrob',
    input: gtkfrob_gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir],
    command: gircompiler_command,
  )

  gettype_gir = custom_target('gir-gettype',
    input: ['gettype.c', 'gettype.h'],
    output: 'GetType-1.0.gir',
    depends: [gettype_lib] + typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--namespace=GetType',
      '--nsversion=1.0',
      '--identifier-prefix=GetType',
      '--symbol-prefix=gettype',
      '--include=GObject-2.0',
      '--pkg=gobject-2.0',
      '--library=gettype-1.0',
      '--c-include=gettype.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '-I', join_paths(source_root, 'gobject-introspection-tests'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += gettype_gir

  test_typelibs += custom_target(
    'generate-typelib-gettype',
    input: gettype_gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir],
    command: gircompiler_command,
  )

  symbolfilter_gir = custom_target('gir-symbolfilter',
    input: ['symbolfilter.h'],
    output: 'Symbolfilter-1.0.gir',
    depends: typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--namespace=Symbolfilter',
      '--nsversion=1.0',
      '--header-only',
      '--symbol-filter-cmd=' + python_path + ' ' +  join_paths(meson.current_source_dir(), 'symbolfilter.py'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += symbolfilter_gir

  test_typelibs += custom_target(
    'generate-typelib-symbolfilter',
    input: symbolfilter_gir,
    output: '@BASENAME@.typelib',
    command: gircompiler_command,
  )

  identfilter_gir = custom_target('gir-identfilter',
    input: ['identfilter.h'],
    output: 'Identfilter-1.0.gir',
    depends: typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--accept-unprefixed',
      '--reparse-validate',
      '--namespace=Identfilter',
      '--nsversion=1.0',
      '--header-only',
      '--identifier-filter-cmd=' + python_path + ' "' +  join_paths(meson.current_source_dir(), 'identfilter.py' + '"'),
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += identfilter_gir

  test_typelibs += custom_target(
    'generate-typelib-identfilter',
    input: identfilter_gir,
    output: '@BASENAME@.typelib',
    command: gircompiler_command,
  )

  headeronly_gir = custom_target('gir-headeronly',
    input: ['headeronly.h'],
    output: 'Headeronly-1.0.gir',
    depends: typelibs,
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--warn-all',
      '--warn-error',
      '--reparse-validate',
      '--namespace=Headeronly',
      '--nsversion=1.0',
      '--header-only',
      extra_giscanner_args,
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )
  test_girs += headeronly_gir

  test_typelibs += custom_target(
    'generate-typelib-headeronly',
    input: headeronly_gir,
    output: '@BASENAME@.typelib',
    command: gircompiler_command,
  )

  if cairo_deps_found
    regress_scanner_cairo_args = ['--include=cairo-1.0']
  else
    regress_scanner_cairo_args = ['-DGI_TEST_DISABLE_CAIRO',]
  endif

  regress_gir = custom_target('gir-regress',
    input: [
      '../../gobject-introspection-tests/annotation.c',
      '../../gobject-introspection-tests/annotation.h',
      '../../gobject-introspection-tests/drawable.c',
      '../../gobject-introspection-tests/drawable.h',
      '../../gobject-introspection-tests/foo.c',
      '../../gobject-introspection-tests/foo.h',
      '../../gobject-introspection-tests/regress.c',
      '../../gobject-introspection-tests/regress.h',
      '../../gobject-introspection-tests/regressextra.c',
      '../../gobject-introspection-tests/regressextra.h',
    ],
    output: 'Regress-1.0.gir',
    depends: [regress_lib] + typelibs + [utility_gir],
    command: [
      test_girscanner,
      '--quiet',
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(source_root, 'gir'),
      '--add-include-path', join_paths(build_root, 'gir'),
      '--add-include-path', meson.current_build_dir(),
      '--namespace=Regress',
      '--nsversion=1.0',
      '--include=Gio-2.0',
      '--include=Utility-1.0',
      '--library=regress-1.0',
      '--c-include=regress.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      extra_giscanner_args,
      ] + regress_scanner_cairo_args + [
      '@INPUT@',
    ],
    env: tests_scanner_run_env,
  )

  # The reference gir is generated with cairo support, so we can only compare
  # things if we build with cairo as well
  if cairo_deps_found
    test_girs += regress_gir
  endif

  regress_typelib = custom_target(
    'generate-typelib-regress',
    input: regress_gir,
    output: '@BASENAME@.typelib',
    command: gircompiler_command,
  )
  test_typelibs += regress_typelib

  if host_system != 'windows'
    regress_unix_gir = custom_target('gir-regress-unix',
      input: [
        '../../gobject-introspection-tests/regress-unix.c',
        '../../gobject-introspection-tests/regress-unix.h',
      ],
      output: 'RegressUnix-1.0.gir',
      depends: [regress_lib] + typelibs + [utility_gir],
      command: [
        test_girscanner,
        '--quiet',
        '--output=@OUTPUT@',
        '--no-libtool',
        '--reparse-validate',
        '--add-include-path', join_paths(source_root, 'gir'),
        '--add-include-path', join_paths(build_root, 'gir'),
        '--add-include-path', meson.current_build_dir(),
        '--namespace=RegressUnix',
        '--nsversion=1.0',
        '--include=Gio-2.0',
        '--include=Utility-1.0',
        '--library=regress-1.0',
        '--c-include=regress-unix.h',
        '-L', meson.current_build_dir(),
        '-I', meson.current_source_dir(),
        '-I', join_paths(meson.current_source_dir(), '..'),
        extra_giscanner_args,
        '@INPUT@',
      ]
    )
    test_girs += regress_unix_gir

    regress_unix_typelib = custom_target(
      'generate-typelib-regress-unix',
      input: regress_unix_gir,
      output: '@BASENAME@.typelib',
      command: gircompiler_command,
    )
    test_typelibs += regress_unix_typelib
  else
    regress_unix_gir = disabler()
  endif
else
  regress_gir = disabler()
  regress_unix_gir = disabler()
endif

gi_tester = files(join_paths('..', 'gi-tester'))

foreach gir : test_girs
  gir_name = fs.name(gir.full_path())
  test(
    'gi-tester-' + gir_name,
    python,
    args: [gi_tester, gir_name],
    depends: [gir],
    env: [
      'srcdir=' + meson.current_source_dir(),
      'builddir=' + meson.current_build_dir(),
    ],
  )
endforeach

if has_girdoctool and glib_dep.type_name() == 'pkgconfig'
  doctool_env = environment()
  doctool_env.set('srcdir', meson.current_source_dir())
  doctool_env.set('builddir', meson.current_build_dir())

  foreach language : ['C', 'Python', 'Gjs']
    regress_docs = custom_target(
      'generate-docs-' + language,
      input: regress_gir,
      depend_files: doc_templates,
      build_by_default: not cairo_deps_found,
      env: doctool_env,
      output: 'Regress-1.0-' + language,
      command: [
        python, girdoctool,
        '--add-include-path=' + join_paths(build_root, 'gir'),
        '--add-include-path=' + join_paths(build_root, 'gobject-introspection-tests'),
        '--add-include-path=' + meson.current_build_dir(),
        '--language', language,
        '--templates-dir=' + join_paths(meson.current_source_dir(), '../../giscanner/doctemplates'),
        '@INPUT@', '-o', '@OUTPUT@',
      ],
      env: tests_scanner_run_env,
    )

    if cairo_deps_found
      test(
        'gi-tester-docs-Regress-1.0-' + language,
        python,
        args: [gi_tester, 'Regress-1.0-' + language],
        depends: [regress_docs],
        env: doctool_env,
      )
    endif
  endforeach

  regress_sections = custom_target(
    'generate-docs-sections',
    input: regress_gir,
    depend_files: [doc_templates],
    build_by_default: not cairo_deps_found,
    output: 'Regress-1.0-sections.txt',
    env: doctool_env,
    command: [
      python, girdoctool,
      '--add-include-path=' + join_paths(build_root, 'gir'),
      '--add-include-path=' + join_paths(build_root, 'gobject-introspection-tests'),
      '--add-include-path=' + meson.current_build_dir(),
      '--write-sections-file',
      '@INPUT@', '-o', '@OUTPUT@'],
    env: tests_scanner_run_env,
  )

  if cairo_deps_found
    test(
      'gi-tester-docs-Regress-1.0-sections.txt',
      python,
      args: [gi_tester, 'Regress-1.0-sections.txt'],
      depends: [regress_sections],
      env: doctool_env,
    )
  endif
endif

foreach typelib : test_typelibs
  typelib_name = fs.name(typelib.full_path())
  test(
    'gi-tester-' + typelib_name,
    python,
    args: [gi_tester, typelib.full_path()],
    depends: [typelib],
  )
endforeach

subdir('annotationparser')
