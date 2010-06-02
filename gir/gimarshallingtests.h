/* -*- Mode: C; c-basic-offset: 4 -*-
 * vim: tabstop=4 shiftwidth=4 expandtab
 */

#include <glib-object.h>

#ifndef __G_I_MARSHALLING_TESTS_H__
#define __G_I_MARSHALLING_TESTS_H__

typedef struct _GIMarshallingTestsSimpleStruct GIMarshallingTestsSimpleStruct;

/* Constants */

#define G_I_MARSHALLING_TESTS_CONSTANT_NUMBER 42
#define G_I_MARSHALLING_TESTS_CONSTANT_UTF8   "const \xe2\x99\xa5 utf8"


/* Booleans */

gboolean g_i_marshalling_tests_boolean_return_true (void);
gboolean g_i_marshalling_tests_boolean_return_false (void);

void g_i_marshalling_tests_boolean_in_true (gboolean bool_);
void g_i_marshalling_tests_boolean_in_false (gboolean bool_);

void g_i_marshalling_tests_boolean_out_true (gboolean *bool_);
void g_i_marshalling_tests_boolean_out_false (gboolean *bool_);

void g_i_marshalling_tests_boolean_inout_true_false (gboolean *bool_);
void g_i_marshalling_tests_boolean_inout_false_true (gboolean *bool_);


/* Integers */

gint8 g_i_marshalling_tests_int8_return_max (void);
gint8 g_i_marshalling_tests_int8_return_min (void);

void g_i_marshalling_tests_int8_in_max (gint8 int8);
void g_i_marshalling_tests_int8_in_min (gint8 int8);

void g_i_marshalling_tests_int8_out_max (gint8 *int8);
void g_i_marshalling_tests_int8_out_min (gint8 *int8);

void g_i_marshalling_tests_int8_inout_max_min (gint8 *int8);
void g_i_marshalling_tests_int8_inout_min_max (gint8 *int8);


guint8 g_i_marshalling_tests_uint8_return (void);

void g_i_marshalling_tests_uint8_in (guint8 uint8);

void g_i_marshalling_tests_uint8_out (guint8 *uint8);
void g_i_marshalling_tests_uint8_inout (guint8 *uint8);


gint16 g_i_marshalling_tests_int16_return_max (void);
gint16 g_i_marshalling_tests_int16_return_min (void);

void g_i_marshalling_tests_int16_in_max (gint16 int16);
void g_i_marshalling_tests_int16_in_min (gint16 int16);

void g_i_marshalling_tests_int16_out_max (gint16 *int16);
void g_i_marshalling_tests_int16_out_min (gint16 *int16);

void g_i_marshalling_tests_int16_inout_max_min (gint16 *int16);
void g_i_marshalling_tests_int16_inout_min_max (gint16 *int16);


guint16 g_i_marshalling_tests_uint16_return (void);

void g_i_marshalling_tests_uint16_in (guint16 uint16);

void g_i_marshalling_tests_uint16_out (guint16 *uint16);
void g_i_marshalling_tests_uint16_inout (guint16 *uint16);


gint32 g_i_marshalling_tests_int32_return_max (void);
gint32 g_i_marshalling_tests_int32_return_min (void);

void g_i_marshalling_tests_int32_in_max (gint32 int32);
void g_i_marshalling_tests_int32_in_min (gint32 int32);

void g_i_marshalling_tests_int32_out_max (gint32 *int32);
void g_i_marshalling_tests_int32_out_min (gint32 *int32);

void g_i_marshalling_tests_int32_inout_max_min (gint32 *int32);
void g_i_marshalling_tests_int32_inout_min_max (gint32 *int32);


guint32 g_i_marshalling_tests_uint32_return (void);

void g_i_marshalling_tests_uint32_in (guint32 uint32);

void g_i_marshalling_tests_uint32_out (guint32 *uint32);
void g_i_marshalling_tests_uint32_inout (guint32 *uint32);


