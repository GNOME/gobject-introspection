#include <stdlib.h>
#include <string.h>

#include <glib.h>
#include <girepository.h>

typedef struct
{
  int foo;
} TestStruct;


int
main (int argc, char *argv[])
{
  const gchar *testfns = "./testfns.la";
  GModule *handle;
  GIRepository *rep;
  GIBaseInfo *info;
  GIFunctionInfo *function;
  GIStructInfo *record;
  GArgument in_args[3];
  GArgument out_args[3];
  GArgument retval;
  gint res;
  gchar *blurb;
  guint len;
  GError *error = NULL;
  TestStruct *s;
  
  g_type_init ();

  rep = g_irepository_get_default ();

  g_assert (!g_irepository_is_registered (NULL, "testfns", NULL));
  
  handle = g_module_open (testfns, 0);
  if (!handle)
    {
      g_error ("module open failed: %s\n", g_module_error ());
      return 1;
    }

  g_assert (g_irepository_is_registered (NULL, "testfns", NULL));

#if 0
  g_print ("after dlopening %s: %d infos in the repository\n", 
	   testfns,
	   g_irepository_get_n_infos (rep, "testfns"));
#endif

  /* test1 calculates x + 4, 
   * taking x as an in parameter
   * and returning the result 
   */
  info = g_irepository_find_by_name (rep, "testfns", "test1");  
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
  info = g_irepository_find_by_name (rep, "testfns", "test2");  
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
  info = g_irepository_find_by_name (rep, "testfns", "test3");  
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
  info = g_irepository_find_by_name (rep, "testfns", "test4");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  in_args[0].v_pointer = "hello world\n";
  if (!g_function_info_invoke (function, in_args, 1, NULL, 0, &retval, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);

  g_base_info_unref (info);

  /* test5 returns a string and a length
   */
  info = g_irepository_find_by_name (rep, "testfns", "test5");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  blurb = NULL;
  len = 0;
  out_args[0].v_pointer = &blurb;
  out_args[1].v_pointer = &len;
  if (!g_function_info_invoke (function, NULL, 0, out_args, 2, &retval, &error))
    g_print ("Invokation of %s failed: %s\n",
	     g_base_info_get_name (info),
	     error->message);
  
  g_assert (strcmp (blurb, "hey there") == 0);
  g_assert (len == strlen (blurb));
  g_base_info_unref (info);
  

  /* test GList*/
  g_print ("Test 6\n");
  info = g_irepository_find_by_name (rep, "testfns", "test6");
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  {
    GList *list = NULL;
    list = g_list_prepend (list, GINT_TO_POINTER(1));
    list = g_list_prepend (list, GINT_TO_POINTER(2));
    retval.v_int = 0;
    in_args[0].v_pointer = out_args[0].v_pointer = list;
    if (!g_function_info_invoke (function, in_args, 1, NULL, 0, &retval, &error))
      g_print ("Invokation of %s failed: %s\n",
	       g_base_info_get_name (info),
	       error->message);

    g_print("returned %d\n", retval.v_int);
    g_assert (retval.v_int == 2);
    g_list_free (list);
  }

  g_base_info_unref (info);
  g_clear_error (&error);

  /* test GList more, transfer ownership*/
  g_print ("Test 7\n");
  info = g_irepository_find_by_name (rep, "testfns", "test7");
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  {
    GList *list = NULL;
    list = g_list_prepend (list, g_strdup("there..."));
    list = g_list_prepend (list, g_strdup("Hey "));
    retval.v_pointer = NULL;
    in_args[0].v_pointer = out_args[0].v_pointer = list;
    if (!g_function_info_invoke (function, in_args, 1, NULL, 0, &retval, &error))
      g_print ("Invokation of %s failed: %s\n",
	       g_base_info_get_name (info),
	       error->message);

    g_print("returned %p\n", retval.v_pointer);
    g_assert (strcmp(retval.v_pointer, "Hey there...")==0);
    g_list_foreach (list, (GFunc) g_free, NULL);
    g_list_free (list);
#if 0
    g_assert (g_callable_info_get_caller_owns ((GICallableInfo *)function) ==
	      GI_TRANSFER_EVERYTHING);
#endif    
    g_free (retval.v_pointer);
  }

  g_base_info_unref (info);
  g_clear_error (&error);

  g_print("Test 8\n");
  info = g_irepository_find_by_name (rep, "testfns", "TestStruct");
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_STRUCT);
  record = (GIStructInfo *)info;
  info = (GIBaseInfo*)g_struct_info_find_method (record, "test8");
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;
  g_assert (g_function_info_get_flags (function) & GI_FUNCTION_IS_CONSTRUCTOR);

  {
    in_args[0].v_int = 42;
    retval.v_pointer = NULL;

    if (!g_function_info_invoke (function, in_args, 1, NULL, 0, &retval, &error))
      g_print ("Invocation of %s failed: %s\n",
               g_base_info_get_name (info),
               error->message);

    s = (TestStruct *)retval.v_pointer;

    g_assert(s->foo == 42);

  }

  g_base_info_unref (info);
  g_clear_error (&error);

  g_print("Test 9\n");
  info = (GIBaseInfo*)g_struct_info_find_method (record, "test9");
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;
  g_assert (g_function_info_get_flags (function) & GI_FUNCTION_IS_METHOD);

  {
    TestStruct s = { 42 };
    int out_i;

    retval.v_pointer = NULL;
    in_args[0].v_pointer = &s;
    out_args[0].v_pointer = &out_i;
    if (!g_function_info_invoke (function, in_args, 1, out_args, 1, &retval, &error))
      g_print ("Invocation of %s failed: %s\n",
               g_base_info_get_name (info),
               error->message);

    g_assert(out_i == 42);
  }

  g_base_info_unref (info);
  g_base_info_unref ((GIBaseInfo*)record);
  g_clear_error (&error);


  /* test error handling */

#if 0
  /* "broken" is in the typelib but not in the .so*/
  info = g_irepository_find_by_name (rep, "testfns", "broken");  
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
  info = g_irepository_find_by_name (rep, "testfns", "test2");  
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_FUNCTION);
  function = (GIFunctionInfo *)info;

  g_assert (!g_function_info_invoke (function, NULL, 0, NULL, 0, NULL, &error) &&
	    error != NULL &&
	    error->domain == G_INVOKE_ERROR &&
	    error->code == G_INVOKE_ERROR_ARGUMENT_MISMATCH);

  g_clear_error (&error);

  /* too few out arguments */
  g_assert (!g_function_info_invoke (function, in_args, 1, NULL, 0, NULL, &error) &&
	    error != NULL &&
	    error->domain == G_INVOKE_ERROR &&
	    error->code == G_INVOKE_ERROR_ARGUMENT_MISMATCH);

  g_clear_error (&error);

  /* too many in arguments */
  g_assert (!g_function_info_invoke (function, in_args, 2, out_args, 1, NULL, &error) &&
	    error != NULL &&
	    error->domain == G_INVOKE_ERROR &&
	    error->code == G_INVOKE_ERROR_ARGUMENT_MISMATCH);

  g_clear_error (&error);

  /* too many out arguments */
  g_assert (!g_function_info_invoke (function, in_args, 1, out_args, 2, NULL, &error) &&
	    error != NULL &&
	    error->domain == G_INVOKE_ERROR &&
	    error->code == G_INVOKE_ERROR_ARGUMENT_MISMATCH);

  g_clear_error (&error);

  return 0;
}
