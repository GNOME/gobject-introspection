#ifndef __FOO_OBJECT_H__
#define __FOO_OBJECT_H__

#include <glib-object.h>
#include <gio/gio.h> /* GAsyncReadyCallback */
#include "utility.h"

#define FOO_SUCCESS_INT 0x1138

#define FOO_DEFINE_SHOULD_BE_EXPOSED "should be exposed"

#define FOO_PIE_IS_TASTY 3.14159

#define FOO_TYPE_INTERFACE           (foo_interface_get_type ())
#define FOO_INTERFACE(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_INTERFACE, FooInterface))
#define FOO_IS_INTERFACE(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_INTERFACE))
#define FOO_INTERFACE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), FOO_TYPE_INTERFACE, FooInterfaceIface))

#define FOO_TYPE_SUBINTERFACE           (foo_sub_interface_get_type ())
#define FOO_SUBINTERFACE(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_SUBINTERFACE, FooSubInterface))
#define FOO_IS_SUBINTERFACE(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_SUBINTERFACE))
#define FOO_SUBINTERFACE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), FOO_TYPE_SUBINTERFACE, FooSubInterfaceIface))


#define FOO_TYPE_OBJECT              (foo_object_get_type ())
#define FOO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_OBJECT, FooObject))
#define FOO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_OBJECT))

#define FOO_TYPE_SUBOBJECT           (foo_subobject_get_type ())
#define FOO_SUBOBJECT(subobject)     (G_TYPE_CHECK_INSTANCE_CAST ((subobject), FOO_TYPE_SUBOBJECT, FooSubobject))
#define FOO_IS_SUBOBJECT(subobject)  (G_TYPE_CHECK_INSTANCE_TYPE ((subobject), FOO_TYPE_SUBOBJECT))

#define FOO_TYPE_BUFFER        (foo_buffer_get_type ())
#define FOO_BUFFER(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_BUFFER, FooBuffer))
#define FOO_IS_BUFFER(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_BUFFER))

#define FOO_TYPE_OTHER_OBJECT  (foo_other_object_get_type ())
#define FOO_OTHER_OBJECT(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_OTHER_OBJECT, FooOtherObject))
#define FOO_IS_OTHER_OBJECT(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_OTHER_OBJECT))

typedef struct _FooInterface       FooInterface;
typedef struct _FooInterfaceIface  FooInterfaceIface;
typedef struct _FooSubInterface       FooSubInterface;
typedef struct _FooSubInterfaceIface  FooSubInterfaceIface;
typedef struct _FooObject          FooObject;
typedef struct _FooObjectClass     FooObjectClass;
typedef struct _FooSubobject       FooSubobject;
typedef struct _FooSubobjectClass  FooSubobjectClass;
typedef struct _FooBuffer          FooBuffer;
typedef struct _FooBufferClass     FooBufferClass;
typedef struct _FooOtherObject          FooOtherObject;
typedef struct _FooOtherObjectClass     FooOtherObjectClass;

struct _FooInterfaceIface
{
  GTypeInterface parent_iface;

  void (*do_foo) (FooInterface *self, int x);
};

GType                 foo_interface_get_type       (void) G_GNUC_CONST;

void foo_interface_do_foo (FooInterface *iface, int x);

void foo_interface_static_method (int x);

struct _FooSubInterfaceIface
{
  GTypeInterface parent_iface;

  /* signals */

  void (*destroy_event) (FooSubInterface *self);

  /* virtual table */

  void (*do_bar) (FooSubInterface *self);

  /* explicitly test un-named parameters */
  void (*do_moo) (FooSubInterface *self, int, gpointer);

  void (*do_baz) (FooSubInterface *self, GCallback callback, gpointer user_data);
};

GType                 foo_sub_interface_get_type       (void) G_GNUC_CONST;

void foo_sub_interface_do_bar (FooSubInterface *self);
void foo_sub_interface_do_moo (FooSubInterface *self, int, gpointer);
void foo_sub_interface_do_baz (FooSubInterface *self,
                               GCallback callback,
                               gpointer user_data);

struct _FooObject
{
  GObject parent_instance;

  int some_int;
};

struct _FooObjectClass
{
  GObjectClass parent_class;

  gboolean (* virtual_method) (FooObject *object, int first_param);

  /* Intended to match GFile */
  void (*read_fn) (FooObject *object, int offset, int length);
  
  /* Test reserved stuff */
  GCallback _reserved[4];
};

gint                  foo_init                     (void);

