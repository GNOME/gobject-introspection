/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/

/**
 * GBinding:flags:
 *
 * Flags to be used to control the #GBinding
 *
 * Since: 2.26
 */


/**
 * GBinding:source:
 *
 * The #GObject that should be used as the source of the binding
 *
 * Since: 2.26
 */


/**
 * GBinding:source-property:
 *
 * The name of the property of #GBinding:source that should be used
 * as the source of the binding
 *
 * Since: 2.26
 */


/**
 * GBinding:target:
 *
 * The #GObject that should be used as the target of the binding
 *
 * Since: 2.26
 */


/**
 * GBinding:target-property:
 *
 * The name of the property of #GBinding:target that should be used
 * as the target of the binding
 *
 * Since: 2.26
 */


/**
 * GObject::notify:
 * @gobject: the object which received the signal.
 * @pspec: the #GParamSpec of the property which changed.
 *
 * The notify signal is emitted on an object when one of its
 * properties has been changed. Note that getting this signal
 * doesn't guarantee that the value of the property has actually
 * changed, it may also be emitted when the setter for the property
 * is called to reinstate the previous value.
 *
 * This signal is typically used to obtain change notification for a
 * single property, by specifying the property name as a detail in the
 * g_signal_connect() call, like this:
 * |[
 * g_signal_connect (text_view->buffer, "notify::paste-target-list",
 *                   G_CALLBACK (gtk_text_view_target_list_notify),
 *                   text_view)
 * ]|
 * It is important to note that you must use
 * <link linkend="canonical-parameter-name">canonical</link> parameter names as
 * detail strings for the notify signal.
 */


/**
 * GParamSpecPool:
 *
 * A #GParamSpecPool maintains a collection of #GParamSpec<!-- -->s which can be
 * quickly accessed by owner and name. The implementation of the #GObject property
 * system uses such a pool to store the #GParamSpecs of the properties all object
 * types.
 */


/**
 * GWeakRef:
 *
 * A structure containing a weak reference to a #GObject.  It can either
 * be empty (i.e. point to %NULL), or point to an object for as long as
 * at least one "strong" reference to that object exists. Before the
 * object's #GObjectClass.dispose method is called, every #GWeakRef
 * associated with becomes empty (i.e. points to %NULL).
 *
 * Like #GValue, #GWeakRef can be statically allocated, stack- or
 * heap-allocated, or embedded in larger structures.
 *
 * Unlike g_object_weak_ref() and g_object_add_weak_pointer(), this weak
 * reference is thread-safe: converting a weak pointer to a reference is
 * atomic with respect to invalidation of weak pointers to destroyed
 * objects.
 *
 * If the object's #GObjectClass.dispose method results in additional
 * references to the object being held, any #GWeakRef<!-- -->s taken
 * before it was disposed will continue to point to %NULL.  If
 * #GWeakRef<!-- -->s are taken after the object is disposed and
 * re-referenced, they will continue to point to it until its refcount
 * goes back to zero, at which point they too will be invalidated.
 */


/**
 * SECTION:enumerations_flags
 * @short_description: Enumeration and flags types
 * @title: Enumeration and Flag Types
 * @see_also: #GParamSpecEnum, #GParamSpecFlags, g_param_spec_enum(),
 * g_param_spec_flags()
 *
 * The GLib type system provides fundamental types for enumeration and
 * flags types. (Flags types are like enumerations, but allow their
 * values to be combined by bitwise or). A registered enumeration or
 * flags type associates a name and a nickname with each allowed
 * value, and the methods g_enum_get_value_by_name(),
 * g_enum_get_value_by_nick(), g_flags_get_value_by_name() and
 * g_flags_get_value_by_nick() can look up values by their name or
 * nickname.  When an enumeration or flags type is registered with the
 * GLib type system, it can be used as value type for object
 * properties, using g_param_spec_enum() or g_param_spec_flags().
 *
 * GObject ships with a utility called <link
 * linkend="glib-mkenums">glib-mkenums</link> that can construct
 * suitable type registration functions from C enumeration
 * definitions.
 */


/**
 * SECTION:gbinding
 * @Title: GBinding
 * @Short_Description: Bind two object properties
 *
 * #GBinding is the representation of a binding between a property on a
 * #GObject instance (or source) and another property on another #GObject
 * instance (or target). Whenever the source property changes, the same
 * value is applied to the target property; for instance, the following
 * binding:
 *
 * |[
 *   g_object_bind_property (object1, "property-a",
 *                           object2, "property-b",
 *                           G_BINDING_DEFAULT);
 * ]|
 *
 * will cause <emphasis>object2:property-b</emphasis> to be updated every
 * time g_object_set() or the specific accessor changes the value of
 * <emphasis>object1:property-a</emphasis>.
 *
 * It is possible to create a bidirectional binding between two properties
 * of two #GObject instances, so that if either property changes, the
 * other is updated as well, for instance:
 *
 * |[
 *   g_object_bind_property (object1, "property-a",
 *                           object2, "property-b",
 *                           G_BINDING_BIDIRECTIONAL);
 * ]|
 *
 * will keep the two properties in sync.
 *
 * It is also possible to set a custom transformation function (in both
 * directions, in case of a bidirectional binding) to apply a custom
 * transformation from the source value to the target value before
 * applying it; for instance, the following binding:
 *
 * |[
 *   g_object_bind_property_full (adjustment1, "value",
 *                                adjustment2, "value",
 *                                G_BINDING_BIDIRECTIONAL,
 *                                celsius_to_fahrenheit,
 *                                fahrenheit_to_celsius,
 *                                NULL, NULL);
 * ]|
 *
 * will keep the <emphasis>value</emphasis> property of the two adjustments
 * in sync; the <function>celsius_to_fahrenheit</function> function will be
 * called whenever the <emphasis>adjustment1:value</emphasis> property changes
 * and will transform the current value of the property before applying it
 * to the <emphasis>adjustment2:value</emphasis> property; vice versa, the
 * <function>fahrenheit_to_celsius</function> function will be called whenever
 * the <emphasis>adjustment2:value</emphasis> property changes, and will
 * transform the current value of the property before applying it to the
 * <emphasis>adjustment1:value</emphasis>.
 *
 * Note that #GBinding does not resolve cycles by itself; a cycle like
 *
 * |[
 *   object1:propertyA -> object2:propertyB
 *   object2:propertyB -> object3:propertyC
 *   object3:propertyC -> object1:propertyA
 * ]|
 *
 * might lead to an infinite loop. The loop, in this particular case,
 * can be avoided if the objects emit the #GObject::notify signal only
 * if the value has effectively been changed. A binding is implemented
 * using the #GObject::notify signal, so it is susceptible to all the
 * various ways of blocking a signal emission, like g_signal_stop_emission()
 * or g_signal_handler_block().
 *
 * A binding will be severed, and the resources it allocates freed, whenever
 * either one of the #GObject instances it refers to are finalized, or when
 * the #GBinding instance loses its last reference.
 *
 * <note><para>Bindings for languages with garbage collection can use
 * g_binding_unbind() to explicitly release a binding between the source
 * and target properties, instead of relying on the last reference on the
 * binding, source, and target instances to drop.</para></note>
 *
 * #GBinding is available since GObject 2.26
 */


/**
 * SECTION:gboxed
 * @short_description: A mechanism to wrap opaque C structures registered
 *     by the type system
 * @see_also: #GParamSpecBoxed, g_param_spec_boxed()
 * @title: Boxed Types
 *
 * GBoxed is a generic wrapper mechanism for arbitrary C structures. The only
 * thing the type system needs to know about the structures is how to copy and
 * free them, beyond that they are treated as opaque chunks of memory.
 *
 * Boxed types are useful for simple value-holder structures like rectangles or
 * points. They can also be used for wrapping structures defined in non-GObject
 * based libraries.
 */


/**
 * SECTION:gclosure
 * @short_description: Functions as first-class objects
 * @title: Closures
 *
 * A #GClosure represents a callback supplied by the programmer. It
 * will generally comprise a function of some kind and a marshaller
 * used to call it. It is the reponsibility of the marshaller to
 * convert the arguments for the invocation from #GValue<!-- -->s into
 * a suitable form, perform the callback on the converted arguments,
 * and transform the return value back into a #GValue.
 *
 * In the case of C programs, a closure usually just holds a pointer
 * to a function and maybe a data argument, and the marshaller
 * converts between #GValue<!-- --> and native C types. The GObject
 * library provides the #GCClosure type for this purpose. Bindings for
 * other languages need marshallers which convert between #GValue<!--
 * -->s and suitable representations in the runtime of the language in
 * order to use functions written in that languages as callbacks.
 *
 * Within GObject, closures play an important role in the
 * implementation of signals. When a signal is registered, the
 * @c_marshaller argument to g_signal_new() specifies the default C
 * marshaller for any closure which is connected to this
 * signal. GObject provides a number of C marshallers for this
 * purpose, see the g_cclosure_marshal_*() functions. Additional C
 * marshallers can be generated with the <link
 * linkend="glib-genmarshal">glib-genmarshal</link> utility.  Closures
 * can be explicitly connected to signals with
 * g_signal_connect_closure(), but it usually more convenient to let
 * GObject create a closure automatically by using one of the
 * g_signal_connect_*() functions which take a callback function/user
 * data pair.
 *
 * Using closures has a number of important advantages over a simple
 * callback function/data pointer combination:
 * <itemizedlist>
 * <listitem><para>
 * Closures allow the callee to get the types of the callback parameters,
 * which means that language bindings don't have to write individual glue
 * for each callback type.
 * </para></listitem>
 * <listitem><para>
 * The reference counting of #GClosure makes it easy to handle reentrancy
 * right; if a callback is removed while it is being invoked, the closure
 * and its parameters won't be freed until the invocation finishes.
 * </para></listitem>
 * <listitem><para>
 * g_closure_invalidate() and invalidation notifiers allow callbacks to be
 * automatically removed when the objects they point to go away.
 * </para></listitem>
 * </itemizedlist>
 */


/**
 * SECTION:generic_values
 * @short_description: A polymorphic type that can hold values of any
 *     other type
 * @see_also: The fundamental types which all support #GValue
 *     operations and thus can be used as a type initializer for
 *     g_value_init() are defined by a separate interface.  See the <link
 *     linkend="gobject-Standard-Parameter-and-Value-Types">Standard
 *     Values API</link> for details.
 * @title: Generic values
 *
 * The #GValue structure is basically a variable container that consists
 * of a type identifier and a specific value of that type.
 * The type identifier within a #GValue structure always determines the
 * type of the associated value.
 * To create a undefined #GValue structure, simply create a zero-filled
 * #GValue structure. To initialize the #GValue, use the g_value_init()
 * function. A #GValue cannot be used until it is initialized.
 * The basic type operations (such as freeing and copying) are determined
 * by the #GTypeValueTable associated with the type ID stored in the #GValue.
 * Other #GValue operations (such as converting values between types) are
 * provided by this interface.
 *
 * The code in the example program below demonstrates #GValue's
 * features.
 *
 * |[
 * #include &lt;glib-object.h&gt;
 *
 * static void
 * int2string (const GValue *src_value,
 *             GValue       *dest_value)
 * {
 *   if (g_value_get_int (src_value) == 42)
 *     g_value_set_static_string (dest_value, "An important number");
 *   else
 *     g_value_set_static_string (dest_value, "What's that?");
 * }
 *
 * int
 * main (int   argc,
 *       char *argv[])
 * {
 *   /&ast; GValues must be initialized &ast;/
 *   GValue a = G_VALUE_INIT;
 *   GValue b = G_VALUE_INIT;
 *   const gchar *message;
 *
 *   /&ast; The GValue starts empty &ast;/
 *   g_assert (!G_VALUE_HOLDS_STRING (&amp;a));
 *
 *   /&ast; Put a string in it &ast;/
 *   g_value_init (&amp;a, G_TYPE_STRING);
 *   g_assert (G_VALUE_HOLDS_STRING (&amp;a));
 *   g_value_set_static_string (&amp;a, "Hello, world!");
 *   g_printf ("%s\n", g_value_get_string (&amp;a));
 *
 *   /&ast; Reset it to its pristine state &ast;/
 *   g_value_unset (&amp;a);
 *
 *   /&ast; It can then be reused for another type &ast;/
 *   g_value_init (&amp;a, G_TYPE_INT);
 *   g_value_set_int (&amp;a, 42);
 *
 *   /&ast; Attempt to transform it into a GValue of type STRING &ast;/
 *   g_value_init (&amp;b, G_TYPE_STRING);
 *
 *   /&ast; An INT is transformable to a STRING &ast;/
 *   g_assert (g_value_type_transformable (G_TYPE_INT, G_TYPE_STRING));
 *
 *   g_value_transform (&amp;a, &amp;b);
 *   g_printf ("%s\n", g_value_get_string (&amp;b));
 *
 *   /&ast; Attempt to transform it again using a custom transform function &ast;/
 *   g_value_register_transform_func (G_TYPE_INT, G_TYPE_STRING, int2string);
 *   g_value_transform (&amp;a, &amp;b);
 *   g_printf ("%s\n", g_value_get_string (&amp;b));
 *   return 0;
 * }
 * ]|
 */


/**
 * SECTION:gparamspec
 * @short_description: Metadata for parameter specifications
 * @see_also: g_object_class_install_property(), g_object_set(),
 *     g_object_get(), g_object_set_property(), g_object_get_property(),
 *     g_value_register_transform_func()
 * @title: GParamSpec
 *
 * #GParamSpec is an object structure that encapsulates the metadata
 * required to specify parameters, such as e.g. #GObject properties.
 *
 * <para id="canonical-parameter-name">
 * Parameter names need to start with a letter (a-z or A-Z). Subsequent
 * characters can be letters, numbers or a '-'.
 * All other characters are replaced by a '-' during construction.
 * The result of this replacement is called the canonical name of the
 * parameter.
 * </para>
 */


/**
 * SECTION:gtype
 * @short_description: The GLib Runtime type identification and
 *     management system
 * @title: Type Information
 *
 * The GType API is the foundation of the GObject system.  It provides the
 * facilities for registering and managing all fundamental data types,
 * user-defined object and interface types.
 *
 * For type creation and registration purposes, all types fall into one of
 * two categories: static or dynamic.  Static types are never loaded or
 * unloaded at run-time as dynamic types may be.  Static types are created
 * with g_type_register_static() that gets type specific information passed
 * in via a #GTypeInfo structure.
 * Dynamic types are created with g_type_register_dynamic() which takes a
 * #GTypePlugin structure instead. The remaining type information (the
 * #GTypeInfo structure) is retrieved during runtime through #GTypePlugin
 * and the g_type_plugin_*() API.
 * These registration functions are usually called only once from a
 * function whose only purpose is to return the type identifier for a
 * specific class.  Once the type (or class or interface) is registered,
 * it may be instantiated, inherited, or implemented depending on exactly
 * what sort of type it is.
 * There is also a third registration function for registering fundamental
 * types called g_type_register_fundamental() which requires both a #GTypeInfo
 * structure and a #GTypeFundamentalInfo structure but it is seldom used
 * since most fundamental types are predefined rather than user-defined.
 *
 * Type instance and class structs are limited to a total of 64 KiB,
 * including all parent types. Similarly, type instances' private data
 * (as created by g_type_class_add_private()) are limited to a total of
 * 64 KiB. If a type instance needs a large static buffer, allocate it
 * separately (typically by using #GArray or #GPtrArray) and put a pointer
 * to the buffer in the structure.
 *
 * A final word about type names.
 * Such an identifier needs to be at least three characters long. There is no
 * upper length limit. The first character needs to be a letter (a-z or A-Z)
 * or an underscore '_'. Subsequent characters can be letters, numbers or
 * any of '-_+'.
 */


/**
 * SECTION:gtypemodule
 * @short_description: Type loading modules
 * @see_also: <variablelist>
 * <varlistentry>
 * <term>#GTypePlugin</term>
 * <listitem><para>The abstract type loader interface.</para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>#GModule</term>
 * <listitem><para>Portable mechanism for dynamically loaded modules.</para></listitem>
 * </varlistentry>
 * </variablelist>
 * @title: GTypeModule
 *
 * #GTypeModule provides a simple implementation of the #GTypePlugin
 * interface. The model of #GTypeModule is a dynamically loaded module
 * which implements some number of types and interface
 * implementations. When the module is loaded, it registers its types
 * and interfaces using g_type_module_register_type() and
 * g_type_module_add_interface().  As long as any instances of these
 * types and interface implementations are in use, the module is kept
 * loaded. When the types and interfaces are gone, the module may be
 * unloaded. If the types and interfaces become used again, the module
 * will be reloaded. Note that the last unref cannot happen in module
 * code, since that would lead to the caller's code being unloaded before
 * g_object_unref() returns to it.
 *
 * Keeping track of whether the module should be loaded or not is done by
 * using a use count - it starts at zero, and whenever it is greater than
 * zero, the module is loaded. The use count is maintained internally by
 * the type system, but also can be explicitly controlled by
 * g_type_module_use() and g_type_module_unuse(). Typically, when loading
 * a module for the first type, g_type_module_use() will be used to load
 * it so that it can initialize its types. At some later point, when the
 * module no longer needs to be loaded except for the type
 * implementations it contains, g_type_module_unuse() is called.
 *
 * #GTypeModule does not actually provide any implementation of module
 * loading and unloading. To create a particular module type you must
 * derive from #GTypeModule and implement the load and unload functions
 * in #GTypeModuleClass.
 */


/**
 * SECTION:gtypeplugin
 * @short_description: An interface for dynamically loadable types
 * @see_also: #GTypeModule and g_type_register_dynamic().
 * @title: GTypePlugin
 *
 * The GObject type system supports dynamic loading of types. The
 * #GTypePlugin interface is used to handle the lifecycle of
 * dynamically loaded types.  It goes as follows:
 *
 * <orderedlist>
 * <listitem><para>
 *   The type is initially introduced (usually upon loading the module
 *   the first time, or by your main application that knows what modules
 *   introduces what types), like this:
 *   |[
 *   new_type_id = g_type_register_dynamic (parent_type_id,
 *                                                 "TypeName",
 *                                                 new_type_plugin,
 *                                                 type_flags);
 *   ]|
 *   where <literal>new_type_plugin</literal> is an implementation of the
 *   #GTypePlugin interface.
 * </para></listitem>
 * <listitem><para>
 *    The type's implementation is referenced, e.g. through
 *    g_type_class_ref() or through g_type_create_instance() (this is
 *    being called by g_object_new()) or through one of the above done on
 *    a type derived from <literal>new_type_id</literal>.
 * </para></listitem>
 * <listitem><para>
 *    This causes the type system to load the type's implementation by calling
 *    g_type_plugin_use() and g_type_plugin_complete_type_info() on
 *    <literal>new_type_plugin</literal>.
 * </para></listitem>
 * <listitem><para>
 *    At some point the type's implementation isn't required anymore, e.g. after
 *    g_type_class_unref() or g_type_free_instance() (called when the reference
 *    count of an instance drops to zero).
 * </para></listitem>
 * <listitem><para>
 *    This causes the type system to throw away the information retrieved from
 *    g_type_plugin_complete_type_info() and then it calls
 *    g_type_plugin_unuse() on <literal>new_type_plugin</literal>.
 * </para></listitem>
 * <listitem><para>
 *    Things may repeat from the second step.
 * </para></listitem>
 * </orderedlist>
 *
 * So basically, you need to implement a #GTypePlugin type that
 * carries a use_count, once use_count goes from zero to one, you need
 * to load the implementation to successfully handle the upcoming
 * g_type_plugin_complete_type_info() call. Later, maybe after
 * succeeding use/unuse calls, once use_count drops to zero, you can
 * unload the implementation again. The type system makes sure to call
 * g_type_plugin_use() and g_type_plugin_complete_type_info() again
 * when the type is needed again.
 *
 * #GTypeModule is an implementation of #GTypePlugin that already
 * implements most of this except for the actual module loading and
 * unloading. It even handles multiple registered types per module.
 */


/**
 * SECTION:objects
 * @title: GObject
 * @short_description: The base object type
 * @see_also: #GParamSpecObject, g_param_spec_object()
 *
 * GObject is the fundamental type providing the common attributes and
 * methods for all object types in GTK+, Pango and other libraries
 * based on GObject.  The GObject class provides methods for object
 * construction and destruction, property access methods, and signal
 * support.  Signals are described in detail in <xref
 * linkend="gobject-Signals"/>.
 *
 * <para id="floating-ref">
 * GInitiallyUnowned is derived from GObject. The only difference between
 * the two is that the initial reference of a GInitiallyUnowned is flagged
 * as a <firstterm>floating</firstterm> reference.
 * This means that it is not specifically claimed to be "owned" by
 * any code portion. The main motivation for providing floating references is
 * C convenience. In particular, it allows code to be written as:
 * |[
 * container = create_container ();
 * container_add_child (container, create_child());
 * ]|
 * If <function>container_add_child()</function> will g_object_ref_sink() the
 * passed in child, no reference of the newly created child is leaked.
 * Without floating references, <function>container_add_child()</function>
 * can only g_object_ref() the new child, so to implement this code without
 * reference leaks, it would have to be written as:
 * |[
 * Child *child;
 * container = create_container ();
 * child = create_child ();
 * container_add_child (container, child);
 * g_object_unref (child);
 * ]|
 * The floating reference can be converted into
 * an ordinary reference by calling g_object_ref_sink().
 * For already sunken objects (objects that don't have a floating reference
 * anymore), g_object_ref_sink() is equivalent to g_object_ref() and returns
 * a new reference.
 * Since floating references are useful almost exclusively for C convenience,
 * language bindings that provide automated reference and memory ownership
 * maintenance (such as smart pointers or garbage collection) should not
 * expose floating references in their API.
 * </para>
 *
 * Some object implementations may need to save an objects floating state
 * across certain code portions (an example is #GtkMenu), to achieve this,
 * the following sequence can be used:
 *
 * |[
 * /&ast; save floating state &ast;/
 * gboolean was_floating = g_object_is_floating (object);
 * g_object_ref_sink (object);
 * /&ast; protected code portion &ast;/
 * ...;
 * /&ast; restore floating state &ast;/
 * if (was_floating)
 *   g_object_force_floating (object);
 * else
 *   g_object_unref (object); /&ast; release previously acquired reference &ast;/
 * ]|
 */


