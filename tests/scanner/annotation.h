#ifndef __ANNOTATION_OBJECT_H__
#define __ANNOTATION_OBJECT_H__

#include <glib-object.h>

typedef enum /*< flags,prefix=ANN >*/
{
  ANN_FLAG_FOO = 1,
  ANN_FLAG_BAR = 2
} AnnotationBitfield;

/**
 * AnnotationCallback:
 * @in: (in) (transfer none): array of ints
 *
 * This is a callback.
 * Return value: (transfer none): array of ints
 */
typedef const gint* (*AnnotationCallback) (const gint *in);

/**
 * AnnotationListCallback:
 * @in: (in) (transfer none) (element-type utf8): list of strings
 *
 * This is a callback taking a list.
 * Return value: (transfer container) (element-type utf8): list of strings
 */
typedef GList* (*AnnotationListCallback) (GList *in);

/**
 * AnnotationNotifyFunc:
 * @data: (closure): The user data
 *
 * This is a callback with a 'closure' argument that is not named
 * 'user_data' and hence has to be annotated.
 */
typedef void (*AnnotationNotifyFunc) (gpointer data);

/**
 * AnnotationObject:
 *
 * This is an object used to test annotations.
 *
 * Attributes: (org.example.Test cows)
 */
typedef struct _AnnotationObject          AnnotationObject;
typedef struct _AnnotationObjectClass     AnnotationObjectClass;

typedef void (*AnnotationForeachFunc) (AnnotationObject *object,
                                       const char *item,
                                       gpointer user_data);

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
void     annotation_object_with_voidp   (AnnotationObject *object,
					 void             *data);
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
gboolean annotation_object_string_out   (AnnotationObject *object,
                                         char            **str_out);
void     annotation_object_foreach      (AnnotationObject *object,
                                         AnnotationForeachFunc func,
                                         gpointer user_data);

void     annotation_object_set_data     (AnnotationObject *object,
                                         const guchar     *data,
                                         gsize             length);
void     annotation_object_set_data2    (AnnotationObject *object,
                                         const gchar      *data,
                                         gsize             length);
void     annotation_object_set_data3    (AnnotationObject *object,
                                         gpointer          data,
                                         gsize             length);

GObject* annotation_object_do_not_use   (AnnotationObject *object);
void     annotation_object_watch        (AnnotationObject *object,
                                         AnnotationForeachFunc func,
                                         gpointer user_data);
void     annotation_object_watch_full   (AnnotationObject *object,
                                         AnnotationForeachFunc func,
                                         gpointer user_data,
                                         GDestroyNotify destroy);
void     annotation_object_hidden_self  (gpointer object);

void     annotation_init                (int              *argc, 
					 char           ***argv);
char **  annotation_return_array        (int             *length);
void     annotation_versioned           (void);
char **  annotation_string_zero_terminated (void);
void     annotation_string_zero_terminated_out (char ***out);

void     annotation_string_array_length (guint n_properties, const gchar * const properties[]);

void     annotation_object_extra_annos (AnnotationObject *object);

void     annotation_custom_destroy (AnnotationCallback callback,
                                    AnnotationNotifyFunc destroy,
                                    gpointer data);
char *   annotation_get_source_file (void);
void     annotation_set_source_file (const char *fname);

gint     annotation_attribute_func (AnnotationObject *object,
                                    const gchar      *data);

void     annotation_invalid_annotation (int foo);

/**
 * AnnotationStruct:
 *
 * This is a test of an array of object in an field of a struct.
 */
struct AnnotationStruct
{
  AnnotationObject *objects[10];
};

void    annotation_ptr_array (GPtrArray *array);

GObject  * annotation_test_parsing_bug630862 (void);

void annotation_space_after_comment_bug631690 (void);

gchar* annotation_return_filename (void);

GObject * annotation_transfer_floating(void);

/* This one we can handle properly */
#define ANNOTATION_CALCULATED_DEFINE (10 * 10)

/**
 * ANNOTATION_CALCULATED_LARGE:
 *
 * Constant to define a calculated large value
 *
 * Value: 10000000000UL
 *
 * Since: 1.4
 */
#define ANNOTATION_CALCULATED_LARGE (1000 * G_GINT64_CONSTANT (10000000))

/**
 * ANNOTATION_CALCULATED_LARGE_DIV:
 *
 * Constant to define a calculated large value
 *
 * Value: 1000000UL
 */
#define ANNOTATION_CALCULATED_LARGE_DIV (1000 / G_GINT64_CONSTANT (10000000))

#endif /* __ANNOTATION_OBJECT_H__ */

