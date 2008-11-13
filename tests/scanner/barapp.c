#include "barapp.h"

#include <girepository.h>
#include <string.h>

G_DEFINE_TYPE(BarBaz, bar_baz, G_TYPE_OBJECT);

static void
bar_baz_class_init (BarBazClass *klass)
{
}

static void
bar_baz_init (BarBaz *object)
{
}

void
barapp_func (void)
{
}

void
barapp_func2 (int x, double y)
{
}

int
main(int argc, char **argv)
{
  const char *prefix = "--introspect-dump=";
  GError *error = NULL;
  if (!(argc == 2 && g_str_has_prefix (argv[1], prefix)))
    {
      g_printerr ("usage: barapp --introspect-dump=types.txt,out.xml\\n");
      return 1;
    }
  g_type_init ();
  g_thread_init (NULL);

  if (!g_irepository_dump (argv[1] + strlen (prefix), &error))
    {
      g_printerr ("%s\n", error->message);
      return 1;
    }
  return 0;
}
