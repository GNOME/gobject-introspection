import os
import subprocess
import tempfile

from .glibtransformer import IntrospectionBinary

# bugzilla.gnome.org/558436
# Compile a binary program which is then linked to a library
# we want to introspect, in order to call its get_type functions.


def mktmp(tmpdir, nsname, nsver, suffix):
    name = '%s-%s%s' % (nsname, nsver, suffix)
    return os.path.join(tmpdir, name)


def compile_introspection_binary(options):
    tmpdir = tempfile.mkdtemp('', 'tmp-introspect')
    nsname = options.namespace_name
    nsver = options.namespace_version
    c_path = mktmp(tmpdir, nsname, nsver, '.c')
    f = open(c_path, 'w')
    f.write('''#include <glib.h>
#include <girepository.h>
#include <string.h>

static GOptionEntry entries[] =
{
  { NULL }
};

int
main(int argc, char **argv)
{
  GOptionContext *context;
  GError *error = NULL;

  g_type_init ();
  g_thread_init (NULL);

  context = g_option_context_new ("");
  g_option_context_add_main_entries (context, entries, "girepository");
  g_option_context_add_group (context, g_irepository_get_option_group ());
  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_printerr ("introspect failed (%d,%d): %s\\n",
                  error->domain, error->code,
                  error->message);
      return 1;
    }
  return 0;
}
''')
    f.close()

    o_path = mktmp(tmpdir, nsname, nsver, '.o')

    cc = os.environ.get('CC', 'gcc')
    ld = os.environ.get('LD', cc)
    pkgconfig = os.environ.get('PKG_CONFIG', 'pkg-config')
    uninst_srcdir = os.environ.get('UNINSTALLED_INTROSPECTION_SRCDIR')
    uninst_builddir = os.environ.get('UNINSTALLED_INTROSPECTION_BUILDDIR')

    pkgs = ['gio-2.0 gthread-2.0']
    if not uninst_srcdir:
        pkgs.append('gobject-introspection-1.0')

    cc_args = [cc]
    if cc == 'gcc':
        cc_args.append('-Wall')
    output = subprocess.Popen([pkgconfig, '--cflags'] + pkgs,
                              stdout=subprocess.PIPE).communicate()[0]
    if uninst_srcdir:
        cc_args.append('-I' + os.path.join(uninst_srcdir, 'girepository'))
    cc_args.extend(output.split())
    for include in options.cpp_includes:
        cc_args.append('-I' + include)
    cc_args.extend(['-c', '-o', o_path, c_path])
    subprocess.check_call(cc_args)

    bin_path = mktmp(tmpdir, nsname, nsver, '')

    ld_args = [ld, '-o', bin_path, o_path]
    libtool_infection = not options.nolibtool
    if not libtool_infection:
        try:
            subprocess.check_call(['libtool', '--version'])
        except subprocess.CalledProcessError, e:
            # If libtool's not installed, assume we don't need it
            libtool_infection = False
    if libtool_infection:
        ld_args.insert(0, 'libtool')
        ld_args.insert(1, '--mode=link')
    output = subprocess.Popen([pkgconfig, '--libs'] + pkgs,
                              stdout=subprocess.PIPE).communicate()[0]
    ld_args.extend(output.split())

    # This hack is only for building gobject-introspection itself
    if uninst_builddir:
        path = os.path.join(uninst_builddir, 'girepository',
                            'libgirepository.la')
        ld_args.append(path)
    # Search the current directory first
    ld_args.append('-L.')

    # We only use the first library; assume others are "custom" libraries like
    # from gir-repository.  Right now those don't define new GTypes, so we
    # don't need to introspect them.
    ld_args.append('-l'+options.libraries[0])
    subprocess.check_call(ld_args)

    os.unlink(c_path)
    return IntrospectionBinary([bin_path], tmpdir)
