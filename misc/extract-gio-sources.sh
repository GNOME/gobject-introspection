#!/bin/sh
GLIBDIR=$1
./g-ir-annotation-tool --extract \
    -DGIO_COMPILATION \
    -I$GLIBDIR \
    -I$GLIBDIR/glib \
    -I$GLIBDIR/gobject \
    -I$GLIBDIR/gmodule \
    -I$GLIBDIR/gio \
    $GLIBDIR/gio/*.c $GLIBDIR/gio/*.h
