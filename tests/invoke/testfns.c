#include <glib.h>

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
  g_printf (blurb);
}

void test5 (gchar **blurb, gint *len)
{
  *blurb = g_strdup ("hey there");
  *len = strlen (*blurb);
}
