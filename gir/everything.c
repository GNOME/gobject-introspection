#include <string.h>
#include <stdlib.h>
#include "everything.h"

static gboolean abort_on_error = TRUE;

#define ASSERT_VALUE(condition)  \
  if (abort_on_error)             \
    g_assert (condition);         \
  else                            \
    g_warn_if_fail (condition);   \

void set_abort_on_error (gboolean in)
{
  abort_on_error = in;
}

/* basic types */
gboolean test_boolean (gboolean in)
{
  return in;
}

gboolean test_boolean_true (gboolean in)
{
  ASSERT_VALUE (in == TRUE);
  return in;
}

gboolean test_boolean_false (gboolean in)
{
  ASSERT_VALUE (in == FALSE);
  return in;
}

gint8 test_int8 (gint8 in)
{
  return in;
}

guint8 test_uint8 (guint8 in)
{
  return in;
}

gint16 test_int16 (gint16 in)
{
  return in;
}

guint16 test_uint16 (guint16 in)
{
  return in;
}

gint32 test_int32 (gint32 in)
{
  return in;
}

guint32 test_uint32 (guint32 in)
{
  return in;
}

gint64 test_int64 (gint64 in)
{
  return in;
}

guint64 test_uint64 (guint64 in)
{
  return in;
}

gshort test_short (gshort in)
{
  return in;
}

gushort test_ushort (gushort in)
{
  return in;
}

gint test_int (gint in)
{
  return in;
}

guint test_uint (guint in)
{
  return in;
}

glong test_long (glong in)
{
  return in;
}

gulong test_ulong (gulong in)
{
  return in;
}

gssize test_ssize (gssize in)
{
  return in;
}

gsize test_size (gsize in)
{
  return in;
}

gfloat test_float (gfloat in)
{
  return in;
}

gdouble test_double (gdouble in)
{
  return in;
}


time_t test_timet (time_t in)
{
  return in;
}

GType test_gtype (GType in)
{
  return in;
}

int test_closure (GClosure *closure)
{
  GValue return_value = {0, };
  int ret;

  g_value_init (&return_value, G_TYPE_INT);

  g_closure_invoke (closure,
                    &return_value,
                    0, NULL,
                    NULL);

  ret = g_value_get_int (&return_value);

  g_value_unset(&return_value);

  return ret;
}

int test_closure_one_arg (GClosure *closure, int arg)
{
  GValue return_value = {0, };
  GValue arguments[1];
  int ret;

  g_value_init (&return_value, G_TYPE_INT);

  memset (&arguments[0], 0, sizeof (arguments));
  g_value_init (&arguments[0], G_TYPE_INT);
  g_value_set_int (&arguments[0], arg);

  g_closure_invoke (closure,
                    &return_value,
                    1, arguments,
                    NULL);

  ret = g_value_get_int (&return_value);

  g_value_unset(&return_value);
  g_value_unset(&arguments[0]);

  return ret;
}

/**
 * test_value_arg:
 * @v: (transfer none): a GValue expected to contain an int
 *
 * Return value: the int contained in the GValue.
 */
int test_int_value_arg(const GValue *v) {
  int i;

  i = g_value_get_int (v);

  return i;
}

static GValue value;
/**
 * test_value_return:
 * @i: an int
 *
 * Return value: (transfer none): the int wrapped in a GValue.
 */
const GValue *test_value_return(int i) {
  memset(&value, '\0', sizeof(GValue));

  g_value_init (&value, G_TYPE_INT);
  g_value_set_int (&value, i);

  return &value;
}

/************************************************************************/
/* foreign structs */

/**
 * test_cairo_context_full_return:
 * Returns: (transfer full):
 */
cairo_t *
test_cairo_context_full_return (void)
{
  cairo_surface_t *surface;
  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 10, 10);
  return cairo_create (surface);
}

/**
 * test_cairo_context_none_in:
 * @context: (transfer none):
 */
void
test_cairo_context_none_in (cairo_t *context)
{
  cairo_surface_t *surface = cairo_get_target (context);

  g_assert (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_ARGB32);
  g_assert (cairo_image_surface_get_width (surface) == 10);
  g_assert (cairo_image_surface_get_height (surface) == 10);
}


/**
 * test_cairo_surface_none_return:
 * Returns: (transfer none):
 */
cairo_surface_t *
test_cairo_surface_none_return (void)
{
  static cairo_surface_t *surface;

  if (surface == NULL) {
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 10, 10);
  }

  return surface;
}

/**
 * test_cairo_surface_full_return:
 * Returns: (transfer full):
 */
cairo_surface_t *
test_cairo_surface_full_return (void)
{
  return cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 10, 10);
}

/**
 * test_cairo_surface_none_in:
 * @surface: (transfer none):
 */
void
test_cairo_surface_none_in (cairo_surface_t *surface)
{
  g_assert (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_ARGB32);
  g_assert (cairo_image_surface_get_width (surface) == 10);
  g_assert (cairo_image_surface_get_height (surface) == 10);
}

/**
 * test_cairo_surface_full_out:
 * @surface: (out) (transfer full):
 */
void
test_cairo_surface_full_out (cairo_surface_t **surface)
{
  *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 10, 10);
}


/************************************************************************/
/* utf8 */
/* insert BLACK HEART SUIT to ensure UTF-8 doesn't get mangled */
static const char utf8_const[]    = "const \xe2\x99\xa5 utf8";
static const char utf8_nonconst[] = "nonconst \xe2\x99\xa5 utf8";

/**
 * test_utf8_const_return:
 * Return value: <const char*> UTF-8 string
 */
G_CONST_RETURN char *test_utf8_const_return (void)
{
  /* transfer mode none */
  return utf8_const;
}

/**
 * test_utf8_nonconst_return:
 * Return value: <char*> UTF-8 string
 */
char *test_utf8_nonconst_return (void)
{
  /* transfer mode full */
  return g_strdup (utf8_nonconst);
}

void test_utf8_nonconst_in (char *in)
{
  /* transfer mode full */
  g_assert (strcmp (in, utf8_nonconst) == 0);
  g_free(in);
}

void test_utf8_const_in (const char *in)
{
  /* transfer mode none */
  g_assert (strcmp (in, utf8_const) == 0);
}