gint64 g_i_marshalling_tests_int64_return_max (void);
gint64 g_i_marshalling_tests_int64_return_min (void);

void g_i_marshalling_tests_int64_in_max (gint64 int64);
void g_i_marshalling_tests_int64_in_min (gint64 int64);

void g_i_marshalling_tests_int64_out_max (gint64 *int64);
void g_i_marshalling_tests_int64_out_min (gint64 *int64);

void g_i_marshalling_tests_int64_inout_max_min (gint64 *int64);
void g_i_marshalling_tests_int64_inout_min_max (gint64 *int64);


guint64 g_i_marshalling_tests_uint64_return (void);

void g_i_marshalling_tests_uint64_in (guint64 uint64);

void g_i_marshalling_tests_uint64_out (guint64 *uint64);
void g_i_marshalling_tests_uint64_inout (guint64 *uint64);


gshort g_i_marshalling_tests_short_return_max (void);
gshort g_i_marshalling_tests_short_return_min (void);

void g_i_marshalling_tests_short_in_max (gshort short_);
void g_i_marshalling_tests_short_in_min (gshort short_);

void g_i_marshalling_tests_short_out_max (gshort *short_);
void g_i_marshalling_tests_short_out_min (gshort *short_);

void g_i_marshalling_tests_short_inout_max_min (gshort *short_);
void g_i_marshalling_tests_short_inout_min_max (gshort *short_);


gushort g_i_marshalling_tests_ushort_return (void);

void g_i_marshalling_tests_ushort_in (gushort ushort);

void g_i_marshalling_tests_ushort_out (gushort *ushort);
void g_i_marshalling_tests_ushort_inout (gushort *ushort);


gint g_i_marshalling_tests_int_return_max (void);
gint g_i_marshalling_tests_int_return_min (void);

void g_i_marshalling_tests_int_in_max (gint int_);
void g_i_marshalling_tests_int_in_min (gint int_);

void g_i_marshalling_tests_int_out_max (gint *int_);
void g_i_marshalling_tests_int_out_min (gint *int_);

void g_i_marshalling_tests_int_inout_max_min (gint *int_);
void g_i_marshalling_tests_int_inout_min_max (gint *int_);


guint g_i_marshalling_tests_uint_return (void);

void g_i_marshalling_tests_uint_in (guint uint);

void g_i_marshalling_tests_uint_out (guint *uint);
void g_i_marshalling_tests_uint_inout (guint *uint);


glong g_i_marshalling_tests_long_return_max (void);
glong g_i_marshalling_tests_long_return_min (void);

void g_i_marshalling_tests_long_in_max (glong long_);
void g_i_marshalling_tests_long_in_min (glong long_);

void g_i_marshalling_tests_long_out_max (glong *long_);
void g_i_marshalling_tests_long_out_min (glong *long_);

void g_i_marshalling_tests_long_inout_max_min (glong *long_);
void g_i_marshalling_tests_long_inout_min_max (glong *long_);


gulong g_i_marshalling_tests_ulong_return (void);

void g_i_marshalling_tests_ulong_in (gulong ulong);

void g_i_marshalling_tests_ulong_out (gulong *ulong);
void g_i_marshalling_tests_ulong_inout (gulong *ulong);


gssize g_i_marshalling_tests_ssize_return_max (void);
gssize g_i_marshalling_tests_ssize_return_min (void);

void g_i_marshalling_tests_ssize_in_max (gssize ssize);
void g_i_marshalling_tests_ssize_in_min (gssize ssize);

void g_i_marshalling_tests_ssize_out_max (gssize *ssize);
void g_i_marshalling_tests_ssize_out_min (gssize *ssize);

void g_i_marshalling_tests_ssize_inout_max_min (gssize *ssize);
void g_i_marshalling_tests_ssize_inout_min_max (gssize *ssize);


gsize g_i_marshalling_tests_size_return (void);

void g_i_marshalling_tests_size_in (gsize size);

void g_i_marshalling_tests_size_out (gsize *size);
void g_i_marshalling_tests_size_inout (gsize *size);


