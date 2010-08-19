#ifndef __GITESTTYPES_H__
#define __GITESTTYPES_H__

#include <cairo/cairo.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <time.h>

void regress_set_abort_on_error (gboolean abort_on_error);

/* basic types */
gboolean regress_test_boolean (gboolean in);
gboolean regress_test_boolean_true (gboolean in);
gboolean regress_test_boolean_false (gboolean in);
gint8 regress_test_int8 (gint8 in);
guint8 regress_test_uint8 (guint8 in);
gint16 regress_test_int16 (gint16 in);
guint16 regress_test_uint16 (guint16 in);
gint32 regress_test_int32 (gint32 in);
guint32 regress_test_uint32 (guint32 in);
gint64 regress_test_int64 (gint64 in);
guint64 regress_test_uint64 (guint64 in);
gshort regress_test_short (gshort in);
gushort regress_test_ushort (gushort in);
gint regress_test_int (gint in);
guint regress_test_uint (guint in);
glong regress_test_long (glong in);
gulong regress_test_ulong (gulong in);
gssize regress_test_ssize (gssize in);
gsize regress_test_size (gsize in);
gfloat regress_test_float (gfloat in);
gdouble regress_test_double (gdouble in);
time_t regress_test_timet (time_t in);
GType regress_test_gtype (GType in);

/* utf8 */
G_CONST_RETURN char *regress_test_utf8_const_return (void);
char *regress_test_utf8_nonconst_return (void);
void regress_test_utf8_nonconst_in (char *in);
void regress_test_utf8_const_in (const char *in);
void regress_test_utf8_out (char **out);
void regress_test_utf8_inout (char **inout);
GSList *regress_test_filename_return (void);
void regress_test_utf8_null_in (char *in);
void regress_test_utf8_null_out (char **char_out);

/* in arguments after out arguments */
void regress_test_int_out_utf8 (int *length, const char *in);

/* multiple output arguments */
void regress_test_multi_double_args (gdouble in, gdouble *one, gdouble *two);
void regress_test_utf8_out_out (char **out0, char **out1);
char *regress_test_utf8_out_nonconst_return (char **out);

/* non-basic-types */
/* array */
gboolean regress_test_strv_in (char **arr);
int regress_test_array_int_in (int n_ints, int *ints);
void regress_test_array_int_out (int *n_ints, int **ints);
void regress_test_array_int_inout (int *n_ints, int **ints);
int regress_test_array_gint8_in (int n_ints, gint8 *ints);
int regress_test_array_gint16_in (int n_ints, gint16 *ints);
gint32 regress_test_array_gint32_in (int n_ints, gint32 *ints);
gint64 regress_test_array_gint64_in (int n_ints, gint64 *ints);
char *regress_test_array_gtype_in (int n_types, GType *types);
char **regress_test_strv_out_container (void);
char **regress_test_strv_out (void);
const char * const * regress_test_strv_out_c (void);
void   regress_test_strv_outarg (char ***retp);
int regress_test_array_fixed_size_int_in (int *ints);
void regress_test_array_fixed_size_int_out (int **ints);
int *regress_test_array_fixed_size_int_return (void);

/* transfer tests */
int regress_test_array_int_in_take (int n_ints, int *ints);
gboolean regress_test_strv_in_container (char **arr);

int *regress_test_array_int_full_out(int *len);
int *regress_test_array_int_none_out(int *len);
void regress_test_array_int_null_in (int *arr, int len);
void regress_test_array_int_null_out (int **arr, int *len);

/* interface */
/* GList */
G_CONST_RETURN GList *regress_test_glist_nothing_return (void);
GList *regress_test_glist_nothing_return2 (void);
GList *regress_test_glist_container_return (void);
GList *regress_test_glist_everything_return (void);
void regress_test_glist_nothing_in (const GList *in);
void regress_test_glist_nothing_in2 (GList *in);
void regress_test_glist_container_in (GList *in);
void regress_test_glist_everything_in (GList *in);
void regress_test_glist_null_in(GSList *in);
void regress_test_glist_null_out(GSList **out_list);
void regress_test_glist_free (GList *in);

