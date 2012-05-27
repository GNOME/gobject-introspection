#include "foo.h"
#include "girepository.h"

/* A hidden type not exposed publicly, similar to GUPNP's XML wrapper
   object */
typedef struct _FooHidden FooHidden;

int foo_init_argv (int argc, char **argv);
int foo_init_argv_address (int *argc, char ***argv);
void foo_private_function (FooObject *foo);
void foo_test_unsigned (unsigned int uint);
void foo_interface_do_foo (FooInterface *self, int x);
void foo_do_foo (FooInterface *self, int x);
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

void foo_interface_do_foo (FooInterface *self, int x)
{
  FOO_INTERFACE_GET_INTERFACE(self)->do_foo (self, x);
}

void foo_interface_static_method (int x)
{
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

enum {
  SUBIFACE_DESTROY_EVENT,
  SUBIFACE_LAST_SIGNAL
};

static void
foo_sub_interface_class_init (gpointer g_class, gpointer class_data);

static guint foo_subiface_signals[SUBIFACE_LAST_SIGNAL] = { 0 };

GType
foo_sub_interface_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      object_type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                   "FooSubInterface",
                                                   sizeof (FooSubInterfaceIface),
                                                   foo_sub_interface_class_init, 0, NULL, 0);

      g_type_interface_add_prerequisite (object_type, FOO_TYPE_INTERFACE);
    }

  return object_type;
}

static void
foo_sub_interface_class_init (gpointer g_class, gpointer class_data)
{
  foo_subiface_signals[SUBIFACE_DESTROY_EVENT] =
    g_signal_new ("destroy-event", FOO_TYPE_SUBINTERFACE,
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (FooSubInterfaceIface, destroy_event),
                  NULL, NULL,
                  gi_cclosure_marshal_generic,
                  G_TYPE_NONE,
                  0,
                  G_TYPE_NONE);
}

void
foo_sub_interface_do_bar (FooSubInterface *self)
{
  FOO_SUBINTERFACE_GET_INTERFACE(self)->do_bar (self);
}

void
foo_sub_interface_do_moo (FooSubInterface *self, int x, gpointer y)
{
  FOO_SUBINTERFACE_GET_INTERFACE(self)->do_moo (self, x, y);
}

/**
 * foo_sub_interface_do_baz:
 * @self:
 * @callback: (scope call):
 * @user_data:
 */