/**
 * SECTION:param_value_types
 * @short_description: Standard Parameter and Value Types
 * @see_also: #GParamSpec, #GValue, g_object_class_install_property().
 * @title: Parameters and Values
 *
 * #GValue provides an abstract container structure which can be
 * copied, transformed and compared while holding a value of any
 * (derived) type, which is registered as a #GType with a
 * #GTypeValueTable in its #GTypeInfo structure.  Parameter
 * specifications for most value types can be created as #GParamSpec
 * derived instances, to implement e.g. #GObject properties which
 * operate on #GValue containers.
 *
 * Parameter names need to start with a letter (a-z or A-Z). Subsequent
 * characters can be letters, numbers or a '-'.
 * All other characters are replaced by a '-' during construction.
 */


/**
 * SECTION:signals
 * @short_description: A means for customization of object behaviour
 *     and a general purpose notification mechanism
 * @title: Signals
 *
 * The basic concept of the signal system is that of the
 * <emphasis>emission</emphasis> of a signal. Signals are introduced
 * per-type and are identified through strings.  Signals introduced
 * for a parent type are available in derived types as well, so
 * basically they are a per-type facility that is inherited.  A signal
 * emission mainly involves invocation of a certain set of callbacks
 * in precisely defined manner. There are two main categories of such
 * callbacks, per-object
 * <footnote><para>Although signals can deal with any kind of instantiatable
 * type, i'm referring to those types as "object types" in the following,
 * simply because that is the context most users will encounter signals in.
 * </para></footnote>
 * ones and user provided ones.
 * The per-object callbacks are most often referred to as "object method
 * handler" or "default (signal) handler", while user provided callbacks are
 * usually just called "signal handler".
 * The object method handler is provided at signal creation time (this most
 * frequently happens at the end of an object class' creation), while user
 * provided handlers are frequently connected and disconnected to/from a certain
 * signal on certain object instances.
 *
 * A signal emission consists of five stages, unless prematurely stopped:
 * <variablelist>
 * <varlistentry><term></term><listitem><para>
 * 	1 - Invocation of the object method handler for %G_SIGNAL_RUN_FIRST signals
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 	2 - Invocation of normal user-provided signal handlers (<emphasis>after</emphasis> flag %FALSE)
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 	3 - Invocation of the object method handler for %G_SIGNAL_RUN_LAST signals
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 	4 - Invocation of user provided signal handlers, connected with an <emphasis>after</emphasis> flag of %TRUE
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 	5 - Invocation of the object method handler for %G_SIGNAL_RUN_CLEANUP signals
 * </para></listitem></varlistentry>
 * </variablelist>
 * The user-provided signal handlers are called in the order they were
 * connected in.
 * All handlers may prematurely stop a signal emission, and any number of
 * handlers may be connected, disconnected, blocked or unblocked during
 * a signal emission.
 * There are certain criteria for skipping user handlers in stages 2 and 4
 * of a signal emission.
 * First, user handlers may be <emphasis>blocked</emphasis>, blocked handlers are omitted
 * during callback invocation, to return from the "blocked" state, a
 * handler has to get unblocked exactly the same amount of times
 * it has been blocked before.
 * Second, upon emission of a %G_SIGNAL_DETAILED signal, an additional
 * "detail" argument passed in to g_signal_emit() has to match the detail
 * argument of the signal handler currently subject to invocation.
 * Specification of no detail argument for signal handlers (omission of the
 * detail part of the signal specification upon connection) serves as a
 * wildcard and matches any detail argument passed in to emission.
 */


/**
 * SECTION:value_arrays
 * @short_description: A container structure to maintain an array of
 *     generic values
 * @see_also: #GValue, #GParamSpecValueArray, g_param_spec_value_array()
 * @title: Value arrays
 *
 * The prime purpose of a #GValueArray is for it to be used as an
 * object property that holds an array of values. A #GValueArray wraps
 * an array of #GValue elements in order for it to be used as a boxed
 * type through %G_TYPE_VALUE_ARRAY.
 *
 * #GValueArray is deprecated in favour of #GArray since GLib 2.32. It
 * is possible to create a #GArray that behaves like a #GValueArray by
 * using the size of #GValue as the element size, and by setting
 * g_value_unset() as the clear function using g_array_set_clear_func(),
 * for instance, the following code:
 *
 * |[
 *   GValueArray *array = g_value_array_new (10);
 * ]|
 *
 * can be replaced by:
 *
 * |[
 *   GArray *array = g_array_sized_new (FALSE, TRUE, sizeof (GValue), 10);
 *   g_array_set_clear_func (array, (GDestroyNotify) g_value_unset);
 * ]|
 */


/**
 * g_binding_get_flags:
 * @binding: a #GBinding
 *
 * Retrieves the flags passed when constructing the #GBinding
 *
 * Returns: the #GBindingFlags used by the #GBinding
 * Since: 2.26
 */


/**
 * g_binding_get_source:
 * @binding: a #GBinding
 *
 * Retrieves the #GObject instance used as the source of the binding
 *
 * Returns: (transfer none): the source #GObject
 * Since: 2.26
 */


/**
 * g_binding_get_source_property:
 * @binding: a #GBinding
 *
 * Retrieves the name of the property of #GBinding:source used as the source
 * of the binding
 *
 * Returns: the name of the source property
 * Since: 2.26
 */


/**
 * g_binding_get_target:
 * @binding: a #GBinding
 *
 * Retrieves the #GObject instance used as the target of the binding
 *
 * Returns: (transfer none): the target #GObject
 * Since: 2.26
 */


/**
 * g_binding_get_target_property:
 * @binding: a #GBinding
 *
 * Retrieves the name of the property of #GBinding:target used as the target
 * of the binding
 *
 * Returns: the name of the target property
 * Since: 2.26
 */


/**
 * g_binding_unbind:
 * @binding: a #GBinding
 *
 * Explicitly releases the binding between the source and the target
 * property expressed by @binding.
 *
 * <note>This function will release the reference that is being held on
 * the @binding instance; if you want to hold on to the #GBinding instance
 * after calling g_binding_unbind(), you will need to hold a reference
 * to it.</note>
 *
 * Since: 2.38
 */


/**
 * g_boxed_copy:
 * @boxed_type: The type of @src_boxed.
 * @src_boxed: The boxed structure to be copied.
 *
 * Provide a copy of a boxed structure @src_boxed which is of type @boxed_type.
 *
 * Returns: The newly created copy of the boxed structure.
 */


/**
 * g_boxed_free:
 * @boxed_type: The type of @boxed.
 * @boxed: The boxed structure to be freed.
 *
 * Free the boxed structure @boxed which is of type @boxed_type.
 */


/**
 * g_boxed_type_register_static:
 * @name: Name of the new boxed type.
 * @boxed_copy: Boxed structure copy function.
 * @boxed_free: Boxed structure free function.
 *
 * This function creates a new %G_TYPE_BOXED derived type id for a new
 * boxed type with name @name. Boxed type handling functions have to be
 * provided to copy and free opaque boxed structures of this type.
 *
 * Returns: New %G_TYPE_BOXED derived type id for @name.
 */


/**
 * g_cclosure_marshal_BOOLEAN__FLAGS:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: a #GValue which can store the returned #gboolean
 * @n_param_values: 2
 * @param_values: a #GValue array holding instance and arg1
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>gboolean (*callback) (gpointer instance, gint arg1, gpointer user_data)</literal> where the #gint parameter
 * denotes a flags type.
 */


/**
 * g_cclosure_marshal_BOOLEAN__OBJECT_BOXED_BOXED:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: a #GValue, which can store the returned string
 * @n_param_values: 3
 * @param_values: a #GValue array holding instance, arg1 and arg2
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>gboolean (*callback) (gpointer instance, GBoxed *arg1, GBoxed *arg2, gpointer user_data)</literal>.
 *
 * Since: 2.26
 */


/**
 * g_cclosure_marshal_BOOL__FLAGS:
 *
 * Another name for g_cclosure_marshal_BOOLEAN__FLAGS().
 */


/**
 * g_cclosure_marshal_STRING__OBJECT_POINTER:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: a #GValue, which can store the returned string
 * @n_param_values: 3
 * @param_values: a #GValue array holding instance, arg1 and arg2
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>gchar* (*callback) (gpointer instance, GObject *arg1, gpointer arg2, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__BOOLEAN:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gboolean parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gboolean arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__BOXED:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #GBoxed* parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, GBoxed *arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__CHAR:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gchar parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gchar arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__DOUBLE:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gdouble parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gdouble arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__ENUM:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the enumeration parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gint arg1, gpointer user_data)</literal> where the #gint parameter denotes an enumeration type..
 */


/**
 * g_cclosure_marshal_VOID__FLAGS:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the flags parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gint arg1, gpointer user_data)</literal> where the #gint parameter denotes a flags type.
 */


/**
 * g_cclosure_marshal_VOID__FLOAT:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gfloat parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gfloat arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__INT:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gint parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gint arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__LONG:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #glong parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, glong arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__OBJECT:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #GObject* parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, GObject *arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__PARAM:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #GParamSpec* parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, GParamSpec *arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__POINTER:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gpointer parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gpointer arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__STRING:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gchar* parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, const gchar *arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__UCHAR:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #guchar parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, guchar arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__UINT:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #guint parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, guint arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__UINT_POINTER:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 3
 * @param_values: a #GValue array holding instance, arg1 and arg2
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, guint arg1, gpointer arg2, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__ULONG:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #gulong parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gulong arg1, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_VOID__VARIANT:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 2
 * @param_values: a #GValue array holding the instance and the #GVariant* parameter
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, GVariant *arg1, gpointer user_data)</literal>.
 *
 * Since: 2.26
 */


/**
 * g_cclosure_marshal_VOID__VOID:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: ignored
 * @n_param_values: 1
 * @param_values: a #GValue array holding only the instance
 * @invocation_hint: the invocation hint given as the last argument
 *  to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_generic:
 * @closure: A #GClosure.
 * @return_gvalue: A #GValue to store the return value. May be %NULL
 *   if the callback of closure doesn't return a value.
 * @n_param_values: The length of the @param_values array.
 * @param_values: An array of #GValue<!-- -->s holding the arguments
 *   on which to invoke the callback of closure.
 * @invocation_hint: The invocation hint given as the last argument to
 *   g_closure_invoke().
 * @marshal_data: Additional data specified when registering the
 *   marshaller, see g_closure_set_marshal() and
 *   g_closure_set_meta_marshal()
 *
 * A generic marshaller function implemented via <ulink
 * url="http://sourceware.org/libffi/">libffi</ulink>.
 *
 * Since: 2.30
 */


/**
 * g_cclosure_new: (skip)
 * @callback_func: the function to invoke
 * @user_data: user data to pass to @callback_func
 * @destroy_data: destroy notify to be called when @user_data is no longer used
 *
 * Creates a new closure which invokes @callback_func with @user_data as
 * the last parameter.
 *
 * Returns: a new #GCClosure
 */


/**
 * g_cclosure_new_object: (skip)
 * @callback_func: the function to invoke
 * @object: a #GObject pointer to pass to @callback_func
 *
 * A variant of g_cclosure_new() which uses @object as @user_data and
 * calls g_object_watch_closure() on @object and the created
 * closure. This function is useful when you have a callback closely
 * associated with a #GObject, and want the callback to no longer run
 * after the object is is freed.
 *
 * Returns: a new #GCClosure
 */


/**
 * g_cclosure_new_object_swap: (skip)
 * @callback_func: the function to invoke
 * @object: a #GObject pointer to pass to @callback_func
 *
 * A variant of g_cclosure_new_swap() which uses @object as @user_data
 * and calls g_object_watch_closure() on @object and the created
 * closure. This function is useful when you have a callback closely
 * associated with a #GObject, and want the callback to no longer run
 * after the object is is freed.
 *
 * Returns: a new #GCClosure
 */


/**
 * g_cclosure_new_swap: (skip)
 * @callback_func: the function to invoke
 * @user_data: user data to pass to @callback_func
 * @destroy_data: destroy notify to be called when @user_data is no longer used
 *
 * Creates a new closure which invokes @callback_func with @user_data as
 * the first parameter.
 *
 * Returns: (transfer full): a new #GCClosure
 */


/**
 * g_clear_object: (skip)
 * @object_ptr: a pointer to a #GObject reference
 *
 * Clears a reference to a #GObject.
 *
 * @object_ptr must not be %NULL.
 *
 * If the reference is %NULL then this function does nothing.
 * Otherwise, the reference count of the object is decreased and the
 * pointer is set to %NULL.
 *
 * This function is threadsafe and modifies the pointer atomically,
 * using memory barriers where needed.
 *
 * A macro is also included that allows this function to be used without
 * pointer casts.
 *
 * Since: 2.28
 */


/**
 * g_closure_add_finalize_notifier: (skip)
 * @closure: a #GClosure
 * @notify_data: data to pass to @notify_func
 * @notify_func: the callback function to register
 *
 * Registers a finalization notifier which will be called when the
 * reference count of @closure goes down to 0. Multiple finalization
 * notifiers on a single closure are invoked in unspecified order. If
 * a single call to g_closure_unref() results in the closure being
 * both invalidated and finalized, then the invalidate notifiers will
 * be run before the finalize notifiers.
 */


/**
 * g_closure_add_invalidate_notifier: (skip)
 * @closure: a #GClosure
 * @notify_data: data to pass to @notify_func
 * @notify_func: the callback function to register
 *
 * Registers an invalidation notifier which will be called when the
 * @closure is invalidated with g_closure_invalidate(). Invalidation
 * notifiers are invoked before finalization notifiers, in an
 * unspecified order.
 */


/**
 * g_closure_add_marshal_guards: (skip)
 * @closure: a #GClosure
 * @pre_marshal_data: data to pass to @pre_marshal_notify
 * @pre_marshal_notify: a function to call before the closure callback
 * @post_marshal_data: data to pass to @post_marshal_notify
 * @post_marshal_notify: a function to call after the closure callback
 *
 * Adds a pair of notifiers which get invoked before and after the
 * closure callback, respectively. This is typically used to protect
 * the extra arguments for the duration of the callback. See
 * g_object_watch_closure() for an example of marshal guards.
 */


/**
 * g_closure_invalidate:
 * @closure: GClosure to invalidate
 *
 * Sets a flag on the closure to indicate that its calling
 * environment has become invalid, and thus causes any future
 * invocations of g_closure_invoke() on this @closure to be
 * ignored. Also, invalidation notifiers installed on the closure will
 * be called at this point. Note that unless you are holding a
 * reference to the closure yourself, the invalidation notifiers may
 * unref the closure and cause it to be destroyed, so if you need to
 * access the closure after calling g_closure_invalidate(), make sure
 * that you've previously called g_closure_ref().
 *
 * Note that g_closure_invalidate() will also be called when the
 * reference count of a closure drops to zero (unless it has already
 * been invalidated before).
 */


/**
 * g_closure_invoke:
 * @closure: a #GClosure
 * @return_value: (allow-none): a #GValue to store the return
 *                value. May be %NULL if the callback of @closure
 *                doesn't return a value.
 * @n_param_values: the length of the @param_values array
 * @param_values: (array length=n_param_values): an array of
 *                #GValue<!-- -->s holding the arguments on which to
 *                invoke the callback of @closure
 * @invocation_hint: (allow-none): a context-dependent invocation hint
 *
 * Invokes the closure, i.e. executes the callback represented by the @closure.
 */


/**
 * g_closure_new_object:
 * @sizeof_closure: the size of the structure to allocate, must be at least
 *  <literal>sizeof (GClosure)</literal>
 * @object: a #GObject pointer to store in the @data field of the newly
 *  allocated #GClosure
 *
 * A variant of g_closure_new_simple() which stores @object in the
 * @data field of the closure and calls g_object_watch_closure() on
 * @object and the created closure. This function is mainly useful
 * when implementing new types of closures.
 *
 * Returns: (transfer full): a newly allocated #GClosure
 */


/**
 * g_closure_new_simple:
 * @sizeof_closure: the size of the structure to allocate, must be at least
 *                  <literal>sizeof (GClosure)</literal>
 * @data: data to store in the @data field of the newly allocated #GClosure
 *
 * Allocates a struct of the given size and initializes the initial
 * part as a #GClosure. This function is mainly useful when
 * implementing new types of closures.
 *
 * |[
 * typedef struct _MyClosure MyClosure;
 * struct _MyClosure
 * {
 *   GClosure closure;
 *   // extra data goes here
 * };
 *
 * static void
 * my_closure_finalize (gpointer  notify_data,
 *                      GClosure *closure)
 * {
 *   MyClosure *my_closure = (MyClosure *)closure;
 *
 *   // free extra data here
 * }
 *
 * MyClosure *my_closure_new (gpointer data)
 * {
 *   GClosure *closure;
 *   MyClosure *my_closure;
 *
 *   closure = g_closure_new_simple (sizeof (MyClosure), data);
 *   my_closure = (MyClosure *) closure;
 *
 *   // initialize extra data here
 *
 *   g_closure_add_finalize_notifier (closure, notify_data,
 *                                    my_closure_finalize);
 *   return my_closure;
 * }
 * ]|
 *
 * Returns: (transfer full): a newly allocated #GClosure
 */


/**
 * g_closure_ref:
 * @closure: #GClosure to increment the reference count on
 *
 * Increments the reference count on a closure to force it staying
 * alive while the caller holds a pointer to it.
 *
 * Returns: (transfer none): The @closure passed in, for convenience
 */


/**
 * g_closure_remove_finalize_notifier: (skip)
 * @closure: a #GClosure
 * @notify_data: data which was passed to g_closure_add_finalize_notifier()
 *  when registering @notify_func
 * @notify_func: the callback function to remove
 *
 * Removes a finalization notifier.
 *
 * Notice that notifiers are automatically removed after they are run.
 */


/**
 * g_closure_remove_invalidate_notifier: (skip)
 * @closure: a #GClosure
 * @notify_data: data which was passed to g_closure_add_invalidate_notifier()
 *               when registering @notify_func
 * @notify_func: the callback function to remove
 *
 * Removes an invalidation notifier.
 *
 * Notice that notifiers are automatically removed after they are run.
 */


/**
 * g_closure_set_marshal: (skip)
 * @closure: a #GClosure
 * @marshal: a #GClosureMarshal function
 *
 * Sets the marshaller of @closure. The <literal>marshal_data</literal>
 * of @marshal provides a way for a meta marshaller to provide additional
 * information to the marshaller. (See g_closure_set_meta_marshal().) For
 * GObject's C predefined marshallers (the g_cclosure_marshal_*()
 * functions), what it provides is a callback function to use instead of
 * @closure->callback.
 */


/**
 * g_closure_set_meta_marshal: (skip)
 * @closure: a #GClosure
 * @marshal_data: context-dependent data to pass to @meta_marshal
 * @meta_marshal: a #GClosureMarshal function
 *
 * Sets the meta marshaller of @closure.  A meta marshaller wraps
 * @closure->marshal and modifies the way it is called in some
 * fashion. The most common use of this facility is for C callbacks.
 * The same marshallers (generated by <link
 * linkend="glib-genmarshal">glib-genmarshal</link>) are used
 * everywhere, but the way that we get the callback function
 * differs. In most cases we want to use @closure->callback, but in
 * other cases we want to use some different technique to retrieve the
 * callback function.
 *
 * For example, class closures for signals (see
 * g_signal_type_cclosure_new()) retrieve the callback function from a
 * fixed offset in the class structure.  The meta marshaller retrieves
 * the right callback and passes it to the marshaller as the
 * @marshal_data argument.
 */


/**
 * g_closure_sink:
 * @closure: #GClosure to decrement the initial reference count on, if it's
 *           still being held
 *
 * Takes over the initial ownership of a closure.  Each closure is
 * initially created in a <firstterm>floating</firstterm> state, which
 * means that the initial reference count is not owned by any caller.
 * g_closure_sink() checks to see if the object is still floating, and
 * if so, unsets the floating state and decreases the reference
 * count. If the closure is not floating, g_closure_sink() does
 * nothing. The reason for the existence of the floating state is to
 * prevent cumbersome code sequences like:
 * |[
 * closure = g_cclosure_new (cb_func, cb_data);
 * g_source_set_closure (source, closure);
 * g_closure_unref (closure); // XXX GObject doesn't really need this
 * ]|
 * Because g_source_set_closure() (and similar functions) take ownership of the
 * initial reference count, if it is unowned, we instead can write:
 * |[
 * g_source_set_closure (source, g_cclosure_new (cb_func, cb_data));
 * ]|
 *
 * Generally, this function is used together with g_closure_ref(). Ane example
 * of storing a closure for later notification looks like:
 * |[
 * static GClosure *notify_closure = NULL;
 * void
 * foo_notify_set_closure (GClosure *closure)
 * {
 *   if (notify_closure)
 *     g_closure_unref (notify_closure);
 *   notify_closure = closure;
 *   if (notify_closure)
 *     {
 *       g_closure_ref (notify_closure);
 *       g_closure_sink (notify_closure);
 *     }
 * }
 * ]|
 *
 * Because g_closure_sink() may decrement the reference count of a closure
 * (if it hasn't been called on @closure yet) just like g_closure_unref(),
 * g_closure_ref() should be called prior to this function.
 */


