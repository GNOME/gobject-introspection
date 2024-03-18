/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* This file gets installed, so we can't assume config.h is available */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "regress-unix.h"

#ifdef G_OS_UNIX

dev_t
regress_unix_test_devt (dev_t in)
{
  return in;
}

gid_t
regress_unix_test_gidt (gid_t in)
{
  return in;
}

pid_t
regress_unix_test_pidt (pid_t in)
{
  return in;
}

socklen_t
regress_unix_test_socklent (socklen_t in)
{
  return in;
}

uid_t
regress_unix_test_uidt (uid_t in)
{
  return in;
}

#endif