GType                 foo_object_get_type          (void) G_GNUC_CONST;
FooObject*            foo_object_new               (void);
UtilityObject*        foo_object_external_type     (FooObject *object);
GObject*              foo_object_new_as_super      (void);

void                  foo_object_various           (FooObject *object, void *data, GType some_type);

void                  foo_object_take_all          (FooObject *object, int x, ...);

typedef gpointer FooObjectCookie;

FooObjectCookie       foo_object_new_cookie        (FooObject *object, const char *target);

void                  foo_object_is_it_time_yet    (FooObject *object, time_t time);

const char *          foo_object_get_name          (FooObject *object);

char *                foo_object_dup_name          (FooObject *object);

void                  foo_object_handle_glyph      (FooObject *object, UtilityGlyph glyph);

gboolean              foo_object_virtual_method    (FooObject *object, int first_param);

void                  foo_object_read              (FooObject *object, int offset, int length);

int                   foo_object_static_meth       (void);

void                  foo_object_skipped_method    (FooObject *object);

struct _FooSubobject
{
  FooObject parent_instance;
};

struct _FooSubobjectClass
{
  FooObjectClass parent_class;
};

GType                 foo_subobject_get_type       (void) G_GNUC_CONST;
FooSubobject*         foo_subobject_new            (void);

FooObject *           foo_object_get_default       (void);

GType                 foo_buffer_get_type          (void);

void                  foo_buffer_some_method       (FooBuffer *buffer);

GType                 foo_other_object_get_type    (void) G_GNUC_CONST;

FooObject *           foo_not_a_constructor_new    (void);

typedef enum
{
  FOO_ENUM_ALPHA,
  FOO_ENUM_BETA,
  FOO_ENUM_DELTA
} FooEnumType;

GType foo_enum_type_get_type (void);

int                   foo_enum_type_method         (FooEnumType foo_enum);

FooEnumType           foo_enum_type_returnv        (int x);

typedef enum
{
  FOO_FLAGS_FIRST  = 1 << 0,
  FOO_FLAGS_SECOND = 1 << 1,
  FOO_FLAGS_THIRD  = 1 << 2
} FooFlagsType;

GType foo_flags_type_get_type (void);

typedef enum
{
  FOO_ENUM_UN = 1,
  FOO_ENUM_DEUX = 2,
  FOO_ENUM_TROIS = 3,
  FOO_ENUM_NEUF = 9
} FooEnumNoType;

typedef enum
{
  FOO_FLAGS_ETT  = 1 << 0,
  FOO_FLAGS_TVA = 1 << 1,
  FOO_FLAGS_FYRA  = 1 << 2
} FooFlagsNoType;

typedef enum
{
  FOO_ENUM_FULLNAME_ONE = 1,
  FOO_ENUM_FULLNAME_TWO,
  FOO_ENUM_FULLNAME_THREE
} FooEnumFullname;

typedef enum
{
  FOO_ADDRESS_INVALID,
  FOO_ADDRESS_IPV4,
  FOO_ADDRESS_IPV6
} FooAddressType;

typedef struct _FooBoxed FooBoxed;

GType                 foo_boxed_get_type       (void) G_GNUC_CONST;
FooBoxed*             foo_boxed_new            (void);
void                  foo_boxed_method         (FooBoxed* boxed);

/* This one tests capitalization handling with respect to DBus */
typedef struct _FooDBusData FooDBusData;
GType                 foo_dbus_data_get_type       (void) G_GNUC_CONST;
void                  foo_dbus_data_method         (FooDBusData* dbusdata);

/* FIXME: Scanner does not support this yet
const char *FOO_CONSTANT_STR = "foo-constant-str";
const int FOO_CONSTANT_INT = 10;
const float FOO_CONSTANT_FLOAT = 10;
*/

/* Callback */
typedef gboolean (* FooCallback) (FooObject *foo, gboolean b, gpointer data);

/* Invalid comments, should be ignored */

/* @ */
/* @: */

typedef struct _FooStruct           FooStruct; 
typedef struct _FooStructPrivate    FooStructPrivate; 

struct _FooStruct
{
  FooStructPrivate *priv;
  int member;
};

typedef struct _FooRectangle          FooRectangle;

struct _FooRectangle
{
  gint x;
  gint y;
  gint width;
  gint height;
};

void
foo_method_external_references (UtilityObject *object,
				UtilityEnumType e,
				UtilityFlagType f,
				UtilityStruct s);

void foo_rectangle_add(FooRectangle *r1, const FooRectangle *r2);

FooRectangle * foo_rectangle_new (int x, int y, int width, int height);