/**
 * test_utf8_out:
 * @out: (out) (transfer full):
 */
void test_utf8_out (char **out)
{
  /* out parameter, transfer mode full */
  *out = g_strdup (utf8_nonconst);
}

/**
 * test_utf8_inout:
 * @inout: (inout):
 */
void test_utf8_inout (char **inout)
{
  /* inout parameter, transfer mode full */
  g_assert (strcmp (*inout, utf8_const) == 0);
  g_free(*inout);
  *inout = g_strdup (utf8_nonconst);
}

/**
 * test_filename_return:
 *
 * Return value: (element-type filename) (transfer full): list of strings
 */
GSList *test_filename_return (void)
{
  GSList *filenames = NULL;
  filenames = g_slist_prepend (filenames, g_filename_from_utf8("/etc/fstab", -1, NULL, NULL, NULL));
  filenames = g_slist_prepend (filenames, g_filename_from_utf8("åäö", -1, NULL, NULL, NULL));
  return filenames;
}

/* in arguments after out arguments */

/**
 * test_int_out_utf8:
 * @out: (out):
 * @in:
 */
void
test_int_out_utf8 (int *length, const char *in)
{
    *length = g_utf8_strlen(in, -1);
}


/* multiple output arguments */

/**
 * test_multi_double_args:
 * @in:
 * @one: (out): 
 * @two: (out): 
 */
void
test_multi_double_args (gdouble in, gdouble *one, gdouble *two)
{
  *one = in * 2;
  *two = in * 3;
}

/**
 * test_utf8_out_out:
 * @out0: (out) (transfer full): a copy of "first"
 * @out1: (out) (transfer full): a copy of "second"
 */
void
test_utf8_out_out (char **out0, char **out1)
{
  *out0 = g_strdup ("first");
  *out1 = g_strdup ("second");
}

/**
 * test_utf8_out_nonconst_return:
 * @out: (out) (transfer full): a copy of "second"
 *
 * Returns: (transfer full): a copy of "first"
 */
char *
test_utf8_out_nonconst_return (char **out)
{
  *out = g_strdup ("second");
  return g_strdup ("first");
}

/**
 * test_utf8_null_in:
 * @in: (allow-none):
 */
void test_utf8_null_in (char *in)
{
  g_assert (in == NULL);
}

/**
 * test_utf8_null_out:
 * @char_out: (allow-none) (out):
 */
void test_utf8_null_out (char **char_out)
{
  *char_out = NULL;
}


/* non-basic-types */

static const char *test_sequence[] = {"1", "2", "3"};

/* array */

/**
 * test_array_int_in:
 * @n_ints:
 * @ints: (array length=n_ints): List of ints
 */
