/* -*- Mode: C; c-basic-offset: 4 -*-
 * vim: tabstop=4 shiftwidth=4 expandtab
 */

#include "gimarshallingtests.h"

#include <string.h>


/* Booleans */

gboolean
g_i_marshalling_tests_boolean_return_true (void)
{
    return TRUE;
}

gboolean
g_i_marshalling_tests_boolean_return_false (void)
{
    return FALSE;
}

void
g_i_marshalling_tests_boolean_in_true (gboolean bool_)
{
    g_assert (bool_ == TRUE);
}

void
g_i_marshalling_tests_boolean_in_false (gboolean bool_)
{
    g_assert (bool_ == FALSE);
}

/**
 * g_i_marshalling_tests_boolean_out_true:
 * bool_: (out):
 */
void
g_i_marshalling_tests_boolean_out_true (gboolean *bool_)
{
    *bool_ = TRUE;
}

/**
 * g_i_marshalling_tests_boolean_out_false:
 * bool_: (out):
 */
void
g_i_marshalling_tests_boolean_out_false (gboolean *bool_)
{
    *bool_ = FALSE;
}

/**
 * g_i_marshalling_tests_boolean_inout_true_false:
 * bool_: (inout):
 */
void
g_i_marshalling_tests_boolean_inout_true_false (gboolean *bool_)
{
    g_assert (*bool_ == TRUE);
    *bool_ = FALSE;
}

/**
 * g_i_marshalling_tests_boolean_inout_false_true:
 * bool_: (inout):
 */
void
g_i_marshalling_tests_boolean_inout_false_true (gboolean *bool_)
{
    g_assert (*bool_ == FALSE);
    *bool_ = TRUE;
}


/* Integers */

gint8
g_i_marshalling_tests_int8_return_max (void)
{
    return G_MAXINT8;
}

gint8
g_i_marshalling_tests_int8_return_min (void)
{
    return G_MININT8;
}

void
g_i_marshalling_tests_int8_in_max (gint8 int8)
{
    g_assert(int8 == G_MAXINT8);
}

void
g_i_marshalling_tests_int8_in_min (gint8 int8)
{
    g_assert(int8 == G_MININT8);
}

/**
 * g_i_marshalling_tests_int8_out_max:
 * int8: (out):
 */
void
g_i_marshalling_tests_int8_out_max (gint8 *int8)
{
    *int8 = G_MAXINT8;
}

/**
 * g_i_marshalling_tests_int8_out_min:
 * int8: (out):
 */
void
g_i_marshalling_tests_int8_out_min (gint8 *int8)
{
    *int8 = G_MININT8;
}

/**
 * g_i_marshalling_tests_int8_inout_max_min:
 * int8: (inout):
 */
void
g_i_marshalling_tests_int8_inout_max_min (gint8 *int8)
{
    g_assert(*int8 == G_MAXINT8);
    *int8 = G_MININT8;
}

/**
 * g_i_marshalling_tests_int8_inout_min_max:
 * int8: (inout):
 */
void
g_i_marshalling_tests_int8_inout_min_max (gint8 *int8)
{
    g_assert(*int8 == G_MININT8);
    *int8 = G_MAXINT8;
}


guint8
g_i_marshalling_tests_uint8_return (void)
{
    return G_MAXUINT8;
}

void
g_i_marshalling_tests_uint8_in (guint8 uint8)
{
    g_assert(uint8 == G_MAXUINT8);
}

/**
 * g_i_marshalling_tests_uint8_out:
 * uint8: (out):
 */
void
g_i_marshalling_tests_uint8_out (guint8 *uint8)
{
    *uint8 = G_MAXUINT8;
}

/**
 * g_i_marshalling_tests_uint8_inout:
 * uint8: (inout):
 */
void
g_i_marshalling_tests_uint8_inout (guint8 *uint8)
{
    g_assert(*uint8 == G_MAXUINT8);
    *uint8 = 0;
}


gint16
g_i_marshalling_tests_int16_return_max (void)
{
    return G_MAXINT16;
}

gint16
g_i_marshalling_tests_int16_return_min (void)
{
    return G_MININT16;
}

void
g_i_marshalling_tests_int16_in_max (gint16 int16)
{
    g_assert(int16 == G_MAXINT16);
}

void
g_i_marshalling_tests_int16_in_min (gint16 int16)
{
    g_assert(int16 == G_MININT16);
}

/**
 * g_i_marshalling_tests_int16_out_max:
 * int16: (out):
 */
void
g_i_marshalling_tests_int16_out_max (gint16 *int16)
{
    *int16 = G_MAXINT16;
}

/**
 * g_i_marshalling_tests_int16_out_min:
 * int16: (out):
 */
void
g_i_marshalling_tests_int16_out_min (gint16 *int16)
{
    *int16 = G_MININT16;
}

/**
 * g_i_marshalling_tests_int16_inout_max_min:
 * int16: (inout):
 */
void
g_i_marshalling_tests_int16_inout_max_min (gint16 *int16)
{
    g_assert(*int16 == G_MAXINT16);
    *int16 = G_MININT16;
}

/**
 * g_i_marshalling_tests_int16_inout_min_max:
 * int16: (inout):
 */
void
g_i_marshalling_tests_int16_inout_min_max (gint16 *int16)
{
    g_assert(*int16 == G_MININT16);
    *int16 = G_MAXINT16;
}


guint16
g_i_marshalling_tests_uint16_return (void)
{
    return G_MAXUINT16;
}

void
g_i_marshalling_tests_uint16_in (guint16 uint16)
{
    g_assert(uint16 == G_MAXUINT16);
}

/**
 * g_i_marshalling_tests_uint16_out:
 * uint16: (out):
 */
void
g_i_marshalling_tests_uint16_out (guint16 *uint16)
{
    *uint16 = G_MAXUINT16;
}

/**
 * g_i_marshalling_tests_uint16_inout:
 * uint16: (inout):
 */
void
g_i_marshalling_tests_uint16_inout (guint16 *uint16)
{
    g_assert(*uint16 == G_MAXUINT16);
    *uint16 = 0;
}


gint32
g_i_marshalling_tests_int32_return_max (void)
{
    return G_MAXINT32;
}

gint32
g_i_marshalling_tests_int32_return_min (void)
{
    return G_MININT32;
}

void
g_i_marshalling_tests_int32_in_max (gint32 int32)
{
    g_assert(int32 == G_MAXINT32);
}

void
g_i_marshalling_tests_int32_in_min (gint32 int32)
{
    g_assert(int32 == G_MININT32);
}

/**
 * g_i_marshalling_tests_int32_out_max:
 * int32: (out):
 */
void
g_i_marshalling_tests_int32_out_max (gint32 *int32)
{
    *int32 = G_MAXINT32;
}

/**
 * g_i_marshalling_tests_int32_out_min:
 * int32: (out):
 */
void
g_i_marshalling_tests_int32_out_min (gint32 *int32)
{
    *int32 = G_MININT32;
}

/**
 * g_i_marshalling_tests_int32_inout_max_min:
 * int32: (inout):
 */
void
g_i_marshalling_tests_int32_inout_max_min (gint32 *int32)
{
    g_assert(*int32 == G_MAXINT32);
    *int32 = G_MININT32;
}

/**
 * g_i_marshalling_tests_int32_inout_min_max:
 * int32: (inout):
 */
void
g_i_marshalling_tests_int32_inout_min_max (gint32 *int32)
{
    g_assert(*int32 == G_MININT32);
    *int32 = G_MAXINT32;
}


guint32
g_i_marshalling_tests_uint32_return (void)
{
    return G_MAXUINT32;
}

void
g_i_marshalling_tests_uint32_in (guint32 uint32)
{
    g_assert(uint32 == G_MAXUINT32);
}

/**
 * g_i_marshalling_tests_uint32_out:
 * uint32: (out):
 */
void
g_i_marshalling_tests_uint32_out (guint32 *uint32)
{
    *uint32 = G_MAXUINT32;
}

/**
 * g_i_marshalling_tests_uint32_inout:
 * uint32: (inout):
 */
void
g_i_marshalling_tests_uint32_inout (guint32 *uint32)
{
    g_assert(*uint32 == G_MAXUINT32);
    *uint32 = 0;
}


gint64
g_i_marshalling_tests_int64_return_max (void)
{
    return G_MAXINT64;
}

gint64
g_i_marshalling_tests_int64_return_min (void)
{
    return G_MININT64;
}

void
g_i_marshalling_tests_int64_in_max (gint64 int64)
{
    g_assert(int64 == G_MAXINT64);
}

void
g_i_marshalling_tests_int64_in_min (gint64 int64)
{
    g_assert(int64 == G_MININT64);
}

/**
 * g_i_marshalling_tests_int64_out_max:
 * int64: (out):
 */
void
g_i_marshalling_tests_int64_out_max (gint64 *int64)
{
    *int64 = G_MAXINT64;
}

/**
 * g_i_marshalling_tests_int64_out_min:
 * int64: (out):
 */
void
g_i_marshalling_tests_int64_out_min (gint64 *int64)
{
    *int64 = G_MININT64;
}

/**
 * g_i_marshalling_tests_int64_inout_max_min:
 * int64: (inout):
 */
void
g_i_marshalling_tests_int64_inout_max_min (gint64 *int64)
{
    g_assert(*int64 == G_MAXINT64);
    *int64 = G_MININT64;
}

/**
 * g_i_marshalling_tests_int64_inout_min_max:
 * int64: (inout):
 */
void
g_i_marshalling_tests_int64_inout_min_max (gint64 *int64)
{
    g_assert(*int64 == G_MININT64);
    *int64 = G_MAXINT64;
}


guint64
g_i_marshalling_tests_uint64_return (void)
{
    return G_MAXUINT64;
}

void
g_i_marshalling_tests_uint64_in (guint64 uint64)
{
    g_assert(uint64 == G_MAXUINT64);
}

/**
 * g_i_marshalling_tests_uint64_out:
 * uint64: (out):
 */
void
g_i_marshalling_tests_uint64_out (guint64 *uint64)
{
    *uint64 = G_MAXUINT64;
}

/**
 * g_i_marshalling_tests_uint64_inout:
 * uint64: (inout):
 */
void
g_i_marshalling_tests_uint64_inout (guint64 *uint64)
{
    g_assert(*uint64 == G_MAXUINT64);
    *uint64 = 0;
}


gshort
g_i_marshalling_tests_short_return_max (void)
{
    return G_MAXSHORT;
}

gshort
g_i_marshalling_tests_short_return_min (void)
{
    return G_MINSHORT;
}

void
g_i_marshalling_tests_short_in_max (gshort short_)
{
    g_assert(short_ == G_MAXSHORT);
}

void
g_i_marshalling_tests_short_in_min (gshort short_)
{
    g_assert(short_ == G_MINSHORT);
}

/**
 * g_i_marshalling_tests_short_out_max:
 * short_: (out):
 */
void
g_i_marshalling_tests_short_out_max (gshort *short_)
{
    *short_ = G_MAXSHORT;
}

/**
 * g_i_marshalling_tests_short_out_min:
 * short_: (out):
 */
