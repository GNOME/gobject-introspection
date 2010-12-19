#!/bin/sh
GLIBDIR=$1
sources=`ls $GLIBDIR/gobject/*.c $GLIBDIR/gobject/*.h | \
    grep -v 'gobject_trace.h' | \
    grep -v 'stamp-'`
./g-ir-annotation-tool --extract \
    -DGOBJECT_COMPILATION \
    -I$GLIBDIR \
    -I$GLIBDIR/glib \
    -I$GLIBDIR/gobject \
    -I$GLIBDIR/gmodule \
    $sources