int
test_array_int_in (int n_ints, int *ints)
{
  int i, sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_array_int_out:
 * @n_ints: (out): the length of @ints
 * @ints: (out) (array length=n_ints) (transfer full): a list of 5 integers, from 0 to 4 in consecutive order
 */
void
test_array_int_out (int *n_ints, int **ints)
{
  int i;
  *n_ints = 5;
  *ints = g_malloc0(sizeof(**ints) * *n_ints);
  for (i = 1; i < *n_ints; i++)
    (*ints)[i] = (*ints)[i-1] + 1;
}

/**
 * test_array_int_inout:
 * @n_ints: (inout): the length of @ints
 * @ints: (inout) (array length=n_ints) (transfer full): a list of integers whose items will be increased by 1, except the first that will be dropped
 */
void
test_array_int_inout (int *n_ints, int **ints)
{
  int i;

  for (i = 1; i < *n_ints; i++) {
	(*ints)[i-1] = (*ints)[i] + 1;
  }

  if (0 < *n_ints) {
    *n_ints -= 1;
  }
  *ints = g_realloc(*ints, sizeof(**ints) * *n_ints);
}

/**
 * test_array_gint8_in:
 * @n_ints:
 * @ints: (array length=n_ints): List of ints
 */
int
test_array_gint8_in (int n_ints, gint8 *ints)
{
  int i, sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_array_gint16_in:
 * @n_ints:
 * @ints: (array length=n_ints): List of ints
 */
int
test_array_gint16_in (int n_ints, gint16 *ints)
{
  int i, sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_array_gint32_in:
 * @n_ints:
 * @ints: (array length=n_ints): List of ints
 */
gint32
test_array_gint32_in (int n_ints, gint32 *ints)
{
  int i;
  gint32 sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_array_gint64_in:
 * @n_ints:
 * @ints: (array length=n_ints): List of ints
 */
gint64
test_array_gint64_in (int n_ints, gint64 *ints)
{
  int i;
  gint64 sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_strv_in:
 * @arr: (array zero-terminated=1) (transfer none):
 */
gboolean
test_strv_in (char **arr)
{
  if (g_strv_length (arr) != 3)
    return FALSE;
  if (strcmp (arr[0], "1") != 0)
    return FALSE;
  if (strcmp (arr[1], "2") != 0)
    return FALSE;
  if (strcmp (arr[2], "3") != 0)
    return FALSE;
  return TRUE;
}

/**
 * test_strv_in_container:
 * @arr: (array zero-terminated=1) (transfer container):
 */
gboolean
test_strv_in_container (char **arr)
{
  gboolean result = test_strv_in (arr);
  g_free (arr);
  return result;
}

/**
 * test_array_gtype_in:
 * @n_types:
 * @types: (array length=n_types): List of types
 * Return value: string representation of provided types
 * */
char *
test_array_gtype_in (int n_types, GType *types)
{
  GString *string;
  int i;

  string = g_string_new ("[");
  for (i = 0; i < n_types; i++)
    {
      g_string_append (string, g_type_name (types[i]));
      g_string_append_c (string, ',');
    }
  g_string_append_c (string, ']');
  return g_string_free (string, FALSE);
}

/**
 * test_strv_out:
 *
 * No annotations here.  We want the default to Do The Right Thing.
 */
char **
test_strv_out (void)
{
  int i = 0;
  int n = 6;
  char **ret = g_new (char *, n);
  ret[i++] = g_strdup ("thanks");
  ret[i++] = g_strdup ("for");
  ret[i++] = g_strdup ("all");
  ret[i++] = g_strdup ("the");
  ret[i++] = g_strdup ("fish");
  ret[i++] = NULL;
  g_assert (i == n);
  return ret;
}

/**
 * test_strv_out_container:
 *
 * Return value: (array zero-terminated=1) (transfer container):
 */
char **
test_strv_out_container (void)
{
  char **ret = g_new (char *, 4);
  ret[0] = "1";
  ret[1] = "2";
  ret[2] = "3";
  ret[3] = NULL;
  return ret;
}

/**
 * test_strv_outarg:
 * @retp: (array zero-terminated=1) (out) (transfer container):
 */
void
test_strv_outarg (char ***retp)
{
  char **ret = g_new (char *, 4);
  ret[0] = "1";
  ret[1] = "2";
  ret[2] = "3";
  ret[3] = NULL;
  *retp = ret;
}

/**
 * test_array_fixed_size_int_in:
 * @ints: (array fixed-size=5): a list of 5 integers
 *
 * Returns: the sum of the items in @ints
 */
int
test_array_fixed_size_int_in (int *ints)
{
  int i, sum = 0;
  for (i = 0; i < 5; i++)
    sum += ints[i];
  return sum;
}

/**
 * test_array_fixed_size_int_out:
 * @ints: (out) (array fixed-size=5) (transfer full): a list of 5 integers ranging from 0 to 4
 */
void
test_array_fixed_size_int_out (int **ints)
{
  int i;
  *ints = g_malloc0(sizeof(**ints) * 5);
  for (i = 1; i < 5; i++)
    (*ints)[i] = (*ints)[i-1] + 1;
}

/**
 * test_array_fixed_size_int_return:
 * Returns: (array fixed-size=5) (transfer full): a list of 5 integers ranging from 0 to 4
 */
int *
test_array_fixed_size_int_return (void)
{
  int i, *ints;
  ints = g_malloc0(sizeof(*ints) * 5);
  for (i = 1; i < 5; i++)
    ints[i] = ints[i-1] + 1;
  return ints;
}

/**
 * test_array_int_in_take:
 * @n_ints:
 * @ints: (array length=n_ints) (transfer full): List of ints
 */
int test_array_int_in_take (int n_ints, int *ints)
{
  int i, sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  g_free (ints);
  return sum;
}

/**
 * test_strv_out_c:
 *
 * No annotations here.  We want the default to Do The Right Thing.
 */
const char * const*
test_strv_out_c (void)
{
  static char **ret = NULL;

  if (ret == NULL)
    ret = test_strv_out ();

  return (const char * const *) ret;
}

/**
 * test_array_int_full_out:
 * @len: length of the returned array.
 * Returns: (array length=len) (transfer full): a new array of integers.
 */
int *
test_array_int_full_out(int *len) {
  int *result, i;
  *len = 5;
  result = g_malloc0(sizeof(*result) * (*len));
  for (i=1; i < (*len); i++)
    result[i] = result[i-1] + 1;
  return result;
}

/**
 * test_array_int_none_out:
 * @len: length of the returned array.
 * Returns: (array length=len) (transfer none): a static array of integers.
 */
int *
test_array_int_none_out(int *len) {
  static int result[5] = { 1, 2, 3, 4, 5 };
  *len = 5;
  return result;
}

/**
 * test_array_int_null_in:
 * @arr: (array length=len) (allow-none):
 * @len: length
 */
void test_array_int_null_in (int *arr, int len)
{
  g_assert (arr == NULL);
}

/**
 * test_array_int_null_out:
 * @arr: (out) (array length=len) (allow-none):
 * @len: (out) : length
 */
void test_array_int_null_out (int **arr, int *len)
{
  *arr = NULL;
  *len = 0;
}

/* interface */

/************************************************************************/
/* GList */

static /*const*/ GList *test_sequence_list()
{
    static GList *list = NULL;
    if (!list) {
        gsize i;
        for (i = 0; i < G_N_ELEMENTS(test_sequence); ++i) {
            list = g_list_prepend (list, (gpointer)test_sequence[i]);
        }
        list = g_list_reverse (list);
    }
    return list;
}

/**
 * test_glist_free:
 * @in: (element-type utf8) (transfer full):
 */
void test_glist_free (GList *in)
{
  g_list_foreach (in, (GFunc)g_free, NULL);
  g_list_free (in);
}

/**
 * test_glist_nothing_return:
 *
 * Return value: (element-type utf8) (transfer none):
 */
G_CONST_RETURN GList *test_glist_nothing_return (void)
{
  return test_sequence_list ();
}

/**
 * test_glist_nothing_return2:
 *
 * Return value: (element-type utf8) (transfer none):
 */
GList *test_glist_nothing_return2 (void)
{
  return test_sequence_list ();
}

/**
 * test_glist_container_return:
 *
 * Return value: (element-type utf8) (transfer container):
 */
GList *test_glist_container_return (void)
{
  return g_list_copy (test_sequence_list ());
}

/**
 * test_glist_everything_return:
 *
 * Return value: (element-type utf8) (transfer full):
 */
GList *test_glist_everything_return (void)
{
  GList *list;
  GList *l;

  list = g_list_copy (test_sequence_list ());
  for (l = list; l != NULL; l = l->next)
      l->data = g_strdup (l->data);
  return list;
}

static void assert_test_sequence_list (const GList *in)
{
  const GList *l;
  gsize i;

  for (i = 0, l = in; l != NULL; ++i, l = l->next) {
      g_assert (i < G_N_ELEMENTS(test_sequence));
      g_assert (strcmp (l->data, test_sequence[i]) == 0);
  }
  g_assert (i == G_N_ELEMENTS(test_sequence));
}

/**
 * test_glist_nothing_in:
 * @in: (element-type utf8):
 */
void test_glist_nothing_in (const GList *in)
{
  assert_test_sequence_list (in);
}

/**
 * test_glist_nothing_in2:
 * @in: (element-type utf8):
 */
void test_glist_nothing_in2 (GList *in)
{
  assert_test_sequence_list (in);
}

/**
 * test_glist_container_in:
 * @in: (element-type utf8) (transfer container):
 */
void test_glist_container_in (GList *in)
{
  assert_test_sequence_list (in);
  g_list_free (in);
}

/**
 * test_glist_everything_in:
 * @in: (element-type utf8) (transfer full):
 */
void test_glist_everything_in (GList *in)
{
  assert_test_sequence_list (in);
  test_glist_free (in);
}

/**
 * test_glist_null_in:
 * @in: (element-type utf8) (allow-none):
 */
void test_glist_null_in (GSList *in)
{
  g_assert (in == NULL);
}

/**
 * test_glist_null_out:
 * @out_list: (out) (element-type utf8) (allow-none):
 */
void test_glist_null_out (GSList **out_list)
{
  *out_list = NULL;
}


/************************************************************************/
/* GSList */

static /*const*/ GSList *test_sequence_slist()
{
    static GSList *list = NULL;
    if (!list) {
        gsize i;
        for (i = 0; i < G_N_ELEMENTS(test_sequence); ++i) {
            list = g_slist_prepend (list, (gpointer)test_sequence[i]);
        }
        list = g_slist_reverse (list);
    }
    return list;
}

/**
 * test_gslist_free:
 * @in: (element-type utf8) (transfer full):
 */
void test_gslist_free (GSList *in)
{
  g_slist_foreach (in, (GFunc)g_free, NULL);
  g_slist_free (in);
}

/**
 * test_gslist_nothing_return:
 *
 * Return value: (element-type utf8) (transfer none):
 */
G_CONST_RETURN GSList *test_gslist_nothing_return (void)
{
  return test_sequence_slist ();
}

/**
 * test_gslist_nothing_return2:
 *
 * Return value: (element-type utf8) (transfer none):
 */
GSList *test_gslist_nothing_return2 (void)
{
  return test_sequence_slist ();
}

/**
 * test_gslist_container_return:
 *
 * Return value: (element-type utf8) (transfer container):
 */
GSList *test_gslist_container_return (void)
{
  return g_slist_copy (test_sequence_slist ());
}

/**
 * test_gslist_everything_return:
 *
 * Return value: (element-type utf8) (transfer full):
 */
GSList *test_gslist_everything_return (void)
{
  GSList *list;
  GSList *l;

  list = g_slist_copy (test_sequence_slist ());
  for (l = list; l != NULL; l = l->next)
      l->data = g_strdup (l->data);
  return list;
}

static void assert_test_sequence_slist (const GSList *in)
{
  const GSList *l;
  gsize i;

  for (i = 0, l = in; l != NULL; ++i, l = l->next) {
      g_assert (i < G_N_ELEMENTS(test_sequence));
      g_assert (strcmp (l->data, test_sequence[i]) == 0);
  }
  g_assert (i == G_N_ELEMENTS(test_sequence));
}

/**
 * test_gslist_nothing_in:
 * @in: (element-type utf8):
 */
void test_gslist_nothing_in (const GSList *in)
{
  assert_test_sequence_slist (in);
}

/**
 * test_gslist_nothing_in2:
 * @in: (element-type utf8):
 */
void test_gslist_nothing_in2 (GSList *in)
{
  assert_test_sequence_slist (in);
}

/**
 * test_gslist_container_in:
 * @in: (element-type utf8) (transfer container):
 */
void test_gslist_container_in (GSList *in)
{
  assert_test_sequence_slist (in);
  g_slist_free (in);
}

/**
 * test_gslist_everything_in:
 * @in: (element-type utf8) (transfer full):
 */
void test_gslist_everything_in (GSList *in)
{
  assert_test_sequence_slist (in);
  test_gslist_free (in);
}

/**
 * test_gslist_null_in:
 * @in: (element-type utf8) (allow-none):
 */
void test_gslist_null_in (GSList *in)
{
  g_assert (in == NULL);
}

/**
 * test_gslist_null_out:
 * @out_list: (out) (element-type utf8) (allow-none):
 */
void test_gslist_null_out (GSList **out_list)
{
  *out_list = NULL;
}

/************************************************************************/
/* GHash */

static char *table_data[3][2] = {
  { "foo", "bar" }, { "baz", "bat" }, { "qux", "quux" }
};

static GHashTable *test_table_ghash_new_container()
{
  GHashTable *hash;
  int i;
  hash = g_hash_table_new(g_str_hash, g_str_equal);
  for (i=0; i<3; i++)
    g_hash_table_insert(hash, table_data[i][0], table_data[i][1]);
  return hash;
}

static GHashTable *test_table_ghash_new_full()
{
  GHashTable *hash;
  int i;
  hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  for (i=0; i<3; i++)
    g_hash_table_insert(hash,
                        g_strdup(table_data[i][0]),
                        g_strdup(table_data[i][1]));
  return hash;
}

static /*const*/ GHashTable *test_table_ghash_const()
{
  static GHashTable *hash = NULL;
  if (!hash) {
    hash = test_table_ghash_new_container();
  }
  return hash;
}

/**
 * test_ghash_free:
 * @in: (transfer full) (element-type utf8 utf8)
 */
void test_ghash_free (GHashTable *in)
{
  /* keys and values are deleted iff an appropriate element destroy function
   * was registered */
  g_hash_table_unref(in);
}

/**
 * test_ghash_null_return:
 *
 * Return value: (element-type utf8 utf8) (transfer none) (allow-none):
 */
G_CONST_RETURN GHashTable *test_ghash_null_return (void)
{
  return NULL;
}

/**
 * test_ghash_nothing_return:
 *
 * Return value: (element-type utf8 utf8) (transfer none):
 */
G_CONST_RETURN GHashTable *test_ghash_nothing_return (void)
{
  return test_table_ghash_const ();
}

/**
 * test_ghash_nothing_return2:
 *
 * Return value: (element-type utf8 utf8) (transfer none):
 */
GHashTable *test_ghash_nothing_return2 (void)
{
  return test_table_ghash_const ();
}

/**
 * test_ghash_container_return:
 *
 * Return value: (element-type utf8 utf8) (transfer container):
 */
GHashTable *test_ghash_container_return (void)
{
  return test_table_ghash_new_container ();
}

/**
 * test_ghash_everything_return:
 *
 * Return value: (element-type utf8 utf8) (transfer full):
 */
GHashTable *test_ghash_everything_return (void)
{
  return test_table_ghash_new_full ();
}

static void assert_test_table_ghash (const GHashTable *in)
{
  GHashTable *h = test_table_ghash_const();
  GHashTableIter iter;
  gpointer key, value;

  g_assert(g_hash_table_size(h) ==
           g_hash_table_size((GHashTable*)in));

  g_hash_table_iter_init(&iter, (GHashTable*)in);
  while (g_hash_table_iter_next (&iter, &key, &value))
    g_assert( strcmp(g_hash_table_lookup(h, (char*)key), (char*)value) == 0);
}

/**
 * test_ghash_null_in:
 * @in: (element-type utf8 utf8) (allow-none):
 */
void test_ghash_null_in (const GHashTable *in)
{
  g_assert (in == NULL);
}

/**
 * test_ghash_null_out:
 * @out: (element-type utf8 utf8) (allow-none) (out):
 */
void test_ghash_null_out (const GHashTable **out)
{
  *out = NULL;
}

/**
 * test_ghash_nothing_in:
 * @in: (element-type utf8 utf8):
 */
void test_ghash_nothing_in (const GHashTable *in)
{
  assert_test_table_ghash (in);
}

/**
 * test_ghash_nothing_in2:
 * @in: (element-type utf8 utf8):
 */
void test_ghash_nothing_in2 (GHashTable *in)
{
  assert_test_table_ghash (in);
}

/**
 * test_ghash_container_in:
 * @in: (transfer container) (element-type utf8 utf8):
 */
void test_ghash_container_in (GHashTable *in)
{
  assert_test_table_ghash (in);
  /* be careful and explicitly steal all the elements from the ghash before
   * freeing it. */
  g_hash_table_steal_all (in);
  g_hash_table_destroy (in);
}

static gboolean ghash_freer(gpointer key, gpointer value, gpointer user_data) {
  g_free(key);
  g_free(value);
  return TRUE;
}

/**
 * test_ghash_everything_in:
 * @in: (transfer full) (element-type utf8 utf8):
 */
void test_ghash_everything_in (GHashTable *in)
{
  assert_test_table_ghash (in);
  /* free the elements, then free the container.  Don't rely on the
   * GHashTable's key/value destructor functions. */
  g_hash_table_foreach_steal (in, ghash_freer, NULL);
  /* okay, dealloc the hash table. */
  g_hash_table_destroy (in);
}

/* Nested collection types */

/**
 * test_ghash_nested_everything_return:
 * Specify nested parameterized types directly with the (type ) annotation.
 *
 * Return value: (type GLib.HashTable<utf8,GLib.HashTable<utf8,utf8>>) (transfer full):
 */
GHashTable *
test_ghash_nested_everything_return (void)
{
  GHashTable *hash;
  hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,
                               (void (*) (gpointer)) g_hash_table_destroy);
  g_hash_table_insert(hash, g_strdup("wibble"), test_table_ghash_new_full());
  return hash;
}

/**
 * test_ghash_nested_everything_return2:
 * Another way of specifying nested parameterized types: using the
 * element-type annotation.
 *
 * Return value: (element-type utf8 GLib.HashTable<utf8,utf8>) (transfer full):
 */
GHashTable *
test_ghash_nested_everything_return2 (void)
{
  return test_ghash_nested_everything_return();
}

/************************************************************************/

/* error? */

/* enums / flags */

GType
test_enum_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { TEST_VALUE1, "TEST_VALUE1", "value1" },
            { TEST_VALUE2, "TEST_VALUE2", "value2" },
            { TEST_VALUE3, "TEST_VALUE3", "value3" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("TestEnum"), values);
    }

    return etype;
}

GType
test_flags_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { TEST_FLAG1, "TEST_FLAG1", "flag1" },
            { TEST_FLAG2, "TEST_FLAG2", "flag2" },
            { TEST_FLAG3, "TEST_FLAG3", "flag3" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("TestFlags"), values);
    }

    return etype;
}

