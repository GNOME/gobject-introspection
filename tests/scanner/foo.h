#ifndef __REGRESS_FOO_OBJECT_H__
#define __REGRESS_FOO_OBJECT_H__

#include <glib-object.h>
#include <gio/gio.h> /* GAsyncReadyCallback */
#include "utility.h"

#define REGRESS_FOO_SUCCESS_INT 0x1138

#define REGRESS_FOO_DEFINE_SHOULD_BE_EXPOSED "should be exposed"

#define REGRESS_FOO_PIE_IS_TASTY 3.14159

#define REGRESS_FOO_TYPE_INTERFACE           (regress_foo_interface_get_type ())
#define REGRESS_FOO_INTERFACE(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_FOO_TYPE_INTERFACE, RegressFooInterface))
#define REGRESS_FOO_IS_INTERFACE(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_FOO_TYPE_INTERFACE))
#define REGRESS_FOO_INTERFACE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), REGRESS_FOO_TYPE_INTERFACE, RegressFooInterfaceIface))

#define REGRESS_FOO_TYPE_SUBINTERFACE           (regress_foo_sub_interface_get_type ())
#define REGRESS_FOO_SUBINTERFACE(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_FOO_TYPE_SUBINTERFACE, RegressFooSubInterface))
#define REGRESS_FOO_IS_SUBINTERFACE(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_FOO_TYPE_SUBINTERFACE))
#define REGRESS_FOO_SUBINTERFACE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), REGRESS_FOO_TYPE_SUBINTERFACE, RegressFooSubInterfaceIface))


#define REGRESS_FOO_TYPE_OBJECT              (regress_foo_object_get_type ())
#define REGRESS_FOO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_FOO_TYPE_OBJECT, RegressFooObject))
#define REGRESS_FOO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_FOO_TYPE_OBJECT))

#define REGRESS_FOO_TYPE_SUBOBJECT           (regress_foo_subobject_get_type ())
#define REGRESS_FOO_SUBOBJECT(subobject)     (G_TYPE_CHECK_INSTANCE_CAST ((subobject), REGRESS_FOO_TYPE_SUBOBJECT, RegressFooSubobject))
#define REGRESS_FOO_IS_SUBOBJECT(subobject)  (G_TYPE_CHECK_INSTANCE_TYPE ((subobject), REGRESS_FOO_TYPE_SUBOBJECT))

#define REGRESS_FOO_TYPE_BUFFER        (regress_foo_buffer_get_type ())
#define REGRESS_FOO_BUFFER(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_FOO_TYPE_BUFFER, RegressFooBuffer))
#define REGRESS_FOO_IS_BUFFER(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_FOO_TYPE_BUFFER))

#define REGRESS_FOO_TYPE_OTHER_OBJECT  (regress_foo_other_object_get_type ())
#define REGRESS_FOO_OTHER_OBJECT(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), REGRESS_FOO_TYPE_OTHER_OBJECT, RegressFooOtherObject))
#define REGRESS_FOO_IS_OTHER_OBJECT(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), REGRESS_FOO_TYPE_OTHER_OBJECT))

typedef struct _RegressFooInterface       RegressFooInterface;
typedef struct _RegressFooInterfaceIface  RegressFooInterfaceIface;
typedef struct _RegressFooSubInterface       RegressFooSubInterface;
typedef struct _RegressFooSubInterfaceIface  RegressFooSubInterfaceIface;
typedef struct _RegressFooObject          RegressFooObject;
typedef struct _RegressFooObjectClass     RegressFooObjectClass;
typedef struct _RegressFooSubobject       RegressFooSubobject;
typedef struct _RegressFooSubobjectClass  RegressFooSubobjectClass;
typedef struct _RegressFooBuffer          RegressFooBuffer;
typedef struct _RegressFooBufferClass     RegressFooBufferClass;
typedef struct _RegressFooOtherObject          RegressFooOtherObject;
typedef struct _RegressFooOtherObjectClass     RegressFooOtherObjectClass;

struct _RegressFooInterfaceIface
{
  GTypeInterface parent_iface;

  void (*do_regress_foo) (RegressFooInterface *self, int x);
};

GType                 regress_foo_interface_get_type       (void) G_GNUC_CONST;