/**
 * g_closure_unref:
 * @closure: #GClosure to decrement the reference count on
 *
 * Decrements the reference count of a closure after it was previously
 * incremented by the same caller. If no other callers are using the
 * closure, then the closure will be destroyed and freed.
 */


/**
 * g_enum_complete_type_info:
 * @g_enum_type: the type identifier of the type being completed
 * @info: (out callee-allocates): the #GTypeInfo struct to be filled in
 * @const_values: An array of #GEnumValue structs for the possible
 *  enumeration values. The array is terminated by a struct with all
 *  members being 0.
 *
 * This function is meant to be called from the <literal>complete_type_info</literal>
 * function of a #GTypePlugin implementation, as in the following
 * example:
 *
 * |[
 * static void
 * my_enum_complete_type_info (GTypePlugin     *plugin,
 *                             GType            g_type,
 *                             GTypeInfo       *info,
 *                             GTypeValueTable *value_table)
 * {
 *   static const GEnumValue values[] = {
 *     { MY_ENUM_FOO, "MY_ENUM_FOO", "foo" },
 *     { MY_ENUM_BAR, "MY_ENUM_BAR", "bar" },
 *     { 0, NULL, NULL }
 *   };
 *
 *   g_enum_complete_type_info (type, info, values);
 * }
 * ]|
 */


/**
 * g_enum_get_value:
 * @enum_class: a #GEnumClass
 * @value: the value to look up
 *
 * Returns the #GEnumValue for a value.
 *
 * Returns: (transfer none): the #GEnumValue for @value, or %NULL
 *          if @value is not a member of the enumeration
 */


/**
 * g_enum_get_value_by_name:
 * @enum_class: a #GEnumClass
 * @name: the name to look up
 *
 * Looks up a #GEnumValue by name.
 *
 * Returns: (transfer none): the #GEnumValue with name @name,
 *          or %NULL if the enumeration doesn't have a member
 *          with that name
 */


/**
 * g_enum_get_value_by_nick:
 * @enum_class: a #GEnumClass
 * @nick: the nickname to look up
 *
 * Looks up a #GEnumValue by nickname.
 *
 * Returns: (transfer none): the #GEnumValue with nickname @nick,
 *          or %NULL if the enumeration doesn't have a member
 *          with that nickname
 */


/**
 * g_enum_register_static:
 * @name: A nul-terminated string used as the name of the new type.
 * @const_static_values: An array of #GEnumValue structs for the possible
 *  enumeration values. The array is terminated by a struct with all
 *  members being 0. GObject keeps a reference to the data, so it cannot
 *  be stack-allocated.
 *
 * Registers a new static enumeration type with the name @name.
 *
 * It is normally more convenient to let <link
 * linkend="glib-mkenums">glib-mkenums</link> generate a
 * my_enum_get_type() function from a usual C enumeration definition
 * than to write one yourself using g_enum_register_static().
 *
 * Returns: The new type identifier.
 */


/**
 * g_flags_complete_type_info:
 * @g_flags_type: the type identifier of the type being completed
 * @info: (out callee-allocates): the #GTypeInfo struct to be filled in
 * @const_values: An array of #GFlagsValue structs for the possible
 *  enumeration values. The array is terminated by a struct with all
 *  members being 0.
 *
 * This function is meant to be called from the complete_type_info()
 * function of a #GTypePlugin implementation, see the example for
 * g_enum_complete_type_info() above.
 */


/**
 * g_flags_get_first_value:
 * @flags_class: a #GFlagsClass
 * @value: the value
 *
 * Returns the first #GFlagsValue which is set in @value.
 *
 * Returns: (transfer none): the first #GFlagsValue which is set in
 *          @value, or %NULL if none is set
 */


/**
 * g_flags_get_value_by_name:
 * @flags_class: a #GFlagsClass
 * @name: the name to look up
 *
 * Looks up a #GFlagsValue by name.
 *
 * Returns: (transfer none): the #GFlagsValue with name @name,
 *          or %NULL if there is no flag with that name
 */


/**
 * g_flags_get_value_by_nick:
 * @flags_class: a #GFlagsClass
 * @nick: the nickname to look up
 *
 * Looks up a #GFlagsValue by nickname.
 *
 * Returns: (transfer none): the #GFlagsValue with nickname @nick,
 *          or %NULL if there is no flag with that nickname
 */


/**
 * g_flags_register_static:
 * @name: A nul-terminated string used as the name of the new type.
 * @const_static_values: An array of #GFlagsValue structs for the possible
 *  flags values. The array is terminated by a struct with all members being 0.
 *  GObject keeps a reference to the data, so it cannot be stack-allocated.
 *
 * Registers a new static flags type with the name @name.
 *
 * It is normally more convenient to let <link
 * linkend="glib-mkenums">glib-mkenums</link> generate a
 * my_flags_get_type() function from a usual C enumeration definition
 * than to write one yourself using g_flags_register_static().
 *
 * Returns: The new type identifier.
 */


/**
 * g_object_add_toggle_ref: (skip)
 * @object: a #GObject
 * @notify: a function to call when this reference is the
 *  last reference to the object, or is no longer
 *  the last reference.
 * @data: data to pass to @notify
 *
 * Increases the reference count of the object by one and sets a
 * callback to be called when all other references to the object are
 * dropped, or when this is already the last reference to the object
 * and another reference is established.
 *
 * This functionality is intended for binding @object to a proxy
 * object managed by another memory manager. This is done with two
 * paired references: the strong reference added by
 * g_object_add_toggle_ref() and a reverse reference to the proxy
 * object which is either a strong reference or weak reference.
 *
 * The setup is that when there are no other references to @object,
 * only a weak reference is held in the reverse direction from @object
 * to the proxy object, but when there are other references held to
 * @object, a strong reference is held. The @notify callback is called
 * when the reference from @object to the proxy object should be
 * <firstterm>toggled</firstterm> from strong to weak (@is_last_ref
 * true) or weak to strong (@is_last_ref false).
 *
 * Since a (normal) reference must be held to the object before
 * calling g_object_add_toggle_ref(), the initial state of the reverse
 * link is always strong.
 *
 * Multiple toggle references may be added to the same gobject,
 * however if there are multiple toggle references to an object, none
 * of them will ever be notified until all but one are removed.  For
 * this reason, you should only ever use a toggle reference if there
 * is important state in the proxy object.
 *
 * Since: 2.8
 */


/**
 * g_object_add_weak_pointer: (skip)
 * @object: The object that should be weak referenced.
 * @weak_pointer_location: (inout): The memory address of a pointer.
 *
 * Adds a weak reference from weak_pointer to @object to indicate that
 * the pointer located at @weak_pointer_location is only valid during
 * the lifetime of @object. When the @object is finalized,
 * @weak_pointer will be set to %NULL.
 *
 * Note that as with g_object_weak_ref(), the weak references created by
 * this method are not thread-safe: they cannot safely be used in one
 * thread if the object's last g_object_unref() might happen in another
 * thread. Use #GWeakRef if thread-safety is required.
 */


/**
 * g_object_bind_property:
 * @source: (type GObject.Object): the source #GObject
 * @source_property: the property on @source to bind
 * @target: (type GObject.Object): the target #GObject
 * @target_property: the property on @target to bind
 * @flags: flags to pass to #GBinding
 *
 * Creates a binding between @source_property on @source and @target_property
 * on @target. Whenever the @source_property is changed the @target_property is
 * updated using the same value. For instance:
 *
 * |[
 *   g_object_bind_property (action, "active", widget, "sensitive", 0);
 * ]|
 *
 * Will result in the "sensitive" property of the widget #GObject instance to be
 * updated with the same value of the "active" property of the action #GObject
 * instance.
 *
 * If @flags contains %G_BINDING_BIDIRECTIONAL then the binding will be mutual:
 * if @target_property on @target changes then the @source_property on @source
 * will be updated as well.
 *
 * The binding will automatically be removed when either the @source or the
 * @target instances are finalized. To remove the binding without affecting the
 * @source and the @target you can just call g_object_unref() on the returned
 * #GBinding instance.
 *
 * A #GObject can have multiple bindings.
 *
 * Returns: (transfer none): the #GBinding instance representing the
 *   binding between the two #GObject instances. The binding is released
 *   whenever the #GBinding reference count reaches zero.
 * Since: 2.26
 */


/**
 * g_object_bind_property_full:
 * @source: (type GObject.Object): the source #GObject
 * @source_property: the property on @source to bind
 * @target: (type GObject.Object): the target #GObject
 * @target_property: the property on @target to bind
 * @flags: flags to pass to #GBinding
 * @transform_to: (scope notified) (allow-none): the transformation function
 *   from the @source to the @target, or %NULL to use the default
 * @transform_from: (scope notified) (allow-none): the transformation function
 *   from the @target to the @source, or %NULL to use the default
 * @user_data: custom data to be passed to the transformation functions,
 *   or %NULL
 * @notify: function to be called when disposing the binding, to free the
 *   resources used by the transformation functions
 *
 * Complete version of g_object_bind_property().
 *
 * Creates a binding between @source_property on @source and @target_property
 * on @target, allowing you to set the transformation functions to be used by
 * the binding.
 *
 * If @flags contains %G_BINDING_BIDIRECTIONAL then the binding will be mutual:
 * if @target_property on @target changes then the @source_property on @source
 * will be updated as well. The @transform_from function is only used in case
 * of bidirectional bindings, otherwise it will be ignored
 *
 * The binding will automatically be removed when either the @source or the
 * @target instances are finalized. To remove the binding without affecting the
 * @source and the @target you can just call g_object_unref() on the returned
 * #GBinding instance.
 *
 * A #GObject can have multiple bindings.
 *
 * <note>The same @user_data parameter will be used for both @transform_to
 * and @transform_from transformation functions; the @notify function will
 * be called once, when the binding is removed. If you need different data
 * for each transformation function, please use
 * g_object_bind_property_with_closures() instead.</note>
 *
 * Returns: (transfer none): the #GBinding instance representing the
 *   binding between the two #GObject instances. The binding is released
 *   whenever the #GBinding reference count reaches zero.
 * Since: 2.26
 */


/**
 * g_object_bind_property_with_closures: (rename-to g_object_bind_property_full)
 * @source: (type GObject.Object): the source #GObject
 * @source_property: the property on @source to bind
 * @target: (type GObject.Object): the target #GObject
 * @target_property: the property on @target to bind
 * @flags: flags to pass to #GBinding
 * @transform_to: a #GClosure wrapping the transformation function
 *   from the @source to the @target, or %NULL to use the default
 * @transform_from: a #GClosure wrapping the transformation function
 *   from the @target to the @source, or %NULL to use the default
 *
 * Creates a binding between @source_property on @source and @target_property
 * on @target, allowing you to set the transformation functions to be used by
 * the binding.
 *
 * This function is the language bindings friendly version of
 * g_object_bind_property_full(), using #GClosure<!-- -->s instead of
 * function pointers.
 *
 * Returns: (transfer none): the #GBinding instance representing the
 *   binding between the two #GObject instances. The binding is released
 *   whenever the #GBinding reference count reaches zero.
 * Since: 2.26
 */


/**
 * g_object_class_find_property:
 * @oclass: a #GObjectClass
 * @property_name: the name of the property to look up
 *
 * Looks up the #GParamSpec for a property of a class.
 *
 * Returns: (transfer none): the #GParamSpec for the property, or
 *          %NULL if the class doesn't have a property of that name
 */


/**
 * g_object_class_install_properties:
 * @oclass: a #GObjectClass
 * @n_pspecs: the length of the #GParamSpec<!-- -->s array
 * @pspecs: (array length=n_pspecs): the #GParamSpec<!-- -->s array
 *   defining the new properties
 *
 * Installs new properties from an array of #GParamSpec<!-- -->s. This is
 * usually done in the class initializer.
 *
 * The property id of each property is the index of each #GParamSpec in
 * the @pspecs array.
 *
 * The property id of 0 is treated specially by #GObject and it should not
 * be used to store a #GParamSpec.
 *
 * This function should be used if you plan to use a static array of
 * #GParamSpec<!-- -->s and g_object_notify_by_pspec(). For instance, this
 * class initialization:
 *
 * |[
 * enum {
 *   PROP_0, PROP_FOO, PROP_BAR, N_PROPERTIES
 * };
 *
 * static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };
 *
 * static void
 * my_object_class_init (MyObjectClass *klass)
 * {
 *   GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 *
 *   obj_properties[PROP_FOO] =
 *     g_param_spec_int ("foo", "Foo", "Foo",
 *                       -1, G_MAXINT,
 *                       0,
 *                       G_PARAM_READWRITE);
 *
 *   obj_properties[PROP_BAR] =
 *     g_param_spec_string ("bar", "Bar", "Bar",
 *                          NULL,
 *                          G_PARAM_READWRITE);
 *
 *   gobject_class->set_property = my_object_set_property;
 *   gobject_class->get_property = my_object_get_property;
 *   g_object_class_install_properties (gobject_class,
 *                                      N_PROPERTIES,
 *                                      obj_properties);
 * }
 * ]|
 *
 * allows calling g_object_notify_by_pspec() to notify of property changes:
 *
 * |[
 * void
 * my_object_set_foo (MyObject *self, gint foo)
 * {
 *   if (self->foo != foo)
 *     {
 *       self->foo = foo;
 *       g_object_notify_by_pspec (G_OBJECT (self), obj_properties[PROP_FOO]);
 *     }
 *  }
 * ]|
 *
 * Since: 2.26
 */


/**
 * g_object_class_install_property:
 * @oclass: a #GObjectClass
 * @property_id: the id for the new property
 * @pspec: the #GParamSpec for the new property
 *
 * Installs a new property. This is usually done in the class initializer.
 *
 * Note that it is possible to redefine a property in a derived class,
 * by installing a property with the same name. This can be useful at times,
 * e.g. to change the range of allowed values or the default value.
 */


/**
 * g_object_class_list_properties:
 * @oclass: a #GObjectClass
 * @n_properties: (out): return location for the length of the returned array
 *
 * Get an array of #GParamSpec* for all properties of a class.
 *
 * Returns: (array length=n_properties) (transfer container): an array of
 *          #GParamSpec* which should be freed after use
 */


/**
 * g_object_class_override_property:
 * @oclass: a #GObjectClass
 * @property_id: the new property ID
 * @name: the name of a property registered in a parent class or
 *  in an interface of this class.
 *
 * Registers @property_id as referring to a property with the
 * name @name in a parent class or in an interface implemented
 * by @oclass. This allows this class to <firstterm>override</firstterm>
 * a property implementation in a parent class or to provide
 * the implementation of a property from an interface.
 *
 * <note>
 * Internally, overriding is implemented by creating a property of type
 * #GParamSpecOverride; generally operations that query the properties of
 * the object class, such as g_object_class_find_property() or
 * g_object_class_list_properties() will return the overridden
 * property. However, in one case, the @construct_properties argument of
 * the @constructor virtual function, the #GParamSpecOverride is passed
 * instead, so that the @param_id field of the #GParamSpec will be
 * correct.  For virtually all uses, this makes no difference. If you
 * need to get the overridden property, you can call
 * g_param_spec_get_redirect_target().
 * </note>
 *
 * Since: 2.4
 */


/**
 * g_object_connect: (skip)
 * @object: a #GObject
 * @signal_spec: the spec for the first signal
 * @...: #GCallback for the first signal, followed by data for the
 *       first signal, followed optionally by more signal
 *       spec/callback/data triples, followed by %NULL
 *
 * A convenience function to connect multiple signals at once.
 *
 * The signal specs expected by this function have the form
 * "modifier::signal_name", where modifier can be one of the following:
 * <variablelist>
 * <varlistentry>
 * <term>signal</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_data (..., NULL, 0)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>object_signal</term>
 * <term>object-signal</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_object (..., 0)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>swapped_signal</term>
 * <term>swapped-signal</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_data (..., NULL, G_CONNECT_SWAPPED)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>swapped_object_signal</term>
 * <term>swapped-object-signal</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_object (..., G_CONNECT_SWAPPED)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>signal_after</term>
 * <term>signal-after</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_data (..., NULL, G_CONNECT_AFTER)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>object_signal_after</term>
 * <term>object-signal-after</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_object (..., G_CONNECT_AFTER)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>swapped_signal_after</term>
 * <term>swapped-signal-after</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_data (..., NULL, G_CONNECT_SWAPPED | G_CONNECT_AFTER)</literal>
 * </para></listitem>
 * </varlistentry>
 * <varlistentry>
 * <term>swapped_object_signal_after</term>
 * <term>swapped-object-signal-after</term>
 * <listitem><para>
 * equivalent to <literal>g_signal_connect_object (..., G_CONNECT_SWAPPED | G_CONNECT_AFTER)</literal>
 * </para></listitem>
 * </varlistentry>
 * </variablelist>
 *
 * |[
 *   menu->toplevel = g_object_connect (g_object_new (GTK_TYPE_WINDOW,
 * 						   "type", GTK_WINDOW_POPUP,
 * 						   "child", menu,
 * 						   NULL),
 * 				     "signal::event", gtk_menu_window_event, menu,
 * 				     "signal::size_request", gtk_menu_window_size_request, menu,
 * 				     "signal::destroy", gtk_widget_destroyed, &amp;menu-&gt;toplevel,
 * 				     NULL);
 * ]|
 *
 * Returns: (transfer none): @object
 */


/**
 * g_object_disconnect: (skip)
 * @object: a #GObject
 * @signal_spec: the spec for the first signal
 * @...: #GCallback for the first signal, followed by data for the first signal,
 *  followed optionally by more signal spec/callback/data triples,
 *  followed by %NULL
 *
 * A convenience function to disconnect multiple signals at once.
 *
 * The signal specs expected by this function have the form
 * "any_signal", which means to disconnect any signal with matching
 * callback and data, or "any_signal::signal_name", which only
 * disconnects the signal named "signal_name".
 */


/**
 * g_object_dup_data:
 * @object: the #GObject to store user data on
 * @key: a string, naming the user data pointer
 * @dup_func: (allow-none): function to dup the value
 * @user_data: (allow-none): passed as user_data to @dup_func
 *
 * This is a variant of g_object_get_data() which returns
 * a 'duplicate' of the value. @dup_func defines the
 * meaning of 'duplicate' in this context, it could e.g.
 * take a reference on a ref-counted object.
 *
 * If the @key is not set on the object then @dup_func
 * will be called with a %NULL argument.
 *
 * Note that @dup_func is called while user data of @object
 * is locked.
 *
 * This function can be useful to avoid races when multiple
 * threads are using object data on the same key on the same
 * object.
 *
 * Returns: the result of calling @dup_func on the value
 *     associated with @key on @object, or %NULL if not set.
 *     If @dup_func is %NULL, the value is returned
 *     unmodified.
 * Since: 2.34
 */


/**
 * g_object_dup_qdata:
 * @object: the #GObject to store user data on
 * @quark: a #GQuark, naming the user data pointer
 * @dup_func: (allow-none): function to dup the value
 * @user_data: (allow-none): passed as user_data to @dup_func
 *
 * This is a variant of g_object_get_qdata() which returns
 * a 'duplicate' of the value. @dup_func defines the
 * meaning of 'duplicate' in this context, it could e.g.
 * take a reference on a ref-counted object.
 *
 * If the @quark is not set on the object then @dup_func
 * will be called with a %NULL argument.
 *
 * Note that @dup_func is called while user data of @object
 * is locked.
 *
 * This function can be useful to avoid races when multiple
 * threads are using object data on the same key on the same
 * object.
 *
 * Returns: the result of calling @dup_func on the value
 *     associated with @quark on @object, or %NULL if not set.
 *     If @dup_func is %NULL, the value is returned
 *     unmodified.
 * Since: 2.34
 */


/**
 * g_object_force_floating:
 * @object: a #GObject
 *
 * This function is intended for #GObject implementations to re-enforce a
 * <link linkend="floating-ref">floating</link> object reference.
 * Doing this is seldom required: all
 * #GInitiallyUnowned<!-- -->s are created with a floating reference which
 * usually just needs to be sunken by calling g_object_ref_sink().
 *
 * Since: 2.10
 */


/**
 * g_object_freeze_notify:
 * @object: a #GObject
 *
 * Increases the freeze count on @object. If the freeze count is
 * non-zero, the emission of "notify" signals on @object is
 * stopped. The signals are queued until the freeze count is decreased
 * to zero. Duplicate notifications are squashed so that at most one
 * #GObject::notify signal is emitted for each property modified while the
 * object is frozen.
 *
 * This is necessary for accessors that modify multiple properties to prevent
 * premature notification while the object is still being modified.
 */


/**
 * g_object_get: (skip)
 * @object: a #GObject
 * @first_property_name: name of the first property to get
 * @...: return location for the first property, followed optionally by more
 *  name/return location pairs, followed by %NULL
 *
 * Gets properties of an object.
 *
 * In general, a copy is made of the property contents and the caller
 * is responsible for freeing the memory in the appropriate manner for
 * the type, for instance by calling g_free() or g_object_unref().
 *
 * <example>
 * <title>Using g_object_get(<!-- -->)</title>
 * An example of using g_object_get() to get the contents
 * of three properties - one of type #G_TYPE_INT,
 * one of type #G_TYPE_STRING, and one of type #G_TYPE_OBJECT:
 * <programlisting>
 *  gint intval;
 *  gchar *strval;
 *  GObject *objval;
 *
 *  g_object_get (my_object,
 *                "int-property", &intval,
 *                "str-property", &strval,
 *                "obj-property", &objval,
 *                NULL);
 *
 *  // Do something with intval, strval, objval
 *
 *  g_free (strval);
 *  g_object_unref (objval);
 * </programlisting>
 * </example>
 */