const gchar *
test_enum_param(TestEnum e)
{
  GEnumValue *ev;
  GEnumClass *ec;

  ec = g_type_class_ref (test_enum_get_type ());
  ev = g_enum_get_value (ec, e);
  g_type_class_unref (ec);

  return ev->value_nick;
}

/* structures */

/**
 * test_struct_a_clone:
 * @a: the structure
 * @a_out: (out caller-allocates): the cloned structure
 *
 * Make a copy of a TestStructA
 */
void
test_struct_a_clone (TestStructA *a,
		     TestStructA *a_out)
{
  *a_out = *a;
}

/**
 * test_struct_b_clone:
 * @b: the structure
 * @b_out: (out): the cloned structure
 *
 * Make a copy of a TestStructB
 */
void
test_struct_b_clone (TestStructB *b,
		     TestStructB *b_out)
{
  *b_out = *b;
}

/* plain-old-data boxed types */

TestSimpleBoxedA *
test_simple_boxed_a_copy (TestSimpleBoxedA *a)
{
  TestSimpleBoxedA *new_a = g_slice_new (TestSimpleBoxedA);

  *new_a = *a;

  return new_a;
}

static void
test_simple_boxed_a_free (TestSimpleBoxedA *a)
{
  g_slice_free (TestSimpleBoxedA, a);
}

