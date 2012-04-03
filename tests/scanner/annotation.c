/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
#include "annotation.h"

char backslash_parsing_tester = '\\';

G_DEFINE_TYPE (AnnotationObject, annotation_object, G_TYPE_OBJECT);

enum {
  PROP_0,
  PROP_STRING_PROPERTY,
  PROP_FUNCTION_PROPERTY,
  PROP_TAB_PROPERTY
};

enum {
  STRING_SIGNAL,
  LIST_SIGNAL,
  DOC_EMPTY_ARG_PARSING,
  ATTRIBUTE_SIGNAL,
  LAST_SIGNAL
};

static guint annotation_object_signals[LAST_SIGNAL] = { 0 };

static void
annotation_object_set_property (GObject         *object,
                                guint            prop_id,
                                const GValue    *value,
                                GParamSpec      *pspec)
{
  switch (prop_id)
    {
    case PROP_STRING_PROPERTY:
      break;
    case PROP_FUNCTION_PROPERTY:
      break;
    case PROP_TAB_PROPERTY:
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
annotation_object_get_property (GObject         *object,
                                guint            prop_id,
                                GValue          *value,
                                GParamSpec      *pspec)
{
  switch (prop_id)
    {
    case PROP_STRING_PROPERTY:
      break;
    case PROP_FUNCTION_PROPERTY:
      break;
    case PROP_TAB_PROPERTY:
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
annotation_object_class_init (AnnotationObjectClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = annotation_object_set_property;
  gobject_class->get_property = annotation_object_get_property;

  /**
   * AnnotationObject::string-signal:
   * @annotation: the annotation object
   * @string: (type utf8): a string
   *
   * This is a signal which has a broken signal handler,
   * it says it's pointer but it's actually a string.
   *
   * Since: 1.0
   * Deprecated: 1.2: Use other-signal instead
   */
  annotation_object_signals[STRING_SIGNAL] =
    g_signal_new ("string-signal",
		  G_OBJECT_CLASS_TYPE (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  0,
		  NULL, NULL,
		  (GSignalCMarshaller)g_cclosure_marshal_VOID__POINTER,
		  G_TYPE_NONE, 1, G_TYPE_POINTER);

  /**
   * AnnotationObject::list-signal:
   * @annotation: the annotation object
   * @list: (type GLib.List) (element-type utf8) (transfer container): a list of strings
   *
   * This is a signal which takes a list of strings, but it's not
   * known by GObject as it's only marked as G_TYPE_POINTER
   */
  annotation_object_signals[LIST_SIGNAL] =
    g_signal_new ("list-signal",
		  G_OBJECT_CLASS_TYPE (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  0,
		  NULL, NULL,
		  (GSignalCMarshaller)g_cclosure_marshal_VOID__POINTER,
		  G_TYPE_NONE, 1, G_TYPE_POINTER);

  /**
   * AnnotationObject::doc-empty-arg-parsing:
   * @annotation: the annotation object
   * @arg1:
   *
   * This signal tests an empty document argument (@arg1)
   */
  annotation_object_signals[DOC_EMPTY_ARG_PARSING] =
    g_signal_new ("doc-empty-arg-parsing",
		  G_OBJECT_CLASS_TYPE (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  0,
		  NULL, NULL,
		  (GSignalCMarshaller)g_cclosure_marshal_VOID__POINTER,
		  G_TYPE_NONE, 1, G_TYPE_POINTER);

  /**
   * AnnotationObject::attribute-signal:
   * @annotation: the annotation object
   * @arg1: (attribute some.annotation.foo1 val1): a value
   * @arg2: (attribute some.annotation.foo2 val2): another value
   *
   * This signal tests a signal with attributes.
   *
   * Returns: (attribute some.annotation.foo3 val3): the return value
   */
  annotation_object_signals[ATTRIBUTE_SIGNAL] =
    g_signal_new ("attribute-signal",
		  G_OBJECT_CLASS_TYPE (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  0,
		  NULL, NULL,
		  NULL, /* marshaller */
		  G_TYPE_STRING,
                  2,
                  G_TYPE_STRING,
                  G_TYPE_STRING);

  /**
   * AnnotationObject:string-property:
   *
   * This is a property which is a string
   *
   * Since: 1.0
   * Deprecated: 1.2: Use better-string-property instead
   */
  g_object_class_install_property (gobject_class,
                                   PROP_STRING_PROPERTY,
                                   g_param_spec_string ("string-property",
                                                        "String property",
                                                        "This property is a string",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
  /**
   * AnnotationObject:function-property:
   *
   * Type: AnnotationCallback
   */
  g_object_class_install_property (gobject_class,
                                   PROP_FUNCTION_PROPERTY,
                                   g_param_spec_pointer ("function-property",
                                                         "Function property",
                                                         "This property is a function pointer",
                                                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT));

	  /**
	   * AnnotationObject:tab-property:
	   *
	   * This is a property annotation intentionally indented with a mix
	   * of tabs and strings to test the tab handling capabilities of the scanner.
	   *
	   * Since: 1.2
	   */
  g_object_class_install_property (gobject_class,
                                   PROP_TAB_PROPERTY,
                                   g_param_spec_string ("tab-property",
                                                        "Tab property",
                                                        "This property is a thing",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
}

static void
annotation_object_init (AnnotationObject *object)
{

}

/**
 * annotation_object_method:
 * @object: a #GObject
 *
 * Return value: an int
 **/
gint
annotation_object_method (AnnotationObject *object)
{
  return 1;
}

/**
 * annotation_object_out:
 * @object: a #GObject
 * @outarg: (out): This is an argument test
 *
 * This is a test for out arguments
 *
 * Return value: an int
 */
gint
annotation_object_out (AnnotationObject *object, int *outarg)
{
  *outarg = 2;
  return 1;
}

/**
 * annotation_object_in:
 * @object: a #GObject
 * @inarg: (in) (transfer none): This is an argument test
 *
 * This is a test for in arguments
 *
 * Return value: an int
 */
gint
annotation_object_in (AnnotationObject *object, int *inarg)
{
  return *inarg;
}


/**
 * annotation_object_inout:
 * @object: a #GObject
 * @inoutarg: (inout): This is an argument test
 *
 * This is a test for out arguments
 *
 * Return value: an int
 */
gint
annotation_object_inout (AnnotationObject *object, int *inoutarg)
{
  return *inoutarg += 1;
}

/**
 * annotation_object_inout2:
 * @object: a #GObject
 * @inoutarg: (inout): This is an argument test
 *
 * This is a second test for out arguments
 *
 * Return value: an int
 */
gint
annotation_object_inout2 (AnnotationObject *object, int *inoutarg)
{
  return *inoutarg += 1;
}


/**
 * annotation_object_inout3:
 * @object: a #GObject
 * @inoutarg: (inout) (allow-none): This is an argument test
 *
 * This is a 3th test for out arguments
 *
 * Return value: an int
 */
gint
annotation_object_inout3 (AnnotationObject *object, int *inoutarg)
{
  if (inoutarg)
    return *inoutarg + 1;
  return 1;
}

/**
 * annotation_object_calleeowns:
 * @object: a #GObject
 * @toown: (out): a #GObject
 *
 * This is a test for out arguments; GObject defaults to transfer
 *
 * Return value: an int
 */
gint
annotation_object_calleeowns (AnnotationObject *object, GObject **toown)
{
  return 1;
}


/**
 * annotation_object_calleesowns:
 * @object: a #GObject
 * @toown1: (out) (transfer full): a #GObject
 * @toown2: (out) (transfer none): a #GObject
 *
 * This is a test for out arguments, one transferred, other not
 *
 * Return value: an int
 */
gint
annotation_object_calleesowns (AnnotationObject *object,
			       GObject **toown1,
			       GObject **toown2)
{
  return 1;
}


/**
 * annotation_object_get_strings:
 * @object: a #GObject
 *
 * This is a test for returning a list of strings, where
 * each string needs to be freed.
 *
 * Return value: (element-type utf8) (transfer full): list of strings
 */
GList*
annotation_object_get_strings (AnnotationObject *object)
{
  GList *list = NULL;
  list = g_list_prepend (list, g_strdup ("annotation"));
  list = g_list_prepend (list, g_strdup ("bar"));
  return list;
}

/**
 * annotation_object_get_hash:
 * @object: a #GObject
 *
 * This is a test for returning a hash table mapping strings to
 * objects.
 *
 * Return value: (element-type utf8 GObject) (transfer full): hash table
 */
GHashTable*
annotation_object_get_hash (AnnotationObject *object)
{
  GHashTable *hash = g_hash_table_new_full (g_str_hash, g_str_equal,
					    g_free, g_object_unref);
  g_hash_table_insert (hash, g_strdup ("one"), g_object_ref (object));
  g_hash_table_insert (hash, g_strdup ("two"), g_object_ref (object));
  return hash;
}

/**
 * annotation_object_with_voidp:
 * @data: Opaque pointer handle
 */
void
annotation_object_with_voidp (AnnotationObject *object, void *data)
{

}

/**
 * annotation_object_get_objects:
 * @object: a #GObject
 *
 * This is a test for returning a list of objects.
 * The list itself should be freed, but not the internal objects,
 * intentionally similar example to gtk_container_get_children
 *
 * Return value: (element-type AnnotationObject) (transfer container): list of objects
 */
GSList*
annotation_object_get_objects (AnnotationObject *object)
{
  GSList *list = NULL;
  list = g_slist_prepend (list, object);
  return list;
}

/**
 * annotation_object_create_object:
 * @object: a #GObject
 *
 * Test returning a caller-owned object
 *
 * Return value: (transfer full): The object
 **/
GObject*
annotation_object_create_object (AnnotationObject *object)
{
	return g_object_ref (object);
}

/**
 * annotation_object_use_buffer:
 * @object: a #GObject
 *
 **/
void
annotation_object_use_buffer   (AnnotationObject *object,
				guchar           *bytes)
{

}

/**
 * annotation_object_compute_sum:
 * @object: a #GObject
 * @nums: (array): Sequence of numbers
 *
 * Test taking a zero-terminated array
 **/
void
annotation_object_compute_sum  (AnnotationObject *object,
				int              *nums)
{

}

/**
 * annotation_object_compute_sum_n:
 * @object: a #GObject
 * @nums: (array length=n_nums zero-terminated=0): Sequence of
 *   numbers that are zero-terminated
 * @n_nums: Length of number array
 *
 * Test taking an array with length parameter
 **/
void
annotation_object_compute_sum_n(AnnotationObject *object,
				int              *nums,
				int               n_nums)
{

}

/**
 * annotation_object_compute_sum_nz:
 * @object: a #AnnotationObject
 * @nums: (array length=n_nums zero-terminated=1): Sequence of numbers that
 * are zero-terminated
 * @n_nums: Length of number array
 *
 * Test taking a zero-terminated array with length parameter
 **/
void
annotation_object_compute_sum_nz(AnnotationObject *object,
                                 int             *nums,
                                 int              n_nums)
{

}

/**
 * annotation_object_parse_args:
 * @object: a #AnnotationObject
 * @argc: (inout): Length of the argument vector
 * @argv: (inout) (array length=argc zero-terminated=1): Argument vector
 *
 * Test taking a zero-terminated array with length parameter
 **/
void
annotation_object_parse_args(AnnotationObject *object,
                             int              *argc,
                             char           ***argv)
{

}

/**
 * annotation_object_string_out:
 * @object: a #AnnotationObject
 * @str_out: (out) (transfer full): string return value
 *
 * Test returning a string as an out parameter
 *
 * Returns: some boolean
 **/
gboolean
annotation_object_string_out(AnnotationObject *object,
                             char            **str_out)
{
  return FALSE;
}

/**
 * annotation_object_foreach:
 * @object: a #AnnotationObject
 * @func: (scope call): Callback to invoke
 * @user_data: Callback user data
 *
 * Test taking a call-scoped callback
 **/
void
annotation_object_foreach (AnnotationObject *object,
                           AnnotationForeachFunc func,
                           gpointer user_data)
{
  
}

/**
 * annotation_object_set_data:
 * @object: a #AnnotationObject
 * @data: (array length=length): The data
 * @length: Length of the data
 *
 * Test taking a guchar * with a length.
 **/
void
annotation_object_set_data (AnnotationObject *object,
                            const guchar *data,
                            gsize length)
{
  
}

/**
 * annotation_object_set_data2:
 * @object: a #AnnotationObject
 * @data: (array length=length) (element-type gint8): The data
 * @length: Length of the data
 *
 * Test taking a gchar * with a length.
 **/
void
annotation_object_set_data2 (AnnotationObject *object,
                             const gchar *data,
                             gsize length)
{
  
}

/**
 * annotation_object_set_data3:
 * @object: a #AnnotationObject
 * @data: (array length=length) (element-type guint8): The data
 * @length: Length of the data
 *
 * Test taking a gchar * with a length, overriding the array element
 * type.
 **/
void
annotation_object_set_data3 (AnnotationObject *object,
                             gpointer data,
                             gsize length)
{
  
}

/**
 * annotation_object_allow_none:
 * @object: a #GObject
 * @somearg: (allow-none):
 *
 * Returns: (transfer none): %NULL always
 **/
GObject*
annotation_object_allow_none (AnnotationObject *object, const gchar *somearg)
{
  return NULL;
}

/**
 * annotation_object_notrans:
 * @object: a #GObject
 *
 * Returns: (transfer none): An object, not referenced
 **/

GObject*
annotation_object_notrans (AnnotationObject *object)
{
  return NULL;
}

/**
 * annotation_object_do_not_use:
 * @object: a #GObject
 *
 * Returns: (transfer none): %NULL always
 * Deprecated: 0.12: Use annotation_object_create_object() instead.
 **/
GObject*
annotation_object_do_not_use (AnnotationObject *object)
{
  return NULL;
}

/**
 * annotation_object_watch: (skip)
 * @object: A #AnnotationObject
 * @func: The callback
 * @user_data: The callback data
 *
 * This is here just for the sake of being overriden by its
 * annotation_object_watch_full().
 */
void
annotation_object_watch (AnnotationObject *object,
                         AnnotationForeachFunc func,
                         gpointer user_data)
{
}

/**
 * annotation_object_watch_full:
 * @object: A #AnnotationObject
 * @func: The callback
 * @user_data: The callback data
 * @destroy: Destroy notification
 *
 * Test overriding via the "Rename To" annotation.
 *
 * Rename to: annotation_object_watch
 */
void
annotation_object_watch_full (AnnotationObject *object,
                              AnnotationForeachFunc func,
                              gpointer user_data,
                              GDestroyNotify destroy)
{
}

/**
 * annotation_object_hidden_self:
 * @object: (type AnnotationObject): A #AnnotationObject
 **/
void
annotation_object_hidden_self (gpointer object)
{
}

/**
 * annotation_init:
 * @argc: (inout): The number of args. 
 * @argv: (inout) (array length=argc): The arguments.
 **/
void
annotation_init (int *argc, char ***argv)
{

}

/**
 * annotation_return_array:
 * @length: (out): Number of return values
 *
 * Return value: (transfer full) (array length=length): The return value
 **/
char **
annotation_return_array (int *length)
{
  return NULL;
}

/**
 * annotation_string_zero_terminated:
 *
 * Return value: (transfer full) (array zero-terminated=1): The return value
 **/
char **
annotation_string_zero_terminated (void)
{
  return NULL;
}

/**
 * annotation_string_zero_terminated_out:
 * @out: (array zero-terminated=1) (inout):
 **/
void
annotation_string_zero_terminated_out (char ***out)
{
}

/**
 * annotation_versioned:
 *
 * Since: 0.6
 **/
void
annotation_versioned (void)
{
}

/**
 * annotation_string_array_length:
 * @n_properties:
 * @properties: (array length=n_properties) (element-type utf8):
 */
void
annotation_string_array_length (guint n_properties, const gchar * const properties[])
{
}

/**
 * annotation_object_extra_annos:
 *
 * Attributes: (org.foobar testvalue)
 */
void
annotation_object_extra_annos (AnnotationObject *object)
{
}

/**
 * annotation_custom_destroy:
 * @callback: (destroy destroy) (closure data): Destroy notification
 *
 * Test messing up the heuristic of closure/destroy-notification
 * detection, and fixing it via annotations.
 */
void
annotation_custom_destroy (AnnotationCallback callback,
                           AnnotationNotifyFunc destroy,
                           gpointer data)
{
}

/**
 * annotation_get_source_file:
 *
 * Return value: (type filename) (transfer full): Source file
 */
char *
annotation_get_source_file (void)
{
  return NULL;
}

/**
 * annotation_set_source_file:
 * @fname: (type filename): Source file
 *
 */
void
annotation_set_source_file (const char *fname)
{
}

/**
 * annotation_ptr_array:
 * @array: (element-type GLib.Value): the array
 */
void
annotation_ptr_array (GPtrArray *array)
{
}

/**
 * annotation_attribute_func:
 * @object: A #AnnotationObject.
 * @data: (attribute some.annotation value) (attribute another.annotation blahvalue): Some data.
 *
 * Returns: (attribute some.other.annotation value2) (attribute yet.another.annotation another_value): The return value.
 */
gint
annotation_attribute_func (AnnotationObject *object,
                           const gchar      *data)
{
  return 42;
}

/**
 * annotation_invalid_annotation:
 * @foo: some text (e.g. example) or else
 */
void
annotation_invalid_annotation (int foo)
{

}


char backslash_parsing_tester_2 = '\\';


/**
 * annotation_test_parsing_bug630862:
 *
 * See https://bugzilla.gnome.org/show_bug.cgi?id=630862
 *
 * Returns: (transfer none): An object, note the colon:in here
 */
GObject  *
annotation_test_parsing_bug630862 (void)
{
  return NULL;
}


/** 
 * annotation_space_after_comment_bug631690:
 *
 * Explicitly test having a space after the ** here.
 */
void
annotation_space_after_comment_bug631690 (void)
{
}

/**
 * annotation_return_filename:
 *
 * Returns: (type filename): An annotated filename
 */
gchar*
annotation_return_filename (void)
{
  return "a utf-8 filename";
}

/**
 * annotation_transfer_floating:
 *
 * Returns: (transfer floating): A floating object
 */
GObject *
annotation_transfer_floating(void)
{
  return NULL;
}
