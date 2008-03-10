#!/bin/sh

cat $1 | sed -e '1 i\const char gmetadata_header[] =\n' -e 's/\\/\\\\/g' -e 's/\"/\\\"/g' -e 's/.*/\"&\\n\"/' -e '$ a\;' > $2
