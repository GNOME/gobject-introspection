
#include "girepository.h"

#include <stdlib.h>
#include <unistd.h>


int
main(int argc, char **argv)
{
  GIRepository *repo;
  GTypelib *ret;
  GIBaseInfo *info;
  char *girdir;
  GArgument in_arg[1];
  GArgument ret_arg;
  GError *error;
  gboolean invoke_return;

  g_type_init ();

  repo = g_irepository_get_default ();

  girdir = g_build_filename (g_getenv ("top_builddir"), "gir", NULL);
  g_irepository_prepend_search_path (girdir);
  g_free (girdir);

  error = NULL;
  ret = g_irepository_require (repo, "GLib", NULL, 0, &error);
  g_assert (ret != NULL);
  g_assert (error == NULL);

  info = g_irepository_find_by_name (repo, "GLib", "file_read_link");
  g_assert (info != NULL);
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  g_assert (g_function_info_get_flags ((GIFunctionInfo *)info) & GI_FUNCTION_THROWS);

  in_arg[0].v_string = g_strdup ("non-existent-file/hope");
  error = NULL;
  invoke_return = g_function_info_invoke ((GIFunctionInfo *)info,
                                          in_arg,
                                          1,
                                          NULL,
                                          0,
                                          &ret_arg,
                                          &error);
  g_free(in_arg[0].v_string);

  g_assert (invoke_return == FALSE);
  g_assert (error != NULL);
  g_assert (error->domain == G_FILE_ERROR);
  g_assert (error->code == G_FILE_ERROR_NOENT);

  exit(0);
}
