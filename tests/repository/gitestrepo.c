
#include "girepository.h"

#include <stdlib.h>
#include <unistd.h>

int 
main(int argc, char **argv)
{
  GIRepository *repo;
  gboolean ret;
  GError *error = NULL;
  GIBaseInfo *info;

  g_type_init ();

  repo = g_irepository_get_default ();

  ret = g_irepository_require (repo, "Gio", NULL, 0, &error);
  g_assert (ret);
  g_assert (error == NULL);

  info = g_irepository_find_by_name (repo, "Gio", "Cancellable");
  g_assert (info != NULL);

  info = g_irepository_find_by_gtype (repo, g_type_from_name ("GCancellable"));
  g_assert (info != NULL);

  exit(0);
}
