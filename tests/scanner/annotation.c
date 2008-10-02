#include "annotation.h"

static char backslash_parsing_tester = '\\';

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
 * @outarg: <out>: This is an argument test
 * Return value: an int
 */
gint
annotation_object_in (AnnotationObject *object, int *outarg)
{
  *outarg = 2;
  return 1;
}

/**
 * annotation_object_in:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @outarg: <in>: This is an argument test
 * Return value: an int
 */
gint
annotation_object_out (AnnotationObject *object, int *outarg)
{
  *outarg = 2;
  return 1;
}


/**
 * annotation_object_inout:
 * @object: a #GObject
 *
 * This is a test for out arguments
 *
 * @inoutarg: <inout>: This is an argument test
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
 *
 * This is a second test for out arguments
 *
 * @inoutarg: <inout>: This is an argument test
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
 *
 * This is a 3th test for out arguments
 *
 * @inoutarg: <inout,allow-none>: This is an argument test
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
 *
 * This is a test for out arguments
 *
 * @toown: <out,transfer>: a #GObject
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
 *
 * This is a test for out arguments
 *
 * @toown1: <out,transfer>: a #GObject
 * @toown2: <out,transfer>: a #GObject
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
 * Return value: <char*,transfer>: list of strings
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
 * Return value: <AnnotationObject*>: list of objects
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
 * Return value: <transfer>: The object
 **/
GObject* 
annotation_object_create_object (AnnotationObject *object)
{
	return g_object_ref (object);
}

void     
annotation_object_use_buffer   (AnnotationObject *object,
				guchar           *bytes)
{
  
}

/**
 * annotation_object_compute_sum:
 * @object: a #GObject
 * @nums: <array>: Sequence of numbers
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
 * @nums: <array,length=2>: Sequence of numbers
 * @nums: Length of number array
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
 * annotation_object_allow_none: 
 * @object: a #GObject
 * @somearg: <allow-none>: 
 **/
GObject*
annotation_object_allow_none (AnnotationObject *object, gchar *somearg)
{
}

/**
 * annotation_object_do_not_use: 
 * @object: a #GObject
 *
 * Deprecated: 0.12: Use annotation_object_create_object() instead.
 **/
GObject*
annotation_object_do_not_use (AnnotationObject *object)
{
  return NULL;
}

static char backslash_parsing_tester_2 = '\\';