GType
test_simple_boxed_a_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestSimpleBoxedA"),
					     (GBoxedCopyFunc)test_simple_boxed_a_copy,
					     (GBoxedFreeFunc)test_simple_boxed_a_free);
  return our_type;
}

TestSimpleBoxedB *
test_simple_boxed_b_copy (TestSimpleBoxedB *b)
{
  TestSimpleBoxedB *new_b = g_slice_new (TestSimpleBoxedB);

  *new_b = *b;

  return new_b;
}

gboolean
test_simple_boxed_a_equals (TestSimpleBoxedA *a,
			    TestSimpleBoxedA *other_a)
{
  return (a->some_int == other_a->some_int &&
	  a->some_int8 == other_a->some_int8 &&
	  a->some_double == other_a->some_double);
}

const TestSimpleBoxedA*
test_simple_boxed_a_const_return (void)
{
  static TestSimpleBoxedA simple_a = {
    5, 6, 7.0
  };

  return &simple_a;
}

static void
test_simple_boxed_b_free (TestSimpleBoxedB *a)
{
  g_slice_free (TestSimpleBoxedB, a);
}

GType
test_simple_boxed_b_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestSimpleBoxedB"),
					     (GBoxedCopyFunc)test_simple_boxed_b_copy,
					     (GBoxedFreeFunc)test_simple_boxed_b_free);
  return our_type;
}

