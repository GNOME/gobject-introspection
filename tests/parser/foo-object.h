#ifndef __FOO_OBJECT_H__
#define __FOO_OBJECT_H__

#include <glib-object.h>

#define FOO_TYPE_OBJECT              (foo_object_get_type ())
#define FOO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_OBJECT, FooObject))
#define FOO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_OBJECT))

#define FOO_TYPE_SUBOBJECT           (foo_subobject_get_type ())
#define FOO_SUBOBJECT(subobject)     (G_TYPE_CHECK_INSTANCE_CAST ((subobject), FOO_TYPE_SUBOBJECT, FooSubobject))
#define FOO_IS_SUBOBJECT(subobject)  (G_TYPE_CHECK_INSTANCE_TYPE ((subobject), FOO_TYPE_SUBOBJECT))

typedef struct _FooObject          FooObject;
typedef struct _FooObjectClass     FooObjectClass;
typedef struct _FooSubobject       FooSubobject;
typedef struct _FooSubobjectClass  FooSubobjectClass;

struct _FooObject
{
  GObject parent_instance;
};

struct _FooObjectClass
{
  GObjectClass parent_class;
};

gint                  foo_init                     (void);

GType                 foo_object_get_type          (void) G_GNUC_CONST;
FooObject*            foo_object_new               ();
gint                  foo_object_method            (FooObject *object);

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

#endif /* __FOO_OBJECT_H__ */