/* Floating-point */

gfloat g_i_marshalling_tests_float_return (void);

void g_i_marshalling_tests_float_in (gfloat float_);

void g_i_marshalling_tests_float_out (gfloat *float_);

void g_i_marshalling_tests_float_inout (gfloat *float_);


gdouble g_i_marshalling_tests_double_return (void);

void g_i_marshalling_tests_double_in (gdouble double_);

void g_i_marshalling_tests_double_out (gdouble *double_);

void g_i_marshalling_tests_double_inout (gdouble *double_);


/* Timestamps */

time_t g_i_marshalling_tests_time_t_return (void);

void g_i_marshalling_tests_time_t_in (time_t time_t_);

void g_i_marshalling_tests_time_t_out (time_t *time_t_);

void g_i_marshalling_tests_time_t_inout (time_t *time_t_);


/* GType */

GType g_i_marshalling_tests_gtype_return (void);

void g_i_marshalling_tests_gtype_in (GType gtype);

void g_i_marshalling_tests_gtype_out (GType *gtype);

void g_i_marshalling_tests_gtype_inout (GType *gtype);


/* UTF-8 */

const gchar *g_i_marshalling_tests_utf8_none_return (void);
gchar *g_i_marshalling_tests_utf8_full_return (void);

void g_i_marshalling_tests_utf8_none_in (const gchar *utf8);
void g_i_marshalling_tests_utf8_full_in (gchar *utf8);

void g_i_marshalling_tests_utf8_none_out (gchar **utf8);
void g_i_marshalling_tests_utf8_full_out (gchar **utf8);

void g_i_marshalling_tests_utf8_dangling_out (gchar **utf8);

void g_i_marshalling_tests_utf8_none_inout (gchar **utf8);
void g_i_marshalling_tests_utf8_full_inout (gchar **utf8);

GSList *g_i_marshalling_tests_filename_list_return (void);

/* Arrays */

/* Fixed-size */
const gint *g_i_marshalling_tests_array_fixed_int_return (void);
const gshort *g_i_marshalling_tests_array_fixed_short_return (void);

void g_i_marshalling_tests_array_fixed_int_in (const gint *ints);
void g_i_marshalling_tests_array_fixed_short_in (const gshort *shorts);

void g_i_marshalling_tests_array_fixed_out (gint **ints);

void g_i_marshalling_tests_array_fixed_out_struct (GIMarshallingTestsSimpleStruct **structs);

void g_i_marshalling_tests_array_fixed_inout (gint **ints);

/* Variable-size */

const gint *g_i_marshalling_tests_array_return (gint *length);

void g_i_marshalling_tests_array_in (const gint *ints, gint length);

void g_i_marshalling_tests_array_out (gint **ints, gint *length);

void g_i_marshalling_tests_array_inout (gint **ints, gint *length);

/* Zero-terminated */

gchar **g_i_marshalling_tests_array_zero_terminated_return (void);

void g_i_marshalling_tests_array_zero_terminated_in (gchar **utf8s);

void g_i_marshalling_tests_array_zero_terminated_out (gchar ***utf8s);

void g_i_marshalling_tests_array_zero_terminated_inout (gchar ***utf8s);


/* GArray */

GArray *g_i_marshalling_tests_garray_int_none_return (void);
GArray *g_i_marshalling_tests_garray_utf8_none_return (void);
GArray *g_i_marshalling_tests_garray_utf8_container_return (void);
GArray *g_i_marshalling_tests_garray_utf8_full_return (void);

void g_i_marshalling_tests_garray_int_none_in (GArray *array_);
void g_i_marshalling_tests_garray_utf8_none_in (GArray *array_);
void g_i_marshalling_tests_garray_utf8_container_in (GArray *array_);
void g_i_marshalling_tests_garray_utf8_full_in (GArray *array_);

