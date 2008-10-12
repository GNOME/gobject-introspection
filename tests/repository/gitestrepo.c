
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
  GType gtype;

  g_type_init ();

  repo = g_irepository_get_default ();

  ret = g_irepository_require (repo, "Gio", NULL, 0, &error);
  g_assert (ret);
  g_assert (error == NULL);

  info = g_irepository_find_by_name (repo, "Gio", "Cancellable");
  g_assert (info != NULL);
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_OBJECT);

  gtype = g_registered_type_info_get_g_type ((GIRegisteredTypeInfo *)info);
  g_assert (g_type_is_a (gtype, G_TYPE_OBJECT));

  info = g_irepository_find_by_gtype (repo, g_type_from_name ("GCancellable"));
  g_assert (info != NULL);

  exit(0);
}