void
g_i_marshalling_tests_short_out_min (gshort *short_)
{
    *short_ = G_MINSHORT;
}

/**
 * g_i_marshalling_tests_short_inout_max_min:
 * short_: (inout):
 */
void
g_i_marshalling_tests_short_inout_max_min (gshort *short_)
{
    g_assert(*short_ == G_MAXSHORT);
    *short_ = G_MINSHORT;
}

/**
 * g_i_marshalling_tests_short_inout_min_max:
 * short_: (inout):
 */
void
g_i_marshalling_tests_short_inout_min_max (gshort *short_)
{
    g_assert(*short_ == G_MINSHORT);
    *short_ = G_MAXSHORT;
}


gushort
g_i_marshalling_tests_ushort_return (void)
{
    return G_MAXUSHORT;
}

void
g_i_marshalling_tests_ushort_in (gushort ushort)
{
    g_assert(ushort == G_MAXUSHORT);
}

/**
 * g_i_marshalling_tests_ushort_out:
 * ushort: (out):
 */
void
g_i_marshalling_tests_ushort_out (gushort *ushort)
{
    *ushort = G_MAXUSHORT;
}

/**
 * g_i_marshalling_tests_ushort_inout:
 * ushort: (inout):
 */
void
g_i_marshalling_tests_ushort_inout (gushort *ushort)
{
    g_assert(*ushort == G_MAXUSHORT);
    *ushort = 0;
}


gint
g_i_marshalling_tests_int_return_max (void)
{
    return G_MAXINT;
}

gint
g_i_marshalling_tests_int_return_min (void)
{
    return G_MININT;
}

void
g_i_marshalling_tests_int_in_max (gint int_)
{
    g_assert(int_ == G_MAXINT);
}

void
g_i_marshalling_tests_int_in_min (gint int_)
{
    g_assert(int_ == G_MININT);
}

/**
 * g_i_marshalling_tests_int_out_max:
 * int_: (out):
 */
void
g_i_marshalling_tests_int_out_max (gint *int_)
{
    *int_ = G_MAXINT;
}

/**
 * g_i_marshalling_tests_int_out_min:
 * int_: (out):
 */
void
g_i_marshalling_tests_int_out_min (gint *int_)
{
    *int_ = G_MININT;
}

/**
 * g_i_marshalling_tests_int_inout_max_min:
 * int_: (inout):
 */
void
g_i_marshalling_tests_int_inout_max_min (gint *int_)
{
    g_assert(*int_ == G_MAXINT);
    *int_ = G_MININT;
}

/**
 * g_i_marshalling_tests_int_inout_min_max:
 * int_: (inout):
 */
void
g_i_marshalling_tests_int_inout_min_max (gint *int_)
{
    g_assert(*int_ == G_MININT);
    *int_ = G_MAXINT;
}


guint
g_i_marshalling_tests_uint_return (void)
{
    return G_MAXUINT;
}

void
g_i_marshalling_tests_uint_in (guint uint)
{
    g_assert(uint == G_MAXUINT);
}

/**
 * g_i_marshalling_tests_uint_out:
 * uint: (out):
 */
void
g_i_marshalling_tests_uint_out (guint *uint)
{
    *uint = G_MAXUINT;
}

/**
 * g_i_marshalling_tests_uint_inout:
 * uint: (inout):
 */
void
g_i_marshalling_tests_uint_inout (guint *uint)
{
    g_assert(*uint == G_MAXUINT);
    *uint = 0;
}


glong
g_i_marshalling_tests_long_return_max (void)
{
    return G_MAXLONG;
}

glong
g_i_marshalling_tests_long_return_min (void)
{
    return G_MINLONG;
}

void
g_i_marshalling_tests_long_in_max (glong long_)
{
    g_assert(long_ == G_MAXLONG);
}

void
g_i_marshalling_tests_long_in_min (glong long_)
{
    g_assert(long_ == G_MINLONG);
}

/**
 * g_i_marshalling_tests_long_out_max:
 * long_: (out):
 */
void
g_i_marshalling_tests_long_out_max (glong *long_)
{
    *long_ = G_MAXLONG;
}

/**
 * g_i_marshalling_tests_long_out_min:
 * long_: (out):
 */
void
g_i_marshalling_tests_long_out_min (glong *long_)
{
    *long_ = G_MINLONG;
}

/**
 * g_i_marshalling_tests_long_inout_max_min:
 * long_: (inout):
 */
void
g_i_marshalling_tests_long_inout_max_min (glong *long_)
{
    g_assert(*long_ == G_MAXLONG);
    *long_ = G_MINLONG;
}

/**
 * g_i_marshalling_tests_long_inout_min_max:
 * long_: (inout):
 */
void
g_i_marshalling_tests_long_inout_min_max (glong *long_)
{
    g_assert(*long_ == G_MINLONG);
    *long_ = G_MAXLONG;
}


gulong
g_i_marshalling_tests_ulong_return (void)
{
    return G_MAXULONG;
}

void
g_i_marshalling_tests_ulong_in (gulong ulong)
{
    g_assert(ulong == G_MAXULONG);
}

/**
 * g_i_marshalling_tests_ulong_out:
 * ulong: (out):
 */
void
g_i_marshalling_tests_ulong_out (gulong *ulong)
{
    *ulong = G_MAXULONG;
}

/**
 * g_i_marshalling_tests_ulong_inout:
 * ulong: (inout):
 */
void
g_i_marshalling_tests_ulong_inout (gulong *ulong)
{
    g_assert(*ulong == G_MAXULONG);
    *ulong = 0;
}


gssize
g_i_marshalling_tests_ssize_return_max (void)
{
    return G_MAXSSIZE;
}

gssize
g_i_marshalling_tests_ssize_return_min (void)
{
    return G_MINSSIZE;
}

void
g_i_marshalling_tests_ssize_in_max (gssize ssize)
{
    g_assert(ssize == G_MAXSSIZE);
}

void
g_i_marshalling_tests_ssize_in_min (gssize ssize)
{
    g_assert(ssize == G_MINSSIZE);
}

/**
 * g_i_marshalling_tests_ssize_out_max:
 * ssize: (out):
 */
void
g_i_marshalling_tests_ssize_out_max (gssize *ssize)
{
    *ssize = G_MAXSSIZE;
}

/**
 * g_i_marshalling_tests_ssize_out_min:
 * ssize: (out):
 */
void
g_i_marshalling_tests_ssize_out_min (gssize *ssize)
{
    *ssize = G_MINSSIZE;
}

/**
 * g_i_marshalling_tests_ssize_inout_max_min:
 * ssize: (inout):
 */
void
g_i_marshalling_tests_ssize_inout_max_min (gssize *ssize)
{
    g_assert(*ssize == G_MAXSSIZE);
    *ssize = G_MINSSIZE;
}

/**
 * g_i_marshalling_tests_ssize_inout_min_max:
 * ssize: (inout):
 */
void
g_i_marshalling_tests_ssize_inout_min_max (gssize *ssize)
{
    g_assert(*ssize == G_MINSSIZE);
    *ssize = G_MAXSSIZE;
}


gsize
g_i_marshalling_tests_size_return (void)
{
    return G_MAXSIZE;
}

void
g_i_marshalling_tests_size_in (gsize size)
{
    g_assert(size == G_MAXSIZE);
}

/**
 * g_i_marshalling_tests_size_out:
 * size: (out):
 */
void
g_i_marshalling_tests_size_out (gsize *size)
{
    *size = G_MAXSIZE;
}

/**
 * g_i_marshalling_tests_size_inout:
 * size: (inout):
 */
void
g_i_marshalling_tests_size_inout (gsize *size)
{
    g_assert(*size == G_MAXSIZE);
    *size = 0;
}


gfloat
g_i_marshalling_tests_float_return (void)
{
    return G_MAXFLOAT;
}

void
g_i_marshalling_tests_float_in (gfloat float_)
{
    g_assert(float_ == G_MAXFLOAT);
}

/**
 * g_i_marshalling_tests_float_out:
 * float_: (out):
 */
void
g_i_marshalling_tests_float_out (gfloat *float_)
{
    *float_ = G_MAXFLOAT;
}

/**
 * g_i_marshalling_tests_float_inout:
 * float_: (inout):
 */
void
g_i_marshalling_tests_float_inout (gfloat *float_)
{
    g_assert(*float_ == G_MAXFLOAT);
    *float_ = G_MINFLOAT;
}


gdouble
g_i_marshalling_tests_double_return (void)
{
    return G_MAXDOUBLE;
}

void
g_i_marshalling_tests_double_in (gdouble double_)
{
    g_assert(double_ == G_MAXDOUBLE);
}

/**
 * g_i_marshalling_tests_double_out:
 * double_: (out):
 */
void
g_i_marshalling_tests_double_out (gdouble *double_)
{
    *double_ = G_MAXDOUBLE;
}

/**
 * g_i_marshalling_tests_double_inout:
 * double_: (inout):
 */
void
g_i_marshalling_tests_double_inout (gdouble *double_)
{
    g_assert(*double_ == G_MAXDOUBLE);
    *double_ = G_MINDOUBLE;
}


time_t
g_i_marshalling_tests_time_t_return (void)
{
    return 1234567890;
}

void
g_i_marshalling_tests_time_t_in (time_t time_t_)
{
    g_assert(time_t_ == 1234567890);
}

/**
 * g_i_marshalling_tests_time_t_out:
 * time_t_: (out):
 */
void
g_i_marshalling_tests_time_t_out (time_t *time_t_)
{
    *time_t_ = 1234567890;
}

/**
 * g_i_marshalling_tests_time_t_inout:
 * time_t_: (inout):
 */
void
g_i_marshalling_tests_time_t_inout (time_t *time_t_)
{
    g_assert(*time_t_ == 1234567890);
    *time_t_ = 0;
}


GType
g_i_marshalling_tests_gtype_return (void)
{
    return G_TYPE_NONE;
}

void
g_i_marshalling_tests_gtype_in (GType gtype)
{
    g_assert(gtype == G_TYPE_NONE);
}

/**
 * g_i_marshalling_tests_gtype_out:
 * gtype: (out):
 */
void
g_i_marshalling_tests_gtype_out (GType *gtype)
{
    *gtype = G_TYPE_NONE;
}

/**
 * g_i_marshalling_tests_gtype_inout:
 * gtype: (inout):
 */
void
g_i_marshalling_tests_gtype_inout (GType *gtype)
{
    g_assert(*gtype == G_TYPE_NONE);
    *gtype = G_TYPE_INT;
}


const gchar *
g_i_marshalling_tests_utf8_none_return (void)
{
    return G_I_MARSHALLING_TESTS_CONSTANT_UTF8;
}

gchar *
g_i_marshalling_tests_utf8_full_return (void)
{
    return g_strdup(G_I_MARSHALLING_TESTS_CONSTANT_UTF8);
}

void
g_i_marshalling_tests_utf8_none_in (const gchar *utf8)
{
    g_assert(strcmp(G_I_MARSHALLING_TESTS_CONSTANT_UTF8, utf8) == 0);
}

