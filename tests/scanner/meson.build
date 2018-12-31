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

test_girs = []

custom_c_args = cc.get_supported_arguments([
  '-Wno-unused-parameter',
])

typedef_lib = shared_library('typedef-1.0',
  sources: ['typedefs.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

sletter_lib = shared_library('sletter-1.0',
  sources: ['sletter.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gio_dep],
)

warnlib_lib = shared_library('warnlib-1.0',
  sources: ['warnlib.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gio_dep],
)

utility_lib = shared_library('utility-1.0',
  sources: ['utility.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

gtkfrob_lib = shared_library('gtkfrob-1.0',
  sources: ['gtkfrob.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

gettype_lib = shared_library('gettype-1.0',
  sources: ['gettype.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + custom_c_args,
  dependencies: [gobject_dep],
)

custom_c_args = cc.get_supported_arguments([
  '-Wno-unused-parameter',
  '-Wno-old-style-definition',
  '-Wno-missing-field-initializers',
])

if with_cairo
  regress_deps = [cairo_dep, cairo_gobject_dep]
  regress_c_args = []
else
  regress_deps = []
  regress_c_args += ['-D_GI_DISABLE_CAIRO']
endif

regress_lib = shared_library('regress-1.0',
  sources: ['regress.c', 'annotation.c', 'foo.c', 'drawable.c'],
  include_directories : [configinc, include_directories('..')],
  c_args: gi_hidden_visibility_cflags + regress_c_args + custom_c_args,
  dependencies: [gobject_dep, gio_dep] + regress_deps,
)

if glib_dep.type_name() == 'pkgconfig'
  test_girs += custom_target('gir-typedef',
    input: ['typedefs.c', 'typedefs.h'],
    output: 'Typedefs-1.0.gir',
    depends: [typedef_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '@INPUT@',
    ]
  )

  test_girs += custom_target('gir-sletter',
    input: ['sletter.c', 'sletter.h'],
    output: 'SLetter-1.0.gir',
    depends: [sletter_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      '@INPUT@',
    ]
  )

  test_girs += custom_target('gir-warnlib',
    input: ['warnlib.c', 'warnlib.h'],
    output: 'WarnLib-1.0.gir',
    depends: [warnlib_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
      '--namespace=WarnLib',
      '--nsversion=1.0',
      '--include=Gio-2.0',
      '--library=warnlib-1.0',
      '--symbol-prefix=warnlib_',
      '--c-include=warnlib.h',
      '-L', meson.current_build_dir(),
      '-I', meson.current_source_dir(),
      '-I', join_paths(meson.current_source_dir(), '..'),
      '@INPUT@',
    ]
  )

  test_girs += custom_target('gir-utility',
    input: ['utility.c', 'utility.h'],
    output: 'Utility-1.0.gir',
    depends: [utility_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      '@INPUT@',
    ]
  )

  test_girs += custom_target('gir-gtkfrob',
    input: ['gtkfrob.c', 'gtkfrob.h'],
    output: 'GtkFrob-1.0.gir',
    depends: [gtkfrob_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      '@INPUT@',
    ]
  )

  test_girs += custom_target('gir-gettype',
    input: ['gettype.c', 'gettype.h'],
    output: 'GetType-1.0.gir',
    depends: [gettype_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      '@INPUT@',
    ]
  )

  if with_cairo
    regress_scanner_cairo_args = ['--include=cairo-1.0']
  else
    regress_scanner_cairo_args = ['-D_GI_DISABLE_CAIRO',]
  endif

  regress_gir = custom_target('gir-regress',
    input: ['regress.c', 'regress.h', 'annotation.c', 'annotation.h',
            'foo.c', 'foo.h', 'drawable.c', 'drawable.h'],
    output: 'Regress-1.0.gir',
    depends: [regress_lib] + typelibs,
    command: [
      python,
      girscanner,
      '--output=@OUTPUT@',
      '--no-libtool',
      '--reparse-validate',
      '--add-include-path', join_paths(meson.source_root(), 'gir'),
      '--add-include-path', join_paths(meson.build_root(), 'gir'),
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
      ] + regress_scanner_cairo_args + [
      '@INPUT@',
    ]
  )

  # The reference gir is generated with cairo support, so we can only compare
  # things if we build with cairo as well
  if with_cairo
    test_girs += regress_gir
  endif
endif

foreach gir : test_girs
  gi_tester = files(join_paths('..', 'gi-tester'))
  gir_name = gir.full_path().split('/')[-1]
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

subdir('annotationparser')
