#ifndef __REGRESS_ANNOTATION_OBJECT_H__
#define __REGRESS_ANNOTATION_OBJECT_H__

#include <glib-object.h>

typedef enum /*< flags,prefix=ANN >*/
{
  ANN_FLAG_FOO = 1,
  ANN_FLAG_BAR = 2
} RegressAnnotationBitfield;

/**
 * RegressAnnotationCallback:
 * @in: (in) (transfer none): array of ints
 *
 * This is a callback.
 * Return value: (transfer none): array of ints
 */
typedef const gint* (*RegressAnnotationCallback) (const gint *in);

/**
 * RegressAnnotationListCallback:
 * @in: (in) (transfer none) (element-type utf8): list of strings
 *
 * This is a callback taking a list.
 * Return value: (transfer container) (element-type utf8): list of strings
 */
typedef GList* (*RegressAnnotationListCallback) (GList *in);

/**
 * RegressAnnotationNotifyFunc:
 * @data: (closure): The user data
 *
 * This is a callback with a 'closure' argument that is not named
 * 'user_data' and hence has to be annotated.
 */
typedef void (*RegressAnnotationNotifyFunc) (gpointer data);

/**
 * RegressAnnotationObject:
 *
 * This is an object used to test annotations.
 *
 * Attributes: (org.example.Test cows)
 */
typedef struct _RegressAnnotationObject          RegressAnnotationObject;
typedef struct _RegressAnnotationObjectClass     RegressAnnotationObjectClass;

typedef void (*RegressAnnotationForeachFunc) (RegressAnnotationObject *object,
                                       const char *item,
                                       gpointer user_data);

struct _RegressAnnotationObject
{
  GObject parent_instance;
};

struct _RegressAnnotationObjectClass
{
  GObjectClass parent_class;
};

GType    regress_annotation_object_get_type (void);

gint     regress_annotation_object_method       (RegressAnnotationObject *object);
gint     regress_annotation_object_out          (RegressAnnotationObject *object,
					 int              *outarg);
GObject* regress_annotation_object_create_object(RegressAnnotationObject *object);
GObject* regress_annotation_object_allow_none   (RegressAnnotationObject *object,
					 const gchar      *somearg);
GObject* regress_annotation_object_notrans      (RegressAnnotationObject *object);
gint     regress_annotation_object_inout        (RegressAnnotationObject *object,
					 int              *inoutarg);
gint     regress_annotation_object_inout2       (RegressAnnotationObject *object,
					 int              *inoutarg);
gint     regress_annotation_object_inout3       (RegressAnnotationObject *object,
					 int              *inoutarg);
gint     regress_annotation_object_in           (RegressAnnotationObject *object,
					 int              *inarg);
gint     regress_annotation_object_calleeowns   (RegressAnnotationObject *object,
					 GObject          **toown);
gint     regress_annotation_object_calleesowns  (RegressAnnotationObject *object,
					 GObject          **toown1,
					 GObject          **toown2);
GList*   regress_annotation_object_get_strings  (RegressAnnotationObject *object);
GHashTable*regress_annotation_object_get_hash   (RegressAnnotationObject *object);
void     regress_annotation_object_with_voidp   (RegressAnnotationObject *object,
					 void             *data);
GSList*  regress_annotation_object_get_objects  (RegressAnnotationObject *object);

void     regress_annotation_object_use_buffer   (RegressAnnotationObject *object,
					 guchar           *bytes);

void     regress_annotation_object_compute_sum  (RegressAnnotationObject *object,
					 int              *nums);

void     regress_annotation_object_compute_sum_n(RegressAnnotationObject *object,
					 int              *nums,
					 int               n_nums);
void     regress_annotation_object_compute_sum_nz(RegressAnnotationObject *object,
                                          int             *nums,
                                          int              n_nums);
void     regress_annotation_object_parse_args   (RegressAnnotationObject *object,
                                         int              *argc,
                                         char           ***argv);
gboolean regress_annotation_object_string_out   (RegressAnnotationObject *object,
                                         char            **str_out);
void     regress_annotation_object_foreach      (RegressAnnotationObject *object,
                                         RegressAnnotationForeachFunc func,
                                         gpointer user_data);

void     regress_annotation_object_set_data     (RegressAnnotationObject *object,
                                         const guchar     *data,
                                         gsize             length);
void     regress_annotation_object_set_data2    (RegressAnnotationObject *object,
                                         const gchar      *data,
                                         gsize             length);
void     regress_annotation_object_set_data3    (RegressAnnotationObject *object,
                                         gpointer          data,
                                         gsize             length);

GObject* regress_annotation_object_do_not_use   (RegressAnnotationObject *object);
void     regress_annotation_object_watch        (RegressAnnotationObject *object,
                                         RegressAnnotationForeachFunc func,
                                         gpointer user_data);
void     regress_annotation_object_watch_full   (RegressAnnotationObject *object,
                                         RegressAnnotationForeachFunc func,
                                         gpointer user_data,
                                         GDestroyNotify destroy);
void     regress_annotation_object_hidden_self  (gpointer object);

void     regress_annotation_init                (int              *argc, 
					 char           ***argv);
char **  regress_annotation_return_array        (int             *length);
void     regress_annotation_versioned           (void);
char **  regress_annotation_string_zero_terminated (void);
void     regress_annotation_string_zero_terminated_out (char ***out);

void     regress_annotation_string_array_length (guint n_properties, const gchar * const properties[]);

void     regress_annotation_object_extra_annos (RegressAnnotationObject *object);

void     regress_annotation_custom_destroy (RegressAnnotationCallback callback,
                                    RegressAnnotationNotifyFunc destroy,
                                    gpointer data);
char *   regress_annotation_get_source_file (void);
void     regress_annotation_set_source_file (const char *fname);

gint     regress_annotation_attribute_func (RegressAnnotationObject *object,
                                    const gchar      *data);

void     regress_annotation_invalid_regress_annotation (int foo);

/**
 * RegressAnnotationStruct:
 *
 * This is a test of an array of object in an field of a struct.
 */
struct RegressAnnotationStruct
{
  RegressAnnotationObject *objects[10];
};

void    regress_annotation_ptr_array (GPtrArray *array);

GObject  * regress_annotation_test_parsing_bug630862 (void);

void regress_annotation_space_after_comment_bug631690 (void);

gchar* regress_annotation_return_filename (void);

GObject * regress_annotation_transfer_floating(void);

/* This one we can handle properly */
#define REGRESS_ANNOTATION_CALCULATED_DEFINE (10 * 10)

/**
 * REGRESS_ANNOTATION_CALCULATED_LARGE:
 *
 * Constant to define a calculated large value
 *
 * Value: 10000000000UL
 *
 * Since: 1.4
 */
#define REGRESS_ANNOTATION_CALCULATED_LARGE (1000 * G_GINT64_CONSTANT (10000000))

/**
 * REGRESS_ANNOTATION_CALCULATED_LARGE_DIV:
 *
 * Constant to define a calculated large value
 *
 * Value: 1000000UL
 */
#define REGRESS_ANNOTATION_CALCULATED_LARGE_DIV (1000 / G_GINT64_CONSTANT (10000000))

#endif /* __REGRESS_ANNOTATION_OBJECT_H__ */