/**
 * g_object_get_data:
 * @object: #GObject containing the associations
 * @key: name of the key for that association
 *
 * Gets a named field from the objects table of associations (see g_object_set_data()).
 *
 * Returns: (transfer none): the data if found, or %NULL if no such data exists.
 */


/**
 * g_object_get_property:
 * @object: a #GObject
 * @property_name: the name of the property to get
 * @value: return location for the property value
 *
 * Gets a property of an object. @value must have been initialized to the
 * expected type of the property (or a type to which the expected type can be
 * transformed) using g_value_init().
 *
 * In general, a copy is made of the property contents and the caller is
 * responsible for freeing the memory by calling g_value_unset().
 *
 * Note that g_object_get_property() is really intended for language
 * bindings, g_object_get() is much more convenient for C programming.
 */


/**
 * g_object_get_qdata:
 * @object: The GObject to get a stored user data pointer from
 * @quark: A #GQuark, naming the user data pointer
 *
 * This function gets back user data pointers stored via
 * g_object_set_qdata().
 *
 * Returns: (transfer none): The user data pointer set, or %NULL
 */


/**
 * g_object_get_valist: (skip)
 * @object: a #GObject
 * @first_property_name: name of the first property to get
 * @var_args: return location for the first property, followed optionally by more
 *  name/return location pairs, followed by %NULL
 *
 * Gets properties of an object.
 *
 * In general, a copy is made of the property contents and the caller
 * is responsible for freeing the memory in the appropriate manner for
 * the type, for instance by calling g_free() or g_object_unref().
 *
 * See g_object_get().
 */


/**
 * g_object_interface_find_property:
 * @g_iface: any interface vtable for the interface, or the default
 *  vtable for the interface
 * @property_name: name of a property to lookup.
 *
 * Find the #GParamSpec with the given name for an
 * interface. Generally, the interface vtable passed in as @g_iface
 * will be the default vtable from g_type_default_interface_ref(), or,
 * if you know the interface has already been loaded,
 * g_type_default_interface_peek().
 *
 * Since: 2.4
 * Returns: (transfer none): the #GParamSpec for the property of the
 *          interface with the name @property_name, or %NULL if no
 *          such property exists.
 */


/**
 * g_object_interface_install_property:
 * @g_iface: any interface vtable for the interface, or the default
 *  vtable for the interface.
 * @pspec: the #GParamSpec for the new property
 *
 * Add a property to an interface; this is only useful for interfaces
 * that are added to GObject-derived types. Adding a property to an
 * interface forces all objects classes with that interface to have a
 * compatible property. The compatible property could be a newly
 * created #GParamSpec, but normally
 * g_object_class_override_property() will be used so that the object
 * class only needs to provide an implementation and inherits the
 * property description, default value, bounds, and so forth from the
 * interface property.
 *
 * This function is meant to be called from the interface's default
 * vtable initialization function (the @class_init member of
 * #GTypeInfo.) It must not be called after after @class_init has
 * been called for any object types implementing this interface.
 *
 * Since: 2.4
 */


/**
 * g_object_interface_list_properties:
 * @g_iface: any interface vtable for the interface, or the default
 *  vtable for the interface
 * @n_properties_p: (out): location to store number of properties returned.
 *
 * Lists the properties of an interface.Generally, the interface
 * vtable passed in as @g_iface will be the default vtable from
 * g_type_default_interface_ref(), or, if you know the interface has
 * already been loaded, g_type_default_interface_peek().
 *
 * Since: 2.4
 * Returns: (array length=n_properties_p) (transfer container): a
 *          pointer to an array of pointers to #GParamSpec
 *          structures. The paramspecs are owned by GLib, but the
 *          array should be freed with g_free() when you are done with
 *          it.
 */


/**
 * g_object_is_floating:
 * @object: (type GObject.Object): a #GObject
 *
 * Checks whether @object has a <link linkend="floating-ref">floating</link>
 * reference.
 *
 * Since: 2.10
 * Returns: %TRUE if @object has a floating reference
 */


/**
 * g_object_new: (skip)
 * @object_type: the type id of the #GObject subtype to instantiate
 * @first_property_name: the name of the first property
 * @...: the value of the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * Creates a new instance of a #GObject subtype and sets its properties.
 *
 * Construction parameters (see #G_PARAM_CONSTRUCT, #G_PARAM_CONSTRUCT_ONLY)
 * which are not explicitly specified are set to their default values.
 *
 * Returns: (transfer full): a new instance of @object_type
 */


/**
 * g_object_new_valist: (skip)
 * @object_type: the type id of the #GObject subtype to instantiate
 * @first_property_name: the name of the first property
 * @var_args: the value of the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * Creates a new instance of a #GObject subtype and sets its properties.
 *
 * Construction parameters (see #G_PARAM_CONSTRUCT, #G_PARAM_CONSTRUCT_ONLY)
 * which are not explicitly specified are set to their default values.
 *
 * Returns: a new instance of @object_type
 */


/**
 * g_object_newv: (rename-to g_object_new)
 * @object_type: the type id of the #GObject subtype to instantiate
 * @n_parameters: the length of the @parameters array
 * @parameters: (array length=n_parameters): an array of #GParameter
 *
 * Creates a new instance of a #GObject subtype and sets its properties.
 *
 * Construction parameters (see #G_PARAM_CONSTRUCT, #G_PARAM_CONSTRUCT_ONLY)
 * which are not explicitly specified are set to their default values.
 *
 * Returns: (type GObject.Object) (transfer full): a new instance of
 * @object_type
 */


/**
 * g_object_notify:
 * @object: a #GObject
 * @property_name: the name of a property installed on the class of @object.
 *
 * Emits a "notify" signal for the property @property_name on @object.
 *
 * When possible, eg. when signaling a property change from within the class
 * that registered the property, you should use g_object_notify_by_pspec()
 * instead.
 *
 * Note that emission of the notify signal may be blocked with
 * g_object_freeze_notify(). In this case, the signal emissions are queued
 * and will be emitted (in reverse order) when g_object_thaw_notify() is
 * called.
 */


/**
 * g_object_notify_by_pspec:
 * @object: a #GObject
 * @pspec: the #GParamSpec of a property installed on the class of @object.
 *
 * Emits a "notify" signal for the property specified by @pspec on @object.
 *
 * This function omits the property name lookup, hence it is faster than
 * g_object_notify().
 *
 * One way to avoid using g_object_notify() from within the
 * class that registered the properties, and using g_object_notify_by_pspec()
 * instead, is to store the GParamSpec used with
 * g_object_class_install_property() inside a static array, e.g.:
 *
 * |[
 *   enum
 *   {
 *     PROP_0,
 *     PROP_FOO,
 *     PROP_LAST
 *   };
 *
 *   static GParamSpec *properties[PROP_LAST];
 *
 *   static void
 *   my_object_class_init (MyObjectClass *klass)
 *   {
 *     properties[PROP_FOO] = g_param_spec_int ("foo", "Foo", "The foo",
 *                                              0, 100,
 *                                              50,
 *                                              G_PARAM_READWRITE);
 *     g_object_class_install_property (gobject_class,
 *                                      PROP_FOO,
 *                                      properties[PROP_FOO]);
 *   }
 * ]|
 *
 * and then notify a change on the "foo" property with:
 *
 * |[
 *   g_object_notify_by_pspec (self, properties[PROP_FOO]);
 * ]|
 *
 * Since: 2.26
 */


/**
 * g_object_ref:
 * @object: (type GObject.Object): a #GObject
 *
 * Increases the reference count of @object.
 *
 * Returns: (type GObject.Object) (transfer none): the same @object
 */


/**
 * g_object_ref_sink:
 * @object: (type GObject.Object): a #GObject
 *
 * Increase the reference count of @object, and possibly remove the
 * <link linkend="floating-ref">floating</link> reference, if @object
 * has a floating reference.
 *
 * In other words, if the object is floating, then this call "assumes
 * ownership" of the floating reference, converting it to a normal
 * reference by clearing the floating flag while leaving the reference
 * count unchanged.  If the object is not floating, then this call
 * adds a new normal reference increasing the reference count by one.
 *
 * Since: 2.10
 * Returns: (type GObject.Object) (transfer none): @object
 */


/**
 * g_object_remove_toggle_ref: (skip)
 * @object: a #GObject
 * @notify: a function to call when this reference is the
 *  last reference to the object, or is no longer
 *  the last reference.
 * @data: data to pass to @notify
 *
 * Removes a reference added with g_object_add_toggle_ref(). The
 * reference count of the object is decreased by one.
 *
 * Since: 2.8
 */


/**
 * g_object_remove_weak_pointer: (skip)
 * @object: The object that is weak referenced.
 * @weak_pointer_location: (inout): The memory address of a pointer.
 *
 * Removes a weak reference from @object that was previously added
 * using g_object_add_weak_pointer(). The @weak_pointer_location has
 * to match the one used with g_object_add_weak_pointer().
 */


/**
 * g_object_replace_data:
 * @object: the #GObject to store user data on
 * @key: a string, naming the user data pointer
 * @oldval: (allow-none): the old value to compare against
 * @newval: (allow-none): the new value
 * @destroy: (allow-none): a destroy notify for the new value
 * @old_destroy: (allow-none): destroy notify for the existing value
 *
 * Compares the user data for the key @key on @object with
 * @oldval, and if they are the same, replaces @oldval with
 * @newval.
 *
 * This is like a typical atomic compare-and-exchange
 * operation, for user data on an object.
 *
 * If the previous value was replaced then ownership of the
 * old value (@oldval) is passed to the caller, including
 * the registered destroy notify for it (passed out in @old_destroy).
 * Its up to the caller to free this as he wishes, which may
 * or may not include using @old_destroy as sometimes replacement
 * should not destroy the object in the normal way.
 *
 * Returns: %TRUE if the existing value for @key was replaced
 *  by @newval, %FALSE otherwise.
 * Since: 2.34
 */


/**
 * g_object_replace_qdata:
 * @object: the #GObject to store user data on
 * @quark: a #GQuark, naming the user data pointer
 * @oldval: (allow-none): the old value to compare against
 * @newval: (allow-none): the new value
 * @destroy: (allow-none): a destroy notify for the new value
 * @old_destroy: (allow-none): destroy notify for the existing value
 *
 * Compares the user data for the key @quark on @object with
 * @oldval, and if they are the same, replaces @oldval with
 * @newval.
 *
 * This is like a typical atomic compare-and-exchange
 * operation, for user data on an object.
 *
 * If the previous value was replaced then ownership of the
 * old value (@oldval) is passed to the caller, including
 * the registered destroy notify for it (passed out in @old_destroy).
 * Its up to the caller to free this as he wishes, which may
 * or may not include using @old_destroy as sometimes replacement
 * should not destroy the object in the normal way.
 *
 * Returns: %TRUE if the existing value for @quark was replaced
 *  by @newval, %FALSE otherwise.
 * Since: 2.34
 */


/**
 * g_object_run_dispose:
 * @object: a #GObject
 *
 * Releases all references to other objects. This can be used to break
 * reference cycles.
 *
 * This functions should only be called from object system implementations.
 */


/**
 * g_object_set: (skip)
 * @object: a #GObject
 * @first_property_name: name of the first property to set
 * @...: value for the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * Sets properties on an object.
 *
 * Note that the "notify" signals are queued and only emitted (in
 * reverse order) after all properties have been set. See
 * g_object_freeze_notify().
 */


/**
 * g_object_set_data:
 * @object: #GObject containing the associations.
 * @key: name of the key
 * @data: data to associate with that key
 *
 * Each object carries around a table of associations from
 * strings to pointers.  This function lets you set an association.
 *
 * If the object already had an association with that name,
 * the old association will be destroyed.
 */


/**
 * g_object_set_data_full: (skip)
 * @object: #GObject containing the associations
 * @key: name of the key
 * @data: data to associate with that key
 * @destroy: function to call when the association is destroyed
 *
 * Like g_object_set_data() except it adds notification
 * for when the association is destroyed, either by setting it
 * to a different value or when the object is destroyed.
 *
 * Note that the @destroy callback is not called if @data is %NULL.
 */


/**
 * g_object_set_property:
 * @object: a #GObject
 * @property_name: the name of the property to set
 * @value: the value
 *
 * Sets a property on an object.
 */


/**
 * g_object_set_qdata: (skip)
 * @object: The GObject to set store a user data pointer
 * @quark: A #GQuark, naming the user data pointer
 * @data: An opaque user data pointer
 *
 * This sets an opaque, named pointer on an object.
 * The name is specified through a #GQuark (retrived e.g. via
 * g_quark_from_static_string()), and the pointer
 * can be gotten back from the @object with g_object_get_qdata()
 * until the @object is finalized.
 * Setting a previously set user data pointer, overrides (frees)
 * the old pointer set, using #NULL as pointer essentially
 * removes the data stored.
 */


/**
 * g_object_set_qdata_full: (skip)
 * @object: The GObject to set store a user data pointer
 * @quark: A #GQuark, naming the user data pointer
 * @data: An opaque user data pointer
 * @destroy: Function to invoke with @data as argument, when @data
 *           needs to be freed
 *
 * This function works like g_object_set_qdata(), but in addition,
 * a void (*destroy) (gpointer) function may be specified which is
 * called with @data as argument when the @object is finalized, or
 * the data is being overwritten by a call to g_object_set_qdata()
 * with the same @quark.
 */


/**
 * g_object_set_valist: (skip)
 * @object: a #GObject
 * @first_property_name: name of the first property to set
 * @var_args: value for the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * Sets properties on an object.
 */


/**
 * g_object_steal_data:
 * @object: #GObject containing the associations
 * @key: name of the key
 *
 * Remove a specified datum from the object's data associations,
 * without invoking the association's destroy handler.
 *
 * Returns: (transfer full): the data if found, or %NULL if no such data exists.
 */


/**
 * g_object_steal_qdata:
 * @object: The GObject to get a stored user data pointer from
 * @quark: A #GQuark, naming the user data pointer
 *
 * This function gets back user data pointers stored via
 * g_object_set_qdata() and removes the @data from object
 * without invoking its destroy() function (if any was
 * set).
 * Usually, calling this function is only required to update
 * user data pointers with a destroy notifier, for example:
 * |[
 * void
 * object_add_to_user_list (GObject     *object,
 *                          const gchar *new_string)
 * {
 *   // the quark, naming the object data
 *   GQuark quark_string_list = g_quark_from_static_string ("my-string-list");
 *   // retrive the old string list
 *   GList *list = g_object_steal_qdata (object, quark_string_list);
 *
 *   // prepend new string
 *   list = g_list_prepend (list, g_strdup (new_string));
 *   // this changed 'list', so we need to set it again
 *   g_object_set_qdata_full (object, quark_string_list, list, free_string_list);
 * }
 * static void
 * free_string_list (gpointer data)
 * {
 *   GList *node, *list = data;
 *
 *   for (node = list; node; node = node->next)
 *     g_free (node->data);
 *   g_list_free (list);
 * }
 * ]|
 * Using g_object_get_qdata() in the above example, instead of
 * g_object_steal_qdata() would have left the destroy function set,
 * and thus the partial string list would have been freed upon
 * g_object_set_qdata_full().
 *
 * Returns: (transfer full): The user data pointer set, or %NULL
 */


/**
 * g_object_thaw_notify:
 * @object: a #GObject
 *
 * Reverts the effect of a previous call to
 * g_object_freeze_notify(). The freeze count is decreased on @object
 * and when it reaches zero, queued "notify" signals are emitted.
 *
 * Duplicate notifications for each property are squashed so that at most one
 * #GObject::notify signal is emitted for each property, in the reverse order
 * in which they have been queued.
 *
 * It is an error to call this function when the freeze count is zero.
 */


/**
 * g_object_unref:
 * @object: (type GObject.Object): a #GObject
 *
 * Decreases the reference count of @object. When its reference count
 * drops to 0, the object is finalized (i.e. its memory is freed).
 */


/**
 * g_object_watch_closure:
 * @object: GObject restricting lifetime of @closure
 * @closure: GClosure to watch
 *
 * This function essentially limits the life time of the @closure to
 * the life time of the object. That is, when the object is finalized,
 * the @closure is invalidated by calling g_closure_invalidate() on
 * it, in order to prevent invocations of the closure with a finalized
 * (nonexisting) object. Also, g_object_ref() and g_object_unref() are
 * added as marshal guards to the @closure, to ensure that an extra
 * reference count is held on @object during invocation of the
 * @closure.  Usually, this function will be called on closures that
 * use this @object as closure data.
 */


/**
 * g_object_weak_ref: (skip)
 * @object: #GObject to reference weakly
 * @notify: callback to invoke before the object is freed
 * @data: extra data to pass to notify
 *
 * Adds a weak reference callback to an object. Weak references are
 * used for notification when an object is finalized. They are called
 * "weak references" because they allow you to safely hold a pointer
 * to an object without calling g_object_ref() (g_object_ref() adds a
 * strong reference, that is, forces the object to stay alive).
 *
 * Note that the weak references created by this method are not
 * thread-safe: they cannot safely be used in one thread if the
 * object's last g_object_unref() might happen in another thread.
 * Use #GWeakRef if thread-safety is required.
 */


/**
 * g_object_weak_unref: (skip)
 * @object: #GObject to remove a weak reference from
 * @notify: callback to search for
 * @data: data to search for
 *
 * Removes a weak reference callback to an object.
 */


/**
 * g_param_get_default_value:
 * @param: a #GParamSpec
 *
 * Gets the default value of @param as a pointer to a #GValue.
 *
 * The #GValue will remain value for the life of @param.
 *
 * Returns: a pointer to a #GValue which must not be modified
 * Since: 2.38
 */


/**
 * g_param_spec_boolean:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecBoolean instance specifying a %G_TYPE_BOOLEAN
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_boxed:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @boxed_type: %G_TYPE_BOXED derived type of this property
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecBoxed instance specifying a %G_TYPE_BOXED
 * derived property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_char:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecChar instance specifying a %G_TYPE_CHAR property.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_double:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecDouble instance specifying a %G_TYPE_DOUBLE
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_enum:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @enum_type: a #GType derived from %G_TYPE_ENUM
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecEnum instance specifying a %G_TYPE_ENUM
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_flags:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @flags_type: a #GType derived from %G_TYPE_FLAGS
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecFlags instance specifying a %G_TYPE_FLAGS
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_float:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecFloat instance specifying a %G_TYPE_FLOAT property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_get_blurb:
 * @pspec: a valid #GParamSpec
 *
 * Get the short description of a #GParamSpec.
 *
 * Returns: the short description of @pspec.
 */


/**
 * g_param_spec_get_name:
 * @pspec: a valid #GParamSpec
 *
 * Get the name of a #GParamSpec.
 *
 * The name is always an "interned" string (as per g_intern_string()).
 * This allows for pointer-value comparisons.
 *
 * Returns: the name of @pspec.
 */


/**
 * g_param_spec_get_nick:
 * @pspec: a valid #GParamSpec
 *
 * Get the nickname of a #GParamSpec.
 *
 * Returns: the nickname of @pspec.
 */


/**
 * g_param_spec_get_qdata:
 * @pspec: a valid #GParamSpec
 * @quark: a #GQuark, naming the user data pointer
 *
 * Gets back user data pointers stored via g_param_spec_set_qdata().
 *
 * Returns: (transfer none): the user data pointer set, or %NULL
 */


/**
 * g_param_spec_get_redirect_target:
 * @pspec: a #GParamSpec
 *
 * If the paramspec redirects operations to another paramspec,
 * returns that paramspec. Redirect is used typically for
 * providing a new implementation of a property in a derived
 * type while preserving all the properties from the parent
 * type. Redirection is established by creating a property
 * of type #GParamSpecOverride. See g_object_class_override_property()
 * for an example of the use of this capability.
 *
 * Since: 2.4
 * Returns: (transfer none): paramspec to which requests on this
 *          paramspec should be redirected, or %NULL if none.
 */


/**
 * g_param_spec_gtype:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @is_a_type: a #GType whose subtypes are allowed as values
 *  of the property (use %G_TYPE_NONE for any type)
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecGType instance specifying a
 * %G_TYPE_GTYPE property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Since: 2.10
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_int:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecInt instance specifying a %G_TYPE_INT property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_int64:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecInt64 instance specifying a %G_TYPE_INT64 property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_internal: (skip)
 * @param_type: the #GType for the property; must be derived from #G_TYPE_PARAM
 * @name: the canonical name of the property
 * @nick: the nickname of the property
 * @blurb: a short description of the property
 * @flags: a combination of #GParamFlags
 *
 * Creates a new #GParamSpec instance.
 *
 * A property name consists of segments consisting of ASCII letters and
 * digits, separated by either the '-' or '_' character. The first
 * character of a property name must be a letter. Names which violate these
 * rules lead to undefined behaviour.
 *
 * When creating and looking up a #GParamSpec, either separator can be
 * used, but they cannot be mixed. Using '-' is considerably more
 * efficient and in fact required when using property names as detail
 * strings for signals.
 *
 * Beyond the name, #GParamSpec<!-- -->s have two more descriptive
 * strings associated with them, the @nick, which should be suitable
 * for use as a label for the property in a property editor, and the
 * @blurb, which should be a somewhat longer description, suitable for
 * e.g. a tooltip. The @nick and @blurb should ideally be localized.
 *
 * Returns: a newly allocated #GParamSpec instance
 */


