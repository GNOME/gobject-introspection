#!/usr/bin/env python3

import sys
from glob import glob

output_file = sys.argv[1]
glob_strs = sys.argv[2].split(',')
filter_str = tuple(sys.argv[3].split(','))
extra_files = sys.argv[4:]

with open(output_file, 'w') as file_:
    for s in glob_strs:
        for f in glob(s):
            if filter_str == ' ' or not f.endswith(filter_str):
                file_.write(f + '\n')
    file_.write('\n'.join(extra_files))