/* opaque boxed */

struct _TestBoxedPrivate
{
  guint magic;
};

TestBoxed *
test_boxed_new (void)
{
  TestBoxed *boxed = g_slice_new0(TestBoxed);
  boxed->priv = g_slice_new0(TestBoxedPrivate);
  boxed->priv->magic = 0xdeadbeef;

  return boxed;
}

TestBoxed *
test_boxed_new_alternative_constructor1 (int i)
{
  TestBoxed *boxed = g_slice_new0(TestBoxed);
  boxed->priv = g_slice_new0(TestBoxedPrivate);
  boxed->priv->magic = 0xdeadbeef;
  boxed->some_int8 = i;

  return boxed;
}

TestBoxed *
test_boxed_new_alternative_constructor2 (int i, int j)
{
  TestBoxed *boxed = g_slice_new0(TestBoxed);
  boxed->priv = g_slice_new0(TestBoxedPrivate);
  boxed->priv->magic = 0xdeadbeef;
  boxed->some_int8 = i + j;

  return boxed;
}

TestBoxed *
test_boxed_new_alternative_constructor3 (char *s)
{
  TestBoxed *boxed = g_slice_new0(TestBoxed);
  boxed->priv = g_slice_new0(TestBoxedPrivate);
  boxed->priv->magic = 0xdeadbeef;
  boxed->some_int8 = atoi(s);

  return boxed;
}

TestBoxed *
test_boxed_copy (TestBoxed *boxed)
{
  TestBoxed *new_boxed = test_boxed_new();
  TestBoxedPrivate *save;

  save = new_boxed->priv;
  *new_boxed = *boxed;
  new_boxed->priv = save;

  return new_boxed;
}

gboolean
test_boxed_equals (TestBoxed *boxed,
		   TestBoxed *other)
{
  return (other->some_int8 == boxed->some_int8 &&
	  test_simple_boxed_a_equals(&other->nested_a, &boxed->nested_a));
}

static void
test_boxed_free (TestBoxed *boxed)
{
  g_assert (boxed->priv->magic == 0xdeadbeef);

  g_slice_free (TestBoxedPrivate, boxed->priv);
  g_slice_free (TestBoxed, boxed);
}

GType
test_boxed_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestBoxed"),
					     (GBoxedCopyFunc)test_boxed_copy,
					     (GBoxedFreeFunc)test_boxed_free);
  return our_type;
}

G_DEFINE_TYPE(TestObj, test_obj, G_TYPE_OBJECT);

enum
{
  PROP_TEST_OBJ_BARE = 1,
  PROP_TEST_OBJ_BOXED
};

