
#include <gitesttypes.h>
#include <string.h>

/* basic types */
gboolean test_boolean (gboolean in)
{
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


/* time_t? */
GType test_gtype (GType in)
{
  return in;
}

#if 0
/************************************************************************/
/* utf8 */
/* insert BLACK HEART SUIT to ensure UTF-8 doesn't get mangled */
static const char utf8_const[]    = "const \xe2\x99\xa5 utf8";
static const char utf8_nonconst[] = "nonconst \xe2\x99\xa5 utf8";

/** test_utf8_const_return:
 * Return value: <const char*> UTF-8 string
 */
G_CONST_RETURN char *test_utf8_const_return (void)
{
  return utf8_const;
}

/** test_utf8_nonconst_return:
 * Return value: <char*> UTF-8 string
 */
char *test_utf8_nonconst_return (void)
{
  return g_strdup (utf8_nonconst);
}

void test_utf8_nonconst_in (char *in)
{
  g_assert (strcmp (in, utf8_nonconst) == 0);
}

void test_utf8_const_in (const char *in)
{
  g_assert (strcmp (in, utf8_const) == 0);
}

void test_utf8_out (char **out)
{
  *out = g_strdup (utf8_nonconst);
}

void test_utf8_inout (char **inout)
{
  g_assert (strcmp (*inout, utf8_const) == 0);
  *input = g_strdup (utf8_nonconst);
}
#endif

/* filename? */
/* non-basic-types */

static const char *test_sequence[] = {"1", "2", "3"};

/* array */
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

char **
test_strv_out (void)
{
  char **ret = g_new (char *, 4);
  ret[0] = "1";
  ret[1] = "2";
  ret[2] = "3";
  ret[3] = NULL;
  return ret;
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

void test_glist_free (GList *in)
{
  g_list_foreach (in, (GFunc)g_free, NULL);
  g_list_free (in);
}

/* free=none */
G_CONST_RETURN GList *test_glist_nothing_return (void)
{
  return test_sequence_list ();
}

/* free=none */
GList *test_glist_nothing_return2 (void)
{
  return test_sequence_list ();
}

/* free=g_list_free */
GList *test_glist_container_return (void)
{
  return g_list_copy (test_sequence_list ());
}

/* free=test_glist_free */
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

  for (i = 0, l = in; l != NULL; ++i, l = l->next)
      g_assert (strcmp (in->data, test_sequence[i]) == 0);
}

void test_glist_nothing_in (const GList *in)
{
  assert_test_sequence_list (in);
}

void test_glist_nothing_in2 (GList *in)
{
  assert_test_sequence_list (in);
}

void test_glist_container_in (GList *in)
{
  assert_test_sequence_list (in);
  g_list_free (in);
}

void test_glist_everything_in (GList *in)
{
  assert_test_sequence_list (in);
  test_glist_free (in);
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

void test_gslist_free (GSList *in)
{
  g_slist_foreach (in, (GFunc)g_free, NULL);
  g_slist_free (in);
}

/* free=none */
G_CONST_RETURN GSList *test_gslist_nothing_return (void)
{
  return test_sequence_slist ();
}

/* free=none */
GSList *test_gslist_nothing_return2 (void)
{
  return test_sequence_slist ();
}

/* free=g_slist_free */
GSList *test_gslist_container_return (void)
{
  return g_slist_copy (test_sequence_slist ());
}

/* free=test_gslist_free */
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

  for (i = 0, l = in; l != NULL; ++i, l = l->next)
      g_assert (strcmp (in->data, test_sequence[i]) == 0);
}

void test_gslist_nothing_in (const GSList *in)
{
  assert_test_sequence_slist (in);
}

void test_gslist_nothing_in2 (GSList *in)
{
  assert_test_sequence_slist (in);
}

void test_gslist_container_in (GSList *in)
{
  assert_test_sequence_slist (in);
  g_slist_free (in);
}

void test_gslist_everything_in (GSList *in)
{
  assert_test_sequence_slist (in);
  test_gslist_free (in);
}

/* ghash? */
/* error? */
