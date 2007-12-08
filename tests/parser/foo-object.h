#ifndef __FOO_OBJECT_H__
#define __FOO_OBJECT_H__

#include <glib-object.h>

#define FOO_TYPE_OBJECT              (foo_object_get_type ())
#define FOO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_OBJECT, FooObject))
#define FOO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_OBJECT))

#define FOO_OBJECT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FOO_TYPE_OBJECT, FooObjectClass))
#define FOO_IS_OBJECT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FOO_TYPE_OBJECT))
#define FOO_OBJECT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FOO_TYPE_OBJECT, FooObjectClass))

typedef struct _FooObject       FooObject;
typedef struct _FooObjectClass  FooObjectClass;

struct _FooObject
{
  GObject parent_instance;
};

struct _FooObjectClass
{
  GObjectClass parent_class;
};

GType                 foo_object_get_type          (void) G_GNUC_CONST;
FooObject*            foo_object_new               ();
gint                  foo_object_method            (FooObject *object);
gint                  foo_init                     (void);

#endif /* __FOO_OBJECT_H__ */
