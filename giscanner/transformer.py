# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

import os
import sys

from .ast import (Bitfield, Callback, Enum, Function, Namespace, Member,
                  Parameter, Return, Struct, Field,
                  Type, Array, Alias, Interface, Class, Node, Union,
                  Varargs, Constant, type_name_from_ctype,
                  type_names, TYPE_STRING, BASIC_GIR_TYPES)
from .config import DATADIR, GIR_DIR, GIR_SUFFIX
from .glibast import GLibBoxed
from .girparser import GIRParser
from .odict import odict
from .sourcescanner import (
    SourceSymbol, ctype_name, CTYPE_POINTER,
    CTYPE_BASIC_TYPE, CTYPE_UNION, CTYPE_ARRAY, CTYPE_TYPEDEF,
    CTYPE_VOID, CTYPE_ENUM, CTYPE_FUNCTION, CTYPE_STRUCT,
    CSYMBOL_TYPE_FUNCTION, CSYMBOL_TYPE_TYPEDEF, CSYMBOL_TYPE_STRUCT,
    CSYMBOL_TYPE_ENUM, CSYMBOL_TYPE_UNION, CSYMBOL_TYPE_OBJECT,
    CSYMBOL_TYPE_MEMBER, CSYMBOL_TYPE_ELLIPSIS, CSYMBOL_TYPE_CONST,
    TYPE_QUALIFIER_CONST)
from .utils import to_underscores

_xdg_data_dirs = [x for x in os.environ.get('XDG_DATA_DIRS', '').split(':') \
                      + [DATADIR, '/usr/share'] if x]


class SkipError(Exception):
    pass


class Names(object):
    names = property(lambda self: self._names)
    aliases = property(lambda self: self._aliases)
    type_names = property(lambda self: self._type_names)
    ctypes = property(lambda self: self._ctypes)

    def __init__(self):
        super(Names, self).__init__()
        self._names = odict() # Maps from GIName -> (namespace, node)
        self._aliases = {} # Maps from GIName -> GIName
        self._type_names = {} # Maps from GTName -> (namespace, node)
        self._ctypes = {} # Maps from CType -> (namespace, node)