/**
 * g_param_spec_long:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecLong instance specifying a %G_TYPE_LONG property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_object:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @object_type: %G_TYPE_OBJECT derived type of this property
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecBoxed instance specifying a %G_TYPE_OBJECT
 * derived property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_override: (skip)
 * @name: the name of the property.
 * @overridden: The property that is being overridden
 *
 * Creates a new property of type #GParamSpecOverride. This is used
 * to direct operations to another paramspec, and will not be directly
 * useful unless you are implementing a new base type similar to GObject.
 *
 * Since: 2.4
 * Returns: the newly created #GParamSpec
 */


/**
 * g_param_spec_param:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @param_type: a #GType derived from %G_TYPE_PARAM
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecParam instance specifying a %G_TYPE_PARAM
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_pointer:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecPointer instance specifying a pointer property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_pool_insert:
 * @pool: a #GParamSpecPool.
 * @pspec: the #GParamSpec to insert
 * @owner_type: a #GType identifying the owner of @pspec
 *
 * Inserts a #GParamSpec in the pool.
 */


/**
 * g_param_spec_pool_list:
 * @pool: a #GParamSpecPool
 * @owner_type: the owner to look for
 * @n_pspecs_p: (out): return location for the length of the returned array
 *
 * Gets an array of all #GParamSpec<!-- -->s owned by @owner_type in
 * the pool.
 *
 * Returns: (array length=n_pspecs_p) (transfer container): a newly
 *          allocated array containing pointers to all #GParamSpecs
 *          owned by @owner_type in the pool
 */


/**
 * g_param_spec_pool_list_owned:
 * @pool: a #GParamSpecPool
 * @owner_type: the owner to look for
 *
 * Gets an #GList of all #GParamSpec<!-- -->s owned by @owner_type in
 * the pool.
 *
 * Returns: (transfer container) (element-type GObject.ParamSpec): a
 *          #GList of all #GParamSpec<!-- -->s owned by @owner_type in
 *          the pool#GParamSpec<!-- -->s.
 */


/**
 * g_param_spec_pool_lookup:
 * @pool: a #GParamSpecPool
 * @param_name: the name to look for
 * @owner_type: the owner to look for
 * @walk_ancestors: If %TRUE, also try to find a #GParamSpec with @param_name
 *  owned by an ancestor of @owner_type.
 *
 * Looks up a #GParamSpec in the pool.
 *
 * Returns: (transfer none): The found #GParamSpec, or %NULL if no
 * matching #GParamSpec was found.
 */


/**
 * g_param_spec_pool_new:
 * @type_prefixing: Whether the pool will support type-prefixed property names.
 *
 * Creates a new #GParamSpecPool.
 *
 * If @type_prefixing is %TRUE, lookups in the newly created pool will
 * allow to specify the owner as a colon-separated prefix of the
 * property name, like "GtkContainer:border-width". This feature is
 * deprecated, so you should always set @type_prefixing to %FALSE.
 *
 * Returns: (transfer none): a newly allocated #GParamSpecPool.
 */


/**
 * g_param_spec_pool_remove:
 * @pool: a #GParamSpecPool
 * @pspec: the #GParamSpec to remove
 *
 * Removes a #GParamSpec from the pool.
 */


/**
 * g_param_spec_ref: (skip)
 * @pspec: a valid #GParamSpec
 *
 * Increments the reference count of @pspec.
 *
 * Returns: the #GParamSpec that was passed into this function
 */


/**
 * g_param_spec_ref_sink: (skip)
 * @pspec: a valid #GParamSpec
 *
 * Convenience function to ref and sink a #GParamSpec.
 *
 * Since: 2.10
 * Returns: the #GParamSpec that was passed into this function
 */


/**
 * g_param_spec_set_qdata:
 * @pspec: the #GParamSpec to set store a user data pointer
 * @quark: a #GQuark, naming the user data pointer
 * @data: an opaque user data pointer
 *
 * Sets an opaque, named pointer on a #GParamSpec. The name is
 * specified through a #GQuark (retrieved e.g. via
 * g_quark_from_static_string()), and the pointer can be gotten back
 * from the @pspec with g_param_spec_get_qdata().  Setting a
 * previously set user data pointer, overrides (frees) the old pointer
 * set, using %NULL as pointer essentially removes the data stored.
 */


/**
 * g_param_spec_set_qdata_full: (skip)
 * @pspec: the #GParamSpec to set store a user data pointer
 * @quark: a #GQuark, naming the user data pointer
 * @data: an opaque user data pointer
 * @destroy: function to invoke with @data as argument, when @data needs to
 *  be freed
 *
 * This function works like g_param_spec_set_qdata(), but in addition,
 * a <literal>void (*destroy) (gpointer)</literal> function may be
 * specified which is called with @data as argument when the @pspec is
 * finalized, or the data is being overwritten by a call to
 * g_param_spec_set_qdata() with the same @quark.
 */


/**
 * g_param_spec_sink:
 * @pspec: a valid #GParamSpec
 *
 * The initial reference count of a newly created #GParamSpec is 1,
 * even though no one has explicitly called g_param_spec_ref() on it
 * yet. So the initial reference count is flagged as "floating", until
 * someone calls <literal>g_param_spec_ref (pspec); g_param_spec_sink
 * (pspec);</literal> in sequence on it, taking over the initial
 * reference count (thus ending up with a @pspec that has a reference
 * count of 1 still, but is not flagged "floating" anymore).
 */


/**
 * g_param_spec_steal_qdata:
 * @pspec: the #GParamSpec to get a stored user data pointer from
 * @quark: a #GQuark, naming the user data pointer
 *
 * Gets back user data pointers stored via g_param_spec_set_qdata()
 * and removes the @data from @pspec without invoking its destroy()
 * function (if any was set).  Usually, calling this function is only
 * required to update user data pointers with a destroy notifier.
 *
 * Returns: (transfer none): the user data pointer set, or %NULL
 */


/**
 * g_param_spec_string:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecString instance.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_uchar:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecUChar instance specifying a %G_TYPE_UCHAR property.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_uint:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecUInt instance specifying a %G_TYPE_UINT property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_uint64:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecUInt64 instance specifying a %G_TYPE_UINT64
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_ulong:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecULong instance specifying a %G_TYPE_ULONG
 * property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_unichar:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @default_value: default value for the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecUnichar instance specifying a %G_TYPE_UINT
 * property. #GValue structures for this property can be accessed with
 * g_value_set_uint() and g_value_get_uint().
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): a newly created parameter specification
 */


/**
 * g_param_spec_unref: (skip)
 * @pspec: a valid #GParamSpec
 *
 * Decrements the reference count of a @pspec.
 */


/**
 * g_param_spec_value_array: (skip)
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @element_spec: a #GParamSpec describing the elements contained in
 *  arrays of this property, may be %NULL
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecValueArray instance specifying a
 * %G_TYPE_VALUE_ARRAY property. %G_TYPE_VALUE_ARRAY is a
 * %G_TYPE_BOXED type, as such, #GValue structures for this property
 * can be accessed with g_value_set_boxed() and g_value_get_boxed().
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_variant:
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @type: a #GVariantType
 * @default_value: (allow-none) (transfer full): a #GVariant of type @type to
 *                 use as the default value, or %NULL
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecVariant instance specifying a #GVariant
 * property.
 *
 * If @default_value is floating, it is consumed.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: (transfer full): the newly created #GParamSpec
 * Since: 2.26
 */


/**
 * g_param_type_register_static:
 * @name: 0-terminated string used as the name of the new #GParamSpec type.
 * @pspec_info: The #GParamSpecTypeInfo for this #GParamSpec type.
 *
 * Registers @name as the name of a new static type derived from
 * #G_TYPE_PARAM. The type system uses the information contained in
 * the #GParamSpecTypeInfo structure pointed to by @info to manage the
 * #GParamSpec type and its instances.
 *
 * Returns: The new type identifier.
 */


/**
 * g_param_value_convert:
 * @pspec: a valid #GParamSpec
 * @src_value: souce #GValue
 * @dest_value: destination #GValue of correct type for @pspec
 * @strict_validation: %TRUE requires @dest_value to conform to @pspec
 * without modifications
 *
 * Transforms @src_value into @dest_value if possible, and then
 * validates @dest_value, in order for it to conform to @pspec.  If
 * @strict_validation is %TRUE this function will only succeed if the
 * transformed @dest_value complied to @pspec without modifications.
 *
 * See also g_value_type_transformable(), g_value_transform() and
 * g_param_value_validate().
 *
 * Returns: %TRUE if transformation and validation were successful,
 *  %FALSE otherwise and @dest_value is left untouched.
 */


/**
 * g_param_value_defaults:
 * @pspec: a valid #GParamSpec
 * @value: a #GValue of correct type for @pspec
 *
 * Checks whether @value contains the default value as specified in @pspec.
 *
 * Returns: whether @value contains the canonical default for this @pspec
 */


/**
 * g_param_value_set_default:
 * @pspec: a valid #GParamSpec
 * @value: a #GValue of correct type for @pspec
 *
 * Sets @value to its default value as specified in @pspec.
 */


/**
 * g_param_value_validate:
 * @pspec: a valid #GParamSpec
 * @value: a #GValue of correct type for @pspec
 *
 * Ensures that the contents of @value comply with the specifications
 * set out by @pspec. For example, a #GParamSpecInt might require
 * that integers stored in @value may not be smaller than -42 and not be
 * greater than +42. If @value contains an integer outside of this range,
 * it is modified accordingly, so the resulting value will fit into the
 * range -42 .. +42.
 *
 * Returns: whether modifying @value was necessary to ensure validity
 */


/**
 * g_param_values_cmp:
 * @pspec: a valid #GParamSpec
 * @value1: a #GValue of correct type for @pspec
 * @value2: a #GValue of correct type for @pspec
 *
 * Compares @value1 with @value2 according to @pspec, and return -1, 0 or +1,
 * if @value1 is found to be less than, equal to or greater than @value2,
 * respectively.
 *
 * Returns: -1, 0 or +1, for a less than, equal to or greater than result
 */


/**
 * g_pointer_type_register_static:
 * @name: the name of the new pointer type.
 *
 * Creates a new %G_TYPE_POINTER derived type id for a new
 * pointer type with name @name.
 *
 * Returns: a new %G_TYPE_POINTER derived type id for @name.
 */


/**
 * g_signal_accumulator_first_wins:
 * @ihint: standard #GSignalAccumulator parameter
 * @return_accu: standard #GSignalAccumulator parameter
 * @handler_return: standard #GSignalAccumulator parameter
 * @dummy: standard #GSignalAccumulator parameter
 *
 * A predefined #GSignalAccumulator for signals intended to be used as a
 * hook for application code to provide a particular value.  Usually
 * only one such value is desired and multiple handlers for the same
 * signal don't make much sense (except for the case of the default
 * handler defined in the class structure, in which case you will
 * usually want the signal connection to override the class handler).
 *
 * This accumulator will use the return value from the first signal
 * handler that is run as the return value for the signal and not run
 * any further handlers (ie: the first handler "wins").
 *
 * Returns: standard #GSignalAccumulator result
 * Since: 2.28
 */


/**
 * g_signal_accumulator_true_handled:
 * @ihint: standard #GSignalAccumulator parameter
 * @return_accu: standard #GSignalAccumulator parameter
 * @handler_return: standard #GSignalAccumulator parameter
 * @dummy: standard #GSignalAccumulator parameter
 *
 * A predefined #GSignalAccumulator for signals that return a
 * boolean values. The behavior that this accumulator gives is
 * that a return of %TRUE stops the signal emission: no further
 * callbacks will be invoked, while a return of %FALSE allows
 * the emission to continue. The idea here is that a %TRUE return
 * indicates that the callback <emphasis>handled</emphasis> the signal,
 * and no further handling is needed.
 *
 * Since: 2.4
 * Returns: standard #GSignalAccumulator result
 */


/**
 * g_signal_add_emission_hook:
 * @signal_id: the signal identifier, as returned by g_signal_lookup().
 * @detail: the detail on which to call the hook.
 * @hook_func: a #GSignalEmissionHook function.
 * @hook_data: user data for @hook_func.
 * @data_destroy: a #GDestroyNotify for @hook_data.
 *
 * Adds an emission hook for a signal, which will get called for any emission
 * of that signal, independent of the instance. This is possible only
 * for signals which don't have #G_SIGNAL_NO_HOOKS flag set.
 *
 * Returns: the hook id, for later use with g_signal_remove_emission_hook().
 */


/**
 * g_signal_chain_from_overridden:
 * @instance_and_params: (array): the argument list of the signal emission.
 *  The first element in the array is a #GValue for the instance the signal
 *  is being emitted on. The rest are any arguments to be passed to the signal.
 * @return_value: Location for the return value.
 *
 * Calls the original class closure of a signal. This function should only
 * be called from an overridden class closure; see
 * g_signal_override_class_closure() and
 * g_signal_override_class_handler().
 */


/**
 * g_signal_chain_from_overridden_handler: (skip)
 * @instance: the instance the signal is being emitted on.
 * @...: parameters to be passed to the parent class closure, followed by a
 *  location for the return value. If the return type of the signal
 *  is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Calls the original class closure of a signal. This function should
 * only be called from an overridden class closure; see
 * g_signal_override_class_closure() and
 * g_signal_override_class_handler().
 *
 * Since: 2.18
 */


/**
 * g_signal_connect_closure:
 * @instance: (type GObject.Object): the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @closure: the closure to connect.
 * @after: whether the handler should be called before or after the
 *  default handler of the signal.
 *
 * Connects a closure to a signal for a particular object.
 *
 * Returns: the handler id (always greater than 0 for successful connections)
 */


/**
 * g_signal_connect_closure_by_id:
 * @instance: (type GObject.Object): the instance to connect to.
 * @signal_id: the id of the signal.
 * @detail: the detail.
 * @closure: the closure to connect.
 * @after: whether the handler should be called before or after the
 *  default handler of the signal.
 *
 * Connects a closure to a signal for a particular object.
 *
 * Returns: the handler id (always greater than 0 for successful connections)
 */


/**
 * g_signal_connect_data:
 * @instance: (type GObject.Object): the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @c_handler: the #GCallback to connect.
 * @data: data to pass to @c_handler calls.
 * @destroy_data: a #GClosureNotify for @data.
 * @connect_flags: a combination of #GConnectFlags.
 *
 * Connects a #GCallback function to a signal for a particular object. Similar
 * to g_signal_connect(), but allows to provide a #GClosureNotify for the data
 * which will be called when the signal handler is disconnected and no longer
 * used. Specify @connect_flags if you need <literal>..._after()</literal> or
 * <literal>..._swapped()</literal> variants of this function.
 *
 * Returns: the handler id (always greater than 0 for successful connections)
 */


/**
 * g_signal_connect_object: (skip)
 * @instance: the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @c_handler: the #GCallback to connect.
 * @gobject: the object to pass as data to @c_handler.
 * @connect_flags: a combination of #GConnectFlags.
 *
 * This is similar to g_signal_connect_data(), but uses a closure which
 * ensures that the @gobject stays alive during the call to @c_handler
 * by temporarily adding a reference count to @gobject.
 *
 * When the @gobject is destroyed the signal handler will be automatically
 * disconnected.  Note that this is not currently threadsafe (ie:
 * emitting a signal while @gobject is being destroyed in another thread
 * is not safe).
 *
 * Returns: the handler id.
 */


/**
 * g_signal_emit:
 * @instance: (type GObject.Object): the instance the signal is being emitted on.
 * @signal_id: the signal id
 * @detail: the detail
 * @...: parameters to be passed to the signal, followed by a
 *  location for the return value. If the return type of the signal
 *  is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emit_by_name:
 * @instance: (type GObject.Object): the instance the signal is being emitted on.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @...: parameters to be passed to the signal, followed by a
 *  location for the return value. If the return type of the signal
 *  is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit_by_name() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emit_valist: (skip)
 * @instance: the instance the signal is being emitted on.
 * @signal_id: the signal id
 * @detail: the detail
 * @var_args: a list of parameters to be passed to the signal, followed by a
 *  location for the return value. If the return type of the signal
 *  is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit_valist() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emitv:
 * @instance_and_params: (array): argument list for the signal emission.
 *  The first element in the array is a #GValue for the instance the signal
 *  is being emitted on. The rest are any arguments to be passed to the signal.
 * @signal_id: the signal id
 * @detail: the detail
 * @return_value: Location to store the return value of the signal emission.
 *
 * Emits a signal.
 *
 * Note that g_signal_emitv() doesn't change @return_value if no handlers are
 * connected, in contrast to g_signal_emit() and g_signal_emit_valist().
 */


/**
 * g_signal_get_invocation_hint:
 * @instance: (type GObject.Object): the instance to query
 *
 * Returns the invocation hint of the innermost signal emission of instance.
 *
 * Returns: (transfer none): the invocation hint of the innermost signal  emission.
 */


/**
 * g_signal_handler_block:
 * @instance: (type GObject.Object): The instance to block the signal handler of.
 * @handler_id: Handler id of the handler to be blocked.
 *
 * Blocks a handler of an instance so it will not be called during any
 * signal emissions unless it is unblocked again. Thus "blocking" a
 * signal handler means to temporarily deactive it, a signal handler
 * has to be unblocked exactly the same amount of times it has been
 * blocked before to become active again.
 *
 * The @handler_id has to be a valid signal handler id, connected to a
 * signal of @instance.
 */


/**
 * g_signal_handler_disconnect:
 * @instance: (type GObject.Object): The instance to remove the signal handler from.
 * @handler_id: Handler id of the handler to be disconnected.
 *
 * Disconnects a handler from an instance so it will not be called during
 * any future or currently ongoing emissions of the signal it has been
 * connected to. The @handler_id becomes invalid and may be reused.
 *
 * The @handler_id has to be a valid signal handler id, connected to a
 * signal of @instance.
 */


/**
 * g_signal_handler_find:
 * @instance: (type GObject.Object): The instance owning the signal handler to be found.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func
 *  and/or @data the handler has to match.
 * @signal_id: Signal the handler has to be connected to.
 * @detail: Signal detail the handler has to be connected to.
 * @closure: (allow-none): The closure the handler will invoke.
 * @func: The C closure callback of the handler (useless for non-C closures).
 * @data: The closure data of the handler's closure.
 *
 * Finds the first signal handler that matches certain selection criteria.
 * The criteria mask is passed as an OR-ed combination of #GSignalMatchType
 * flags, and the criteria values are passed as arguments.
 * The match @mask has to be non-0 for successful matches.
 * If no handler was found, 0 is returned.
 *
 * Returns: A valid non-0 signal handler id for a successful match.
 */


/**
 * g_signal_handler_is_connected:
 * @instance: (type GObject.Object): The instance where a signal handler is sought.
 * @handler_id: the handler id.
 *
 * Returns whether @handler_id is the id of a handler connected to @instance.
 *
 * Returns: whether @handler_id identifies a handler connected to @instance.
 */


/**
 * g_signal_handler_unblock:
 * @instance: (type GObject.Object): The instance to unblock the signal handler of.
 * @handler_id: Handler id of the handler to be unblocked.
 *
 * Undoes the effect of a previous g_signal_handler_block() call.  A
 * blocked handler is skipped during signal emissions and will not be
 * invoked, unblocking it (for exactly the amount of times it has been
 * blocked before) reverts its "blocked" state, so the handler will be
 * recognized by the signal system and is called upon future or
 * currently ongoing signal emissions (since the order in which
 * handlers are called during signal emissions is deterministic,
 * whether the unblocked handler in question is called as part of a
 * currently ongoing emission depends on how far that emission has
 * proceeded yet).
 *
 * The @handler_id has to be a valid id of a signal handler that is
 * connected to a signal of @instance and is currently blocked.
 */


/**
 * g_signal_handlers_block_matched:
 * @instance: (type GObject.Object): The instance to block handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func
 *  and/or @data the handlers have to match.
 * @signal_id: Signal the handlers have to be connected to.
 * @detail: Signal detail the handlers have to be connected to.
 * @closure: (allow-none): The closure the handlers will invoke.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Blocks all handlers on an instance that match a certain selection criteria.
 * The criteria mask is passed as an OR-ed combination of #GSignalMatchType
 * flags, and the criteria values are passed as arguments.
 * Passing at least one of the %G_SIGNAL_MATCH_CLOSURE, %G_SIGNAL_MATCH_FUNC
 * or %G_SIGNAL_MATCH_DATA match flags is required for successful matches.
 * If no handlers were found, 0 is returned, the number of blocked handlers
 * otherwise.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_handlers_destroy:
 * @instance: (type GObject.Object): The instance where a signal handler is sought.
 */


