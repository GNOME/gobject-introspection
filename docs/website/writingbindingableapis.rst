========================
Writing Bindingable APIs
========================

Things to avoid
---------------

Structures with custom memory management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Avoid creating C structures with custom _ref/_unref/_free type functions. You
have two general choices; a `boxed
<https://developer.gnome.org/gobject/unstable/gobject-Boxed-Types.html>`__
type (this is a value type, it is copied), or a full `GObject
<https://developer.gnome.org/gobject/unstable/gobject-The-Base-Object-Type.html>`__.
GObject is not significantly more typing, and using it gives infrastructure
like toggle references that are critical for garbage-collected language
bindings.

Example to avoid:

.. code-block:: c

    struct _GstMiniObject {
      GTypeInstance instance;
      /*< public >*/ /* with COW */
      gint refcount;
      guint flags;


Functionality only accessible through a C macro
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The scanner does not support C macros as API. Solution - add a function
accessor rather than a macro. This also has the side effect of making
debugging in C code easier.

Example:

.. code-block:: c

    #define GTK_WIDGET_FLAGS(wid)             (GTK_OBJECT_FLAGS (wid))

    GtkWidgetFlags gtk_widget_get_flags (GtkWidget *widget); /* Actually, see http://bugzilla.gnome.org/show_bug.cgi?id=69872 */


Direct C structure access for objects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Having GObjects also have fields can be difficult to bind. Create accessor
functions.

Example:

.. code-block:: c

    struct _SoupMessage {
            GObject parent;

            /*< public >*/
            const char         *method;

            guint               status_code;
    ...
    }

    const char * soup_message_get_method (SoupMessage *message);  /*  Or use a GObject property */


va_list
~~~~~~~

Using varargs can be convenient for C, but they are difficult to bind.
Solution: Keep the C function for the convenience of C programmers, but add an
another function which takes an array (either zero terminated or with a length
parameter).

**Good** example: 

.. code-block:: c

    GtkListStore *gtk_list_store_new              (gint          n_columns,
                                                   ...);
    GtkListStore *gtk_list_store_newv             (gint          n_columns,
                                                   GType        *types);


Multiple out parameters
~~~~~~~~~~~~~~~~~~~~~~~

Multiple out parameters are supported by introspection, but not all languages
have an obvious mapping for multiple out values. A boxed structure could serve
as an alternative.

Example to think about (here, there could be a boxed ``struct GtkCoordinate {
gint x; gint y; }`` structure).

.. code-block:: c

    void         gtk_widget_get_pointer     (GtkWidget      *widget,
                                             gint           *x,
                                             gint           *y);


Arrays
~~~~~~

For reference types, zero-terminated arrays are the easiest to work with.
Arrays of primitive type such as "int" will require length metadata.


Callbacks
~~~~~~~~~

Callbacks are hard to support for introspection bindings because of their
complex life-cycle. Try to avoid having more than one callback in the same
function, and consider using GClosure when you need more.


Using a different name for error domain quarks from the enum name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Error domain quarks should always be named in the form
<namespace>_<module>_error_quark() for an error enum called
<Namespace><Module>Error. Example to avoid:

.. code-block:: c

    typedef enum FooBarError {
      FOO_BAR_ERROR_MOO,
      FOO_BAR_ERROR_BLEAT
    };

    GQuark foo_bar_errors_quark();


Custom code in constructors
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Creating an object via ``foo_bar_new()`` shouldn't execute any code
differently than creating the same object via ``g_object_new()``, since many
bindings (and also GtkBuilder/Glade) create objects using ``g_object_new()``.
That is, don't do this:

.. code-block:: c

    FooBar *
    foo_bar_new (void)
    {
        FooBar *retval = FOO_BAR (g_object_new (FOO_TYPE_BAR, NULL));
        retval->priv->some_variable = 5;  /* Don't do this! */
        return retval;
    }

Instead, put initialization code in the ``foo_bar_init()`` function or the
``foo_bar_constructed()`` virtual function.