/* GSList */
G_CONST_RETURN GSList *regress_test_gslist_nothing_return (void);
GSList *regress_test_gslist_nothing_return2 (void);
GSList *regress_test_gslist_container_return (void);
GSList *regress_test_gslist_everything_return (void);
void regress_test_gslist_nothing_in (const GSList *in);
void regress_test_gslist_nothing_in2 (GSList *in);
void regress_test_gslist_container_in (GSList *in);
void regress_test_gslist_everything_in (GSList *in);
void regress_test_gslist_null_in(GSList *in);
void regress_test_gslist_null_out(GSList **out_list);
void regress_test_gslist_free (GSList *in);

/* GHashTable */
G_CONST_RETURN GHashTable *regress_test_ghash_null_return (void);
G_CONST_RETURN GHashTable *regress_test_ghash_nothing_return (void);
GHashTable *regress_test_ghash_nothing_return2 (void);
GHashTable *regress_test_ghash_container_return (void);
GHashTable *regress_test_ghash_everything_return (void);
void regress_test_ghash_null_in (const GHashTable *in);
void regress_test_ghash_null_out (const GHashTable **out);
void regress_test_ghash_nothing_in (const GHashTable *in);
void regress_test_ghash_nothing_in2 (GHashTable *in);
void regress_test_ghash_container_in (GHashTable *in);
void regress_test_ghash_everything_in (GHashTable *in);
void regress_test_ghash_free (GHashTable *in);
GHashTable *regress_test_ghash_nested_everything_return (void);
GHashTable *regress_test_ghash_nested_everything_return2 (void);

/* error? */

/* closure */
int regress_test_closure (GClosure *closure);
int regress_test_closure_one_arg (GClosure *closure, int arg);

/* value */
int regress_test_int_value_arg(const GValue *v);
const GValue *regress_test_value_return(int i);

/* foreign structs */
cairo_t *regress_test_cairo_context_full_return (void);
void regress_test_cairo_context_none_in (cairo_t *context);

cairo_surface_t *regress_test_cairo_surface_none_return (void);
cairo_surface_t *regress_test_cairo_surface_full_return (void);
void regress_test_cairo_surface_none_in (cairo_surface_t *surface);
void regress_test_cairo_surface_full_out (cairo_surface_t **surface);


/* enums / flags */

typedef enum
{
  REGRESS_TEST_VALUE1,
  REGRESS_TEST_VALUE2,
  REGRESS_TEST_VALUE3 = 42
} RegressTestEnum;

typedef enum
{
  REGRESS_TEST_FLAG1 = 1 << 0,
  REGRESS_TEST_FLAG2 = 1 << 1,
  REGRESS_TEST_FLAG3 = 1 << 2,
} RegressTestFlags;

GType regress_test_enum_get_type (void) G_GNUC_CONST;
#define REGRESS_TEST_TYPE_ENUM (regress_test_enum_get_type ())
GType regress_test_flags_get_type (void) G_GNUC_CONST;
#define REGRESS_TEST_TYPE_FLAGS (regress_test_flags_get_type ())

const gchar * regress_test_enum_param(RegressTestEnum e);

/* structures */
typedef struct _RegressTestStructA RegressTestStructA;
typedef struct _RegressTestStructB RegressTestStructB;

struct _RegressTestStructA
{
  gint some_int;
  gint8 some_int8;
  gdouble some_double;
  RegressTestEnum some_enum;
};

void regress_test_struct_a_clone (RegressTestStructA *a,
				  RegressTestStructA *a_out);

struct _RegressTestStructB
{
  gint8 some_int8;
  RegressTestStructA nested_a;
};

void regress_test_struct_b_clone (RegressTestStructB *b,
			  RegressTestStructB *b_out);

/* This one has a non-basic member */
struct _RegressTestStructC
{
  gint another_int;
  GObject *obj;
};

/* plain-old-data boxed types */
typedef struct _RegressTestSimpleBoxedA RegressTestSimpleBoxedA;
typedef struct _RegressTestSimpleBoxedB RegressTestSimpleBoxedB;

struct _RegressTestSimpleBoxedA
{
  gint some_int;
  gint8 some_int8;
  gdouble some_double;
  RegressTestEnum some_enum;
};