void regress_foo_interface_do_regress_foo (RegressFooInterface *iface, int x);

void regress_foo_interface_static_method (int x);

struct _RegressFooSubInterfaceIface
{
  GTypeInterface parent_iface;

  /* signals */

  void (*destroy_event) (RegressFooSubInterface *self);

  /* virtual table */

  void (*do_bar) (RegressFooSubInterface *self);

  /* explicitly test un-named parameters */
  void (*do_moo) (RegressFooSubInterface *self, int, gpointer);

  void (*do_baz) (RegressFooSubInterface *self, GCallback callback, gpointer user_data);
};

GType                 regress_foo_sub_interface_get_type       (void) G_GNUC_CONST;

void regress_foo_sub_interface_do_bar (RegressFooSubInterface *self);
void regress_foo_sub_interface_do_moo (RegressFooSubInterface *self, int, gpointer);
void regress_foo_sub_interface_do_baz (RegressFooSubInterface *self,
                                       GCallback callback,
                                       gpointer user_data);

struct _RegressFooObject
{
  GObject parent_instance;

  int some_int;
};

struct _RegressFooObjectClass
{
  GObjectClass parent_class;

  gboolean (* virtual_method) (RegressFooObject *object, int first_param);

  /* Intended to match GFile */
  void (*read_fn) (RegressFooObject *object, int offset, int length);
  
  /* Test reserved stuff */
  GCallback _reserved[4];
};

gint                  regress_foo_init                     (void);

GType                 regress_foo_object_get_type          (void) G_GNUC_CONST;
RegressFooObject*            regress_foo_object_new               (void);
UtilityObject*        regress_foo_object_external_type     (RegressFooObject *object);
GObject*              regress_foo_object_new_as_super      (void);

void                  regress_foo_object_various           (RegressFooObject *object, void *data, GType some_type);

void                  regress_foo_object_take_all          (RegressFooObject *object, int x, ...);

typedef gpointer RegressFooObjectCookie;

RegressFooObjectCookie       regress_foo_object_new_cookie        (RegressFooObject *object, const char *target);

void                  regress_foo_object_is_it_time_yet    (RegressFooObject *object, time_t time);

const char *          regress_foo_object_get_name          (RegressFooObject *object);

char *                regress_foo_object_dup_name          (RegressFooObject *object);

void                  regress_foo_object_handle_glyph      (RegressFooObject *object, UtilityGlyph glyph);

gboolean              regress_foo_object_virtual_method    (RegressFooObject *object, int first_param);

void                  regress_foo_object_read              (RegressFooObject *object, int offset, int length);

int                   regress_foo_object_static_meth       (void);

void                  regress_foo_object_skipped_method    (RegressFooObject *object);

struct _RegressFooSubobject
{
  RegressFooObject parent_instance;
};

struct _RegressFooSubobjectClass
{
  RegressFooObjectClass parent_class;
};

GType                 regress_foo_subobject_get_type       (void) G_GNUC_CONST;
RegressFooSubobject*         regress_foo_subobject_new            (void);

RegressFooObject *           regress_foo_object_get_default       (void);

GType                 regress_foo_buffer_get_type          (void);

void                  regress_foo_buffer_some_method       (RegressFooBuffer *buffer);

GType                 regress_foo_other_object_get_type    (void) G_GNUC_CONST;

RegressFooObject *           regress_foo_not_a_constructor_new    (void);

typedef enum
{
  REGRESS_FOO_ENUM_ALPHA,
  REGRESS_FOO_ENUM_BETA,
  REGRESS_FOO_ENUM_DELTA
} RegressFooEnumType;

GType regress_foo_enum_type_get_type (void);

int                   regress_foo_enum_type_method         (RegressFooEnumType regress_foo_enum);

RegressFooEnumType           regress_foo_enum_type_returnv        (int x);

typedef enum
{
  REGRESS_FOO_FLAGS_FIRST  = 1 << 0,
  REGRESS_FOO_FLAGS_SECOND = 1 << 1,
  REGRESS_FOO_FLAGS_THIRD  = 1 << 2
} RegressFooFlagsType;

GType regress_foo_flags_type_get_type (void);

