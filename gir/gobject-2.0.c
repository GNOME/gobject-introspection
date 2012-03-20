/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/

/**
 * GBaseFinalizeFunc:
 * @g_class: The #GTypeClass structure to finalize.
 *
 * A callback function used by the type system to finalize those portions
 * of a derived types class structure that were setup from the corresponding
 * GBaseInitFunc() function. Class finalization basically works the inverse
 * way in which class intialization is performed.
 * See GClassInitFunc() for a discussion of the class intialization process.
 */


/**
 * GBaseInitFunc:
 * @g_class: The #GTypeClass structure to initialize.
 *
 * A callback function used by the type system to do base initialization
 * of the class structures of derived types. It is called as part of the
 * initialization process of all derived classes and should reallocate
 * or reset all dynamic class members copied over from the parent class.
 * For example, class members (such as strings) that are not sufficiently
 * handled by a plain memory copy of the parent class into the derived class
 * have to be altered. See GClassInitFunc() for a discussion of the class
 * intialization process.
 */


/**
 * GBinding:
 *
 * <structname>GBinding</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 2.26
 */


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
 * GBindingFlags:
 * @G_BINDING_DEFAULT: The default binding; if the source property changes, the target property is updated with its value.
 * @G_BINDING_BIDIRECTIONAL: Bidirectional binding; if either the property of the source or the property of the target changes, the other is updated.
 * @G_BINDING_SYNC_CREATE: Synchronize the values of the source and target properties when creating the binding; the direction of the synchronization is always from the source to the target.
 * @G_BINDING_INVERT_BOOLEAN: If the two properties being bound are booleans, setting one to %TRUE will result in the other being set to %FALSE and vice versa. This flag will only work for boolean properties, and cannot be used when passing custom transformation functions to g_object_bind_property_full().
 *
 * Flags to be passed to g_object_bind_property() or
 * g_object_bind_property_full().
 *
 * This enumeration can be extended at later date.
 *
 * Since: 2.26
 */


/**
 * GBindingTransformFunc:
 * @binding: a #GBinding
 * @source_value: the value of the source property
 * @target_value: the value of the target property
 * @user_data: data passed to the transform function
 *
 * A function to be called to transform the source property of @source
 * from @source_value into the target property of @target
 * using @target_value.
 *
 * otherwise
 *
 * Returns: %TRUE if the transformation was successful, and %FALSE
 * Since: 2.26
 */


/**
 * GBookmarkFile:
 *
 * The <structname>GBookmarkFile</structname> struct contains only
 * private data and should not be directly accessed.
 */


/**
 * GBookmarkFileError:
 * @G_BOOKMARK_FILE_ERROR_INVALID_URI: URI was ill-formed
 * @G_BOOKMARK_FILE_ERROR_INVALID_VALUE: a requested field was not found
 * @G_BOOKMARK_FILE_ERROR_APP_NOT_REGISTERED: a requested application did not register a bookmark
 * @G_BOOKMARK_FILE_ERROR_URI_NOT_FOUND: a requested URI was not found
 * @G_BOOKMARK_FILE_ERROR_READ: document was ill formed
 * @G_BOOKMARK_FILE_ERROR_UNKNOWN_ENCODING: the text being parsed was in an unknown encoding
 * @G_BOOKMARK_FILE_ERROR_WRITE: an error occurred while writing
 * @G_BOOKMARK_FILE_ERROR_FILE_NOT_FOUND: requested file was not found
 *
 * Error codes returned by bookmark file parsing.
 */


/**
 * GBoxedCopyFunc:
 * @boxed: The boxed structure to be copied.
 *
 * This function is provided by the user and should produce a copy
 * of the passed in boxed structure.
 *
 * Returns: The newly created copy of the boxed structure.
 */


/**
 * GBoxedFreeFunc:
 * @boxed: The boxed structure to be freed.
 *
 * This function is provided by the user and should free the boxed
 * structure passed.
 */


/**
 * GCClosure:
 * @closure: the #GClosure
 * @callback: the callback function
 *
 * A #GCClosure is a specialization of #GClosure for C function callbacks.
 */


/**
 * GCallback:
 *
 * The type used for callback functions in structure definitions and function
 * signatures. This doesn't mean that all callback functions must take no
 * parameters and return void. The required signature of a callback function
 * is determined by the context in which is used (e.g. the signal to which it
 * is connected). Use G_CALLBACK() to cast the callback function to a #GCallback.
 */


/**
 * GChecksum:
 *
 * An opaque structure representing a checksumming operation.
 * To create a new GChecksum, use g_checksum_new(). To free
 * a GChecksum, use g_checksum_free().
 *
 * Since: 2.16
 */


/**
 * GChecksumType:
 * @G_CHECKSUM_MD5: Use the MD5 hashing algorithm
 * @G_CHECKSUM_SHA1: Use the SHA-1 hashing algorithm
 * @G_CHECKSUM_SHA256: Use the SHA-256 hashing algorithm
 *
 * The hashing algorithm to be used by #GChecksum when performing the
 * digest of some data.
 *
 * Note that the #GChecksumType enumeration may be extended at a later
 * date to include new hashing algorithm types.
 *
 * Since: 2.16
 */


/**
 * GChildWatchFunc:
 * @pid: the process id of the child process
 * @status: Status information about the child process, see waitpid(2) for more information about this field
 * @user_data: user data passed to g_child_watch_add()
 *
 * The type of functions to be called when a child exists.
 */


/**
 * GClassFinalizeFunc:
 * @g_class: The #GTypeClass structure to finalize.
 * @class_data: The @class_data member supplied via the #GTypeInfo structure.
 *
 * A callback function used by the type system to finalize a class.
 * This function is rarely needed, as dynamically allocated class resources
 * should be handled by GBaseInitFunc() and GBaseFinalizeFunc().
 * Also, specification of a GClassFinalizeFunc() in the #GTypeInfo
 * structure of a static type is invalid, because classes of static types
 * will never be finalized (they are artificially kept alive when their
 * reference count drops to zero).
 */


/**
 * GClassInitFunc:
 * @g_class: The #GTypeClass structure to initialize.
 * @class_data: The @class_data member supplied via the #GTypeInfo structure.
 *
 * A callback function used by the type system to initialize the class
 * of a specific type. This function should initialize all static class
 * members.
 * The initialization process of a class involves:
 * <itemizedlist>
 * <listitem><para>
 * 1 - Copying common members from the parent class over to the
 * derived class structure.
 * </para></listitem>
 * <listitem><para>
 * 2 -  Zero initialization of the remaining members not copied
 * over from the parent class.
 * </para></listitem>
 * <listitem><para>
 * 3 - Invocation of the GBaseInitFunc() initializers of all parent
 * types and the class' type.
 * </para></listitem>
 * <listitem><para>
 * 4 - Invocation of the class' GClassInitFunc() initializer.
 * </para></listitem>
 * </itemizedlist>
 * Since derived classes are partially initialized through a memory copy
 * of the parent class, the general rule is that GBaseInitFunc() and
 * GBaseFinalizeFunc() should take care of necessary reinitialization
 * and release of those class members that were introduced by the type
 * that specified these GBaseInitFunc()/GBaseFinalizeFunc().
 * GClassInitFunc() should only care about initializing static
 * class members, while dynamic class members (such as allocated strings
 * or reference counted resources) are better handled by a GBaseInitFunc()
 * for this type, so proper initialization of the dynamic class members
 * is performed for class initialization of derived types as well.
 * An example may help to correspond the intend of the different class
 * initializers:
 *
 * |[
 * typedef struct {
 * GObjectClass parent_class;
 * gint         static_integer;
 * gchar       *dynamic_string;
 * } TypeAClass;
 * static void
 * type_a_base_class_init (TypeAClass *class)
 * {
 * class->dynamic_string = g_strdup ("some string");
 * }
 * static void
 * type_a_base_class_finalize (TypeAClass *class)
 * {
 * g_free (class->dynamic_string);
 * }
 * static void
 * type_a_class_init (TypeAClass *class)
 * {
 * class->static_integer = 42;
 * }
 *
 * typedef struct {
 * TypeAClass   parent_class;
 * gfloat       static_float;
 * GString     *dynamic_gstring;
 * } TypeBClass;
 * static void
 * type_b_base_class_init (TypeBClass *class)
 * {
 * class->dynamic_gstring = g_string_new ("some other string");
 * }
 * static void
 * type_b_base_class_finalize (TypeBClass *class)
 * {
 * g_string_free (class->dynamic_gstring);
 * }
 * static void
 * type_b_class_init (TypeBClass *class)
 * {
 * class->static_float = 3.14159265358979323846;
 * }
 * ]|
 * Initialization of TypeBClass will first cause initialization of
 * TypeAClass (derived classes reference their parent classes, see
 * g_type_class_ref() on this).
 * Initialization of TypeAClass roughly involves zero-initializing its fields,
 * then calling its GBaseInitFunc() type_a_base_class_init() to allocate
 * its dynamic members (dynamic_string), and finally calling its GClassInitFunc()
 * type_a_class_init() to initialize its static members (static_integer).
 * The first step in the initialization process of TypeBClass is then
 * a plain memory copy of the contents of TypeAClass into TypeBClass and
 * zero-initialization of the remaining fields in TypeBClass.
 * The dynamic members of TypeAClass within TypeBClass now need
 * reinitialization which is performed by calling type_a_base_class_init()
 * with an argument of TypeBClass.
 * After that, the GBaseInitFunc() of TypeBClass, type_b_base_class_init()
 * is called to allocate the dynamic members of TypeBClass (dynamic_gstring),
 * and finally the GClassInitFunc() of TypeBClass, type_b_class_init(),
 * is called to complete the initialization process with the static members
 * (static_float).
 * Corresponding finalization counter parts to the GBaseInitFunc() functions
 * have to be provided to release allocated resources at class finalization
 * time.
 */


/**
 * GClosure:
 * @in_marshal: Indicates whether the closure is currently being invoked with g_closure_invoke()
 * @is_invalid: Indicates whether the closure has been invalidated by g_closure_invalidate()
 *
 * A #GClosure represents a callback supplied by the programmer.
 */


/**
 * GClosureMarshal:
 * @closure: the #GClosure to which the marshaller belongs
 * @return_value: (allow-none): a #GValue to store the return value. May be %NULL if the callback of @closure doesn't return a value.
 * @n_param_values: the length of the @param_values array
 * @param_values: (array length=n_param_values): an array of #GValue<!-- -->s holding the arguments on which to invoke the callback of @closure
 * @invocation_hint: (allow-none): the invocation hint given as the last argument to g_closure_invoke()
 * @marshal_data: (allow-none): additional data specified when registering the marshaller, see g_closure_set_marshal() and g_closure_set_meta_marshal()
 *
 * The type used for marshaller functions.
 */


/**
 * GClosureNotify:
 * @data: data specified when registering the notification callback
 * @closure: the #GClosure on which the notification is emitted
 *
 * The type used for the various notification callbacks which can be registered
 * on closures.
 */


/**
 * GConnectFlags:
 * @G_CONNECT_AFTER: whether the handler should be called before or after the default handler of the signal.
 * @G_CONNECT_SWAPPED: whether the instance and data should be swapped when calling the handler.
 *
 * The connection flags are used to specify the behaviour of a signal's
 * connection.
 */


/**
 * GConvertError:
 * @G_CONVERT_ERROR_NO_CONVERSION: Conversion between the requested character sets is not supported.
 * @G_CONVERT_ERROR_ILLEGAL_SEQUENCE: Invalid byte sequence in conversion input.
 * @G_CONVERT_ERROR_FAILED: Conversion failed for some reason.
 * @G_CONVERT_ERROR_PARTIAL_INPUT: Partial character sequence at end of input.
 * @G_CONVERT_ERROR_BAD_URI: URI is invalid.
 * @G_CONVERT_ERROR_NOT_ABSOLUTE_PATH: Pathname is not an absolute path.
 *
 * Error codes returned by character set conversion routines.
 */


/**
 * GCopyFunc:
 * @src: A pointer to the data which should be copied
 * @data: Additional data
 *
 * A function of this signature is used to copy the node data
 * when doing a deep-copy of a tree.
 *
 * Returns: A pointer to the copy
 * Since: 2.4
 */


/**
 * GDateTime:
 *
 * <structname>GDateTime</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 2.26
 */


/**
 * GDebugKey:
 * @key: the string
 * @value: the flag
 *
 * Associates a string with a bit flag.
 * Used in g_parse_debug_string().
 */


/**
 * GEnumClass:
 * @g_type_class: the parent class
 * @minimum: the smallest possible value.
 * @maximum: the largest possible value.
 * @n_values: the number of possible values.
 * @values: an array of #GEnumValue structs describing the individual values.
 *
 * The class of an enumeration type holds information about its
 * possible values.
 */


/**
 * GEnumValue:
 * @value: the enum value
 * @value_name: the name of the value
 * @value_nick: the nickname of the value
 *
 * A structure which contains a single enum value, its name, and its
 * nickname.
 */


/**
 * GError:
 * @domain: error domain, e.g. #G_FILE_ERROR
 * @code: error code, e.g. %G_FILE_ERROR_NOENT
 * @message: human-readable informative error message
 *
 * The <structname>GError</structname> structure contains
 * information about an error that has occurred.
 */


/**
 * GFlagsClass:
 * @g_type_class: the parent class
 * @mask: a mask covering all possible values.
 * @n_values: the number of possible values.
 * @values: an array of #GFlagsValue structs describing the individual values.
 *
 * The class of a flags type holds information about its
 * possible values.
 */


/**
 * GFlagsValue:
 * @value: the flags value
 * @value_name: the name of the value
 * @value_nick: the nickname of the value
 *
 * A structure which contains a single flags value, its name, and its
 * nickname.
 */


/**
 * GFreeFunc:
 * @data: a data pointer
 *
 * Declares a type of function which takes an arbitrary
 * data pointer argument and has no return value. It is
 * not currently used in GLib or GTK+.
 */


/**
 * GHmac:
 *
 * An opaque structure representing a HMAC operation.
 * To create a new GHmac, use g_hmac_new(). To free
 * a GHmac, use g_hmac_unref().
 *
 * Since: 2.30
 */


/**
 * GIconv:
 *
 * The <structname>GIConv</structname> struct wraps an
 * iconv() conversion descriptor. It contains private data
 * and should only be accessed using the following functions.
 */


/**
 * GInitiallyUnowned:
 *
 * All the fields in the <structname>GInitiallyUnowned</structname> structure
 * are private to the #GInitiallyUnowned implementation and should never be
 * accessed directly.
 */


/**
 * GInitiallyUnownedClass:
 *
 * The class structure for the <structname>GInitiallyUnowned</structname> type.
 */


/**
 * GInstanceInitFunc:
 * @instance: The instance to initialize.
 * @g_class: The class of the type the instance is created for.
 *
 * A callback function used by the type system to initialize a new
 * instance of a type. This function initializes all instance members and
 * allocates any resources required by it.
 * Initialization of a derived instance involves calling all its parent
 * types instance initializers, so the class member of the instance
 * is altered during its initialization to always point to the class that
 * belongs to the type the current initializer was introduced for.
 */


/**
 * GInterfaceFinalizeFunc:
 * @g_iface: The interface structure to finalize.
 * @iface_data: The @interface_data supplied via the #GInterfaceInfo structure.
 *
 * A callback function used by the type system to finalize an interface.
 * This function should destroy any internal data and release any resources
 * allocated by the corresponding GInterfaceInitFunc() function.
 */


/**
 * GInterfaceInfo:
 * @interface_init: location of the interface initialization function
 * @interface_finalize: location of the interface finalization function
 * @interface_data: user-supplied data passed to the interface init/finalize functions
 *
 * A structure that provides information to the type system which is
 * used specifically for managing interface types.
 */


/**
 * GInterfaceInitFunc:
 * @g_iface: The interface structure to initialize.
 * @iface_data: The @interface_data supplied via the #GInterfaceInfo structure.
 *
 * A callback function used by the type system to initialize a new
 * interface.  This function should initialize all internal data and
 * allocate any resources required by the interface.
 */


/**
 * GLIB_CHECK_VERSION:
 * @major: the major version to check for
 * @minor: the minor version to check for
 * @micro: the micro version to check for
 *
 * Checks the version of the GLib library that is being compiled
 * against.
 *
 * <example>
 * <title>Checking the version of the GLib library</title>
 * <programlisting>
 * if (!GLIB_CHECK_VERSION (1, 2, 0))
 * g_error ("GLib version 1.2.0 or above is needed");
 * </programlisting>
 * </example>
 *
 * See glib_check_version() for a runtime check.
 *
 * is the same as or newer than the passed-in version.
 *
 * Returns: %TRUE if the version of the GLib header files
 */


/**
 * GLIB_VERSION_2_26:
 *
 * A macro that evaluates to the 2.26 version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * Since: 2.32
 */


/**
 * GLIB_VERSION_2_28:
 *
 * A macro that evaluates to the 2.28 version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * Since: 2.32
 */


/**
 * GLIB_VERSION_2_30:
 *
 * A macro that evaluates to the 2.30 version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * Since: 2.32
 */


/**
 * GLIB_VERSION_2_32:
 *
 * A macro that evaluates to the 2.32 version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * Since: 2.32
 */


/**
 * GLIB_VERSION_MAX_ALLOWED:
 *
 * A macro that should be defined by the user prior to including
 * the glib.h header.
 * The definition should be one of the predefined GLib version
 * macros: %GLIB_VERSION_2_26, %GLIB_VERSION_2_28,...
 *
 * This macro defines the upper bound for the GLib API to use.
 *
 * If a function has been introduced in a newer version of GLib,
 * it is possible to use this symbol to get compiler warnings when
 * trying to use that function.
 *
 * Since: 2.32
 */


/**
 * GLIB_VERSION_MIN_REQUIRED:
 *
 * A macro that should be defined by the user prior to including
 * the glib.h header.
 * The definition should be one of the predefined GLib version
 * macros: %GLIB_VERSION_2_26, %GLIB_VERSION_2_28,...
 *
 * This macro defines the lower bound for the GLib API to use.
 *
 * If a function has been deprecated in a newer version of GLib,
 * it is possible to use this symbol to avoid the compiler warnings
 * without disabling warning for every deprecated function.
 *
 * Since: 2.32
 */


/**
 * GMainContext:
 *
 * The <structname>GMainContext</structname> struct is an opaque data
 * type representing a set of sources to be handled in a main loop.
 */


/**
 * GMainLoop:
 *
 * The <structname>GMainLoop</structname> struct is an opaque data type
 * representing the main event loop of a GLib or GTK+ application.
 */


/**
 * GMarkupError:
 * @G_MARKUP_ERROR_BAD_UTF8: text being parsed was not valid UTF-8
 * @G_MARKUP_ERROR_EMPTY: document contained nothing, or only whitespace
 * @G_MARKUP_ERROR_PARSE: document was ill-formed
 * @G_MARKUP_ERROR_UNKNOWN_ELEMENT: error should be set by #GMarkupParser functions; element wasn't known
 * @G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE: error should be set by #GMarkupParser functions; attribute wasn't known
 * @G_MARKUP_ERROR_INVALID_CONTENT: error should be set by #GMarkupParser functions; content was invalid
 * @G_MARKUP_ERROR_MISSING_ATTRIBUTE: error should be set by #GMarkupParser functions; a required attribute was missing
 *
 * Error codes returned by markup parsing.
 */


/**
 * GMarkupParseContext:
 *
 * A parse context is used to parse a stream of bytes that
 * you expect to contain marked-up text.
 *
 * See g_markup_parse_context_new(), #GMarkupParser, and so
 * on for more details.
 */


/**
 * GMarkupParseFlags:
 * @G_MARKUP_DO_NOT_USE_THIS_UNSUPPORTED_FLAG: flag you should not use
 * @G_MARKUP_TREAT_CDATA_AS_TEXT: When this flag is set, CDATA marked sections are not passed literally to the @passthrough function of the parser. Instead, the content of the section (without the <literal>&lt;![CDATA[</literal> and <literal>]]&gt;</literal>) is passed to the @text function. This flag was added in GLib 2.12
 * @G_MARKUP_PREFIX_ERROR_POSITION: Normally errors caught by GMarkup itself have line/column information prefixed to them to let the caller know the location of the error. When this flag is set the location information is also prefixed to errors generated by the #GMarkupParser implementation functions
 *
 * Flags that affect the behaviour of the parser.
 */


/**
 * GMarkupParser:
 * @start_element: Callback to invoke when the opening tag of an element is seen.
 * @end_element: Callback to invoke when the closing tag of an element is seen. Note that this is also called for empty tags like <literal>&lt;empty/&gt;</literal>.
 * @text: Callback to invoke when some text is seen (text is always inside an element). Note that the text of an element may be spread over multiple calls of this function. If the %G_MARKUP_TREAT_CDATA_AS_TEXT flag is set, this function is also called for the content of CDATA marked sections.
 * @passthrough: Callback to invoke for comments, processing instructions and doctype declarations; if you're re-writing the parsed document, write the passthrough text back out in the same position. If the %G_MARKUP_TREAT_CDATA_AS_TEXT flag is not set, this function is also called for CDATA marked sections.
 * @error: Callback to invoke when an error occurs.
 *
 * Any of the fields in #GMarkupParser can be %NULL, in which case they
 * will be ignored. Except for the @error function, any of these callbacks
 * can set an error; in particular the %G_MARKUP_ERROR_UNKNOWN_ELEMENT,
 * %G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE, and %G_MARKUP_ERROR_INVALID_CONTENT
 * errors are intended to be set from these callbacks. If you set an error
 * from a callback, g_markup_parse_context_parse() will report that error
 * back to its caller.
 */


/**
 * GMemVTable:
 * @malloc: function to use for allocating memory.
 * @realloc: function to use for reallocating memory.
 * @free: function to use to free memory.
 * @calloc: function to use for allocating zero-filled memory.
 * @try_malloc: function to use for allocating memory without a default error handler.
 * @try_realloc: function to use for reallocating memory without a default error handler.
 *
 * A set of functions used to perform memory allocation. The same #GMemVTable must
 * be used for all allocations in the same program; a call to g_mem_set_vtable(),
 * if it exists, should be prior to any use of GLib.
 */


/**
 * GNormalizeMode:
 * @G_NORMALIZE_DEFAULT: standardize differences that do not affect the text content, such as the above-mentioned accent representation
 * @G_NORMALIZE_NFD: another name for %G_NORMALIZE_DEFAULT
 * @G_NORMALIZE_DEFAULT_COMPOSE: like %G_NORMALIZE_DEFAULT, but with composed forms rather than a maximally decomposed form
 * @G_NORMALIZE_NFC: another name for %G_NORMALIZE_DEFAULT_COMPOSE
 * @G_NORMALIZE_ALL: beyond %G_NORMALIZE_DEFAULT also standardize the "compatibility" characters in Unicode, such as SUPERSCRIPT THREE to the standard forms (in this case DIGIT THREE). Formatting information may be lost but for most text operations such characters should be considered the same
 * @G_NORMALIZE_NFKD: another name for %G_NORMALIZE_ALL
 * @G_NORMALIZE_ALL_COMPOSE: like %G_NORMALIZE_ALL, but with composed forms rather than a maximally decomposed form
 * @G_NORMALIZE_NFKC: another name for %G_NORMALIZE_ALL_COMPOSE
 *
 * Defines how a Unicode string is transformed in a canonical
 * form, standardizing such issues as whether a character with
 * an accent is represented as a base character and combining
 * accent or as a single precomposed character. Unicode strings
 * should generally be normalized before comparing them.
 */


/**
 * GObject:
 *
 * All the fields in the <structname>GObject</structname> structure are private
 * to the #GObject implementation and should never be accessed directly.
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
 * G_CALLBACK (gtk_text_view_target_list_notify),
 * text_view)
 * ]|
 * It is important to note that you must use
 * <link linkend="canonical-parameter-name">canonical</link> parameter names as
 * detail strings for the notify signal.
 */


/**
 * GObjectClass:
 * @g_type_class: the parent class
 * @constructor: the @constructor function is called by g_object_new () to complete the object initialization after all the construction properties are set. The first thing a @constructor implementation must do is chain up to the @constructor of the parent class. Overriding @constructor should be rarely needed, e.g. to handle construct properties, or to implement singletons.
 * @set_property: the generic setter for all properties of this type. Should be overridden for every type with properties. Implementations of @set_property don't need to emit property change notification explicitly, this is handled by the type system.
 * @get_property: the generic getter for all properties of this type. Should be overridden for every type with properties.
 * @dispose: the @dispose function is supposed to drop all references to other objects, but keep the instance otherwise intact, so that client method invocations still work. It may be run multiple times (due to reference loops). Before returning, @dispose should chain up to the @dispose method of the parent class.
 * @finalize: instance finalization function, should finish the finalization of the instance begun in @dispose and chain up to the @finalize method of the parent class.
 * @dispatch_properties_changed: emits property change notification for a bunch of properties. Overriding @dispatch_properties_changed should be rarely needed.
 * @notify: the class closure for the notify signal
 * @constructed: the @constructed function is called by g_object_new() as the final step of the object creation process.  At the point of the call, all construction properties have been set on the object.  The purpose of this call is to allow for object initialisation steps that can only be performed after construction properties have been set.  @constructed implementors should chain up to the @constructed call of their parent class to allow it to complete its initialisation.
 *
 * The class structure for the <structname>GObject</structname> type.
 *
 * <example>
 * <title>Implementing singletons using a constructor</title>
 * <programlisting>
 * static MySingleton *the_singleton = NULL;
 *
 * static GObject*
 * my_singleton_constructor (GType                  type,
 * guint                  n_construct_params,
 * GObjectConstructParam *construct_params)
 * {
 * GObject *object;
 *
 * if (!the_singleton)
 * {
 * object = G_OBJECT_CLASS (parent_class)->constructor (type,
 * n_construct_params,
 * construct_params);
 * the_singleton = MY_SINGLETON (object);
 * }
 * else
 * object = g_object_ref (G_OBJECT (the_singleton));
 *
 * return object;
 * }
 * </programlisting></example>
 */


/**
 * GObjectConstructParam:
 * @pspec: the #GParamSpec of the construct parameter
 * @value: the value to set the parameter to
 *
 * The <structname>GObjectConstructParam</structname> struct is an auxiliary
 * structure used to hand #GParamSpec/#GValue pairs to the @constructor of
 * a #GObjectClass.
 */


/**
 * GObjectFinalizeFunc:
 * @object: the #GObject being finalized
 *
 * The type of the @finalize function of #GObjectClass.
 */


/**
 * GObjectGetPropertyFunc:
 * @object: a #GObject
 * @property_id: the numeric id under which the property was registered with g_object_class_install_property().
 * @value: a #GValue to return the property value in
 * @pspec: the #GParamSpec describing the property
 *
 * The type of the @get_property function of #GObjectClass.
 */


/**
 * GObjectSetPropertyFunc:
 * @object: a #GObject
 * @property_id: the numeric id under which the property was registered with g_object_class_install_property().
 * @value: the new value for the property
 * @pspec: the #GParamSpec describing the property
 *
 * The type of the @set_property function of #GObjectClass.
 */


/**
 * GOptionArg:
 * @G_OPTION_ARG_NONE: No extra argument. This is useful for simple flags.
 * @G_OPTION_ARG_STRING: The option takes a string argument.
 * @G_OPTION_ARG_INT: The option takes an integer argument.
 * @G_OPTION_ARG_CALLBACK: The option provides a callback to parse the extra argument.
 * @G_OPTION_ARG_FILENAME: The option takes a filename as argument.
 * @G_OPTION_ARG_STRING_ARRAY: The option takes a string argument, multiple uses of the option are collected into an array of strings.
 * @G_OPTION_ARG_FILENAME_ARRAY: The option takes a filename as argument, multiple uses of the option are collected into an array of strings.
 * @G_OPTION_ARG_DOUBLE: The option takes a double argument. The argument can be formatted either for the user's locale or for the "C" locale. Since 2.12
 * @G_OPTION_ARG_INT64: The option takes a 64-bit integer. Like %G_OPTION_ARG_INT but for larger numbers. The number can be in decimal base, or in hexadecimal (when prefixed with <literal>0x</literal>, for example, <literal>0xffffffff</literal>). Since 2.12
 *
 * The #GOptionArg enum values determine which type of extra argument the
 * options expect to find. If an option expects an extra argument, it
 * can be specified in several ways; with a short option:
 * <option>-x arg</option>, with a long option: <option>--name arg</option>
 * or combined in a single argument: <option>--name=arg</option>.
 */


