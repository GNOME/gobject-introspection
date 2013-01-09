/* doc-examples-obj.c */

#include "doc-examples-obj.h"

/**
 * DocExamplesObj:
 *
 * This is an example of how to document a class
 *
 * This class has a signal: #DocExamplesObj::signal-example.
 *
 * And also has a property: #DocExamplesObj:property-example.
 *
 * Since: 0.99
 */

G_DEFINE_TYPE (DocExamplesObj, doc_examples_obj, G_TYPE_OBJECT)

static void
doc_examples_obj_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  switch (property_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
doc_examples_obj_set_property (GObject      *object,
                               guint         property_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  switch (property_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
doc_examples_obj_class_init (DocExamplesObjClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GParamSpec *pspec;

  gobject_class->get_property = doc_examples_obj_get_property;
  gobject_class->set_property = doc_examples_obj_set_property;

  /**
   * DocExamplesObj::signal-example:
   * @obj:
   * @int_param: a parameter of type int
   * @float_param: a parameter of type float
   * @pointer_param: A pointer to @obj's thingy --
   *   pass @int_param if you really want to.
   *
   * This is an example of how to document a signal.
   *
   * Since: 0.99
   */
  g_signal_new ("signal-example",
      G_TYPE_FROM_CLASS (gobject_class),
      G_SIGNAL_RUN_LAST,
      0, NULL, NULL,
      NULL,
      G_TYPE_NONE, 3, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_POINTER);

  /**
   * DocExamplesObj:property-example:
   *
   * This is an example of how to document a property.
   *
   * Type: GLib.HashTable(utf8,gint8)
   * Transfer: container
   *
   * Since: 0.99
   */
  pspec = g_param_spec_boxed ("property-example",
                              "Example property",
                              "A contained GHashTable",
                              G_TYPE_HASH_TABLE,
                              G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class,
                                   1,
                                   pspec);
}

static void
doc_examples_obj_init (DocExamplesObj *self)
{

}

DocExamplesObj *
doc_examples_obj_new (void)
{
  return g_object_new (DOC_EXAMPLES_TYPE_OBJ, NULL);
}

/**
 * doc_examples_obj_method:
 * @first_arg: A #DocExamplesObj.
 * @second_arg: second argument
 * @boolean_arg: You should always pass %TRUE.
 * @pointer_arg: (allow-none): If not %NULL, do a thing.
 *   Pass @first_arg if you want to sometimes. You can
 *   also pass @second_arg, or even @boolean_arg.
 * @string: A NUL-terminated string.
 *
 * This is an example of how to document a method.
 *
 * You should call this on a #DocExamplesObj that was
 * created with doc_examples_obj_new().
 *
 * This should be a %FALSEALARM.
 *
 * Since: 0.99
 *
 * Returns: Either %FALSE or something %FALSE-y.
 */
gboolean
doc_examples_obj_method (DocExamplesObj *self, gint first_arg, gfloat second_arg,
                         gboolean boolean_arg, gpointer pointer_arg, gchar *string)
{
  return FALSE;
}

/**
 * doc_examples_obj_static_method:
 * @out_arg: (out) (allow-none): a pointer to int, or %NULL to ignore
 *
 * This is an example of a function with an out argument
 * and a return value.
 *
 * Returns: %TRUE if @out_arg is valid, %FALSE otherwise
 */
gboolean
doc_examples_obj_static_method (gint *out_arg)
{
  if (out_arg)
    *out_arg = 42;

  return TRUE;
}

/**
 * doc_examples_array_function:
 * @out_len: (out): the length of the returned array
 *
 * This function returns an array with an explicit length,
 * and the length should be invisible in most introspected bindings.
 *
 * Returns: (array length=out_len) (transfer full): an array of numbers.
 */
gint *
doc_examples_array_function (gint *out_len)
{
  gint *array;
  int i, n = 3;

  array = g_new(int, n);
  for (i = 0; i < n; i++)
    array[i] = i;

  *out_len = n;
  return array;
}

/**
 * doc_examples_callback_function:
 * @callback: Just Call Me Maybe
 * @user_data: your stuff
 * @destroy_notify: how to get rid of @user_data
 *
 * This is a function that takes a callback. Different languages
 * will expose this in different ways (e.g. Python keeps the
 * @user_data parameter, while JS doesn't)
 */
void
doc_examples_callback_function (DocExamplesCallback callback,
                                gpointer            user_data,
                                GDestroyNotify      destroy_notify)
{
  gchar *result;

  result = callback (42, 17);
  g_free (result);

  if (user_data && destroy_notify)
    destroy_notify (user_data);
}
