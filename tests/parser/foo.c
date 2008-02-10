#define FOO_SUCCESS_INT 0x1138

#include "foo-object.h"

GType
foo_interface_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      object_type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                   "FooInterface",
                                                   sizeof (FooInterfaceIface),
                                                   NULL, 0, NULL, 0);

      g_type_interface_add_prerequisite (object_type, G_TYPE_OBJECT);
    }

  return object_type;
}

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

GType
foo_enum_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { FOO_ENUM_ALPHA, "FOO_ENUM_ALPHA", "alpha" },
            { FOO_ENUM_BETA, "FOO_ENUM_BETA", "beta" },
            { FOO_ENUM_DELTA, "FOO_ENUM_DELTA", "delta" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("FooEnumType"), values);
    }
    return etype;
}

GType
foo_flags_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { FOO_FLAGS_FIRST, "FOO_FLAGS_FIRST", "first" },
            { FOO_FLAGS_SECOND, "FOO_FLAGS_SECOND", "second" },
            { FOO_FLAGS_THIRD, "FOO_FLAGS_THIRD", "third" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("FooFlagsType"), values);
    }
    return etype;
}