/**
 * g_signal_handlers_disconnect_matched:
 * @instance: (type GObject.Object): The instance to remove handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func
 *  and/or @data the handlers have to match.
 * @signal_id: Signal the handlers have to be connected to.
 * @detail: Signal detail the handlers have to be connected to.
 * @closure: (allow-none): The closure the handlers will invoke.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Disconnects all handlers on an instance that match a certain
 * selection criteria. The criteria mask is passed as an OR-ed
 * combination of #GSignalMatchType flags, and the criteria values are
 * passed as arguments.  Passing at least one of the
 * %G_SIGNAL_MATCH_CLOSURE, %G_SIGNAL_MATCH_FUNC or
 * %G_SIGNAL_MATCH_DATA match flags is required for successful
 * matches.  If no handlers were found, 0 is returned, the number of
 * disconnected handlers otherwise.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_handlers_unblock_matched:
 * @instance: (type GObject.Object): The instance to unblock handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func
 *  and/or @data the handlers have to match.
 * @signal_id: Signal the handlers have to be connected to.
 * @detail: Signal detail the handlers have to be connected to.
 * @closure: (allow-none): The closure the handlers will invoke.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Unblocks all handlers on an instance that match a certain selection
 * criteria. The criteria mask is passed as an OR-ed combination of
 * #GSignalMatchType flags, and the criteria values are passed as arguments.
 * Passing at least one of the %G_SIGNAL_MATCH_CLOSURE, %G_SIGNAL_MATCH_FUNC
 * or %G_SIGNAL_MATCH_DATA match flags is required for successful matches.
 * If no handlers were found, 0 is returned, the number of unblocked handlers
 * otherwise. The match criteria should not apply to any handlers that are
 * not currently blocked.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_has_handler_pending:
 * @instance: (type GObject.Object): the object whose signal handlers are sought.
 * @signal_id: the signal id.
 * @detail: the detail.
 * @may_be_blocked: whether blocked handlers should count as match.
 *
 * Returns whether there are any handlers connected to @instance for the
 * given signal id and detail.
 *
 * One example of when you might use this is when the arguments to the
 * signal are difficult to compute. A class implementor may opt to not
 * emit the signal if no one is attached anyway, thus saving the cost
 * of building the arguments.
 *
 * Returns: %TRUE if a handler is connected to the signal, %FALSE
 *          otherwise.
 */


/**
 * g_signal_list_ids:
 * @itype: Instance or interface type.
 * @n_ids: Location to store the number of signal ids for @itype.
 *
 * Lists the signals by id that a certain instance or interface type
 * created. Further information about the signals can be acquired through
 * g_signal_query().
 *
 * Returns: (array length=n_ids): Newly allocated array of signal IDs.
 */


/**
 * g_signal_lookup:
 * @name: the signal's name.
 * @itype: the type that the signal operates on.
 *
 * Given the name of the signal and the type of object it connects to, gets
 * the signal's identifying integer. Emitting the signal by number is
 * somewhat faster than using the name each time.
 *
 * Also tries the ancestors of the given type.
 *
 * See g_signal_new() for details on allowed signal names.
 *
 * Returns: the signal's identifying number, or 0 if no signal was found.
 */


/**
 * g_signal_name:
 * @signal_id: the signal's identifying number.
 *
 * Given the signal's identifier, finds its name.
 *
 * Two different signals may have the same name, if they have differing types.
 *
 * Returns: the signal name, or %NULL if the signal number was invalid.
 */


/**
 * g_signal_new:
 * @signal_name: the name for the signal
 * @itype: the type this signal pertains to. It will also pertain to
 *  types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when
 *  the default handler is to be invoked. You should at least specify
 *  %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_offset: The offset of the function pointer in the class structure
 *  for this type. Used to invoke a class method generically. Pass 0 to
 *  not associate a class method slot with this signal.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter
 *  values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal
 *  without a return value.
 * @n_params: the number of parameter types to follow.
 * @...: a list of types, one for each parameter.
 *
 * Creates a new signal. (This is usually done in the class initializer.)
 *
 * A signal name consists of segments consisting of ASCII letters and
 * digits, separated by either the '-' or '_' character. The first
 * character of a signal name must be a letter. Names which violate these
 * rules lead to undefined behaviour of the GSignal system.
 *
 * When registering a signal and looking up a signal, either separator can
 * be used, but they cannot be mixed.
 *
 * If 0 is used for @class_offset subclasses cannot override the class handler
 * in their <code>class_init</code> method by doing
 * <code>super_class->signal_handler = my_signal_handler</code>. Instead they
 * will have to use g_signal_override_class_handler().
 *
 * If c_marshaller is %NULL, g_cclosure_marshal_generic() will be used as
 * the marshaller for this signal.
 *
 * Returns: the signal id
 */


/**
 * g_signal_new_class_handler:
 * @signal_name: the name for the signal
 * @itype: the type this signal pertains to. It will also pertain to
 *  types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when
 *  the default handler is to be invoked. You should at least specify
 *  %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_handler: a #GCallback which acts as class implementation of
 *  this signal. Used to invoke a class method generically. Pass %NULL to
 *  not associate a class method with this signal.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter
 *  values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal
 *  without a return value.
 * @n_params: the number of parameter types to follow.
 * @...: a list of types, one for each parameter.
 *
 * Creates a new signal. (This is usually done in the class initializer.)
 *
 * This is a variant of g_signal_new() that takes a C callback instead
 * off a class offset for the signal's class handler. This function
 * doesn't need a function pointer exposed in the class structure of
 * an object definition, instead the function pointer is passed
 * directly and can be overriden by derived classes with
 * g_signal_override_class_closure() or
 * g_signal_override_class_handler()and chained to with
 * g_signal_chain_from_overridden() or
 * g_signal_chain_from_overridden_handler().
 *
 * See g_signal_new() for information about signal names.
 *
 * If c_marshaller is %NULL @g_cclosure_marshal_generic will be used as
 * the marshaller for this signal.
 *
 * Returns: the signal id
 * Since: 2.18
 */


/**
 * g_signal_new_valist:
 * @signal_name: the name for the signal
 * @itype: the type this signal pertains to. It will also pertain to
 *  types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when
 *  the default handler is to be invoked. You should at least specify
 *  %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_closure: The closure to invoke on signal emission; may be %NULL.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter
 *  values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal
 *  without a return value.
 * @n_params: the number of parameter types in @args.
 * @args: va_list of #GType, one for each parameter.
 *
 * Creates a new signal. (This is usually done in the class initializer.)
 *
 * See g_signal_new() for details on allowed signal names.
 *
 * If c_marshaller is %NULL, g_cclosure_marshal_generic() will be used as
 * the marshaller for this signal.
 *
 * Returns: the signal id
 */


/**
 * g_signal_newv:
 * @signal_name: the name for the signal
 * @itype: the type this signal pertains to. It will also pertain to
 *     types which are derived from this type
 * @signal_flags: a combination of #GSignalFlags specifying detail of when
 *     the default handler is to be invoked. You should at least specify
 *     %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST
 * @class_closure: (allow-none): The closure to invoke on signal emission;
 *     may be %NULL
 * @accumulator: (allow-none): the accumulator for this signal; may be %NULL
 * @accu_data: user data for the @accumulator
 * @c_marshaller: (allow-none): the function to translate arrays of
 *     parameter values to signal emissions into C language callback
 *     invocations or %NULL
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal
 *     without a return value
 * @n_params: the length of @param_types
 * @param_types: (array length=n_params): an array of types, one for
 *     each parameter
 *
 * Creates a new signal. (This is usually done in the class initializer.)
 *
 * See g_signal_new() for details on allowed signal names.
 *
 * If c_marshaller is %NULL @g_cclosure_marshal_generic will be used as
 * the marshaller for this signal.
 *
 * Returns: the signal id
 */


/**
 * g_signal_override_class_closure:
 * @signal_id: the signal id
 * @instance_type: the instance type on which to override the class closure
 *  for the signal.
 * @class_closure: the closure.
 *
 * Overrides the class closure (i.e. the default handler) for the given signal
 * for emissions on instances of @instance_type. @instance_type must be derived
 * from the type to which the signal belongs.
 *
 * See g_signal_chain_from_overridden() and
 * g_signal_chain_from_overridden_handler() for how to chain up to the
 * parent class closure from inside the overridden one.
 */


/**
 * g_signal_override_class_handler:
 * @signal_name: the name for the signal
 * @instance_type: the instance type on which to override the class handler
 *  for the signal.
 * @class_handler: the handler.
 *
 * Overrides the class closure (i.e. the default handler) for the
 * given signal for emissions on instances of @instance_type with
 * callback @class_handler. @instance_type must be derived from the
 * type to which the signal belongs.
 *
 * See g_signal_chain_from_overridden() and
 * g_signal_chain_from_overridden_handler() for how to chain up to the
 * parent class closure from inside the overridden one.
 *
 * Since: 2.18
 */


/**
 * g_signal_parse_name:
 * @detailed_signal: a string of the form "signal-name::detail".
 * @itype: The interface/instance type that introduced "signal-name".
 * @signal_id_p: (out): Location to store the signal id.
 * @detail_p: (out): Location to store the detail quark.
 * @force_detail_quark: %TRUE forces creation of a #GQuark for the detail.
 *
 * Internal function to parse a signal name into its @signal_id
 * and @detail quark.
 *
 * Returns: Whether the signal name could successfully be parsed and @signal_id_p and @detail_p contain valid return values.
 */


/**
 * g_signal_query:
 * @signal_id: The signal id of the signal to query information for.
 * @query: (out caller-allocates): A user provided structure that is
 *  filled in with constant values upon success.
 *
 * Queries the signal system for in-depth information about a
 * specific signal. This function will fill in a user-provided
 * structure to hold signal-specific information. If an invalid
 * signal id is passed in, the @signal_id member of the #GSignalQuery
 * is 0. All members filled into the #GSignalQuery structure should
 * be considered constant and have to be left untouched.
 */


/**
 * g_signal_remove_emission_hook:
 * @signal_id: the id of the signal
 * @hook_id: the id of the emission hook, as returned by
 *  g_signal_add_emission_hook()
 *
 * Deletes an emission hook.
 */


/**
 * g_signal_stop_emission:
 * @instance: (type GObject.Object): the object whose signal handlers you wish to stop.
 * @signal_id: the signal identifier, as returned by g_signal_lookup().
 * @detail: the detail which the signal was emitted with.
 *
 * Stops a signal's current emission.
 *
 * This will prevent the default method from running, if the signal was
 * %G_SIGNAL_RUN_LAST and you connected normally (i.e. without the "after"
 * flag).
 *
 * Prints a warning if used on a signal which isn't being emitted.
 */


/**
 * g_signal_stop_emission_by_name:
 * @instance: (type GObject.Object): the object whose signal handlers you wish to stop.
 * @detailed_signal: a string of the form "signal-name::detail".
 *
 * Stops a signal's current emission.
 *
 * This is just like g_signal_stop_emission() except it will look up the
 * signal id for you.
 */


/**
 * g_signal_type_cclosure_new:
 * @itype: the #GType identifier of an interface or classed type
 * @struct_offset: the offset of the member function of @itype's class
 *  structure which is to be invoked by the new closure
 *
 * Creates a new closure which invokes the function found at the offset
 * @struct_offset in the class structure of the interface or classed type
 * identified by @itype.
 *
 * Returns: a new #GCClosure
 */


/**
 * g_source_set_closure:
 * @source: the source
 * @closure: a #GClosure
 *
 * Set the callback for a source as a #GClosure.
 *
 * If the source is not one of the standard GLib types, the @closure_callback
 * and @closure_marshal fields of the #GSourceFuncs structure must have been
 * filled in with pointers to appropriate functions.
 */


/**
 * g_source_set_dummy_callback:
 * @source: the source
 *
 * Sets a dummy callback for @source. The callback will do nothing, and
 * if the source expects a #gboolean return value, it will return %TRUE.
 * (If the source expects any other type of return value, it will return
 * a 0/%NULL value; whatever g_value_init() initializes a #GValue to for
 * that type.)
 *
 * If the source is not one of the standard GLib types, the
 * @closure_callback and @closure_marshal fields of the #GSourceFuncs
 * structure must have been filled in with pointers to appropriate
 * functions.
 */


/**
 * g_strdup_value_contents:
 * @value: #GValue which contents are to be described.
 *
 * Return a newly allocated string, which describes the contents of a
 * #GValue.  The main purpose of this function is to describe #GValue
 * contents for debugging output, the way in which the contents are
 * described may change between different GLib versions.
 *
 * Returns: Newly allocated string.
 */


/**
 * g_type_add_class_cache_func: (skip)
 * @cache_data: data to be passed to @cache_func
 * @cache_func: a #GTypeClassCacheFunc
 *
 * Adds a #GTypeClassCacheFunc to be called before the reference count of a
 * class goes from one to zero. This can be used to prevent premature class
 * destruction. All installed #GTypeClassCacheFunc functions will be chained
 * until one of them returns %TRUE. The functions have to check the class id
 * passed in to figure whether they actually want to cache the class of this
 * type, since all classes are routed through the same #GTypeClassCacheFunc
 * chain.
 */


/**
 * g_type_add_class_private:
 * @class_type: GType of an classed type.
 * @private_size: size of private structure.
 *
 * Registers a private class structure for a classed type;
 * when the class is allocated, the private structures for
 * the class and all of its parent types are allocated
 * sequentially in the same memory block as the public
 * structures. This function should be called in the
 * type's get_type() function after the type is registered.
 * The private structure can be retrieved using the
 * G_TYPE_CLASS_GET_PRIVATE() macro.
 *
 * Since: 2.24
 */


/**
 * g_type_add_interface_check: (skip)
 * @check_data: data to pass to @check_func
 * @check_func: function to be called after each interface
 *              is initialized.
 *
 * Adds a function to be called after an interface vtable is
 * initialized for any class (i.e. after the @interface_init member of
 * #GInterfaceInfo has been called).
 *
 * This function is useful when you want to check an invariant that
 * depends on the interfaces of a class. For instance, the
 * implementation of #GObject uses this facility to check that an
 * object implements all of the properties that are defined on its
 * interfaces.
 *
 * Since: 2.4
 */


/**
 * g_type_add_interface_dynamic:
 * @instance_type: the #GType value of an instantiable type.
 * @interface_type: the #GType value of an interface type.
 * @plugin: the #GTypePlugin structure to retrieve the #GInterfaceInfo from.
 *
 * Adds the dynamic @interface_type to @instantiable_type. The information
 * contained in the #GTypePlugin structure pointed to by @plugin
 * is used to manage the relationship.
 */


/**
 * g_type_add_interface_static:
 * @instance_type: #GType value of an instantiable type.
 * @interface_type: #GType value of an interface type.
 * @info: The #GInterfaceInfo structure for this
 *        (@instance_type, @interface_type) combination.
 *
 * Adds the static @interface_type to @instantiable_type.  The
 * information contained in the #GInterfaceInfo structure pointed to by
 * @info is used to manage the relationship.
 */


/**
 * g_type_check_instance:
 * @instance: A valid #GTypeInstance structure.
 *
 * Private helper function to aid implementation of the G_TYPE_CHECK_INSTANCE()
 * macro.
 *
 * Returns: %TRUE if @instance is valid, %FALSE otherwise.
 */


/**
 * g_type_children:
 * @type: The parent type.
 * @n_children: (out) (allow-none): Optional #guint pointer to contain
 *              the number of child types.
 *
 * Return a newly allocated and 0-terminated array of type IDs, listing the
 * child types of @type. The return value has to be g_free()ed after use.
 *
 * Returns: (array length=n_children) (transfer full): Newly allocated
 *          and 0-terminated array of child types.
 */


/**
 * g_type_class_add_private:
 * @g_class: class structure for an instantiatable type
 * @private_size: size of private structure.
 *
 * Registers a private structure for an instantiatable type.
 *
 * When an object is allocated, the private structures for
 * the type and all of its parent types are allocated
 * sequentially in the same memory block as the public
 * structures.
 *
 * Note that the accumulated size of the private structures of
 * a type and all its parent types cannot exceed 64 KiB.
 *
 * This function should be called in the type's class_init() function.
 * The private structure can be retrieved using the
 * G_TYPE_INSTANCE_GET_PRIVATE() macro.
 *
 * The following example shows attaching a private structure
 * <structname>MyObjectPrivate</structname> to an object
 * <structname>MyObject</structname> defined in the standard GObject
 * fashion.
 * type's class_init() function.
 * Note the use of a structure member "priv" to avoid the overhead
 * of repeatedly calling MY_OBJECT_GET_PRIVATE().
 *
 * |[
 * typedef struct _MyObject        MyObject;
 * typedef struct _MyObjectPrivate MyObjectPrivate;
 *
 * struct _MyObject {
 *  GObject parent;
 *
 *  MyObjectPrivate *priv;
 * };
 *
 * struct _MyObjectPrivate {
 *   int some_field;
 * };
 *
 * static void
 * my_object_class_init (MyObjectClass *klass)
 * {
 *   g_type_class_add_private (klass, sizeof (MyObjectPrivate));
 * }
 *
 * static void
 * my_object_init (MyObject *my_object)
 * {
 *   my_object->priv = G_TYPE_INSTANCE_GET_PRIVATE (my_object,
 *                                                  MY_TYPE_OBJECT,
 *                                                  MyObjectPrivate);
 * }
 *
 * static int
 * my_object_get_some_field (MyObject *my_object)
 * {
 *   MyObjectPrivate *priv;
 *
 *   g_return_val_if_fail (MY_IS_OBJECT (my_object), 0);
 *
 *   priv = my_object->priv;
 *
 *   return priv->some_field;
 * }
 * ]|
 *
 * Since: 2.4
 */


/**
 * g_type_class_get_instance_private_offset: (skip)
 * @g_class: a #GTypeClass
 *
 * Gets the offset of the private data for instances of @g_class.
 *
 * This is how many bytes you should add to the instance pointer of a
 * class in order to get the private data for the type represented by
 * @g_class.
 *
 * You can only call this function after you have registered a private
 * data area for @g_class using g_type_class_add_private().
 *
 * Returns: the offset, in bytes
 * Since: 2.38
 */


/**
 * g_type_class_peek:
 * @type: Type ID of a classed type.
 *
 * This function is essentially the same as g_type_class_ref(), except that
 * the classes reference count isn't incremented. As a consequence, this function
 * may return %NULL if the class of the type passed in does not currently
 * exist (hasn't been referenced before).
 *
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 *  structure for the given type ID or %NULL if the class does not
 *  currently exist.
 */


/**
 * g_type_class_peek_parent:
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to
 *  retrieve the parent class for.
 *
 * This is a convenience function often needed in class initializers.
 * It returns the class structure of the immediate parent type of the
 * class passed in.  Since derived classes hold a reference count on
 * their parent classes as long as they are instantiated, the returned
 * class will always exist. This function is essentially equivalent
 * to:
 *
 * <programlisting>
 * g_type_class_peek (g_type_parent (G_TYPE_FROM_CLASS (g_class)));
 * </programlisting>
 *
 * Returns: (type GObject.TypeClass) (transfer none): The parent class
 *  of @g_class.
 */


/**
 * g_type_class_peek_static:
 * @type: Type ID of a classed type.
 *
 * A more efficient version of g_type_class_peek() which works only for
 * static types.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 *  structure for the given type ID or %NULL if the class does not
 *  currently exist or is dynamically loaded.
 */


/**
 * g_type_class_ref:
 * @type: Type ID of a classed type.
 *
 * Increments the reference count of the class structure belonging to
 * @type. This function will demand-create the class if it doesn't
 * exist already.
 *
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 *  structure for the given type ID.
 */


/**
 * g_type_class_unref:
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to
 *  unreference.
 *
 * Decrements the reference count of the class structure being passed in.
 * Once the last reference count of a class has been released, classes
 * may be finalized by the type system, so further dereferencing of a
 * class pointer after g_type_class_unref() are invalid.
 */


/**
 * g_type_class_unref_uncached: (skip)
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to
 *  unreference.
 *
 * A variant of g_type_class_unref() for use in #GTypeClassCacheFunc
 * implementations. It unreferences a class without consulting the chain
 * of #GTypeClassCacheFunc<!-- -->s, avoiding the recursion which would occur
 * otherwise.
 */


/**
 * g_type_create_instance: (skip)
 * @type: An instantiatable type to create an instance for.
 *
 * Creates and initializes an instance of @type if @type is valid and
 * can be instantiated. The type system only performs basic allocation
 * and structure setups for instances: actual instance creation should
 * happen through functions supplied by the type's fundamental type
 * implementation.  So use of g_type_create_instance() is reserved for
 * implementators of fundamental types only. E.g. instances of the
 * #GObject hierarchy should be created via g_object_new() and
 * <emphasis>never</emphasis> directly through
 * g_type_create_instance() which doesn't handle things like singleton
 * objects or object construction.  Note: Do <emphasis>not</emphasis>
 * use this function, unless you're implementing a fundamental
 * type. Also language bindings should <emphasis>not</emphasis> use
 * this function but g_object_new() instead.
 *
 * Returns: An allocated and initialized instance, subject to further
 *  treatment by the fundamental type implementation.
 */


/**
 * g_type_default_interface_peek:
 * @g_type: an interface type
 *
 * If the interface type @g_type is currently in use, returns its
 * default interface vtable.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeInterface) (transfer none): the default
 *  vtable for the interface, or %NULL if the type is not currently in
 *  use.
 */


/**
 * g_type_default_interface_ref:
 * @g_type: an interface type
 *
 * Increments the reference count for the interface type @g_type,
 * and returns the default interface vtable for the type.
 *
 * If the type is not currently in use, then the default vtable
 * for the type will be created and initalized by calling
 * the base interface init and default vtable init functions for
 * the type (the @<structfield>base_init</structfield>
 * and <structfield>class_init</structfield> members of #GTypeInfo).
 * Calling g_type_default_interface_ref() is useful when you
 * want to make sure that signals and properties for an interface
 * have been installed.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeInterface) (transfer none): the default
 *  vtable for the interface; call g_type_default_interface_unref()
 *  when you are done using the interface.
 */


/**
 * g_type_default_interface_unref:
 * @g_iface: (type GObject.TypeInterface): the default vtable
 *  structure for a interface, as returned by
 *  g_type_default_interface_ref()
 *
 * Decrements the reference count for the type corresponding to the
 * interface default vtable @g_iface. If the type is dynamic, then
 * when no one is using the interface and all references have
 * been released, the finalize function for the interface's default
 * vtable (the <structfield>class_finalize</structfield> member of
 * #GTypeInfo) will be called.
 *
 * Since: 2.4
 */