GType                   regress_test_simple_boxed_a_get_type     (void);
RegressTestSimpleBoxedA *regress_test_simple_boxed_a_copy         (RegressTestSimpleBoxedA *a);
gboolean                regress_test_simple_boxed_a_equals       (RegressTestSimpleBoxedA *a,
                                                          RegressTestSimpleBoxedA *other_a);
const RegressTestSimpleBoxedA *regress_test_simple_boxed_a_const_return (void);


struct _RegressTestSimpleBoxedB
{
  gint8 some_int8;
  RegressTestSimpleBoxedA nested_a;
};

GType             regress_test_simple_boxed_b_get_type (void);
RegressTestSimpleBoxedB *regress_test_simple_boxed_b_copy     (RegressTestSimpleBoxedB *b);

/* opaque boxed */
#define REGRESS_TEST_TYPE_BOXED (regress_test_boxed_get_type())

typedef struct _RegressTestBoxed RegressTestBoxed;
typedef struct _RegressTestBoxedPrivate RegressTestBoxedPrivate;

struct _RegressTestBoxed
{
  gint8 some_int8;
  RegressTestSimpleBoxedA nested_a;

  RegressTestBoxedPrivate *priv;
};

GType      regress_test_boxed_get_type (void);
RegressTestBoxed *regress_test_boxed_new      (void);
RegressTestBoxed *regress_test_boxed_new_alternative_constructor1  (int i);
RegressTestBoxed *regress_test_boxed_new_alternative_constructor2  (int i, int j);
RegressTestBoxed *regress_test_boxed_new_alternative_constructor3  (char *s);

RegressTestBoxed *regress_test_boxed_copy     (RegressTestBoxed *boxed);
gboolean   regress_test_boxed_equals   (RegressTestBoxed *boxed,
					RegressTestBoxed *other);

/* gobject */
#define REGRESS_TEST_TYPE_OBJ              (regress_test_obj_get_type ())
#define REGRESS_TEST_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_TEST_TYPE_OBJ, RegressTestObj))
#define REGRESS_TEST_IS_OBJECT(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_TEST_TYPE_OBJ))
#define REGRESS_TEST_OBJ_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), REGRESS_TEST_TYPE_OBJ, RegressTestObjClass))

typedef struct _RegressTestObj          RegressTestObj;
typedef struct _RegressTestObjClass     RegressTestObjClass;

/**
 * RegressTestObj:
 * @bare: (allow-none):
 */
struct _RegressTestObj
{
  GObject parent_instance;

  GObject *bare;
  RegressTestBoxed *boxed;
  GHashTable *hash_table;
  GList *list;
  gint8 some_int8;
  float some_float;
  double some_double;
  char* string;
};

struct _RegressTestObjClass
{
  GObjectClass parent_class;

  int (*matrix) (RegressTestObj *obj, const char *somestr);

  guint test_signal;
  guint test_signal_with_static_scope_arg;
};

GType      regress_test_obj_get_type (void);
RegressTestObj*   regress_test_obj_new_from_file (const char *x, GError **error);
void       regress_test_obj_set_bare (RegressTestObj *obj, GObject *bare);
int        regress_test_obj_instance_method (RegressTestObj *obj);
double     regress_test_obj_static_method (int x);

void regress_test_obj_torture_signature_0 (RegressTestObj    *obj,
                                   int        x,
                                   double     *y,
                                   int        *z,
                                   const char *foo,
                                   int        *q,
                                   guint       m);
gboolean regress_test_obj_torture_signature_1 (RegressTestObj    *obj,
                                       int        x,
                                       double     *y,
                                       int        *z,
                                       const char *foo,
                                       int        *q,
                                       guint       m,
                                       GError    **error);

/* virtual */
int        regress_test_obj_do_matrix (RegressTestObj *obj, const char *somestr);

void regress_test_obj_null_in (RegressTestObj *obj);
void regress_test_obj_null_out (RegressTestObj **obj);

/* inheritance */
#define REGRESS_TEST_TYPE_SUB_OBJ           (regress_test_sub_obj_get_type ())
#define REGRESS_TEST_SUB_OBJECT(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_TEST_TYPE_SUB_OBJ, RegressTestSubObj))
#define REGRESS_TEST_IS_SUB_OBJECT(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_TEST_TYPE_SUB_OBJ))
#define REGRESS_TEST_SUB_OBJ_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), REGRESS_TEST_TYPE_SUB_OBJ, RegressTestSubObjClass))

