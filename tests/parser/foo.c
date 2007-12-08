#define FOO_SUCCESS_INT 0x1138

#include "foo-object.h"

G_DEFINE_TYPE (FooObject, foo_object, G_TYPE_OBJECT);

static void
foo_object_class_init (FooObjectClass *klass)
{

}

static void
foo_object_init (FooObject *object)
{

}

G_DEFINE_TYPE (FooSubobject, foo_subobject, FOO_TYPE_OBJECT);

static void
foo_subobject_class_init (FooSubobjectClass *klass)
{

}

static void
foo_subobject_init (FooSubobject *object)
{

}

int foo_init (void)
{
  return FOO_SUCCESS_INT;
}

int foo_init_argv (int argc, char **argv)
{
  return FOO_SUCCESS_INT;
}

int foo_init_argv_address (int *argc, char ***argv)
{
  return FOO_SUCCESS_INT;
}