/**
 * GOptionArgFunc:
 * @option_name: The name of the option being parsed. This will be either a single dash followed by a single letter (for a short name) or two dashes followed by a long option name.
 * @value: The value to be parsed.
 * @data: User data added to the #GOptionGroup containing the option when it was created with g_option_group_new()
 * @error: A return location for errors. The error code %G_OPTION_ERROR_FAILED is intended to be used for errors in #GOptionArgFunc callbacks.
 *
 * The type of function to be passed as callback for %G_OPTION_ARG_CALLBACK
 * options.
 *
 * occurred, in which case @error should be set with g_set_error()
 *
 * Returns: %TRUE if the option was successfully parsed, %FALSE if an error
 */


/**
 * GOptionContext:
 *
 * A <structname>GOptionContext</structname> struct defines which options
 * are accepted by the commandline option parser. The struct has only private
 * fields and should not be directly accessed.
 */


/**
 * GOptionEntry:
 * @long_name: The long name of an option can be used to specify it in a commandline as --<replaceable>long_name</replaceable>. Every option must have a long name. To resolve conflicts if multiple option groups contain the same long name, it is also possible to specify the option as --<replaceable>groupname</replaceable>-<replaceable>long_name</replaceable>.
 * @short_name: If an option has a short name, it can be specified -<replaceable>short_name</replaceable> in a commandline. @short_name must be a printable ASCII character different from '-', or zero if the option has no short name.
 * @flags: Flags from #GOptionFlags.
 * @arg: The type of the option, as a #GOptionArg.
 * @arg_data: If the @arg type is %G_OPTION_ARG_CALLBACK, then @arg_data must point to a #GOptionArgFunc callback function, which will be called to handle the extra argument. Otherwise, @arg_data is a pointer to a location to store the value, the required type of the location depends on the @arg type: <variablelist> <varlistentry> <term>%G_OPTION_ARG_NONE</term> <listitem><para>%gboolean</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_STRING</term> <listitem><para>%gchar*</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_INT</term> <listitem><para>%gint</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_FILENAME</term> <listitem><para>%gchar*</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_STRING_ARRAY</term> <listitem><para>%gchar**</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_FILENAME_ARRAY</term> <listitem><para>%gchar**</para></listitem> </varlistentry> <varlistentry> <term>%G_OPTION_ARG_DOUBLE</term> <listitem><para>%gdouble</para></listitem> </varlistentry> </variablelist> If @arg type is %G_OPTION_ARG_STRING or %G_OPTION_ARG_FILENAME the location will contain a newly allocated string if the option was given. That string needs to be freed by the callee using g_free(). Likewise if @arg type is %G_OPTION_ARG_STRING_ARRAY or %G_OPTION_ARG_FILENAME_ARRAY, the data should be freed using g_strfreev().
 * @description: the description for the option in <option>--help</option> output. The @description is translated using the @translate_func of the group, see g_option_group_set_translation_domain().
 * @arg_description: The placeholder to use for the extra argument parsed by the option in <option>--help</option> output. The @arg_description is translated using the @translate_func of the group, see g_option_group_set_translation_domain().
 *
 * A <structname>GOptionEntry</structname> defines a single option.
 * To have an effect, they must be added to a #GOptionGroup with
 * g_option_context_add_main_entries() or g_option_group_add_entries().
 */


/**
 * GOptionError:
 * @G_OPTION_ERROR_UNKNOWN_OPTION: An option was not known to the parser. This error will only be reported, if the parser hasn't been instructed to ignore unknown options, see g_option_context_set_ignore_unknown_options().
 * @G_OPTION_ERROR_BAD_VALUE: A value couldn't be parsed.
 * @G_OPTION_ERROR_FAILED: A #GOptionArgFunc callback failed.
 *
 * Error codes returned by option parsing.
 */


/**
 * GOptionErrorFunc:
 * @context: The active #GOptionContext
 * @group: The group to which the function belongs
 * @data: User data added to the #GOptionGroup containing the option when it was created with g_option_group_new()
 * @error: The #GError containing details about the parse error
 *
 * The type of function to be used as callback when a parse error occurs.
 */


/**
 * GOptionFlags:
 * @G_OPTION_FLAG_HIDDEN: The option doesn't appear in <option>--help</option> output.
 * @G_OPTION_FLAG_IN_MAIN: The option appears in the main section of the <option>--help</option> output, even if it is defined in a group.
 * @G_OPTION_FLAG_REVERSE: For options of the %G_OPTION_ARG_NONE kind, this flag indicates that the sense of the option is reversed.
 * @G_OPTION_FLAG_NO_ARG: For options of the %G_OPTION_ARG_CALLBACK kind, this flag indicates that the callback does not take any argument (like a %G_OPTION_ARG_NONE option). Since 2.8
 * @G_OPTION_FLAG_FILENAME: For options of the %G_OPTION_ARG_CALLBACK kind, this flag indicates that the argument should be passed to the callback in the GLib filename encoding rather than UTF-8. Since 2.8
 * @G_OPTION_FLAG_OPTIONAL_ARG: For options of the %G_OPTION_ARG_CALLBACK kind, this flag indicates that the argument supply is optional. If no argument is given then data of %GOptionParseFunc will be set to NULL. Since 2.8
 * @G_OPTION_FLAG_NOALIAS: This flag turns off the automatic conflict resolution which prefixes long option names with <literal>groupname-</literal> if there is a conflict. This option should only be used in situations where aliasing is necessary to model some legacy commandline interface. It is not safe to use this option, unless all option groups are under your direct control. Since 2.8.
 *
 * Flags which modify individual options.
 */


/**
 * GOptionGroup:
 *
 * A <structname>GOptionGroup</structname> struct defines the options in a single
 * group. The struct has only private fields and should not be directly accessed.
 *
 * All options in a group share the same translation function. Libraries which
 * need to parse commandline options are expected to provide a function for
 * getting a <structname>GOptionGroup</structname> holding their options, which
 * the application can then add to its #GOptionContext.
 */


/**
 * GOptionParseFunc:
 * @context: The active #GOptionContext
 * @group: The group to which the function belongs
 * @data: User data added to the #GOptionGroup containing the option when it was created with g_option_group_new()
 * @error: A return location for error details
 *
 * The type of function that can be called before and after parsing.
 *
 * occurred, in which case @error should be set with g_set_error()
 *
 * Returns: %TRUE if the function completed successfully, %FALSE if an error
 */


/**
 * GParamFlags:
 * @G_PARAM_READABLE: the parameter is readable
 * @G_PARAM_WRITABLE: the parameter is writable
 * @G_PARAM_CONSTRUCT: the parameter will be set upon object construction
 * @G_PARAM_CONSTRUCT_ONLY: the parameter will only be set upon object construction
 * @G_PARAM_LAX_VALIDATION: upon parameter conversion (see g_param_value_convert()) strict validation is not required
 * @G_PARAM_STATIC_NAME: the string used as name when constructing the parameter is guaranteed to remain valid and unmodified for the lifetime of the parameter. Since 2.8
 * @G_PARAM_STATIC_NICK: the string used as nick when constructing the parameter is guaranteed to remain valid and unmmodified for the lifetime of the parameter. Since 2.8
 * @G_PARAM_STATIC_BLURB: the string used as blurb when constructing the parameter is guaranteed to remain valid and unmodified for the lifetime of the parameter. Since 2.8
 * @G_PARAM_PRIVATE: internal
 * @G_PARAM_DEPRECATED: the parameter is deprecated and will be removed in a future version. A warning will be generated if it is used while running with G_ENABLE_DIAGNOSTIC=1. Since: 2.26
 *
 * Through the #GParamFlags flag values, certain aspects of parameters
 * can be configured.
 */


/**
 * GParamSpec:
 * @g_type_instance: private #GTypeInstance portion
 * @name: name of this parameter: always an interned string
 * @flags: #GParamFlags flags for this parameter
 * @value_type: the #GValue type for this parameter
 * @owner_type: #GType type that uses (introduces) this parameter
 *
 * All other fields of the <structname>GParamSpec</structname> struct are private and
 * should not be used directly.
 */


/**
 * GParamSpecBoolean:
 * @parent_instance: private #GParamSpec portion
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for boolean properties.
 */


/**
 * GParamSpecBoxed:
 * @parent_instance: private #GParamSpec portion
 *
 * A #GParamSpec derived structure that contains the meta data for boxed properties.
 */


/**
 * GParamSpecChar:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for character properties.
 */


/**
 * GParamSpecClass:
 * @g_type_class: the parent class
 * @value_type: the #GValue type for this parameter
 * @finalize: The instance finalization function (optional), should chain up to the finalize method of the parent class.
 * @value_set_default: Resets a @value to the default value for this type (recommended, the default is g_value_reset()), see g_param_value_set_default().
 * @value_validate: Ensures that the contents of @value comply with the specifications set out by this type (optional), see g_param_value_validate().
 * @values_cmp: Compares @value1 with @value2 according to this type (recommended, the default is memcmp()), see g_param_values_cmp().
 *
 * The class structure for the <structname>GParamSpec</structname> type.
 * Normally, <structname>GParamSpec</structname> classes are filled by
 * g_param_type_register_static().
 */


/**
 * GParamSpecDouble:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @epsilon: values closer than @epsilon will be considered identical by g_param_values_cmp(); the default value is 1e-90.
 *
 * A #GParamSpec derived structure that contains the meta data for double properties.
 */


/**
 * GParamSpecEnum:
 * @parent_instance: private #GParamSpec portion
 * @enum_class: the #GEnumClass for the enum
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for enum
 * properties.
 */


/**
 * GParamSpecFlags:
 * @parent_instance: private #GParamSpec portion
 * @flags_class: the #GFlagsClass for the flags
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for flags
 * properties.
 */


/**
 * GParamSpecFloat:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 * @epsilon: values closer than @epsilon will be considered identical by g_param_values_cmp(); the default value is 1e-30.
 *
 * A #GParamSpec derived structure that contains the meta data for float properties.
 */


/**
 * GParamSpecGType:
 * @parent_instance: private #GParamSpec portion
 * @is_a_type: a #GType whose subtypes can occur as values
 *
 * A #GParamSpec derived structure that contains the meta data for #GType properties.
 *
 * Since: 2.10
 */


/**
 * GParamSpecInt:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for integer properties.
 */


/**
 * GParamSpecInt64:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for 64bit integer properties.
 */


/**
 * GParamSpecLong:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for long integer properties.
 */


/**
 * GParamSpecObject:
 * @parent_instance: private #GParamSpec portion
 *
 * A #GParamSpec derived structure that contains the meta data for object properties.
 */


/**
 * GParamSpecOverride:
 *
 * This is a type of #GParamSpec type that simply redirects operations to
 * another paramspec.  All operations other than getting or
 * setting the value are redirected, including accessing the nick and
 * blurb, validating a value, and so forth. See
 * g_param_spec_get_redirect_target() for retrieving the overidden
 * property. #GParamSpecOverride is used in implementing
 * g_object_class_override_property(), and will not be directly useful
 * unless you are implementing a new base type similar to GObject.
 *
 * Since: 2.4
 */


/**
 * GParamSpecParam:
 * @parent_instance: private #GParamSpec portion
 *
 * A #GParamSpec derived structure that contains the meta data for %G_TYPE_PARAM
 * properties.
 */


/**
 * GParamSpecPointer:
 * @parent_instance: private #GParamSpec portion
 *
 * A #GParamSpec derived structure that contains the meta data for pointer properties.
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
 * GParamSpecString:
 * @parent_instance: private #GParamSpec portion
 * @default_value: default value for the property specified
 * @cset_first: a string containing the allowed values for the first byte
 * @cset_nth: a string containing the allowed values for the subsequent bytes
 * @substitutor: the replacement byte for bytes which don't match @cset_first or @cset_nth.
 * @null_fold_if_empty: replace empty string by %NULL
 * @ensure_non_null: replace %NULL strings by an empty string
 *
 * A #GParamSpec derived structure that contains the meta data for string
 * properties.
 */


/**
 * GParamSpecTypeInfo:
 * @instance_size: Size of the instance (object) structure.
 * @n_preallocs: Prior to GLib 2.10, it specified the number of pre-allocated (cached) instances to reserve memory for (0 indicates no caching). Since GLib 2.10, it is ignored, since instances are allocated with the <link linkend="glib-Memory-Slices">slice allocator</link> now.
 * @instance_init: Location of the instance initialization function (optional).
 * @value_type: The #GType of values conforming to this #GParamSpec
 * @finalize: The instance finalization function (optional).
 * @value_set_default: Resets a @value to the default value for @pspec (recommended, the default is g_value_reset()), see g_param_value_set_default().
 * @value_validate: Ensures that the contents of @value comply with the specifications set out by @pspec (optional), see g_param_value_validate().
 * @values_cmp: Compares @value1 with @value2 according to @pspec (recommended, the default is memcmp()), see g_param_values_cmp().
 *
 * This structure is used to provide the type system with the information
 * required to initialize and destruct (finalize) a parameter's class and
 * instances thereof.
 * The initialized structure is passed to the g_param_type_register_static()
 * The type system will perform a deep copy of this structure, so its memory
 * does not need to be persistent across invocation of
 * g_param_type_register_static().
 */


/**
 * GParamSpecUChar:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for unsigned character properties.
 */


/**
 * GParamSpecUInt:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for unsigned integer properties.
 */


/**
 * GParamSpecUInt64:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for unsigned 64bit integer properties.
 */


/**
 * GParamSpecULong:
 * @parent_instance: private #GParamSpec portion
 * @minimum: minimum value for the property specified
 * @maximum: maximum value for the property specified
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for unsigned long integer properties.
 */


/**
 * GParamSpecUnichar:
 * @parent_instance: private #GParamSpec portion
 * @default_value: default value for the property specified
 *
 * A #GParamSpec derived structure that contains the meta data for unichar (unsigned integer) properties.
 */


/**
 * GParamSpecValueArray:
 * @parent_instance: private #GParamSpec portion
 * @element_spec: a #GParamSpec describing the elements contained in arrays of this property, may be %NULL
 * @fixed_n_elements: if greater than 0, arrays of this property will always have this many elements
 *
 * A #GParamSpec derived structure that contains the meta data for #GValueArray properties.
 */


/**
 * GParamSpecVariant:
 * @parent_instance: private #GParamSpec portion
 * @type: a #GVariantType, or %NULL
 * @default_value: a #GVariant, or %NULL
 *
 * A #GParamSpec derived structure that contains the meta data for #GVariant properties.
 *
 * Since: 2.26
 */


/**
 * GParameter:
 * @name: the parameter name
 * @value: the parameter value
 *
 * The <structname>GParameter</structname> struct is an auxiliary structure used
 * to hand parameter name/value pairs to g_object_newv().
 */


/**
 * GPid:
 *
 * A type which is used to hold a process identification.
 *
 * On UNIX, processes are identified by a process id (an integer),
 * while Windows uses process handles (which are pointers).
 *
 * GPid is used in GLib only for descendant processes spawned with
 * the g_spawn functions.
 */


/**
 * GPollFD:
 * @fd: the file descriptor to poll (or a <type>HANDLE</type> on Win32)
 * @events: a bitwise combination from #GIOCondition, specifying which events should be polled for. Typically for reading from a file descriptor you would use %G_IO_IN | %G_IO_HUP | %G_IO_ERR, and for writing you would use %G_IO_OUT | %G_IO_ERR.
 * @revents: a bitwise combination of flags from #GIOCondition, returned from the poll() function to indicate which events occurred.
 *
 * Represents a file descriptor, which events to poll for, and which events
 * occurred.
 */


/**
 * GPollFunc:
 * @ufds: an array of #GPollFD elements
 * @nfsd: the number of elements in @ufds
 * @timeout_: the maximum time to wait for an event of the file descriptors. A negative value indicates an infinite timeout.
 *
 * Specifies the type of function passed to g_main_context_set_poll_func().
 * The semantics of the function should match those of the poll() system call.
 *
 * reported, or -1 if an error occurred.
 *
 * Returns: the number of #GPollFD elements which have events or errors
 */


/**
 * GPrintFunc:
 * @string: the message to output
 *
 * Specifies the type of the print handler functions.
 * These are called with the complete formatted string to output.
 */


/**
 * GQueue:
 * @head: a pointer to the first element of the queue
 * @tail: a pointer to the last element of the queue
 * @length: the number of elements in the queue
 *
 * Contains the public fields of a
 * <link linkend="glib-Double-ended-Queues">Queue</link>.
 */


/**
 * GRegex:
 *
 * A GRegex is the "compiled" form of a regular expression pattern. This
 * structure is opaque and its fields cannot be accessed directly.
 *
 * Since: 2.14
 */


/**
 * GRegexCompileFlags:
 * @G_REGEX_CASELESS: Letters in the pattern match both upper- and lowercase letters. This option can be changed within a pattern by a "(?i)" option setting.
 * @G_REGEX_MULTILINE: By default, GRegex treats the strings as consisting of a single line of characters (even if it actually contains newlines). The "start of line" metacharacter ("^") matches only at the start of the string, while the "end of line" metacharacter ("$") matches only at the end of the string, or before a terminating newline (unless #G_REGEX_DOLLAR_ENDONLY is set). When #G_REGEX_MULTILINE is set, the "start of line" and "end of line" constructs match immediately following or immediately before any newline in the string, respectively, as well as at the very start and end. This can be changed within a pattern by a "(?m)" option setting.
 * @G_REGEX_DOTALL: A dot metacharater (".") in the pattern matches all characters, including newlines. Without it, newlines are excluded. This option can be changed within a pattern by a ("?s") option setting.
 * @G_REGEX_EXTENDED: Whitespace data characters in the pattern are totally ignored except when escaped or inside a character class. Whitespace does not include the VT character (code 11). In addition, characters between an unescaped "#" outside a character class and the next newline character, inclusive, are also ignored. This can be changed within a pattern by a "(?x)" option setting.
 * @G_REGEX_ANCHORED: The pattern is forced to be "anchored", that is, it is constrained to match only at the first matching point in the string that is being searched. This effect can also be achieved by appropriate constructs in the pattern itself such as the "^" metacharater.
 * @G_REGEX_DOLLAR_ENDONLY: A dollar metacharacter ("$") in the pattern matches only at the end of the string. Without this option, a dollar also matches immediately before the final character if it is a newline (but not before any other newlines). This option is ignored if #G_REGEX_MULTILINE is set.
 * @G_REGEX_UNGREEDY: Inverts the "greediness" of the quantifiers so that they are not greedy by default, but become greedy if followed by "?". It can also be set by a "(?U)" option setting within the pattern.
 * @G_REGEX_RAW: Usually strings must be valid UTF-8 strings, using this flag they are considered as a raw sequence of bytes. @G_REGEX_NO_AUTO_CAPTURE: Disables the use of numbered capturing parentheses in the pattern. Any opening parenthesis that is not followed by "?" behaves as if it were followed by "?:" but named parentheses can still be used for capturing (and they acquire numbers in the usual way).
 * @G_REGEX_OPTIMIZE: Optimize the regular expression. If the pattern will be used many times, then it may be worth the effort to optimize it to improve the speed of matches.
 * @G_REGEX_DUPNAMES: Names used to identify capturing subpatterns need not be unique. This can be helpful for certain types of pattern when it is known that only one instance of the named subpattern can ever be matched.
 * @G_REGEX_NEWLINE_CR: Usually any newline character is recognized, if this option is set, the only recognized newline character is '\r'.
 * @G_REGEX_NEWLINE_LF: Usually any newline character is recognized, if this option is set, the only recognized newline character is '\n'.
 * @G_REGEX_NEWLINE_CRLF: Usually any newline character is recognized, if this option is set, the only recognized newline character sequence is '\r\n'.
 *
 * Flags specifying compile-time options.
 *
 * Since: 2.14
 */


/**
 * GRegexError:
 * @G_REGEX_ERROR_COMPILE: Compilation of the regular expression failed.
 * @G_REGEX_ERROR_OPTIMIZE: Optimization of the regular expression failed.
 * @G_REGEX_ERROR_REPLACE: Replacement failed due to an ill-formed replacement string.
 * @G_REGEX_ERROR_MATCH: The match process failed.
 * @G_REGEX_ERROR_INTERNAL: Internal error of the regular expression engine. Since 2.16
 * @G_REGEX_ERROR_STRAY_BACKSLASH: "\\" at end of pattern. Since 2.16
 * @G_REGEX_ERROR_MISSING_CONTROL_CHAR: "\\c" at end of pattern. Since 2.16
 * @G_REGEX_ERROR_UNRECOGNIZED_ESCAPE: Unrecognized character follows "\\". Since 2.16
 * @G_REGEX_ERROR_QUANTIFIERS_OUT_OF_ORDER: Numbers out of order in "{}" quantifier. Since 2.16
 * @G_REGEX_ERROR_QUANTIFIER_TOO_BIG: Number too big in "{}" quantifier. Since 2.16
 * @G_REGEX_ERROR_UNTERMINATED_CHARACTER_CLASS: Missing terminating "]" for character class. Since 2.16
 * @G_REGEX_ERROR_INVALID_ESCAPE_IN_CHARACTER_CLASS: Invalid escape sequence in character class. Since 2.16
 * @G_REGEX_ERROR_RANGE_OUT_OF_ORDER: Range out of order in character class. Since 2.16
 * @G_REGEX_ERROR_NOTHING_TO_REPEAT: Nothing to repeat. Since 2.16
 * @G_REGEX_ERROR_UNRECOGNIZED_CHARACTER: Unrecognized character after "(?", "(?&lt;" or "(?P". Since 2.16
 * @G_REGEX_ERROR_POSIX_NAMED_CLASS_OUTSIDE_CLASS: POSIX named classes are supported only within a class. Since 2.16
 * @G_REGEX_ERROR_UNMATCHED_PARENTHESIS: Missing terminating ")" or ")" without opening "(". Since 2.16
 * @G_REGEX_ERROR_INEXISTENT_SUBPATTERN_REFERENCE: Reference to non-existent subpattern. Since 2.16
 * @G_REGEX_ERROR_UNTERMINATED_COMMENT: Missing terminating ")" after comment. Since 2.16
 * @G_REGEX_ERROR_EXPRESSION_TOO_LARGE: Regular expression too large. Since 2.16
 * @G_REGEX_ERROR_MEMORY_ERROR: Failed to get memory. Since 2.16
 * @G_REGEX_ERROR_VARIABLE_LENGTH_LOOKBEHIND: Lookbehind assertion is not fixed length. Since 2.16
 * @G_REGEX_ERROR_MALFORMED_CONDITION: Malformed number or name after "(?(". Since 2.16
 * @G_REGEX_ERROR_TOO_MANY_CONDITIONAL_BRANCHES: Conditional group contains more than two branches. Since 2.16
 * @G_REGEX_ERROR_ASSERTION_EXPECTED: Assertion expected after "(?(". Since 2.16
 * @G_REGEX_ERROR_UNKNOWN_POSIX_CLASS_NAME: Unknown POSIX class name. Since 2.16
 * @G_REGEX_ERROR_POSIX_COLLATING_ELEMENTS_NOT_SUPPORTED: POSIX collating elements are not supported. Since 2.16
 * @G_REGEX_ERROR_HEX_CODE_TOO_LARGE: Character value in "\\x{...}" sequence is too large. Since 2.16
 * @G_REGEX_ERROR_INVALID_CONDITION: Invalid condition "(?(0)". Since 2.16
 * @G_REGEX_ERROR_SINGLE_BYTE_MATCH_IN_LOOKBEHIND: \\C not allowed in lookbehind assertion. Since 2.16
 * @G_REGEX_ERROR_INFINITE_LOOP: Recursive call could loop indefinitely. Since 2.16
 * @G_REGEX_ERROR_MISSING_SUBPATTERN_NAME_TERMINATOR: Missing terminator in subpattern name. Since 2.16
 * @G_REGEX_ERROR_DUPLICATE_SUBPATTERN_NAME: Two named subpatterns have the same name. Since 2.16
 * @G_REGEX_ERROR_MALFORMED_PROPERTY: Malformed "\\P" or "\\p" sequence. Since 2.16
 * @G_REGEX_ERROR_UNKNOWN_PROPERTY: Unknown property name after "\\P" or "\\p". Since 2.16
 * @G_REGEX_ERROR_SUBPATTERN_NAME_TOO_LONG: Subpattern name is too long (maximum 32 characters). Since 2.16
 * @G_REGEX_ERROR_TOO_MANY_SUBPATTERNS: Too many named subpatterns (maximum 10,000). Since 2.16
 * @G_REGEX_ERROR_INVALID_OCTAL_VALUE: Octal value is greater than "\\377". Since 2.16
 * @G_REGEX_ERROR_TOO_MANY_BRANCHES_IN_DEFINE: "DEFINE" group contains more than one branch. Since 2.16
 * @G_REGEX_ERROR_DEFINE_REPETION: Repeating a "DEFINE" group is not allowed. Since 2.16
 * @G_REGEX_ERROR_INCONSISTENT_NEWLINE_OPTIONS: Inconsistent newline options. Since 2.16
 * @G_REGEX_ERROR_MISSING_BACK_REFERENCE: "\\g" is not followed by a braced name or an optionally braced non-zero number. Since 2.16
 *
 * Error codes returned by regular expressions functions.
 *
 * Since: 2.14
 */


/**
 * GRegexEvalCallback:
 * @match_info: the #GMatchInfo generated by the match. Use g_match_info_get_regex() and g_match_info_get_string() if you need the #GRegex or the matched string.
 * @result: a #GString containing the new string
 * @user_data: user data passed to g_regex_replace_eval()
 *
 * Specifies the type of the function passed to g_regex_replace_eval().
 * It is called for each occurrence of the pattern in the string passed
 * to g_regex_replace_eval(), and it should append the replacement to
 * @result.
 *
 * Returns: %FALSE to continue the replacement process, %TRUE to stop it
 * Since: 2.14
 */


/**
 * GRegexMatchFlags:
 * @G_REGEX_MATCH_ANCHORED: The pattern is forced to be "anchored", that is, it is constrained to match only at the first matching point in the string that is being searched. This effect can also be achieved by appropriate constructs in the pattern itself such as the "^" metacharater.
 * @G_REGEX_MATCH_NOTBOL: Specifies that first character of the string is not the beginning of a line, so the circumflex metacharacter should not match before it. Setting this without #G_REGEX_MULTILINE (at compile time) causes circumflex never to match. This option affects only the behaviour of the circumflex metacharacter, it does not affect "\A".
 * @G_REGEX_MATCH_NOTEOL: Specifies that the end of the subject string is not the end of a line, so the dollar metacharacter should not match it nor (except in multiline mode) a newline immediately before it. Setting this without #G_REGEX_MULTILINE (at compile time) causes dollar never to match. This option affects only the behaviour of the dollar metacharacter, it does not affect "\Z" or "\z".
 * @G_REGEX_MATCH_NOTEMPTY: An empty string is not considered to be a valid match if this option is set. If there are alternatives in the pattern, they are tried. If all the alternatives match the empty string, the entire match fails. For example, if the pattern "a?b?" is applied to a string not beginning with "a" or "b", it matches the empty string at the start of the string. With this flag set, this match is not valid, so GRegex searches further into the string for occurrences of "a" or "b".
 * @G_REGEX_MATCH_PARTIAL: Turns on the partial matching feature, for more documentation on partial matching see g_match_info_is_partial_match().
 * @G_REGEX_MATCH_NEWLINE_CR: Overrides the newline definition set when creating a new #GRegex, setting the '\r' character as line terminator.
 * @G_REGEX_MATCH_NEWLINE_LF: Overrides the newline definition set when creating a new #GRegex, setting the '\n' character as line terminator.
 * @G_REGEX_MATCH_NEWLINE_CRLF: Overrides the newline definition set when creating a new #GRegex, setting the '\r\n' characters as line terminator.
 * @G_REGEX_MATCH_NEWLINE_ANY: Overrides the newline definition set when creating a new #GRegex, any newline character or character sequence is recognized.
 *
 * Flags specifying match-time options.
 *
 * Since: 2.14
 */