typedef struct _RegressTestSubObj         RegressTestSubObj;
typedef struct _RegressTestSubObjClass    RegressTestSubObjClass;

struct _RegressTestSubObj
{
  RegressTestObj parent_instance;
};

struct _RegressTestSubObjClass
{
  RegressTestObjClass parent_class;
};

GType       regress_test_sub_obj_get_type (void);
RegressTestSubObj* regress_test_sub_obj_new (void);
void        regress_test_sub_obj_unset_bare (RegressTestSubObj *obj);
int         regress_test_sub_obj_instance_method (RegressTestSubObj *obj);

/* fundamental object */
#define REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT            (regress_test_fundamental_object_get_type())
#define REGRESS_TEST_IS_FUNDAMENTAL_OBJECT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT))
#define REGRESS_TEST_IS_FUNDAMENTAL_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT))
#define REGRESS_TEST_FUNDAMENTAL_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT, RegressTestFundamentalObjectClass))
#define REGRESS_TEST_FUNDAMENTAL_OBJECT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT, RegressTestFundamentalObject))
#define REGRESS_TEST_FUNDAMENTAL_OBJECT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT, RegressTestFundamentalObjectClass))
#define REGRESS_TEST_FUNDAMENTAL_OBJECT_CAST(obj)       ((RegressTestFundamentalObject*)(obj))

typedef struct _RegressTestFundamentalObject RegressTestFundamentalObject;
typedef struct _RegressTestFundamentalObjectClass RegressTestFundamentalObjectClass;
/**
 * RegressTestFundamentalObjectCopyFunction:
 *
 * Returns: (transfer full):
 */
typedef RegressTestFundamentalObject * (*RegressTestFundamentalObjectCopyFunction) (const RegressTestFundamentalObject *obj);
typedef void (*RegressTestFundamentalObjectFinalizeFunction) (RegressTestFundamentalObject *obj);


struct _RegressTestFundamentalObject {
  GTypeInstance instance;
  gint refcount;
  guint flags;
};

struct _RegressTestFundamentalObjectClass {
  GTypeClass type_class;

  RegressTestFundamentalObjectCopyFunction copy;
  RegressTestFundamentalObjectFinalizeFunction finalize;
};

GType 		       regress_test_fundamental_object_get_type (void);
RegressTestFundamentalObject* regress_test_fundamental_object_ref      (RegressTestFundamentalObject *fundamental_object);
void 		       regress_test_fundamental_object_unref 	(RegressTestFundamentalObject *fundamental_object);

#define REGRESS_TEST_VALUE_HOLDS_FUNDAMENTAL_OBJECT(value)  (G_VALUE_HOLDS(value, REGRESS_TEST_TYPE_FUNDAMENTAL_OBJECT))

void 		       regress_test_value_set_fundamental_object (GValue *value, RegressTestFundamentalObject *fundamental_object);
RegressTestFundamentalObject* regress_test_value_get_fundamental_object (const GValue *value);

typedef struct _RegressTestFundamentalSubObject RegressTestFundamentalSubObject;
typedef struct _RegressTestFundamentalSubObjectClass RegressTestFundamentalSubObjectClass;

struct _RegressTestFundamentalSubObject
{
  RegressTestFundamentalObject fundamental_object;
  char *data;
};

struct _RegressTestFundamentalSubObjectClass {
  RegressTestFundamentalObjectClass fundamental_object_class;
};

GType regress_test_fundamental_sub_object_get_type(void);

RegressTestFundamentalSubObject *
regress_test_fundamental_sub_object_new (const char *data);

/* callback */
typedef void (*RegressTestSimpleCallback) (void);
typedef int (*RegressTestCallback) (void);
typedef int (*RegressTestCallbackUserData) (gpointer user_data);

void regress_test_simple_callback (RegressTestSimpleCallback callback);
int regress_test_callback (RegressTestCallback callback);
int regress_test_multi_callback (RegressTestCallback callback);
int regress_test_callback_user_data (RegressTestCallbackUserData callback,
                             gpointer user_data);
