#define FOO_SUCCESS_INT 0x1138

#include "foo.h"

/* A hidden type not exposed publicly, similar to GUPNP's XML wrapper
   object */
typedef struct _FooHidden FooHidden;

int foo_init_argv (int argc, char **argv);
int foo_init_argv_address (int *argc, char ***argv);
void foo_private_function (FooObject *foo);
void foo_test_unsigned (unsigned int uint);
void foo_interface_do_foo (FooInterface *self);
void foo_do_foo (FooInterface *self);
int foo_enum_method (FooEnumType foo_enum);
FooHidden * foo_hidden_copy (const FooHidden *boxed);
void foo_hidden_free (FooHidden *boxed);
GType foo_hidden_get_type (void);
FooBoxed *foo_boxed_copy (const FooBoxed *boxed);
void foo_boxed_free (FooBoxed *boxed);
void foo_dbus_data_free (FooDBusData *boxed);
FooDBusData *foo_dbus_data_copy (const FooDBusData *boxed);

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
  PROP_STRING,
  PROP_HIDDEN
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

GType
foo_sub_interface_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      object_type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                   "FooSubInterface",
                                                   sizeof (FooSubInterfaceIface),
                                                   NULL, 0, NULL, 0);

      g_type_interface_add_prerequisite (object_type, FOO_TYPE_INTERFACE);
    }

  return object_type;
}

void foo_sub_interface_do_bar (FooSubInterface *self)
{
  FOO_SUBINTERFACE_GET_INTERFACE(self)->do_bar (self);
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
  switch (prop_id)
    {
    case PROP_STRING:
      break;
    case PROP_HIDDEN:
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
  switch (prop_id)
    {
    case PROP_STRING:
      break;
    case PROP_HIDDEN:
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
  g_object_class_install_property (gobject_class,
                                   PROP_HIDDEN,
                                   g_param_spec_boxed ("hidden",
						       "hidden property",
						       "should not be exposed",
						       foo_hidden_get_type (),
						       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
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
  return NULL;
}

void                  
foo_object_take_all (FooObject *object, int x, ...)
{

}

void
foo_do_foo (FooInterface *self)
{


}

void
foo_object_is_it_time_yet (FooObject *object, time_t time)
{
}

const char *
foo_object_get_name (FooObject *object)
{
  return "foo";
}

char *
foo_object_dup_name (FooObject *object)
{
  return g_strdup ("foo");
}

G_DEFINE_ABSTRACT_TYPE (FooSubobject, foo_subobject, FOO_TYPE_OBJECT);

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

/* FooDbus */
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
foo_dbus_data_free (FooDBusData *boxed)
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

GType
foo_brect_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FooBRect",
					     (GBoxedCopyFunc) g_memdup, /* Won't work */
					     (GBoxedFreeFunc) g_free);
  return our_type;
}

GType
foo_bunion_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FooBUnion",
					     (GBoxedCopyFunc) g_memdup, /* Won't work */
					     (GBoxedFreeFunc) g_free);
  return our_type;
}

void foo_test_unsigned (unsigned int uint)
{
}

void
foo_test_string_array (char **array)
{
}

/**
 * foo_rectangle_add:
 * @r1: (inout): add to this rect
 * @r2: source rectangle
 */
void
foo_rectangle_add(FooRectangle *r1, const FooRectangle *r2)
{

}

/* FooHidden */

struct _FooHidden
{
  char *frob;
};

FooHidden *
foo_hidden_copy (const FooHidden *boxed)
{
  return (FooHidden *)g_memdup (boxed, sizeof (FooHidden));
}

void
foo_hidden_free (FooHidden *boxed)
{
  g_slice_free (FooHidden, boxed);
}


GType
foo_hidden_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FooHidden",
					     (GBoxedCopyFunc) foo_hidden_copy,
					     (GBoxedFreeFunc) foo_hidden_free);
  return our_type;
}

GType
foo_error_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { FOO_ERROR_GOOD, "FOO_ERROR_GOOD", "good" },
            { FOO_ERROR_BAD, "FOO_ERROR_BAD", "bad" },
            { FOO_ERROR_UGLY, "FOO_ERROR_UGLY", "ugly" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("FooError"), values);
    }
    return etype;
}

GQuark
foo_error_quark (void)
{
  return g_quark_from_static_string ("foo-error-quark");
}