void g_i_marshalling_tests_garray_utf8_none_out (GArray **array_);
void g_i_marshalling_tests_garray_utf8_container_out (GArray **array_);
void g_i_marshalling_tests_garray_utf8_full_out (GArray **array_);

void g_i_marshalling_tests_garray_utf8_none_inout (GArray **array_);
void g_i_marshalling_tests_garray_utf8_container_inout (GArray **array_);
void g_i_marshalling_tests_garray_utf8_full_inout (GArray **array_);

/* GStrv */

GStrv g_i_marshalling_tests_gstrv_return (void);
void g_i_marshalling_tests_gstrv_in (GStrv g_strv);
void g_i_marshalling_tests_gstrv_out (GStrv *g_strv);
void g_i_marshalling_tests_gstrv_inout (GStrv *g_strv);

/* GList */

GList *g_i_marshalling_tests_glist_int_none_return (void);
GList *g_i_marshalling_tests_glist_utf8_none_return (void);
GList *g_i_marshalling_tests_glist_utf8_container_return (void);
GList *g_i_marshalling_tests_glist_utf8_full_return (void);

void g_i_marshalling_tests_glist_int_none_in (GList *list);
void g_i_marshalling_tests_glist_utf8_none_in (GList *list);
void g_i_marshalling_tests_glist_utf8_container_in (GList *list);
void g_i_marshalling_tests_glist_utf8_full_in (GList *list);

void g_i_marshalling_tests_glist_utf8_none_out (GList **list);
void g_i_marshalling_tests_glist_utf8_container_out (GList **list);
void g_i_marshalling_tests_glist_utf8_full_out (GList **list);

void g_i_marshalling_tests_glist_utf8_none_inout (GList **list);
void g_i_marshalling_tests_glist_utf8_container_inout (GList **list);
void g_i_marshalling_tests_glist_utf8_full_inout (GList **list);


/* GSList */

GSList *g_i_marshalling_tests_gslist_int_none_return (void);
GSList *g_i_marshalling_tests_gslist_utf8_none_return (void);
GSList *g_i_marshalling_tests_gslist_utf8_container_return (void);
GSList *g_i_marshalling_tests_gslist_utf8_full_return (void);

void g_i_marshalling_tests_gslist_int_none_in (GSList *list);
void g_i_marshalling_tests_gslist_utf8_none_in (GSList *list);
void g_i_marshalling_tests_gslist_utf8_container_in (GSList *list);
void g_i_marshalling_tests_gslist_utf8_full_in (GSList *list);

void g_i_marshalling_tests_gslist_utf8_none_out (GSList **list);
void g_i_marshalling_tests_gslist_utf8_container_out (GSList **list);
void g_i_marshalling_tests_gslist_utf8_full_out (GSList **list);

void g_i_marshalling_tests_gslist_utf8_none_inout (GSList **list);
void g_i_marshalling_tests_gslist_utf8_container_inout (GSList **list);
void g_i_marshalling_tests_gslist_utf8_full_inout (GSList **list);


/* GHashTable */

GHashTable *g_i_marshalling_tests_ghashtable_int_none_return (void);
GHashTable *g_i_marshalling_tests_ghashtable_utf8_none_return (void);
GHashTable *g_i_marshalling_tests_ghashtable_utf8_container_return (void);
GHashTable *g_i_marshalling_tests_ghashtable_utf8_full_return (void);

void g_i_marshalling_tests_ghashtable_int_none_in (GHashTable *hash_table);
void g_i_marshalling_tests_ghashtable_utf8_none_in (GHashTable *hash_table);
void g_i_marshalling_tests_ghashtable_utf8_container_in (GHashTable *hash_table);
void g_i_marshalling_tests_ghashtable_utf8_full_in (GHashTable *hash_table);

void g_i_marshalling_tests_ghashtable_utf8_none_out (GHashTable **hash_table);
void g_i_marshalling_tests_ghashtable_utf8_container_out (GHashTable **hash_table);
void g_i_marshalling_tests_ghashtable_utf8_full_out (GHashTable **hash_table);

