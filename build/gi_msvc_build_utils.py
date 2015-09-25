import os

def parent_dir(path):
    if not os.path.isabs(path):
        path = os.path.abspath(path)
    if os.path.isfile(path):
        path = os.path.dirname(path)
    return os.path.split(path)[0]