/**
 * GSignalAccumulator:
 * @ihint: Signal invocation hint, see #GSignalInvocationHint.
 * @return_accu: Accumulator to collect callback return values in, this is the return value of the current signal emission.
 * @handler_return: A #GValue holding the return value of the signal handler.
 * @data: Callback data that was specified when creating the signal.
 *
 * The signal accumulator is a special callback function that can be used
 * to collect return values of the various callbacks that are called
 * during a signal emission. The signal accumulator is specified at signal
 * creation time, if it is left %NULL, no accumulation of callback return
 * values is performed. The return value of signal emissions is then the
 * value returned by the last callback.
 *
 * should be aborted. Returning %FALSE means to abort the
 * current emission and %TRUE is returned for continuation.
 *
 * Returns: The accumulator function returns whether the signal emission
 */


/**
 * GSignalCMarshaller:
 *
 * This is the signature of marshaller functions, required to marshall
 * arrays of parameter values to signal emissions into C language callback
 * invocations. It is merely an alias to #GClosureMarshal since the #GClosure
 * mechanism takes over responsibility of actual function invocation for the
 * signal system.
 */


/**
 * GSignalCVaMarshaller:
 *
 * This is the signature of va_list marshaller functions, an optional
 * marshaller that can be used in some situations to avoid
 * marshalling the signal argument into GValues.
 */


/**
 * GSignalEmissionHook:
 * @ihint: Signal invocation hint, see #GSignalInvocationHint.
 * @n_param_values: the number of parameters to the function, including the instance on which the signal was emitted.
 * @param_values: (array length=n_param_values): the instance on which the signal was emitted, followed by the parameters of the emission.
 * @data: user data associated with the hook.
 *
 * A simple function pointer to get invoked when the signal is emitted. This
 * allows you to tie a hook to the signal type, so that it will trap all
 * emissions of that signal, from any object.
 *
 * You may not attach these to signals created with the #G_SIGNAL_NO_HOOKS flag.
 *
 * hook is disconnected (and destroyed).
 *
 * Returns: whether it wants to stay connected. If it returns %FALSE, the signal
 */


/**
 * GSignalFlags:
 * @G_SIGNAL_RUN_FIRST: Invoke the object method handler in the first emission stage.
 * @G_SIGNAL_RUN_LAST: Invoke the object method handler in the third emission stage.
 * @G_SIGNAL_RUN_CLEANUP: Invoke the object method handler in the last emission stage.
 * @G_SIGNAL_NO_RECURSE: Signals being emitted for an object while currently being in emission for this very object will not be emitted recursively, but instead cause the first emission to be restarted.
 * @G_SIGNAL_DETAILED: This signal supports "::detail" appendices to the signal name upon handler connections and emissions.
 * @G_SIGNAL_ACTION: Action signals are signals that may freely be emitted on alive objects from user code via g_signal_emit() and friends, without the need of being embedded into extra code that performs pre or post emission adjustments on the object. They can also be thought of as object methods which can be called generically by third-party code.
 * @G_SIGNAL_NO_HOOKS: No emissions hooks are supported for this signal.
 * @G_SIGNAL_MUST_COLLECT: Varargs signal emission will always collect the arguments, even if there are no signal handlers connected.  Since 2.30.
 * @G_SIGNAL_DEPRECATED: The signal is deprecated and will be removed in a future version. A warning will be generated if it is connected while running with G_ENABLE_DIAGNOSTIC=1.  Since 2.32.
 *
 * The signal flags are used to specify a signal's behaviour, the overall
 * signal description outlines how especially the RUN flags control the
 * stages of a signal emission.
 */


/**
 * GSignalInvocationHint:
 * @signal_id: The signal id of the signal invoking the callback
 * @detail: The detail passed on for this emission
 * @run_type: The stage the signal emission is currently in, this field will contain one of %G_SIGNAL_RUN_FIRST, %G_SIGNAL_RUN_LAST or %G_SIGNAL_RUN_CLEANUP.
 *
 * The #GSignalInvocationHint structure is used to pass on additional information
 * to callbacks during a signal emission.
 */


/**
 * GSignalMatchType:
 * @G_SIGNAL_MATCH_ID: The signal id must be equal.
 * @G_SIGNAL_MATCH_DETAIL: The signal detail be equal.
 * @G_SIGNAL_MATCH_CLOSURE: The closure must be the same.
 * @G_SIGNAL_MATCH_FUNC: The C closure callback must be the same.
 * @G_SIGNAL_MATCH_DATA: The closure data must be the same.
 * @G_SIGNAL_MATCH_UNBLOCKED: Only unblocked signals may matched.
 *
 * The match types specify what g_signal_handlers_block_matched(),
 * g_signal_handlers_unblock_matched() and g_signal_handlers_disconnect_matched()
 * match signals by.
 */


/**
 * GSignalQuery:
 * @signal_id: The signal id of the signal being queried, or 0 if the signal to be queried was unknown.
 * @signal_name: The signal name.
 * @itype: The interface/instance type that this signal can be emitted for.
 * @signal_flags: The signal flags as passed in to g_signal_new().
 * @return_type: The return type for user callbacks.
 * @n_params: The number of parameters that user callbacks take.
 * @param_types: The individual parameter types for user callbacks, note that the effective callback signature is: <programlisting> @return_type callback (#gpointer     data1, [param_types param_names,] gpointer     data2); </programlisting>
 *
 * A structure holding in-depth information for a specific signal. It is
 * filled in by the g_signal_query() function.
 */


/**
 * GSource:
 *
 * The <structname>GSource</structname> struct is an opaque data type
 * representing an event source.
 */


/**
 * GSourceCallbackFuncs:
 * @ref: Called when a reference is added to the callback object
 * @unref: Called when a reference to the callback object is dropped
 * @get: Called to extract the callback function and data from the callback object. The <structname>GSourceCallbackFuncs</structname> struct contains functions for managing callback objects.
 *
 *
 */


/**
 * GSourceDummyMarshal:
 *
 * This is just a placeholder for #GClosureMarshal,
 * which cannot be used here for dependency reasons.
 */


/**
 * GSourceFunc:
 * @user_data: data passed to the function, set when the source was created with one of the above functions
 *
 * Specifies the type of function passed to g_timeout_add(),
 * g_timeout_add_full(), g_idle_add(), and g_idle_add_full().
 *
 * Returns: %FALSE if the source should be removed
 */


/**
 * GSourceFuncs:
 * @prepare: Called before all the file descriptors are polled. If the source can determine that it is ready here (without waiting for the results of the poll() call) it should return %TRUE. It can also return a @timeout_ value which should be the maximum timeout (in milliseconds) which should be passed to the poll() call. The actual timeout used will be -1 if all sources returned -1, or it will be the minimum of all the @timeout_ values returned which were >= 0.
 * @check: Called after all the file descriptors are polled. The source should return %TRUE if it is ready to be dispatched. Note that some time may have passed since the previous prepare function was called, so the source should be checked again here.
 * @dispatch: Called to dispatch the event source, after it has returned %TRUE in either its @prepare or its @check function. The @dispatch function is passed in a callback function and data. The callback function may be %NULL if the source was never connected to a callback using g_source_set_callback(). The @dispatch function should call the callback function with @user_data and whatever additional parameters are needed for this type of event source.
 * @finalize: Called when the source is finalized.
 *
 * The <structname>GSourceFuncs</structname> struct contains a table of
 * functions used to handle event sources in a generic manner.
 *
 * For idle sources, the prepare and check functions always return %TRUE
 * to indicate that the source is always ready to be processed. The prepare
 * function also returns a timeout value of 0 to ensure that the poll() call
 * doesn't block (since that would be time wasted which could have been spent
 * running the idle function).
 *
 * For timeout sources, the prepare and check functions both return %TRUE
 * if the timeout interval has expired. The prepare function also returns
 * a timeout value to ensure that the poll() call doesn't block too long
 * and miss the next timeout.
 *
 * For file descriptor sources, the prepare function typically returns %FALSE,
 * since it must wait until poll() has been called before it knows whether
 * any events need to be processed. It sets the returned timeout to -1 to
 * indicate that it doesn't mind how long the poll() call blocks. In the
 * check function, it tests the results of the poll() call to see if the
 * required condition has been met, and returns %TRUE if so.
 */


/**
 * GSpawnChildSetupFunc:
 * @user_data: user data to pass to the function.
 *
 * Specifies the type of the setup function passed to g_spawn_async(),
 * g_spawn_sync() and g_spawn_async_with_pipes(), which can, in very
 * limited ways, be used to affect the child's execution.
 *
 * On POSIX platforms, the function is called in the child after GLib
 * has performed all the setup it plans to perform, but before calling
 * exec(). Actions taken in this function will only affect the child,
 * not the parent.
 *
 * On Windows, the function is called in the parent. Its usefulness on
 * Windows is thus questionable. In many cases executing the child setup
 * function in the parent can have ill effects, and you should be very
 * careful when porting software to Windows that uses child setup
 * functions.
 *
 * However, even on POSIX, you are extremely limited in what you can
 * safely do from a #GSpawnChildSetupFunc, because any mutexes that
 * were held by other threads in the parent process at the time of the
 * fork() will still be locked in the child process, and they will
 * never be unlocked (since the threads that held them don't exist in
 * the child). POSIX allows only async-signal-safe functions (see
 * <citerefentry><refentrytitle>signal</refentrytitle><manvolnum>7</manvolnum></citerefentry>)
 * to be called in the child between fork() and exec(), which
 * drastically limits the usefulness of child setup functions.
 *
 * In particular, it is not safe to call any function which may
 * call malloc(), which includes POSIX functions such as setenv().
 * If you need to set up the child environment differently from
 * the parent, you should use g_get_environ(), g_environ_setenv(),
 * and g_environ_unsetenv(), and then pass the complete environment
 * list to the <literal>g_spawn...</literal> function.
 */


/**
 * GSpawnError:
 * @G_SPAWN_ERROR_FORK: Fork failed due to lack of memory.
 * @G_SPAWN_ERROR_READ: Read or select on pipes failed.
 * @G_SPAWN_ERROR_CHDIR: Changing to working directory failed.
 * @G_SPAWN_ERROR_ACCES: execv() returned <literal>EACCES</literal>
 * @G_SPAWN_ERROR_PERM: execv() returned <literal>EPERM</literal>
 * @G_SPAWN_ERROR_TOO_BIG: execv() returned <literal>E2BIG</literal>
 * @G_SPAWN_ERROR_2BIG: deprecated alias for %G_SPAWN_ERROR_TOO_BIG
 * @G_SPAWN_ERROR_NOEXEC: execv() returned <literal>ENOEXEC</literal>
 * @G_SPAWN_ERROR_NAMETOOLONG: execv() returned <literal>ENAMETOOLONG</literal>
 * @G_SPAWN_ERROR_NOENT: execv() returned <literal>ENOENT</literal>
 * @G_SPAWN_ERROR_NOMEM: execv() returned <literal>ENOMEM</literal>
 * @G_SPAWN_ERROR_NOTDIR: execv() returned <literal>ENOTDIR</literal>
 * @G_SPAWN_ERROR_LOOP: execv() returned <literal>ELOOP</literal>
 * @G_SPAWN_ERROR_TXTBUSY: execv() returned <literal>ETXTBUSY</literal>
 * @G_SPAWN_ERROR_IO: execv() returned <literal>EIO</literal>
 * @G_SPAWN_ERROR_NFILE: execv() returned <literal>ENFILE</literal>
 * @G_SPAWN_ERROR_MFILE: execv() returned <literal>EMFILE</literal>
 * @G_SPAWN_ERROR_INVAL: execv() returned <literal>EINVAL</literal>
 * @G_SPAWN_ERROR_ISDIR: execv() returned <literal>EISDIR</literal>
 * @G_SPAWN_ERROR_LIBBAD: execv() returned <literal>ELIBBAD</literal>
 * @G_SPAWN_ERROR_FAILED: Some other fatal failure, <literal>error-&gt;message</literal> should explain.
 *
 * Error codes returned by spawning processes.
 */


/**
 * GSpawnFlags:
 * @G_SPAWN_LEAVE_DESCRIPTORS_OPEN: the parent's open file descriptors will be inherited by the child; otherwise all descriptors except stdin/stdout/stderr will be closed before calling exec() in the child.
 * @G_SPAWN_DO_NOT_REAP_CHILD: the child will not be automatically reaped; you must use g_child_watch_add() yourself (or call waitpid() or handle <literal>SIGCHLD</literal> yourself), or the child will become a zombie.
 * @G_SPAWN_SEARCH_PATH: <literal>argv[0]</literal> need not be an absolute path, it will be looked for in the user's <envar>PATH</envar>.
 * @G_SPAWN_STDOUT_TO_DEV_NULL: the child's standard output will be discarded, instead of going to the same location as the parent's standard output.
 * @G_SPAWN_STDERR_TO_DEV_NULL: the child's standard error will be discarded.
 * @G_SPAWN_CHILD_INHERITS_STDIN: the child will inherit the parent's standard input (by default, the child's standard input is attached to <filename>/dev/null</filename>).
 * @G_SPAWN_FILE_AND_ARGV_ZERO: the first element of <literal>argv</literal> is the file to execute, while the remaining elements are the actual argument vector to pass to the file. Normally g_spawn_async_with_pipes() uses <literal>argv[0]</literal> as the file to execute, and passes all of <literal>argv</literal> to the child.
 *
 * Flags passed to g_spawn_sync(), g_spawn_async() and g_spawn_async_with_pipes().
 */


/**
 * GStrv:
 *
 * A C representable type name for #G_TYPE_STRV.
 */


/**
 * GTestLogFatalFunc:
 * @log_domain: the log domain of the message
 * @log_level: the log level of the message (including the fatal and recursion flags)
 * @message: the message to process
 * @user_data: user data, set in g_test_log_set_fatal_handler()
 *
 * Specifies the prototype of fatal log handler functions.
 *
 * Returns: %TRUE if the program should abort, %FALSE otherwise
 * Since: 2.22
 */


/**
 * GTimeSpan:
 *
 * A value representing an interval of time, in microseconds.
 *
 * Since: 2.26
 */


/**
 * GTimeType:
 * @G_TIME_TYPE_STANDARD: the time is in local standard time
 * @G_TIME_TYPE_DAYLIGHT: the time is in local daylight time
 * @G_TIME_TYPE_UNIVERSAL: the time is in UTC
 *
 * Disambiguates a given time in two ways.
 *
 * First, specifies if the given time is in universal or local time.
 *
 * Second, if the time is in local time, specifies if it is local
 * standard time or local daylight time.  This is important for the case
 * where the same local time occurs twice (during daylight savings time
 * transitions, for example).
 */


/**
 * GToggleNotify:
 * @data: Callback data passed to g_object_add_toggle_ref()
 * @object: The object on which g_object_add_toggle_ref() was called.
 * @is_last_ref: %TRUE if the toggle reference is now the last reference to the object. %FALSE if the toggle reference was the last reference and there are now other references.
 *
 * A callback function used for notification when the state
 * of a toggle reference changes. See g_object_add_toggle_ref().
 */


/**
 * GTranslateFunc:
 * @str: the untranslated string
 * @data: user data specified when installing the function, e.g. in g_option_group_set_translate_func()
 *
 * The type of functions which are used to translate user-visible
 * strings, for <option>--help</option> output.
 *
 * The returned string is owned by GLib and must not be freed.
 *
 * Returns: a translation of the string for the current locale.
 */


/**
 * GType:
 *
 * A numerical value which represents the unique identifier of a registered
 * type.
 */


/**
 * GTypeCValue:
 * @v_int: the field for holding integer values
 * @v_long: the field for holding long integer values
 * @v_int64: the field for holding 64 bit integer values
 * @v_double: the field for holding floating point values
 * @v_pointer: the field for holding pointers
 *
 * A union holding one collected value.
 */


/**
 * GTypeClass:
 *
 * An opaque structure used as the base of all classes.
 */


/**
 * GTypeClassCacheFunc:
 * @cache_data: data that was given to the g_type_add_class_cache_func() call
 * @g_class: The #GTypeClass structure which is unreferenced
 *
 * A callback function which is called when the reference count of a class
 * drops to zero. It may use g_type_class_ref() to prevent the class from
 * being freed. You should not call g_type_class_unref() from a
 * #GTypeClassCacheFunc function to prevent infinite recursion, use
 * g_type_class_unref_uncached() instead.
 *
 * The functions have to check the class id passed in to figure
 * whether they actually want to cache the class of this type, since all
 * classes are routed through the same #GTypeClassCacheFunc chain.
 *
 * called, %FALSE to continue.
 *
 * Returns: %TRUE to stop further #GTypeClassCacheFunc<!-- -->s from being
 */


/**
 * GTypeDebugFlags:
 * @G_TYPE_DEBUG_NONE: Print no messages.
 * @G_TYPE_DEBUG_OBJECTS: Print messages about object bookkeeping.
 * @G_TYPE_DEBUG_SIGNALS: Print messages about signal emissions.
 * @G_TYPE_DEBUG_MASK: Mask covering all debug flags.
 *
 * The <type>GTypeDebugFlags</type> enumeration values can be passed to
 * g_type_init_with_debug_flags() to trigger debugging messages during runtime.
 * Note that the messages can also be triggered by setting the
 * <envar>GOBJECT_DEBUG</envar> environment variable to a ':'-separated list of
 * "objects" and "signals".
 */


/**
 * GTypeFlags:
 * @G_TYPE_FLAG_ABSTRACT: Indicates an abstract type. No instances can be created for an abstract type.
 * @G_TYPE_FLAG_VALUE_ABSTRACT: Indicates an abstract value type, i.e. a type that introduces a value table, but can't be used for g_value_init().
 *
 * Bit masks used to check or determine characteristics of a type.
 */


/**
 * GTypeFundamentalFlags:
 * @G_TYPE_FLAG_CLASSED: Indicates a classed type.
 * @G_TYPE_FLAG_INSTANTIATABLE: Indicates an instantiable type (implies classed).
 * @G_TYPE_FLAG_DERIVABLE: Indicates a flat derivable type.
 * @G_TYPE_FLAG_DEEP_DERIVABLE: Indicates a deep derivable type (implies derivable).
 *
 * Bit masks used to check or determine specific characteristics of a
 * fundamental type.
 */


/**
 * GTypeFundamentalInfo:
 * @type_flags: #GTypeFundamentalFlags describing the characteristics of the fundamental type
 *
 * A structure that provides information to the type system which is
 * used specifically for managing fundamental types.
 */


/**
 * GTypeInfo:
 * @class_size: Size of the class structure (required for interface, classed and instantiatable types).
 * @base_init: Location of the base initialization function (optional).
 * @base_finalize: Location of the base finalization function (optional).
 * @class_init: Location of the class initialization function for classed and instantiatable types. Location of the default vtable inititalization function for interface types. (optional) This function is used both to fill in virtual functions in the class or default vtable, and to do type-specific setup such as registering signals and object properties.
 * @class_finalize: Location of the class finalization function for classed and instantiatable types. Location fo the default vtable finalization function for interface types. (optional)
 * @class_data: User-supplied data passed to the class init/finalize functions.
 * @instance_size: Size of the instance (object) structure (required for instantiatable types only).
 * @n_preallocs: Prior to GLib 2.10, it specified the number of pre-allocated (cached) instances to reserve memory for (0 indicates no caching). Since GLib 2.10, it is ignored, since instances are allocated with the <link linkend="glib-Memory-Slices">slice allocator</link> now.
 * @instance_init: Location of the instance initialization function (optional, for instantiatable types only).
 * @value_table: A #GTypeValueTable function table for generic handling of GValues of this type (usually only useful for fundamental types).
 *
 * This structure is used to provide the type system with the information
 * required to initialize and destruct (finalize) a type's class and
 * its instances.
 * The initialized structure is passed to the g_type_register_static() function
 * (or is copied into the provided #GTypeInfo structure in the
 * g_type_plugin_complete_type_info()). The type system will perform a deep
 * copy of this structure, so its memory does not need to be persistent
 * across invocation of g_type_register_static().
 */


/**
 * GTypeInstance:
 *
 * An opaque structure used as the base of all type instances.
 */


/**
 * GTypeInterface:
 *
 * An opaque structure used as the base of all interface types.
 */


/**
 * GTypeInterfaceCheckFunc:
 * @check_data: data passed to g_type_add_interface_check().
 * @g_iface: the interface that has been initialized
 *
 * A callback called after an interface vtable is initialized.
 * See g_type_add_interface_check().
 *
 * Since: 2.4
 */


/**
 * GTypeModule:
 * @name: the name of the module
 *
 * The members of the <structname>GTypeModule</structname> structure should not
 * be accessed directly, except for the @name field.
 */


/**
 * GTypeModuleClass:
 * @parent_class: the parent class
 * @load: loads the module and registers one or more types using g_type_module_register_type().
 * @unload: unloads the module
 *
 * In order to implement dynamic loading of types based on #GTypeModule,
 * the @load and @unload functions in #GTypeModuleClass must be implemented.
 */


/**
 * GTypePlugin:
 *
 * The <structname>GTypePlugin</structname> typedef is used as a placeholder
 * for objects that implement the <structname>GTypePlugin</structname>
 * interface.
 */


/**
 * GTypePluginClass:
 * @use_plugin: Increases the use count of the plugin.
 * @unuse_plugin: Decreases the use count of the plugin.
 * @complete_type_info: Fills in the #GTypeInfo and #GTypeValueTable structs for the type. The structs are initialized with <literal>memset(s, 0, sizeof (s))</literal> before calling this function.
 * @complete_interface_info: Fills in missing parts of the #GInterfaceInfo for the interface. The structs is initialized with <literal>memset(s, 0, sizeof (s))</literal> before calling this function.
 *
 * The #GTypePlugin interface is used by the type system in order to handle
 * the lifecycle of dynamically loaded types.
 */


/**
 * GTypePluginCompleteInterfaceInfo:
 * @plugin: the #GTypePlugin
 * @instance_type: the #GType of an instantiable type to which the interface is added
 * @interface_type: the #GType of the interface whose info is completed
 * @info: the #GInterfaceInfo to fill in
 *
 * The type of the @complete_interface_info function of #GTypePluginClass.
 */


/**
 * GTypePluginCompleteTypeInfo:
 * @plugin: the #GTypePlugin
 * @g_type: the #GType whose info is completed
 * @info: the #GTypeInfo struct to fill in
 * @value_table: the #GTypeValueTable to fill in
 *
 * The type of the @complete_type_info function of #GTypePluginClass.
 */


/**
 * GTypePluginUnuse:
 * @plugin: the #GTypePlugin whose use count should be decreased
 *
 * The type of the @unuse_plugin function of #GTypePluginClass.
 */


/**
 * GTypePluginUse:
 * @plugin: the #GTypePlugin whose use count should be increased
 *
 * The type of the @use_plugin function of #GTypePluginClass, which gets called
 * to increase the use count of @plugin.
 */


/**
 * GTypeQuery:
 * @type: the #GType value of the type.
 * @type_name: the name of the type.
 * @class_size: the size of the class structure.
 * @instance_size: the size of the instance structure.
 *
 * A structure holding information for a specific type. It is
 * filled in by the g_type_query() function.
 */


/**
 * GTypeValueTable:
 * @value_init: Default initialize @values contents by poking values directly into the value->data array. The data array of the #GValue passed into this function was zero-filled with <function>memset()</function>, so no care has to be taken to free any old contents. E.g. for the implementation of a string value that may never be %NULL, the implementation might look like: |[ value->data[0].v_pointer = g_strdup (""); ]|
 * @value_free: Free any old contents that might be left in the data array of the passed in @value. No resources may remain allocated through the #GValue contents after this function returns. E.g. for our above string type: |[ // only free strings without a specific flag for static storage if (!(value->data[1].v_uint & G_VALUE_NOCOPY_CONTENTS)) g_free (value->data[0].v_pointer); ]|
 * @value_copy: @dest_value is a #GValue with zero-filled data section and @src_value is a properly setup #GValue of same or derived type. The purpose of this function is to copy the contents of @src_value into @dest_value in a way, that even after @src_value has been freed, the contents of @dest_value remain valid. String type example: |[ dest_value->data[0].v_pointer = g_strdup (src_value->data[0].v_pointer); ]|
 * @value_peek_pointer: If the value contents fit into a pointer, such as objects or strings, return this pointer, so the caller can peek at the current contents. To extend on our above string example: |[ return value->data[0].v_pointer; ]|
 * @collect_format: A string format describing how to collect the contents of this value bit-by-bit. Each character in the format represents an argument to be collected, and the characters themselves indicate the type of the argument. Currently supported arguments are: <variablelist> <varlistentry><term /><listitem><para> 'i' - Integers. passed as collect_values[].v_int. </para></listitem></varlistentry> <varlistentry><term /><listitem><para> 'l' - Longs. passed as collect_values[].v_long. </para></listitem></varlistentry> <varlistentry><term /><listitem><para> 'd' - Doubles. passed as collect_values[].v_double. </para></listitem></varlistentry> <varlistentry><term /><listitem><para> 'p' - Pointers. passed as collect_values[].v_pointer. </para></listitem></varlistentry> </variablelist> It should be noted that for variable argument list construction, ANSI C promotes every type smaller than an integer to an int, and floats to doubles. So for collection of short int or char, 'i' needs to be used, and for collection of floats 'd'.
 * @collect_value: The collect_value() function is responsible for converting the values collected from a variable argument list into contents suitable for storage in a GValue. This function should setup @value similar to value_init(); e.g. for a string value that does not allow %NULL pointers, it needs to either spew an error, or do an implicit conversion by storing an empty string. The @value passed in to this function has a zero-filled data array, so just like for value_init() it is guaranteed to not contain any old contents that might need freeing. @n_collect_values is exactly the string length of @collect_format, and @collect_values is an array of unions #GTypeCValue with length @n_collect_values, containing the collected values according to @collect_format. @collect_flags is an argument provided as a hint by the caller. It may contain the flag %G_VALUE_NOCOPY_CONTENTS indicating, that the collected value contents may be considered "static" for the duration of the @value lifetime. Thus an extra copy of the contents stored in @collect_values is not required for assignment to @value. For our above string example, we continue with: |[ if (!collect_values[0].v_pointer) value->data[0].v_pointer = g_strdup (""); else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) { value->data[0].v_pointer = collect_values[0].v_pointer; // keep a flag for the value_free() implementation to not free this string value->data[1].v_uint = G_VALUE_NOCOPY_CONTENTS; } else value->data[0].v_pointer = g_strdup (collect_values[0].v_pointer); return NULL; ]| It should be noted, that it is generally a bad idea to follow the #G_VALUE_NOCOPY_CONTENTS hint for reference counted types. Due to reentrancy requirements and reference count assertions performed by the signal emission code, reference counts should always be incremented for reference counted contents stored in the value->data array.  To deviate from our string example for a moment, and taking a look at an exemplary implementation for collect_value() of #GObject: |[ if (collect_values[0].v_pointer) { GObject *object = G_OBJECT (collect_values[0].v_pointer); // never honour G_VALUE_NOCOPY_CONTENTS for ref-counted types value->data[0].v_pointer = g_object_ref (object); return NULL; } else return g_strdup_printf ("Object passed as invalid NULL pointer"); } ]| The reference count for valid objects is always incremented, regardless of @collect_flags. For invalid objects, the example returns a newly allocated string without altering @value. Upon success, collect_value() needs to return %NULL. If, however, an error condition occurred, collect_value() may spew an error by returning a newly allocated non-%NULL string, giving a suitable description of the error condition. The calling code makes no assumptions about the @value contents being valid upon error returns, @value is simply thrown away without further freeing. As such, it is a good idea to not allocate #GValue contents, prior to returning an error, however, collect_values() is not obliged to return a correctly setup @value for error returns, simply because any non-%NULL return is considered a fatal condition so further program behaviour is undefined.
 * @lcopy_format: Format description of the arguments to collect for @lcopy_value, analogous to @collect_format. Usually, @lcopy_format string consists only of 'p's to provide lcopy_value() with pointers to storage locations.
 * @lcopy_value: This function is responsible for storing the @value contents into arguments passed through a variable argument list which got collected into @collect_values according to @lcopy_format. @n_collect_values equals the string length of @lcopy_format, and @collect_flags may contain %G_VALUE_NOCOPY_CONTENTS. In contrast to collect_value(), lcopy_value() is obliged to always properly support %G_VALUE_NOCOPY_CONTENTS. Similar to collect_value() the function may prematurely abort by returning a newly allocated string describing an error condition. To complete the string example: |[ gchar **string_p = collect_values[0].v_pointer; if (!string_p) return g_strdup_printf ("string location passed as NULL"); if (collect_flags & G_VALUE_NOCOPY_CONTENTS) *string_p = value->data[0].v_pointer; else *string_p = g_strdup (value->data[0].v_pointer); ]| And an illustrative version of lcopy_value() for reference-counted types: |[ GObject **object_p = collect_values[0].v_pointer; if (!object_p) return g_strdup_printf ("object location passed as NULL"); if (!value->data[0].v_pointer) *object_p = NULL; else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) /&ast; always honour &ast;/ *object_p = value->data[0].v_pointer; else *object_p = g_object_ref (value->data[0].v_pointer); return NULL; ]|
 *
 * The #GTypeValueTable provides the functions required by the #GValue implementation,
 * to serve as a container for values of a type.
 */