void g_i_marshalling_tests_ghashtable_utf8_none_inout (GHashTable **hash_table);
void g_i_marshalling_tests_ghashtable_utf8_container_inout (GHashTable **hash_table);
void g_i_marshalling_tests_ghashtable_utf8_full_inout (GHashTable **hash_table);


/* GValue */

GValue *g_i_marshalling_tests_gvalue_return (void);

void g_i_marshalling_tests_gvalue_in (GValue *value);

void g_i_marshalling_tests_gvalue_out (GValue **value);

void g_i_marshalling_tests_gvalue_inout (GValue **value);


/* GClosure */

void g_i_marshalling_tests_gclosure_in (GClosure *closure);


/* Pointer */

gpointer g_i_marshalling_tests_pointer_in_return (gpointer pointer);


/* Enum */

typedef enum
{
  G_I_MARSHALLING_TESTS_ENUM_VALUE1,
  G_I_MARSHALLING_TESTS_ENUM_VALUE2,
  G_I_MARSHALLING_TESTS_ENUM_VALUE3 = 42
} GIMarshallingTestsEnum;

GIMarshallingTestsEnum g_i_marshalling_tests_enum_return (void);

void g_i_marshalling_tests_enum_in (GIMarshallingTestsEnum enum_);

void g_i_marshalling_tests_enum_out (GIMarshallingTestsEnum *enum_);

void g_i_marshalling_tests_enum_inout (GIMarshallingTestsEnum *enum_);


/* GEnum */

typedef enum
{
  G_I_MARSHALLING_TESTS_GENUM_VALUE1,
  G_I_MARSHALLING_TESTS_GENUM_VALUE2,
  G_I_MARSHALLING_TESTS_GENUM_VALUE3 = 42
} GIMarshallingTestsGEnum;

GType g_i_marshalling_tests_genum_get_type (void) G_GNUC_CONST;
#define G_I_MARSHALLING_TESTS_TYPE_GENUM (g_i_marshalling_tests_genum_get_type ())

GIMarshallingTestsEnum g_i_marshalling_tests_genum_return (void);

void g_i_marshalling_tests_genum_in (GIMarshallingTestsGEnum enum_);

void g_i_marshalling_tests_genum_out (GIMarshallingTestsGEnum *enum_);

void g_i_marshalling_tests_genum_inout (GIMarshallingTestsGEnum *enum_);


/* GFlags */

typedef enum
{
  G_I_MARSHALLING_TESTS_FLAGS_VALUE1 = 1 << 0,
  G_I_MARSHALLING_TESTS_FLAGS_VALUE2 = 1 << 1,
  G_I_MARSHALLING_TESTS_FLAGS_VALUE3 = 1 << 2
} GIMarshallingTestsFlags;

GType g_i_marshalling_tests_flags_get_type (void) G_GNUC_CONST;
#define G_I_MARSHALLING_TESTS_TYPE_FLAGS (g_i_marshalling_tests_flags_get_type ())

GIMarshallingTestsFlags g_i_marshalling_tests_flags_return (void);

void g_i_marshalling_tests_flags_in (GIMarshallingTestsFlags flags_);
void g_i_marshalling_tests_flags_in_zero (GIMarshallingTestsFlags flags);

void g_i_marshalling_tests_flags_out (GIMarshallingTestsFlags *flags_);

void g_i_marshalling_tests_flags_inout (GIMarshallingTestsFlags *flags_);


/* Structure */

struct _GIMarshallingTestsSimpleStruct {
    glong long_;
    gint8 int8;
};

typedef struct {
    GIMarshallingTestsSimpleStruct simple_struct;
} GIMarshallingTestsNestedStruct;

typedef struct {
    GIMarshallingTestsNestedStruct *pointer;
} GIMarshallingTestsNotSimpleStruct;


GIMarshallingTestsSimpleStruct *g_i_marshalling_tests__simple_struct_return (void);

void g_i_marshalling_tests__simple_struct_in (GIMarshallingTestsSimpleStruct *struct_);