typedef struct _FooEventAny FooEventAny;
typedef struct _FooEventExpose FooEventExpose;

typedef union  _FooEvent FooEvent;

struct _FooEventAny
{
  gint8 send_event;
};

struct _FooEventExpose
{
  gint8 send_event;
  gint count;
};
  
union _FooEvent
{
  int type;
  FooEventAny any;
  FooEventExpose expose;
};

typedef void FooXEvent;

/* And now some boxed variants */

typedef struct _FooBRect          FooBRect;

struct _FooBRect
{
  double x;
  double y;
};

GType foo_brect_get_type (void);

FooBRect *foo_brect_new (double x, double y);

void foo_brect_add (FooBRect *b1, FooBRect *b2);

typedef union _FooBUnion FooBUnion;

union _FooBUnion
{
  int type;
  double v;
  FooBRect *rect;
};

typedef union _FooUnion FooUnion;

union _FooUnion
{
  int foo;
};

typedef struct _FooUtilityStruct FooUtilityStruct;
struct _FooUtilityStruct
{
  UtilityStruct bar;
};

typedef struct _FooThingWithArray FooThingWithArray;
struct _FooThingWithArray
{
  int x;
  int y;
  char lines[80];
  guchar *data;
} ;

FooBUnion *foo_bunion_new (void);

GType foo_bunion_get_type (void);

int foo_bunion_get_contained_type (FooBUnion *bunion);

void foo_test_unsigned_qualifier (unsigned int unsigned_param);
void foo_test_unsigned_type (unsigned unsigned_param);

void foo_test_string_array (char **array);

void foo_test_string_array_with_g (gchar **array);

GArray *foo_test_array (void);

const char * foo_test_const_char_retval (void);
const FooStruct * foo_test_const_struct_retval (void);
void foo_test_const_char_param (const char * param);
void foo_test_const_struct_param (const FooStruct * param);

typedef void (*FooVarargsCallback) (const char * param, ...);
void foo_test_varargs_callback (gint i, FooVarargsCallback callback);
void foo_test_varargs_callback2 (FooVarargsCallback callback);
void foo_test_varargs_callback3 (FooVarargsCallback callback,
				 FooVarargsCallback callback2);

/* Make sure callbacks get the right scope by default */
void foo_async_ready_callback(GCancellable *cancellable,
                              GAsyncReadyCallback callback,
                              gpointer user_data);
void foo_destroy_notify_callback(FooCallback callback,
                                 gpointer data,
                                 GDestroyNotify destroy);

typedef enum {
  FOO_ERROR_GOOD,
  FOO_ERROR_BAD,
  FOO_ERROR_UGLY
} FooError;
GType foo_error_get_type (void);

GQuark foo_error_quark (void);

typedef enum
{
  FOO_LAYER_DESKTOP        = 0,
  FOO_LAYER_BOTTOM        = 1,
  FOO_LAYER_NORMAL        = 2,
  FOO_LAYER_TOP        = 4, /* Same as DOCK; see EWMH and bug 330717 */
  FOO_LAYER_DOCK        = 4,
  FOO_LAYER_FULLSCREEN        = 5,
  FOO_LAYER_FOCUSED_WINDOW    = 6,
  FOO_LAYER_OVERRIDE_REDIRECT = 7,
  FOO_LAYER_LAST        = 8
} FooStackLayer;

typedef enum
{
  FOO_SOME_SINGLE_ENUM
} FooASingle;

/* Should be skipped */
void foo_some_variant (guint x, va_list args);
void foo_some_variant_ptr (guint x, va_list *args);

/**
 * FooSkippable: (skip)
 * @FOO_SKIPPABLE_ONE: a skippable enum value
 * @FOO_SKIPPABLE_TWO: another skippable enum value
 *
 * Some type that is only interesting from C and should not be
 * exposed to language bindings.
 */
typedef enum {
  FOO_SKIPPABLE_ONE,
  FOO_SKIPPABLE_TWO
} FooSkippable;
void foo_skip_me (FooSkippable fs);

typedef struct _FooForeignStruct           FooForeignStruct;

struct _FooForeignStruct
{
  int foo;
};

FooForeignStruct* foo_foreign_struct_new (void);
FooForeignStruct* foo_foreign_struct_copy (FooForeignStruct *original);

/* This one should be a global, not a method on UtilityObject since
 * it's a separate namespace.
 */
void foo_object_a_global_method (UtilityObject *obj);

FooOtherObject * foo_object_append_new_stack_layer (FooObject *obj, int x);

#endif /* __FOO_OBJECT_H__ */