/**
 * GUnicodeBreakType:
 * @G_UNICODE_BREAK_MANDATORY: Mandatory Break (BK)
 * @G_UNICODE_BREAK_CARRIAGE_RETURN: Carriage Return (CR)
 * @G_UNICODE_BREAK_LINE_FEED: Line Feed (LF)
 * @G_UNICODE_BREAK_COMBINING_MARK: Attached Characters and Combining Marks (CM)
 * @G_UNICODE_BREAK_SURROGATE: Surrogates (SG)
 * @G_UNICODE_BREAK_ZERO_WIDTH_SPACE: Zero Width Space (ZW)
 * @G_UNICODE_BREAK_INSEPARABLE: Inseparable (IN)
 * @G_UNICODE_BREAK_NON_BREAKING_GLUE: Non-breaking ("Glue") (GL)
 * @G_UNICODE_BREAK_CONTINGENT: Contingent Break Opportunity (CB)
 * @G_UNICODE_BREAK_SPACE: Space (SP)
 * @G_UNICODE_BREAK_AFTER: Break Opportunity After (BA)
 * @G_UNICODE_BREAK_BEFORE: Break Opportunity Before (BB)
 * @G_UNICODE_BREAK_BEFORE_AND_AFTER: Break Opportunity Before and After (B2)
 * @G_UNICODE_BREAK_HYPHEN: Hyphen (HY)
 * @G_UNICODE_BREAK_NON_STARTER: Nonstarter (NS)
 * @G_UNICODE_BREAK_OPEN_PUNCTUATION: Opening Punctuation (OP)
 * @G_UNICODE_BREAK_CLOSE_PUNCTUATION: Closing Punctuation (CL)
 * @G_UNICODE_BREAK_QUOTATION: Ambiguous Quotation (QU)
 * @G_UNICODE_BREAK_EXCLAMATION: Exclamation/Interrogation (EX)
 * @G_UNICODE_BREAK_IDEOGRAPHIC: Ideographic (ID)
 * @G_UNICODE_BREAK_NUMERIC: Numeric (NU)
 * @G_UNICODE_BREAK_INFIX_SEPARATOR: Infix Separator (Numeric) (IS)
 * @G_UNICODE_BREAK_SYMBOL: Symbols Allowing Break After (SY)
 * @G_UNICODE_BREAK_ALPHABETIC: Ordinary Alphabetic and Symbol Characters (AL)
 * @G_UNICODE_BREAK_PREFIX: Prefix (Numeric) (PR)
 * @G_UNICODE_BREAK_POSTFIX: Postfix (Numeric) (PO)
 * @G_UNICODE_BREAK_COMPLEX_CONTEXT: Complex Content Dependent (South East Asian) (SA)
 * @G_UNICODE_BREAK_AMBIGUOUS: Ambiguous (Alphabetic or Ideographic) (AI)
 * @G_UNICODE_BREAK_UNKNOWN: Unknown (XX)
 * @G_UNICODE_BREAK_NEXT_LINE: Next Line (NL)
 * @G_UNICODE_BREAK_WORD_JOINER: Word Joiner (WJ)
 * @G_UNICODE_BREAK_HANGUL_L_JAMO: Hangul L Jamo (JL)
 * @G_UNICODE_BREAK_HANGUL_V_JAMO: Hangul V Jamo (JV)
 * @G_UNICODE_BREAK_HANGUL_T_JAMO: Hangul T Jamo (JT)
 * @G_UNICODE_BREAK_HANGUL_LV_SYLLABLE: Hangul LV Syllable (H2)
 * @G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE: Hangul LVT Syllable (H3)
 * @G_UNICODE_BREAK_CLOSE_PARANTHESIS: Closing Parenthesis (CP). Since 2.28
 * @G_UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER: Conditional Japanese Starter (CJ). Since: 2.32
 * @G_UNICODE_BREAK_HEBREW_LETTER: Hebrew Letter (HL). Since: 2.32
 *
 * These are the possible line break classifications.
 *
 * The five Hangul types were added in Unicode 4.1, so, has been
 * introduced in GLib 2.10. Note that new types may be added in the future.
 * Applications should be ready to handle unknown values.
 * They may be regarded as %G_UNICODE_BREAK_UNKNOWN.
 *
 * See <ulink url="http://www.unicode.org/unicode/reports/tr14/">http://www.unicode.org/unicode/reports/tr14/</ulink>.
 */


/**
 * GUnicodeScript:
 * @G_UNICODE_SCRIPT_COMMON: a character used by multiple different scripts
 * @G_UNICODE_SCRIPT_INHERITED: a mark glyph that takes its script from the i                             base glyph to which it is attached
 * @G_UNICODE_SCRIPT_ARABIC: Arabic
 * @G_UNICODE_SCRIPT_ARMENIAN: Armenian
 * @G_UNICODE_SCRIPT_BENGALI: Bengali
 * @G_UNICODE_SCRIPT_BOPOMOFO: Bopomofo
 * @G_UNICODE_SCRIPT_CHEROKEE: Cherokee
 * @G_UNICODE_SCRIPT_COPTIC: Coptic
 * @G_UNICODE_SCRIPT_CYRILLIC: Cyrillic
 * @G_UNICODE_SCRIPT_DESERET: Deseret
 * @G_UNICODE_SCRIPT_DEVANAGARI: Devanagari
 * @G_UNICODE_SCRIPT_ETHIOPIC: Ethiopic
 * @G_UNICODE_SCRIPT_GEORGIAN: Georgian
 * @G_UNICODE_SCRIPT_GOTHIC: Gothic
 * @G_UNICODE_SCRIPT_GREEK: Greek
 * @G_UNICODE_SCRIPT_GUJARATI: Gujarati
 * @G_UNICODE_SCRIPT_GURMUKHI: Gurmukhi
 * @G_UNICODE_SCRIPT_HAN: Han
 * @G_UNICODE_SCRIPT_HANGUL: Hangul
 * @G_UNICODE_SCRIPT_HEBREW: Hebrew
 * @G_UNICODE_SCRIPT_HIRAGANA: Hiragana
 * @G_UNICODE_SCRIPT_KANNADA: Kannada
 * @G_UNICODE_SCRIPT_KATAKANA: Katakana
 * @G_UNICODE_SCRIPT_KHMER: Khmer
 * @G_UNICODE_SCRIPT_LAO: Lao
 * @G_UNICODE_SCRIPT_LATIN: Latin
 * @G_UNICODE_SCRIPT_MALAYALAM: Malayalam
 * @G_UNICODE_SCRIPT_MONGOLIAN: Mongolian
 * @G_UNICODE_SCRIPT_MYANMAR: Myanmar
 * @G_UNICODE_SCRIPT_OGHAM: Ogham
 * @G_UNICODE_SCRIPT_OLD_ITALIC: Old Italic
 * @G_UNICODE_SCRIPT_ORIYA: Oriya
 * @G_UNICODE_SCRIPT_RUNIC: Runic
 * @G_UNICODE_SCRIPT_SINHALA: Sinhala
 * @G_UNICODE_SCRIPT_SYRIAC: Syriac
 * @G_UNICODE_SCRIPT_TAMIL: Tamil
 * @G_UNICODE_SCRIPT_TELUGU: Telugu
 * @G_UNICODE_SCRIPT_THAANA: Thaana
 * @G_UNICODE_SCRIPT_THAI: Thai
 * @G_UNICODE_SCRIPT_TIBETAN: Tibetan Canadian Aboriginal
 * @G_UNICODE_SCRIPT_YI: Yi
 * @G_UNICODE_SCRIPT_TAGALOG: Tagalog
 * @G_UNICODE_SCRIPT_HANUNOO: Hanunoo
 * @G_UNICODE_SCRIPT_BUHID: Buhid
 * @G_UNICODE_SCRIPT_TAGBANWA: Tagbanwa
 * @G_UNICODE_SCRIPT_BRAILLE: Braille
 * @G_UNICODE_SCRIPT_CYPRIOT: Cypriot
 * @G_UNICODE_SCRIPT_LIMBU: Limbu
 * @G_UNICODE_SCRIPT_OSMANYA: Osmanya
 * @G_UNICODE_SCRIPT_SHAVIAN: Shavian
 * @G_UNICODE_SCRIPT_LINEAR_B: Linear B
 * @G_UNICODE_SCRIPT_TAI_LE: Tai Le
 * @G_UNICODE_SCRIPT_UGARITIC: Ugaritic New Tai Lue
 * @G_UNICODE_SCRIPT_BUGINESE: Buginese
 * @G_UNICODE_SCRIPT_GLAGOLITIC: Glagolitic
 * @G_UNICODE_SCRIPT_TIFINAGH: Tifinagh Syloti Nagri Old Persian
 * @G_UNICODE_SCRIPT_KHAROSHTHI: Kharoshthi
 * @G_UNICODE_SCRIPT_UNKNOWN: an unassigned code point
 * @G_UNICODE_SCRIPT_BALINESE: Balinese
 * @G_UNICODE_SCRIPT_CUNEIFORM: Cuneiform
 * @G_UNICODE_SCRIPT_PHOENICIAN: Phoenician
 * @G_UNICODE_SCRIPT_PHAGS_PA: Phags-pa
 * @G_UNICODE_SCRIPT_NKO: N'Ko
 * @G_UNICODE_SCRIPT_KAYAH_LI: Kayah Li. Since 2.16.3
 * @G_UNICODE_SCRIPT_LEPCHA: Lepcha. Since 2.16.3
 * @G_UNICODE_SCRIPT_REJANG: Rejang. Since 2.16.3
 * @G_UNICODE_SCRIPT_SUNDANESE: Sundanese. Since 2.16.3
 * @G_UNICODE_SCRIPT_SAURASHTRA: Saurashtra. Since 2.16.3
 * @G_UNICODE_SCRIPT_CHAM: Cham. Since 2.16.3
 * @G_UNICODE_SCRIPT_OL_CHIKI: Ol Chiki. Since 2.16.3
 * @G_UNICODE_SCRIPT_VAI: Vai. Since 2.16.3
 * @G_UNICODE_SCRIPT_CARIAN: Carian. Since 2.16.3
 * @G_UNICODE_SCRIPT_LYCIAN: Lycian. Since 2.16.3
 * @G_UNICODE_SCRIPT_LYDIAN: Lydian. Since 2.16.3
 * @G_UNICODE_SCRIPT_AVESTAN: Avestan. Since 2.26
 * @G_UNICODE_SCRIPT_BAMUM: Bamum. Since 2.26 Egyptian Hieroglpyhs. Since 2.26 Imperial Aramaic. Since 2.26 Inscriptional Pahlavi. Since 2.26 Inscriptional Parthian. Since 2.26
 * @G_UNICODE_SCRIPT_JAVANESE: Javanese. Since 2.26
 * @G_UNICODE_SCRIPT_KAITHI: Kaithi. Since 2.26
 * @G_UNICODE_SCRIPT_LISU: Lisu. Since 2.26 Meetei Mayek. Since 2.26 Old South Arabian. Since 2.26
 * @G_UNICODE_SCRIPT_OLD_TURKIC: Old Turkic. Since 2.28
 * @G_UNICODE_SCRIPT_SAMARITAN: Samaritan. Since 2.26
 * @G_UNICODE_SCRIPT_TAI_THAM: Tai Tham. Since 2.26
 * @G_UNICODE_SCRIPT_TAI_VIET: Tai Viet. Since 2.26
 * @G_UNICODE_SCRIPT_BATAK: Batak. Since 2.28
 * @G_UNICODE_SCRIPT_BRAHMI: Brahmi. Since 2.28
 * @G_UNICODE_SCRIPT_MANDAIC: Mandaic. Since 2.28
 * @G_UNICODE_SCRIPT_CHAKMA: Chakma. Since: 2.32
 * @G_UNICODE_SCRIPT_MEROITIC_CURSIVE: Meroitic Cursive. Since: 2.32
 * @G_UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS, Meroitic Hieroglyphs. Since: 2.32
 * @G_UNICODE_SCRIPT_MIAO: Miao. Since: 2.32
 * @G_UNICODE_SCRIPT_SHARADA: Sharada. Since: 2.32
 * @G_UNICODE_SCRIPT_SORA_SOMPENG: Sora Sompeng. Since: 2.32
 * @G_UNICODE_SCRIPT_TAKRI: Takri. Since: 2.32
 *
 * The #GUnicodeScript enumeration identifies different writing
 * systems. The values correspond to the names as defined in the
 * Unicode standard. The enumeration has been added in GLib 2.14,
 * and is interchangeable with #PangoScript.
 *
 * Note that new types may be added in the future. Applications
 * should be ready to handle unknown values.
 * See <ulink
 * url="http://www.unicode.org/reports/tr24/">Unicode Standard Annex
 * #24: Script names</ulink>.
 */


/**
 * GUnicodeType:
 * @G_UNICODE_CONTROL: General category "Other, Control" (Cc)
 * @G_UNICODE_FORMAT: General category "Other, Format" (Cf)
 * @G_UNICODE_UNASSIGNED: General category "Other, Not Assigned" (Cn)
 * @G_UNICODE_PRIVATE_USE: General category "Other, Private Use" (Co)
 * @G_UNICODE_SURROGATE: General category "Other, Surrogate" (Cs)
 * @G_UNICODE_LOWERCASE_LETTER: General category "Letter, Lowercase" (Ll)
 * @G_UNICODE_MODIFIER_LETTER: General category "Letter, Modifier" (Lm)
 * @G_UNICODE_OTHER_LETTER: General category "Letter, Other" (Lo)
 * @G_UNICODE_TITLECASE_LETTER: General category "Letter, Titlecase" (Lt)
 * @G_UNICODE_UPPERCASE_LETTER: General category "Letter, Uppercase" (Lu)
 * @G_UNICODE_SPACING_MARK: General category "Mark, Spacing" (Mc)
 * @G_UNICODE_ENCLOSING_MARK: General category "Mark, Enclosing" (Me)
 * @G_UNICODE_NON_SPACING_MARK: General category "Mark, Nonspacing" (Mn)
 * @G_UNICODE_DECIMAL_NUMBER: General category "Number, Decimal Digit" (Nd)
 * @G_UNICODE_LETTER_NUMBER: General category "Number, Letter" (Nl)
 * @G_UNICODE_OTHER_NUMBER: General category "Number, Other" (No)
 * @G_UNICODE_CONNECT_PUNCTUATION: General category "Punctuation, Connector" (Pc)
 * @G_UNICODE_DASH_PUNCTUATION: General category "Punctuation, Dash" (Pd)
 * @G_UNICODE_CLOSE_PUNCTUATION: General category "Punctuation, Close" (Pe)
 * @G_UNICODE_FINAL_PUNCTUATION: General category "Punctuation, Final quote" (Pf)
 * @G_UNICODE_INITIAL_PUNCTUATION: General category "Punctuation, Initial quote" (Pi)
 * @G_UNICODE_OTHER_PUNCTUATION: General category "Punctuation, Other" (Po)
 * @G_UNICODE_OPEN_PUNCTUATION: General category "Punctuation, Open" (Ps)
 * @G_UNICODE_CURRENCY_SYMBOL: General category "Symbol, Currency" (Sc)
 * @G_UNICODE_MODIFIER_SYMBOL: General category "Symbol, Modifier" (Sk)
 * @G_UNICODE_MATH_SYMBOL: General category "Symbol, Math" (Sm)
 * @G_UNICODE_OTHER_SYMBOL: General category "Symbol, Other" (So)
 * @G_UNICODE_LINE_SEPARATOR: General category "Separator, Line" (Zl)
 * @G_UNICODE_PARAGRAPH_SEPARATOR: General category "Separator, Paragraph" (Zp)
 * @G_UNICODE_SPACE_SEPARATOR: General category "Separator, Space" (Zs)
 *
 * These are the possible character classifications from the
 * Unicode specification.
 * See <ulink url="http://www.unicode.org/Public/UNIDATA/UnicodeData.html">http://www.unicode.org/Public/UNIDATA/UnicodeData.html</ulink>.
 */


/**
 * GUserDirectory:
 * @G_USER_DIRECTORY_DESKTOP: the user's Desktop directory
 * @G_USER_DIRECTORY_DOCUMENTS: the user's Documents directory
 * @G_USER_DIRECTORY_DOWNLOAD: the user's Downloads directory
 * @G_USER_DIRECTORY_MUSIC: the user's Music directory
 * @G_USER_DIRECTORY_PICTURES: the user's Pictures directory
 * @G_USER_DIRECTORY_PUBLIC_SHARE: the user's shared directory
 * @G_USER_DIRECTORY_TEMPLATES: the user's Templates directory
 * @G_USER_DIRECTORY_VIDEOS: the user's Movies directory
 * @G_USER_N_DIRECTORIES: the number of enum values
 *
 * These are logical ids for special directories which are defined
 * depending on the platform used. You should use g_get_user_special_dir()
 * to retrieve the full path associated to the logical id.
 *
 * The #GUserDirectory enumeration can be extended at later date. Not
 * every platform has a directory for every logical id in this
 * enumeration.
 *
 * Since: 2.14
 */


/**
 * GValue:
 *
 * An opaque structure used to hold different types of values.
 * The data within the structure has protected scope: it is accessible only
 * to functions within a #GTypeValueTable structure, or implementations of
 * the g_value_*() API. That is, code portions which implement new fundamental
 * types.
 * #GValue users cannot make any assumptions about how data is stored
 * within the 2 element @data union, and the @g_type member should
 * only be accessed through the G_VALUE_TYPE() macro.
 */


/**
 * GValueArray:
 * @n_values: number of values contained in the array
 * @values: array of values
 *
 * A #GValueArray contains an array of #GValue elements.
 */


/**
 * GValueTransform:
 * @src_value: Source value.
 * @dest_value: Target value.
 *
 * The type of value transformation functions which can be registered with
 * g_value_register_transform_func().
 */


/**
 * GVariantType:
 *
 * A type in the GVariant type system.
 *
 * Two types may not be compared by value; use g_variant_type_equal() or
 * g_variant_type_is_subtype_of().  May be copied using
 * g_variant_type_copy() and freed using g_variant_type_free().
 */


/**
 * GVoidFunc:
 *
 * Declares a type of function which takes no arguments
 * and has no return value. It is used to specify the type
 * function passed to g_atexit().
 */


/**
 * GWeakNotify:
 * @data: data that was provided when the weak reference was established
 * @where_the_object_was: the object being finalized
 *
 * A #GWeakNotify function can be added to an object as a callback that gets
 * triggered when the object is finalized. Since the object is already being
 * finalized when the #GWeakNotify is called, there's not much you could do
 * with the object, apart from e.g. using its address as hash-index or the like.
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
 * G_BOOKMARK_FILE_ERROR:
 *
 * Error domain for bookmark file parsing.
 * Errors in this domain will be from the #GBookmarkFileError
 * enumeration. See #GError for information on error domains.
 */


/**
 * G_BREAKPOINT:
 *
 * Inserts a breakpoint instruction into the code.
 *
 * On x86 and alpha systems this is implemented as a soft interrupt
 * and on other architectures it raises a <literal>SIGTRAP</literal> signal.
 */


/**
 * G_CALLBACK:
 * @f: a function pointer.
 *
 * Cast a function pointer to a #GCallback.
 */


/**
 * G_CCLOSURE_SWAP_DATA:
 * @cclosure: a #GCClosure
 *
 * Checks whether the user data of the #GCClosure should be passed as the
 * first parameter to the callback. See g_cclosure_new_swap().
 *
 * Returns: %TRUE if data has to be swapped.
 */


/**
 * G_CLOSURE_NEEDS_MARSHAL:
 * @closure: a #GClosure
 *
 * Check if the closure still needs a marshaller. See g_closure_set_marshal().
 *
 * @closure.
 *
 * Returns: %TRUE if a #GClosureMarshal marshaller has not yet been set on
 */


/**
 * G_CLOSURE_N_NOTIFIERS:
 * @cl: a #GClosure
 *
 * Get the total number of notifiers connected with the closure @cl.
 * The count includes the meta marshaller, the finalize and invalidate notifiers
 * and the marshal guards. Note that each guard counts as two notifiers.
 * See g_closure_set_meta_marshal(), g_closure_add_finalize_notifier(),
 * g_closure_add_invalidate_notifier() and g_closure_add_marshal_guards().
 *
 * Returns: number of notifiers
 */


/**
 * G_CONVERT_ERROR:
 *
 * Error domain for character set conversions. Errors in this domain will
 * be from the #GConvertError enumeration. See #GError for information on
 * error domains.
 */


/**
 * G_DATALIST_FLAGS_MASK:
 *
 * A bitmask that restricts the possible flags passed to
 * g_datalist_set_flags(). Passing a flags value where
 * flags & ~G_DATALIST_FLAGS_MASK != 0 is an error.
 */


/**
 * G_DEFINE_ABSTRACT_TYPE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 *
 * A convenience macro for type implementations.
 * Similar to G_DEFINE_TYPE(), but defines an abstract type.
 * See G_DEFINE_TYPE_EXTENDED() for an example.
 *
 * Since: 2.4
 */


/**
 * G_DEFINE_ABSTRACT_TYPE_WITH_CODE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 * @_C_: Custom code that gets inserted in the @type_name_get_type() function.
 *
 * A convenience macro for type implementations.
 * Similar to G_DEFINE_TYPE_WITH_CODE(), but defines an abstract type and allows you to
 * insert custom code into the *_get_type() function, e.g. interface implementations
 * via G_IMPLEMENT_INTERFACE(). See G_DEFINE_TYPE_EXTENDED() for an example.
 *
 * Since: 2.4
 */


/**
 * G_DEFINE_BOXED_TYPE:
 * @TypeName: The name of the new type, in Camel case.
 * @type_name: The name of the new type, in lowercase, with words separated by '_'.
 * @copy_func: the #GBoxedCopyFunc for the new type
 * @free_func: the #GBoxedFreeFunc for the new type
 *
 * A convenience macro for boxed type implementations, which defines a
 * type_name_get_type() function registering the boxed type.
 *
 * Since: 2.26
 */


/**
 * G_DEFINE_BOXED_TYPE_WITH_CODE:
 * @TypeName: The name of the new type, in Camel case.
 * @type_name: The name of the new type, in lowercase, with words separated by '_'.
 * @copy_func: the #GBoxedCopyFunc for the new type
 * @free_func: the #GBoxedFreeFunc for the new type
 * @_C_: Custom code that gets inserted in the *_get_type() function.
 *
 * A convenience macro for boxed type implementations.
 * Similar to G_DEFINE_BOXED_TYPE(), but allows to insert custom code into the
 * type_name_get_type() function, e.g. to register value transformations with
 * g_value_register_transform_func().
 *
 * Since: 2.26
 */


/**
 * G_DEFINE_DYNAMIC_TYPE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 *
 * A convenience macro for dynamic type implementations, which declares a
 * class initialization function, an instance initialization function (see
 * #GTypeInfo for information about these) and a static variable named
 * @t_n<!-- -->_parent_class pointing to the parent class. Furthermore,
 * it defines a <function>*_get_type()</function> and a static
 * <function>*_register_type()</function> function for use in your
 * <function>module_init()</function>.
 * See G_DEFINE_DYNAMIC_TYPE_EXTENDED() for an example.
 *
 * Since: 2.14
 */


/**
 * G_DEFINE_DYNAMIC_TYPE_EXTENDED:
 * @TypeName: The name of the new type, in Camel case.
 * @type_name: The name of the new type, in lowercase, with words separated by '_'.
 * @TYPE_PARENT: The #GType of the parent type.
 * @flags: #GTypeFlags to pass to g_type_module_register_type()
 * @CODE: Custom code that gets inserted in the *_get_type() function.
 *
 * A more general version of G_DEFINE_DYNAMIC_TYPE() which
 * allows to specify #GTypeFlags and custom code.
 *
 * |[
 * G_DEFINE_DYNAMIC_TYPE_EXTENDED (GtkGadget,
 * gtk_gadget,
 * GTK_TYPE_THING,
 * 0,
 * G_IMPLEMENT_INTERFACE_DYNAMIC (TYPE_GIZMO,
 * gtk_gadget_gizmo_init));
 * ]|
 * expands to
 * |[
 * static void     gtk_gadget_init              (GtkGadget      *self);
 * static void     gtk_gadget_class_init        (GtkGadgetClass *klass);
 * static void     gtk_gadget_class_finalize    (GtkGadgetClass *klass);
 *
 * static gpointer gtk_gadget_parent_class = NULL;
 * static GType    gtk_gadget_type_id = 0;
 *
 * static void     gtk_gadget_class_intern_init (gpointer klass)
 * {
 * gtk_gadget_parent_class = g_type_class_peek_parent (klass);
 * gtk_gadget_class_init ((GtkGadgetClass*) klass);
 * }
 *
 * GType
 * gtk_gadget_get_type (void)
 * {
 * return gtk_gadget_type_id;
 * }
 *
 * static void
 * gtk_gadget_register_type (GTypeModule *type_module)
 * {
 * const GTypeInfo g_define_type_info = {
 * sizeof (GtkGadgetClass),
 * (GBaseInitFunc) NULL,
 * (GBaseFinalizeFunc) NULL,
 * (GClassInitFunc) gtk_gadget_class_intern_init,
 * (GClassFinalizeFunc) gtk_gadget_class_finalize,
 * NULL,   // class_data
 * sizeof (GtkGadget),
 * 0,      // n_preallocs
 * (GInstanceInitFunc) gtk_gadget_init,
 * NULL    // value_table
 * };
 * gtk_gadget_type_id = g_type_module_register_type (type_module,
 * GTK_TYPE_THING,
 * GtkGadget,
 * &g_define_type_info,
 * (GTypeFlags) flags);
 * {
 * const GInterfaceInfo g_implement_interface_info = {
 * (GInterfaceInitFunc) gtk_gadget_gizmo_init
 * };
 * g_type_module_add_interface (type_module, g_define_type_id, TYPE_GIZMO, &g_implement_interface_info);
 * }
 * }
 * ]|
 *
 * Since: 2.14
 */


/**
 * G_DEFINE_INTERFACE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the prerequisite type for the interface, or 0 (%G_TYPE_INVALID) for no prerequisite type.
 *
 * A convenience macro for #GTypeInterface definitions, which declares
 * a default vtable initialization function and defines a *_get_type()
 * function.
 *
 * The macro expects the interface initialization function to have the
 * name <literal>t_n ## _default_init</literal>, and the interface
 * structure to have the name <literal>TN ## Interface</literal>.
 *
 * Since: 2.24
 */