static void
test_obj_set_property (GObject      *object,
                       guint         property_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  TestObj *self = TEST_OBJECT (object);

  switch (property_id)
    {
    case PROP_TEST_OBJ_BARE:
      test_obj_set_bare (self, g_value_get_object (value));
      break;

    case PROP_TEST_OBJ_BOXED:
      if (self->boxed)
        test_boxed_free (self->boxed);
      self->boxed = g_value_dup_boxed (value);
      break;
      
    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
test_obj_get_property (GObject    *object,
                        guint       property_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
  TestObj *self = TEST_OBJECT (object);

  switch (property_id)
    {
    case PROP_TEST_OBJ_BARE:
      g_value_set_object (value, self->bare);
      break;

    case PROP_TEST_OBJ_BOXED:
      g_value_set_boxed (value, self->boxed);
      break;
      
    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
test_obj_dispose (GObject *gobject)
{
  TestObj *self = TEST_OBJECT (gobject);

  if (self->bare)
    {
      g_object_unref (self->bare);

      self->bare = NULL;
    }

  if (self->boxed)
    {
      test_boxed_free (self->boxed);
      self->boxed = NULL;
    }
  
  /* Chain up to the parent class */
  G_OBJECT_CLASS (test_obj_parent_class)->dispose (gobject);
}

static int
test_obj_default_matrix (TestObj *obj, const char *somestr)
{
  return 42;
}

static void
test_obj_class_init (TestObjClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GParamSpec *pspec;
  GType param_types[1];

  klass->test_signal =
    g_signal_newv ("test",
                   G_TYPE_FROM_CLASS (gobject_class),
                   G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                   NULL /* closure */,
                   NULL /* accumulator */,
                   NULL /* accumulator data */,
                   g_cclosure_marshal_VOID__VOID,
                   G_TYPE_NONE /* return_type */,
                   0     /* n_params */,
                   NULL  /* param_types */);

  param_types[0] = test_simple_boxed_a_get_type() | G_SIGNAL_TYPE_STATIC_SCOPE;
  klass->test_signal_with_static_scope_arg =
    g_signal_newv ("test-with-static-scope-arg",
                   G_TYPE_FROM_CLASS (gobject_class),
                   G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                   NULL /* closure */,
                   NULL /* accumulator */,
                   NULL /* accumulator data */,
                   g_cclosure_marshal_VOID__BOXED,
                   G_TYPE_NONE /* return_type */,
                   1     /* n_params */,
                   param_types);

  gobject_class->set_property = test_obj_set_property;
  gobject_class->get_property = test_obj_get_property;
  gobject_class->dispose = test_obj_dispose;

  pspec = g_param_spec_object ("bare",
                               "Bare property",
                               "A contained object",
                               G_TYPE_OBJECT,
                               G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class,
                                   PROP_TEST_OBJ_BARE,
                                   pspec);

  pspec = g_param_spec_boxed ("boxed",
                              "Boxed property",
                              "A contained boxed struct",
                              TEST_TYPE_BOXED,
                              G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class,
                                   PROP_TEST_OBJ_BOXED,
                                   pspec);
  
  klass->matrix = test_obj_default_matrix;
}

static void
test_obj_init (TestObj *obj)
{
  obj->bare = NULL;
  obj->boxed = NULL;
}

TestObj *
test_obj_new_from_file (const char *x, GError **error)
{
  return g_object_new (TEST_TYPE_OBJ, NULL);
}

/**
 * test_obj_set_bare:
 * @bare: (allow-none):
 */
void
test_obj_set_bare (TestObj *obj, GObject *bare)
{
  if (obj->bare)
    g_object_unref (obj->bare);
  obj->bare = bare;
  if (obj->bare)
    g_object_ref (obj->bare);
}

int
test_obj_instance_method (TestObj *obj)
{
    return -1;
}

double
test_obj_static_method (int x)
{
  return x;
}

/**
 * test_obj_torture_signature_0:
 * @obj: A #TestObj
 * @x:
 * @y: (out):
 * @z: (out):
 * @foo:
 * @q: (out):
 * @m:
 *
 */
void
test_obj_torture_signature_0 (TestObj    *obj,
                              int         x,
                              double     *y,
                              int        *z,
                              const char *foo,
                              int        *q,
                              guint       m)
{
  *y = x;
  *z = x * 2;
  *q = g_utf8_strlen (foo, -1) + m;
}

/**
 * test_obj_torture_signature_1:
 * @obj: A #TestObj
 * @x:
 * @y: (out):
 * @z: (out):
 * @foo:
 * @q: (out):
 * @m:
 * @error: A #GError
 *
 * This function throws an error if m is odd.
 */
gboolean
test_obj_torture_signature_1 (TestObj   *obj,
                              int        x,
                              double     *y,
                              int        *z,
                              const char *foo,
                              int        *q,
                              guint       m,
                              GError    **error)
{
  *y = x;
  *z = x * 2;
  *q = g_utf8_strlen (foo, -1) + m;
  if (m % 2 == 0)
      return TRUE;
  g_set_error (error, G_IO_ERROR, G_IO_ERROR_FAILED, "m is odd");
  return FALSE;
}

/**
 * test_obj_do_matrix:
 * @obj: A #TestObj
 * @somestr: Meaningless string
 *
 * This method is virtual.  Notably its name differs from the virtual
 * slot name, which makes it useful for testing bindings handle this
 * case.
 *
 * Virtual: matrix
 */
int
test_obj_do_matrix (TestObj *obj, const char *somestr)
{
  return TEST_OBJ_GET_CLASS (obj)->matrix (obj, somestr);
}

/**
 * test_object_null_in:
 * @obj: (allow-none) A #TestObj
 */
void
test_object_null_in (TestObj *obj)
{
}

/**
 * test_object_null_out:
 * @obj: (allow-none) (out) A #TestObj
 */
void
test_object_null_out (TestObj **obj)
{
}

typedef struct _CallbackInfo CallbackInfo;

struct _CallbackInfo
{
  TestCallbackUserData callback;
  GDestroyNotify notify;
  gpointer user_data;
};


G_DEFINE_TYPE(TestSubObj, test_sub_obj, TEST_TYPE_OBJ);

static void
test_sub_obj_class_init (TestSubObjClass *klass)
{
}

static void
test_sub_obj_init (TestSubObj *obj)
{
}

TestSubObj*
test_sub_obj_new ()
{
  return g_object_new (TEST_TYPE_SUB_OBJ, NULL);
}

int
test_sub_obj_instance_method (TestSubObj *obj)
{
    return 0;
}

void
test_sub_obj_unset_bare (TestSubObj *obj)
{
  test_obj_set_bare(TEST_OBJECT(obj), NULL);
}


/**
 * test_callback:
 * @callback: (scope call) (allow-none):
 *
 **/
int
test_callback (TestCallback callback)
{
    if (callback != NULL)
        return callback();
    return 0;
}

/**
 * test_multi_callback:
 * @callback: (scope call) (allow-none):
 *
 **/
int
test_multi_callback (TestCallback callback)
{
    int sum = 0;
    if (callback != NULL) {
        sum += callback();
        sum += callback();
    }

    return sum;
}



/**
 * test_simple_callback:
 * @callback: (scope call) (allow-none):
 *
 **/
void
test_simple_callback (TestSimpleCallback callback)
{
    if (callback != NULL)
        callback();

    return;
}

/**
 * test_callback_user_data:
 * @callback: (scope call):
 *
 * Call - callback parameter persists for the duration of the method
 * call and can be released on return.
 **/
int
test_callback_user_data (TestCallbackUserData callback,
                         gpointer user_data)
{
  return callback(user_data);
}

static GSList *notified_callbacks = NULL;

/**
 * test_callback_destroy_notify:
 * @callback: (scope notified):
 *
 * Notified - callback persists until a DestroyNotify delegate
 * is invoked.
 **/
int
test_callback_destroy_notify (TestCallbackUserData callback,
                              gpointer user_data,
                              GDestroyNotify notify)
{
  int retval;
  CallbackInfo *info;

  retval = callback(user_data);

  info = g_slice_new(CallbackInfo);
  info->callback = callback;
  info->notify = notify;
  info->user_data = user_data;

  notified_callbacks = g_slist_prepend(notified_callbacks, info);

  return retval;
}

/**
 * test_callback_thaw_notifications:
 *
 * Invokes all callbacks installed by #test_callback_destroy_notify(),
 * adding up their return values, and removes them, invoking the
 * corresponding destroy notfications.
 *
 * Return value: Sum of the return values of the invoked callbacks.
 */
int
test_callback_thaw_notifications (void)
{
  int retval = 0;
  GSList *node;

  for (node = notified_callbacks; node != NULL; node = node->next)
    {
      CallbackInfo *info = node->data;
      retval += info->callback (info->user_data);
      if (info->notify)
        info->notify (info->user_data);
      g_slice_free (CallbackInfo, info);
    }

  g_slist_free (notified_callbacks);
  notified_callbacks = NULL;

  return retval;
}

static GSList *async_callbacks = NULL;

/**
 * test_callback_async:
 * @callback: (scope async):
 *
 **/
void
test_callback_async (TestCallbackUserData callback,
                     gpointer user_data)
{
  CallbackInfo *info;

  info = g_slice_new(CallbackInfo);
  info->callback = callback;
  info->user_data = user_data;

  async_callbacks = g_slist_prepend(async_callbacks, info);
}

/**
 * test_callback_thaw_async:
 */
int
test_callback_thaw_async (void)
{
  int retval = 0;
  GSList *node;

  for (node = async_callbacks; node != NULL; node = node->next)
    {
      CallbackInfo *info = node->data;
      retval = info->callback (info->user_data);
      g_slice_free (CallbackInfo, info);
    }

  g_slist_free (async_callbacks);
  async_callbacks = NULL;
  return retval;
}

void
test_async_ready_callback (GAsyncReadyCallback callback)
{
  GSimpleAsyncResult *result = g_simple_async_result_new (NULL, callback, NULL,
    test_async_ready_callback);
  g_simple_async_result_complete_in_idle (result);
}

/**
 * test_obj_instance_method_callback:
 * @callback: (scope call) (allow-none):
 *
 **/
void
test_obj_instance_method_callback (TestObj *obj, TestCallback callback)
{
    if (callback != NULL)
        callback();
}

/**
 * test_obj_static_method_callback:
 * @callback: (scope call) (allow-none):
 *
 **/
void
test_obj_static_method_callback (TestCallback callback)
{
    if (callback != NULL)
        callback();
}

/**
 * test_obj_new_callback:
 * @callback: (scope notified):
 *
 **/
TestObj *
test_obj_new_callback (TestCallbackUserData callback, gpointer user_data,
                       GDestroyNotify notify)
{
  CallbackInfo *info;

  callback(user_data);

  info = g_slice_new(CallbackInfo);
  info->callback = callback;
  info->notify = notify;
  info->user_data = user_data;

  notified_callbacks = g_slist_prepend(notified_callbacks, info);

  return g_object_new (TEST_TYPE_OBJ, NULL);
}

/* interface */

static void
test_interface_class_init(void *g_iface)
{
}

GType
test_interface_get_type(void)
{
    static GType type = 0;
    if (type == 0) {
        type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                              "EverythingTestInterface",
                                              sizeof (TestInterfaceIface),
                                              (GClassInitFunc) test_interface_class_init,
                                              0, NULL, 0);
    }

    return type;
}

/* gobject with non-standard prefix */
G_DEFINE_TYPE(TestWi8021x, test_wi_802_1x, G_TYPE_OBJECT);

enum
{
  PROP_TEST_WI_802_1X_TESTBOOL = 1
};

static void
test_wi_802_1x_set_property (GObject      *object,
                             guint         property_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
  TestWi8021x *self = TEST_WI_802_1X (object);

  switch (property_id)
    {
    case PROP_TEST_WI_802_1X_TESTBOOL:
      test_wi_802_1x_set_testbool (self, g_value_get_boolean (value));
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
test_wi_802_1x_get_property (GObject    *object,
                        guint       property_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
  TestWi8021x *self = TEST_WI_802_1X (object);

  switch (property_id)
    {
    case PROP_TEST_WI_802_1X_TESTBOOL:
      g_value_set_boolean (value, test_wi_802_1x_get_testbool (self));
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
test_wi_802_1x_dispose (GObject *gobject)
{
  /* Chain up to the parent class */
  G_OBJECT_CLASS (test_wi_802_1x_parent_class)->dispose (gobject);
}

static void
test_wi_802_1x_class_init (TestWi8021xClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GParamSpec *pspec;

  gobject_class->set_property = test_wi_802_1x_set_property;
  gobject_class->get_property = test_wi_802_1x_get_property;
  gobject_class->dispose = test_wi_802_1x_dispose;

  pspec = g_param_spec_boolean ("testbool",
                                "Nick for testbool",
                                "Blurb for testbool",
                                TRUE,
                                G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class,
                                   PROP_TEST_WI_802_1X_TESTBOOL,
                                   pspec);
}

static void
test_wi_802_1x_init (TestWi8021x *obj)
{
  obj->testbool = TRUE;
}

TestWi8021x *
test_wi_802_1x_new (void)
{
  return g_object_new (TEST_TYPE_WI_802_1X, NULL);
}

void
test_wi_802_1x_set_testbool (TestWi8021x *obj, gboolean val)
{
  obj->testbool = val;
}

gboolean
test_wi_802_1x_get_testbool (TestWi8021x *obj)
{
  return obj->testbool;
}

int
test_wi_802_1x_static_method (int x)
{
  return 2*x;
}

/* floating gobject */
G_DEFINE_TYPE(TestFloating, test_floating, G_TYPE_INITIALLY_UNOWNED);

static void
test_floating_finalize(GObject *object)
{
  g_assert(!g_object_is_floating (object));

  G_OBJECT_CLASS(test_floating_parent_class)->finalize(object);
}

static void
test_floating_class_init (TestFloatingClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = test_floating_finalize;
}

static void
test_floating_init (TestFloating *obj)
{
}

TestFloating *
test_floating_new (void)
{
  return g_object_new (TEST_TYPE_FLOATING, NULL);
}


/**
 * test_torture_signature_0:
 * @x:
 * @y: (out):
 * @z: (out):
 * @foo:
 * @q: (out):
 * @m:
 *
 */
void
test_torture_signature_0 (int         x,
                          double     *y,
                          int        *z,
                          const char *foo,
                          int        *q,
                          guint       m)
{
  *y = x;
  *z = x * 2;
  *q = g_utf8_strlen (foo, -1) + m;
}

/**
 * test_torture_signature_1:
 * @x:
 * @y: (out):
 * @z: (out):
 * @foo:
 * @q: (out):
 * @m:
 * @error: A #GError
 *
 * This function throws an error if m is odd.
 */
gboolean
test_torture_signature_1 (int         x,
                          double     *y,
                          int        *z,
                          const char *foo,
                          int        *q,
                          guint       m,
                          GError    **error)
{
  *y = x;
  *z = x * 2;
  *q = g_utf8_strlen (foo, -1) + m;
  if (m % 2 == 0)
      return TRUE;
  g_set_error (error, G_IO_ERROR, G_IO_ERROR_FAILED, "m is odd");
  return FALSE;
}

/**
 * test_torture_signature_2:
 * @x:
 * @callback:
 * @user_data:
 * @notify:
 * @y: (out):
 * @z: (out):
 * @foo:
 * @q: (out):
 * @m:
 *
 */
void
test_torture_signature_2 (int                   x,
                          TestCallbackUserData  callback,
                          gpointer              user_data,
                          GDestroyNotify        notify,
                          double               *y,
                          int                  *z,
                          const char           *foo,
                          int                  *q,
                          guint                 m)
{
  *y = x;
  *z = x * 2;
  *q = g_utf8_strlen (foo, -1) + m;  
  notify (user_data);
}

