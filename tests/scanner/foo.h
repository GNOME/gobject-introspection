#ifndef __FOO_OBJECT_H__
#define __FOO_OBJECT_H__

#include <glib-object.h>
#include "utility.h"

#define FOO_TYPE_INTERFACE           (foo_interface_get_type ())
#define FOO_INTERFACE(object)        (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_INTERFACE, FooInterface))
#define FOO_IS_INTERFACE(object)     (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_INTERFACE))
#define FOO_INTERFACE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), FOO_TYPE_INTERFACE, FooInterfaceIface))

#define FOO_TYPE_OBJECT              (foo_object_get_type ())
#define FOO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_OBJECT, FooObject))
#define FOO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_OBJECT))

#define FOO_TYPE_SUBOBJECT           (foo_subobject_get_type ())
#define FOO_SUBOBJECT(subobject)     (G_TYPE_CHECK_INSTANCE_CAST ((subobject), FOO_TYPE_SUBOBJECT, FooSubobject))
#define FOO_IS_SUBOBJECT(subobject)  (G_TYPE_CHECK_INSTANCE_TYPE ((subobject), FOO_TYPE_SUBOBJECT))

typedef struct _FooInterface       FooInterface;
typedef struct _FooInterfaceIface  FooInterfaceIface;
typedef struct _FooObject          FooObject;
typedef struct _FooObjectClass     FooObjectClass;
typedef struct _FooSubobject       FooSubobject;
typedef struct _FooSubobjectClass  FooSubobjectClass;

struct _FooInterfaceIface
{
  GTypeInterface parent_iface;

  void (*do_foo) (FooInterface *self);
};

GType                 foo_interface_get_type       (void) G_GNUC_CONST;

struct _FooObject
{
  GObject parent_instance;
};

struct _FooObjectClass
{
  GObjectClass parent_class;

  gboolean (* virtual_method) (FooObject *object, int first_param);
};

gint                  foo_init                     (void);

GType                 foo_object_get_type          (void) G_GNUC_CONST;
FooObject*            foo_object_new               ();
UtilityObject*        foo_object_external_type     (FooObject *object);

void                  foo_object_various           (FooObject *object, void *data, GType some_type);

void                  foo_object_take_all          (FooObject *object, int x, ...);

/* A random typedef */
typedef GSList FooList;

void                  foo_object_with_tdef         (FooObject *object, FooList *blah);

typedef gpointer FooObjectCookie;

FooObjectCookie       foo_object_new_cookie        (FooObject *object, const char *target);

void                  foo_object_is_it_time_yet    (FooObject *object, time_t time);

struct _FooSubobject
{
  FooObject parent_instance;
};

struct _FooSubobjectClass
{
  FooObjectClass parent_class;
};

GType                 foo_subobject_get_type       (void) G_GNUC_CONST;
FooSubobject*         foo_subobject_new            ();

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

typedef enum
{
  FOO_ENUM_UN = 1,
  FOO_ENUM_DEUX = 2,
  FOO_ENUM_TROIS = 3,
} FooEnumNoType;

GType foo_flags_type_get_type (void);

typedef enum
{
  FOO_ENUM_FULLNAME_ONE = 1,
  FOO_ENUM_FULLNAME_TWO,
  FOO_ENUM_FULLNAME_THREE
} FooEnumFullname;

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

#endif /* __FOO_OBJECT_H__ */