void
g_i_marshalling_tests_utf8_full_in (gchar *utf8)
{
    g_assert(strcmp(G_I_MARSHALLING_TESTS_CONSTANT_UTF8, utf8) == 0);
    g_free(utf8);
}

/**
 * g_i_marshalling_tests_utf8_none_out:
 * utf8: (out) (transfer none):
 */
void
g_i_marshalling_tests_utf8_none_out (gchar **utf8)
{
    *utf8 = G_I_MARSHALLING_TESTS_CONSTANT_UTF8;
}

/**
 * g_i_marshalling_tests_utf8_full_out:
 * utf8: (out) (transfer full):
 */
void
g_i_marshalling_tests_utf8_full_out (gchar **utf8)
{
    *utf8 = g_strdup(G_I_MARSHALLING_TESTS_CONSTANT_UTF8);
}

/**
 * g_i_marshalling_tests_utf8_dangling_out:
 * utf8: (out) (transfer full):
 */
void
g_i_marshalling_tests_utf8_dangling_out (gchar **utf8)
{
    /* Intentionally don't touch the pointer to see how
       the bindings handle this case.  Bindings should be
       robust against broken C functions and can initialize 
       even OUT vlues to NULL.
    */
}

/**
 * g_i_marshalling_tests_utf8_none_inout:
 * utf8: (inout) (transfer none):
 */
void
g_i_marshalling_tests_utf8_none_inout (gchar **utf8)
{
    g_assert(strcmp(G_I_MARSHALLING_TESTS_CONSTANT_UTF8, *utf8) == 0);
    *utf8 = "";
}

/**
 * g_i_marshalling_tests_utf8_full_inout:
 * utf8: (inout) (transfer full):
 */
void
g_i_marshalling_tests_utf8_full_inout (gchar **utf8)
{
    g_assert(strcmp(G_I_MARSHALLING_TESTS_CONSTANT_UTF8, *utf8) == 0);
    g_free(*utf8);
    *utf8 = g_strdup("");
}


/**
 * g_i_marshalling_tests_array_fixed_int_return:
 * Returns: (array fixed-size=4):
 */
const gint *
g_i_marshalling_tests_array_fixed_int_return (void)
{
    static gint ints[] = {-1, 0, 1, 2};
    return ints;
}

/**
 * g_i_marshalling_tests_array_fixed_short_return:
 * Returns: (array fixed-size=4):
 */
const gshort *
g_i_marshalling_tests_array_fixed_short_return (void)
{
    static gshort shorts[] = {-1, 0, 1, 2};
    return shorts;
}

/**
 * g_i_marshalling_tests_array_fixed_int_in:
 * @ints: (array fixed-size=4):
 */
void
g_i_marshalling_tests_array_fixed_int_in (const gint *ints)
{
    g_assert(ints[0] == -1);
    g_assert(ints[1] == 0);
    g_assert(ints[2] == 1);
    g_assert(ints[3] == 2);
}

/**
 * g_i_marshalling_tests_array_fixed_short_in:
 * @shorts: (array fixed-size=4):
 */
void
g_i_marshalling_tests_array_fixed_short_in (const gshort *shorts)
{
    g_assert(shorts[0] == -1);
    g_assert(shorts[1] == 0);
    g_assert(shorts[2] == 1);
    g_assert(shorts[3] == 2);
}

/**
 * g_i_marshalling_tests_array_fixed_out:
 * @ints: (out) (array fixed-size=4) (transfer none):
 */
void
g_i_marshalling_tests_array_fixed_out (gint **ints)
{
    static gint values[] = {-1, 0, 1, 2};
    *ints = values;
}

/**
 * g_i_marshalling_tests_array_fixed_out_struct:
 * @structs: (out) (array fixed-size=2) (transfer none):
 */
void
g_i_marshalling_tests_array_fixed_out_struct (GIMarshallingTestsSimpleStruct **structs)
{
    static GIMarshallingTestsSimpleStruct *values;

    if (values == NULL) {
        values = g_new(GIMarshallingTestsSimpleStruct, 2);

        values[0].long_ = 7;
        values[0].int8 = 6;

        values[1].long_ = 6;
        values[1].int8 = 7;
    }

    *structs = values;
}

/**
 * g_i_marshalling_tests_array_fixed_inout:
 * @ints: (inout) (array fixed-size=4) (transfer none):
 */
void
g_i_marshalling_tests_array_fixed_inout (gint **ints)
{
    static gint values[] = {2, 1, 0, -1};

    g_assert((*ints)[0] == -1);
    g_assert((*ints)[1] == 0);
    g_assert((*ints)[2] == 1);
    g_assert((*ints)[3] == 2);

    *ints = values;
}


/**
 * g_i_marshalling_tests_array_return:
 * Returns: (array length=length):
 */
const gint *
g_i_marshalling_tests_array_return (gint *length)
{
    static gint ints[] = {-1, 0, 1, 2};

    *length = 4;
    return ints;
}

/**
 * g_i_marshalling_tests_array_in:
 * @ints: (array length=length):
 */
void
g_i_marshalling_tests_array_in (const gint *ints, gint length)
{
    g_assert(length == 4);
    g_assert(ints[0] == -1);
    g_assert(ints[1] == 0);
    g_assert(ints[2] == 1);
    g_assert(ints[3] == 2);
}

/**
 * g_i_marshalling_tests_array_out:
 * @ints: (out) (array length=length) (transfer none):
 */
void
g_i_marshalling_tests_array_out (gint **ints, gint *length)
{
    static gint values[] = {-1, 0, 1, 2};

    *length = 4;
    *ints = values;
}

/**
 * g_i_marshalling_tests_array_inout:
 * @ints: (inout) (array length=length) (transfer none):
 * @length: (inout):
 */
void
g_i_marshalling_tests_array_inout (gint **ints, gint *length)
{
    static gint values[] = {-2, -1, 0, 1, 2};

    g_assert(*length == 4);
    g_assert((*ints)[0] == -1);
    g_assert((*ints)[1] == 0);
    g_assert((*ints)[2] == 1);
    g_assert((*ints)[3] == 2);

    *length = 5;
    *ints = values;
}

/**
 * g_i_marshalling_tests_array_zero_terminated_return:
 * Returns: (array zero-terminated=1) (transfer none):
 */
gchar **
g_i_marshalling_tests_array_zero_terminated_return (void)
{
    static gchar *values[] = {"0", "1", "2", NULL};
    return values;
}

/**
 * g_i_marshalling_tests_array_zero_terminated_in:
 * @utf8s: (array zero-terminated=1) (transfer none):
 */
void
g_i_marshalling_tests_array_zero_terminated_in (gchar **utf8s)
{
    g_assert(g_strv_length(utf8s));
    g_assert(strcmp(utf8s[0], "0") == 0);
    g_assert(strcmp(utf8s[1], "1") == 0);
    g_assert(strcmp(utf8s[2], "2") == 0);
}

/**
 * g_i_marshalling_tests_array_zero_terminated_out:
 * @utf8s: (out) (array zero-terminated=1) (transfer none):
 */
void
g_i_marshalling_tests_array_zero_terminated_out (gchar ***utf8s)
{
    static gchar *values[] = {"0", "1", "2", NULL};
    *utf8s = values;
}

/**
 * g_i_marshalling_tests_array_zero_terminated_inout:
 * @utf8s: (inout) (array zero-terminated=1) (transfer none):
 */
void
g_i_marshalling_tests_array_zero_terminated_inout (gchar ***utf8s)
{
    static gchar *values[] = {"-1", "0", "1", "2", NULL};

    g_assert(g_strv_length(*utf8s));
    g_assert(strcmp((*utf8s)[0], "0") == 0);
    g_assert(strcmp((*utf8s)[1], "1") == 0);
    g_assert(strcmp((*utf8s)[2], "2") == 0);

    *utf8s = values;
}


/**
 * g_i_marshalling_tests_garray_int_none_return:
 * Returns: (element-type gint) (transfer none):
 */
GArray *
g_i_marshalling_tests_garray_int_none_return (void)
{
    static GArray *array = NULL;
    gint i;

    if (array == NULL) {
        array = g_array_new (TRUE, TRUE, sizeof (gint));
        for (i = -1; i < 3; i++)
            g_array_append_val (array, i);
    }

    return array;
}

/**
 * g_i_marshalling_tests_garray_utf8_none_return:
 * Returns: (element-type utf8) (transfer none):
 */
GArray *
g_i_marshalling_tests_garray_utf8_none_return (void)
{
    static GArray *array = NULL;
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    if (array == NULL) {
        array = g_array_new (TRUE, TRUE, sizeof (gchar *));
        for (i = 0; values[i]; i++)
            g_array_append_val (array, values[i]);
    }

    return array;
}

/**
 * g_i_marshalling_tests_garray_utf8_container_return:
 * Returns: (element-type utf8) (transfer container):
 */
GArray *
g_i_marshalling_tests_garray_utf8_container_return (void)
{
    GArray *array = NULL;
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    array = g_array_new (TRUE, TRUE, sizeof (gchar *));
    for (i = 0; values[i]; i++)
        g_array_append_val (array, values[i]);

    return array;
}

/**
 * g_i_marshalling_tests_garray_utf8_full_return:
 * Returns: (element-type utf8) (transfer full):
 */
GArray *
g_i_marshalling_tests_garray_utf8_full_return (void)
{
    GArray *array = NULL;
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    array = g_array_new (TRUE, TRUE, sizeof (gchar *));
    for (i = 0; values[i]; i++) {
        gchar *str = g_strdup (values[i]);
        g_array_append_val (array, str);
    }

    return array;
}

/**
 * g_i_marshalling_tests_garray_int_none_in:
 * @array_: (element-type gint) (transfer none):
 */
void
g_i_marshalling_tests_garray_int_none_in (GArray *array_)
{
    g_assert (array_->len == 4);
    g_assert (g_array_index (array_, gint, 0) == -1);
    g_assert (g_array_index (array_, gint, 1) == 0);
    g_assert (g_array_index (array_, gint, 2) == 1);
    g_assert (g_array_index (array_, gint, 3) == 2);
}