void g_i_marshalling_tests__simple_struct_out (GIMarshallingTestsSimpleStruct **struct_);

void g_i_marshalling_tests__simple_struct_inout (GIMarshallingTestsSimpleStruct **struct_);

void g_i_marshalling_tests_simple_struct_method (GIMarshallingTestsSimpleStruct *struct_);


typedef struct {
    glong long_;
} GIMarshallingTestsPointerStruct;

GType g_i_marshalling_tests_pointer_struct_get_type (void) G_GNUC_CONST;

GIMarshallingTestsPointerStruct *g_i_marshalling_tests__pointer_struct_return (void);

void g_i_marshalling_tests__pointer_struct_in (GIMarshallingTestsPointerStruct *struct_);

void g_i_marshalling_tests__pointer_struct_out (GIMarshallingTestsPointerStruct **struct_);

void g_i_marshalling_tests__pointer_struct_inout (GIMarshallingTestsPointerStruct **struct_);


typedef struct {
    glong long_;
    GStrv g_strv;
} GIMarshallingTestsBoxedStruct;

GType g_i_marshalling_tests_boxed_struct_get_type (void) G_GNUC_CONST;

GIMarshallingTestsBoxedStruct *g_i_marshalling_tests_boxed_struct_new (void);

GIMarshallingTestsBoxedStruct *g_i_marshalling_tests__boxed_struct_return (void);

void g_i_marshalling_tests__boxed_struct_in (GIMarshallingTestsBoxedStruct *struct_);

void g_i_marshalling_tests__boxed_struct_out (GIMarshallingTestsBoxedStruct **struct_);

void g_i_marshalling_tests__boxed_struct_inout (GIMarshallingTestsBoxedStruct **struct_);

typedef union {
    glong long_;
} GIMarshallingTestsUnion;

GType g_i_marshalling_tests_union_get_type (void) G_GNUC_CONST;

GIMarshallingTestsUnion *g_i_marshalling_tests__union_return (void);

void g_i_marshalling_tests__union_in (GIMarshallingTestsUnion *union_);

void g_i_marshalling_tests__union_out (GIMarshallingTestsUnion **union_);

void g_i_marshalling_tests__union_inout (GIMarshallingTestsUnion **union_);

void g_i_marshalling_tests_union_method (GIMarshallingTestsUnion *union_);

/* Object */

#define G_I_MARSHALLING_TESTS_TYPE_OBJECT             (g_i_marshalling_tests_object_get_type ())
#define G_I_MARSHALLING_TESTS_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_I_MARSHALLING_TESTS_TYPE_OBJECT, GIMarshallingTestsObject))
#define G_I_MARSHALLING_TESTS_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), G_I_MARSHALLING_TESTS_TYPE_OBJECT, GIMarshallingTestsObjectClass))
#define G_I_MARSHALLING_TESTS_IS_OBJECT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_I_MARSHALLING_TESTS_TYPE_OBJECT))
#define G_I_MARSHALLING_TESTS_IS_OBJECT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), G_I_MARSHALLING_TESTS_TYPE_OBJECT))
#define G_I_MARSHALLING_TESTS_OBJECT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), G_I_MARSHALLING_TESTS_TYPE_OBJECT, GIMarshallingTestsObjectClass))

typedef struct _GIMarshallingTestsObjectClass GIMarshallingTestsObjectClass;
typedef struct _GIMarshallingTestsObject GIMarshallingTestsObject;

struct _GIMarshallingTestsObjectClass
{
	GObjectClass parent_class;

    /**
     * GIMarshallingTestsObjectClass::method_int8_in:
     * @in: (in):
     */
    void (* method_int8_in) (GIMarshallingTestsObject *self, gint8 in);

    /**
     * GIMarshallingTestsObjectClass::method_int8_out:
     * @out: (out):
     */
    void (* method_int8_out) (GIMarshallingTestsObject *self, gint8 *out);

