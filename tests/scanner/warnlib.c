/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

#include "config.h"

#include "warnlib.h"

GQuark
warnlib_unpaired_error_quark (void)
{
  return g_quark_from_static_string ("warnlib-unpaired-error");
}

gboolean
warnlib_throw_unpaired (GError **error)
{
  g_set_error_literal (error, warnlib_unpaired_error_quark (), 0,
                       "Unpaired error");
  return FALSE;
}