typedef enum
{
  REGRESS_FOO_ENUM_UN = 1,
  REGRESS_FOO_ENUM_DEUX = 2,
  REGRESS_FOO_ENUM_TROIS = 3,
  REGRESS_FOO_ENUM_NEUF = 9
} RegressFooEnumNoType;

typedef enum
{
  REGRESS_FOO_FLAGS_ETT  = 1 << 0,
  REGRESS_FOO_FLAGS_TVA = 1 << 1,
  REGRESS_FOO_FLAGS_FYRA  = 1 << 2
} RegressFooFlagsNoType;

typedef enum
{
  REGRESS_FOO_ENUM_FULLNAME_ONE = 1,
  REGRESS_FOO_ENUM_FULLNAME_TWO,
  REGRESS_FOO_ENUM_FULLNAME_THREE
} RegressFooEnumFullname;

typedef enum
{
  REGRESS_FOO_ADDRESS_INVALID,
  REGRESS_FOO_ADDRESS_IPV4,
  REGRESS_FOO_ADDRESS_IPV6
} RegressFooAddressType;

typedef struct _RegressFooBoxed RegressFooBoxed;

GType                 regress_foo_boxed_get_type       (void) G_GNUC_CONST;
RegressFooBoxed*             regress_foo_boxed_new            (void);
void                  regress_foo_boxed_method         (RegressFooBoxed* boxed);

/* This one tests capitalization handling with respect to DBus */
typedef struct _RegressFooDBusData RegressFooDBusData;
GType                 regress_foo_dbus_data_get_type       (void) G_GNUC_CONST;
void                  regress_foo_dbus_data_method         (RegressFooDBusData* dbusdata);

/* FIXME: Scanner does not support this yet
const char *REGRESS_FOO_CONSTANT_STR = "regress_foo-constant-str";
const int REGRESS_FOO_CONSTANT_INT = 10;
const float REGRESS_FOO_CONSTANT_FLOAT = 10;
*/

/* Callback */
typedef gboolean (* RegressFooCallback) (RegressFooObject *regress_foo, gboolean b, gpointer data);

/* Invalid comments, should be ignored */

/* @ */
/* @: */

typedef struct _RegressFooStruct           RegressFooStruct; 
typedef struct _RegressFooStructPrivate    RegressFooStructPrivate; 

struct _RegressFooStruct
{
  RegressFooStructPrivate *priv;
  int member;
};

typedef struct _RegressFooRectangle          RegressFooRectangle;

struct _RegressFooRectangle
{
  gint x;
  gint y;
  gint width;
  gint height;
};

void
regress_foo_method_external_references (UtilityObject *object,
                                        UtilityEnumType e,
                                        UtilityFlagType f,
                                        UtilityStruct s);

void regress_foo_rectangle_add(RegressFooRectangle *r1, const RegressFooRectangle *r2);

RegressFooRectangle * regress_foo_rectangle_new (int x, int y, int width, int height);


typedef struct _RegressFooEventAny RegressFooEventAny;
typedef struct _RegressFooEventExpose RegressFooEventExpose;

typedef union  _RegressFooEvent RegressFooEvent;

struct _RegressFooEventAny
{
  gint8 send_event;
};

struct _RegressFooEventExpose
{
  gint8 send_event;
  gint count;
};
  
union _RegressFooEvent
{
  int type;
  RegressFooEventAny any;
  RegressFooEventExpose expose;
};

typedef void RegressFooXEvent;

/* And now some boxed variants */

typedef struct _RegressFooBRect          RegressFooBRect;

struct _RegressFooBRect
{
  double x;
  double y;
};

GType regress_foo_brect_get_type (void);

RegressFooBRect *regress_foo_brect_new (double x, double y);

void regress_foo_brect_add (RegressFooBRect *b1, RegressFooBRect *b2);

typedef union _RegressFooBUnion RegressFooBUnion;

union _RegressFooBUnion
{
  int type;
  double v;
  RegressFooBRect *rect;
};

typedef union _RegressFooUnion RegressFooUnion;

union _RegressFooUnion
{
  int regress_foo;
};

typedef struct _RegressFooUtilityStruct RegressFooUtilityStruct;
struct _RegressFooUtilityStruct
{
  UtilityStruct bar;
};