    /**
     * GIMarshallingTestsObjectClass::method_with_default_implementation:
     * @in: (in):
     */
    void (* method_with_default_implementation) (GIMarshallingTestsObject *self, gint8 in);
};

struct _GIMarshallingTestsObject
{
	GObject parent_instance;

    gint int_;
};

GType g_i_marshalling_tests_object_get_type (void) G_GNUC_CONST;
void g_i_marshalling_tests_object_static_method (void);
void g_i_marshalling_tests_object_method (GIMarshallingTestsObject *object);
void g_i_marshalling_tests_object_overridden_method (GIMarshallingTestsObject *object);
GIMarshallingTestsObject *g_i_marshalling_tests_object_new (gint int_);

void g_i_marshalling_tests_object_method_array_in (GIMarshallingTestsObject *object, const gint *ints, gint length);
void g_i_marshalling_tests_object_method_array_out (GIMarshallingTestsObject *object, gint **ints, gint *length);
void g_i_marshalling_tests_object_method_array_inout (GIMarshallingTestsObject *object, gint **ints, gint *length);
const gint *g_i_marshalling_tests_object_method_array_return (GIMarshallingTestsObject *object, gint *length);

void g_i_marshalling_tests_object_method_int8_in (GIMarshallingTestsObject *object, gint8 in);
void g_i_marshalling_tests_object_method_int8_out (GIMarshallingTestsObject *object, gint8 *out);
void g_i_marshalling_tests_object_method_with_default_implementation (GIMarshallingTestsObject *object, gint8 in);


GIMarshallingTestsObject *g_i_marshalling_tests__object_none_return (void);
GIMarshallingTestsObject *g_i_marshalling_tests__object_full_return (void);

void g_i_marshalling_tests__object_none_in (GIMarshallingTestsObject *object);
void g_i_marshalling_tests__object_full_in (GIMarshallingTestsObject *object);

void g_i_marshalling_tests__object_none_out (GIMarshallingTestsObject **object);
void g_i_marshalling_tests__object_full_out (GIMarshallingTestsObject **object);

void g_i_marshalling_tests__object_none_inout (GIMarshallingTestsObject **object);
void g_i_marshalling_tests__object_full_inout (GIMarshallingTestsObject **object);
void g_i_marshalling_tests__object_inout_same (GIMarshallingTestsObject **object);

void g_i_marshalling_tests__object_int8_in (GIMarshallingTestsObject *object, gint8 in);
void g_i_marshalling_tests__object_int8_out (GIMarshallingTestsObject *object, gint8 *out);

#define G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT             (g_i_marshalling_tests_sub_object_get_type ())
#define G_I_MARSHALLING_TESTS_SUB_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT, GIMarshallingTestsSubObject))
#define G_I_MARSHALLING_TESTS_SUB_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT, GIMarshallingTestsSubObjectClass))
#define G_I_MARSHALLING_TESTS_IS_SUB_OBJECT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT))
#define G_I_MARSHALLING_TESTS_IS_SUB_OBJECT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT))
#define G_I_MARSHALLING_TESTS_SUB_OBJECT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), G_I_MARSHALLING_TESTS_TYPE_SUB_OBJECT, GIMarshallingTestsSubObjectClass))

typedef struct _GIMarshallingTestsSubObjectClass GIMarshallingTestsSubObjectClass;
typedef struct _GIMarshallingTestsSubObject GIMarshallingTestsSubObject;

struct _GIMarshallingTestsSubObjectClass
{
	GIMarshallingTestsObjectClass parent_class;
};

struct _GIMarshallingTestsSubObject
{
	GIMarshallingTestsObject parent_instance;
};

GType g_i_marshalling_tests_sub_object_get_type (void) G_GNUC_CONST;

void g_i_marshalling_tests_sub_object_sub_method (GIMarshallingTestsSubObject *object);
void g_i_marshalling_tests_sub_object_overwritten_method (GIMarshallingTestsSubObject *object);

/* Interfaces */