/**
 * G_DEFINE_INTERFACE_WITH_CODE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the prerequisite type for the interface, or 0 (%G_TYPE_INVALID) for no prerequisite type.
 * @_C_: Custom code that gets inserted in the *_get_type() function.
 *
 * A convenience macro for #GTypeInterface definitions. Similar to
 * G_DEFINE_INTERFACE(), but allows you to insert custom code into the
 * *_get_type() function, e.g. additional interface implementations
 * via G_IMPLEMENT_INTERFACE(), or additional prerequisite types. See
 * G_DEFINE_TYPE_EXTENDED() for a similar example using
 * G_DEFINE_TYPE_WITH_CODE().
 *
 * Since: 2.24
 */


/**
 * G_DEFINE_POINTER_TYPE:
 * @TypeName: The name of the new type, in Camel case.
 * @type_name: The name of the new type, in lowercase, with words separated by '_'.
 *
 * A convenience macro for pointer type implementations, which defines a
 * type_name_get_type() function registering the pointer type.
 *
 * Since: 2.26
 */


/**
 * G_DEFINE_POINTER_TYPE_WITH_CODE:
 * @TypeName: The name of the new type, in Camel case.
 * @type_name: The name of the new type, in lowercase, with words separated by '_'.
 * @_C_: Custom code that gets inserted in the *_get_type() function.
 *
 * A convenience macro for pointer type implementations.
 * Similar to G_DEFINE_POINTER_TYPE(), but allows to insert custom code into the
 * type_name_get_type() function.
 *
 * Since: 2.26
 */


/**
 * G_DEFINE_TYPE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 *
 * A convenience macro for type implementations, which declares a
 * class initialization function, an instance initialization function (see #GTypeInfo for information about
 * these) and a static variable named @t_n<!-- -->_parent_class pointing to the parent class. Furthermore, it defines
 * a *_get_type() function. See G_DEFINE_TYPE_EXTENDED() for an example.
 *
 * Since: 2.4
 */


/**
 * G_DEFINE_TYPE_EXTENDED:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type, in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 * @_f_: #GTypeFlags to pass to g_type_register_static()
 * @_C_: Custom code that gets inserted in the *_get_type() function.
 *
 * The most general convenience macro for type implementations, on which
 * G_DEFINE_TYPE(), etc are based.
 *
 * |[
 * G_DEFINE_TYPE_EXTENDED (GtkGadget,
 * gtk_gadget,
 * GTK_TYPE_WIDGET,
 * 0,
 * G_IMPLEMENT_INTERFACE (TYPE_GIZMO,
 * gtk_gadget_gizmo_init));
 * ]|
 * expands to
 * |[
 * static void     gtk_gadget_init       (GtkGadget      *self);
 * static void     gtk_gadget_class_init (GtkGadgetClass *klass);
 * static gpointer gtk_gadget_parent_class = NULL;
 * static void     gtk_gadget_class_intern_init (gpointer klass)
 * {
 * gtk_gadget_parent_class = g_type_class_peek_parent (klass);
 * gtk_gadget_class_init ((GtkGadgetClass*) klass);
 * }
 *
 * GType
 * gtk_gadget_get_type (void)
 * {
 * static volatile gsize g_define_type_id__volatile = 0;
 * if (g_once_init_enter (&g_define_type_id__volatile))
 * {
 * GType g_define_type_id =
 * g_type_register_static_simple (GTK_TYPE_WIDGET,
 * g_intern_static_string ("GtkGadget"),
 * sizeof (GtkGadgetClass),
 * (GClassInitFunc) gtk_gadget_class_intern_init,
 * sizeof (GtkGadget),
 * (GInstanceInitFunc) gtk_gadget_init,
 * (GTypeFlags) flags);
 * {
 * const GInterfaceInfo g_implement_interface_info = {
 * (GInterfaceInitFunc) gtk_gadget_gizmo_init
 * };
 * g_type_add_interface_static (g_define_type_id, TYPE_GIZMO, &g_implement_interface_info);
 * }
 * g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
 * }
 * return g_define_type_id__volatile;
 * }
 * ]|
 * The only pieces which have to be manually provided are the definitions of
 * the instance and class structure and the definitions of the instance and
 * class init functions.
 *
 * Since: 2.4
 */


/**
 * G_DEFINE_TYPE_WITH_CODE:
 * @TN: The name of the new type, in Camel case.
 * @t_n: The name of the new type in lowercase, with words separated by '_'.
 * @T_P: The #GType of the parent type.
 * @_C_: Custom code that gets inserted in the *_get_type() function.
 *
 * A convenience macro for type implementations.
 * Similar to G_DEFINE_TYPE(), but allows you to insert custom code into the
 * *_get_type() function, e.g. interface implementations via G_IMPLEMENT_INTERFACE().
 * See G_DEFINE_TYPE_EXTENDED() for an example.
 *
 * Since: 2.4
 */


/**
 * G_ENUM_CLASS:
 * @class: a valid #GEnumClass
 *
 * Casts a derived #GEnumClass structure into a #GEnumClass structure.
 */


/**
 * G_ENUM_CLASS_TYPE:
 * @class: a #GEnumClass
 *
 * Get the type identifier from a given #GEnumClass structure.
 *
 * Returns: the #GType
 */


/**
 * G_ENUM_CLASS_TYPE_NAME:
 * @class: a #GEnumClass
 *
 * Get the static type name from a given #GEnumClass structure.
 *
 * Returns: the type name.
 */


/**
 * G_FLAGS_CLASS:
 * @class: a valid #GFlagsClass
 *
 * Casts a derived #GFlagsClass structure into a #GFlagsClass structure.
 */


/**
 * G_FLAGS_CLASS_TYPE:
 * @class: a #GFlagsClass
 *
 * Get the type identifier from a given #GFlagsClass structure.
 *
 * Returns: the #GType
 */


/**
 * G_FLAGS_CLASS_TYPE_NAME:
 * @class: a #GFlagsClass
 *
 * Get the static type name from a given #GFlagsClass structure.
 *
 * Returns: the type name.
 */


/**
 * G_IMPLEMENT_INTERFACE:
 * @TYPE_IFACE: The #GType of the interface to add
 * @iface_init: The interface init function
 *
 * A convenience macro to ease interface addition in the @_C_ section
 * of G_DEFINE_TYPE_WITH_CODE() or G_DEFINE_ABSTRACT_TYPE_WITH_CODE().
 * See G_DEFINE_TYPE_EXTENDED() for an example.
 *
 * Note that this macro can only be used together with the G_DEFINE_TYPE_*
 * macros, since it depends on variable names from those macros.
 *
 * Since: 2.4
 */


/**
 * G_IMPLEMENT_INTERFACE_DYNAMIC:
 * @TYPE_IFACE: The #GType of the interface to add
 * @iface_init: The interface init function
 *
 * A convenience macro to ease interface addition in the @_C_ section
 * of G_DEFINE_DYNAMIC_TYPE_EXTENDED(). See G_DEFINE_DYNAMIC_TYPE_EXTENDED()
 * for an example.
 *
 * Note that this macro can only be used together with the
 * G_DEFINE_DYNAMIC_TYPE_EXTENDED macros, since it depends on variable
 * names from that macro.
 *
 * Since: 2.24
 */


/**
 * G_INITIALLY_UNOWNED:
 * @object: Object which is subject to casting.
 *
 * Casts a #GInitiallyUnowned or derived pointer into a (GInitiallyUnowned*)
 * pointer. Depending on the current debugging level, this function may invoke
 * certain runtime checks to identify invalid casts.
 */


/**
 * G_INITIALLY_UNOWNED_CLASS:
 * @class: a valid #GInitiallyUnownedClass
 *
 * Casts a derived #GInitiallyUnownedClass structure into a
 * #GInitiallyUnownedClass structure.
 */


/**
 * G_INITIALLY_UNOWNED_GET_CLASS:
 * @object: a #GInitiallyUnowned instance.
 *
 * Get the class structure associated to a #GInitiallyUnowned instance.
 *
 * Returns: pointer to object class structure.
 */


/**
 * G_IS_ENUM_CLASS:
 * @class: a #GEnumClass
 *
 * Checks whether @class "is a" valid #GEnumClass structure of type %G_TYPE_ENUM
 * or derived.
 */


/**
 * G_IS_FLAGS_CLASS:
 * @class: a #GFlagsClass
 *
 * Checks whether @class "is a" valid #GFlagsClass structure of type %G_TYPE_FLAGS
 * or derived.
 */


/**
 * G_IS_INITIALLY_UNOWNED:
 * @object: Instance to check for being a %G_TYPE_INITIALLY_UNOWNED.
 *
 * Checks whether a valid #GTypeInstance pointer is of type %G_TYPE_INITIALLY_UNOWNED.
 */


/**
 * G_IS_INITIALLY_UNOWNED_CLASS:
 * @class: a #GInitiallyUnownedClass
 *
 * Checks whether @class "is a" valid #GInitiallyUnownedClass structure of type
 * %G_TYPE_INITIALLY_UNOWNED or derived.
 */


/**
 * G_IS_OBJECT:
 * @object: Instance to check for being a %G_TYPE_OBJECT.
 *
 * Checks whether a valid #GTypeInstance pointer is of type %G_TYPE_OBJECT.
 */


/**
 * G_IS_OBJECT_CLASS:
 * @class: a #GObjectClass
 *
 * Checks whether @class "is a" valid #GObjectClass structure of type
 * %G_TYPE_OBJECT or derived.
 */


/**
 * G_IS_PARAM_SPEC:
 * @pspec: a #GParamSpec
 *
 * Checks whether @pspec "is a" valid #GParamSpec structure of type %G_TYPE_PARAM
 * or derived.
 */


/**
 * G_IS_PARAM_SPEC_BOOLEAN:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_BOOLEAN.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_BOXED:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_BOXED.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_CHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_CHAR.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_CLASS:
 * @pclass: a #GParamSpecClass
 *
 * Checks whether @pclass "is a" valid #GParamSpecClass structure of type
 * %G_TYPE_PARAM or derived.
 */


/**
 * G_IS_PARAM_SPEC_DOUBLE:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_DOUBLE.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_ENUM:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_ENUM.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_FLAGS:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_FLAGS.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_FLOAT:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_FLOAT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_GTYPE:
 * @pspec: a #GParamSpec
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_GTYPE.
 *
 * Since: 2.10
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_INT:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_INT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_INT64:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_INT64.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_LONG:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_LONG.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_OBJECT:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_OBJECT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_OVERRIDE:
 * @pspec: a #GParamSpec
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_OVERRIDE.
 *
 * Since: 2.4
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_PARAM:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_PARAM.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_POINTER:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_POINTER.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_STRING:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_STRING.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_UCHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_UCHAR.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_UINT:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_UINT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_UINT64:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_UINT64.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_ULONG:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_ULONG.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_UNICHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_UNICHAR.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_IS_PARAM_SPEC_VALUE_ARRAY:
 * @pspec: a valid #GParamSpec instance
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_VALUE_ARRAY.
 *
 * Returns: %TRUE on success.
 * Deprecated: 2.32: Use #GArray instead of #GValueArray
 */


/**
 * G_IS_PARAM_SPEC_VARIANT:
 * @pspec: a #GParamSpec
 *
 * Checks whether the given #GParamSpec is of type %G_TYPE_PARAM_VARIANT.
 *
 * Returns: %TRUE on success
 * Since: 2.26
 */


/**
 * G_IS_VALUE:
 * @value: A #GValue structure.
 *
 * Checks if @value is a valid and initialized #GValue structure.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_MARKUP_ERROR:
 *
 * Error domain for markup parsing.
 * Errors in this domain will be from the #GMarkupError enumeration.
 * See #GError for information on error domains.
 */


/**
 * G_NODE_IS_LEAF:
 * @node: a #GNode
 *
 * Returns %TRUE if a #GNode is a leaf node.
 *
 * (i.e. it has no children)
 *
 * Returns: %TRUE if the #GNode is a leaf node
 */


/**
 * G_NODE_IS_ROOT:
 * @node: a #GNode
 *
 * Returns %TRUE if a #GNode is the root of a tree.
 *
 * (i.e. it has no parent or siblings)
 *
 * Returns: %TRUE if the #GNode is the root of a tree
 */


/**
 * G_OBJECT:
 * @object: Object which is subject to casting.
 *
 * Casts a #GObject or derived pointer into a (GObject*) pointer.
 * Depending on the current debugging level, this function may invoke
 * certain runtime checks to identify invalid casts.
 */


/**
 * G_OBJECT_CLASS:
 * @class: a valid #GObjectClass
 *
 * Casts a derived #GObjectClass structure into a #GObjectClass structure.
 */


/**
 * G_OBJECT_CLASS_NAME:
 * @class: a valid #GObjectClass
 *
 * Return the name of a class structure's type.
 *
 * should not be freed.
 *
 * Returns: Type name of @class. The string is owned by the type system and
 */


/**
 * G_OBJECT_CLASS_TYPE:
 * @class: a valid #GObjectClass
 *
 * Get the type id of a class structure.
 *
 * Returns: Type id of @class.
 */


/**
 * G_OBJECT_GET_CLASS:
 * @object: a #GObject instance.
 *
 * Get the class structure associated to a #GObject instance.
 *
 * Returns: pointer to object class structure.
 */


/**
 * G_OBJECT_TYPE:
 * @object: Object to return the type id for.
 *
 * Get the type id of an object.
 *
 * Returns: Type id of @object.
 */


/**
 * G_OBJECT_TYPE_NAME:
 * @object: Object to return the type name for.
 *
 * Get the name of an object's type.
 *
 * should not be freed.
 *
 * Returns: Type name of @object. The string is owned by the type system and
 */


/**
 * G_OBJECT_WARN_INVALID_PROPERTY_ID:
 * @object: the #GObject on which set_property() or get_property() was called
 * @property_id: the numeric id of the property
 * @pspec: the #GParamSpec of the property
 *
 * This macro should be used to emit a standard warning about unexpected
 * properties in set_property() and get_property() implementations.
 */


/**
 * G_OPTION_ERROR:
 *
 * Error domain for option parsing. Errors in this domain will
 * be from the #GOptionError enumeration. See #GError for information on
 * error domains.
 */


/**
 * G_OPTION_REMAINING:
 *
 * If a long option in the main group has this name, it is not treated as a
 * regular option. Instead it collects all non-option arguments which would
 * otherwise be left in <literal>argv</literal>. The option must be of type
 * %G_OPTION_ARG_CALLBACK, %G_OPTION_ARG_STRING_ARRAY
 * or %G_OPTION_ARG_FILENAME_ARRAY.
 *
 *
 * Using #G_OPTION_REMAINING instead of simply scanning <literal>argv</literal>
 * for leftover arguments has the advantage that GOption takes care of
 * necessary encoding conversions for strings or filenames.
 *
 * Since: 2.6
 */


/**
 * G_PARAM_MASK:
 *
 * Mask containing the bits of #GParamSpec.flags which are reserved for GLib.
 */


/**
 * G_PARAM_READWRITE:
 *
 * #GParamFlags value alias for %G_PARAM_READABLE | %G_PARAM_WRITABLE.
 */


/**
 * G_PARAM_SPEC:
 * @pspec: a valid #GParamSpec
 *
 * Casts a derived #GParamSpec object (e.g. of type #GParamSpecInt) into
 * a #GParamSpec object.
 */


/**
 * G_PARAM_SPEC_BOOLEAN:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecBoolean.
 */


/**
 * G_PARAM_SPEC_BOXED:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecBoxed.
 */


/**
 * G_PARAM_SPEC_CHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecChar.
 */


/**
 * G_PARAM_SPEC_CLASS:
 * @pclass: a valid #GParamSpecClass
 *
 * Casts a derived #GParamSpecClass structure into a #GParamSpecClass structure.
 */


/**
 * G_PARAM_SPEC_DOUBLE:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecDouble.
 */


/**
 * G_PARAM_SPEC_ENUM:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecEnum.
 */


/**
 * G_PARAM_SPEC_FLAGS:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecFlags.
 */


/**
 * G_PARAM_SPEC_FLOAT:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecFloat.
 */


/**
 * G_PARAM_SPEC_GET_CLASS:
 * @pspec: a valid #GParamSpec
 *
 * Retrieves the #GParamSpecClass of a #GParamSpec.
 */


/**
 * G_PARAM_SPEC_GTYPE:
 * @pspec: a #GParamSpec
 *
 * Casts a #GParamSpec into a #GParamSpecGType.
 *
 * Since: 2.10
 */


/**
 * G_PARAM_SPEC_INT:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecInt.
 */


/**
 * G_PARAM_SPEC_INT64:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecInt64.
 */


/**
 * G_PARAM_SPEC_LONG:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecLong.
 */


/**
 * G_PARAM_SPEC_OBJECT:
 * @pspec: a valid #GParamSpec instance
 *
 * Casts a #GParamSpec instance into a #GParamSpecObject.
 */


/**
 * G_PARAM_SPEC_OVERRIDE:
 * @pspec: a #GParamSpec
 *
 * Casts a #GParamSpec into a #GParamSpecOverride.
 *
 * Since: 2.4
 */


/**
 * G_PARAM_SPEC_PARAM:
 * @pspec: a valid #GParamSpec instance
 *
 * Casts a #GParamSpec instance into a #GParamSpecParam.
 */


/**
 * G_PARAM_SPEC_POINTER:
 * @pspec: a valid #GParamSpec instance
 *
 * Casts a #GParamSpec instance into a #GParamSpecPointer.
 */


/**
 * G_PARAM_SPEC_STRING:
 * @pspec: a valid #GParamSpec instance
 *
 * Casts a #GParamSpec instance into a #GParamSpecString.
 */


/**
 * G_PARAM_SPEC_TYPE:
 * @pspec: a valid #GParamSpec
 *
 * Retrieves the #GType of this @pspec.
 */


/**
 * G_PARAM_SPEC_TYPE_NAME:
 * @pspec: a valid #GParamSpec
 *
 * Retrieves the #GType name of this @pspec.
 */


/**
 * G_PARAM_SPEC_UCHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecUChar.
 */


/**
 * G_PARAM_SPEC_UINT:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecUInt.
 */


/**
 * G_PARAM_SPEC_UINT64:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecUInt64.
 */


/**
 * G_PARAM_SPEC_ULONG:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecULong.
 */


/**
 * G_PARAM_SPEC_UNICHAR:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecUnichar.
 */


/**
 * G_PARAM_SPEC_VALUE_ARRAY:
 * @pspec: a valid #GParamSpec instance
 *
 * Cast a #GParamSpec instance into a #GParamSpecValueArray.
 *
 * Deprecated: 2.32: Use #GArray instead of #GValueArray
 */


/**
 * G_PARAM_SPEC_VALUE_TYPE:
 * @pspec: a valid #GParamSpec
 *
 * Retrieves the #GType to initialize a #GValue for this parameter.
 */


/**
 * G_PARAM_SPEC_VARIANT:
 * @pspec: a #GParamSpec
 *
 * Casts a #GParamSpec into a #GParamSpecVariant.
 *
 * Since: 2.26
 */


/**
 * G_PARAM_STATIC_STRINGS:
 *
 * #GParamFlags value alias for %G_PARAM_STATIC_NAME | %G_PARAM_STATIC_NICK | %G_PARAM_STATIC_BLURB.
 *
 * Since 2.13.0
 */


/**
 * G_PARAM_USER_SHIFT:
 *
 * Minimum shift count to be used for user defined flags, to be stored in
 * #GParamSpec.flags. The maximum allowed is 30 + G_PARAM_USER_SHIFT.
 */


/**
 * G_PRIORITY_DEFAULT:
 *
 * Use this for default priority event sources.
 *
 * In GLib this priority is used when adding timeout functions
 * with g_timeout_add(). In GDK this priority is used for events
 * from the X server.
 */


/**
 * G_PRIORITY_DEFAULT_IDLE:
 *
 * Use this for default priority idle functions.
 *
 * In GLib this priority is used when adding idle functions with
 * g_idle_add().
 */


/**
 * G_PRIORITY_HIGH:
 *
 * Use this for high priority event sources.
 *
 * It is not used within GLib or GTK+.
 */


/**
 * G_PRIORITY_HIGH_IDLE:
 *
 * Use this for high priority idle functions.
 *
 * GTK+ uses #G_PRIORITY_HIGH_IDLE + 10 for resizing operations,
 * and #G_PRIORITY_HIGH_IDLE + 20 for redrawing operations. (This is
 * done to ensure that any pending resizes are processed before any
 * pending redraws, so that widgets are not redrawn twice unnecessarily.)
 */


/**
 * G_PRIORITY_LOW:
 *
 * Use this for very low priority background tasks.
 *
 * It is not used within GLib or GTK+.
 */


/**
 * G_QUEUE_INIT:
 *
 * A statically-allocated #GQueue must be initialized with this
 * macro before it can be used. This macro can be used to initialize
 * a variable, but it cannot be assigned to a variable. In that case
 * you have to use g_queue_init().
 *
 * |[
 * GQueue my_queue = G_QUEUE_INIT;
 * ]|
 *
 * Since: 2.14
 */


/**
 * G_REGEX_ERROR:
 *
 * Error domain for regular expressions. Errors in this domain will be
 * from the #GRegexError enumeration. See #GError for information on
 * error domains.
 *
 * Since: 2.14
 */


/**
 * G_SIGNAL_FLAGS_MASK:
 *
 * A mask for all #GSignalFlags bits.
 */


/**
 * G_SIGNAL_MATCH_MASK:
 *
 * A mask for all #GSignalMatchType bits.
 */


/**
 * G_SIGNAL_TYPE_STATIC_SCOPE:
 *
 * This macro flags signal argument types for which the signal system may
 * assume that instances thereof remain persistent across all signal emissions
 * they are used in. This is only useful for non ref-counted, value-copy types.
 *
 * To flag a signal argument in this way, add
 * <literal>| G_SIGNAL_TYPE_STATIC_SCOPE</literal> to the corresponding argument
 * of g_signal_new().
 * |[
 * g_signal_new ("size_request",
 * G_TYPE_FROM_CLASS (gobject_class),
 * G_SIGNAL_RUN_FIRST,
 * G_STRUCT_OFFSET (GtkWidgetClass, size_request),
 * NULL, NULL,
 * _gtk_marshal_VOID__BOXED,
 * G_TYPE_NONE, 1,
 * GTK_TYPE_REQUISITION | G_SIGNAL_TYPE_STATIC_SCOPE);
 * ]|
 */


/**
 * G_SOURCE_CONTINUE:
 *
 * Use this macro as the return value of a #GSourceFunc to leave
 * the #GSource in the main loop.
 *
 * Since: 2.28
 */


/**
 * G_SOURCE_REMOVE:
 *
 * Use this macro as the return value of a #GSourceFunc to remove
 * the #GSource from the main loop.
 *
 * Since: 2.28
 */


/**
 * G_SPAWN_ERROR:
 *
 * Error domain for spawning processes. Errors in this domain will
 * be from the #GSpawnError enumeration. See #GError for information on
 * error domains.
 */


/**
 * G_TIME_SPAN_DAY:
 *
 * Evaluates to a time span of one day.
 *
 * Since: 2.26
 */


/**
 * G_TIME_SPAN_HOUR:
 *
 * Evaluates to a time span of one hour.
 *
 * Since: 2.26
 */


/**
 * G_TIME_SPAN_MILLISECOND:
 *
 * Evaluates to a time span of one millisecond.
 *
 * Since: 2.26
 */


/**
 * G_TIME_SPAN_MINUTE:
 *
 * Evaluates to a time span of one minute.
 *
 * Since: 2.26
 */


/**
 * G_TIME_SPAN_SECOND:
 *
 * Evaluates to a time span of one second.
 *
 * Since: 2.26
 */


/**
 * G_TYPE_ARRAY:
 *
 * The #GType for a boxed type holding a #GArray reference.
 *
 * Since: 2.22
 */


/**
 * G_TYPE_BOOLEAN:
 *
 * The fundamental type corresponding to #gboolean.
 */


/**
 * G_TYPE_BOXED:
 *
 * The fundamental type from which all boxed types are derived.
 */


/**
 * G_TYPE_BYTES:
 *
 * The #GType for #GBytes.
 *
 * Since: 2.32
 */


/**
 * G_TYPE_BYTE_ARRAY:
 *
 * The #GType for a boxed type holding a #GByteArray reference.
 *
 * Since: 2.22
 */


/**
 * G_TYPE_CHAR:
 *
 * The fundamental type corresponding to #gchar.
 * The type designated by G_TYPE_CHAR is unconditionally an 8-bit signed integer.
 * This may or may not be the same type a the C type "gchar".
 */


/**
 * G_TYPE_CHECK_CLASS_CAST:
 * @g_class: Location of a #GTypeClass structure.
 * @g_type: The type to be returned.
 * @c_type: The corresponding C type of class structure of @g_type.
 *
 * Checks that @g_class is a class structure of the type identified by @g_type
 * and issues a warning if this is not the case. Returns @g_class casted
 * to a pointer to @c_type.
 *
 * This macro should only be used in type implementations.
 */


/**
 * G_TYPE_CHECK_CLASS_TYPE:
 * @g_class: Location of a #GTypeClass structure.
 * @g_type: The type to be checked.
 *
 * Checks if @g_class is a class structure of the type identified by
 * @g_type.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_CHECK_INSTANCE:
 * @instance: Location of a #GTypeInstance structure.
 *
 * Checks if @instance is a valid #GTypeInstance structure,
 * otherwise issues a warning and returns %FALSE.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_CHECK_INSTANCE_CAST:
 * @instance: Location of a #GTypeInstance structure.
 * @g_type: The type to be returned.
 * @c_type: The corresponding C type of @g_type.
 *
 * Checks that @instance is an instance of the type identified by @g_type
 * and issues a warning if this is not the case. Returns @instance casted
 * to a pointer to @c_type.
 *
 * This macro should only be used in type implementations.
 */


/**
 * G_TYPE_CHECK_INSTANCE_TYPE:
 * @instance: Location of a #GTypeInstance structure.
 * @g_type: The type to be checked
 *
 * Checks if @instance is an instance of the type identified by @g_type.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_CHECK_VALUE:
 * @value: a #GValue
 *
 * Checks if @value has been initialized to hold values
 * of a value type.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_CHECK_VALUE_TYPE:
 * @value: a #GValue
 * @g_type: The type to be checked.
 *
 * Checks if @value has been initialized to hold values
 * of type @g_type.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_CLASS_GET_PRIVATE:
 * @klass: the class of a type deriving from @private_type.
 * @g_type: the type identifying which private data to retrieve.
 * @c_type: The C type for the private structure.
 *
 * Gets the private class structure for a particular type.
 * The private structure must have been registered in the
 * get_type() function with g_type_add_class_private().
 *
 * This macro should only be used in type implementations.
 *
 * Since: 2.24
 * Returns: a pointer to the private data structure.
 */


/**
 * G_TYPE_CLOSURE:
 *
 * The #GType for #GClosure.
 */


/**
 * G_TYPE_DATE:
 *
 * The #GType for #GDate.
 */


/**
 * G_TYPE_DATE_TIME:
 *
 * The #GType for a boxed type holding a #GDateTime.
 *
 * Since: 2.26
 */


/**
 * G_TYPE_DOUBLE:
 *
 * The fundamental type corresponding to #gdouble.
 */


/**
 * G_TYPE_ENUM:
 *
 * The fundamental type from which all enumeration types are derived.
 */


/**
 * G_TYPE_ERROR:
 *
 * The #GType for a boxed type holding a #GError.
 *
 * Since: 2.26
 */


/**
 * G_TYPE_FLAGS:
 *
 * The fundamental type from which all flags types are derived.
 */


/**
 * G_TYPE_FLAG_RESERVED_ID_BIT:
 *
 * A bit in the type number that's supposed to be left untouched.
 */


/**
 * G_TYPE_FLOAT:
 *
 * The fundamental type corresponding to #gfloat.
 */


/**
 * G_TYPE_FROM_CLASS:
 * @g_class: Location of a valid #GTypeClass structure.
 *
 * Get the type identifier from a given @class structure.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: the #GType
 */


/**
 * G_TYPE_FROM_INSTANCE:
 * @instance: Location of a valid #GTypeInstance structure.
 *
 * Get the type identifier from a given @instance structure.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: the #GType
 */