/**
 * g_type_depth:
 * @type: A #GType value.
 *
 * Returns the length of the ancestry of the passed in type. This
 * includes the type itself, so that e.g. a fundamental type has depth 1.
 *
 * Returns: The depth of @type.
 */


/**
 * g_type_ensure:
 * @type: a #GType.
 *
 * Ensures that the indicated @type has been registered with the
 * type system, and its _class_init() method has been run.
 *
 * In theory, simply calling the type's _get_type() method (or using
 * the corresponding macro) is supposed take care of this. However,
 * _get_type() methods are often marked %G_GNUC_CONST for performance
 * reasons, even though this is technically incorrect (since
 * %G_GNUC_CONST requires that the function not have side effects,
 * which _get_type() methods do on the first call). As a result, if
 * you write a bare call to a _get_type() macro, it may get optimized
 * out by the compiler. Using g_type_ensure() guarantees that the
 * type's _get_type() method is called.
 *
 * Since: 2.34
 */


/**
 * g_type_free_instance:
 * @instance: an instance of a type.
 *
 * Frees an instance of a type, returning it to the instance pool for
 * the type, if there is one.
 *
 * Like g_type_create_instance(), this function is reserved for
 * implementors of fundamental types.
 */


/**
 * g_type_from_name:
 * @name: Type name to lookup.
 *
 * Lookup the type ID from a given type name, returning 0 if no type
 * has been registered under this name (this is the preferred method
 * to find out by name whether a specific type has been registered
 * yet).
 *
 * Returns: Corresponding type ID or 0.
 */


/**
 * g_type_fundamental:
 * @type_id: valid type ID
 *
 * Internal function, used to extract the fundamental type ID portion.
 * use G_TYPE_FUNDAMENTAL() instead.
 *
 * Returns: fundamental type ID
 */


/**
 * g_type_fundamental_next:
 *
 * Returns the next free fundamental type id which can be used to
 * register a new fundamental type with g_type_register_fundamental().
 * The returned type ID represents the highest currently registered
 * fundamental type identifier.
 *
 * Returns: The nextmost fundamental type ID to be registered,
 *          or 0 if the type system ran out of fundamental type IDs.
 */


/**
 * g_type_get_plugin:
 * @type: The #GType to retrieve the plugin for.
 *
 * Returns the #GTypePlugin structure for @type or
 * %NULL if @type does not have a #GTypePlugin structure.
 *
 * Returns: (transfer none): The corresponding plugin if @type is a
 *          dynamic type, %NULL otherwise.
 */


/**
 * g_type_get_qdata:
 * @type: a #GType
 * @quark: a #GQuark id to identify the data
 *
 * Obtains data which has previously been attached to @type
 * with g_type_set_qdata().
 *
 * Note that this does not take subtyping into account; data
 * attached to one type with g_type_set_qdata() cannot
 * be retrieved from a subtype using g_type_get_qdata().
 *
 * Returns: (transfer none): the data, or %NULL if no data was found
 */


/**
 * g_type_get_type_registration_serial:
 *
 * Returns an opaque serial number that represents the state of the set of
 * registered types. Any time a type is registered this serial changes,
 * which means you can cache information based on type lookups (such as
 * g_type_from_name()) and know if the cache is still valid at a later
 * time by comparing the current serial with the one at the type lookup.
 *
 * Since: 2.36
 * Returns: An unsigned int, representing the state of type registrations.
 */


/**
 * g_type_init:
 *
 * This function used to initialise the type system.  Since GLib 2.36,
 * the type system is initialised automatically and this function does
 * nothing.
 *
 * Deprecated: 2.36: the type system is now initialised automatically
 */


/**
 * g_type_init_with_debug_flags:
 * @debug_flags: Bitwise combination of #GTypeDebugFlags values for
 *               debugging purposes.
 *
 * This function used to initialise the type system with debugging
 * flags.  Since GLib 2.36, the type system is initialised automatically
 * and this function does nothing.
 *
 * If you need to enable debugging features, use the GOBJECT_DEBUG
 * environment variable.
 *
 * Deprecated: 2.36: the type system is now initialised automatically
 */


/**
 * g_type_interface_add_prerequisite:
 * @interface_type: #GType value of an interface type.
 * @prerequisite_type: #GType value of an interface or instantiatable type.
 *
 * Adds @prerequisite_type to the list of prerequisites of @interface_type.
 * This means that any type implementing @interface_type must also implement
 * @prerequisite_type. Prerequisites can be thought of as an alternative to
 * interface derivation (which GType doesn't support). An interface can have
 * at most one instantiatable prerequisite type.
 */


/**
 * g_type_interface_get_plugin:
 * @instance_type: the #GType value of an instantiatable type.
 * @interface_type: the #GType value of an interface type.
 *
 * Returns the #GTypePlugin structure for the dynamic interface
 * @interface_type which has been added to @instance_type, or %NULL if
 * @interface_type has not been added to @instance_type or does not
 * have a #GTypePlugin structure. See g_type_add_interface_dynamic().
 *
 * Returns: (transfer none): the #GTypePlugin for the dynamic
 *          interface @interface_type of @instance_type.
 */


/**
 * g_type_interface_peek:
 * @instance_class: (type GObject.TypeClass): A #GTypeClass structure.
 * @iface_type: An interface ID which this class conforms to.
 *
 * Returns the #GTypeInterface structure of an interface to which the
 * passed in class conforms.
 *
 * Returns: (type GObject.TypeInterface) (transfer none): The GTypeInterface
 *  structure of iface_type if implemented by @instance_class, %NULL
 *  otherwise
 */


/**
 * g_type_interface_peek_parent:
 * @g_iface: (type GObject.TypeInterface): A #GTypeInterface structure.
 *
 * Returns the corresponding #GTypeInterface structure of the parent type
 * of the instance type to which @g_iface belongs. This is useful when
 * deriving the implementation of an interface from the parent type and
 * then possibly overriding some methods.
 *
 * Returns: (transfer none) (type GObject.TypeInterface): The
 *  corresponding #GTypeInterface structure of the parent type of the
 *  instance type to which @g_iface belongs, or %NULL if the parent
 *  type doesn't conform to the interface.
 */


/**
 * g_type_interface_prerequisites:
 * @interface_type: an interface type
 * @n_prerequisites: (out) (allow-none): location to return the number
 *                   of prerequisites, or %NULL
 *
 * Returns the prerequisites of an interfaces type.
 *
 * Since: 2.2
 * Returns: (array length=n_prerequisites) (transfer full): a
 *          newly-allocated zero-terminated array of #GType containing
 *          the prerequisites of @interface_type
 */


/**
 * g_type_interfaces:
 * @type: The type to list interface types for.
 * @n_interfaces: (out) (allow-none): Optional #guint pointer to
 *                contain the number of interface types.
 *
 * Return a newly allocated and 0-terminated array of type IDs, listing the
 * interface types that @type conforms to. The return value has to be
 * g_free()ed after use.
 *
 * Returns: (array length=n_interfaces) (transfer full): Newly
 *          allocated and 0-terminated array of interface types.
 */


/**
 * g_type_is_a:
 * @type: Type to check anchestry for.
 * @is_a_type: Possible anchestor of @type or interface @type could conform to.
 *
 * If @is_a_type is a derivable type, check whether @type is a
 * descendant of @is_a_type.  If @is_a_type is an interface, check
 * whether @type conforms to it.
 *
 * Returns: %TRUE if @type is_a @is_a_type holds true.
 */


/**
 * g_type_module_add_interface:
 * @module: a #GTypeModule
 * @instance_type: type to which to add the interface.
 * @interface_type: interface type to add
 * @interface_info: type information structure
 *
 * Registers an additional interface for a type, whose interface lives
 * in the given type plugin. If the interface was already registered
 * for the type in this plugin, nothing will be done.
 *
 * As long as any instances of the type exist, the type plugin will
 * not be unloaded.
 */


/**
 * g_type_module_register_enum:
 * @module: a #GTypeModule
 * @name: name for the type
 * @const_static_values: an array of #GEnumValue structs for the
 *                       possible enumeration values. The array is
 *                       terminated by a struct with all members being
 *                       0.
 *
 * Looks up or registers an enumeration that is implemented with a particular
 * type plugin. If a type with name @type_name was previously registered,
 * the #GType identifier for the type is returned, otherwise the type
 * is newly registered, and the resulting #GType identifier returned.
 *
 * As long as any instances of the type exist, the type plugin will
 * not be unloaded.
 *
 * Since: 2.6
 * Returns: the new or existing type ID
 */


/**
 * g_type_module_register_flags:
 * @module: a #GTypeModule
 * @name: name for the type
 * @const_static_values: an array of #GFlagsValue structs for the
 *                       possible flags values. The array is
 *                       terminated by a struct with all members being
 *                       0.
 *
 * Looks up or registers a flags type that is implemented with a particular
 * type plugin. If a type with name @type_name was previously registered,
 * the #GType identifier for the type is returned, otherwise the type
 * is newly registered, and the resulting #GType identifier returned.
 *
 * As long as any instances of the type exist, the type plugin will
 * not be unloaded.
 *
 * Since: 2.6
 * Returns: the new or existing type ID
 */


/**
 * g_type_module_register_type:
 * @module: a #GTypeModule
 * @parent_type: the type for the parent class
 * @type_name: name for the type
 * @type_info: type information structure
 * @flags: flags field providing details about the type
 *
 * Looks up or registers a type that is implemented with a particular
 * type plugin. If a type with name @type_name was previously registered,
 * the #GType identifier for the type is returned, otherwise the type
 * is newly registered, and the resulting #GType identifier returned.
 *
 * When reregistering a type (typically because a module is unloaded
 * then reloaded, and reinitialized), @module and @parent_type must
 * be the same as they were previously.
 *
 * As long as any instances of the type exist, the type plugin will
 * not be unloaded.
 *
 * Returns: the new or existing type ID
 */


/**
 * g_type_module_set_name:
 * @module: a #GTypeModule.
 * @name: a human-readable name to use in error messages.
 *
 * Sets the name for a #GTypeModule
 */


/**
 * g_type_module_unuse:
 * @module: a #GTypeModule
 *
 * Decreases the use count of a #GTypeModule by one. If the
 * result is zero, the module will be unloaded. (However, the
 * #GTypeModule will not be freed, and types associated with the
 * #GTypeModule are not unregistered. Once a #GTypeModule is
 * initialized, it must exist forever.)
 */


/**
 * g_type_module_use:
 * @module: a #GTypeModule
 *
 * Increases the use count of a #GTypeModule by one. If the
 * use count was zero before, the plugin will be loaded.
 * If loading the plugin fails, the use count is reset to
 * its prior value.
 *
 * Returns: %FALSE if the plugin needed to be loaded and
 *  loading the plugin failed.
 */


/**
 * g_type_name:
 * @type: Type to return name for.
 *
 * Get the unique name that is assigned to a type ID.  Note that this
 * function (like all other GType API) cannot cope with invalid type
 * IDs. %G_TYPE_INVALID may be passed to this function, as may be any
 * other validly registered type ID, but randomized type IDs should
 * not be passed in and will most likely lead to a crash.
 *
 * Returns: Static type name or %NULL.
 */


/**
 * g_type_next_base:
 * @leaf_type: Descendant of @root_type and the type to be returned.
 * @root_type: Immediate parent of the returned type.
 *
 * Given a @leaf_type and a @root_type which is contained in its
 * anchestry, return the type that @root_type is the immediate parent
 * of.  In other words, this function determines the type that is
 * derived directly from @root_type which is also a base class of
 * @leaf_type.  Given a root type and a leaf type, this function can
 * be used to determine the types and order in which the leaf type is
 * descended from the root type.
 *
 * Returns: Immediate child of @root_type and anchestor of @leaf_type.
 */


/**
 * g_type_parent:
 * @type: The derived type.
 *
 * Return the direct parent type of the passed in type.  If the passed
 * in type has no parent, i.e. is a fundamental type, 0 is returned.
 *
 * Returns: The parent type.
 */


/**
 * g_type_plugin_complete_interface_info:
 * @plugin: the #GTypePlugin
 * @instance_type: the #GType of an instantiable type to which the interface
 *  is added
 * @interface_type: the #GType of the interface whose info is completed
 * @info: the #GInterfaceInfo to fill in
 *
 * Calls the @complete_interface_info function from the
 * #GTypePluginClass of @plugin. There should be no need to use this
 * function outside of the GObject type system itself.
 */


/**
 * g_type_plugin_complete_type_info:
 * @plugin: a #GTypePlugin
 * @g_type: the #GType whose info is completed
 * @info: the #GTypeInfo struct to fill in
 * @value_table: the #GTypeValueTable to fill in
 *
 * Calls the @complete_type_info function from the #GTypePluginClass of @plugin.
 * There should be no need to use this function outside of the GObject
 * type system itself.
 */


/**
 * g_type_plugin_unuse:
 * @plugin: a #GTypePlugin
 *
 * Calls the @unuse_plugin function from the #GTypePluginClass of
 * @plugin.  There should be no need to use this function outside of
 * the GObject type system itself.
 */


/**
 * g_type_plugin_use:
 * @plugin: a #GTypePlugin
 *
 * Calls the @use_plugin function from the #GTypePluginClass of
 * @plugin.  There should be no need to use this function outside of
 * the GObject type system itself.
 */


/**
 * g_type_qname:
 * @type: Type to return quark of type name for.
 *
 * Get the corresponding quark of the type IDs name.
 *
 * Returns: The type names quark or 0.
 */


/**
 * g_type_query:
 * @type: the #GType value of a static, classed type.
 * @query: (out caller-allocates): A user provided structure that is
 *         filled in with constant values upon success.
 *
 * Queries the type system for information about a specific type.
 * This function will fill in a user-provided structure to hold
 * type-specific information. If an invalid #GType is passed in, the
 * @type member of the #GTypeQuery is 0. All members filled into the
 * #GTypeQuery structure should be considered constant and have to be
 * left untouched.
 */


/**
 * g_type_register_dynamic:
 * @parent_type: Type from which this type will be derived.
 * @type_name: 0-terminated string used as the name of the new type.
 * @plugin: The #GTypePlugin structure to retrieve the #GTypeInfo from.
 * @flags: Bitwise combination of #GTypeFlags values.
 *
 * Registers @type_name as the name of a new dynamic type derived from
 * @parent_type.  The type system uses the information contained in the
 * #GTypePlugin structure pointed to by @plugin to manage the type and its
 * instances (if not abstract).  The value of @flags determines the nature
 * (e.g. abstract or not) of the type.
 *
 * Returns: The new type identifier or #G_TYPE_INVALID if registration failed.
 */


/**
 * g_type_register_fundamental:
 * @type_id: A predefined type identifier.
 * @type_name: 0-terminated string used as the name of the new type.
 * @info: The #GTypeInfo structure for this type.
 * @finfo: The #GTypeFundamentalInfo structure for this type.
 * @flags: Bitwise combination of #GTypeFlags values.
 *
 * Registers @type_id as the predefined identifier and @type_name as the
 * name of a fundamental type. If @type_id is already registered, or a type
 * named @type_name is already registered, the behaviour is undefined. The type
 * system uses the information contained in the #GTypeInfo structure pointed to
 * by @info and the #GTypeFundamentalInfo structure pointed to by @finfo to
 * manage the type and its instances. The value of @flags determines additional
 * characteristics of the fundamental type.
 *
 * Returns: The predefined type identifier.
 */


/**
 * g_type_register_static:
 * @parent_type: Type from which this type will be derived.
 * @type_name: 0-terminated string used as the name of the new type.
 * @info: The #GTypeInfo structure for this type.
 * @flags: Bitwise combination of #GTypeFlags values.
 *
 * Registers @type_name as the name of a new static type derived from
 * @parent_type.  The type system uses the information contained in the
 * #GTypeInfo structure pointed to by @info to manage the type and its
 * instances (if not abstract).  The value of @flags determines the nature
 * (e.g. abstract or not) of the type.
 *
 * Returns: The new type identifier.
 */


/**
 * g_type_register_static_simple: (skip)
 * @parent_type: Type from which this type will be derived.
 * @type_name: 0-terminated string used as the name of the new type.
 * @class_size: Size of the class structure (see #GTypeInfo)
 * @class_init: Location of the class initialization function (see #GTypeInfo)
 * @instance_size: Size of the instance structure (see #GTypeInfo)
 * @instance_init: Location of the instance initialization function (see #GTypeInfo)
 * @flags: Bitwise combination of #GTypeFlags values.
 *
 * Registers @type_name as the name of a new static type derived from
 * @parent_type.  The value of @flags determines the nature (e.g.
 * abstract or not) of the type. It works by filling a #GTypeInfo
 * struct and calling g_type_register_static().
 *
 * Since: 2.12
 * Returns: The new type identifier.
 */


/**
 * g_type_remove_class_cache_func: (skip)
 * @cache_data: data that was given when adding @cache_func
 * @cache_func: a #GTypeClassCacheFunc
 *
 * Removes a previously installed #GTypeClassCacheFunc. The cache
 * maintained by @cache_func has to be empty when calling
 * g_type_remove_class_cache_func() to avoid leaks.
 */


/**
 * g_type_remove_interface_check: (skip)
 * @check_data: callback data passed to g_type_add_interface_check()
 * @check_func: callback function passed to g_type_add_interface_check()
 *
 * Removes an interface check function added with
 * g_type_add_interface_check().
 *
 * Since: 2.4
 */


/**
 * g_type_set_qdata:
 * @type: a #GType
 * @quark: a #GQuark id to identify the data
 * @data: the data
 *
 * Attaches arbitrary data to a type.
 */


/**
 * g_type_value_table_peek: (skip)
 * @type: A #GType value.
 *
 * Returns the location of the #GTypeValueTable associated with @type.
 * <emphasis>Note that this function should only be used from source code
 * that implements or has internal knowledge of the implementation of
 * @type.</emphasis>
 *
 * Returns: Location of the #GTypeValueTable associated with @type or
 *  %NULL if there is no #GTypeValueTable associated with @type.
 */


/**
 * g_value_array_append:
 * @value_array: #GValueArray to add an element to
 * @value: (allow-none): #GValue to copy into #GValueArray, or %NULL
 *
 * Insert a copy of @value as last element of @value_array. If @value is
 * %NULL, an uninitialized value is appended.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_append_val() instead.
 */


/**
 * g_value_array_copy:
 * @value_array: #GValueArray to copy
 *
 * Construct an exact copy of a #GValueArray by duplicating all its
 * contents.
 *
 * Returns: (transfer full): Newly allocated copy of #GValueArray
 * Deprecated: 2.32: Use #GArray and g_array_ref() instead.
 */


/**
 * g_value_array_free:
 * @value_array: #GValueArray to free
 *
 * Free a #GValueArray including its contents.
 *
 * Deprecated: 2.32: Use #GArray and g_array_unref() instead.
 */


/**
 * g_value_array_get_nth:
 * @value_array: #GValueArray to get a value from
 * @index_: index of the value of interest
 *
 * Return a pointer to the value at @index_ containd in @value_array.
 *
 * Returns: (transfer none): pointer to a value at @index_ in @value_array
 * Deprecated: 2.32: Use g_array_index() instead.
 */


/**
 * g_value_array_insert:
 * @value_array: #GValueArray to add an element to
 * @index_: insertion position, must be &lt;= value_array-&gt;n_values
 * @value: (allow-none): #GValue to copy into #GValueArray, or %NULL
 *
 * Insert a copy of @value at specified position into @value_array. If @value
 * is %NULL, an uninitialized value is inserted.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_insert_val() instead.
 */


/**
 * g_value_array_new:
 * @n_prealloced: number of values to preallocate space for
 *
 * Allocate and initialize a new #GValueArray, optionally preserve space
 * for @n_prealloced elements. New arrays always contain 0 elements,
 * regardless of the value of @n_prealloced.
 *
 * Returns: a newly allocated #GValueArray with 0 values
 * Deprecated: 2.32: Use #GArray and g_array_sized_new() instead.
 */


/**
 * g_value_array_prepend:
 * @value_array: #GValueArray to add an element to
 * @value: (allow-none): #GValue to copy into #GValueArray, or %NULL
 *
 * Insert a copy of @value as first element of @value_array. If @value is
 * %NULL, an uninitialized value is prepended.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_prepend_val() instead.
 */


/**
 * g_value_array_remove:
 * @value_array: #GValueArray to remove an element from
 * @index_: position of value to remove, which must be less than
 *          <code>value_array-><link
 *          linkend="GValueArray.n-values">n_values</link></code>
 *
 * Remove the value at position @index_ from @value_array.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_remove_index() instead.
 */


/**
 * g_value_array_sort:
 * @value_array: #GValueArray to sort
 * @compare_func: (scope call): function to compare elements
 *
 * Sort @value_array using @compare_func to compare the elements according to
 * the semantics of #GCompareFunc.
 *
 * The current implementation uses the same sorting algorithm as standard
 * C qsort() function.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_sort().
 */


/**
 * g_value_array_sort_with_data: (rename-to g_value_array_sort)
 * @value_array: #GValueArray to sort
 * @compare_func: (scope call): function to compare elements
 * @user_data: (closure): extra data argument provided for @compare_func
 *
 * Sort @value_array using @compare_func to compare the elements according
 * to the semantics of #GCompareDataFunc.
 *
 * The current implementation uses the same sorting algorithm as standard
 * C qsort() function.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_sort_with_data().
 */


/**
 * g_value_copy:
 * @src_value: An initialized #GValue structure.
 * @dest_value: An initialized #GValue structure of the same type as @src_value.
 *
 * Copies the value of @src_value into @dest_value.
 */


/**
 * g_value_dup_boxed: (skip)
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 *
 * Get the contents of a %G_TYPE_BOXED derived #GValue.  Upon getting,
 * the boxed value is duplicated and needs to be later freed with
 * g_boxed_free(), e.g. like: g_boxed_free (G_VALUE_TYPE (@value),
 * return_value);
 *
 * Returns: boxed contents of @value
 */


