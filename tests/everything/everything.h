#ifndef __GITESTTYPES_H__
#define __GITESTTYPES_H__

#include <glib-object.h>
#include <time.h>

/* basic types */
gboolean test_boolean (gboolean in);
gint8 test_int8 (gint8 in);
guint8 test_uint8 (guint8 in);
gint16 test_int16 (gint16 in);
guint16 test_uint16 (guint16 in);
gint32 test_int32 (gint32 in);
guint32 test_uint32 (guint32 in);
gint64 test_int64 (gint64 in);
guint64 test_uint64 (guint64 in);
gint test_int (gint in);
guint test_uint (guint in);
glong test_long (glong in);
gulong test_ulong (gulong in);
gssize test_ssize (gssize in);
gsize test_size (gsize in);
gfloat test_float (gfloat in);
gdouble test_double (gdouble in);
time_t test_timet (time_t in);
GType test_gtype (GType in);
#if 0
/* utf8 */
G_CONST_RETURN char *test_utf8_const_return (void);
char *test_utf8_nonconst_return (void);
void test_utf8_nonconst_in (char *in);
void test_utf8_const_in (const char *in);
void test_utf8_out (char **out);
void test_utf8_inout (char **inout);
#endif
GSList *test_filename_return (void);
/* non-basic-types */
/* array */
gboolean test_strv_in (char **arr);
int test_array_int_in (int n_ints, int *ints);
char *test_array_gtype_in (int n_types, GType *types);
char **test_strv_out (void);
/* interface */
/* GList */
G_CONST_RETURN GList *test_glist_nothing_return (void);
GList *test_glist_nothing_return2 (void);
GList *test_glist_container_return (void);
GList *test_glist_everything_return (void);
void test_glist_nothing_in (const GList *in);
void test_glist_nothing_in2 (GList *in);
void test_glist_container_in (GList *in);
void test_glist_everything_in (GList *in);
void test_glist_free (GList *in);

/* GSList */
G_CONST_RETURN GSList *test_gslist_nothing_return (void);
GSList *test_gslist_nothing_return2 (void);
GSList *test_gslist_container_return (void);
GSList *test_gslist_everything_return (void);
void test_gslist_nothing_in (const GSList *in);
void test_gslist_nothing_in2 (GSList *in);
void test_gslist_container_in (GSList *in);
void test_gslist_everything_in (GSList *in);
void test_gslist_free (GSList *in);

/* ghash? */
/* error? */

/* closure */
int test_closure (GClosure *closure);
int test_closure_one_arg (GClosure *closure, int arg);

/* value */
int test_int_value_arg(const GValue *v);
const GValue *test_value_return(int i);

/* enums / flags */

typedef enum
{
  TEST_VALUE1,
  TEST_VALUE2,
  TEST_VALUE3 = 42
} TestEnum;

typedef enum
{
  TEST_FLAG1 = 1 << 0,
  TEST_FLAG2 = 1 << 1,
  TEST_FLAG3 = 1 << 2,
} TestFlags;

GType test_enum_get_type (void) G_GNUC_CONST;
#define TEST_TYPE_ENUM (test_enum_get_type ())
GType test_flags_get_type (void) G_GNUC_CONST;
#define TES_TYPE_FLAGS (test_flags_get_type ())

const gchar * test_enum_param(TestEnum e);

/* structures */
typedef struct _TestStructA TestStructA;
typedef struct _TestStructB TestStructB;

struct _TestStructA
{
  gint some_int;
  gint8 some_int8;
  gdouble some_double;
  TestEnum some_enum;
};

void test_struct_a_clone (TestStructA *a,
			  TestStructA *a_out);

struct _TestStructB
{
  gint8 some_int8;
  TestStructA nested_a;
};

void test_struct_b_clone (TestStructB *b,
			  TestStructB *b_out);

/* This one has a non-basic member */
struct _TestStructC
{
  gint another_int;
  GObject *obj;
};

/* plain-old-data boxed types */
typedef struct _TestSimpleBoxedA TestSimpleBoxedA;
typedef struct _TestSimpleBoxedB TestSimpleBoxedB;

struct _TestSimpleBoxedA
{
  gint some_int;
  gint8 some_int8;
  gdouble some_double;
  TestEnum some_enum;
};

GType                   test_simple_boxed_a_get_type     (void);
TestSimpleBoxedA *      test_simple_boxed_a_copy         (TestSimpleBoxedA *a);
gboolean                test_simple_boxed_a_equals       (TestSimpleBoxedA *a,
                                                          TestSimpleBoxedA *other_a);
const TestSimpleBoxedA *test_simple_boxed_a_const_return (void);


struct _TestSimpleBoxedB
{
  gint8 some_int8;
  TestSimpleBoxedA nested_a;
};

GType             test_simple_boxed_b_get_type (void);
TestSimpleBoxedB *test_simple_boxed_b_copy     (TestSimpleBoxedB *b);

/* opaque boxed */
typedef struct _TestBoxed TestBoxed;
typedef struct _TestBoxedPrivate TestBoxedPrivate;

struct _TestBoxed
{
  gint8 some_int8;
  TestSimpleBoxedA nested_a;

  TestBoxedPrivate *priv;
};

GType      test_boxed_get_type (void);
TestBoxed *test_boxed_new      (void);
TestBoxed *test_boxed_copy     (TestBoxed *boxed);
gboolean   test_boxed_equals   (TestBoxed *boxed,
				TestBoxed *other);

/* gobject */
#define TEST_TYPE_OBJ              (test_obj_get_type ())
#define TEST_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), TEST_TYPE_OBJ, TestObj))
#define TEST_IS_OBJECT(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), TEST_TYPE_OBJ))
#define TEST_OBJ_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), TEST_TYPE_OBJ, TestObjClass))

typedef struct _TestObj          TestObj;
typedef struct _TestObjClass     TestObjClass;

/**
 * TestObj:
 * @bare: (allow-none):
 */
struct _TestObj
{
  GObject parent_instance;

  GObject *bare;
};

struct _TestObjClass
{
  GObjectClass parent_class;

  int (*matrix) (TestObj *obj, const char *somestr);

  guint test_signal;
  guint test_signal_with_static_scope_arg;
};

GType      test_obj_get_type (void);
TestObj*   test_obj_new_from_file (const char *x, GError **error);
void       test_obj_set_bare (TestObj *obj, GObject *bare);
double     test_obj_static_method (int x);

/* virtual */
int        test_obj_do_matrix (TestObj *obj, const char *somestr);

/* callback */
typedef int (*TestCallback) ();
typedef int (*TestCallbackUserData) (gpointer user_data);

int test_callback (TestCallback callback);
int test_callback_user_data (TestCallbackUserData callback,
                             gpointer user_data);
int test_callback_destroy_notify (TestCallbackUserData callback,
                                  gpointer user_data,
                                  GDestroyNotify notify);
int test_callback_thaw_notifications (void);
int test_callback_infinte (TestCallbackUserData callback,
                           gpointer user_data);


#endif /* __GITESTTYPES_H__ */
