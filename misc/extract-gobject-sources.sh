#!/bin/sh
GLIBDIR=$1
tools/g-ir-annotation-tool --extract \
    -DGOBJECT_COMPILATION \
    -I$GLIBDIR \
    -I$GLIBDIR/glib \
    -I$GLIBDIR/gobject \
    -I$GLIBDIR/gmodule \
    $GLIBDIR/gobject/*.c $GLIBDIR/gobject/*.h