class Transformer(object):

    def __init__(self, cachestore, namespace_name, namespace_version):
        self._cachestore = cachestore
        self.generator = None
        self._namespace = Namespace(namespace_name, namespace_version)
        self._names = Names()
        self._pkg_config_packages = set()
        self._typedefs_ns = {}
        self._strip_prefix = ''
        self._includes = set()
        self._includepaths = []

    def get_names(self):
        return self._names

    def get_includes(self):
        return self._includes

    def set_strip_prefix(self, strip_prefix):
        self._strip_prefix = strip_prefix

    def get_strip_prefix(self):
        return self._strip_prefix

    def get_pkgconfig_packages(self):
        return self._pkg_config_packages

    def set_source_ast(self, src_ast):
        self.generator = src_ast

    def parse(self):
        nodes = []
        for symbol in self.generator.get_symbols():
            try:
                node = self._traverse_one(symbol)
            except SkipError:
                continue
            self._add_node(node)
        return self._namespace

    def set_include_paths(self, paths):
        self._includepaths = list(paths)

    def register_include(self, include):
        if include in self._includes:
            return
        filename = self._find_include(include)
        self._parse_include(filename)
        self._includes.add(include)

    # Private

    def _find_include(self, include):
        searchdirs = self._includepaths[:]
        for path in _xdg_data_dirs:
            searchdirs.append(os.path.join(path, GIR_SUFFIX))
        searchdirs.append(GIR_DIR)

        girname = '%s-%s.gir' % (include.name, include.version)
        for d in searchdirs:
            path = os.path.join(d, girname)
            if os.path.exists(path):
                return path
        sys.stderr.write("Couldn't find include %r (search path: %r)\n"\
                         % (girname, searchdirs))
        sys.exit(1)

    def _parse_include(self, filename):
        parser = self._cachestore.load(filename)
        if parser is None:
            parser = GIRParser()
            parser.set_include_parsing(True)
            parser.parse(filename)
            self._cachestore.store(filename, parser)

        for include in parser.get_includes():
            self.register_include(include)

        for pkg in parser.get_pkgconfig_packages():
            self._pkg_config_packages.add(pkg)
        namespace = parser.get_namespace()
        nsname = namespace.name
        for node in namespace.nodes:
            if isinstance(node, Alias):
                self._names.aliases[node.name] = (nsname, node)
            elif isinstance(node, (GLibBoxed, Interface, Class)):
                self._names.type_names[node.type_name] = (nsname, node)
            giname = '%s.%s' % (nsname, node.name)
            self._names.names[giname] = (nsname, node)
            if hasattr(node, 'ctype'):
                self._names.ctypes[node.ctype] = (nsname, node)
            elif hasattr(node, 'symbol'):
                self._names.ctypes[node.symbol] = (nsname, node)

    def _add_node(self, node):
        if node is None:
            return
        if node.name.startswith('_'):
            return
        self._namespace.nodes.append(node)
        self._names.names[node.name] = (None, node)

    def _strip_namespace_func(self, name):
        prefix = self._namespace.name.lower() + '_'
        if name.lower().startswith(prefix):
            name = name[len(prefix):]
        else:
            prefix = to_underscores(self._namespace.name).lower() + '_'
            if name.lower().startswith(prefix):
                name = name[len(prefix):]
        return self.remove_prefix(name, isfunction=True)

    def remove_prefix(self, name, isfunction=False):
        # when --strip-prefix=g:
        #   GHashTable -> HashTable
        #   g_hash_table_new -> hash_table_new
        prefix = self._strip_prefix.lower()
        if isfunction:
            prefix += '_'
        if len(name) > len(prefix) and name.lower().startswith(prefix):
            name = name[len(prefix):]

        while name.startswith('_'):
            name = name[1:]
        return name

    def _traverse_one(self, symbol, stype=None):
        assert isinstance(symbol, SourceSymbol), symbol

        if stype is None:
            stype = symbol.type
        if stype == CSYMBOL_TYPE_FUNCTION:
            return self._create_function(symbol)
        elif stype == CSYMBOL_TYPE_TYPEDEF:
            return self._create_typedef(symbol)
        elif stype == CSYMBOL_TYPE_STRUCT:
            return self._create_struct(symbol)
        elif stype == CSYMBOL_TYPE_ENUM:
            return self._create_enum(symbol)
        elif stype == CSYMBOL_TYPE_OBJECT:
            return self._create_object(symbol)
        elif stype == CSYMBOL_TYPE_MEMBER:
            return self._create_member(symbol)
        elif stype == CSYMBOL_TYPE_UNION:
            return self._create_union(symbol)
        elif stype == CSYMBOL_TYPE_CONST:
            return self._create_const(symbol)
        else:
            raise NotImplementedError(
                'Transformer: unhandled symbol: %r' % (symbol, ))

    def _enum_common_prefix(self, symbol):
        def common_prefix(a, b):
            commonparts = []
            for aword, bword in zip(a.split('_'), b.split('_')):
                if aword != bword:
                    return '_'.join(commonparts) + '_'
                commonparts.append(aword)
            return min(a, b)

        # Nothing less than 2 has a common prefix
        if len(list(symbol.base_type.child_list)) < 2:
            return None
        prefix = None
        for child in symbol.base_type.child_list:
            if prefix is None:
                prefix = child.ident
            else:
                prefix = common_prefix(prefix, child.ident)
                if prefix == '':
                    return None
        return prefix

    def _create_enum(self, symbol):
        prefix = self._enum_common_prefix(symbol)
        if prefix:
            prefixlen = len(prefix)
        else:
            prefixlen = 0
        members = []
        for child in symbol.base_type.child_list:
            if prefixlen > 0:
                name = child.ident[prefixlen:]
            else:
                # Ok, the enum members don't have a consistent prefix
                # among them, so let's just remove the global namespace
                # prefix.
                name = self.remove_prefix(child.ident)
            members.append(Member(name.lower(),
                                  child.const_int,
                                  child.ident))

        enum_name = self.remove_prefix(symbol.ident)
        if symbol.base_type.is_bitfield:
            klass = Bitfield
        else:
            klass = Enum
        node = klass(enum_name, symbol.ident, members)
        self._names.type_names[symbol.ident] = (None, node)
        return node

    def _create_object(self, symbol):
        return Member(symbol.ident, symbol.base_type.name,
                      symbol.ident)

    def _type_is_callback(self, type):
        if isinstance(type, Callback):
            return True
        node = self._names.names.get(type.name)
        if node and isinstance(node[1], Callback):
            return True
        return False

    def _handle_closure(self, param, closure_idx, closure_param):
        if (closure_param.type.name == 'any' and
            closure_param.name.endswith('data')):
            param.closure_name = closure_param.name
            param.closure_index = closure_idx
            return True
        return False

    def _handle_destroy(self, param, destroy_idx, destroy_param):
        if (destroy_param.type.name == 'GLib.DestroyNotify' or
            destroy_param.type.ctype == 'GDestroyNotify'):
            param.destroy_name = destroy_param.name
            param.destroy_index = destroy_idx
            return True
        return False

    def _augment_callback_params(self, params):
        for i, param in enumerate(params):
            if not self._type_is_callback(param.type):
                continue

            # set a default scope
            if param.scope is None:
                param.scope = 'call'

            # j is the index where we look for closure/destroy to
            # group with the callback param
            j = i + 1
            if j == len(params):
                continue # no more args -> nothing to group
            # look at the param directly following for either a
            # closure or a destroy; only one of these will fire
            had_closure = self._handle_closure(param, j, params[j])
            had_destroy = self._handle_destroy(param, j, params[j])
            j += 1
            # are we out of params, or did we find neither?
            if j == len(params) or (not had_closure and not had_destroy):
                continue
            # we found either a closure or a destroy; check the
            # parameter following for the other
            if not had_closure:
                self._handle_closure(param, j, params[j])
            if not had_destroy:
                self._handle_destroy(param, j, params[j])

    def _create_function(self, symbol):
        parameters = list(self._create_parameters(symbol.base_type))
        return_ = self._create_return(symbol.base_type.base_type)
        self._augment_callback_params(parameters)
        name = self._strip_namespace_func(symbol.ident)
        func = Function(name, return_, parameters, symbol.ident)
        return func

    def _create_source_type(self, source_type):
        if source_type is None:
            return 'None'
        if source_type.type == CTYPE_VOID:
            value = 'void'
        elif source_type.type == CTYPE_BASIC_TYPE:
            value = source_type.name
        elif source_type.type == CTYPE_TYPEDEF:
            value = source_type.name
        elif source_type.type == CTYPE_ARRAY:
            return self._create_source_type(source_type.base_type)
        elif source_type.type == CTYPE_POINTER:
            value = self._create_source_type(source_type.base_type) + '*'
        else:
            value = 'any'
        return value

    def _create_parameters(self, base_type):

        # warn if we see annotations for unknown parameters
        param_names = set(child.ident for child in base_type.child_list)
        for child in base_type.child_list:
            yield self._create_parameter(child)

    def _create_member(self, symbol):
        source_type = symbol.base_type
        if (source_type.type == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_callback(symbol)
        elif source_type.type == CTYPE_STRUCT and source_type.name is None:
            node = self._create_struct(symbol, anonymous=True)
        elif source_type.type == CTYPE_UNION and source_type.name is None:
            node = self._create_union(symbol, anonymous=True)
        else:
            # Special handling for fields; we don't have annotations on them
            # to apply later, yet.
            if source_type.type == CTYPE_ARRAY:
                ctype = self._create_source_type(source_type)
                canonical_ctype = self._canonicalize_ctype(ctype)
                if canonical_ctype[-1] == '*':
                    derefed_name = canonical_ctype[:-1]
                else:
                    derefed_name = canonical_ctype
                derefed_name = self.resolve_param_type(derefed_name)
                ftype = Array(None, ctype, self.parse_ctype(derefed_name))
                child_list = list(symbol.base_type.child_list)
                ftype.zeroterminated = False
                if child_list:
                    ftype.size = '%d' % (child_list[0].const_int, )
            else:
                ftype = self._create_type(symbol.base_type,
                                          is_param=False, is_retval=False)
            ftype = self.resolve_param_type(ftype)
            # Fields are assumed to be read-write
            # (except for Objects, see also glibtransformer.py)
            node = Field(symbol.ident, ftype, ftype.name,
                         readable=True, writable=True, bits=symbol.const_int)
        return node

    def _create_typedef(self, symbol):
        ctype = symbol.base_type.type
        if (ctype == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_typedef_callback(symbol)
        elif (ctype == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_STRUCT):
            node = self._create_typedef_struct(symbol, disguised=True)
        elif ctype == CTYPE_STRUCT:
            node = self._create_typedef_struct(symbol)
        elif ctype == CTYPE_UNION:
            node = self._create_typedef_union(symbol)
        elif ctype == CTYPE_ENUM:
            return self._create_enum(symbol)
        elif ctype in (CTYPE_TYPEDEF,
                       CTYPE_POINTER,
                       CTYPE_BASIC_TYPE,
                       CTYPE_VOID):
            name = self.remove_prefix(symbol.ident)
            if symbol.base_type.name:
                target = self.remove_prefix(symbol.base_type.name)
            else:
                target = 'none'
            if name in type_names:
                return None
            return Alias(name, target, ctype=symbol.ident)
        else:
            raise NotImplementedError(
                "symbol %r of type %s" % (symbol.ident, ctype_name(ctype)))
        return node

    def _canonicalize_ctype(self, ctype):
        # First look up the ctype including any pointers;
        # a few type names like 'char*' have their own aliases
        # and we need pointer information for those.
        firstpass = type_name_from_ctype(ctype)

        # If we have a particular alias for this, skip deep
        # canonicalization to prevent changing
        # e.g. char* -> int8*
        if firstpass != ctype:
            return firstpass

        # We're also done if the type is already a fundamental
        # known type, or there are no pointers.
        if ctype in type_names or not firstpass.endswith('*'):
            return firstpass

        # We have a pointer type.
        # Strip the end pointer, canonicalize our base type
        base = firstpass[:-1]
        canonical_base = self._canonicalize_ctype(base)

        # Append the pointer again
        canonical = canonical_base + '*'

        return canonical

    def parse_ctype(self, ctype, is_member=False):
        canonical = self._canonicalize_ctype(ctype)

        # Remove all pointers - we require standard calling
        # conventions.  For example, an 'int' is always passed by
        # value (unless it's out or inout).
        derefed_typename = canonical.replace('*', '')

        # Preserve "pointerness" of struct/union members
        if (is_member and canonical.endswith('*') and
            derefed_typename in BASIC_GIR_TYPES):
            return 'any'
        else:
            return derefed_typename

    def _create_type(self, source_type, is_param, is_retval):
        ctype = self._create_source_type(source_type)
        if ctype.startswith('va_list'):
            raise SkipError()
        # FIXME: FILE* should not be skipped, it should be handled
        #        properly instead
        elif ctype == 'FILE*':
            raise SkipError

        is_member = not (is_param or is_retval)
        # Here we handle basic type parsing; most of the heavy lifting
        # and inference comes in annotationparser.py when we merge
        # in annotation data.
        derefed_name = self.parse_ctype(ctype, is_member)
        rettype = Type(derefed_name, ctype)
        rettype.canonical = self._canonicalize_ctype(ctype)
        derefed_ctype = ctype.replace('*', '')
        rettype.derefed_canonical = self._canonicalize_ctype(derefed_ctype)

        canontype = type_name_from_ctype(ctype)
        # Is it a const char * or a const gpointer?
        if ((canontype == TYPE_STRING or source_type.type == CTYPE_POINTER) and
            (source_type.base_type.type_qualifier & TYPE_QUALIFIER_CONST)):
            rettype.is_const = True
        return rettype

    def _create_parameter(self, symbol):
        if symbol.type == CSYMBOL_TYPE_ELLIPSIS:
            ptype = Varargs()
        else:
            ptype = self._create_type(symbol.base_type,
                                      is_param=True, is_retval=False)
            ptype = self.resolve_param_type(ptype)
        return Parameter(symbol.ident, ptype)

    def _create_return(self, source_type):
        rtype = self._create_type(source_type,
                                  is_param=False, is_retval=True)
        rtype = self.resolve_param_type(rtype)
        return_ = Return(rtype)
        return return_

    def _create_const(self, symbol):
        # Don't create constants for non-public things
        # http://bugzilla.gnome.org/show_bug.cgi?id=572790
        if (symbol.source_filename is None or
            not symbol.source_filename.endswith('.h')):
            return None
        name = self._strip_namespace_func(symbol.ident)
        if symbol.const_string is not None:
            type_name = 'utf8'
            value = symbol.const_string
        elif symbol.const_int is not None:
            type_name = 'int'
            value = symbol.const_int
        elif symbol.const_double is not None:
            type_name = 'double'
            value = symbol.const_double
        else:
            raise AssertionError()

        const = Constant(name, type_name, value)
        return const

    def _create_typedef_struct(self, symbol, disguised=False):
        name = self.remove_prefix(symbol.ident)
        struct = Struct(name, symbol.ident, disguised)
        self._typedefs_ns[symbol.ident] = struct
        self._create_struct(symbol)
        return struct

    def _create_typedef_union(self, symbol):
        name = self.remove_prefix(symbol.ident)
        union = Union(name, symbol.ident)
        self._typedefs_ns[symbol.ident] = union
        self._create_union(symbol)
        return union

    def _create_typedef_callback(self, symbol):
        callback = self._create_callback(symbol)
        self._typedefs_ns[callback.name] = callback
        return callback

    def _create_compound(self, klass, symbol, anonymous):
        if symbol.ident is None:
            # the compound is an anonymous member of another union or a struct
            assert anonymous
            compound = klass(None, None)
        else:
            compound = self._typedefs_ns.get(symbol.ident, None)

        if compound is None:
            # This is a bit of a hack; really we should try
            # to resolve through the typedefs to find the real
            # name
            if symbol.ident.startswith('_'):
                name = symbol.ident[1:]
                compound = self._typedefs_ns.get(name, None)
            else:
                name = symbol.ident
            if compound is None:
                name = self.remove_prefix(name)
                compound = klass(name, symbol.ident)

        for child in symbol.base_type.child_list:
            field = self._traverse_one(child)
            if field:
                compound.fields.append(field)

        return compound

    def _create_struct(self, symbol, anonymous=False):
        return self._create_compound(Struct, symbol, anonymous)

    def _create_union(self, symbol, anonymous=False):
        return self._create_compound(Union, symbol, anonymous)

    def _create_callback(self, symbol):
        parameters = list(self._create_parameters(symbol.base_type.base_type))
        retval = self._create_return(symbol.base_type.base_type.base_type)

        # Mark the 'user_data' arguments
        for i, param in enumerate(parameters):
            if (param.type.name == 'any' and
                param.name == 'user_data'):
                param.closure_index = i

        if symbol.ident.find('_') > 0:
            name = self.remove_prefix(symbol.ident, True)
        else:
            name = self.remove_prefix(symbol.ident)
        callback = Callback(name, retval, parameters, symbol.ident)

        return callback

    def _typepair_to_str(self, item):
        nsname, item = item
        if nsname is None:
            return item.name
        return '%s.%s' % (nsname, item.name)

    def _resolve_type_name_1(self, type_name, ctype, names):
        # First look using the built-in names
        if ctype:
            try:
                return type_names[ctype]
            except KeyError, e:
                pass
        try:
            return type_names[type_name]
        except KeyError, e:
            pass

        if ctype:
            ctype = ctype.replace('*', '')
            resolved = names.ctypes.get(ctype)
            if resolved:
                return self._typepair_to_str(resolved)
        type_name = self.remove_prefix(type_name)
        resolved = names.aliases.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        resolved = names.names.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        resolved = names.type_names.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        raise KeyError("failed to find %r" % (type_name, ))

    def resolve_type_name_full(self, type_name, ctype,
                               names, allow_invalid=True):
        try:
            return self._resolve_type_name_1(type_name, ctype, names)
        except KeyError, e:
            try:
                return self._resolve_type_name_1(type_name, ctype, self._names)
            except KeyError, e:
                if not allow_invalid:
                    raise
                return type_name

    def resolve_type_name(self, type_name, ctype=None):
        try:
            return self.resolve_type_name_full(type_name, ctype, self._names)
        except KeyError, e:
            return type_name

    def gtypename_to_giname(self, gtname, names):
        resolved = names.type_names.get(gtname)
        if resolved:
            return self._typepair_to_str(resolved)
        resolved = self._names.type_names.get(gtname)
        if resolved:
            return self._typepair_to_str(resolved)
        raise KeyError("Failed to resolve GType name: %r" % (gtname, ))

    def ctype_of(self, obj):
        if hasattr(obj, 'ctype'):
            return obj.ctype
        elif hasattr(obj, 'symbol'):
            return obj.symbol
        else:
            return None

    def resolve_param_type_full(self, ptype, names, **kwargs):
        if isinstance(ptype, Node):
            ptype.name = self.resolve_type_name_full(ptype.name,
                                                     self.ctype_of(ptype),
                                                     names, **kwargs)
        elif isinstance(ptype, basestring):
            return self.resolve_type_name_full(ptype, ptype, names, **kwargs)
        else:
            raise AssertionError("Unhandled param: %r" % (ptype, ))
        return ptype

    def resolve_param_type(self, ptype):
        try:
            return self.resolve_param_type_full(ptype, self._names)
        except KeyError, e:
            return ptype

    def follow_aliases(self, type_name, names):
        while True:
            resolved = names.aliases.get(type_name)
            if resolved:
                (ns, alias) = resolved
                type_name = alias.target
            else:
                break
        return type_name

    def iter_enums(self):
        for node in self._namespace.nodes:
            if isinstance(node, Enum):
                yield node