typedef struct _RegressFooThingWithArray RegressFooThingWithArray;
struct _RegressFooThingWithArray
{
  int x;
  int y;
  char lines[80];
  guchar *data;
} ;

RegressFooBUnion *regress_foo_bunion_new (void);

GType regress_foo_bunion_get_type (void);

int regress_foo_bunion_get_contained_type (RegressFooBUnion *bunion);

void regress_foo_test_unsigned_qualifier (unsigned int unsigned_param);
void regress_foo_test_unsigned_type (unsigned unsigned_param);

void regress_foo_test_string_array (char **array);

void regress_foo_test_string_array_with_g (gchar **array);

GArray *regress_foo_test_array (void);

const char * regress_foo_test_const_char_retval (void);
const RegressFooStruct * regress_foo_test_const_struct_retval (void);
void regress_foo_test_const_char_param (const char * param);
void regress_foo_test_const_struct_param (const RegressFooStruct * param);

typedef void (*RegressFooVarargsCallback) (const char * param, ...);
void regress_foo_test_varargs_callback (gint i, RegressFooVarargsCallback callback);
void regress_foo_test_varargs_callback2 (RegressFooVarargsCallback callback);
void regress_foo_test_varargs_callback3 (RegressFooVarargsCallback callback,
                                         RegressFooVarargsCallback callback2);

/* Make sure callbacks get the right scope by default */
void regress_foo_async_ready_callback(GCancellable *cancellable,
                                      GAsyncReadyCallback callback,
                                      gpointer user_data);
void regress_foo_destroy_notify_callback(RegressFooCallback callback,
                                         gpointer data,
                                         GDestroyNotify destroy);

typedef enum {
  REGRESS_FOO_ERROR_GOOD,
  REGRESS_FOO_ERROR_BAD,
  REGRESS_FOO_ERROR_UGLY
} RegressFooError;
GType regress_foo_error_get_type (void);

GQuark regress_foo_error_quark (void);

typedef enum
{
  REGRESS_FOO_LAYER_DESKTOP        = 0,
  REGRESS_FOO_LAYER_BOTTOM        = 1,
  REGRESS_FOO_LAYER_NORMAL        = 2,
  REGRESS_FOO_LAYER_TOP        = 4, /* Same as DOCK; see EWMH and bug 330717 */
  REGRESS_FOO_LAYER_DOCK        = 4,
  REGRESS_FOO_LAYER_FULLSCREEN        = 5,
  REGRESS_FOO_LAYER_FOCUSED_WINDOW    = 6,
  REGRESS_FOO_LAYER_OVERRIDE_REDIRECT = 7,
  REGRESS_FOO_LAYER_LAST        = 8
} RegressFooStackLayer;

typedef enum
{
  REGRESS_FOO_SOME_SINGLE_ENUM
} RegressFooASingle;

/* Should be skipped */
void regress_foo_some_variant (guint x, va_list args);
void regress_foo_some_variant_ptr (guint x, va_list *args);

/**
 * RegressFooSkippable: (skip)
 * @REGRESS_FOO_SKIPPABLE_ONE: a skippable enum value
 * @REGRESS_FOO_SKIPPABLE_TWO: another skippable enum value
 *
 * Some type that is only interesting from C and should not be
 * exposed to language bindings.
 */
typedef enum {
  REGRESS_FOO_SKIPPABLE_ONE,
  REGRESS_FOO_SKIPPABLE_TWO
} RegressFooSkippable;
void regress_foo_skip_me (RegressFooSkippable fs);

typedef struct _RegressFooForeignStruct           RegressFooForeignStruct;

struct _RegressFooForeignStruct
{
  int regress_foo;
};

RegressFooForeignStruct* regress_foo_foreign_struct_new (void);
RegressFooForeignStruct* regress_foo_foreign_struct_copy (RegressFooForeignStruct *original);

/* This one should be a global, not a method on UtilityObject since
 * it's a separate namespace.
 */
void regress_foo_object_a_global_method (UtilityObject *obj);

RegressFooOtherObject * regress_foo_object_append_new_stack_layer (RegressFooObject *obj, int x);

#endif /* __REGRESS_FOO_OBJECT_H__ */
