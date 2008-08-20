#include "annotation.h"

G_DEFINE_TYPE (AnnotationObject, annotation_object, G_TYPE_OBJECT);

static void
annotation_object_class_init (AnnotationObjectClass *klass)
{

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
 *
 * This is a test for out arguments
 *
 * @outarg: (out): This is an argument test
 * Return value: an int
 */
gint
annotation_object_in (AnnotationObject *object, int *outarg)
{
	return 1;
}

/**
 * annotation_object_in:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @outarg: (in): This is an argument test
 * Return value: an int
 */
gint
annotation_object_out (AnnotationObject *object, int *outarg)
{
	return 1;
}


/**
 * annotation_object_inout:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @inoutarg: (inout): This is an argument test
 * Return value: an int
 */
gint
annotation_object_inout (AnnotationObject *object, int *inoutarg)
{
	return 1;
}

/**
 * annotation_object_inout2:
 * @object: a #GObject
 *
 * This is a second test for out arguments
 *
 * @inoutarg: (in) (out): This is an argument test
 * Return value: an int
 */
gint
annotation_object_inout2 (AnnotationObject *object, int *inoutarg)
{
	return 1;
}


/**
 * annotation_object_inout3:
 * @object: a #GObject
 *
 * This is a 3th test for out arguments
 *
 * @inoutarg: (in-out) (allow-none): This is an argument test
 * Return value: an int
 */
gint
annotation_object_inout3 (AnnotationObject *object, int *inoutarg)
{
	return 1;
}

/**
 * annotation_object_calleeowns:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @toown: (callee-owns): a #GObject
 * Return value: an int
 */
gint
annotation_object_calleeowns (AnnotationObject *object, GObject *toown)
{
	return 1;
}


/**
 * annotation_object_calleesowns:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @toown1: (callee-owns): a #GObject
 * @toown2: (callee-owns): a #GObject
 * Return value: an int
 */
gint
annotation_object_calleesowns (AnnotationObject *object,
			       GObject *toown1,
			       GObject *toown2)
{
	return 1;
}


/**
 * annotation_object_get_strings:
 * @object: a #GObject
 *
 * This is a test for returning a list of strings
 *
 * Return value: (seq char* (callee-owns)) (caller-owns): list of strings
 */
GList*
annotation_object_get_strings (AnnotationObject *object)
{
  GList *list = NULL;
  list = g_list_prepend (list, "annotation");
  list = g_list_prepend (list, "bar");
  return list;
}


/**
 * annotation_object_with_voidp
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
 * Return value: (seq AnnotationObject* (callee-owns)) (caller-owns): a list
 *               of strings
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
 * Return value: (caller-owns): The object
 **/
GObject*
annotation_object_create_object (AnnotationObject *object)
{
	return g_object_ref (object);
}

/**
 * annotation_object_allow_none: 
 * @object: a #GObject
 * @allow_none: (allow-none): 
 **/
GObject*
annotation_object_allow_none (AnnotationObject *object, gchar *allow_none)
{
}
