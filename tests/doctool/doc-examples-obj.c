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
      G_TYPE_NONE, 2, G_TYPE_UINT, G_TYPE_UINT);

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
 * @string: A %NULL-terminated string.
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