/**
 * g_value_dup_object:
 * @value: a valid #GValue whose type is derived from %G_TYPE_OBJECT
 *
 * Get the contents of a %G_TYPE_OBJECT derived #GValue, increasing
 * its reference count. If the contents of the #GValue are %NULL, then
 * %NULL will be returned.
 *
 * Returns: (type GObject.Object) (transfer full): object content of @value,
 *          should be unreferenced when no longer needed.
 */


/**
 * g_value_dup_param: (skip)
 * @value: a valid #GValue whose type is derived from %G_TYPE_PARAM
 *
 * Get the contents of a %G_TYPE_PARAM #GValue, increasing its
 * reference count.
 *
 * Returns: #GParamSpec content of @value, should be unreferenced when
 *          no longer needed.
 */


/**
 * g_value_dup_string:
 * @value: a valid #GValue of type %G_TYPE_STRING
 *
 * Get a copy the contents of a %G_TYPE_STRING #GValue.
 *
 * Returns: a newly allocated copy of the string content of @value
 */


/**
 * g_value_dup_variant:
 * @value: a valid #GValue of type %G_TYPE_VARIANT
 *
 * Get the contents of a variant #GValue, increasing its refcount.
 *
 * Returns: variant contents of @value, should be unrefed using
 *   g_variant_unref() when no longer needed
 * Since: 2.26
 */


/**
 * g_value_fits_pointer:
 * @value: An initialized #GValue structure.
 *
 * Determines if @value will fit inside the size of a pointer value.
 * This is an internal function introduced mainly for C marshallers.
 *
 * Returns: %TRUE if @value will fit inside a pointer value.
 */


/**
 * g_value_get_boolean:
 * @value: a valid #GValue of type %G_TYPE_BOOLEAN
 *
 * Get the contents of a %G_TYPE_BOOLEAN #GValue.
 *
 * Returns: boolean contents of @value
 */


/**
 * g_value_get_boxed:
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 *
 * Get the contents of a %G_TYPE_BOXED derived #GValue.
 *
 * Returns: (transfer none): boxed contents of @value
 */


/**
 * g_value_get_char:
 * @value: a valid #GValue of type %G_TYPE_CHAR
 *
 * Do not use this function; it is broken on platforms where the %char
 * type is unsigned, such as ARM and PowerPC.  See g_value_get_schar().
 *
 * Get the contents of a %G_TYPE_CHAR #GValue.
 *
 * Returns: character contents of @value
 * Deprecated: 2.32: This function's return type is broken, see g_value_get_schar()
 */


/**
 * g_value_get_double:
 * @value: a valid #GValue of type %G_TYPE_DOUBLE
 *
 * Get the contents of a %G_TYPE_DOUBLE #GValue.
 *
 * Returns: double contents of @value
 */


/**
 * g_value_get_enum:
 * @value: a valid #GValue whose type is derived from %G_TYPE_ENUM
 *
 * Get the contents of a %G_TYPE_ENUM #GValue.
 *
 * Returns: enum contents of @value
 */


/**
 * g_value_get_flags:
 * @value: a valid #GValue whose type is derived from %G_TYPE_FLAGS
 *
 * Get the contents of a %G_TYPE_FLAGS #GValue.
 *
 * Returns: flags contents of @value
 */


/**
 * g_value_get_float:
 * @value: a valid #GValue of type %G_TYPE_FLOAT
 *
 * Get the contents of a %G_TYPE_FLOAT #GValue.
 *
 * Returns: float contents of @value
 */


/**
 * g_value_get_gtype:
 * @value: a valid #GValue of type %G_TYPE_GTYPE
 *
 * Get the contents of a %G_TYPE_GTYPE #GValue.
 *
 * Since: 2.12
 * Returns: the #GType stored in @value
 */


/**
 * g_value_get_int:
 * @value: a valid #GValue of type %G_TYPE_INT
 *
 * Get the contents of a %G_TYPE_INT #GValue.
 *
 * Returns: integer contents of @value
 */


/**
 * g_value_get_int64:
 * @value: a valid #GValue of type %G_TYPE_INT64
 *
 * Get the contents of a %G_TYPE_INT64 #GValue.
 *
 * Returns: 64bit integer contents of @value
 */


/**
 * g_value_get_long:
 * @value: a valid #GValue of type %G_TYPE_LONG
 *
 * Get the contents of a %G_TYPE_LONG #GValue.
 *
 * Returns: long integer contents of @value
 */


/**
 * g_value_get_object:
 * @value: a valid #GValue of %G_TYPE_OBJECT derived type
 *
 * Get the contents of a %G_TYPE_OBJECT derived #GValue.
 *
 * Returns: (type GObject.Object) (transfer none): object contents of @value
 */


/**
 * g_value_get_param:
 * @value: a valid #GValue whose type is derived from %G_TYPE_PARAM
 *
 * Get the contents of a %G_TYPE_PARAM #GValue.
 *
 * Returns: (transfer none): #GParamSpec content of @value
 */


/**
 * g_value_get_pointer:
 * @value: a valid #GValue of %G_TYPE_POINTER
 *
 * Get the contents of a pointer #GValue.
 *
 * Returns: (transfer none): pointer contents of @value
 */


/**
 * g_value_get_schar:
 * @value: a valid #GValue of type %G_TYPE_CHAR
 *
 * Get the contents of a %G_TYPE_CHAR #GValue.
 *
 * Returns: signed 8 bit integer contents of @value
 * Since: 2.32
 */


/**
 * g_value_get_string:
 * @value: a valid #GValue of type %G_TYPE_STRING
 *
 * Get the contents of a %G_TYPE_STRING #GValue.
 *
 * Returns: string content of @value
 */


/**
 * g_value_get_uchar:
 * @value: a valid #GValue of type %G_TYPE_UCHAR
 *
 * Get the contents of a %G_TYPE_UCHAR #GValue.
 *
 * Returns: unsigned character contents of @value
 */


/**
 * g_value_get_uint:
 * @value: a valid #GValue of type %G_TYPE_UINT
 *
 * Get the contents of a %G_TYPE_UINT #GValue.
 *
 * Returns: unsigned integer contents of @value
 */


/**
 * g_value_get_uint64:
 * @value: a valid #GValue of type %G_TYPE_UINT64
 *
 * Get the contents of a %G_TYPE_UINT64 #GValue.
 *
 * Returns: unsigned 64bit integer contents of @value
 */


/**
 * g_value_get_ulong:
 * @value: a valid #GValue of type %G_TYPE_ULONG
 *
 * Get the contents of a %G_TYPE_ULONG #GValue.
 *
 * Returns: unsigned long integer contents of @value
 */


/**
 * g_value_get_variant:
 * @value: a valid #GValue of type %G_TYPE_VARIANT
 *
 * Get the contents of a variant #GValue.
 *
 * Returns: variant contents of @value
 * Since: 2.26
 */


/**
 * g_value_init:
 * @value: A zero-filled (uninitialized) #GValue structure.
 * @g_type: Type the #GValue should hold values of.
 *
 * Initializes @value with the default value of @type.
 *
 * Returns: (transfer none): the #GValue structure that has been passed in
 */


/**
 * g_value_peek_pointer:
 * @value: An initialized #GValue structure.
 *
 * Returns: (transfer none): the value contents as pointer. This
 * function asserts that g_value_fits_pointer() returned %TRUE for the
 * passed in value.  This is an internal function introduced mainly
 * for C marshallers.
 */


/**
 * g_value_register_transform_func: (skip)
 * @src_type: Source type.
 * @dest_type: Target type.
 * @transform_func: a function which transforms values of type @src_type
 *  into value of type @dest_type
 *
 * Registers a value transformation function for use in g_value_transform().
 * A previously registered transformation function for @src_type and @dest_type
 * will be replaced.
 */


/**
 * g_value_reset:
 * @value: An initialized #GValue structure.
 *
 * Clears the current value in @value and resets it to the default value
 * (as if the value had just been initialized).
 *
 * Returns: the #GValue structure that has been passed in
 */


/**
 * g_value_set_boolean:
 * @value: a valid #GValue of type %G_TYPE_BOOLEAN
 * @v_boolean: boolean value to be set
 *
 * Set the contents of a %G_TYPE_BOOLEAN #GValue to @v_boolean.
 */


/**
 * g_value_set_boxed:
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 * @v_boxed: (allow-none): boxed value to be set
 *
 * Set the contents of a %G_TYPE_BOXED derived #GValue to @v_boxed.
 */


/**
 * g_value_set_boxed_take_ownership:
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 * @v_boxed: (allow-none): duplicated unowned boxed value to be set
 *
 * This is an internal function introduced mainly for C marshallers.
 *
 * Deprecated: 2.4: Use g_value_take_boxed() instead.
 */


/**
 * g_value_set_char:
 * @value: a valid #GValue of type %G_TYPE_CHAR
 * @v_char: character value to be set
 *
 * Set the contents of a %G_TYPE_CHAR #GValue to @v_char.
 *
 * Deprecated: 2.32: This function's input type is broken, see g_value_set_schar()
 */


/**
 * g_value_set_double:
 * @value: a valid #GValue of type %G_TYPE_DOUBLE
 * @v_double: double value to be set
 *
 * Set the contents of a %G_TYPE_DOUBLE #GValue to @v_double.
 */


/**
 * g_value_set_enum:
 * @value: a valid #GValue whose type is derived from %G_TYPE_ENUM
 * @v_enum: enum value to be set
 *
 * Set the contents of a %G_TYPE_ENUM #GValue to @v_enum.
 */


/**
 * g_value_set_flags:
 * @value: a valid #GValue whose type is derived from %G_TYPE_FLAGS
 * @v_flags: flags value to be set
 *
 * Set the contents of a %G_TYPE_FLAGS #GValue to @v_flags.
 */


/**
 * g_value_set_float:
 * @value: a valid #GValue of type %G_TYPE_FLOAT
 * @v_float: float value to be set
 *
 * Set the contents of a %G_TYPE_FLOAT #GValue to @v_float.
 */


/**
 * g_value_set_gtype:
 * @value: a valid #GValue of type %G_TYPE_GTYPE
 * @v_gtype: #GType to be set
 *
 * Set the contents of a %G_TYPE_GTYPE #GValue to @v_gtype.
 *
 * Since: 2.12
 */


/**
 * g_value_set_instance:
 * @value: An initialized #GValue structure.
 * @instance: (allow-none): the instance
 *
 * Sets @value from an instantiatable type via the
 * value_table's collect_value() function.
 */


/**
 * g_value_set_int:
 * @value: a valid #GValue of type %G_TYPE_INT
 * @v_int: integer value to be set
 *
 * Set the contents of a %G_TYPE_INT #GValue to @v_int.
 */


/**
 * g_value_set_int64:
 * @value: a valid #GValue of type %G_TYPE_INT64
 * @v_int64: 64bit integer value to be set
 *
 * Set the contents of a %G_TYPE_INT64 #GValue to @v_int64.
 */


/**
 * g_value_set_long:
 * @value: a valid #GValue of type %G_TYPE_LONG
 * @v_long: long integer value to be set
 *
 * Set the contents of a %G_TYPE_LONG #GValue to @v_long.
 */


/**
 * g_value_set_object:
 * @value: a valid #GValue of %G_TYPE_OBJECT derived type
 * @v_object: (type GObject.Object) (allow-none): object value to be set
 *
 * Set the contents of a %G_TYPE_OBJECT derived #GValue to @v_object.
 *
 * g_value_set_object() increases the reference count of @v_object
 * (the #GValue holds a reference to @v_object).  If you do not wish
 * to increase the reference count of the object (i.e. you wish to
 * pass your current reference to the #GValue because you no longer
 * need it), use g_value_take_object() instead.
 *
 * It is important that your #GValue holds a reference to @v_object (either its
 * own, or one it has taken) to ensure that the object won't be destroyed while
 * the #GValue still exists).
 */


/**
 * g_value_set_object_take_ownership: (skip)
 * @value: a valid #GValue of %G_TYPE_OBJECT derived type
 * @v_object: (allow-none): object value to be set
 *
 * This is an internal function introduced mainly for C marshallers.
 *
 * Deprecated: 2.4: Use g_value_take_object() instead.
 */


/**
 * g_value_set_param:
 * @value: a valid #GValue of type %G_TYPE_PARAM
 * @param: (allow-none): the #GParamSpec to be set
 *
 * Set the contents of a %G_TYPE_PARAM #GValue to @param.
 */


/**
 * g_value_set_param_take_ownership: (skip)
 * @value: a valid #GValue of type %G_TYPE_PARAM
 * @param: (allow-none): the #GParamSpec to be set
 *
 * This is an internal function introduced mainly for C marshallers.
 *
 * Deprecated: 2.4: Use g_value_take_param() instead.
 */


/**
 * g_value_set_pointer:
 * @value: a valid #GValue of %G_TYPE_POINTER
 * @v_pointer: pointer value to be set
 *
 * Set the contents of a pointer #GValue to @v_pointer.
 */


/**
 * g_value_set_schar:
 * @value: a valid #GValue of type %G_TYPE_CHAR
 * @v_char: signed 8 bit integer to be set
 *
 * Set the contents of a %G_TYPE_CHAR #GValue to @v_char.
 *
 * Since: 2.32
 */


/**
 * g_value_set_static_boxed:
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 * @v_boxed: (allow-none): static boxed value to be set
 *
 * Set the contents of a %G_TYPE_BOXED derived #GValue to @v_boxed.
 * The boxed value is assumed to be static, and is thus not duplicated
 * when setting the #GValue.
 */


/**
 * g_value_set_static_string:
 * @value: a valid #GValue of type %G_TYPE_STRING
 * @v_string: (allow-none): static string to be set
 *
 * Set the contents of a %G_TYPE_STRING #GValue to @v_string.
 * The string is assumed to be static, and is thus not duplicated
 * when setting the #GValue.
 */


/**
 * g_value_set_string:
 * @value: a valid #GValue of type %G_TYPE_STRING
 * @v_string: (allow-none): caller-owned string to be duplicated for the #GValue
 *
 * Set the contents of a %G_TYPE_STRING #GValue to @v_string.
 */


/**
 * g_value_set_string_take_ownership:
 * @value: a valid #GValue of type %G_TYPE_STRING
 * @v_string: (allow-none): duplicated unowned string to be set
 *
 * This is an internal function introduced mainly for C marshallers.
 *
 * Deprecated: 2.4: Use g_value_take_string() instead.
 */


/**
 * g_value_set_uchar:
 * @value: a valid #GValue of type %G_TYPE_UCHAR
 * @v_uchar: unsigned character value to be set
 *
 * Set the contents of a %G_TYPE_UCHAR #GValue to @v_uchar.
 */


/**
 * g_value_set_uint:
 * @value: a valid #GValue of type %G_TYPE_UINT
 * @v_uint: unsigned integer value to be set
 *
 * Set the contents of a %G_TYPE_UINT #GValue to @v_uint.
 */


/**
 * g_value_set_uint64:
 * @value: a valid #GValue of type %G_TYPE_UINT64
 * @v_uint64: unsigned 64bit integer value to be set
 *
 * Set the contents of a %G_TYPE_UINT64 #GValue to @v_uint64.
 */


/**
 * g_value_set_ulong:
 * @value: a valid #GValue of type %G_TYPE_ULONG
 * @v_ulong: unsigned long integer value to be set
 *
 * Set the contents of a %G_TYPE_ULONG #GValue to @v_ulong.
 */


/**
 * g_value_set_variant:
 * @value: a valid #GValue of type %G_TYPE_VARIANT
 * @variant: (allow-none): a #GVariant, or %NULL
 *
 * Set the contents of a variant #GValue to @variant.
 * If the variant is floating, it is consumed.
 *
 * Since: 2.26
 */


/**
 * g_value_take_boxed:
 * @value: a valid #GValue of %G_TYPE_BOXED derived type
 * @v_boxed: (allow-none): duplicated unowned boxed value to be set
 *
 * Sets the contents of a %G_TYPE_BOXED derived #GValue to @v_boxed
 * and takes over the ownership of the callers reference to @v_boxed;
 * the caller doesn't have to unref it any more.
 *
 * Since: 2.4
 */


/**
 * g_value_take_object: (skip)
 * @value: a valid #GValue of %G_TYPE_OBJECT derived type
 * @v_object: (allow-none): object value to be set
 *
 * Sets the contents of a %G_TYPE_OBJECT derived #GValue to @v_object
 * and takes over the ownership of the callers reference to @v_object;
 * the caller doesn't have to unref it any more (i.e. the reference
 * count of the object is not increased).
 *
 * If you want the #GValue to hold its own reference to @v_object, use
 * g_value_set_object() instead.
 *
 * Since: 2.4
 */


/**
 * g_value_take_param: (skip)
 * @value: a valid #GValue of type %G_TYPE_PARAM
 * @param: (allow-none): the #GParamSpec to be set
 *
 * Sets the contents of a %G_TYPE_PARAM #GValue to @param and takes
 * over the ownership of the callers reference to @param; the caller
 * doesn't have to unref it any more.
 *
 * Since: 2.4
 */


/**
 * g_value_take_string:
 * @value: a valid #GValue of type %G_TYPE_STRING
 * @v_string: (allow-none): string to take ownership of
 *
 * Sets the contents of a %G_TYPE_STRING #GValue to @v_string.
 *
 * Since: 2.4
 */


/**
 * g_value_take_variant:
 * @value: a valid #GValue of type %G_TYPE_VARIANT
 * @variant: (allow-none): a #GVariant, or %NULL
 *
 * Set the contents of a variant #GValue to @variant, and takes over
 * the ownership of the caller's reference to @variant;
 * the caller doesn't have to unref it any more (i.e. the reference
 * count of the variant is not increased).
 *
 * If @variant was floating then its floating reference is converted to
 * a hard reference.
 *
 * If you want the #GValue to hold its own reference to @variant, use
 * g_value_set_variant() instead.
 *
 * This is an internal function introduced mainly for C marshallers.
 *
 * Since: 2.26
 */


/**
 * g_value_transform:
 * @src_value: Source value.
 * @dest_value: Target value.
 *
 * Tries to cast the contents of @src_value into a type appropriate
 * to store in @dest_value, e.g. to transform a %G_TYPE_INT value
 * into a %G_TYPE_FLOAT value. Performing transformations between
 * value types might incur precision lossage. Especially
 * transformations into strings might reveal seemingly arbitrary
 * results and shouldn't be relied upon for production code (such
 * as rcfile value or object property serialization).
 *
 * Returns: Whether a transformation rule was found and could be applied.
 *  Upon failing transformations, @dest_value is left untouched.
 */


/**
 * g_value_type_compatible:
 * @src_type: source type to be copied.
 * @dest_type: destination type for copying.
 *
 * Returns whether a #GValue of type @src_type can be copied into
 * a #GValue of type @dest_type.
 *
 * Returns: %TRUE if g_value_copy() is possible with @src_type and @dest_type.
 */


/**
 * g_value_type_transformable:
 * @src_type: Source type.
 * @dest_type: Target type.
 *
 * Check whether g_value_transform() is able to transform values
 * of type @src_type into values of type @dest_type.
 *
 * Returns: %TRUE if the transformation is possible, %FALSE otherwise.
 */


/**
 * g_value_unset:
 * @value: An initialized #GValue structure.
 *
 * Clears the current value in @value and "unsets" the type,
 * this releases all resources associated with this GValue.
 * An unset value is the same as an uninitialized (zero-filled)
 * #GValue structure.
 */


/**
 * g_variant_get_gtype:
 *
 * Since: 2.24
 * Deprecated: 2.26
 */


/**
 * g_weak_ref_clear: (skip)
 * @weak_ref: (inout): location of a weak reference, which
 *  may be empty
 *
 * Frees resources associated with a non-statically-allocated #GWeakRef.
 * After this call, the #GWeakRef is left in an undefined state.
 *
 * You should only call this on a #GWeakRef that previously had
 * g_weak_ref_init() called on it.
 *
 * Since: 2.32
 */


/**
 * g_weak_ref_get: (skip)
 * @weak_ref: (inout): location of a weak reference to a #GObject
 *
 * If @weak_ref is not empty, atomically acquire a strong
 * reference to the object it points to, and return that reference.
 *
 * This function is needed because of the potential race between taking
 * the pointer value and g_object_ref() on it, if the object was losing
 * its last reference at the same time in a different thread.
 *
 * The caller should release the resulting reference in the usual way,
 * by using g_object_unref().
 *
 * Returns: (transfer full) (type GObject.Object): the object pointed to
 *     by @weak_ref, or %NULL if it was empty
 * Since: 2.32
 */


/**
 * g_weak_ref_init: (skip)
 * @weak_ref: (inout): uninitialized or empty location for a weak
 *    reference
 * @object: (allow-none): a #GObject or %NULL
 *
 * Initialise a non-statically-allocated #GWeakRef.
 *
 * This function also calls g_weak_ref_set() with @object on the
 * freshly-initialised weak reference.
 *
 * This function should always be matched with a call to
 * g_weak_ref_clear().  It is not necessary to use this function for a
 * #GWeakRef in static storage because it will already be
 * properly initialised.  Just use g_weak_ref_set() directly.
 *
 * Since: 2.32
 */


/**
 * g_weak_ref_set: (skip)
 * @weak_ref: location for a weak reference
 * @object: (allow-none): a #GObject or %NULL
 *
 * Change the object to which @weak_ref points, or set it to
 * %NULL.
 *
 * You must own a strong reference on @object while calling this
 * function.
 *
 * Since: 2.32
 */



/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/
