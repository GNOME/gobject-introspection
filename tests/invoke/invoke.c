#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

#include <glib.h>
#include <girepository.h>

int
main (int argc, char *argv[])
{
  const gchar *testfns = "./testfns.la";
  GModule *handle;
  GIRepository *rep;
  GIBaseInfo *info;
  GIFunctionInfo *function;
  GArgument in_args[3];
  GArgument out_args[3];
  GArgument retval;
  gint res;
  gchar *blurb;
  gint len;
  GError *error = NULL;
  const gchar *name;
  
  g_type_init ();

  rep = g_irepository_get_default ();

  g_print ("before dlopening %s: %d infos in the repository\n", 
	   testfns,
	   g_irepository_get_n_infos (rep, "test"));

  if (argc == 1)
    {
      handle = g_module_open (testfns, 0);
      if (!handle)
	{
	  g_error ("module open failed: %s\n", g_module_error ());
	  return;
	}
    }
  else
    {
      name = g_irepository_register_file (rep, "test", &error);
      if (error)
	{
	  g_error ("Unable to load metadata 'test': %s", error->message);
	  return;
	}
      g_print ("Loaded %s from test.gmeta\n", name);
    }

  g_print ("after dlopening %s: %d infos in the repository\n", 
	   testfns,
	   g_irepository_get_n_infos (rep, "test"));

  /* test1 calculates x + 4, 
   * taking x as an in parameter
   * and returning the result 
   */
  info = g_irepository_find_by_name (rep, "test", "test1");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  retval.v_int = 0;
  in_args[0].v_int = 4;
  if (!g_function_info_invoke (function, in_args, 1, NULL, 0, &retval, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_assert (retval.v_int == 8);
  g_base_info_unref (info);
  
  /* test2 calculates x + 4, 
   * taking x as an in parameter
   * and storing the result in an out parameter
   */
  info = g_irepository_find_by_name (rep, "test", "test2");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  in_args[0].v_int = 5;
  res = 0;
  out_args[0].v_pointer = &res;
  if (!g_function_info_invoke (function, in_args, 1, out_args, 1, &retval, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_assert (res == 9);
  g_base_info_unref (info);
  
  /* test3 calculates x + 4, 
   * taking x as an inout parameter
   * and storing the result in the same parameter
   */
  info = g_irepository_find_by_name (rep, "test", "test3");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  res = 6;
  in_args[0].v_pointer = out_args[0].v_pointer = &res;
  if (!g_function_info_invoke (function, in_args, 1, out_args, 1, &retval, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_assert (res == 10);
  g_base_info_unref (info);

  /* test4 prints out a string
   */
  info = g_irepository_find_by_name (rep, "test", "test4");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  in_args[0].v_pointer = "hello world\n";
  if (!g_function_info_invoke (function, in_args, 1, NULL, 0, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_base_info_unref (info);

  /* test5 returns a string and a length
   */
  info = g_irepository_find_by_name (rep, "test", "test5");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  blurb = NULL;
  len = 0;
  out_args[0].v_pointer = &blurb;
  out_args[1].v_pointer = &len;
  if (!g_function_info_invoke (function, NULL, 0, out_args, 2, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);
  
  g_assert (strcmp (blurb, "hey there") == 0);
  g_assert (len == strlen (blurb));
  g_base_info_unref (info);
  
  /* test error handling */

#if 0
  /* test6 is not implemented */
  info = g_irepository_find_by_name (rep, "test", "test6");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  if (!g_function_info_invoke (function, NULL, 0, NULL, 0, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_base_info_unref (info);
  g_clear_error (&error);
#endif
  
  /* too few in arguments */
  info = g_irepository_find_by_name (rep, "test", "test2");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  if (!g_function_info_invoke (function, NULL, 0, NULL, 0, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_clear_error (&error);

  /* too few out arguments */
  if (!g_function_info_invoke (function, in_args, 1, NULL, 0, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_clear_error (&error);

  /* too many in arguments */
  if (!g_function_info_invoke (function, in_args, 2, out_args, 1, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_clear_error (&error);

  /* too many out arguments */
  if (!g_function_info_invoke (function, in_args, 1, out_args, 2, NULL, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_clear_error (&error);

  return 0;
}
