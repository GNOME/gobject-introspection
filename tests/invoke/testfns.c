#include <string.h>

#include <glib.h>
#include <glib/gprintf.h>

typedef struct {
    int foo;
} TestStruct;

gint test1 (gint in);
void test2 (gint in, gint *out);
void test3 (gint *inout);
void test4 (const gchar *blurb);
void test5 (gchar **blurb, gint *len);
gint test6 (GList *list);
char *test7 (GList *list);
TestStruct * test8 (int foo);
void test9 (TestStruct *test_struct, int *out);

gint test1 (gint in)
{
  return in + 4;
}

void test2 (gint in, gint *out)
{
  *out = in + 4;
}

void test3 (gint *inout)
{
  *inout = *inout + 4;
}

void test4 (const gchar *blurb)
{
  g_printf ("%s", blurb);
}

void test5 (gchar **blurb, gint *len)
{
  *blurb = g_strdup ("hey there");
  *len = strlen (*blurb);
}

gint test6 (GList *list)
{
  return g_list_length(list);
}

char *test7 (GList *list)
{
  GList *lp;
  GString *string = g_string_new("");

  for (lp=list; lp ; lp=lp->next)
    {
      g_string_append(string, (const char *)lp->data);
    }
  return g_string_free (string, FALSE);
}

/* constructor */
TestStruct * test8 (int foo)
{
  TestStruct *ret;

  ret = g_new(TestStruct, 1);
  ret->foo = foo;
  return ret;
}

void test9 (TestStruct *test_struct, int *out)
{
  *out = test_struct->foo;
}