/**
 * G_TYPE_FROM_INTERFACE:
 * @g_iface: Location of a valid #GTypeInterface structure.
 *
 * Get the type identifier from a given @interface structure.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: the #GType
 */


/**
 * G_TYPE_FUNDAMENTAL:
 * @type: A #GType value.
 *
 * The fundamental type which is the ancestor of @type.
 * Fundamental types are types that serve as ultimate bases for the derived types,
 * thus they are the roots of distinct inheritance hierarchies.
 */


/**
 * G_TYPE_FUNDAMENTAL_MAX:
 *
 * An integer constant that represents the number of identifiers reserved
 * for types that are assigned at compile-time.
 */


/**
 * G_TYPE_FUNDAMENTAL_SHIFT:
 *
 * Shift value used in converting numbers to type IDs.
 */


/**
 * G_TYPE_GSTRING:
 *
 * The #GType for #GString.
 */


/**
 * G_TYPE_GTYPE:
 *
 * The type for #GType.
 */


/**
 * G_TYPE_HASH_TABLE:
 *
 * The #GType for a boxed type holding a #GHashTable reference.
 *
 * Since: 2.10
 */


/**
 * G_TYPE_HAS_VALUE_TABLE:
 * @type: A #GType value.
 *
 * Checks if @type has a #GTypeValueTable.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_INITIALLY_UNOWNED:
 *
 * The type for #GInitiallyUnowned.
 */


/**
 * G_TYPE_INSTANCE_GET_CLASS:
 * @instance: Location of the #GTypeInstance structure.
 * @g_type: The #GType of the class to be returned.
 * @c_type: The C type of the class structure.
 *
 * Get the class structure of a given @instance, casted
 * to a specified ancestor type @g_type of the instance.
 *
 * Note that while calling a GInstanceInitFunc(), the class pointer gets
 * modified, so it might not always return the expected pointer.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: a pointer to the class structure
 */


/**
 * G_TYPE_INSTANCE_GET_INTERFACE:
 * @instance: Location of the #GTypeInstance structure.
 * @g_type: The #GType of the interface to be returned.
 * @c_type: The C type of the interface structure.
 *
 * Get the interface structure for interface @g_type of a given @instance.
 *
 * This macro should only be used in type implementations.
 *
 * Returns: a pointer to the interface structure
 */


/**
 * G_TYPE_INSTANCE_GET_PRIVATE:
 * @instance: the instance of a type deriving from @private_type.
 * @g_type: the type identifying which private data to retrieve.
 * @c_type: The C type for the private structure.
 *
 * Gets the private structure for a particular type.
 * The private structure must have been registered in the
 * class_init function with g_type_class_add_private().
 *
 * This macro should only be used in type implementations.
 *
 * Since: 2.4
 * Returns: a pointer to the private data structure.
 */


/**
 * G_TYPE_INT:
 *
 * The fundamental type corresponding to #gint.
 */


/**
 * G_TYPE_INT64:
 *
 * The fundamental type corresponding to #gint64.
 */


/**
 * G_TYPE_INTERFACE:
 *
 * The fundamental type from which all interfaces are derived.
 */


/**
 * G_TYPE_INVALID:
 *
 * An invalid #GType used as error return value in some functions which return
 * a #GType.
 */


/**
 * G_TYPE_IO_CHANNEL:
 *
 * The #GType for #GIOChannel.
 */


/**
 * G_TYPE_IO_CONDITION:
 *
 * The #GType for #GIOCondition.
 */


/**
 * G_TYPE_IS_ABSTRACT:
 * @type: A #GType value.
 *
 * Checks if @type is an abstract type.  An abstract type cannot be
 * instantiated and is normally used as an abstract base class for
 * derived classes.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_CLASSED:
 * @type: A #GType value.
 *
 * Checks if @type is a classed type.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_DEEP_DERIVABLE:
 * @type: A #GType value.
 *
 * Checks if @type is a deep derivable type.  A deep derivable type
 * can be used as the base class of a deep (multi-level) class hierarchy.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_DERIVABLE:
 * @type: A #GType value.
 *
 * Checks if @type is a derivable type.  A derivable type can
 * be used as the base class of a flat (single-level) class hierarchy.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_DERIVED:
 * @type: A #GType value.
 *
 * Checks if @type is derived (or in object-oriented terminology:
 * inherited) from another type (this holds true for all non-fundamental
 * types).
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_ENUM:
 * @type: a #GType ID.
 *
 * Checks whether @type "is a" %G_TYPE_ENUM.
 *
 * Returns: %TRUE if @type "is a" %G_TYPE_ENUM.
 */


/**
 * G_TYPE_IS_FLAGS:
 * @type: a #GType ID.
 *
 * Checks whether @type "is a" %G_TYPE_FLAGS.
 *
 * Returns: %TRUE if @type "is a" %G_TYPE_FLAGS.
 */


/**
 * G_TYPE_IS_FUNDAMENTAL:
 * @type: A #GType value.
 *
 * Checks if @type is a fundamental type.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_INSTANTIATABLE:
 * @type: A #GType value.
 *
 * Checks if @type can be instantiated.  Instantiation is the
 * process of creating an instance (object) of this type.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_INTERFACE:
 * @type: A #GType value.
 *
 * Checks if @type is an interface type.
 * An interface type provides a pure API, the implementation
 * of which is provided by another type (which is then said to conform
 * to the interface).  GLib interfaces are somewhat analogous to Java
 * interfaces and C++ classes containing only pure virtual functions,
 * with the difference that GType interfaces are not derivable (but see
 * g_type_interface_add_prerequisite() for an alternative).
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_OBJECT:
 * @type: Type id to check
 *
 * Check if the passed in type id is a %G_TYPE_OBJECT or derived from it.
 *
 * Returns: %FALSE or %TRUE, indicating whether @type is a %G_TYPE_OBJECT.
 */


/**
 * G_TYPE_IS_PARAM:
 * @type: a #GType ID
 *
 * Checks whether @type "is a" %G_TYPE_PARAM.
 */


/**
 * G_TYPE_IS_VALUE:
 * @type: A #GType value.
 *
 * Checks whether the passed in type ID can be used for g_value_init().
 * That is, this macro checks whether this type provides an implementation
 * of the #GTypeValueTable functions required for a type to create a #GValue of.
 *
 * Returns: Whether @type is suitable as a #GValue type.
 */


/**
 * G_TYPE_IS_VALUE_ABSTRACT:
 * @type: A #GType value.
 *
 * Checks if @type is an abstract value type.  An abstract value type introduces
 * a value table, but can't be used for g_value_init() and is normally used as
 * an abstract base type for derived value types.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_IS_VALUE_TYPE:
 * @type: A #GType value.
 *
 * Checks if @type is a value type and can be used with g_value_init().
 *
 * Returns: %TRUE on success.
 */


/**
 * G_TYPE_KEY_FILE:
 *
 * The #GType for a boxed type holding a #GKeyFile.
 *
 * Since: 2.32
 */


/**
 * G_TYPE_LONG:
 *
 * The fundamental type corresponding to #glong.
 */


/**
 * G_TYPE_MAIN_CONTEXT:
 *
 * The #GType for a boxed type holding a #GMainContext.
 *
 * Since: 2.30
 */


/**
 * G_TYPE_MAIN_LOOP:
 *
 * The #GType for a boxed type holding a #GMainLoop.
 *
 * Since: 2.30
 */


/**
 * G_TYPE_MAKE_FUNDAMENTAL:
 * @x: the fundamental type number.
 *
 * Get the type ID for the fundamental type number @x.
 * Use g_type_fundamental_next() instead of this macro to create new fundamental
 * types.
 *
 * Returns: the GType
 */


/**
 * G_TYPE_MATCH_INFO:
 *
 * The #GType for a boxed type holding a #GMatchInfo reference.
 *
 * Since: 2.30
 */


/**
 * G_TYPE_NONE:
 *
 * A fundamental type which is used as a replacement for the C
 * <literal>void</literal> return type.
 */


/**
 * G_TYPE_OBJECT:
 *
 * The fundamental type for #GObject.
 */


/**
 * G_TYPE_PARAM:
 *
 * The fundamental type from which all #GParamSpec types are derived.
 */


/**
 * G_TYPE_PARAM_BOOLEAN:
 *
 * The #GType of #GParamSpecBoolean.
 */


/**
 * G_TYPE_PARAM_BOXED:
 *
 * The #GType of #GParamSpecBoxed.
 */


/**
 * G_TYPE_PARAM_CHAR:
 *
 * The #GType of #GParamSpecChar.
 */


/**
 * G_TYPE_PARAM_DOUBLE:
 *
 * The #GType of #GParamSpecDouble.
 */


/**
 * G_TYPE_PARAM_ENUM:
 *
 * The #GType of #GParamSpecEnum.
 */


/**
 * G_TYPE_PARAM_FLAGS:
 *
 * The #GType of #GParamSpecFlags.
 */


/**
 * G_TYPE_PARAM_FLOAT:
 *
 * The #GType of #GParamSpecFloat.
 */


/**
 * G_TYPE_PARAM_GTYPE:
 *
 * The #GType of #GParamSpecGType.
 *
 * Since: 2.10
 */


/**
 * G_TYPE_PARAM_INT:
 *
 * The #GType of #GParamSpecInt.
 */


/**
 * G_TYPE_PARAM_INT64:
 *
 * The #GType of #GParamSpecInt64.
 */


/**
 * G_TYPE_PARAM_LONG:
 *
 * The #GType of #GParamSpecLong.
 */


/**
 * G_TYPE_PARAM_OBJECT:
 *
 * The #GType of #GParamSpecObject.
 */


/**
 * G_TYPE_PARAM_OVERRIDE:
 *
 * The #GType of #GParamSpecOverride.
 *
 * Since: 2.4
 */


/**
 * G_TYPE_PARAM_PARAM:
 *
 * The #GType of #GParamSpecParam.
 */


/**
 * G_TYPE_PARAM_POINTER:
 *
 * The #GType of #GParamSpecPointer.
 */


/**
 * G_TYPE_PARAM_STRING:
 *
 * The #GType of #GParamSpecString.
 */


/**
 * G_TYPE_PARAM_UCHAR:
 *
 * The #GType of #GParamSpecUChar.
 */


/**
 * G_TYPE_PARAM_UINT:
 *
 * The #GType of #GParamSpecUInt.
 */


/**
 * G_TYPE_PARAM_UINT64:
 *
 * The #GType of #GParamSpecUInt64.
 */


/**
 * G_TYPE_PARAM_ULONG:
 *
 * The #GType of #GParamSpecULong.
 */


/**
 * G_TYPE_PARAM_UNICHAR:
 *
 * The #GType of #GParamSpecUnichar.
 */


/**
 * G_TYPE_PARAM_VALUE_ARRAY:
 *
 * The #GType of #GParamSpecValueArray.
 *
 * Deprecated: 2.32: Use #GArray instead of #GValueArray
 */


/**
 * G_TYPE_PARAM_VARIANT:
 *
 * The #GType of #GParamSpecVariant.
 *
 * Since: 2.26
 */


/**
 * G_TYPE_POINTER:
 *
 * The fundamental type corresponding to #gpointer.
 */


/**
 * G_TYPE_PTR_ARRAY:
 *
 * The #GType for a boxed type holding a #GPtrArray reference.
 *
 * Since: 2.22
 */


/**
 * G_TYPE_REGEX:
 *
 * The #GType for a boxed type holding a #GRegex reference.
 *
 * Since: 2.14
 */


/**
 * G_TYPE_RESERVED_BSE_FIRST:
 *
 * First fundamental type number to create a new fundamental type id with
 * G_TYPE_MAKE_FUNDAMENTAL() reserved for BSE.
 */


/**
 * G_TYPE_RESERVED_BSE_LAST:
 *
 * Last fundamental type number reserved for BSE.
 */


/**
 * G_TYPE_RESERVED_GLIB_FIRST:
 *
 * First fundamental type number to create a new fundamental type id with
 * G_TYPE_MAKE_FUNDAMENTAL() reserved for GLib.
 */


/**
 * G_TYPE_RESERVED_GLIB_LAST:
 *
 * Last fundamental type number reserved for GLib.
 */


/**
 * G_TYPE_RESERVED_USER_FIRST:
 *
 * First available fundamental type number to create new fundamental
 * type id with G_TYPE_MAKE_FUNDAMENTAL().
 */


/**
 * G_TYPE_SOURCE:
 *
 * The #GType for a boxed type holding a #GSource.
 *
 * Since: 2.30
 */


/**
 * G_TYPE_STRING:
 *
 * The fundamental type corresponding to nul-terminated C strings.
 */


/**
 * G_TYPE_STRV:
 *
 * The #GType for a boxed type holding a %NULL-terminated array of strings.
 *
 * The code fragments in the following example show the use of a property of
 * type #G_TYPE_STRV with g_object_class_install_property(), g_object_set()
 * and g_object_get().
 *
 * |[
 * g_object_class_install_property (object_class,
 * PROP_AUTHORS,
 * g_param_spec_boxed ("authors",
 * _("Authors"),
 * _("List of authors"),
 * G_TYPE_STRV,
 * G_PARAM_READWRITE));
 *
 * gchar *authors[] = { "Owen", "Tim", NULL };
 * g_object_set (obj, "authors", authors, NULL);
 *
 * gchar *writers[];
 * g_object_get (obj, "authors", &writers, NULL);
 * /&ast; do something with writers &ast;/
 * g_strfreev (writers);
 * ]|
 *
 * Since: 2.4
 */


/**
 * G_TYPE_UCHAR:
 *
 * The fundamental type corresponding to #guchar.
 */


/**
 * G_TYPE_UINT:
 *
 * The fundamental type corresponding to #guint.
 */


/**
 * G_TYPE_UINT64:
 *
 * The fundamental type corresponding to #guint64.
 */


/**
 * G_TYPE_ULONG:
 *
 * The fundamental type corresponding to #gulong.
 */


/**
 * G_TYPE_VALUE:
 *
 * The type ID of the "GValue" type which is a boxed type,
 * used to pass around pointers to GValues.
 */


/**
 * G_TYPE_VALUE_ARRAY:
 *
 * The type ID of the "GValueArray" type which is a boxed type,
 * used to pass around pointers to GValueArrays.
 *
 * Deprecated: 2.32: Use #GArray instead of #GValueArray
 */


/**
 * G_TYPE_VARIANT:
 *
 * The fundamental type corresponding to #GVariant.
 *
 * All floating #GVariant instances passed through the #GType system are
 * consumed.
 *
 * Note that callbacks in closures, and signal handlers
 * for signals of return type %G_TYPE_VARIANT, must never return floating
 * variants.
 *
 * Note: GLib 2.24 did include a boxed type with this name. It was replaced
 * with this fundamental type in 2.26.
 *
 * Since: 2.26
 */


/**
 * G_TYPE_VARIANT_BUILDER:
 *
 * The #GType for a boxed type holding a #GVariantBuilder.
 *
 * Since: 2.30
 */


/**
 * G_TYPE_VARIANT_TYPE:
 *
 * The #GType for a boxed type holding a #GVariantType.
 *
 * Since: 2.24
 */


/**
 * G_UNICHAR_MAX_DECOMPOSITION_LENGTH:
 *
 * The maximum length (in codepoints) of a compatibility or canonical
 * decomposition of a single Unicode character.
 *
 * This is as defined by Unicode 6.1.
 *
 * Since: 2.32
 */


/**
 * G_UNICODE_COMBINING_MARK:
 *
 * Older name for %G_UNICODE_SPACING_MARK.
 *
 * Deprecated: 2.30: Use %G_UNICODE_SPACING_MARK.
 */


/**
 * G_URI_RESERVED_CHARS_ALLOWED_IN_PATH:
 *
 * Allowed characters in a path. Includes "!$&'()*+,;=:@/".
 */


/**
 * G_URI_RESERVED_CHARS_ALLOWED_IN_PATH_ELEMENT:
 *
 * Allowed characters in path elements. Includes "!$&'()*+,;=:@".
 */


/**
 * G_URI_RESERVED_CHARS_ALLOWED_IN_USERINFO:
 *
 * Allowed characters in userinfo as defined in RFC 3986. Includes "!$&'()*+,;=:".
 */


/**
 * G_URI_RESERVED_CHARS_GENERIC_DELIMITERS:
 *
 * Generic delimiters characters as defined in RFC 3986. Includes ":/?#[]@".
 */


/**
 * G_URI_RESERVED_CHARS_SUBCOMPONENT_DELIMITERS:
 *
 * Subcomponent delimiter characters as defined in RFC 3986. Includes "!$&'()*+,;=".
 */


/**
 * G_VALUE_COLLECT:
 * @value: a #GValue return location. @value is supposed to be initialized according to the value type to be collected
 * @var_args: the va_list variable; it may be evaluated multiple times
 * @flags: flags which are passed on to the collect_value() function of the #GTypeValueTable of @value.
 * @__error: a #gchar** variable that will be modified to hold a g_new() allocated error messages if something fails
 *
 * Collects a variable argument value from a va_list. We have to
 * implement the varargs collection as a macro, because on some systems
 * va_list variables cannot be passed by reference.
 *
 * Note: If you are creating the @value argument just before calling this macro,
 * you should use the #G_VALUE_COLLECT_INIT variant and pass the unitialized
 * #GValue. That variant is faster than #G_VALUE_COLLECT.
 */


/**
 * G_VALUE_COLLECT_FORMAT_MAX_LENGTH:
 *
 * The maximal number of #GTypeCValue<!-- -->s which can be collected for a
 * single #GValue.
 */


/**
 * G_VALUE_COLLECT_INIT:
 * @value: a #GValue return location. @value must contain only 0 bytes.
 * @_value_type: the #GType to use for @value.
 * @var_args: the va_list variable; it may be evaluated multiple times
 * @flags: flags which are passed on to the collect_value() function of the #GTypeValueTable of @value.
 * @__error: a #gchar** variable that will be modified to hold a g_new() allocated error messages if something fails
 *
 * Collects a variable argument value from a va_list. We have to
 * implement the varargs collection as a macro, because on some systems
 * va_list variables cannot be passed by reference.
 *
 * Since: 2.24
 */


/**
 * G_VALUE_HOLDS:
 * @value: A #GValue structure.
 * @type: A #GType value.
 *
 * Checks if @value holds (or contains) a value of @type.
 * This macro will also check for @value != %NULL and issue a
 * warning if the check fails.
 *
 * Returns: %TRUE if @value holds the @type.
 */


/**
 * G_VALUE_HOLDS_BOOLEAN:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_BOOLEAN.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_BOXED:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values derived
 * from type %G_TYPE_BOXED.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_CHAR:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_CHAR.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_DOUBLE:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_DOUBLE.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_ENUM:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values derived from type %G_TYPE_ENUM.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_FLAGS:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values derived from type %G_TYPE_FLAGS.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_FLOAT:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_FLOAT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_GTYPE:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_GTYPE.
 *
 * Since: 2.12
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_INT:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_INT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_INT64:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_INT64.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_LONG:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_LONG.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_OBJECT:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values derived from type %G_TYPE_OBJECT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_PARAM:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values derived from type %G_TYPE_PARAM.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_POINTER:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_POINTER.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_STRING:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_STRING.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_UCHAR:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_UCHAR.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_UINT:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_UINT.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_UINT64:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_UINT64.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_ULONG:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_ULONG.
 *
 * Returns: %TRUE on success.
 */


/**
 * G_VALUE_HOLDS_VARIANT:
 * @value: a valid #GValue structure
 *
 * Checks whether the given #GValue can hold values of type %G_TYPE_VARIANT.
 *
 * Returns: %TRUE on success.
 * Since: 2.26
 */


/**
 * G_VALUE_INIT:
 *
 * A #GValue must be initialized before it can be used.
 * This macro can be used as initializer instead of an explicit
 * <literal>{ 0 }</literal> when declaring a variable,
 * but it cannot be assigned to a variable.
 *
 * |[
 * GValue value = G_VALUE_INIT;
 * ]|
 *
 * Since: 2.30
 */


/**
 * G_VALUE_LCOPY:
 * @value: a #GValue return location. @value is supposed to be initialized according to the value type to be collected
 * @var_args: the va_list variable; it may be evaluated multiple times
 * @flags: flags which are passed on to the lcopy_value() function of the #GTypeValueTable of @value.
 * @__error: a #gchar** variable that will be modified to hold a g_new() allocated error messages if something fails
 *
 * Collects a value's variable argument locations from a va_list. Usage is
 * analogous to G_VALUE_COLLECT().
 */


/**
 * G_VALUE_NOCOPY_CONTENTS:
 *
 * If passed to G_VALUE_COLLECT(), allocated data won't be copied
 * but used verbatim. This does not affect ref-counted types like
 * objects.
 */


/**
 * G_VALUE_TYPE:
 * @value: A #GValue structure.
 *
 * Get the type identifier of @value.
 *
 * Returns: the #GType.
 */


/**
 * G_VALUE_TYPE_NAME:
 * @value: A #GValue structure.
 *
 * Gets the the type name of @value.
 *
 * Returns: the type name.
 */


/**
 * G_VARIANT_TYPE:
 * @type_string: a well-formed #GVariantType type string
 *
 * Converts a string to a const #GVariantType.  Depending on the
 * current debugging level, this function may perform a runtime check
 * to ensure that @string is a valid GVariant type string.
 *
 * It is always a programmer error to use this macro with an invalid
 * type string. If in doubt, use g_variant_type_string_is_valid() to
 * check if the string is valid.
 *
 * Since 2.24
 */


/**
 * G_VARIANT_TYPE_ANY:
 *
 * An indefinite type that is a supertype of every type (including
 * itself).
 */


/**
 * G_VARIANT_TYPE_ARRAY:
 *
 * An indefinite type that is a supertype of every array type.
 */


/**
 * G_VARIANT_TYPE_BASIC:
 *
 * An indefinite type that is a supertype of every basic (ie:
 * non-container) type.
 */


/**
 * G_VARIANT_TYPE_BOOLEAN:
 *
 * The type of a value that can be either %TRUE or %FALSE.
 */


/**
 * G_VARIANT_TYPE_BYTE:
 *
 * The type of an integer value that can range from 0 to 255.
 */


/**
 * G_VARIANT_TYPE_BYTESTRING:
 *
 * The type of an array of bytes.  This type is commonly used to pass
 * around strings that may not be valid utf8.  In that case, the
 * convention is that the nul terminator character should be included as
 * the last character in the array.
 */


/**
 * G_VARIANT_TYPE_BYTESTRING_ARRAY:
 *
 * The type of an array of byte strings (an array of arrays of bytes).
 */


/**
 * G_VARIANT_TYPE_DICTIONARY:
 *
 * An indefinite type that is a supertype of every dictionary type --
 * that is, any array type that has an element type equal to any
 * dictionary entry type.
 */


/**
 * G_VARIANT_TYPE_DICT_ENTRY:
 *
 * An indefinite type that is a supertype of every dictionary entry
 * type.
 */


/**
 * G_VARIANT_TYPE_DOUBLE:
 *
 * The type of a double precision IEEE754 floating point number.
 * These guys go up to about 1.80e308 (plus and minus) but miss out on
 * some numbers in between.  In any case, that's far greater than the
 * estimated number of fundamental particles in the observable
 * universe.
 */


/**
 * G_VARIANT_TYPE_HANDLE:
 *
 * The type of a 32bit signed integer value, that by convention, is used
 * as an index into an array of file descriptors that are sent alongside
 * a D-Bus message.
 *
 * If you are not interacting with D-Bus, then there is no reason to make
 * use of this type.
 */


/**
 * G_VARIANT_TYPE_INT16:
 *
 * The type of an integer value that can range from -32768 to 32767.
 */


/**
 * G_VARIANT_TYPE_INT32:
 *
 * The type of an integer value that can range from -2147483648 to
 * 2147483647.
 */


/**
 * G_VARIANT_TYPE_INT64:
 *
 * The type of an integer value that can range from
 * -9223372036854775808 to 9223372036854775807.
 */


/**
 * G_VARIANT_TYPE_MAYBE:
 *
 * An indefinite type that is a supertype of every maybe type.
 */


/**
 * G_VARIANT_TYPE_OBJECT_PATH:
 *
 * The type of a D-Bus object reference.  These are strings of a
 * specific format used to identify objects at a given destination on
 * the bus.
 *
 * If you are not interacting with D-Bus, then there is no reason to make
 * use of this type.  If you are, then the D-Bus specification contains a
 * precise description of valid object paths.
 */


/**
 * G_VARIANT_TYPE_OBJECT_PATH_ARRAY:
 *
 * The type of an array of object paths.
 */


/**
 * G_VARIANT_TYPE_SIGNATURE:
 *
 * The type of a D-Bus type signature.  These are strings of a specific
 * format used as type signatures for D-Bus methods and messages.
 *
 * If you are not interacting with D-Bus, then there is no reason to make
 * use of this type.  If you are, then the D-Bus specification contains a
 * precise description of valid signature strings.
 */


/**
 * G_VARIANT_TYPE_STRING:
 *
 * The type of a string.  "" is a string.  %NULL is not a string.
 */


/**
 * G_VARIANT_TYPE_STRING_ARRAY:
 *
 * The type of an array of strings.
 */


/**
 * G_VARIANT_TYPE_TUPLE:
 *
 * An indefinite type that is a supertype of every tuple type,
 * regardless of the number of items in the tuple.
 */


/**
 * G_VARIANT_TYPE_UINT16:
 *
 * The type of an integer value that can range from 0 to 65535.
 * There were about this many people living in Toronto in the 1870s.
 */


/**
 * G_VARIANT_TYPE_UINT32:
 *
 * The type of an integer value that can range from 0 to 4294967295.
 * That's one number for everyone who was around in the late 1970s.
 */


/**
 * G_VARIANT_TYPE_UINT64:
 *
 * The type of an integer value that can range from 0 to
 * 18446744073709551616.  That's a really big number, but a Rubik's
 * cube can have a bit more than twice as many possible positions.
 */


/**
 * G_VARIANT_TYPE_UNIT:
 *
 * The empty tuple type.  Has only one instance.  Known also as "triv"
 * or "void".
 */


/**
 * G_VARIANT_TYPE_VARDICT:
 *
 * The type of a dictionary mapping strings to variants (the ubiquitous
 * "a{sv}" type).
 *
 * Since: 2.30
 */


/**
 * G_VARIANT_TYPE_VARIANT:
 *
 * The type of a box that contains any other value (including another
 * variant).
 */


/**
 * SECTION:enumerations_flags
 * @short_description: Enumeration and flags types
 * @title: Enumeration and Flag Types g_param_spec_flags()
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
 * g_object_bind_property (object1, "property-a",
 * object2, "property-b",
 * G_BINDING_DEFAULT);
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
 * g_object_bind_property (object1, "property-a",
 * object2, "property-b",
 * G_BINDING_BIDIRECTIONAL);
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
 * g_object_bind_property_full (adjustment1, "value",
 * adjustment2, "value",
 * G_BINDING_BIDIRECTIONAL,
 * celsius_to_fahrenheit,
 * fahrenheit_to_celsius,
 * NULL, NULL);
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
 * object1:propertyA -> object2:propertyB
 * object2:propertyB -> object3:propertyC
 * object3:propertyC -> object1:propertyA
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
 * #GBinding is available since GObject 2.26
 */