void
foo_sub_interface_do_baz (FooSubInterface *self, GCallback callback, gpointer user_data)
{
  FOO_SUBINTERFACE_GET_INTERFACE(self)->do_baz (self, callback, user_data);
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

FooObject *
foo_object_new (void)
{
  return g_object_new (FOO_TYPE_OBJECT, NULL);
}

GObject *
foo_object_new_as_super (void)
{
  return g_object_new (FOO_TYPE_OBJECT, NULL);
}

/**
 * foo_object_external_type:
 * @object: a #FooObject
 *
 * Returns: (transfer none): %NULL always
 */
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
foo_do_foo (FooInterface *self, int x)
{


}

void
foo_object_is_it_time_yet (FooObject *object, time_t time)
{
}

/**
 * foo_object_new_cookie: (skip)
 * @object:
 * @target:
 *
 * Not sure why this test is here...
 */
FooObjectCookie
foo_object_new_cookie (FooObject *object, const char *target)
{
  return NULL;
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

/**
 * foo_object_read:
 * @object: obj
 * @offset: offset
 * @length: length
 *
 * Read some stuff.
 *
 * Virtual: read_fn
 */
void
foo_object_read (FooObject *object, int offset, int length)
{

}

/**
 * foo_object_skipped_method: (skip)
 * @object: obj
 *
 * This is only useful from C.
 */
void
foo_object_skipped_method (FooObject *object)
{
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

/**
 * foo_object_get_default:
 *
 * This function is intended to match clutter_stage_get_default which
 * uses a C sugar return type.
 *
 * Return value: (type FooSubobject) (transfer none): The global #FooSubobject
 */
FooObject *
foo_object_get_default ()
{
  return NULL;
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

/**
 * foo_test_string_array:
 * @array: (array zero-terminated=1):
 */
void
foo_test_string_array (char **array)
{
}

/**
 * foo_test_string_array_with_g:
 * @array: (array zero-terminated=1):
 */
void
foo_test_string_array_with_g (gchar **array)
{
}

/**
 * foo_test_array:
 *
 * Returns: (element-type utf8) (transfer container):
 */
GArray *
foo_test_array (void)
{
  return NULL;
}

/**
 * foo_rectangle_new: (skip)
 *
 * This is a C convenience constructor; we have to (skip)
 * it because it's not a boxed type.
 */
FooRectangle *
foo_rectangle_new (int x, int y, int width, int height)
{
  FooRectangle *r = g_slice_new (FooRectangle);
  r->x = x;
  r->y = y;
  r->width = width;
  r->height = height;
  return r;
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

void
foo_some_variant (guint x, va_list args)
{
}

GType foo_tile_handler_get_type(void);

/* This setup of a totally hidden parent class matches
 * http://bugzilla.gnome.org/show_bug.cgi?id=561360
 */
#define FOO_TYPE_TILE_HANDLER        (foo_tile_handler_get_type ())
#define FOO_TILE_HANDLER(object)     (G_TYPE_CHECK_INSTANCE_CAST ((object), FOO_TYPE_TILE_HANDLER, FooTileHandler))
#define FOO_IS_TILE_HANDLER(object)  (G_TYPE_CHECK_INSTANCE_TYPE ((object), FOO_TYPE_TILE_HANDLER))

struct _FooTileHandler
{
  FooObject parent_instance;
};


struct _FooTileHandlerClass
{
  FooObjectClass parent_class;
};

typedef struct _FooTileHandler          FooTileHandler;
typedef struct _FooTileHandlerClass     FooTileHandlerClass;

G_DEFINE_TYPE(FooTileHandler, foo_tile_handler, FOO_TYPE_OBJECT);

static void
foo_tile_handler_class_init (FooTileHandlerClass *klass)
{

}

static void
foo_tile_handler_init (FooTileHandler *object)
{

}

struct _FooBuffer
{
  FooTileHandler parent_instance;
};

struct _FooBufferClass
{
  FooTileHandlerClass parent_class;
};

G_DEFINE_TYPE(FooBuffer, foo_buffer, FOO_TYPE_TILE_HANDLER);

static void
foo_buffer_class_init (FooBufferClass *klass)
{

}

static void
foo_buffer_init (FooBuffer *object)
{

}

void
foo_buffer_some_method (FooBuffer *buffer)
{
}

struct _FooOtherObject
{
  GObject parent_instance;
};

struct _FooOtherObjectClass
{
  GObjectClass parent_class;
};

G_DEFINE_TYPE(FooOtherObject, foo_other_object, G_TYPE_OBJECT);

static void
foo_other_object_class_init (FooOtherObjectClass *klass)
{

}

static void
foo_other_object_init (FooOtherObject *object)
{

}


#define FOO_DEFINE_SHOULD_NOT_BE_EXPOSED "should not be exposed"

/**
 * foo_skip_me: (skip)
 * @fs: a #FooSkippable
 *
 * Does something that's only interesting from C and should not be
 * exposed to language bindings.
 */
void
foo_skip_me (FooSkippable fs)
{
}

/**
 * FooForeignStruct: (foreign)
 *
 */

FooForeignStruct*
foo_foreign_struct_new (void)
{
  return g_slice_new0 (FooForeignStruct);
}

FooForeignStruct*
foo_foreign_struct_copy (FooForeignStruct *original)
{
    FooForeignStruct *copy;
    copy = foo_foreign_struct_new ();
    copy->foo = original->foo;
    return copy;
}

/**
 * foo_test_varargs_callback: (skip)
 *
 */
void
foo_test_varargs_callback (gint i, FooVarargsCallback callback)
{
}

/**
 * foo_test_varargs_callback2: (skip)
 *
 */
void
foo_test_varargs_callback2 (FooVarargsCallback callback)
{
}

/**
 * foo_test_varargs_callback3: (skip)
 *
 */
void
foo_test_varargs_callback3 (FooVarargsCallback callback,
			    FooVarargsCallback callback2)
{
}

/**
 * foo_object_append_new_stack_layer:
 *
 * This shouldn't be scanned as a constructor.
 *
 * Returns: (transfer none):
 */
FooOtherObject *
foo_object_append_new_stack_layer (FooObject *obj, int x)
{
  return NULL;
}

/**
 * foo_not_a_constructor_new:
 *
 * This should be scanned as a top-level function, and shouldn't cause
 * a "Can't find matching type for constructor" warning.
 *
 * Returns: (transfer none):
 */
FooObject *
foo_not_a_constructor_new (void)
{
  return NULL;
}