/**
 * g_i_marshalling_tests_garray_utf8_none_in:
 * @array_: (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_garray_utf8_none_in (GArray *array_)
{
    g_assert (array_->len == 3);
    g_assert (strcmp (g_array_index (array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 2), "2") == 0);
}

/**
 * g_i_marshalling_tests_garray_utf8_container_in:
 * @array_: (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_garray_utf8_container_in (GArray *array_)
{
    g_assert (array_->len == 3);
    g_assert (strcmp (g_array_index (array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 2), "2") == 0);
    g_array_free (array_, TRUE);
}

/**
 * g_i_marshalling_tests_garray_utf8_full_in:
 * @array_: (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_garray_utf8_full_in (GArray *array_)
{
    g_assert (array_->len == 3);
    g_assert (strcmp (g_array_index (array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (array_, gchar*, 2), "2") == 0);
    g_free (g_array_index (array_, gchar*, 0));
    g_free (g_array_index (array_, gchar*, 1));
    g_free (g_array_index (array_, gchar*, 2));
    g_array_free (array_, TRUE);
}

/**
 * g_i_marshalling_tests_garray_utf8_none_out:
 * @array_: (out) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_garray_utf8_none_out (GArray **array_)
{
    static GArray *internal = NULL;
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    if (internal == NULL) {
        internal = g_array_new (TRUE, TRUE, sizeof (gchar *));
        for (i = 0; values[i]; i++)
            g_array_append_val (internal, values[i]);
    }

    *array_ = internal;
}

/**
 * g_i_marshalling_tests_garray_utf8_container_out:
 * @array_: (out) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_garray_utf8_container_out (GArray **array_)
{
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    *array_ = NULL;

    *array_ = g_array_new (TRUE, TRUE, sizeof (gchar *));
    for (i = 0; values[i]; i++)
        g_array_append_val (*array_, values[i]);
}

/**
 * g_i_marshalling_tests_garray_utf8_full_out:
 * @array_: (out) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_garray_utf8_full_out (GArray **array_)
{
    static gchar *values[] = {"0", "1", "2", NULL};
    gint i;

    *array_ = NULL;

    *array_ = g_array_new (TRUE, TRUE, sizeof (gchar *));
    for (i = 0; values[i]; i++) {
        gchar *str = g_strdup (values[i]);
        g_array_append_val (*array_, str);
    }
}

/**
 * g_i_marshalling_tests_garray_utf8_none_inout:
 * @array_: (inout) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_garray_utf8_none_inout (GArray **array_)
{
    static GArray *internal = NULL;
    static gchar *values[] = {"-2", "-1", "0", "1", NULL};
    gint i;

    g_assert ((*array_)->len == 3);
    g_assert (strcmp (g_array_index (*array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 2), "2") == 0);

    if (internal == NULL) {
        internal = g_array_new (TRUE, TRUE, sizeof (gchar *));
        for (i = 0; values[i]; i++)
            g_array_append_val (internal, values[i]);
    }

    *array_ = internal;
}

/**
 * g_i_marshalling_tests_garray_utf8_container_inout:
 * @array_: (inout) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_garray_utf8_container_inout (GArray **array_)
{
    static gchar *val1 = "-1";
    static gchar *val2 = "-2";

    g_assert ((*array_)->len == 3);
    g_assert (strcmp (g_array_index (*array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 2), "2") == 0);

    g_array_remove_index (*array_, (*array_)->len - 1);

    g_array_prepend_val (*array_, val1);
    g_array_prepend_val (*array_, val2);
}

/**
 * g_i_marshalling_tests_garray_utf8_full_inout:
 * @array_: (inout) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_garray_utf8_full_inout (GArray **array_)
{
    static gchar *val1 = "-1";
    static gchar *val2 = "-2";
    gchar *val;

    g_assert ((*array_)->len == 3);
    g_assert (strcmp (g_array_index (*array_, gchar*, 0), "0") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 1), "1") == 0);
    g_assert (strcmp (g_array_index (*array_, gchar*, 2), "2") == 0);

    g_free (g_array_index (*array_, gchar*, (*array_)->len - 1));
    g_array_remove_index (*array_, (*array_)->len - 1);

    val = g_strdup (val1);
    g_array_prepend_val (*array_, val);

    val = g_strdup (val2);
    g_array_prepend_val (*array_, val);
}

/**
 * g_i_marshalling_tests_gstrv_return:
 * Returns:
 */
GStrv
g_i_marshalling_tests_gstrv_return (void)
{
    GStrv values = g_new0 (gchar*, 4);
    values[0] = g_strdup ("0");
    values[1] = g_strdup ("1");
    values[2] = g_strdup ("2");
    values[3] = NULL;
    return values;
}

/**
 * g_i_marshalling_tests_gstrv_in:
 * @g_strv:
 */
void
g_i_marshalling_tests_gstrv_in (GStrv g_strv)
{
    g_assert(g_strv_length(g_strv) == 3);
    g_assert(strcmp(g_strv[0], "0") == 0);
    g_assert(strcmp(g_strv[1], "1") == 0);
    g_assert(strcmp(g_strv[2], "2") == 0);
}

/**
 * g_i_marshalling_tests_gstrv_out:
 * @g_strv: (out) (transfer none):
 */
void
g_i_marshalling_tests_gstrv_out (GStrv *g_strv)
{
    static gchar *values[] = {"0", "1", "2", NULL};
    *g_strv = values;
}

/**
 * g_i_marshalling_tests_gstrv_inout:
 * @g_strv: (inout) (transfer none):
 */
void
g_i_marshalling_tests_gstrv_inout (GStrv *g_strv)
{
    static gchar *values[] = {"-1", "0", "1", "2", NULL};

    g_assert(g_strv_length(*g_strv) == 3);
    g_assert(strcmp((*g_strv)[0], "0") == 0);
    g_assert(strcmp((*g_strv)[1], "1") == 0);
    g_assert(strcmp((*g_strv)[2], "2") == 0);

    *g_strv = values;
}

/**
 * g_i_marshalling_tests_glist_int_none_return:
 * Returns: (element-type gint) (transfer none):
 */
GList *
g_i_marshalling_tests_glist_int_none_return (void)
{
    static GList *list = NULL;

    if (list == NULL) {
        list = g_list_append(list, GINT_TO_POINTER(-1));
        list = g_list_append(list, GINT_TO_POINTER(0));
        list = g_list_append(list, GINT_TO_POINTER(1));
        list = g_list_append(list, GINT_TO_POINTER(2));
    }

    return list;
}

/**
 * g_i_marshalling_tests_glist_utf8_none_return:
 * Returns: (element-type utf8) (transfer none):
 */
GList *
g_i_marshalling_tests_glist_utf8_none_return (void)
{
    static GList *list = NULL;

    if (list == NULL) {
        list = g_list_append(list, "0");
        list = g_list_append(list, "1");
        list = g_list_append(list, "2");
    }

    return list;
}

/**
 * g_i_marshalling_tests_glist_utf8_container_return:
 * Returns: (element-type utf8) (transfer container):
 */
GList *
g_i_marshalling_tests_glist_utf8_container_return (void)
{
    GList *list = NULL;

    list = g_list_append(list, "0");
    list = g_list_append(list, "1");
    list = g_list_append(list, "2");

    return list;
}

/**
 * g_i_marshalling_tests_glist_utf8_full_return:
 * Returns: (element-type utf8) (transfer full):
 */
GList *
g_i_marshalling_tests_glist_utf8_full_return (void)
{
    GList *list = NULL;

    list = g_list_append(list, g_strdup("0"));
    list = g_list_append(list, g_strdup("1"));
    list = g_list_append(list, g_strdup("2"));

    return list;
}

/**
 * g_i_marshalling_tests_glist_int_none_in:
 * @list: (element-type gint) (transfer none):
 */
void
g_i_marshalling_tests_glist_int_none_in (GList *list)
{
    g_assert(g_list_length(list) == 4);
    g_assert(GPOINTER_TO_INT(g_list_nth_data(list, 0)) == -1);
    g_assert(GPOINTER_TO_INT(g_list_nth_data(list, 1)) == 0);
    g_assert(GPOINTER_TO_INT(g_list_nth_data(list, 2)) == 1);
    g_assert(GPOINTER_TO_INT(g_list_nth_data(list, 3)) == 2);
}

/**
 * g_i_marshalling_tests_glist_utf8_none_in:
 * @list: (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_glist_utf8_none_in (GList *list)
{
    g_assert(g_list_length(list) == 3);
    g_assert(strcmp(g_list_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(list, 2), "2") == 0);
}

/**
 * g_i_marshalling_tests_glist_utf8_container_in:
 * @list: (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_glist_utf8_container_in (GList *list)
{
    g_assert(g_list_length(list) == 3);
    g_assert(strcmp(g_list_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(list, 2), "2") == 0);
    g_list_free(list);
}

/**
 * g_i_marshalling_tests_glist_utf8_full_in:
 * @list: (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_glist_utf8_full_in (GList *list)
{
    g_assert(g_list_length(list) == 3);
    g_assert(strcmp(g_list_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(list, 2), "2") == 0);
    g_free(g_list_nth_data(list, 0));
    g_free(g_list_nth_data(list, 1));
    g_free(g_list_nth_data(list, 2));
    g_list_free(list);
}

/**
 * g_i_marshalling_tests_glist_utf8_none_out:
 * @list: (out) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_glist_utf8_none_out (GList **list)
{
    static GList *values = NULL;

    if (values == NULL) {
        values = g_list_append(values, "0");
        values = g_list_append(values, "1");
        values = g_list_append(values, "2");
    }

    *list = values;
}

/**
 * g_i_marshalling_tests_glist_utf8_container_out:
 * @list: (out) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_glist_utf8_container_out (GList **list)
{
    *list = NULL;

    *list = g_list_append(*list, "0");
    *list = g_list_append(*list, "1");
    *list = g_list_append(*list, "2");
}

/**
 * g_i_marshalling_tests_glist_utf8_full_out:
 * @list: (out) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_glist_utf8_full_out (GList **list)
{
    *list = NULL;

    *list = g_list_append(*list, g_strdup("0"));
    *list = g_list_append(*list, g_strdup("1"));
    *list = g_list_append(*list, g_strdup("2"));
}

/**
 * g_i_marshalling_tests_glist_utf8_none_inout:
 * @list: (inout) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_glist_utf8_none_inout (GList **list)
{
    static GList *values = NULL;

    g_assert(g_list_length(*list) == 3);
    g_assert(strcmp(g_list_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 2), "2") == 0);

    if (values == NULL) {
        values = g_list_append(values, "-2");
        values = g_list_append(values, "-1");
        values = g_list_append(values, "0");
        values = g_list_append(values, "1");
    }

    *list = values;
}

/**
 * g_i_marshalling_tests_glist_utf8_container_inout:
 * @list: (inout) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_glist_utf8_container_inout (GList **list)
{
    g_assert(g_list_length(*list) == 3);
    g_assert(strcmp(g_list_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 2), "2") == 0);

    *list = g_list_remove_link(*list, g_list_last(*list));

    *list = g_list_prepend(*list, "-1");
    *list = g_list_prepend(*list, "-2");
}

/**
 * g_i_marshalling_tests_glist_utf8_full_inout:
 * @list: (inout) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_glist_utf8_full_inout (GList **list)
{
    gpointer *data;

    g_assert(g_list_length(*list) == 3);
    g_assert(strcmp(g_list_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_list_nth_data(*list, 2), "2") == 0);

    data = g_list_last(*list)->data;
    *list = g_list_remove(*list, data);
    g_free(data);

    *list = g_list_prepend(*list, g_strdup("-1"));
    *list = g_list_prepend(*list, g_strdup("-2"));
}


/**
 * g_i_marshalling_tests_gslist_int_none_return:
 * Returns: (element-type gint) (transfer none):
 */
GSList *
g_i_marshalling_tests_gslist_int_none_return (void)
{
    static GSList *list = NULL;

    if (list == NULL) {
        list = g_slist_prepend(list, GINT_TO_POINTER(-1));
        list = g_slist_prepend(list, GINT_TO_POINTER(0));
        list = g_slist_prepend(list, GINT_TO_POINTER(1));
        list = g_slist_prepend(list, GINT_TO_POINTER(2));
        list = g_slist_reverse(list);
    }

    return list;
}