/**
 * SECTION:gboxed
 * @short_description: A mechanism to wrap opaque C structures registered by the type system
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
 * @short_description: A polymorphic type that can hold values of any other type
 * @see_also: The fundamental types which all support #GValue operations and thus can be used as a type initializer for g_value_init() are defined by a separate interface.  See the <link linkend="gobject-Standard-Parameter-and-Value-Types">Standard Values API</link> for details.
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
 * GValue       *dest_value)
 * {
 * if (g_value_get_int (src_value) == 42)
 * g_value_set_static_string (dest_value, "An important number");
 * else
 * g_value_set_static_string (dest_value, "What's that?");
 * }
 *
 * int
 * main (int   argc,
 * char *argv[])
 * {
 * /&ast; GValues must be initialized &ast;/
 * GValue a = G_VALUE_INIT;
 * GValue b = G_VALUE_INIT;
 * const gchar *message;
 *
 * g_type_init ();
 *
 * /&ast; The GValue starts empty &ast;/
 * g_assert (!G_VALUE_HOLDS_STRING (&amp;a));
 *
 * /&ast; Put a string in it &ast;/
 * g_value_init (&amp;a, G_TYPE_STRING);
 * g_assert (G_VALUE_HOLDS_STRING (&amp;a));
 * g_value_set_static_string (&amp;a, "Hello, world!");
 * g_printf ("%s\n", g_value_get_string (&amp;a));
 *
 * /&ast; Reset it to its pristine state &ast;/
 * g_value_unset (&amp;a);
 *
 * /&ast; It can then be reused for another type &ast;/
 * g_value_init (&amp;a, G_TYPE_INT);
 * g_value_set_int (&amp;a, 42);
 *
 * /&ast; Attempt to transform it into a GValue of type STRING &ast;/
 * g_value_init (&amp;b, G_TYPE_STRING);
 *
 * /&ast; An INT is transformable to a STRING &ast;/
 * g_assert (g_value_type_transformable (G_TYPE_INT, G_TYPE_STRING));
 *
 * g_value_transform (&amp;a, &amp;b);
 * g_printf ("%s\n", g_value_get_string (&amp;b));
 *
 * /&ast; Attempt to transform it again using a custom transform function &ast;/
 * g_value_register_transform_func (G_TYPE_INT, G_TYPE_STRING, int2string);
 * g_value_transform (&amp;a, &amp;b);
 * g_printf ("%s\n", g_value_get_string (&amp;b));
 * return 0;
 * }
 * ]|
 */


/**
 * SECTION:gparamspec
 * @short_description: Metadata for parameter specifications
 * @see_also: g_object_class_install_property(), g_object_set(), g_object_get(), g_object_set_property(), g_object_get_property(), g_value_register_transform_func()
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
 * @short_description: The GLib Runtime type identification and management system
 *
 * The GType API is the foundation of the GObject system.  It provides the
 * facilities for registering and managing all fundamental data types,
 * user-defined object and interface types.  Before using any GType
 * or GObject functions, g_type_init() must be called to initialize the
 * type system.
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
 * @short_description: Type loading modules <varlistentry> <term>#GTypePlugin</term> <listitem><para>The abstract type loader interface.</para></listitem> </varlistentry> <varlistentry> <term>#GModule</term> <listitem><para>Portable mechanism for dynamically loaded modules.</para></listitem> </varlistentry> </variablelist>
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
 * The type is initially introduced (usually upon loading the module
 * the first time, or by your main application that knows what modules
 * introduces what types), like this:
 * |[
 * new_type_id = g_type_register_dynamic (parent_type_id,
 * "TypeName",
 * new_type_plugin,
 * type_flags);
 * ]|
 * where <literal>new_type_plugin</literal> is an implementation of the
 * #GTypePlugin interface.
 * </para></listitem>
 * <listitem><para>
 * The type's implementation is referenced, e.g. through
 * g_type_class_ref() or through g_type_create_instance() (this is
 * being called by g_object_new()) or through one of the above done on
 * a type derived from <literal>new_type_id</literal>.
 * </para></listitem>
 * <listitem><para>
 * This causes the type system to load the type's implementation by calling
 * g_type_plugin_use() and g_type_plugin_complete_type_info() on
 * <literal>new_type_plugin</literal>.
 * </para></listitem>
 * <listitem><para>
 * At some point the type's implementation isn't required anymore, e.g. after
 * g_type_class_unref() or g_type_free_instance() (called when the reference
 * count of an instance drops to zero).
 * </para></listitem>
 * <listitem><para>
 * This causes the type system to throw away the information retrieved from
 * g_type_plugin_complete_type_info() and then it calls
 * g_type_plugin_unuse() on <literal>new_type_plugin</literal>.
 * </para></listitem>
 * <listitem><para>
 * Things may repeat from the second step.
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
 * g_object_force_floating (object);
 * g_object_unref (object); /&ast; release previously acquired reference &ast;/
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
 * @short_description: A means for customization of object behaviour and a general purpose notification mechanism
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
 * 1 - Invocation of the object method handler for %G_SIGNAL_RUN_FIRST signals
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 2 - Invocation of normal user-provided signal handlers (<emphasis>after</emphasis> flag %FALSE)
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 3 - Invocation of the object method handler for %G_SIGNAL_RUN_LAST signals
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 4 - Invocation of user provided signal handlers, connected with an <emphasis>after</emphasis> flag of %TRUE
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * 5 - Invocation of the object method handler for %G_SIGNAL_RUN_CLEANUP signals
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
 * @short_description: A container structure to maintain an array of generic values
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
 * GValueArray *array = g_value_array_new (10);
 * ]|
 *
 * can be replaced by:
 *
 * |[
 * GArray *array = g_array_sized_new (FALSE, TRUE, sizeof (GValue), 10);
 * g_array_set_clear_func (array, (GDestroyNotify) g_value_unset);
 * ]|
 */


/**
 * SECTION:value_collection
 * @Short_description: Converting varargs to generic values
 * @Title: Varargs Value Collection
 *
 * The macros in this section provide the varargs parsing support needed
 * in variadic GObject functions such as g_object_new() or g_object_set().
 * They currently support the collection of integral types, floating point
 * types and pointers.
 */


/**
 * g_alloca:
 * @size: number of bytes to allocate.
 *
 * Allocates @size bytes on the stack; these bytes will be freed when the current
 * stack frame is cleaned up. This macro essentially just wraps the alloca()
 * function present on most UNIX variants.
 * Thus it provides the same advantages and pitfalls as alloca():
 * <variablelist>
 * <varlistentry><term></term><listitem><para>
 * + alloca() is very fast, as on most systems it's implemented by just adjusting
 * the stack pointer register.
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * + It doesn't cause any memory fragmentation, within its scope, separate alloca()
 * blocks just build up and are released together at function end.
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * - Allocation sizes have to fit into the current stack frame. For instance in a
 * threaded environment on Linux, the per-thread stack size is limited to 2 Megabytes,
 * so be sparse with alloca() uses.
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * - Allocation failure due to insufficient stack space is not indicated with a %NULL
 * return like e.g. with malloc(). Instead, most systems probably handle it the same
 * way as out of stack space situations from infinite function recursion, i.e.
 * with a segmentation fault.
 * </para></listitem></varlistentry>
 * <varlistentry><term></term><listitem><para>
 * - Special care has to be taken when mixing alloca() with GNU C variable sized arrays.
 * Stack space allocated with alloca() in the same scope as a variable sized array
 * will be freed together with the variable sized array upon exit of that scope, and
 * not upon exit of the enclosing function scope.
 * </para></listitem></varlistentry>
 * </variablelist>
 *
 * Returns: space for @size bytes, allocated on the stack
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
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
 * @invocation_hint: the invocation hint given as the last argument to g_closure_invoke()
 * @marshal_data: additional data specified when registering the marshaller
 *
 * A marshaller for a #GCClosure with a callback of type
 * <literal>void (*callback) (gpointer instance, gpointer user_data)</literal>.
 */


/**
 * g_cclosure_marshal_generic:
 * @closure: A #GClosure.
 * @return_gvalue: A #GValue to store the return value. May be %NULL if the callback of closure doesn't return a value.
 * @n_param_values: The length of the @param_values array.
 * @param_values: An array of #GValue<!-- -->s holding the arguments on which to invoke the callback of closure.
 * @invocation_hint: The invocation hint given as the last argument to g_closure_invoke().
 * @marshal_data: Additional data specified when registering the marshaller, see g_closure_set_marshal() and g_closure_set_meta_marshal()
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
 * @return_value: (allow-none): a #GValue to store the return value. May be %NULL if the callback of @closure doesn't return a value.
 * @n_param_values: the length of the @param_values array
 * @param_values: (array length=n_param_values): an array of #GValue<!-- -->s holding the arguments on which to invoke the callback of @closure
 * @invocation_hint: (allow-none): a context-dependent invocation hint
 *
 * Invokes the closure, i.e. executes the callback represented by the @closure.
 */


/**
 * g_closure_new_object:
 * @sizeof_closure: the size of the structure to allocate, must be at least <literal>sizeof (GClosure)</literal>
 * @object: a #GObject pointer to store in the @data field of the newly allocated #GClosure
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
 * @sizeof_closure: the size of the structure to allocate, must be at least <literal>sizeof (GClosure)</literal>
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
 * GClosure closure;
 * // extra data goes here
 * };
 *
 * static void
 * my_closure_finalize (gpointer  notify_data,
 * GClosure *closure)
 * {
 * MyClosure *my_closure = (MyClosure *)closure;
 *
 * // free extra data here
 * }
 *
 * MyClosure *my_closure_new (gpointer data)
 * {
 * GClosure *closure;
 * MyClosure *my_closure;
 *
 * closure = g_closure_new_simple (sizeof (MyClosure), data);
 * my_closure = (MyClosure *) closure;
 *
 * // initialize extra data here
 *
 * g_closure_add_finalize_notifier (closure, notify_data,
 * my_closure_finalize);
 * return my_closure;
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
 * @notify_data: data which was passed to g_closure_add_finalize_notifier() when registering @notify_func
 * @notify_func: the callback function to remove
 *
 * Removes a finalization notifier.
 *
 * Notice that notifiers are automatically removed after they are run.
 */


/**
 * g_closure_remove_invalidate_notifier: (skip)
 * @closure: a #GClosure
 * @notify_data: data which was passed to g_closure_add_invalidate_notifier() when registering @notify_func
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
 * @closure: #GClosure to decrement the initial reference count on, if it's still being held
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
 * if (notify_closure)
 * g_closure_unref (notify_closure);
 * notify_closure = closure;
 * if (notify_closure)
 * {
 * g_closure_ref (notify_closure);
 * g_closure_sink (notify_closure);
 * }
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
 * @info: the #GTypeInfo struct to be filled in
 * @const_values: An array of #GEnumValue structs for the possible enumeration values. The array is terminated by a struct with all members being 0.
 *
 * This function is meant to be called from the <literal>complete_type_info</literal>
 * function of a #GTypePlugin implementation, as in the following
 * example:
 *
 * |[
 * static void
 * my_enum_complete_type_info (GTypePlugin     *plugin,
 * GType            g_type,
 * GTypeInfo       *info,
 * GTypeValueTable *value_table)
 * {
 * static const GEnumValue values[] = {
 * { MY_ENUM_FOO, "MY_ENUM_FOO", "foo" },
 * { MY_ENUM_BAR, "MY_ENUM_BAR", "bar" },
 * { 0, NULL, NULL }
 * };
 *
 * g_enum_complete_type_info (type, info, values);
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
 * member of the enumeration
 *
 * Returns: the #GEnumValue for @value, or %NULL if @value is not a
 */


/**
 * g_enum_get_value_by_name:
 * @enum_class: a #GEnumClass
 * @name: the name to look up
 *
 * Looks up a #GEnumValue by name.
 *
 * enumeration doesn't have a member with that name
 *
 * Returns: the #GEnumValue with name @name, or %NULL if the
 */


/**
 * g_enum_get_value_by_nick:
 * @enum_class: a #GEnumClass
 * @nick: the nickname to look up
 *
 * Looks up a #GEnumValue by nickname.
 *
 * enumeration doesn't have a member with that nickname
 *
 * Returns: the #GEnumValue with nickname @nick, or %NULL if the
 */


/**
 * g_enum_register_static:
 * @name: A nul-terminated string used as the name of the new type.
 * @const_static_values: An array of #GEnumValue structs for the possible enumeration values. The array is terminated by a struct with all members being 0. GObject keeps a reference to the data, so it cannot be stack-allocated.
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
 * @info: the #GTypeInfo struct to be filled in
 * @const_values: An array of #GFlagsValue structs for the possible enumeration values. The array is terminated by a struct with all members being 0.
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
 * none is set
 *
 * Returns: the first #GFlagsValue which is set in @value, or %NULL if
 */


/**
 * g_flags_get_value_by_name:
 * @flags_class: a #GFlagsClass
 * @name: the name to look up
 *
 * Looks up a #GFlagsValue by name.
 *
 * flag with that name
 *
 * Returns: the #GFlagsValue with name @name, or %NULL if there is no
 */


/**
 * g_flags_get_value_by_nick:
 * @flags_class: a #GFlagsClass
 * @nick: the nickname to look up
 *
 * Looks up a #GFlagsValue by nickname.
 *
 * no flag with that nickname
 *
 * Returns: the #GFlagsValue with nickname @nick, or %NULL if there is
 */


/**
 * g_flags_register_static:
 * @name: A nul-terminated string used as the name of the new type.
 * @const_static_values: An array of #GFlagsValue structs for the possible flags values. The array is terminated by a struct with all members being 0. GObject keeps a reference to the data, so it cannot be stack-allocated.
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
 * g_main_destroy:
 * @loop: a #GMainLoop
 *
 * Frees the memory allocated for the #GMainLoop.
 *
 * Deprecated: 2.2: Use g_main_loop_unref() instead
 */


/**
 * g_main_is_running:
 * @loop: a #GMainLoop
 *
 * Checks if the main loop is running.
 *
 * Returns: %TRUE if the main loop is running
 * Deprecated: 2.2: Use g_main_loop_is_running() instead
 */


/**
 * g_main_iteration:
 * @may_block: set to %TRUE if it should block (i.e. wait) until an event source becomes ready. It will return after an event source has been processed. If set to %FALSE it will return immediately if no event source is ready to be processed.
 *
 * Runs a single iteration for the default #GMainContext.
 *
 * Returns: %TRUE if more events are pending.
 * Deprecated: 2.2: Use g_main_context_iteration() instead.
 */


/**
 * g_main_new:
 * @is_running: set to %TRUE to indicate that the loop is running. This is not very important since calling g_main_run() will set this to %TRUE anyway.
 *
 * Creates a new #GMainLoop for th default main context.
 *
 * Returns: a new #GMainLoop
 * Deprecated: 2.2: Use g_main_loop_new() instead
 */


/**
 * g_main_pending:
 *
 * Checks if any events are pending for the default #GMainContext
 * (i.e. ready to be processed).
 *
 *
 * Deprected: 2.2: Use g_main_context_pending() instead.
 *
 * Returns: %TRUE if any events are pending.
 */


/**
 * g_main_quit:
 * @loop: a #GMainLoop
 *
 * Stops the #GMainLoop.
 * If g_main_run() was called to run the #GMainLoop, it will now return.
 *
 * Deprecated: 2.2: Use g_main_loop_quit() instead
 */


/**
 * g_main_run:
 * @loop: a #GMainLoop
 *
 * Runs a main loop until it stops running.
 *
 * Deprecated: 2.2: Use g_main_loop_run() instead
 */


/**
 * g_main_set_poll_func:
 * @func: the function to call to poll all file descriptors
 *
 * Sets the function to use for the handle polling of file descriptors
 * for the default main context.
 *
 * Deprecated: 2.2: Use g_main_context_set_poll_func() again
 */


/**
 * g_new:
 * @struct_type: the type of the elements to allocate
 * @n_structs: the number of elements to allocate
 *
 * Allocates @n_structs elements of type @struct_type.
 * The returned pointer is cast to a pointer to the given type.
 * If @n_structs is 0 it returns %NULL.
 * Care is taken to avoid overflow when calculating the size of the allocated block.
 *
 * Since the returned pointer is already casted to the right type,
 * it is normally unnecessary to cast it explicitly, and doing
 * so might hide memory allocation errors.
 *
 * Returns: a pointer to the allocated memory, cast to a pointer to @struct_type
 */


/**
 * g_new0:
 * @struct_type: the type of the elements to allocate.
 * @n_structs: the number of elements to allocate.
 *
 * Allocates @n_structs elements of type @struct_type, initialized to 0's.
 * The returned pointer is cast to a pointer to the given type.
 * If @n_structs is 0 it returns %NULL.
 * Care is taken to avoid overflow when calculating the size of the allocated block.
 *
 * Since the returned pointer is already casted to the right type,
 * it is normally unnecessary to cast it explicitly, and doing
 * so might hide memory allocation errors.
 *
 * Returns: a pointer to the allocated memory, cast to a pointer to @struct_type.
 */


/**
 * g_newa:
 * @struct_type: Type of memory chunks to be allocated
 * @n_structs: Number of chunks to be allocated
 *
 * Wraps g_alloca() in a more typesafe manner.
 *
 * Returns: Pointer to stack space for @n_structs chunks of type @struct_type
 */


/**
 * g_node_append:
 * @parent: the #GNode to place the new #GNode under
 * @node: the #GNode to insert
 *
 * Inserts a #GNode as the last child of the given parent.
 *
 * Returns: the inserted #GNode
 */


/**
 * g_node_append_data:
 * @parent: the #GNode to place the new #GNode under
 * @data: the data for the new #GNode
 *
 * Inserts a new #GNode as the last child of the given parent.
 *
 * Returns: the new #GNode
 */


/**
 * g_node_first_child:
 * @node: a #GNode
 *
 * Gets the first child of a #GNode.
 *
 * or has no children
 *
 * Returns: the first child of @node, or %NULL if @node is %NULL
 */


/**
 * g_node_insert_data:
 * @parent: the #GNode to place the new #GNode under
 * @position: the position to place the new #GNode at. If position is -1, the new #GNode is inserted as the last child of @parent
 * @data: the data for the new #GNode
 *
 * Inserts a new #GNode at the given position.
 *
 * Returns: the new #GNode
 */


/**
 * g_node_insert_data_after:
 * @parent: the #GNode to place the new #GNode under
 * @sibling: the sibling #GNode to place the new #GNode after
 * @data: the data for the new #GNode
 *
 * Inserts a new #GNode after the given sibling.
 *
 * Returns: the new #GNode
 */


/**
 * g_node_insert_data_before:
 * @parent: the #GNode to place the new #GNode under
 * @sibling: the sibling #GNode to place the new #GNode before
 * @data: the data for the new #GNode
 *
 * Inserts a new #GNode before the given sibling.
 *
 * Returns: the new #GNode
 */


/**
 * g_node_next_sibling:
 * @node: a #GNode
 *
 * Gets the next sibling of a #GNode.
 *
 * or %NULL
 *
 * Returns: the next sibling of @node, or %NULL if @node is the last node
 */


/**
 * g_node_prepend_data:
 * @parent: the #GNode to place the new #GNode under
 * @data: the data for the new #GNode
 *
 * Inserts a new #GNode as the first child of the given parent.
 *
 * Returns: the new #GNode
 */


/**
 * g_node_prev_sibling:
 * @node: a #GNode
 *
 * Gets the previous sibling of a #GNode.
 *
 * node or %NULL
 *
 * Returns: the previous sibling of @node, or %NULL if @node is the first
 */


/**
 * g_object_add_toggle_ref: (skip)
 * @object: a #GObject
 * @notify: a function to call when this reference is the last reference to the object, or is no longer the last reference.
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
 * g_object_bind_property (action, "active", widget, "sensitive", 0);
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
 * binding between the two #GObject instances. The binding is released
 * whenever the #GBinding reference count reaches zero.
 *
 * Returns: (transfer none): the #GBinding instance representing the
 * Since: 2.26
 */


/**
 * g_object_bind_property_full:
 * @source: (type GObject.Object): the source #GObject
 * @source_property: the property on @source to bind
 * @target: (type GObject.Object): the target #GObject
 * @target_property: the property on @target to bind
 * @flags: flags to pass to #GBinding
 * @transform_to: (scope notified) (allow-none): the transformation function from the @source to the @target, or %NULL to use the default
 * @transform_from: (scope notified) (allow-none): the transformation function from the @target to the @source, or %NULL to use the default
 * @user_data: custom data to be passed to the transformation functions, or %NULL
 * @notify: function to be called when disposing the binding, to free the resources used by the transformation functions
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
 * binding between the two #GObject instances. The binding is released
 * whenever the #GBinding reference count reaches zero.
 *
 * Returns: (transfer none): the #GBinding instance representing the
 * Since: 2.26
 */


/**
 * g_object_bind_property_with_closures:
 * @source: (type GObject.Object): the source #GObject
 * @source_property: the property on @source to bind
 * @target: (type GObject.Object): the target #GObject
 * @target_property: the property on @target to bind
 * @flags: flags to pass to #GBinding
 * @transform_to: a #GClosure wrapping the transformation function from the @source to the @target, or %NULL to use the default
 * @transform_from: a #GClosure wrapping the transformation function from the @target to the @source, or %NULL to use the default
 *
 * Creates a binding between @source_property on @source and @target_property
 * on @target, allowing you to set the transformation functions to be used by
 * the binding.
 *
 * This function is the language bindings friendly version of
 * g_object_bind_property_full(), using #GClosure<!-- -->s instead of
 * function pointers.
 *
 *
 * binding between the two #GObject instances. The binding is released
 * whenever the #GBinding reference count reaches zero.
 *
 * Rename to: g_object_bind_property_full
 * Returns: (transfer none): the #GBinding instance representing the
 * Since: 2.26
 */


/**
 * g_object_class_find_property:
 * @oclass: a #GObjectClass
 * @property_name: the name of the property to look up
 *
 * Looks up the #GParamSpec for a property of a class.
 *
 * %NULL if the class doesn't have a property of that name
 *
 * Returns: (transfer none): the #GParamSpec for the property, or
 */


/**
 * g_object_class_install_properties:
 * @oclass: a #GObjectClass
 * @n_pspecs: the length of the #GParamSpec<!-- -->s array
 * @pspecs: (array length=n_pspecs): the #GParamSpec<!-- -->s array defining the new properties
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
 * PROP_0, PROP_FOO, PROP_BAR, N_PROPERTIES
 * };
 *
 * static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };
 *
 * static void
 * my_object_class_init (MyObjectClass *klass)
 * {
 * GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
 *
 * obj_properties[PROP_FOO] =
 * g_param_spec_int ("foo", "Foo", "Foo",
 * -1, G_MAXINT,
 * 0,
 * G_PARAM_READWRITE);
 *
 * obj_properties[PROP_BAR] =
 * g_param_spec_string ("bar", "Bar", "Bar",
 * NULL,
 * G_PARAM_READWRITE);
 *
 * gobject_class->set_property = my_object_set_property;
 * gobject_class->get_property = my_object_get_property;
 * g_object_class_install_properties (gobject_class,
 * N_PROPERTIES,
 * obj_properties);
 * }
 * ]|
 *
 * allows calling g_object_notify_by_pspec() to notify of property changes:
 *
 * |[
 * void
 * my_object_set_foo (MyObject *self, gint foo)
 * {
 * if (self->foo != foo)
 * {
 * self->foo = foo;
 * g_object_notify_by_pspec (G_OBJECT (self), obj_properties[PROP_FOO]);
 * }
 * }
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
 * #GParamSpec* which should be freed after use
 *
 * Returns: (array length=n_properties) (transfer container): an array of
 */


/**
 * g_object_class_override_property:
 * @oclass: a #GObjectClass
 * @property_id: the new property ID
 * @name: the name of a property registered in a parent class or in an interface of this class.
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
 * @...: #GCallback for the first signal, followed by data for the first signal, followed optionally by more signal spec/callback/data triples, followed by %NULL
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
 * menu->toplevel = g_object_connect (g_object_new (GTK_TYPE_WINDOW,
 * "type", GTK_WINDOW_POPUP,
 * "child", menu,
 * NULL),
 * "signal::event", gtk_menu_window_event, menu,
 * "signal::size_request", gtk_menu_window_size_request, menu,
 * "signal::destroy", gtk_widget_destroyed, &amp;menu-&gt;toplevel,
 * NULL);
 * ]|
 *
 * Returns: (transfer none): @object
 */


/**
 * g_object_disconnect: (skip)
 * @object: a #GObject
 * @signal_spec: the spec for the first signal
 * @...: #GCallback for the first signal, followed by data for the first signal, followed optionally by more signal spec/callback/data triples, followed by %NULL
 *
 * A convenience function to disconnect multiple signals at once.
 *
 * The signal specs expected by this function have the form
 * "any_signal", which means to disconnect any signal with matching
 * callback and data, or "any_signal::signal_name", which only
 * disconnects the signal named "signal_name".
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
 * to zero.
 *
 * This is necessary for accessors that modify multiple properties to prevent
 * premature notification while the object is still being modified.
 */


/**
 * g_object_get: (skip)
 * @object: a #GObject
 * @first_property_name: name of the first property to get
 * @...: return location for the first property, followed optionally by more name/return location pairs, followed by %NULL
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
 * gint intval;
 * gchar *strval;
 * GObject *objval;
 *
 * g_object_get (my_object,
 * "int-property", &intval,
 * "str-property", &strval,
 * "obj-property", &objval,
 * NULL);
 *
 * // Do something with intval, strval, objval
 *
 * g_free (strval);
 * g_object_unref (objval);
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
 * @var_args: return location for the first property, followed optionally by more name/return location pairs, followed by %NULL
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
 * @g_iface: any interface vtable for the interface, or the default vtable for the interface
 * @property_name: name of a property to lookup.
 *
 * Find the #GParamSpec with the given name for an
 * interface. Generally, the interface vtable passed in as @g_iface
 * will be the default vtable from g_type_default_interface_ref(), or,
 * if you know the interface has already been loaded,
 * g_type_default_interface_peek().
 *
 *
 * interface with the name @property_name, or %NULL if no
 * such property exists.
 *
 * Since: 2.4
 * Returns: (transfer none): the #GParamSpec for the property of the
 */


/**
 * g_object_interface_install_property:
 * @g_iface: any interface vtable for the interface, or the default vtable for the interface.
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
 * @g_iface: any interface vtable for the interface, or the default vtable for the interface
 * @n_properties_p: (out): location to store number of properties returned.
 *
 * Lists the properties of an interface.Generally, the interface
 * vtable passed in as @g_iface will be the default vtable from
 * g_type_default_interface_ref(), or, if you know the interface has
 * already been loaded, g_type_default_interface_peek().
 *
 *
 * pointer to an array of pointers to #GParamSpec
 * structures. The paramspecs are owned by GLib, but the
 * array should be freed with g_free() when you are done with
 * it.
 *
 * Since: 2.4
 * Returns: (array length=n_properties_p) (transfer container): a
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
 * @...: the value of the first property, followed optionally by more name/value pairs, followed by %NULL
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
 * @var_args: the value of the first property, followed optionally by more name/value pairs, followed by %NULL
 *
 * Creates a new instance of a #GObject subtype and sets its properties.
 *
 * Construction parameters (see #G_PARAM_CONSTRUCT, #G_PARAM_CONSTRUCT_ONLY)
 * which are not explicitly specified are set to their default values.
 *
 * Returns: a new instance of @object_type
 */


/**
 * g_object_newv:
 * @object_type: the type id of the #GObject subtype to instantiate
 * @n_parameters: the length of the @parameters array
 * @parameters: (array length=n_parameters): an array of #GParameter
 *
 * Creates a new instance of a #GObject subtype and sets its properties.
 *
 * Construction parameters (see #G_PARAM_CONSTRUCT, #G_PARAM_CONSTRUCT_ONLY)
 * which are not explicitly specified are set to their default values.
 *
 * @object_type
 *
 * Rename to: g_object_new
 * Returns: (type GObject.Object) (transfer full): a new instance of
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
 * enum
 * {
 * PROP_0,
 * PROP_FOO,
 * PROP_LAST
 * };
 *
 * static GParamSpec *properties[PROP_LAST];
 *
 * static void
 * my_object_class_init (MyObjectClass *klass)
 * {
 * properties[PROP_FOO] = g_param_spec_int ("foo", "Foo", "The foo",
 * 0, 100,
 * 50,
 * G_PARAM_READWRITE);
 * g_object_class_install_property (gobject_class,
 * PROP_FOO,
 * properties[PROP_FOO]);
 * }
 * ]|
 *
 * and then notify a change on the "foo" property with:
 *
 * |[
 * g_object_notify_by_pspec (self, properties[PROP_FOO]);
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
 * @notify: a function to call when this reference is the last reference to the object, or is no longer the last reference.
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
 * @...: value for the first property, followed optionally by more name/value pairs, followed by %NULL
 *
 * Sets properties on an object.
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
 * @destroy: Function to invoke with @data as argument, when @data needs to be freed
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
 * @var_args: value for the first property, followed optionally by more name/value pairs, followed by %NULL
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
 * const gchar *new_string)
 * {
 * // the quark, naming the object data
 * GQuark quark_string_list = g_quark_from_static_string ("my-string-list");
 * // retrive the old string list
 * GList *list = g_object_steal_qdata (object, quark_string_list);
 *
 * // prepend new string
 * list = g_list_prepend (list, g_strdup (new_string));
 * // this changed 'list', so we need to set it again
 * g_object_set_qdata_full (object, quark_string_list, list, free_string_list);
 * }
 * static void
 * free_string_list (gpointer data)
 * {
 * GList *node, *list = data;
 *
 * for (node = list; node; node = node->next)
 * g_free (node->data);
 * g_list_free (list);
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
 * and when it reaches zero, all queued "notify" signals are emitted.
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
 * g_param_spec_boolean: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_boxed: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_char: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_double: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_enum: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_flags: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_float: (skip)
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
 * Returns: a newly created parameter specification
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
 *
 * paramspec should be redirected, or %NULL if none.
 *
 * Since: 2.4
 * Returns: (transfer none): paramspec to which requests on this
 */


