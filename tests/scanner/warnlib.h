/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

#ifndef __WARNLIB_H__
#define __WARNLIB_H__

#include <gio/gio.h>

#define WARNLIB_UNPAIRED_ERROR (warnlib_unpaired_error_quark ())
GQuark warnlib_unpaired_error_quark (void);

gboolean warnlib_throw_unpaired (GError **error);

#endif