#define G_I_MARSHALLING_TESTS_TYPE_INTERFACE              (g_i_marshalling_tests_interface_get_type ())
#define G_I_MARSHALLING_TESTS_INTERFACE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), G_I_MARSHALLING_TESTS_TYPE_INTERFACE, GIMarshallingTestsInterface))
#define G_I_MARSHALLING_TESTS_IS_INTERFACE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), G_I_MARSHALLING_TESTS_TYPE_INTERFACE))
#define G_I_MARSHALLING_TESTS_INTERFACE_GET_IFACE(obj)    (G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_I_MARSHALLING_TESTS_TYPE_INTERFACE, GIMarshallingTestsInterfaceIface))

typedef struct _GIMarshallingTestsInterface GIMarshallingTestsInterface;
typedef struct _GIMarshallingTestsInterfaceIface GIMarshallingTestsInterfaceIface;

struct _GIMarshallingTestsInterfaceIface {
    GTypeInterface base_iface;

    /**
     * GIMarshallingTestsInterfaceIface::test_int8_in:
     * @in: (in):
     */
    void (* test_int8_in) (GIMarshallingTestsInterface *self, gint8 in);
};

GType g_i_marshalling_tests_interface_get_type (void) G_GNUC_CONST;

void g_i_marshalling_tests_interface_test_int8_in (GIMarshallingTestsInterface *self, gint8 in);

void g_i_marshalling_tests_test_interface_test_int8_in (GIMarshallingTestsInterface *test_iface, gint8 in);


/* Multiple output arguments */

void g_i_marshalling_tests_int_out_out (gint *int0, gint *int1);
void g_i_marshalling_tests_int_out_in (gint *int0, gint int1);
gint g_i_marshalling_tests_int_return_out (gint *int_);
void g_i_marshalling_tests_utf8_full_out_out (gchar **utf80, gchar **utf82);


/* Overrides */

#define G_I_MARSHALLING_TESTS_OVERRIDES_CONSTANT 42


typedef struct {
    glong long_;
} GIMarshallingTestsOverridesStruct;

GType g_i_marshalling_tests_overrides_struct_get_type (void) G_GNUC_CONST;

GIMarshallingTestsOverridesStruct *g_i_marshalling_tests_overrides_struct_new (void);

glong g_i_marshalling_tests_overrides_struct_method (GIMarshallingTestsOverridesStruct *struct_);

GIMarshallingTestsOverridesStruct *g_i_marshalling_tests__overrides_struct_return (void);


#define G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT             (g_i_marshalling_tests_overrides_object_get_type ())
#define G_I_MARSHALLING_TESTS_OVERRIDES_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT, GIMarshallingTestsOverridesObject))
#define G_I_MARSHALLING_TESTS_OVERRIDES_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT, GIMarshallingTestsOverridesObjectClass))
#define G_I_MARSHALLING_TESTS_IS_OVERRIDES_OBJECT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT))
#define G_I_MARSHALLING_TESTS_IS_OVERRIDES_OBJECT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT))
#define G_I_MARSHALLING_TESTS_OVERRIDES_OBJECT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT, GIMarshallingTestsOverridesObjectClass))

typedef struct _GIMarshallingTestsOverridesObjectClass GIMarshallingTestsOverridesObjectClass;
typedef struct _GIMarshallingTestsOverridesObject GIMarshallingTestsOverridesObject;

struct _GIMarshallingTestsOverridesObjectClass
{
	GObjectClass parent_class;
};

struct _GIMarshallingTestsOverridesObject
{
	GObject parent_instance;

    glong long_;
};

GType g_i_marshalling_tests_overrides_object_get_type (void) G_GNUC_CONST;

GIMarshallingTestsOverridesObject *g_i_marshalling_tests_overrides_object_new (void);

glong g_i_marshalling_tests_overrides_object_method (GIMarshallingTestsOverridesObject *object);


GIMarshallingTestsOverridesObject *g_i_marshalling_tests__overrides_object_return (void);

#endif /* __G_I_MARSHALLING_TESTS_H__ */
