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

from . import ast
from . import message
from .cachestore import CacheStore
from .girparser import GIRParser
from .sourcescanner import (
    SourceSymbol, ctype_name, CTYPE_POINTER,
    CTYPE_BASIC_TYPE, CTYPE_UNION, CTYPE_ARRAY, CTYPE_TYPEDEF,
    CTYPE_VOID, CTYPE_ENUM, CTYPE_FUNCTION, CTYPE_STRUCT,
    CSYMBOL_TYPE_FUNCTION, CSYMBOL_TYPE_TYPEDEF, CSYMBOL_TYPE_STRUCT,
    CSYMBOL_TYPE_ENUM, CSYMBOL_TYPE_UNION, CSYMBOL_TYPE_OBJECT,
    CSYMBOL_TYPE_MEMBER, CSYMBOL_TYPE_ELLIPSIS, CSYMBOL_TYPE_CONST,
    TYPE_QUALIFIER_CONST, TYPE_QUALIFIER_VOLATILE)


class TransformerException(Exception):
    pass


_xdg_data_dirs = [x for x in os.environ.get('XDG_DATA_DIRS', '').split(os.pathsep)]
_xdg_data_dirs.append(DATADIR)

if os.name != 'nt':
    _xdg_data_dirs.append('/usr/share')


