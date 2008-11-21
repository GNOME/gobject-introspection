#ifndef __ANNOTATION_OBJECT_H__
#define __ANNOTATION_OBJECT_H__

#include <glib-object.h>

/**
 * AnnotationCallback:
 * @in: (in) (transfer none): array of ints
 *
 * Return value: (transfer none): array of ints
 */
typedef const gint* (*AnnotationCallback) (const gint *in);

/**
 * AnnotationListCallback:
 * @in: (in) (transfer none) (element-type utf8): list of strings
 *
 * Return value: (transfer container) (element-type utf8): list of strings
 */
typedef GList* (*AnnotationListCallback) (GList *in);

typedef struct _AnnotationObject          AnnotationObject;
typedef struct _AnnotationObjectClass     AnnotationObjectClass;

struct _AnnotationObject
{
  GObject parent_instance;
};

struct _AnnotationObjectClass
{
  GObjectClass parent_class;
};

GType    annotation_object_get_type (void);

gint     annotation_object_method       (AnnotationObject *object);
gint     annotation_object_out          (AnnotationObject *object,
					 int              *outarg);
GObject* annotation_object_create_object(AnnotationObject *object);
GObject* annotation_object_allow_none   (AnnotationObject *object,
					 const gchar      *somearg);
GObject* annotation_object_notrans      (AnnotationObject *object);
gint     annotation_object_inout        (AnnotationObject *object,
					 int              *inoutarg);
gint     annotation_object_inout2       (AnnotationObject *object,
					 int              *inoutarg);
gint     annotation_object_inout3       (AnnotationObject *object,
					 int              *inoutarg);
gint     annotation_object_in           (AnnotationObject *object,
					 int              *inarg);
gint     annotation_object_calleeowns   (AnnotationObject *object,
					 GObject          **toown);
gint     annotation_object_calleesowns  (AnnotationObject *object,
					 GObject          **toown1,
					 GObject          **toown2);
GList*   annotation_object_get_strings  (AnnotationObject *object);
GHashTable*annotation_object_get_hash   (AnnotationObject *object);
GSList*  annotation_object_get_objects  (AnnotationObject *object);

void     annotation_object_use_buffer   (AnnotationObject *object,
					 guchar           *bytes);

void     annotation_object_compute_sum  (AnnotationObject *object,
					 int              *nums);

void     annotation_object_compute_sum_n(AnnotationObject *object,
					 int              *nums,
					 int               n_nums);
void     annotation_object_compute_sum_nz(AnnotationObject *object,
                                          int             *nums,
                                          int              n_nums);
void     annotation_object_parse_args   (AnnotationObject *object,
                                         int              *argc,
                                         char           ***argv);

GObject* annotation_object_do_not_use   (AnnotationObject *object);


void     annotation_init (int *argc, char ***argv);
char **  annotation_return_array (int *length);

#endif /* __ANNOTATION_OBJECT_H__ */