int regress_test_callback_destroy_notify (RegressTestCallbackUserData callback,
                                  gpointer user_data,
                                  GDestroyNotify notify);
int regress_test_callback_thaw_notifications (void);

void regress_test_callback_async (RegressTestCallbackUserData callback, gpointer user_data);
int regress_test_callback_thaw_async (void);

void regress_test_async_ready_callback (GAsyncReadyCallback callback);

void regress_test_obj_instance_method_callback (RegressTestObj *obj, RegressTestCallback callback);
void regress_test_obj_static_method_callback (RegressTestCallback callback);
RegressTestObj *regress_test_obj_new_callback (RegressTestCallbackUserData callback,
                                gpointer user_data,
                                GDestroyNotify notify);

/* interface */
#define REGRESS_TEST_TYPE_INTERFACE              (regress_test_interface_get_type ())
#define REGRESS_TEST_INTERFACE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_TEST_TYPE_INTERFACE, RegressTestInterface))
#define REGRESS_TEST_IS_INTERFACE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_TEST_TYPE_INTERFACE))
#define REGRESS_TEST_INTERFACE_GET_IFACE(obj)    (G_TYPE_INSTANCE_GET_INTERFACE ((obj), REGRESS_TEST_TYPE_INTERFACE, RegressTestInterfaceIface))

typedef struct _RegressTestInterfaceIface RegressTestInterfaceIface;

struct _RegressTestInterfaceIface {
    GTypeInterface base_iface;
};

GType regress_test_interface_get_type (void) G_GNUC_CONST;

/* gobject with non-standard prefix */
#define REGRESS_TEST_TYPE_WI_802_1X              (regress_test_wi_802_1x_get_type ())
#define REGRESS_TEST_WI_802_1X(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_TEST_TYPE_WI_802_1X, RegressTestWi8021x))
#define REGRESS_TEST_IS_WI_802_1X(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_TEST_TYPE_WI_802_1X))
#define REGRESS_TEST_WI_802_1X_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), REGRESS_TEST_TYPE_WI_802_1X, RegressTestWi8021xClass))

typedef struct
{
  GObject parent_instance;

  gboolean testbool;
} RegressTestWi8021x;

typedef struct
{
  GObjectClass parent_class;
} RegressTestWi8021xClass;

GType        regress_test_wi_802_1x_get_type (void);
RegressTestWi8021x* regress_test_wi_802_1x_new (void);
gboolean     regress_test_wi_802_1x_get_testbool (RegressTestWi8021x *obj);
void         regress_test_wi_802_1x_set_testbool (RegressTestWi8021x *obj, gboolean v);
int          regress_test_wi_802_1x_static_method (int x);

/* floating gobject */
#define REGRESS_TEST_TYPE_FLOATING           (regress_test_floating_get_type ())
#define REGRESS_TEST_FLOATING(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_TEST_TYPE_FLOATING, RegressTestFloating))
#define REGRESS_TEST_IS_FLOATING(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_TEST_TYPE_FLOATING))
#define REGRESS_TEST_FLOATING_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), REGRESS_TEST_TYPE_FLOATING, RegressTestFloatingClass))

typedef struct
{
  GInitiallyUnowned parent_instance;
} RegressTestFloating;

typedef struct
{
  GInitiallyUnownedClass parent_class;
} RegressTestFloatingClass;

GType        regress_test_floating_get_type (void);
RegressTestFloating* regress_test_floating_new (void);

/* Function signature torture tests */
void regress_test_torture_signature_0 (int        x,
                               double     *y,
                               int        *z,
                               const char *foo,
                               int        *q,
                               guint       m);
gboolean regress_test_torture_signature_1 (int        x,
                                   double     *y,
                                   int        *z,
                                   const char *foo,
                                   int        *q,
                                   guint       m,
                                   GError    **error);
void regress_test_torture_signature_2 (int                  x,
				       RegressTestCallbackUserData  callback,
				       gpointer              user_data,
				       GDestroyNotify        notify,
				       double               *y,
				       int                  *z,
				       const char           *foo,
				       int                  *q,
				       guint                 m);

GValue *regress_test_date_in_gvalue (void);
GValue *regress_test_strv_in_gvalue (void);

#endif /* __GITESTTYPES_H__ */