class Transformer(object):
    namespace = property(lambda self: self._namespace)

    def __init__(self, namespace, accept_unprefixed=False):
        self._cachestore = CacheStore()
        self._accept_unprefixed = accept_unprefixed
        self._namespace = namespace
        self._pkg_config_packages = set()
        self._typedefs_ns = {}
        self._parsed_includes = {}  # <string namespace -> Namespace>
        self._includepaths = []
        self._passthrough_mode = False

    def get_pkgconfig_packages(self):
        return self._pkg_config_packages

    def disable_cache(self):
        self._cachestore = None

    def set_passthrough_mode(self):
        self._passthrough_mode = True

    def _append_new_node(self, node):
        original = self._namespace.get(node.name)
        # Special case constants here; we allow duplication to sort-of
        # handle #ifdef.  But this introduces an arch-dependency in the .gir
        # file.  So far this has only come up scanning glib - in theory, other
        # modules will just depend on that.
        if isinstance(original, ast.Constant) and isinstance(node, ast.Constant):
            pass
        elif original:
            positions = set()
            positions.update(original.file_positions)
            positions.update(node.file_positions)
            message.fatal("Namespace conflict for '%s'" % (node.name, ),
                          positions)
        else:
            self._namespace.append(node)

    def parse(self, symbols):
        for symbol in symbols:
            ## WORKAROUND ##
            # https://bugzilla.gnome.org/show_bug.cgi?id=550616
            if symbol.ident in ['gst_g_error_get_type']:
                continue
            node = self._traverse_one(symbol)
            if node:
                self._append_new_node(node)

        # Now look through the namespace for things like
        # typedef struct _Foo Foo;
        # where we've never seen the struct _Foo.  Just create
        # an empty structure for these as "disguised"
        # If we do have a class/interface, merge fields
        for typedef, compound in self._typedefs_ns.iteritems():
            ns_compound = self._namespace.get(compound.name)
            if not ns_compound:
                ns_compound = self._namespace.get('_' + compound.name)
            if (not ns_compound and isinstance(compound, (ast.Record, ast.Union))
            and len(compound.fields) == 0):
                disguised = ast.Record(compound.name, typedef, disguised=True)
                self._namespace.append(disguised)
            elif not ns_compound:
                self._namespace.append(compound)
            elif isinstance(ns_compound, (ast.Record, ast.Union)) and len(ns_compound.fields) == 0:
                ns_compound.fields = compound.fields
        self._typedefs_ns = None

    def set_include_paths(self, paths):
        self._includepaths = list(paths)

    def register_include(self, include):
        if include in self._namespace.includes:
            return
        self._namespace.includes.add(include)
        filename = self._find_include(include)
        self._parse_include(filename)

    def register_include_uninstalled(self, include_path):
        basename = os.path.basename(include_path)
        if not basename.endswith('.gir'):
            raise SystemExit("Include path %r must be a filename path "
                             "ending in .gir" % (include_path, ))
        girname = basename[:-4]
        include = ast.Include.from_string(girname)
        if include in self._namespace.includes:
            return
        self._namespace.includes.add(include)
        self._parse_include(include_path, uninstalled=True)

    def lookup_giname(self, name):
        """Given a name of the form Foo or Bar.Foo,
return the corresponding ast.Node, or None if none
available.  Will throw KeyError however for unknown
namespaces."""
        if '.' not in name:
            return self._namespace.get(name)
        else:
            (ns, giname) = name.split('.', 1)
            if ns == self._namespace.name:
                return self._namespace.get(giname)
            # Fallback to the main namespace if not a dependency and matches a prefix
            if ns in self._namespace.identifier_prefixes and not ns in self._parsed_includes:
                message.warn(("Deprecated reference to identifier " +
                              "prefix %s in GIName %s") % (ns, name))
                return self._namespace.get(giname)
            include = self._parsed_includes[ns]
            return include.get(giname)

    def lookup_typenode(self, typeobj):
        """Given a Type object, if it points to a giname,
calls lookup_giname() on the name.  Otherwise return
None."""
        if typeobj.target_giname:
            return self.lookup_giname(typeobj.target_giname)
        return None

    # Private

    def _find_include(self, include):
        searchdirs = self._includepaths[:]
        for path in _xdg_data_dirs:
            searchdirs.append(os.path.join(path, 'gir-1.0'))
        searchdirs.append(os.path.join(DATADIR, 'gir-1.0'))

        girname = '%s-%s.gir' % (include.name, include.version)
        for d in searchdirs:
            path = os.path.join(d, girname)
            if os.path.exists(path):
                return path
        sys.stderr.write("Couldn't find include %r (search path: %r)\n" % (girname, searchdirs))
        sys.exit(1)

    @classmethod
    def parse_from_gir(cls, filename, extra_include_dirs=None):
        self = cls(None)
        if extra_include_dirs is not None:
            self.set_include_paths(extra_include_dirs)
        self.set_passthrough_mode()
        self._parse_include(filename)
        parser = self._cachestore.load(filename)
        self._namespace = parser.get_namespace()
        del self._parsed_includes[self._namespace.name]
        return self

    def _parse_include(self, filename, uninstalled=False):
        parser = None
        if self._cachestore is not None:
            parser = self._cachestore.load(filename)
        if parser is None:
            parser = GIRParser(types_only=not self._passthrough_mode)
            parser.parse(filename)
            if self._cachestore is not None:
                self._cachestore.store(filename, parser)

        for include in parser.get_namespace().includes:
            if include.name not in self._parsed_includes:
                dep_filename = self._find_include(include)
                self._parse_include(dep_filename)

        if not uninstalled:
            for pkg in parser.get_namespace().exported_packages:
                self._pkg_config_packages.add(pkg)
        namespace = parser.get_namespace()
        self._parsed_includes[namespace.name] = namespace

    def _iter_namespaces(self):
        """Return an iterator over all included namespaces; the
currently-scanned namespace is first."""
        yield self._namespace
        for ns in self._parsed_includes.itervalues():
            yield ns

    def _sort_matches(self, x, y):
        if x[0] is self._namespace:
            return 1
        elif y[0] is self._namespace:
            return -1
        return cmp(x[2], y[2])

    def _split_c_string_for_namespace_matches(self, name, is_identifier=False):
        matches = []  # Namespaces which might contain this name
        unprefixed_namespaces = []  # Namespaces with no prefix, last resort
        for ns in self._iter_namespaces():
            if is_identifier:
                prefixes = ns.identifier_prefixes
            elif name[0].isupper():
                prefixes = ns._ucase_symbol_prefixes
            else:
                prefixes = ns.symbol_prefixes
            if prefixes:
                for prefix in prefixes:
                    if (not is_identifier) and (not prefix.endswith('_')):
                        prefix = prefix + '_'
                    if name.startswith(prefix):
                        matches.append((ns, name[len(prefix):], len(prefix)))
                        break
            else:
                unprefixed_namespaces.append(ns)
        if matches:
            matches.sort(self._sort_matches)
            return map(lambda x: (x[0], x[1]), matches)
        elif self._accept_unprefixed:
            return [(self._namespace, name)]
        elif unprefixed_namespaces:
            # A bit of a hack; this function ideally shouldn't look through the
            # contents of namespaces; but since we aren't scanning anything
            # without a prefix, it's not too bad.
            for ns in unprefixed_namespaces:
                if name in ns:
                    return [(ns, name)]
        raise ValueError("Unknown namespace for %s %r"
                         % ('identifier' if is_identifier else 'symbol', name, ))

    def split_ctype_namespaces(self, ident):
        """Given a StudlyCaps string identifier like FooBar, return a
list of (namespace, stripped_identifier) sorted by namespace length,
or raise ValueError.  As a special case, if the current namespace matches,
it is always biggest (i.e. last)."""
        return self._split_c_string_for_namespace_matches(ident, is_identifier=True)

    def split_csymbol_namespaces(self, symbol):
        """Given a C symbol like foo_bar_do_baz, return a list of
(namespace, stripped_symbol) sorted by namespace match probablity, or
raise ValueError."""
        return self._split_c_string_for_namespace_matches(symbol, is_identifier=False)

    def split_csymbol(self, symbol):
        """Given a C symbol like foo_bar_do_baz, return the most probable
(namespace, stripped_symbol) match, or raise ValueError."""
        matches = self._split_c_string_for_namespace_matches(symbol, is_identifier=False)
        return matches[-1]

    def strip_identifier(self, ident):
        hidden = ident.startswith('_')
        if hidden:
            ident = ident[1:]
        try:
            matches = self.split_ctype_namespaces(ident)
        except ValueError as e:
            raise TransformerException(str(e))
        for ns, name in matches:
            if ns is self._namespace:
                if hidden:
                    return '_' + name
                return name
        (ns, name) = matches[-1]
        raise TransformerException(
            "Skipping foreign identifier %r from namespace %s" % (ident, ns.name, ))
        return None

    def _strip_symbol(self, symbol):
        ident = symbol.ident
        hidden = ident.startswith('_')
        if hidden:
            ident = ident[1:]
        try:
            (ns, name) = self.split_csymbol(ident)
        except ValueError as e:
            raise TransformerException(str(e))
        if ns != self._namespace:
            raise TransformerException(
                "Skipping foreign symbol from namespace %s" % (ns.name, ))
        if hidden:
            return '_' + name
        return name

    def _traverse_one(self, symbol, stype=None, parent_symbol=None):
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
        elif stype == CSYMBOL_TYPE_MEMBER:
            return self._create_member(symbol, parent_symbol)
        elif stype == CSYMBOL_TYPE_UNION:
            return self._create_union(symbol)
        elif stype == CSYMBOL_TYPE_CONST:
            return self._create_const(symbol)
        # Ignore variable declarations in the header
        elif stype == CSYMBOL_TYPE_OBJECT:
            pass
        else:
            print 'transformer: unhandled symbol: %r' % (symbol, )

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
            if child.private:
                continue
            if prefixlen > 0:
                name = child.ident[prefixlen:]
            else:
                # Ok, the enum members don't have a consistent prefix
                # among them, so let's just remove the global namespace
                # prefix.
                try:
                    name = self._strip_symbol(child)
                except TransformerException as e:
                    message.warn_symbol(symbol, e)
                    return None
            members.append(ast.Member(name.lower(),
                                      child.const_int,
                                      child.ident,
                                      None))

        try:
            enum_name = self.strip_identifier(symbol.ident)
        except TransformerException as e:
            message.warn_symbol(symbol, e)
            return None
        if symbol.base_type.is_bitfield:
            klass = ast.Bitfield
        else:
            klass = ast.Enum
        node = klass(enum_name, symbol.ident, members=members)
        node.add_symbol_reference(symbol)
        return node

    def _create_function(self, symbol):
        # Drop functions that start with _ very early on here
        if symbol.ident.startswith('_'):
            return None
        parameters = list(self._create_parameters(symbol, symbol.base_type))
        return_ = self._create_return(symbol.base_type.base_type)
        try:
            name = self._strip_symbol(symbol)
        except TransformerException as e:
            message.warn_symbol(symbol, e)
            return None
        func = ast.Function(name, return_, parameters, False, symbol.ident)
        func.add_symbol_reference(symbol)
        return func

    def _create_source_type(self, source_type):
        assert source_type is not None
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
            value = 'gpointer'
        return value

    def _create_complete_source_type(self, source_type):
        assert source_type is not None

        const = (source_type.type_qualifier & TYPE_QUALIFIER_CONST)
        volatile = (source_type.type_qualifier & TYPE_QUALIFIER_VOLATILE)

        if source_type.type == CTYPE_VOID:
            return 'void'
        elif source_type.type in [CTYPE_BASIC_TYPE,
                                  CTYPE_TYPEDEF,
                                  CTYPE_STRUCT,
                                  CTYPE_UNION,
                                  CTYPE_ENUM]:
            value = source_type.name
            if not value:
                value = 'gpointer'
            if const:
                value = 'const ' + value
            if volatile:
                value = 'volatile ' + value
        elif source_type.type == CTYPE_ARRAY:
            return self._create_complete_source_type(source_type.base_type)
        elif source_type.type == CTYPE_POINTER:
            value = self._create_complete_source_type(source_type.base_type) + '*'
            # TODO: handle pointer to function as a special case?
            if const:
                value += ' const'
            if volatile:
                value += ' volatile'

        else:
            if const:
                value = 'gconstpointer'
            else:
                value = 'gpointer'
            if volatile:
                value = 'volatile ' + value
            return value

        return value

    def _create_parameters(self, symbol, base_type):
        # warn if we see annotations for unknown parameters
        param_names = set(child.ident for child in base_type.child_list)
        for i, child in enumerate(base_type.child_list):
            yield self._create_parameter(symbol, i, child)

    def _synthesize_union_type(self, symbol, parent_symbol):
        # Synthesize a named union so that it can be referenced.
        parent_ident = parent_symbol.ident
        # FIXME: Should split_ctype_namespaces handle the hidden case?
        hidden = parent_ident.startswith('_')
        if hidden:
            parent_ident = parent_ident[1:]
        matches = self.split_ctype_namespaces(parent_ident)
        (namespace, parent_name) = matches[-1]
        assert namespace and parent_name
        if hidden:
            parent_name = '_' + parent_name
        fake_union = ast.Union("%s__%s__union" % (parent_name, symbol.ident))
        # _parse_fields accesses <type>.base_type.child_list, so we have to
        # pass symbol.base_type even though that refers to the array, not the
        # union.
        self._parse_fields(symbol.base_type, fake_union)
        self._append_new_node(fake_union)
        fake_type = ast.Type(
            target_giname="%s.%s" % (namespace.name, fake_union.name))
        return fake_type

    def _create_member(self, symbol, parent_symbol=None):
        source_type = symbol.base_type
        if (source_type.type == CTYPE_POINTER
        and symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_callback(symbol, member=True)
        elif source_type.type == CTYPE_STRUCT and source_type.name is None:
            node = self._create_struct(symbol, anonymous=True)
        elif source_type.type == CTYPE_UNION and source_type.name is None:
            node = self._create_union(symbol, anonymous=True)
        else:
            # Special handling for fields; we don't have annotations on them
            # to apply later, yet.
            if source_type.type == CTYPE_ARRAY:
                complete_ctype = self._create_complete_source_type(source_type)
                # If the array contains anonymous unions, like in the GValue
                # struct, we need to handle this specially.  This is necessary
                # to be able to properly calculate the size of the compound
                # type (e.g. GValue) that contains this array, see
                # <https://bugzilla.gnome.org/show_bug.cgi?id=657040>.
                if (source_type.base_type.type == CTYPE_UNION
                and source_type.base_type.name is None):
                    synthesized_type = self._synthesize_union_type(symbol, parent_symbol)
                    ftype = ast.Array(None, synthesized_type, complete_ctype=complete_ctype)
                else:
                    ctype = self._create_source_type(source_type)
                    canonical_ctype = self._canonicalize_ctype(ctype)
                    if canonical_ctype[-1] == '*':
                        derefed_name = canonical_ctype[:-1]
                    else:
                        derefed_name = canonical_ctype
                    if complete_ctype[-1] == '*':
                        derefed_complete_ctype = complete_ctype[:-1]
                    else:
                        derefed_complete_ctype = complete_ctype
                    from_ctype = self.create_type_from_ctype_string(ctype,
                                                                    complete_ctype=complete_ctype)
                    ftype = ast.Array(None, from_ctype,
                                      ctype=derefed_name,
                                      complete_ctype=derefed_complete_ctype)
                child_list = list(symbol.base_type.child_list)
                ftype.zeroterminated = False
                if child_list:
                    ftype.size = child_list[0].const_int
            else:
                ftype = self._create_type_from_base(symbol.base_type)
            # ast.Fields are assumed to be read-write
            # (except for Objects, see also glibtransformer.py)
            node = ast.Field(symbol.ident, ftype,
                             readable=True, writable=True,
                             bits=symbol.const_int)
            if symbol.private:
                node.readable = False
                node.writable = False
                node.private = True
        return node

    def _create_typedef(self, symbol):
        ctype = symbol.base_type.type
        if (ctype == CTYPE_POINTER and symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_typedef_callback(symbol)
        elif (ctype == CTYPE_POINTER and symbol.base_type.base_type.type == CTYPE_STRUCT):
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
            try:
                name = self.strip_identifier(symbol.ident)
            except TransformerException as e:
                message.warn(e)
                return None
            if symbol.base_type.name:
                complete_ctype = self._create_complete_source_type(symbol.base_type)
                target = self.create_type_from_ctype_string(symbol.base_type.name,
                                                            complete_ctype=complete_ctype)
            else:
                target = ast.TYPE_ANY
            if name in ast.type_names:
                return None
            return ast.Alias(name, target, ctype=symbol.ident)
        else:
            raise NotImplementedError(
                "symbol %r of type %s" % (symbol.ident, ctype_name(ctype)))
        return node

    def _canonicalize_ctype(self, ctype):
        # First look up the ctype including any pointers;
        # a few type names like 'char*' have their own aliases
        # and we need pointer information for those.
        firstpass = ast.type_names.get(ctype)

        # If we have a particular alias for this, skip deep
        # canonicalization to prevent changing
        # e.g. char* -> int8*
        if firstpass:
            return firstpass.target_fundamental

        if not ctype.endswith('*'):
            return ctype

        # We have a pointer type.
        # Strip the end pointer, canonicalize our base type
        base = ctype[:-1]
        canonical_base = self._canonicalize_ctype(base)

        # Append the pointer again
        canonical = canonical_base + '*'

        return canonical

    def _create_type_from_base(self, source_type, is_parameter=False, is_return=False):
        ctype = self._create_source_type(source_type)
        complete_ctype = self._create_complete_source_type(source_type)
        const = ((source_type.type == CTYPE_POINTER) and
                 (source_type.base_type.type_qualifier & TYPE_QUALIFIER_CONST))
        return self.create_type_from_ctype_string(ctype, is_const=const,
                                                  is_parameter=is_parameter, is_return=is_return,
                                                  complete_ctype=complete_ctype)

    def _create_bare_container_type(self, base, ctype=None,
                                    is_const=False, complete_ctype=None):
        if base in ('GList', 'GSList', 'GLib.List', 'GLib.SList'):
            if base in ('GList', 'GSList'):
                name = 'GLib.' + base[1:]
            else:
                name = base
            return ast.List(name, ast.TYPE_ANY, ctype=ctype,
                        is_const=is_const, complete_ctype=complete_ctype)
        elif base in ('GArray', 'GPtrArray', 'GByteArray',
                      'GLib.Array', 'GLib.PtrArray', 'GLib.ByteArray',
                      'GObject.Array', 'GObject.PtrArray', 'GObject.ByteArray'):
            if '.' in base:
                name = 'GLib.' + base.split('.', 1)[1]
            else:
                name = 'GLib.' + base[1:]
            return ast.Array(name, ast.TYPE_ANY, ctype=ctype,
                         is_const=is_const, complete_ctype=complete_ctype)
        elif base in ('GHashTable', 'GLib.HashTable', 'GObject.HashTable'):
            return ast.Map(ast.TYPE_ANY, ast.TYPE_ANY, ctype=ctype, is_const=is_const,
                           complete_ctype=complete_ctype)
        return None

    def create_type_from_ctype_string(self, ctype, is_const=False,
                                      is_parameter=False, is_return=False,
                                      complete_ctype=None):
        canonical = self._canonicalize_ctype(ctype)
        base = canonical.replace('*', '')

        # Special default: char ** -> ast.Array, same for GStrv
        if (is_return and canonical == 'utf8*') or base == 'GStrv':
            bare_utf8 = ast.TYPE_STRING.clone()
            bare_utf8.ctype = None
            return ast.Array(None, bare_utf8, ctype=ctype,
                             is_const=is_const, complete_ctype=complete_ctype)

        fundamental = ast.type_names.get(base)
        if fundamental is not None:
            return ast.Type(target_fundamental=fundamental.target_fundamental,
                        ctype=ctype,
                        is_const=is_const, complete_ctype=complete_ctype)
        container = self._create_bare_container_type(base, ctype=ctype, is_const=is_const,
                                                     complete_ctype=complete_ctype)
        if container:
            return container
        return ast.Type(ctype=ctype, is_const=is_const, complete_ctype=complete_ctype)

    def _create_parameter(self, parent_symbol, index, symbol):
        if symbol.type == CSYMBOL_TYPE_ELLIPSIS:
            return ast.Parameter('...', ast.Varargs())
        else:
            ptype = self._create_type_from_base(symbol.base_type, is_parameter=True)

            if symbol.ident is None:
                if symbol.base_type and symbol.base_type.type != CTYPE_VOID:
                    message.warn_symbol(parent_symbol, "missing parameter name; undocumentable")
                ident = 'arg%d' % (index, )
            else:
                ident = symbol.ident

            return ast.Parameter(ident, ptype)

    def _create_return(self, source_type):
        typeval = self._create_type_from_base(source_type, is_return=True)
        return ast.Return(typeval)

    def _create_const(self, symbol):
        if symbol.ident.startswith('_'):
            return None

        # Don't create constants for non-public things
        # http://bugzilla.gnome.org/show_bug.cgi?id=572790
        if (symbol.source_filename is None or not symbol.source_filename.endswith('.h')):
            return None
        try:
            name = self._strip_symbol(symbol)
        except TransformerException as e:
            message.warn_symbol(symbol, e)
            return None
        if symbol.const_string is not None:
            typeval = ast.TYPE_STRING
            value = unicode(symbol.const_string, 'utf-8')
        elif symbol.const_int is not None:
            if symbol.base_type is not None:
                typeval = self._create_type_from_base(symbol.base_type)
            else:
                typeval = ast.TYPE_INT
            unaliased = typeval
            self._resolve_type_from_ctype(unaliased)
            if typeval.target_giname and typeval.ctype:
                target = self.lookup_giname(typeval.target_giname)
                target = self.resolve_aliases(target)
                if isinstance(target, ast.Type):
                    unaliased = target
            if unaliased == ast.TYPE_UINT64:
                value = str(symbol.const_int % 2 ** 64)
            elif unaliased == ast.TYPE_UINT32:
                value = str(symbol.const_int % 2 ** 32)
            elif unaliased == ast.TYPE_UINT16:
                value = str(symbol.const_int % 2 ** 16)
            elif unaliased == ast.TYPE_UINT8:
                value = str(symbol.const_int % 2 ** 16)
            else:
                value = str(symbol.const_int)
        elif symbol.const_double is not None:
            typeval = ast.TYPE_DOUBLE
            value = '%f' % (symbol.const_double, )
        else:
            raise AssertionError()

        const = ast.Constant(name, typeval, value,
                             symbol.ident)
        const.add_symbol_reference(symbol)
        return const

    def _create_typedef_struct(self, symbol, disguised=False):
        try:
            name = self.strip_identifier(symbol.ident)
        except TransformerException as e:
            message.warn_symbol(symbol, e)
            return None
        struct = ast.Record(name, symbol.ident, disguised=disguised)
        self._parse_fields(symbol, struct)
        struct.add_symbol_reference(symbol)
        self._typedefs_ns[symbol.ident] = struct
        return None

    def _create_typedef_union(self, symbol):
        try:
            name = self.strip_identifier(symbol.ident)
        except TransformerException as e:
            message.warn(e)
            return None
        union = ast.Union(name, symbol.ident)
        self._parse_fields(symbol, union)
        union.add_symbol_reference(symbol)
        self._typedefs_ns[symbol.ident] = union
        return None

    def _create_typedef_callback(self, symbol):
        callback = self._create_callback(symbol)
        if not callback:
            return None
        self._typedefs_ns[callback.name] = callback
        return callback

    def _parse_fields(self, symbol, compound):
        for child in symbol.base_type.child_list:
            child_node = self._traverse_one(child, parent_symbol=symbol)
            if not child_node:
                continue
            if isinstance(child_node, ast.Field):
                field = child_node
            else:
                field = ast.Field(child.ident, None, True, False,
                              anonymous_node=child_node)
            compound.fields.append(field)

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
                compound = self._typedefs_ns.get(symbol.ident[1:], None)
            if compound is None:
                if anonymous:
                    name = symbol.ident
                else:
                    try:
                        name = self.strip_identifier(symbol.ident)
                    except TransformerException as e:
                        message.warn(e)
                        return None
                compound = klass(name, symbol.ident)

        self._parse_fields(symbol, compound)
        compound.add_symbol_reference(symbol)
        return compound

    def _create_struct(self, symbol, anonymous=False):
        return self._create_compound(ast.Record, symbol, anonymous)

    def _create_union(self, symbol, anonymous=False):
        return self._create_compound(ast.Union, symbol, anonymous)

    def _create_callback(self, symbol, member=False):
        parameters = list(self._create_parameters(symbol, symbol.base_type.base_type))
        retval = self._create_return(symbol.base_type.base_type.base_type)

        # Mark the 'user_data' arguments
        for i, param in enumerate(parameters):
            if (param.type.target_fundamental == 'gpointer' and param.argname == 'user_data'):
                param.closure_name = param.argname

        if member:
            name = symbol.ident
        elif symbol.ident.find('_') > 0:
            try:
                name = self._strip_symbol(symbol)
            except TransformerException as e:
                message.warn_symbol(symbol, e)
                return None
        else:
            try:
                name = self.strip_identifier(symbol.ident)
            except TransformerException as e:
                message.warn(e)
                return None
        callback = ast.Callback(name, retval, parameters, False,
                                ctype=symbol.ident)
        callback.add_symbol_reference(symbol)

        return callback

    def create_type_from_user_string(self, typestr):
        """Parse a C type string (as might be given from an
        annotation) and resolve it.  For compatibility, we can consume
both GI type string (utf8, Foo.Bar) style, as well as C (char *, FooBar) style.

Note that type resolution may not succeed."""
        if '.' in typestr:
            container = self._create_bare_container_type(typestr)
            if container:
                typeval = container
            else:
                typeval = self._namespace.type_from_name(typestr)
        else:
            typeval = self.create_type_from_ctype_string(typestr)

        self.resolve_type(typeval)
        if typeval.resolved:
            # Explicitly clear out the c_type; there isn't one in this case.
            typeval.ctype = None
        return typeval

    def _resolve_type_from_ctype_all_namespaces(self, typeval, pointer_stripped):
        # If we can't determine the namespace from the type name,
        # fall back to trying all of our includes.  An example of this is mutter,
        # which has nominal namespace of "Meta", but a few classes are
        # "Mutter".  We don't export that data in introspection currently.
        # Basically the library should be fixed, but we'll hack around it here.
        for namespace in self._parsed_includes.itervalues():
            target = namespace.get_by_ctype(pointer_stripped)
            if target:
                typeval.target_giname = '%s.%s' % (namespace.name, target.name)
                return True
        return False

    def _resolve_type_from_ctype(self, typeval):
        assert typeval.ctype is not None
        pointer_stripped = typeval.ctype.replace('*', '')
        try:
            matches = self.split_ctype_namespaces(pointer_stripped)
        except ValueError:
            return self._resolve_type_from_ctype_all_namespaces(typeval, pointer_stripped)
        for namespace, name in matches:
            target = namespace.get(name)
            if not target:
                target = namespace.get_by_ctype(pointer_stripped)
            if target:
                typeval.target_giname = '%s.%s' % (namespace.name, target.name)
                return True
        return False

    def _resolve_type_from_gtype_name(self, typeval):
        assert typeval.gtype_name is not None
        for ns in self._iter_namespaces():
            node = ns.type_names.get(typeval.gtype_name, None)
            if node is not None:
                typeval.target_giname = '%s.%s' % (ns.name, node.name)
                return True
        return False

    def _resolve_type_internal(self, typeval):
        if isinstance(typeval, (ast.Array, ast.List)):
            return self.resolve_type(typeval.element_type)
        elif isinstance(typeval, ast.Map):
            key_resolved = self.resolve_type(typeval.key_type)
            value_resolved = self.resolve_type(typeval.value_type)
            return key_resolved and value_resolved
        elif typeval.resolved:
            return True
        elif typeval.ctype:
            return self._resolve_type_from_ctype(typeval)
        elif typeval.gtype_name:
            return self._resolve_type_from_gtype_name(typeval)

    def resolve_type(self, typeval):
        if not self._resolve_type_internal(typeval):
            return False

        if typeval.target_fundamental or typeval.target_foreign:
            return True

        assert typeval.target_giname is not None

        try:
            type_ = self.lookup_giname(typeval.target_giname)
        except KeyError:
            type_ = None

        if type_ is None:
            typeval.target_giname = None

        return typeval.resolved

    def resolve_aliases(self, typenode):
        """Removes all aliases from typenode, returns first non-alias
        in the typenode alias chain.  Returns typenode argument if it
        is not an alias."""
        while isinstance(typenode, ast.Alias):
            if typenode.target.target_giname is not None:
                typenode = self.lookup_giname(typenode.target.target_giname)
            elif typenode.target.target_fundamental is not None:
                typenode = ast.type_names[typenode.target.target_fundamental]
            else:
                break
        return typenode
