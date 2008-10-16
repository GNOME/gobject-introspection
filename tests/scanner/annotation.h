#ifndef __ANNOTATION_OBJECT_H__
#define __ANNOTATION_OBJECT_H__

#include <glib-object.h>

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
					 gchar            *somearg);
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
GSList*  annotation_object_get_objects  (AnnotationObject *object);

void     annotation_object_use_buffer   (AnnotationObject *object,
					 guchar           *bytes);

void     annotation_object_compute_sum  (AnnotationObject *object,
					 int              *nums);

void     annotation_object_compute_sum_n(AnnotationObject *object,
					 int              *nums,
					 int               n_nums);

GObject* annotation_object_do_not_use   (AnnotationObject *object);


#endif /* __ANNOTATION_OBJECT_H__ */
