import os
import re

def process_in(src, dest, vars, mode):
    if mode == 1:
        RE_VARS = re.compile(r'%(\w+?)%')
    if mode == 2:
        RE_VARS = re.compile(r'@(\w+?)@')
    with open(src, 'r') as s:
        with open(dest, 'w') as d:
            for i in s:
                i = RE_VARS.sub(lambda x: str(vars[x.group(1)]), i)
                d.write(i)

def parent_dir(path):
    if not os.path.isabs(path):
        path = os.path.abspath(path)
    if os.path.isfile(path):
        path = os.path.dirname(path)
    return os.path.split(path)[0]
