#ifndef __GITESTTYPES_H__
#define __GITESTTYPES_H__

#include <glib-object.h>

/* basic types */
gboolean test_boolean (gboolean in);
gint8 test_int8 (gint8 in);
guint8 test_uint8 (guint8 in);
gint16 test_int16 (gint16 in);
guint16 test_uint16 (guint16 in);
gint32 test_int32 (gint32 in);
guint32 test_uint32 (guint32 in);
gint64 test_int64 (gint64 in);
guint64 test_uint64 (guint64 in);
gint test_int (gint in);
guint test_uint (guint in);
glong test_long (glong in);
gulong test_ulong (gulong in);
gssize test_ssize (gssize in);
gsize test_size (gsize in);
gfloat test_float (gfloat in);
gdouble test_double (gdouble in);
/* time_t? */
GType test_gtype (GType in);
#if 0
/* utf8 */
G_CONST_RETURN char *test_utf8_const_return (void);
char *test_utf8_nonconst_return (void);
void test_utf8_nonconst_in (char *in);
void test_utf8_const_in (const char *in);
void test_utf8_out (char **out);
void test_utf8_inout (char **inout);
#endif
/* filename? */
/* non-basic-types */
/* array */
gboolean test_strv_in (char **arr);
char **test_strv_out (void);
/* interface */
/* GList */
G_CONST_RETURN GList *test_glist_nothing_return (void);
GList *test_glist_nothing_return2 (void);
GList *test_glist_container_return (void);
GList *test_glist_everything_return (void);
void test_glist_nothing_in (const GList *in);
void test_glist_nothing_in2 (GList *in);
void test_glist_container_in (GList *in);
void test_glist_everything_in (GList *in);
void test_glist_free (GList *in);

/* GSList */
G_CONST_RETURN GSList *test_gslist_nothing_return (void);
GSList *test_gslist_nothing_return2 (void);
GSList *test_gslist_container_return (void);
GSList *test_gslist_everything_return (void);
void test_gslist_nothing_in (const GSList *in);
void test_gslist_nothing_in2 (GSList *in);
void test_gslist_container_in (GSList *in);
void test_gslist_everything_in (GSList *in);
void test_gslist_free (GSList *in);

/* ghash? */
/* error? */

#endif /* __GITESTTYPES_H__ */