/**
 * g_i_marshalling_tests_gslist_utf8_none_return:
 * Returns: (element-type utf8) (transfer none):
 */
GSList *
g_i_marshalling_tests_gslist_utf8_none_return (void)
{
    static GSList *list = NULL;

    if (list == NULL) {
        list = g_slist_prepend(list, "0");
        list = g_slist_prepend(list, "1");
        list = g_slist_prepend(list, "2");
        list = g_slist_reverse(list);
    }

    return list;
}

/**
 * g_i_marshalling_tests_gslist_utf8_container_return:
 * Returns: (element-type utf8) (transfer container):
 */
GSList *
g_i_marshalling_tests_gslist_utf8_container_return (void)
{
    GSList *list = NULL;

    list = g_slist_prepend(list, "0");
    list = g_slist_prepend(list, "1");
    list = g_slist_prepend(list, "2");
    list = g_slist_reverse(list);

    return list;
}

/**
 * g_i_marshalling_tests_gslist_utf8_full_return:
 * Returns: (element-type utf8) (transfer full):
 */
GSList *
g_i_marshalling_tests_gslist_utf8_full_return (void)
{
    GSList *list = NULL;

    list = g_slist_prepend(list, g_strdup("0"));
    list = g_slist_prepend(list, g_strdup("1"));
    list = g_slist_prepend(list, g_strdup("2"));
    list = g_slist_reverse(list);

    return list;
}

/**
 * g_i_marshalling_tests_gslist_int_none_in:
 * @list: (element-type gint) (transfer none):
 */
void
g_i_marshalling_tests_gslist_int_none_in (GSList *list)
{
    g_assert(g_slist_length(list) == 4);
    g_assert(GPOINTER_TO_INT(g_slist_nth_data(list, 0)) == -1);
    g_assert(GPOINTER_TO_INT(g_slist_nth_data(list, 1)) == 0);
    g_assert(GPOINTER_TO_INT(g_slist_nth_data(list, 2)) == 1);
    g_assert(GPOINTER_TO_INT(g_slist_nth_data(list, 3)) == 2);
}

/**
 * g_i_marshalling_tests_gslist_utf8_none_in:
 * @list: (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_gslist_utf8_none_in (GSList *list)
{
    g_assert(g_slist_length(list) == 3);
    g_assert(strcmp(g_slist_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 2), "2") == 0);
}

/**
 * g_i_marshalling_tests_gslist_utf8_container_in:
 * @list: (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_gslist_utf8_container_in (GSList *list)
{
    g_assert(g_slist_length(list) == 3);
    g_assert(strcmp(g_slist_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 2), "2") == 0);
    g_slist_free(list);
}

/**
 * g_i_marshalling_tests_gslist_utf8_full_in:
 * @list: (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_gslist_utf8_full_in (GSList *list)
{
    g_assert(g_slist_length(list) == 3);
    g_assert(strcmp(g_slist_nth_data(list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(list, 2), "2") == 0);
    g_free(g_slist_nth_data(list, 0));
    g_free(g_slist_nth_data(list, 1));
    g_free(g_slist_nth_data(list, 2));
    g_slist_free(list);
}

/**
 * g_i_marshalling_tests_gslist_utf8_none_out:
 * @list: (out) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_gslist_utf8_none_out (GSList **list)
{
    static GSList *values = NULL;

    if (values == NULL) {
        values = g_slist_prepend(values, "0");
        values = g_slist_prepend(values, "1");
        values = g_slist_prepend(values, "2");
        values = g_slist_reverse(values);
    }

    *list = values;
}

/**
 * g_i_marshalling_tests_gslist_utf8_container_out:
 * @list: (out) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_gslist_utf8_container_out (GSList **list)
{
    *list = NULL;

    *list = g_slist_prepend(*list, "0");
    *list = g_slist_prepend(*list, "1");
    *list = g_slist_prepend(*list, "2");
    *list = g_slist_reverse(*list);
}

/**
 * g_i_marshalling_tests_gslist_utf8_full_out:
 * @list: (out) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_gslist_utf8_full_out (GSList **list)
{
    *list = NULL;

    *list = g_slist_prepend(*list, g_strdup("0"));
    *list = g_slist_prepend(*list, g_strdup("1"));
    *list = g_slist_prepend(*list, g_strdup("2"));
    *list = g_slist_reverse(*list);
}

/**
 * g_i_marshalling_tests_gslist_utf8_none_inout:
 * @list: (inout) (element-type utf8) (transfer none):
 */
void
g_i_marshalling_tests_gslist_utf8_none_inout (GSList **list)
{
    static GSList *values = NULL;

    g_assert(g_slist_length(*list) == 3);
    g_assert(strcmp(g_slist_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 2), "2") == 0);

    if (values == NULL) {
        values = g_slist_prepend(values, "-2");
        values = g_slist_prepend(values, "-1");
        values = g_slist_prepend(values, "0");
        values = g_slist_prepend(values, "1");
        values = g_slist_reverse(values);
    }

    *list = values;
}

/**
 * g_i_marshalling_tests_gslist_utf8_container_inout:
 * @list: (inout) (element-type utf8) (transfer container):
 */
void
g_i_marshalling_tests_gslist_utf8_container_inout (GSList **list)
{
    g_assert(g_slist_length(*list) == 3);
    g_assert(strcmp(g_slist_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 2), "2") == 0);

    *list = g_slist_remove_link(*list, g_slist_last(*list));

    *list = g_slist_prepend(*list, "-1");
    *list = g_slist_prepend(*list, "-2");
}

/**
 * g_i_marshalling_tests_gslist_utf8_full_inout:
 * @list: (inout) (element-type utf8) (transfer full):
 */
void
g_i_marshalling_tests_gslist_utf8_full_inout (GSList **list)
{
    gpointer *data;

    g_assert(g_slist_length(*list) == 3);
    g_assert(strcmp(g_slist_nth_data(*list, 0), "0") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 1), "1") == 0);
    g_assert(strcmp(g_slist_nth_data(*list, 2), "2") == 0);

    data = g_slist_last(*list)->data;
    *list = g_slist_remove(*list, data);
    g_free(data);

    *list = g_slist_prepend(*list, g_strdup("-1"));
    *list = g_slist_prepend(*list, g_strdup("-2"));
}


/**
 * g_i_marshalling_tests_ghashtable_int_none_return:
 * Returns: (element-type gint gint) (transfer none):
 */
