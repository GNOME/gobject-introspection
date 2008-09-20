#define FOO_SUCCESS_INT 0x1138

#include "foo.h"

static void foo_do_foo (FooInterface *self);

typedef struct
{
  int i;
} PrivateStruct;

void foo_private_function (FooObject *foo)
{

}

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

void foo_interface_do_foo (FooInterface *self)
{
  FOO_INTERFACE_GET_INTERFACE(self)->do_foo (self);
}

enum {
  PROP_0,
  PROP_STRING
};

enum {
  SIGNAL,
  LAST_SIGNAL
};

static guint foo_object_signals[LAST_SIGNAL] = { 0 };

static void
foo_foo_interface_init (gpointer         g_iface,
			gpointer         iface_data)
{
  FooInterfaceIface *iface = (FooInterfaceIface *)g_iface;
  iface->do_foo = foo_do_foo;
}

G_DEFINE_TYPE_EXTENDED (FooObject, foo_object, G_TYPE_OBJECT,
			0, G_IMPLEMENT_INTERFACE (FOO_TYPE_INTERFACE,
						  foo_foo_interface_init));

static void
foo_object_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FooObject *foo = FOO_OBJECT (object);

  switch (prop_id)
    {
    case PROP_STRING:
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
foo_object_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FooObject *foo = FOO_OBJECT (object);

  switch (prop_id)
    {
    case PROP_STRING:
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
foo_object_class_init (FooObjectClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = foo_object_set_property;
  gobject_class->get_property = foo_object_get_property;

  g_object_class_install_property (gobject_class,
                                   PROP_STRING,
                                   g_param_spec_string ("string",
                                                        "String nick",
                                                        "The String Property Blurb",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
  foo_object_signals[SIGNAL] =
    g_signal_new ("signal",
		  G_OBJECT_CLASS_TYPE (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  0,
		  NULL, NULL,
		  (GSignalCMarshaller)g_cclosure_marshal_STRING__OBJECT_POINTER,
		  G_TYPE_STRING, 2, G_TYPE_OBJECT, G_TYPE_POINTER);

}

static void
foo_object_init (FooObject *object)
{

}

UtilityObject*
foo_object_external_type (FooObject *object)
{

}

void
foo_do_foo (FooInterface *self)
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
foo_enum_type_get_type (void)
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

int foo_enum_method (FooEnumType foo_enum)
{
  return 0;
}


GType
foo_flags_type_get_type (void)
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

struct _FooBoxed
{
  int private;
};


FooBoxed *
foo_boxed_copy (const FooBoxed *boxed)
{
  return (FooBoxed *)g_memdup (boxed, sizeof (FooBoxed));
}

void
foo_boxed_free (FooBoxed *boxed)
{
  g_slice_free (FooBoxed, boxed);
}


GType
foo_boxed_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FooBoxed",
					     (GBoxedCopyFunc) foo_boxed_copy,
					     (GBoxedFreeFunc) foo_boxed_free);
  return our_type;
}

FooBoxed *
foo_boxed_new (void)
{
  return g_slice_new0 (FooBoxed);
}

void
foo_boxed_method (FooBoxed *boxed)
{

}

struct _FooDBusData
{
  double private;
};

FooDBusData *
foo_dbus_data_copy (const FooDBusData *boxed)
{
  return (FooDBusData *)g_memdup (boxed, sizeof (FooDBusData));
}

void
foo_dbus_data_free (FooBoxed *boxed)
{
  g_slice_free (FooDBusData, boxed);
}


GType
foo_dbus_data_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FooDBusData",
					     (GBoxedCopyFunc) foo_dbus_data_copy,
					     (GBoxedFreeFunc) foo_dbus_data_free);
  return our_type;
}
