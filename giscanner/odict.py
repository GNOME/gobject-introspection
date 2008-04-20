# odict - an ordered dictionary

from UserDict import DictMixin


class odict(DictMixin):
    def __init__(self):
        self._items = {}
        self._keys = []

    def __setitem__(self, key, value):
        if key not in self._items:
            self._keys.append(key)
        self._items[key] = value

    def __getitem__(self, key):
        return self._items[key]

    def __delitem__(self, key):
        del self._items[key]
        self._keys.remove(key)

    def keys(self):
        return self._keys[:]
