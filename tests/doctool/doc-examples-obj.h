/* doc-examples-obj.h */

#ifndef _DOC_EXAMPLES_OBJ_H
#define _DOC_EXAMPLES_OBJ_H

#include <glib-object.h>

G_BEGIN_DECLS

#define DOC_EXAMPLES_TYPE_OBJ doc_examples_obj_get_type()

#define DOC_EXAMPLES_OBJ(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  DOC_EXAMPLES_TYPE_OBJ, DocExamplesObj))

#define DOC_EXAMPLES_OBJ_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  DOC_EXAMPLES_TYPE_OBJ, DocExamplesObjClass))

#define DOC_EXAMPLES_IS_OBJ(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  DOC_EXAMPLES_TYPE_OBJ))

#define DOC_EXAMPLES_IS_OBJ_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  DOC_EXAMPLES_TYPE_OBJ))

#define DOC_EXAMPLES_OBJ_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  DOC_EXAMPLES_TYPE_OBJ, DocExamplesObjClass))

typedef struct _DocExamplesObj DocExamplesObj;
typedef struct _DocExamplesObjClass DocExamplesObjClass;

struct _DocExamplesObj
{
  GObject parent;
};

struct _DocExamplesObjClass
{
  GObjectClass parent_class;

  /**
   * DocExamplesObjClass::vfunc:
   * @self:
   * @first_arg: first argument
   *
   * This is an example of how to document a vfunc.
   *
   * Since: 0.99
   */
  void (*vfunc) (DocExamplesObj *self, gint first_arg);
};

GType doc_examples_obj_get_type (void) G_GNUC_CONST;

DocExamplesObj *doc_examples_obj_new (void);
gboolean doc_examples_obj_method (DocExamplesObj *self, gint first_arg, gfloat second_arg,
                                  gboolean boolean_arg, gpointer pointer_arg, gchar *string);

gboolean doc_examples_obj_static_method (gint *out_arg);

gint *doc_examples_array_function (gint *out_len);

/**
 * DocExamplesEnum:
 * @DOC_EXAMPLES_FOO: a foo
 * @DOC_EXAMPLES_BAR: a bar
 *
 * This is an example to document an enumeration.
 */
typedef enum {
  DOC_EXAMPLES_FOO,
  DOC_EXAMPLES_BAR
} DocExamplesEnum;

/**
 * DocExamplesCallback:
 * @one: first parameter
 * @two: second parameter
 *
 * Returns: something
 */
typedef gchar * (*DocExamplesCallback) (int one, int two);

void doc_examples_callback_function (DocExamplesCallback callback,
                                     gpointer            user_data,
                                     GDestroyNotify      destroy_notify);

G_END_DECLS

#endif /* _DOC_EXAMPLES_OBJ_H */