GHashTable *
g_i_marshalling_tests_ghashtable_int_none_return (void)
{
    static GHashTable *hash_table = NULL;

    if (hash_table == NULL) {
        hash_table = g_hash_table_new(NULL, NULL);
        g_hash_table_insert(hash_table, GINT_TO_POINTER(-1), GINT_TO_POINTER(1));
        g_hash_table_insert(hash_table, GINT_TO_POINTER(0), GINT_TO_POINTER(0));
        g_hash_table_insert(hash_table, GINT_TO_POINTER(1), GINT_TO_POINTER(-1));
        g_hash_table_insert(hash_table, GINT_TO_POINTER(2), GINT_TO_POINTER(-2));
    }

    return hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_none_return:
 * Returns: (element-type utf8 utf8) (transfer none):
 */
GHashTable *
g_i_marshalling_tests_ghashtable_utf8_none_return (void)
{
    static GHashTable *hash_table = NULL;

    if (hash_table == NULL) {
        hash_table = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(hash_table, "-1", "1");
        g_hash_table_insert(hash_table, "0", "0");
        g_hash_table_insert(hash_table, "1", "-1");
        g_hash_table_insert(hash_table, "2", "-2");
    }

    return hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_container_return:
 * Returns: (element-type utf8 utf8) (transfer container):
 */
GHashTable *
g_i_marshalling_tests_ghashtable_utf8_container_return (void)
{
    GHashTable *hash_table = NULL;

    hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash_table, "-1", "1");
    g_hash_table_insert(hash_table, "0", "0");
    g_hash_table_insert(hash_table, "1", "-1");
    g_hash_table_insert(hash_table, "2", "-2");

    return hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_full_return:
 * Returns: (element-type utf8 utf8) (transfer full):
 */
GHashTable *
g_i_marshalling_tests_ghashtable_utf8_full_return (void)
{
    GHashTable *hash_table = NULL;

    hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash_table, g_strdup("-1"), g_strdup("1"));
    g_hash_table_insert(hash_table, g_strdup("0"), g_strdup("0"));
    g_hash_table_insert(hash_table, g_strdup("1"), g_strdup("-1"));
    g_hash_table_insert(hash_table, g_strdup("2"), g_strdup("-2"));

    return hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_int_none_in:
 * @hash_table: (element-type gint gint) (transfer none):
 */
void
g_i_marshalling_tests_ghashtable_int_none_in (GHashTable *hash_table)
{
    g_assert(GPOINTER_TO_INT(g_hash_table_lookup(hash_table, GINT_TO_POINTER(-1))) == 1);
    g_assert(GPOINTER_TO_INT(g_hash_table_lookup(hash_table, GINT_TO_POINTER(0))) == 0);
    g_assert(GPOINTER_TO_INT(g_hash_table_lookup(hash_table, GINT_TO_POINTER(1))) == -1);
    g_assert(GPOINTER_TO_INT(g_hash_table_lookup(hash_table, GINT_TO_POINTER(2))) == -2);
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_none_in:
 * @hash_table: (element-type utf8 utf8) (transfer none):
 */
void
g_i_marshalling_tests_ghashtable_utf8_none_in (GHashTable *hash_table)
{
    g_assert(strcmp(g_hash_table_lookup(hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "2"), "-2") == 0);
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_container_in:
 * @hash_table: (element-type utf8 utf8) (transfer container):
 */
void
g_i_marshalling_tests_ghashtable_utf8_container_in (GHashTable *hash_table)
{
    g_assert(strcmp(g_hash_table_lookup(hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "2"), "-2") == 0);
    g_hash_table_steal_all(hash_table);
    g_hash_table_unref(hash_table);
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_full_in:
 * @hash_table: (element-type utf8 utf8) (transfer full):
 */
void
g_i_marshalling_tests_ghashtable_utf8_full_in (GHashTable *hash_table)
{
    GHashTableIter hash_table_iter;
    gpointer key, value;

    g_assert(strcmp(g_hash_table_lookup(hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(hash_table, "2"), "-2") == 0);

    g_hash_table_iter_init(&hash_table_iter, hash_table);
    while (g_hash_table_iter_next(&hash_table_iter, &key, &value)) {
        g_free(key);
        g_free(value);
        g_hash_table_iter_steal(&hash_table_iter);
    }

    g_hash_table_unref(hash_table);
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_none_out:
 * @hash_table: (out) (element-type utf8 utf8) (transfer none):
 */
void
g_i_marshalling_tests_ghashtable_utf8_none_out (GHashTable **hash_table)
{
    static GHashTable *new_hash_table = NULL;

    if (new_hash_table == NULL) {
        new_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(new_hash_table, "-1", "1");
        g_hash_table_insert(new_hash_table, "0", "0");
        g_hash_table_insert(new_hash_table, "1", "-1");
        g_hash_table_insert(new_hash_table, "2", "-2");
    }

    *hash_table = new_hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_container_out:
 * @hash_table: (out) (element-type utf8 utf8) (transfer container):
 */
void
g_i_marshalling_tests_ghashtable_utf8_container_out (GHashTable **hash_table)
{
    *hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(*hash_table, "-1", "1");
    g_hash_table_insert(*hash_table, "0", "0");
    g_hash_table_insert(*hash_table, "1", "-1");
    g_hash_table_insert(*hash_table, "2", "-2");
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_full_out:
 * @hash_table: (out) (element-type utf8 utf8) (transfer full):
 */
void
g_i_marshalling_tests_ghashtable_utf8_full_out (GHashTable **hash_table)
{
    *hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(*hash_table, g_strdup("-1"), g_strdup("1"));
    g_hash_table_insert(*hash_table, g_strdup("0"), g_strdup("0"));
    g_hash_table_insert(*hash_table, g_strdup("1"), g_strdup("-1"));
    g_hash_table_insert(*hash_table, g_strdup("2"), g_strdup("-2"));
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_none_inout:
 * @hash_table: (inout) (element-type utf8 utf8) (transfer none):
 */
void
g_i_marshalling_tests_ghashtable_utf8_none_inout (GHashTable **hash_table)
{
    static GHashTable *new_hash_table = NULL;

    g_assert(strcmp(g_hash_table_lookup(*hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "2"), "-2") == 0);

    if (new_hash_table == NULL) {
        new_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(new_hash_table, "-1", "1");
        g_hash_table_insert(new_hash_table, "0", "0");
        g_hash_table_insert(new_hash_table, "1", "1");
    }

    *hash_table = new_hash_table;
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_container_inout:
 * @hash_table: (inout) (element-type utf8 utf8) (transfer container):
 */
void
g_i_marshalling_tests_ghashtable_utf8_container_inout (GHashTable **hash_table)
{
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "2"), "-2") == 0);

    g_hash_table_steal(*hash_table, "2");
    g_hash_table_steal(*hash_table, "1");
    g_hash_table_insert(*hash_table, "1", "1");
}

/**
 * g_i_marshalling_tests_ghashtable_utf8_full_inout:
 * @hash_table: (inout) (element-type utf8 utf8) (transfer full):
 */
void
g_i_marshalling_tests_ghashtable_utf8_full_inout (GHashTable **hash_table)
{
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "-1"), "1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "0"), "0") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "1"), "-1") == 0);
    g_assert(strcmp(g_hash_table_lookup(*hash_table, "2"), "-2") == 0);

    g_hash_table_steal(*hash_table, "2");
    g_hash_table_steal(*hash_table, "1");
    g_hash_table_insert(*hash_table, "1", g_strdup("1"));
}


/**
 * g_i_marshalling_tests_gvalue_return:
 * Returns: (transfer none):
 */
GValue *
g_i_marshalling_tests_gvalue_return (void)
{
    static GValue *value = NULL;

    if (value == NULL) {
        value = g_new0(GValue, 1);
        g_value_init(value, G_TYPE_INT);
        g_value_set_int(value, 42);
    }

    return value;
}

/**
 * g_i_marshalling_tests_gvalue_in:
 * @value: (transfer none):
 */
void
g_i_marshalling_tests_gvalue_in (GValue *value)
{
    g_assert(g_value_get_int(value) == 42);
}

/**
 * g_i_marshalling_tests_gvalue_out:
 * @value: (out) (transfer none):
 */
void
g_i_marshalling_tests_gvalue_out (GValue **value)
{
    static GValue *new_value = NULL;

    if (new_value == NULL) {
        new_value = g_new0(GValue, 1);
        g_value_init(new_value, G_TYPE_INT);
        g_value_set_int(new_value, 42);
    }

    *value = new_value;
}

/**
 * g_i_marshalling_tests_gvalue_inout:
 * @value: (inout) (transfer none):
 */
void
g_i_marshalling_tests_gvalue_inout (GValue **value)
{
    g_assert(g_value_get_int(*value) == 42);
    g_value_unset(*value);
    g_value_init(*value, G_TYPE_STRING);
    g_value_set_string(*value, "42");
}


/**
 * g_i_marshalling_tests_gclosure_in:
 * @closure: (transfer none):
 */
void
g_i_marshalling_tests_gclosure_in (GClosure *closure)
{
    GValue return_value = {0, };

    g_value_init (&return_value, G_TYPE_INT);

    g_closure_invoke (closure,
            &return_value,
            0, NULL,
            NULL);

    g_assert(g_value_get_int (&return_value) == 42);

    g_value_unset(&return_value);
}

gpointer
g_i_marshalling_tests_pointer_in_return (gpointer pointer)
{
    return pointer;
}

GType
g_i_marshalling_tests_genum_get_type (void)
{
    static GType type = 0;
    if (G_UNLIKELY(type == 0)) {
        static const GEnumValue values[] = {
            { G_I_MARSHALLING_TESTS_GENUM_VALUE1, "G_I_MARSHALLING_TESTS_GENUM_VALUE1", "value1" },
            { G_I_MARSHALLING_TESTS_GENUM_VALUE2, "G_I_MARSHALLING_TESTS_GENUM_VALUE2", "value2" },
            { G_I_MARSHALLING_TESTS_GENUM_VALUE3, "G_I_MARSHALLING_TESTS_GENUM_VALUE3", "value3" },
            { 0, NULL, NULL }
        };
        type = g_enum_register_static (g_intern_static_string ("GIMarshallingTestsGEnum"), values);
    }

    return type;
}

GIMarshallingTestsEnum
g_i_marshalling_tests_genum_return (void)
{
    return G_I_MARSHALLING_TESTS_GENUM_VALUE3;
}

void
g_i_marshalling_tests_genum_in (GIMarshallingTestsGEnum enum_)
{
    g_assert(enum_ == G_I_MARSHALLING_TESTS_GENUM_VALUE3);
}

/**
 * g_i_marshalling_tests_genum_out:
 * @enum_: (out):
 */
void
g_i_marshalling_tests_genum_out (GIMarshallingTestsGEnum *enum_)
{
    *enum_ = G_I_MARSHALLING_TESTS_GENUM_VALUE3;
}

/**
 * g_i_marshalling_tests_genum_inout:
 * @enum_: (inout):
 */
void
g_i_marshalling_tests_genum_inout (GIMarshallingTestsGEnum *enum_)
{
    g_assert(*enum_ == G_I_MARSHALLING_TESTS_GENUM_VALUE3);
    *enum_ = G_I_MARSHALLING_TESTS_GENUM_VALUE1;
}


GIMarshallingTestsEnum
g_i_marshalling_tests_enum_return (void)
{
    return G_I_MARSHALLING_TESTS_ENUM_VALUE3;
}

void
g_i_marshalling_tests_enum_in (GIMarshallingTestsEnum enum_)
{
    g_assert(enum_ == G_I_MARSHALLING_TESTS_ENUM_VALUE3);
}

/**
 * g_i_marshalling_tests_enum_out:
 * @enum_: (out):
 */
void
g_i_marshalling_tests_enum_out (GIMarshallingTestsEnum *enum_)
{
    *enum_ = G_I_MARSHALLING_TESTS_ENUM_VALUE3;
}

/**
 * g_i_marshalling_tests_enum_inout:
 * @enum_: (inout):
 */
void
g_i_marshalling_tests_enum_inout (GIMarshallingTestsEnum *enum_)
{
    g_assert(*enum_ == G_I_MARSHALLING_TESTS_ENUM_VALUE3);
    *enum_ = G_I_MARSHALLING_TESTS_ENUM_VALUE1;
}


GType
g_i_marshalling_tests_flags_get_type (void)
{
    static GType type = 0;
    if (G_UNLIKELY(type == 0)) {
        static const GFlagsValue values[] = {
            { G_I_MARSHALLING_TESTS_FLAGS_VALUE1, "G_I_MARSHALLING_TESTS_FLAGS_VALUE1", "value1" },
            { G_I_MARSHALLING_TESTS_FLAGS_VALUE2, "G_I_MARSHALLING_TESTS_FLAGS_VALUE2", "value2" },
            { G_I_MARSHALLING_TESTS_FLAGS_VALUE3, "G_I_MARSHALLING_TESTS_FLAGS_VALUE3", "value3" },
            { 0, NULL, NULL }
        };
        type = g_flags_register_static (g_intern_static_string ("GIMarshallingTestsFlags"), values);
    }

    return type;
}

GIMarshallingTestsFlags
g_i_marshalling_tests_flags_return (void)
{
    return G_I_MARSHALLING_TESTS_FLAGS_VALUE2;
}

void
g_i_marshalling_tests_flags_in (GIMarshallingTestsFlags flags_)
{
    g_assert(flags_ == G_I_MARSHALLING_TESTS_FLAGS_VALUE2);
}

void
g_i_marshalling_tests_flags_in_zero (GIMarshallingTestsFlags flags)
{
    g_assert(flags == 0);
}

/**
 * g_i_marshalling_tests_flags_out:
 * @flags_: (out):
 */
void
g_i_marshalling_tests_flags_out (GIMarshallingTestsFlags *flags_)
{
    *flags_ = G_I_MARSHALLING_TESTS_FLAGS_VALUE2;
}

/**
 * g_i_marshalling_tests_flags_inout:
 * @flags_: (inout):
 */
void
g_i_marshalling_tests_flags_inout (GIMarshallingTestsFlags *flags_)
{
    g_assert(*flags_ == G_I_MARSHALLING_TESTS_FLAGS_VALUE2);
    *flags_ = G_I_MARSHALLING_TESTS_FLAGS_VALUE1;
}


/**
 * g_i_marshalling_tests__simple_struct_return:
 * Returns: (transfer none):
 */
GIMarshallingTestsSimpleStruct *
g_i_marshalling_tests__simple_struct_return (void)
{
    static GIMarshallingTestsSimpleStruct *struct_ = NULL;

    if (struct_ == NULL) {
        struct_ = g_new(GIMarshallingTestsSimpleStruct, 1);

        struct_->long_ = 6;
        struct_->int8 = 7;
    }

    return struct_;
}

/**
 * g_i_marshalling_tests__simple_struct_in:
 * @struct_: (transfer none):
 */
void
g_i_marshalling_tests__simple_struct_in (GIMarshallingTestsSimpleStruct *struct_)
{
    g_assert(struct_->long_ == 6);
    g_assert(struct_->int8 == 7);
}

/**
 * g_i_marshalling_tests__simple_struct_out:
 * @struct_: (out) (transfer none):
 */
void
g_i_marshalling_tests__simple_struct_out (GIMarshallingTestsSimpleStruct **struct_)
{
    static GIMarshallingTestsSimpleStruct *new_struct = NULL;

    if (new_struct == NULL) {
        new_struct = g_new(GIMarshallingTestsSimpleStruct, 1);

        new_struct->long_ = 6;
        new_struct->int8 = 7;
    }

    *struct_ = new_struct;
}

/**
 * g_i_marshalling_tests__simple_struct_inout:
 * @struct_: (inout) (transfer none):
 */
void
g_i_marshalling_tests__simple_struct_inout (GIMarshallingTestsSimpleStruct **struct_)
{
    g_assert((*struct_)->long_ == 6);
    g_assert((*struct_)->int8 == 7);

    (*struct_)->long_ = 7;
    (*struct_)->int8 = 6;
}

void
g_i_marshalling_tests_simple_struct_method (GIMarshallingTestsSimpleStruct *struct_)
{
    g_assert(struct_->long_ == 6);
    g_assert(struct_->int8 == 7);
}


GType
g_i_marshalling_tests_pointer_struct_get_type (void)
{
    static GType type = 0;

    if (type == 0) {
        type = g_pointer_type_register_static ("GIMarshallingTestsPointerStruct");
    }

    return type;
}

/**
 * g_i_marshalling_tests__pointer_struct_return:
 * Returns: (transfer none):
 */
GIMarshallingTestsPointerStruct *
g_i_marshalling_tests__pointer_struct_return (void)
{
    static GIMarshallingTestsPointerStruct *struct_ = NULL;

    if (struct_ == NULL) {
        struct_ = g_new(GIMarshallingTestsPointerStruct, 1);

        struct_->long_ = 42;
    }

    return struct_;
}

/**
 * g_i_marshalling_tests__pointer_struct_in:
 * @struct_: (transfer none):
 */
void
g_i_marshalling_tests__pointer_struct_in (GIMarshallingTestsPointerStruct *struct_)
{
    g_assert(struct_->long_ == 42);
}

/**
 * g_i_marshalling_tests__pointer_struct_out:
 * @struct_: (out) (transfer none):
 */
void
g_i_marshalling_tests__pointer_struct_out (GIMarshallingTestsPointerStruct **struct_)
{
    static GIMarshallingTestsPointerStruct *new_struct = NULL;

    if (new_struct == NULL) {
        new_struct = g_new(GIMarshallingTestsPointerStruct, 1);

        new_struct->long_ = 42;
    }

    *struct_ = new_struct;
}

/**
 * g_i_marshalling_tests__pointer_struct_inout:
 * @struct_: (inout) (transfer none):
 */
void
g_i_marshalling_tests__pointer_struct_inout (GIMarshallingTestsPointerStruct **struct_)
{
    g_assert((*struct_)->long_ == 42);

    (*struct_)->long_ = 0;
}


static GIMarshallingTestsBoxedStruct *
g_i_marshalling_tests_boxed_struct_copy (GIMarshallingTestsBoxedStruct *struct_)
{
    GIMarshallingTestsBoxedStruct *new_struct;

    new_struct = g_slice_new (GIMarshallingTestsBoxedStruct);

    *new_struct = *struct_;

    return new_struct;
}

static void
g_i_marshalling_tests_boxed_struct_free (GIMarshallingTestsBoxedStruct *struct_)
{
    g_slice_free (GIMarshallingTestsBoxedStruct, struct_);
}

GType
g_i_marshalling_tests_boxed_struct_get_type (void)
{
    static GType type = 0;

    if (type == 0) {
        type = g_boxed_type_register_static ("GIMarshallingTestsBoxedStruct",
                (GBoxedCopyFunc) g_i_marshalling_tests_boxed_struct_copy,
                (GBoxedFreeFunc) g_i_marshalling_tests_boxed_struct_free);
    }

    return type;
}

GIMarshallingTestsBoxedStruct *
g_i_marshalling_tests_boxed_struct_new (void)
{
    return g_slice_new (GIMarshallingTestsBoxedStruct);
}

/**
 * g_i_marshalling_tests__boxed_struct_return:
 * Returns: (transfer none):
 */
GIMarshallingTestsBoxedStruct *
g_i_marshalling_tests__boxed_struct_return (void)
{
    static GIMarshallingTestsBoxedStruct *struct_ = NULL;

    if (struct_ == NULL) {
        struct_ = g_new(GIMarshallingTestsBoxedStruct, 1);

        struct_->long_ = 42;
        struct_->g_strv = g_new0(gchar*, 4);
        struct_->g_strv[0] = g_strdup("0");
        struct_->g_strv[1] = g_strdup("1");
        struct_->g_strv[2] = g_strdup("2");
        struct_->g_strv[3] = NULL;
    }

    return struct_;
}

/**
 * g_i_marshalling_tests__boxed_struct_in:
 * @struct_: (transfer none):
 */
void
g_i_marshalling_tests__boxed_struct_in (GIMarshallingTestsBoxedStruct *struct_)
{
    g_assert(struct_->long_ == 42);
}

/**
 * g_i_marshalling_tests__boxed_struct_out:
 * @struct_: (out) (transfer none):
 */
void
g_i_marshalling_tests__boxed_struct_out (GIMarshallingTestsBoxedStruct **struct_)
{
    static GIMarshallingTestsBoxedStruct *new_struct = NULL;

    if (new_struct == NULL) {
        new_struct = g_new(GIMarshallingTestsBoxedStruct, 1);

        new_struct->long_ = 42;
    }

    *struct_ = new_struct;
}

/**
 * g_i_marshalling_tests__boxed_struct_inout:
 * @struct_: (inout) (transfer none):
 */
void
g_i_marshalling_tests__boxed_struct_inout (GIMarshallingTestsBoxedStruct **struct_)
{
    g_assert((*struct_)->long_ == 42);

    (*struct_)->long_ = 0;
}

static GIMarshallingTestsUnion *
g_i_marshalling_tests_union_copy (GIMarshallingTestsUnion *union_)
{
    GIMarshallingTestsUnion *new_union;

    new_union = g_slice_new (GIMarshallingTestsUnion);

    *new_union = *union_;

    return new_union;
}

static void
g_i_marshalling_tests_union_free (GIMarshallingTestsUnion *union_)
{
    g_slice_free (GIMarshallingTestsUnion, union_);
}

GType
g_i_marshalling_tests_union_get_type (void)
{
    static GType type = 0;

    if (type == 0) {
        type = g_boxed_type_register_static ("GIMarshallingTestsUnion",
                (GBoxedCopyFunc) g_i_marshalling_tests_union_copy,
                (GBoxedFreeFunc) g_i_marshalling_tests_union_free);
    }

    return type;
}

/**
 * g_i_marshalling_tests__union_return:
 * Returns: (transfer none):
 */
GIMarshallingTestsUnion *
g_i_marshalling_tests__union_return (void)
{
    static GIMarshallingTestsUnion *union_ = NULL;

    if (union_ == NULL) {
        union_ = g_new(GIMarshallingTestsUnion, 1);

        union_->long_ = 42;
    }

    return union_;
}

/**
 * g_i_marshalling_tests__union_in:
 * @union_: (transfer none):
 */
void
g_i_marshalling_tests__union_in (GIMarshallingTestsUnion *union_)
{
    g_assert(union_->long_ == 42);
}

/**
 * g_i_marshalling_tests__union_out:
 * @union_: (out) (transfer none):
 */
void
g_i_marshalling_tests__union_out (GIMarshallingTestsUnion **union_)
{
    static GIMarshallingTestsUnion *new_union = NULL;

    if (new_union == NULL) {
        new_union = g_new(GIMarshallingTestsUnion, 1);

        new_union->long_ = 42;
    }

    *union_ = new_union;
}

/**
 * g_i_marshalling_tests__union_inout:
 * @union_: (inout) (transfer none):
 */
void
g_i_marshalling_tests__union_inout (GIMarshallingTestsUnion **union_)
{
    g_assert((*union_)->long_ == 42);

    (*union_)->long_ = 0;
}

void
g_i_marshalling_tests_union_method (GIMarshallingTestsUnion *union_)
{
    g_assert(union_->long_ == 42);
}



enum
{
	PROP_0,
	PROP_INT_
};

static void g_i_marshalling_tests_object_real_method_with_default_implementation (
        GIMarshallingTestsObject *self, gint8 in);

G_DEFINE_TYPE (GIMarshallingTestsObject, g_i_marshalling_tests_object, G_TYPE_OBJECT);

static void
g_i_marshalling_tests_object_init (GIMarshallingTestsObject *object)
{
}

static void
g_i_marshalling_tests_object_finalize (GObject *object)
{
	G_OBJECT_CLASS (g_i_marshalling_tests_object_parent_class)->finalize (object);
}

static void
g_i_marshalling_tests_object_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (G_I_MARSHALLING_TESTS_IS_OBJECT (object));

	switch (prop_id) {
        case PROP_INT_:
            G_I_MARSHALLING_TESTS_OBJECT (object)->int_ = g_value_get_int (value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
	}
}

static void
g_i_marshalling_tests_object_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (G_I_MARSHALLING_TESTS_IS_OBJECT (object));

	switch (prop_id) {
        case PROP_INT_:
            g_value_set_int (value, G_I_MARSHALLING_TESTS_OBJECT (object)->int_);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
	}
}

static void
g_i_marshalling_tests_object_class_init (GIMarshallingTestsObjectClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
#if 0
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);
#endif

	object_class->finalize = g_i_marshalling_tests_object_finalize;
	object_class->set_property = g_i_marshalling_tests_object_set_property;
	object_class->get_property = g_i_marshalling_tests_object_get_property;

	g_object_class_install_property (object_class, PROP_INT_,
         g_param_spec_int ("int", "Integer", "An integer", G_MININT, G_MAXINT, 0,
              G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));

    klass->method_with_default_implementation = g_i_marshalling_tests_object_real_method_with_default_implementation;
}


void
g_i_marshalling_tests_object_static_method (void)
{
}

void
g_i_marshalling_tests_object_method (GIMarshallingTestsObject *object)
{
	g_return_if_fail (G_I_MARSHALLING_TESTS_IS_OBJECT (object));
    g_assert (object->int_ == 42);
}

void
g_i_marshalling_tests_object_overridden_method (GIMarshallingTestsObject *object)
{
	g_return_if_fail (G_I_MARSHALLING_TESTS_IS_OBJECT (object));
    g_assert (object->int_ == 0);
}

GIMarshallingTestsObject *
g_i_marshalling_tests_object_new (gint int_)
{
    return g_object_new (G_I_MARSHALLING_TESTS_TYPE_OBJECT, "int", int_, NULL);
}

/**
 * g_i_marshalling_tests_object_method_array_in:
 * @ints: (array length=length):
 */
void
g_i_marshalling_tests_object_method_array_in (GIMarshallingTestsObject *object, const gint *ints, gint length)
{
    g_assert(length == 4);
    g_assert(ints[0] == -1);
    g_assert(ints[1] == 0);
    g_assert(ints[2] == 1);
    g_assert(ints[3] == 2);
}

/**
 * g_i_marshalling_tests_object_method_array_out:
 * @ints: (out) (array length=length) (transfer none):
 */
void
g_i_marshalling_tests_object_method_array_out (GIMarshallingTestsObject *object, gint **ints, gint *length)
{
    static gint values[] = {-1, 0, 1, 2};

    *length = 4;
    *ints = values;
}

/**
 * g_i_marshalling_tests_object_method_array_inout:
 * @ints: (inout) (array length=length) (transfer none):
 * @length: (inout):
 */
void
g_i_marshalling_tests_object_method_array_inout (GIMarshallingTestsObject *object, gint **ints, gint *length)
{
    static gint values[] = {-2, -1, 0, 1, 2};

    g_assert(*length == 4);
    g_assert((*ints)[0] == -1);
    g_assert((*ints)[1] == 0);
    g_assert((*ints)[2] == 1);
    g_assert((*ints)[3] == 2);

    *length = 5;
    *ints = values;
}

/**
 * g_i_marshalling_tests_object_method_array_return:
 * Returns: (array length=length):
 */
const gint *
g_i_marshalling_tests_object_method_array_return (GIMarshallingTestsObject *object, gint *length)
{
    static gint ints[] = {-1, 0, 1, 2};

    *length = 4;
    return ints;
}

/**
 * g_i_marshalling_tests_object_method_int8_in:
 * @in: (in):
 */
void
g_i_marshalling_tests_object_method_int8_in (GIMarshallingTestsObject *self, gint8 in)
{
  G_I_MARSHALLING_TESTS_OBJECT_GET_CLASS (self)->method_int8_in (self, in);
}

/**
 * g_i_marshalling_tests_object_method_int8_out:
 * @out: (out):
 */
void
g_i_marshalling_tests_object_method_int8_out (GIMarshallingTestsObject *self, gint8 *out)
{
  G_I_MARSHALLING_TESTS_OBJECT_GET_CLASS (self)->method_int8_out (self, out);
}

/**
 * g_i_marshalling_tests_object_method_with_default_implementation:
 * @in: (in):
 */
void
g_i_marshalling_tests_object_method_with_default_implementation (GIMarshallingTestsObject *self, gint8 in)
{
    G_I_MARSHALLING_TESTS_OBJECT_GET_CLASS (self)->method_with_default_implementation (self, in);
}

static void
g_i_marshalling_tests_object_real_method_with_default_implementation (GIMarshallingTestsObject *self, gint8 in)
{
    GValue val = {0, };
    g_value_init (&val, G_TYPE_INT);
    g_value_set_int (&val, in);
    g_object_set_property (G_OBJECT (self), "int", &val);
}


/**
 * g_i_marshalling_tests__object_none_return:
 * Returns: (transfer none):
 */
GIMarshallingTestsObject *
g_i_marshalling_tests__object_none_return (void)
{
    static GIMarshallingTestsObject *object = NULL;

    if (object == NULL) {
        object = g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
    }

    return object;
}

/**
 * g_i_marshalling_tests__object_full_return:
 * Returns: (transfer full):
 */
GIMarshallingTestsObject *
g_i_marshalling_tests__object_full_return (void)
{
    return g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
}

/**
 * g_i_marshalling_tests__object_none_in:
 * @object: (transfer none):
 */
void
g_i_marshalling_tests__object_none_in (GIMarshallingTestsObject *object)
{
    g_assert(object->int_ == 42);
}

/**
 * g_i_marshalling_tests__object_full_in:
 * @object: (transfer full):
 */
void
g_i_marshalling_tests__object_full_in (GIMarshallingTestsObject *object)
{
    g_assert(object->int_ == 42);
    g_object_unref(object);
}

/**
 * g_i_marshalling_tests__object_none_out:
 * @object: (out) (transfer none):
 */
void
g_i_marshalling_tests__object_none_out (GIMarshallingTestsObject **object)
{
    static GIMarshallingTestsObject *new_object = NULL;

    if (new_object == NULL) {
        new_object = g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
    }

    *object = new_object;
}

/**
 * g_i_marshalling_tests__object_full_out:
 * @object: (out) (transfer full):
 */
void
g_i_marshalling_tests__object_full_out (GIMarshallingTestsObject **object)
{
    *object = g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
}

/**
 * g_i_marshalling_tests__object_none_inout:
 * @object: (inout) (transfer none):
 */
void
g_i_marshalling_tests__object_none_inout (GIMarshallingTestsObject **object)
{
    static GIMarshallingTestsObject *new_object = NULL;

    g_assert((*object)->int_ == 42);

    if (new_object == NULL) {
        new_object = g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
        new_object->int_ = 0;
    }

    *object = new_object;
}

/**
 * g_i_marshalling_tests__object_full_inout:
 * @object: (inout) (transfer full):
 */
void
g_i_marshalling_tests__object_full_inout (GIMarshallingTestsObject **object)
{
    g_assert((*object)->int_ == 42);
    g_object_unref(*object);

    *object = g_object_new(G_I_MARSHALLING_TESTS_TYPE_OBJECT, NULL);
}

/**
 * g_i_marshalling_tests__object_inout_same:
 * @object: (inout):
 */
void
g_i_marshalling_tests__object_inout_same (GIMarshallingTestsObject **object)
{
    g_assert((*object)->int_ == 42);
    (*object)->int_ = 0;
}

/**
 * g_i_marshalling_tests__object_test_int8_in:
 * @in: (in):
 */
void
g_i_marshalling_tests__object_int8_in (GIMarshallingTestsObject *object, gint8 in)
{
  g_i_marshalling_tests_object_method_int8_in (object, in);
}

/**
 * g_i_marshalling_tests__object_test_int8_out:
 * @out: (out):
 */
void
g_i_marshalling_tests__object_int8_out (GIMarshallingTestsObject *object, gint8 *out)
{
  g_i_marshalling_tests_object_method_int8_out (object, out);
}


G_DEFINE_TYPE (GIMarshallingTestsSubObject, g_i_marshalling_tests_sub_object, G_I_MARSHALLING_TESTS_TYPE_OBJECT);

static void
g_i_marshalling_tests_sub_object_init (GIMarshallingTestsSubObject *object)
{
}

static void
g_i_marshalling_tests_sub_object_finalize (GObject *object)
{
	G_OBJECT_CLASS(g_i_marshalling_tests_sub_object_parent_class)->finalize(object);
}

static void
g_i_marshalling_tests_sub_object_class_init (GIMarshallingTestsSubObjectClass *klass)
{
	G_OBJECT_CLASS(klass)->finalize = g_i_marshalling_tests_sub_object_finalize;
}

void
g_i_marshalling_tests_sub_object_sub_method (GIMarshallingTestsSubObject *object)
{
    g_assert(G_I_MARSHALLING_TESTS_OBJECT(object)->int_ == 0);
}

void
g_i_marshalling_tests_sub_object_overwritten_method (GIMarshallingTestsSubObject *object)
{
    g_assert(G_I_MARSHALLING_TESTS_OBJECT(object)->int_ == 0);
}

/* Interfaces */

static void
g_i_marshalling_tests_interface_class_init(void *g_iface)
{
}

GType
g_i_marshalling_tests_interface_get_type(void)
{
    static GType type = 0;
    if (type == 0) {
        type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                              "GIMarshallingTestsInterface",
                                              sizeof (GIMarshallingTestsInterfaceIface),
                                              (GClassInitFunc) g_i_marshalling_tests_interface_class_init,
                                              0, NULL, 0);
    }

    return type;
}

/**
 * g_i_marshalling_tests_interface_test_int8_in:
 * @in: (in):
 */
void
g_i_marshalling_tests_interface_test_int8_in (GIMarshallingTestsInterface *self, gint8 in)
{
  G_I_MARSHALLING_TESTS_INTERFACE_GET_IFACE (self)->test_int8_in (self, in);
}

/**
 * g_i_marshalling_tests_test_interface_test_int8_in:
 * @in: (in):
 */
void
g_i_marshalling_tests_test_interface_test_int8_in (GIMarshallingTestsInterface *test_iface, gint8 in)
{
  g_i_marshalling_tests_interface_test_int8_in (test_iface, in);
}


/**
 * g_i_marshalling_tests_int_out_out:
 * int0: (out):
 * int1: (out):
 */
void
g_i_marshalling_tests_int_out_out (gint *int0, gint *int1)
{
    *int0 = 6;
    *int1 = 7;
}

/**
 * g_i_marshalling_tests_int_return_out:
 * int_: (out):
 */
gint
g_i_marshalling_tests_int_return_out (gint *int_)
{
    *int_ = 7;
    return 6;
}


static GIMarshallingTestsOverridesStruct *
g_i_marshalling_tests_overrides_struct_copy (GIMarshallingTestsOverridesStruct *struct_)
{
    GIMarshallingTestsOverridesStruct *new_struct;

    new_struct = g_slice_new (GIMarshallingTestsOverridesStruct);

    *new_struct = *struct_;

    return new_struct;
}

static void
g_i_marshalling_tests_overrides_struct_free (GIMarshallingTestsOverridesStruct *struct_)
{
    g_slice_free (GIMarshallingTestsOverridesStruct, struct_);
}

GType
g_i_marshalling_tests_overrides_struct_get_type (void)
{
    static GType type = 0;

    if (type == 0) {
        type = g_boxed_type_register_static ("GIMarshallingTestsOverridesStruct",
                (GBoxedCopyFunc) g_i_marshalling_tests_overrides_struct_copy,
                (GBoxedFreeFunc) g_i_marshalling_tests_overrides_struct_free);
    }

    return type;
}

GIMarshallingTestsOverridesStruct *
g_i_marshalling_tests_overrides_struct_new (void)
{
    return g_slice_new (GIMarshallingTestsOverridesStruct);
}

glong
g_i_marshalling_tests_overrides_struct_method (GIMarshallingTestsOverridesStruct *struct_)
{
    return 42;
}


/**
 * g_i_marshalling_tests__overrides_struct_return:
 *
 * Returns: (transfer full):
 */
GIMarshallingTestsOverridesStruct *
g_i_marshalling_tests__overrides_struct_return (void)
{
    return g_i_marshalling_tests_overrides_struct_new();
}


G_DEFINE_TYPE (GIMarshallingTestsOverridesObject, g_i_marshalling_tests_overrides_object, G_TYPE_OBJECT);

static void
g_i_marshalling_tests_overrides_object_init (GIMarshallingTestsOverridesObject *object)
{
}

static void
g_i_marshalling_tests_overrides_object_finalize (GObject *object)
{
	G_OBJECT_CLASS (g_i_marshalling_tests_overrides_object_parent_class)->finalize (object);
}

static void
g_i_marshalling_tests_overrides_object_class_init (GIMarshallingTestsOverridesObjectClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
#if 0
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);
#endif

	object_class->finalize = g_i_marshalling_tests_overrides_object_finalize;
}

GIMarshallingTestsOverridesObject *
g_i_marshalling_tests_overrides_object_new (void)
{
    return g_object_new (G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT, NULL);
}

glong
g_i_marshalling_tests_overrides_object_method (GIMarshallingTestsOverridesObject *object)
{
    return 42;
}


/**
 * g_i_marshalling_tests__overrides_object_return:
 *
 * Returns: (transfer full):
 */
GIMarshallingTestsOverridesObject *
g_i_marshalling_tests__overrides_object_return (void)
{
    return g_object_new (G_I_MARSHALLING_TESTS_TYPE_OVERRIDES_OBJECT, NULL);
}