/**
 * g_param_spec_gtype: (skip)
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @is_a_type: a #GType whose subtypes are allowed as values of the property (use %G_TYPE_NONE for any type)
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecGType instance specifying a
 * %G_TYPE_GTYPE property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Since: 2.10
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_int: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_int64: (skip)
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
 * Returns: a newly created parameter specification
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
 * g_param_spec_long: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_object: (skip)
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
 * Returns: a newly created parameter specification
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
 * g_param_spec_param: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_pointer: (skip)
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecPointer instance specifying a pointer property.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: a newly created parameter specification
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
 * allocated array containing pointers to all #GParamSpecs
 * owned by @owner_type in the pool
 *
 * Returns: (array length=n_pspecs_p) (transfer container): a newly
 */


/**
 * g_param_spec_pool_list_owned:
 * @pool: a #GParamSpecPool
 * @owner_type: the owner to look for
 *
 * Gets an #GList of all #GParamSpec<!-- -->s owned by @owner_type in
 * the pool.
 *
 * #GList of all #GParamSpec<!-- -->s owned by @owner_type in
 * the pool#GParamSpec<!-- -->s.
 *
 * Returns: (transfer container) (element-type GObject.ParamSpec): a
 */


/**
 * g_param_spec_pool_lookup:
 * @pool: a #GParamSpecPool
 * @param_name: the name to look for
 * @owner_type: the owner to look for
 * @walk_ancestors: If %TRUE, also try to find a #GParamSpec with @param_name owned by an ancestor of @owner_type.
 *
 * Looks up a #GParamSpec in the pool.
 *
 * matching #GParamSpec was found.
 *
 * Returns: (transfer none): The found #GParamSpec, or %NULL if no
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
 * @destroy: function to invoke with @data as argument, when @data needs to be freed
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
 * g_param_spec_string: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_uchar: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_uint: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_uint64: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_ulong: (skip)
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
 * Returns: a newly created parameter specification
 */


/**
 * g_param_spec_unichar: (skip)
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
 * Returns: a newly created parameter specification
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
 * @element_spec: a #GParamSpec describing the elements contained in arrays of this property, may be %NULL
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
 * g_param_spec_variant: (skip)
 * @name: canonical name of the property specified
 * @nick: nick name for the property specified
 * @blurb: description of the property specified
 * @type: a #GVariantType
 * @default_value: (allow-none): a #GVariant of type @type to use as the default value, or %NULL
 * @flags: flags for the property specified
 *
 * Creates a new #GParamSpecVariant instance specifying a #GVariant
 * property.
 *
 * If @default_value is floating, it is consumed.
 *
 * See g_param_spec_internal() for details on property names.
 *
 * Returns: the newly created #GParamSpec
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
 * @strict_validation: %TRUE requires @dest_value to conform to @pspec without modifications
 *
 * Transforms @src_value into @dest_value if possible, and then
 * validates @dest_value, in order for it to conform to @pspec.  If
 * @strict_validation is %TRUE this function will only succeed if the
 * transformed @dest_value complied to @pspec without modifications.
 *
 * See also g_value_type_transformable(), g_value_transform() and
 * g_param_value_validate().
 *
 * %FALSE otherwise and @dest_value is left untouched.
 *
 * Returns: %TRUE if transformation and validation were successful,
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
 * g_renew:
 * @struct_type: the type of the elements to allocate
 * @mem: the currently allocated memory
 * @n_structs: the number of elements to allocate
 *
 * Reallocates the memory pointed to by @mem, so that it now has space for
 * @n_structs elements of type @struct_type. It returns the new address of
 * the memory, which may have been moved.
 * Care is taken to avoid overflow when calculating the size of the allocated block.
 *
 * Returns: a pointer to the new allocated memory, cast to a pointer to @struct_type
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
 * @instance_and_params: (array) the argument list of the signal emission. The first element in the array is a #GValue for the instance the signal is being emitted on. The rest are any arguments to be passed to the signal.
 * @return_value: Location for the return value.
 *
 * Calls the original class closure of a signal. This function should only
 * be called from an overridden class closure; see
 * g_signal_override_class_closure() and
 * g_signal_override_class_handler().
 */


/**
 * g_signal_chain_from_overridden_handler:
 * @instance: the instance the signal is being emitted on.
 * @...: parameters to be passed to the parent class closure, followed by a location for the return value. If the return type of the signal is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Calls the original class closure of a signal. This function should
 * only be called from an overridden class closure; see
 * g_signal_override_class_closure() and
 * g_signal_override_class_handler().
 *
 * Since: 2.18
 */


/**
 * g_signal_connect:
 * @instance: the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @c_handler: the #GCallback to connect.
 * @data: data to pass to @c_handler calls.
 *
 * Connects a #GCallback function to a signal for a particular object.
 *
 * The handler will be called before the default handler of the signal.
 *
 * Returns: the handler id
 */


/**
 * g_signal_connect_after:
 * @instance: the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @c_handler: the #GCallback to connect.
 * @data: data to pass to @c_handler calls.
 *
 * Connects a #GCallback function to a signal for a particular object.
 *
 * The handler will be called after the default handler of the signal.
 *
 * Returns: the handler id
 */


/**
 * g_signal_connect_closure:
 * @instance: the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @closure: the closure to connect.
 * @after: whether the handler should be called before or after the default handler of the signal.
 *
 * Connects a closure to a signal for a particular object.
 *
 * Returns: the handler id
 */


/**
 * g_signal_connect_closure_by_id:
 * @instance: the instance to connect to.
 * @signal_id: the id of the signal.
 * @detail: the detail.
 * @closure: the closure to connect.
 * @after: whether the handler should be called before or after the default handler of the signal.
 *
 * Connects a closure to a signal for a particular object.
 *
 * Returns: the handler id
 */


/**
 * g_signal_connect_data:
 * @instance: the instance to connect to.
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
 * Returns: the handler id
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
 * Note that there is a bug in GObject that makes this function
 * much less useful than it might seem otherwise. Once @gobject is
 * disposed, the callback will no longer be called, but, the signal
 * handler is <emphasis>not</emphasis> currently disconnected. If the
 * @instance is itself being freed at the same time than this doesn't
 * matter, since the signal will automatically be removed, but
 * if @instance persists, then the signal handler will leak. You
 * should not remove the signal yourself because in a future versions of
 * GObject, the handler <emphasis>will</emphasis> automatically
 * be disconnected.
 *
 * It's possible to work around this problem in a way that will
 * continue to work with future versions of GObject by checking
 * that the signal handler is still connected before disconnected it:
 * <informalexample><programlisting>
 * if (g_signal_handler_is_connected (instance, id))
 * g_signal_handler_disconnect (instance, id);
 * </programlisting></informalexample>
 *
 * Returns: the handler id.
 */


/**
 * g_signal_connect_swapped:
 * @instance: the instance to connect to.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @c_handler: the #GCallback to connect.
 * @data: data to pass to @c_handler calls.
 *
 * Connects a #GCallback function to a signal for a particular object.
 *
 * The instance on which the signal is emitted and @data will be swapped when
 * calling the handler.
 *
 * Returns: the handler id
 */


/**
 * g_signal_emit:
 * @instance: the instance the signal is being emitted on.
 * @signal_id: the signal id
 * @detail: the detail
 * @...: parameters to be passed to the signal, followed by a location for the return value. If the return type of the signal is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emit_by_name:
 * @instance: the instance the signal is being emitted on.
 * @detailed_signal: a string of the form "signal-name::detail".
 * @...: parameters to be passed to the signal, followed by a location for the return value. If the return type of the signal is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit_by_name() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emit_valist:
 * @instance: the instance the signal is being emitted on.
 * @signal_id: the signal id
 * @detail: the detail
 * @var_args: a list of parameters to be passed to the signal, followed by a location for the return value. If the return type of the signal is #G_TYPE_NONE, the return value location can be omitted.
 *
 * Emits a signal.
 *
 * Note that g_signal_emit_valist() resets the return value to the default
 * if no handlers are connected, in contrast to g_signal_emitv().
 */


/**
 * g_signal_emitv:
 * @instance_and_params: (array): argument list for the signal emission. The first element in the array is a #GValue for the instance the signal is being emitted on. The rest are any arguments to be passed to the signal.
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
 * @instance: the instance to query
 *
 * Returns the invocation hint of the innermost signal emission of instance.
 *
 * Returns: (transfer none): the invocation hint of the innermost signal  emission.
 */


/**
 * g_signal_handler_block:
 * @instance: The instance to block the signal handler of.
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
 * @instance: The instance to remove the signal handler from.
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
 * @instance: The instance owning the signal handler to be found.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func and/or @data the handler has to match.
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
 * @instance: The instance where a signal handler is sought.
 * @handler_id: the handler id.
 *
 * Returns whether @handler_id is the id of a handler connected to @instance.
 *
 * Returns: whether @handler_id identifies a handler connected to @instance.
 */


/**
 * g_signal_handler_unblock:
 * @instance: The instance to unblock the signal handler of.
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
 * g_signal_handlers_block_by_func:
 * @instance: The instance to block handlers from.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Blocks all handlers on an instance that match @func and @data.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_handlers_block_matched:
 * @instance: The instance to block handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func and/or @data the handlers have to match.
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
 * g_signal_handlers_disconnect_by_data:
 * @instance: The instance to remove handlers from
 * @data: the closure data of the handlers' closures
 *
 * Disconnects all handlers on an instance that match @data.
 *
 * Returns: The number of handlers that matched.
 * Since: 2.32
 */


/**
 * g_signal_handlers_disconnect_by_func:
 * @instance: The instance to remove handlers from.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Disconnects all handlers on an instance that match @func and @data.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_handlers_disconnect_matched:
 * @instance: The instance to remove handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func and/or @data the handlers have to match.
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
 * g_signal_handlers_unblock_by_func:
 * @instance: The instance to unblock handlers from.
 * @func: The C closure callback of the handlers (useless for non-C closures).
 * @data: The closure data of the handlers' closures.
 *
 * Unblocks all handlers on an instance that match @func and @data.
 *
 * Returns: The number of handlers that matched.
 */


/**
 * g_signal_handlers_unblock_matched:
 * @instance: The instance to unblock handlers from.
 * @mask: Mask indicating which of @signal_id, @detail, @closure, @func and/or @data the handlers have to match.
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
 * @instance: the object whose signal handlers are sought.
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
 * otherwise.
 *
 * Returns: %TRUE if a handler is connected to the signal, %FALSE
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
 * @itype: the type this signal pertains to. It will also pertain to types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when the default handler is to be invoked. You should at least specify %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_offset: The offset of the function pointer in the class structure for this type. Used to invoke a class method generically. Pass 0 to not associate a class method slot with this signal.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal without a return value.
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
 * @itype: the type this signal pertains to. It will also pertain to types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when the default handler is to be invoked. You should at least specify %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_handler: a #GCallback which acts as class implementation of this signal. Used to invoke a class method generically. Pass %NULL to not associate a class method with this signal.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal without a return value.
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
 * @itype: the type this signal pertains to. It will also pertain to types which are derived from this type.
 * @signal_flags: a combination of #GSignalFlags specifying detail of when the default handler is to be invoked. You should at least specify %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST.
 * @class_closure: The closure to invoke on signal emission; may be %NULL.
 * @accumulator: the accumulator for this signal; may be %NULL.
 * @accu_data: user data for the @accumulator.
 * @c_marshaller: (allow-none): the function to translate arrays of parameter values to signal emissions into C language callback invocations or %NULL.
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal without a return value.
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
 * @itype: the type this signal pertains to. It will also pertain to types which are derived from this type
 * @signal_flags: a combination of #GSignalFlags specifying detail of when the default handler is to be invoked. You should at least specify %G_SIGNAL_RUN_FIRST or %G_SIGNAL_RUN_LAST
 * @class_closure: (allow-none): The closure to invoke on signal emission; may be %NULL
 * @accumulator: (allow-none): the accumulator for this signal; may be %NULL
 * @accu_data: user data for the @accumulator
 * @c_marshaller: (allow-none): the function to translate arrays of parameter values to signal emissions into C language callback invocations or %NULL
 * @return_type: the type of return value, or #G_TYPE_NONE for a signal without a return value
 * @n_params: the length of @param_types
 * @param_types: (array length=n_params): an array of types, one for each parameter
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
 * @instance_type: the instance type on which to override the class closure for the signal.
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
 * @instance_type: the instance type on which to override the class handler for the signal.
 * @class_handler: the handler.
 *
 * Overrides the class closure (i.e. the default handler) for the
 * given signal for emissions on instances of @instance_type with
 * callabck @class_handler. @instance_type must be derived from the
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
 * @query: (out caller-allocates): A user provided structure that is filled in with constant values upon success.
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
 * @hook_id: the id of the emission hook, as returned by g_signal_add_emission_hook()
 *
 * Deletes an emission hook.
 */


/**
 * g_signal_stop_emission:
 * @instance: the object whose signal handlers you wish to stop.
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
 * @instance: the object whose signal handlers you wish to stop.
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
 * @struct_offset: the offset of the member function of @itype's class structure which is to be invoked by the new closure
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
 * g_try_new:
 * @struct_type: the type of the elements to allocate
 * @n_structs: the number of elements to allocate
 *
 * Attempts to allocate @n_structs elements of type @struct_type, and returns
 * %NULL on failure. Contrast with g_new(), which aborts the program on failure.
 * The returned pointer is cast to a pointer to the given type.
 * The function returns %NULL when @n_structs is 0 of if an overflow occurs.
 *
 * Since: 2.8
 * Returns: a pointer to the allocated memory, cast to a pointer to @struct_type
 */


/**
 * g_try_new0:
 * @struct_type: the type of the elements to allocate
 * @n_structs: the number of elements to allocate
 *
 * Attempts to allocate @n_structs elements of type @struct_type, initialized
 * to 0's, and returns %NULL on failure. Contrast with g_new0(), which aborts
 * the program on failure.
 * The returned pointer is cast to a pointer to the given type.
 * The function returns %NULL when @n_structs is 0 of if an overflow occurs.
 *
 * Since: 2.8
 * Returns: a pointer to the allocated memory, cast to a pointer to @struct_type
 */


/**
 * g_try_renew:
 * @struct_type: the type of the elements to allocate
 * @mem: the currently allocated memory
 * @n_structs: the number of elements to allocate
 *
 * Attempts to reallocate the memory pointed to by @mem, so that it now has
 * space for @n_structs elements of type @struct_type, and returns %NULL on
 * failure. Contrast with g_renew(), which aborts the program on failure.
 * It returns the new address of the memory, which may have been moved.
 * The function returns %NULL if an overflow occurs.
 *
 * Since: 2.8
 * Returns: a pointer to the new allocated memory, cast to a pointer to @struct_type
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
 * @check_func: function to be called after each interface is initialized.
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
 * @info: The #GInterfaceInfo structure for this (@instance_type, @interface_type) combination.
 *
 * Adds the static @interface_type to @instantiable_type.  The
 * information contained in the #GInterfaceInfo structure pointed to by
 * @info is used to manage the relationship.
 */


/**
 * g_type_check_instance:
 * @instance: A valid #GTypeInstance structure.
 * @Returns: #TRUE if @instance is valid, #FALSE otherwise.
 *
 * Private helper function to aid implementation of the G_TYPE_CHECK_INSTANCE()
 * macro.
 */


/**
 * g_type_children:
 * @type: The parent type.
 * @n_children: (out) (allow-none): Optional #guint pointer to contain the number of child types.
 *
 * Return a newly allocated and 0-terminated array of type IDs, listing the
 * child types of @type. The return value has to be g_free()ed after use.
 *
 * and 0-terminated array of child types.
 *
 * Returns: (array length=n_children) (transfer full): Newly allocated
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
 * a type and all its parent types cannot excced 64 KiB.
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
 * GObject parent;
 *
 * MyObjectPrivate *priv;
 * };
 *
 * struct _MyObjectPrivate {
 * int some_field;
 * };
 *
 * static void
 * my_object_class_init (MyObjectClass *klass)
 * {
 * g_type_class_add_private (klass, sizeof (MyObjectPrivate));
 * }
 *
 * static void
 * my_object_init (MyObject *my_object)
 * {
 * my_object->priv = G_TYPE_INSTANCE_GET_PRIVATE (my_object,
 * MY_TYPE_OBJECT,
 * MyObjectPrivate);
 * }
 *
 * static int
 * my_object_get_some_field (MyObject *my_object)
 * {
 * MyObjectPrivate *priv;
 *
 * g_return_val_if_fail (MY_IS_OBJECT (my_object), 0);
 *
 * priv = my_object->priv;
 *
 * return priv->some_field;
 * }
 * ]|
 *
 * Since: 2.4
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
 * structure for the given type ID or %NULL if the class does not
 * currently exist.
 *
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 */


/**
 * g_type_class_peek_parent:
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to retrieve the parent class for.
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
 * of @g_class.
 *
 * Returns: (type GObject.TypeClass) (transfer none): The parent class
 */


/**
 * g_type_class_peek_static:
 * @type: Type ID of a classed type.
 *
 * A more efficient version of g_type_class_peek() which works only for
 * static types.
 *
 * structure for the given type ID or %NULL if the class does not
 * currently exist or is dynamically loaded.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 */


/**
 * g_type_class_ref:
 * @type: Type ID of a classed type.
 *
 * Increments the reference count of the class structure belonging to
 * @type. This function will demand-create the class if it doesn't
 * exist already.
 *
 * structure for the given type ID.
 *
 * Returns: (type GObject.TypeClass) (transfer none): The #GTypeClass
 */


/**
 * g_type_class_unref:
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to unreference.
 *
 * Decrements the reference count of the class structure being passed in.
 * Once the last reference count of a class has been released, classes
 * may be finalized by the type system, so further dereferencing of a
 * class pointer after g_type_class_unref() are invalid.
 */


/**
 * g_type_class_unref_uncached: (skip)
 * @g_class: (type GObject.TypeClass): The #GTypeClass structure to unreference.
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
 * treatment by the fundamental type implementation.
 *
 * Returns: An allocated and initialized instance, subject to further
 */


/**
 * g_type_default_interface_peek:
 * @g_type: an interface type
 *
 * If the interface type @g_type is currently in use, returns its
 * default interface vtable.
 *
 *
 * vtable for the interface, or %NULL if the type is not currently in
 * use.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeInterface) (transfer none): the default
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
 *
 * vtable for the interface; call g_type_default_interface_unref()
 * when you are done using the interface.
 *
 * Since: 2.4
 * Returns: (type GObject.TypeInterface) (transfer none): the default
 */


/**
 * g_type_default_interface_unref:
 * @g_iface: (type GObject.TypeInterface): the default vtable structure for a interface, as returned by g_type_default_interface_ref()
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
 * or 0 if the type system ran out of fundamental type IDs.
 *
 * Returns: The nextmost fundamental type ID to be registered,
 */


/**
 * g_type_get_plugin:
 * @type: The #GType to retrieve the plugin for.
 *
 * Returns the #GTypePlugin structure for @type or
 * %NULL if @type does not have a #GTypePlugin structure.
 *
 * dynamic type, %NULL otherwise.
 *
 * Returns: (transfer none): The corresponding plugin if @type is a
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
 * g_type_init:
 *
 * Prior to any use of the type system, g_type_init() has to be called
 * to initialize the type system and assorted other code portions
 * (such as the various fundamental type implementations or the signal
 * system).
 *
 * This function is idempotent.
 *
 * Since version 2.24 this also initializes the thread system
 */


/**
 * g_type_init_with_debug_flags:
 * @debug_flags: Bitwise combination of #GTypeDebugFlags values for debugging purposes.
 *
 * Similar to g_type_init(), but additionally sets debug flags.
 *
 * This function is idempotent.
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
 * interface @interface_type of @instance_type.
 *
 * Returns: (transfer none): the #GTypePlugin for the dynamic
 */


/**
 * g_type_interface_peek:
 * @instance_class: (type GObject.TypeClass): A #GTypeClass structure.
 * @iface_type: An interface ID which this class conforms to.
 *
 * Returns the #GTypeInterface structure of an interface to which the
 * passed in class conforms.
 *
 * structure of iface_type if implemented by @instance_class, %NULL
 * otherwise
 *
 * Returns: (type GObject.TypeInterface) (transfer none): The GTypeInterface
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
 * corresponding #GTypeInterface structure of the parent type of the
 * instance type to which @g_iface belongs, or %NULL if the parent
 * type doesn't conform to the interface.
 *
 * Returns: (transfer none) (type GObject.TypeInterface): The
 */


/**
 * g_type_interface_prerequisites:
 * @interface_type: an interface type
 * @n_prerequisites: (out) (allow-none): location to return the number of prerequisites, or %NULL
 *
 * Returns the prerequisites of an interfaces type.
 *
 *
 * newly-allocated zero-terminated array of #GType containing
 * the prerequisites of @interface_type
 *
 * Since: 2.2
 * Returns: (array length=n_prerequisites) (transfer full): a
 */


/**
 * g_type_interfaces:
 * @type: The type to list interface types for.
 * @n_interfaces: (out) (allow-none): Optional #guint pointer to contain the number of interface types.
 *
 * Return a newly allocated and 0-terminated array of type IDs, listing the
 * interface types that @type conforms to. The return value has to be
 * g_free()ed after use.
 *
 * allocated and 0-terminated array of interface types.
 *
 * Returns: (array length=n_interfaces) (transfer full): Newly
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
 * @const_static_values: an array of #GEnumValue structs for the possible enumeration values. The array is terminated by a struct with all members being 0.
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
 * @const_static_values: an array of #GFlagsValue structs for the possible flags values. The array is terminated by a struct with all members being 0.
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
 * loading the plugin failed.
 *
 * Returns: %FALSE if the plugin needed to be loaded and
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
 * @instance_type: the #GType of an instantiable type to which the interface is added
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
 * @query: (out caller-allocates): A user provided structure that is filled in with constant values upon success.
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
 * %NULL if there is no #GTypeValueTable associated with @type.
 *
 * Returns: Location of the #GTypeValueTable associated with @type or
 */


/**
 * g_utf8_next_char:
 * @p: Pointer to the start of a valid UTF-8 character
 *
 * Skips to the next character in a UTF-8 string. The string must be
 * valid; this macro is as fast as possible, and has no error-checking.
 * You would use this macro to iterate over a string character by
 * character. The macro returns the start of the next UTF-8 character.
 * Before using this macro, use g_utf8_validate() to validate strings
 * that may contain invalid UTF-8.
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
 * @index_: position of value to remove, which must be less than <code>value_array-><link linkend="GValueArray.n-values">n_values</link></code>
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
 * The current implementation uses Quick-Sort as sorting algorithm.
 *
 * Returns: (transfer none): the #GValueArray passed in as @value_array
 * Deprecated: 2.32: Use #GArray and g_array_sort().
 */


/**
 * g_value_array_sort_with_data:
 * @value_array: #GValueArray to sort
 * @compare_func: (scope call): function to compare elements
 * @user_data: (closure): extra data argument provided for @compare_func
 *
 * Sort @value_array using @compare_func to compare the elements according
 * to the semantics of #GCompareDataFunc.
 *
 * The current implementation uses Quick-Sort as sorting algorithm.
 *
 * Rename to: g_value_array_sort
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
 * should be unreferenced when no longer needed.
 *
 * Returns: (type GObject.Object) (transfer full): object content of @value,
 */


/**
 * g_value_dup_param: (skip)
 * @value: a valid #GValue whose type is derived from %G_TYPE_PARAM
 *
 * Get the contents of a %G_TYPE_PARAM #GValue, increasing its
 * reference count.
 *
 * no longer needed.
 *
 * Returns: #GParamSpec content of @value, should be unreferenced when
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
 * g_variant_unref() when no longer needed
 *
 * Returns: variant contents of @value, should be unrefed using
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
 * function asserts that g_value_fits_pointer() returned %TRUE for the
 * passed in value.  This is an internal function introduced mainly
 * for C marshallers.
 *
 * Returns: (transfer none): the value contents as pointer. This
 */


/**
 * g_value_register_transform_func: (skip)
 * @src_type: Source type.
 * @dest_type: Target type.
 * @transform_func: a function which transforms values of type @src_type into value of type @dest_type
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
 * Upon failing transformations, @dest_value is left untouched.
 *
 * Returns: Whether a transformation rule was found and could be applied.
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
 *
 *
 * Since: 2.24
 * Deprecated: 2.26
 */


/**
 * g_warn_if_fail:
 * @expr: the expression to check
 *
 * Logs a warning if the expression is not true.
 *
 * Since: 2.16
 */


/**
 * g_warn_if_reached:
 *
 * Logs a critical warning.
 *
 * Since: 2.16
 */


/**
 * g_weak_ref_clear: (skip)
 * @weak_ref: (inout): location of a weak reference, which may be empty
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
 * by @weak_ref, or %NULL if it was empty
 *
 * Returns: (transfer full) (type GObject.Object): the object pointed to
 * Since: 2.32
 */


/**
 * g_weak_ref_init: (skip)
 * @weak_ref: (inout): uninitialized or empty location for a weak reference
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


/**
 * gchararray:
 *
 * A C representable type name for #G_TYPE_STRING.
 */


/**
 * gunichar:
 *
 * A type which can hold any UTF-32 or UCS-4 character code,
 * also known as a Unicode code point.
 *
 * If you want to produce the UTF-8 representation of a #gunichar,
 * use g_ucs4_to_utf8(). See also g_utf8_to_ucs4() for the reverse
 * process.
 *
 * To print/scan values of this type as integer, use
 * %G_GINT32_MODIFIER and/or %G_GUINT32_FORMAT.
 *
 * The notation to express a Unicode code point in running text is
 * as a hexadecimal number with four to six digits and uppercase
 * letters, prefixed by the string "U+". Leading zeros are omitted,
 * unless the code point would have fewer than four hexadecimal digits.
 * For example, "U+0041 LATIN CAPITAL LETTER A". To print a code point
 * in the U+-notation, use the format string "U+\%04"G_GINT32_FORMAT"X".
 * To scan, use the format string "U+\%06"G_GINT32_FORMAT"X".
 *
 * |[
 * gunichar c;
 * sscanf ("U+0041", "U+%06"G_GINT32_FORMAT"X", &amp;c)
 * g_print ("Read U+%04"G_GINT32_FORMAT"X", c);
 * ]|
 */


/**
 * gunichar2:
 *
 * A type which can hold any UTF-16 code
 * point<footnote id="utf16_surrogate_pairs">UTF-16 also has so called
 * <firstterm>surrogate pairs</firstterm> to encode characters beyond
 * the BMP as pairs of 16bit numbers. Surrogate pairs cannot be stored
 * in a single gunichar2 field, but all GLib functions accepting gunichar2
 * arrays will correctly interpret surrogate pairs.</footnote>.
 *
 * To print/scan values of this type to/from text you need to convert
 * to/from UTF-8, using g_utf16_to_utf8()/g_utf8_to_utf16().
 *
 * To print/scan values of this type as integer, use
 * %G_GINT16_MODIFIER and/or %G_GUINT16_FORMAT.
 */



/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/
