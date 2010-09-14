# -*- Mode: Python -*-
# Copyright (C) 2010 Red Hat, Inc.
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

import re

from . import ast
from . import message
from .annotationparser import (TAG_VFUNC, TAG_SINCE, TAG_DEPRECATED, TAG_RETURNS,
                               TAG_ATTRIBUTES, TAG_RENAME_TO, TAG_TYPE, TAG_TRANSFER,
                               TAG_UNREF_FUNC, TAG_REF_FUNC, TAG_SET_VALUE_FUNC,
                               TAG_GET_VALUE_FUNC)
from .annotationparser import (OPT_ALLOW_NONE,
                               OPT_ARRAY, OPT_ELEMENT_TYPE, OPT_IN, OPT_INOUT,
                               OPT_INOUT_ALT, OPT_OUT, OPT_SCOPE,
                               OPT_TYPE, OPT_CLOSURE, OPT_DESTROY, OPT_SKIP,
                               OPT_FOREIGN, OPT_ARRAY_FIXED_SIZE,
                               OPT_ARRAY_LENGTH, OPT_ARRAY_ZERO_TERMINATED)
from .annotationparser import AnnotationParser
from .transformer import TransformerException
from .utils import to_underscores, to_underscores_noprefix

class MainTransformer(object):

    def __init__(self, transformer, blocks):
        self._transformer = transformer
        self._blocks = blocks
        self._namespace = transformer.namespace
        self._uscore_type_names = {}

    # Public API

    def transform(self):
        # Dirty hack for now...maybe eventually we'll support the "typedef GSList FooSet"
        # pattern.
        if self._namespace.name == 'Atk':
            attribute = self._namespace.get('Attribute')
            attributeset = self._namespace.get('AttributeSet')
            if attribute and attributeset:
                alias = ast.Alias('AttributeSet', target=ast.TYPE_ANY)
                self._namespace.append(alias, replace=True)

        # Some initial namespace surgery
        self._namespace.walk(self._pass_fixup_hidden_fields)

        # We have a rough tree which should have most of of the types
        # we know about.  Let's attempt closure; walk over all of the
        # Type() types and see if they match up with something.
        self._namespace.walk(self._pass_type_resolution)

        # Determine some default values for transfer etc.
        # based on the current tree.
        self._namespace.walk(self._pass_callable_defaults)

        # Read in most annotations now.
        self._namespace.walk(self._pass_read_annotations)

        # Now that we've possibly seen more types from annotations,
        # do another type resolution pass.
        self._namespace.walk(self._pass_type_resolution)

        # Generate a reverse mapping "bar_baz" -> BarBaz
        for node in self._namespace.itervalues():
            if isinstance(node, ast.Registered) and node.get_type is not None:
                self._uscore_type_names[node.c_symbol_prefix] = node
            elif isinstance(node, (ast.Record, ast.Union)):
                uscored = to_underscores_noprefix(node.name).lower()
                self._uscore_type_names[uscored] = node

        for node in list(self._namespace.itervalues()):
            if isinstance(node, ast.Function):
                # Discover which toplevel functions are actually methods
                self._pair_function(node)
            if isinstance(node, (ast.Class, ast.Interface)):
                self._pair_class_virtuals(node)

        # Some annotations need to be post function pairing
        self._namespace.walk(self._pass_read_annotations2)

        # Another type resolution pass after we've parsed virtuals, etc.
        self._namespace.walk(self._pass_type_resolution)

        self._namespace.walk(self._pass3)

        # TODO - merge into pass3
        self._pair_quarks_with_enums()

    # Private

    def _pass_fixup_hidden_fields(self, node, chain):
        """Hide all callbacks starting with _; the typical
usage is void (*_gtk_reserved1)(void);"""
        if not isinstance(node, (ast.Class, ast.Interface,
                                 ast.Record, ast.Union)):
            return True
        for field in node.fields:
            if (field.name.startswith('_')
                and field.anonymous_node is not None
                and isinstance(field.anonymous_node, ast.Callback)):
                field.introspectable = False
        return True

    def _get_validate_parameter_name(self, parent, param_name, origin):
        try:
            param = parent.get_parameter(param_name)
        except ValueError, e:
            param = None
        if param is None:
            if isinstance(origin, ast.Parameter):
                origin_name = 'parameter %s' % (origin.argname, )
            else:
                origin_name = 'return value'
            message.log_node(
                message.FATAL, parent,
                "can't find parameter %s referenced by %s of %r"
                % (param_name, origin_name, parent.name))

        return param.argname

    def _apply_annotation_rename_to(self, node, chain, block):
        if not block:
            return
        rename_to = block.get(TAG_RENAME_TO)
        if not rename_to:
            return
        rename_to = rename_to.value
        target = self._namespace.get_by_symbol(rename_to)
        if not target:
            message.warn_node(node,
                "Can't find symbol %r referenced by Rename annotation" % (
                rename_to, ))
        elif target.shadowed_by:
            message.warn_node(node,
                "Function %r already shadowed by %r, can't overwrite with %r" % (
                target.symbol,
                target.shadowed_by,
                rename_to))
        elif target.shadows:
            message.warn_node(node,
                "Function %r already shadows %r, can't multiply shadow with %r" % (
                target.symbol,
                target.shadows,
                rename_to))
        else:
            target.shadowed_by = node.name
            node.shadows = target.name

    def _apply_annotations_function(self, node, chain):
        block = self._blocks.get(node.symbol)
        self._apply_annotations_callable(node, chain, block)

    def _pass_callable_defaults(self, node, chain):
        if isinstance(node, (ast.Callable, ast.Signal)):
            for param in node.parameters:
                if param.transfer is None:
                    param.transfer = self._get_transfer_default(node, param)
            if node.retval.transfer is None:
                node.retval.transfer = self._get_transfer_default(node, node.retval)
        return True

    def _get_annotation_name(self, node):
        if isinstance(node, (ast.Class, ast.Interface, ast.Record,
                             ast.Union, ast.Enum, ast.Bitfield,
                             ast.Callback, ast.Alias)):
            if node.ctype is not None:
                return node.ctype
            elif isinstance(node, ast.Registered) and node.gtype_name is not None:
                return node.gtype_name
            return node.c_name
        assert False, "Unhandled node %r" % (node, )

    def _get_block(self, node):
        return self._blocks.get(self._get_annotation_name(node))

    def _pass_read_annotations(self, node, chain):
        if not node.namespace:
            return False
        if isinstance(node, ast.Alias):
            self._apply_annotations_alias(node, chain)
        if isinstance(node, ast.Function):
            self._apply_annotations_function(node, chain)
        if isinstance(node, ast.Callback):
            self._apply_annotations_callable(node, chain, block = self._get_block(node))
        if isinstance(node, (ast.Class, ast.Interface, ast.Record,
                             ast.Union, ast.Enum, ast.Bitfield,
                             ast.Callback)):
            self._apply_annotations_annotated(node, self._get_block(node))
        if isinstance(node, (ast.Class, ast.Interface, ast.Record, ast.Union)):
            block = self._get_block(node)
            for field in node.fields:
                self._apply_annotations_field(node, block, field)
        if isinstance(node, (ast.Class, ast.Interface)):
            for prop in node.properties:
                self._apply_annotations_property(node, prop)
            for sig in node.signals:
                self._apply_annotations_signal(node, sig)
        if isinstance(node, ast.Class):
            block = self._get_block(node)
            if block:
                tag = block.get(TAG_UNREF_FUNC)
                node.unref_func = tag.value if tag else None
                tag = block.get(TAG_REF_FUNC)
                node.ref_func = tag.value if tag else None
                tag = block.get(TAG_SET_VALUE_FUNC)
                node.set_value_func = tag.value if tag else None
                tag = block.get(TAG_GET_VALUE_FUNC)
                node.get_value_func = tag.value if tag else None
        return True

    def _adjust_container_type(self, parent, node, options):
        has_element_type = OPT_ELEMENT_TYPE in options
        has_array = OPT_ARRAY in options

        if has_array:
            self._apply_annotations_array(parent, node, options)
        elif has_element_type:
            self._apply_annotations_element_type(parent, node, options)

    def _resolve(self, type_str, orig_node=None):
        def grab_one(type_str, resolver, top_combiner, combiner):
            """Return a complete type, and the trailing string part after it.
            Use resolver() on each identifier, and combiner() on the parts of
            each complete type. (top_combiner is used on the top-most type.)"""
            bits = re.split(r'([,<>])', type_str, 1)
            first, sep, rest = [bits[0], '', ''] if (len(bits)==1) else bits
            args = [resolver(first)]
            if sep == '<':
                while sep != '>':
                    next, rest = grab_one(rest, resolver, combiner, combiner)
                    args.append(next)
                    sep, rest = rest[0], rest[1:]
            else:
                rest = sep + rest
            return top_combiner(*args), rest
        def resolver(ident):
            res = self._transformer.create_type_from_user_string(ident)
            return res
        def combiner(base, *rest):
            if not rest:
                return base
            if isinstance(base, ast.List) and len(rest) == 1:
                return ast.List(base.name, *rest)
            if isinstance(base, ast.Map) and len(rest) == 2:
                return ast.Map(*rest)
            message.warn(
                "Too many parameters in type specification %r" % (type_str, ))
            return base
        def top_combiner(base, *rest):
            if orig_node is not None:
                base.is_const = orig_node.is_const
            return combiner(base, *rest)

        result, rest = grab_one(type_str, resolver, top_combiner, combiner)
        if rest:
            message.warn("Trailing components in type specification %r" % (
                type_str, ))
        return result

    def _apply_annotations_array(self, parent, node, options):
        array_opt = options.get(OPT_ARRAY)
        if array_opt:
            array_values = array_opt.all()
        else:
            array_values = {}

        element_type = options.get(OPT_ELEMENT_TYPE)
        if element_type is not None:
            element_type_node = self._resolve(element_type.one())
        elif isinstance(node.type, ast.Array):
            element_type_node = node.type.element_type
        else:
            # We're assuming here that Foo* with an (array) annotation
            # and no (element-type) means array of Foo
            element_type_node = node.type.clone()
            # Explicitly erase ctype since it's no longer valid
            element_type_node.ctype = None

        if isinstance(node.type, ast.Array):
            array_type = node.type.array_type
        else:
            array_type = None
        container_type = ast.Array(array_type, element_type_node,
                               ctype=node.type.ctype,
                               is_const=node.type.is_const)
        if OPT_ARRAY_ZERO_TERMINATED in array_values:
            container_type.zeroterminated = array_values.get(
                OPT_ARRAY_ZERO_TERMINATED) == '1'
        length = array_values.get(OPT_ARRAY_LENGTH)
        if length is not None:
            paramname = self._get_validate_parameter_name(parent, length, node)
            if paramname:
                param = parent.get_parameter(paramname)
                param.direction = node.direction
                if param.direction == ast.PARAM_DIRECTION_OUT:
                    param.transfer = ast.PARAM_TRANSFER_FULL
                container_type.length_param_name = param.argname
        fixed = array_values.get(OPT_ARRAY_FIXED_SIZE)
        if fixed:
            container_type.size = int(fixed)
        node.type = container_type

    def _apply_annotations_element_type(self, parent, node, options):
        element_type_opt = options.get(OPT_ELEMENT_TYPE)
        element_type = element_type_opt.flat()
        if isinstance(node.type, ast.List):
            assert len(element_type) == 1
            node.type.element_type = self._resolve(element_type[0])
        elif isinstance(node.type, ast.Map):
            assert len(element_type) == 2
            node.type.key_type = self._resolve(element_type[0])
            node.type.value_type = self._resolve(element_type[1])
        elif isinstance(node.type, ast.Array):
            node.type.element_type = self._resolve(element_type[0])
        else:
            message.warn_node(parent,
                "Unknown container %r for element-type annotation" % (node.type, ))

    def _get_transfer_default_param(self, parent, node):
        if node.direction in [ast.PARAM_DIRECTION_INOUT,
                              ast.PARAM_DIRECTION_OUT]:
            if node.caller_allocates:
                return ast.PARAM_TRANSFER_NONE
            return ast.PARAM_TRANSFER_FULL
        return ast.PARAM_TRANSFER_NONE

    def _get_transfer_default_returntype_basic(self, typeval):
        if (typeval.is_equiv(ast.BASIC_GIR_TYPES)
            or typeval.is_const
            or typeval.is_equiv(ast.TYPE_NONE)):
            return ast.PARAM_TRANSFER_NONE
        elif typeval.is_equiv(ast.TYPE_STRING):
            # Non-const strings default to FULL
            return ast.PARAM_TRANSFER_FULL
        elif typeval.target_fundamental:
            # This looks like just GType right now
            return None
        return None

    def _is_gi_subclass(self, typeval, supercls_type):
        cls = self._transformer.lookup_typenode(typeval)
        assert cls, str(typeval)
        supercls = self._transformer.lookup_typenode(supercls_type)
        assert supercls
        if cls is supercls:
            return True
        if cls.parent and cls.parent.target_giname != 'GObject.Object':
            return self._is_gi_subclass(cls.parent, supercls_type)
        return False

    def _get_transfer_default_return(self, parent, node):
        typeval = node.type
        basic = self._get_transfer_default_returntype_basic(typeval)
        if basic:
            return basic
        if not typeval.target_giname:
            return None
        target = self._transformer.lookup_typenode(typeval)
        if isinstance(target, ast.Alias):
            return self._get_transfer_default_returntype_basic(target.target)
        elif (isinstance(target, ast.Boxed)
              or (isinstance(target, (ast.Record, ast.Union)) and target.gtype_name is not None)):
            return ast.PARAM_TRANSFER_FULL
        elif isinstance(target, (ast.Enum, ast.Bitfield)):
            return ast.PARAM_TRANSFER_NONE
        # Handle constructors specially here
        elif isinstance(parent, ast.Function) and parent.is_constructor:
            if isinstance(target, ast.Class):
                initially_unowned_type = ast.Type(target_giname='GObject.InitiallyUnowned')
                initially_unowned = self._transformer.lookup_typenode(initially_unowned_type)
                if initially_unowned and self._is_gi_subclass(typeval, initially_unowned_type):
                    return ast.PARAM_TRANSFER_NONE
                else:
                    return ast.PARAM_TRANSFER_FULL
            elif isinstance(target, (ast.Record, ast.Union)):
                return ast.PARAM_TRANSFER_FULL
            else:
                assert False, "Invalid constructor"
        elif isinstance(target, (ast.Class, ast.Record, ast.Union)):
            # Explicitly no default for these
            return None
        else:
            return None

    def _get_transfer_default(self, parent, node):
        if node.type.is_equiv(ast.TYPE_NONE) or isinstance(node.type, ast.Varargs):
            return ast.PARAM_TRANSFER_NONE
        elif isinstance(node, ast.Parameter):
            return self._get_transfer_default_param(parent, node)
        elif isinstance(node, ast.Return):
            return self._get_transfer_default_return(parent, node)
        elif isinstance(node, ast.Field):
            return ast.PARAM_TRANSFER_NONE
        elif isinstance(node, ast.Property):
            return ast.PARAM_TRANSFER_NONE
        else:
            raise AssertionError(node)

    def _apply_annotations_param_ret_common(self, parent, node, tag):
        options = getattr(tag, 'options', {})

        param_type = options.get(OPT_TYPE)
        if param_type:
            node.type = self._resolve(param_type.one(), node.type)

        caller_allocates = False
        annotated_direction = None
        if (OPT_INOUT in options or
            OPT_INOUT_ALT in options):
            annotated_direction = ast.PARAM_DIRECTION_INOUT
        elif OPT_OUT in options:
            subtype = options[OPT_OUT]
            if subtype is not None:
                subtype = subtype.one()
            annotated_direction = ast.PARAM_DIRECTION_OUT
            if subtype in (None, ''):
                if node.type.target_giname and node.type.ctype:
                    caller_allocates = '**' not in node.type.ctype
                else:
                    caller_allocates = False
            elif subtype == 'caller-allocates':
                caller_allocates = True
            elif subtype == 'callee-allocates':
                caller_allocates = False
            else:
                message.fatal("out allocation for %s is invalid (%r)" % (
                    node, subtype))
        elif OPT_IN in options:
            annotated_direction = ast.PARAM_DIRECTION_IN

        if (annotated_direction is not None) and (annotated_direction != node.direction):
            node.direction = annotated_direction
            node.caller_allocates = caller_allocates
            # Also reset the transfer default if we're toggling direction
            node.transfer = self._get_transfer_default(parent, node)

        transfer_tag = options.get(TAG_TRANSFER)
        if transfer_tag:
            node.transfer = transfer_tag.one()

        self._adjust_container_type(parent, node, options)

        if (OPT_ALLOW_NONE in options or
            node.type.target_giname == 'Gio.Cancellable'):
            node.allow_none = True

        if tag is not None and tag.comment is not None:
            node.doc = tag.comment

        for key in options:
            if '.' in key:
                value = options.get(key)
                if value:
                    node.attributes.append((key, value.one()))

    def _apply_annotations_annotated(self, node, block):
        if block is None:
            return

        node.doc = block.comment

        since_tag = block.get(TAG_SINCE)
        if since_tag is not None:
            node.version = since_tag.value

        deprecated_tag = block.get(TAG_DEPRECATED)
        if deprecated_tag is not None:
            value = deprecated_tag.value
            if ': ' in value:
                version, desc = value.split(': ')
            else:
                desc = value
                version = None
            node.deprecated = desc
            if version is not None:
                node.deprecated_version = version

        annos_tag = block.get(TAG_ATTRIBUTES)
        if annos_tag is not None:
            options = AnnotationParser.parse_options(annos_tag.value)
            for key, value in options.iteritems():
                if value:
                    node.attributes.append((key, value.one()))

        if OPT_SKIP in block.options:
            node.skip = True

        if OPT_FOREIGN in block.options:
            node.foreign = True

    def _apply_annotations_alias(self, node, chain):
        block = self._get_block(node)
        self._apply_annotations_annotated(node, block)

    def _apply_annotations_param(self, parent, param, tag):
        if tag:
            options = tag.options
        else:
            options = {}
        if isinstance(parent, (ast.Function, ast.VFunction)):
            scope = options.get(OPT_SCOPE)
            if scope:
                scope = scope.one()
                if scope not in [ast.PARAM_SCOPE_CALL,
                                 ast.PARAM_SCOPE_ASYNC,
                                 ast.PARAM_SCOPE_NOTIFIED]:
                    message.warn_node(
                        parent,
                        "Invalid scope %r for parameter %r" % (scope, param.argname))
                else:
                    param.scope = scope
                    param.transfer = ast.PARAM_TRANSFER_NONE

            destroy = options.get(OPT_DESTROY)
            if destroy:
                param.destroy_name = self._get_validate_parameter_name(parent,
                                                                       destroy.one(),
                                                                       param)
                if param.destroy_name is not None:
                    param.scope = ast.PARAM_SCOPE_NOTIFIED
                    destroy_param = parent.get_parameter(param.destroy_name)
                    # This is technically bogus; we're setting the scope on the destroy
                    # itself.  But this helps avoid tripping a warning from finaltransformer,
                    # since we don't have a way right now to flag this callback a destroy.
                    destroy_param.scope = ast.PARAM_SCOPE_NOTIFIED
            closure = options.get(OPT_CLOSURE)
            if closure:
                param.closure_name = self._get_validate_parameter_name(parent,
                                                                       closure.one(),
                                                                       param)
        elif isinstance(parent, ast.Callback):
            if OPT_CLOSURE in options:
                # For callbacks, (closure) appears without an
                # argument, and tags a parameter that is a closure. We
                # represent it (weirdly) in the gir and typelib by
                # setting param.closure_name to itself.
                param.closure_name = param.argname

        self._apply_annotations_param_ret_common(parent, param, tag)

    def _apply_annotations_return(self, parent, return_, block):
        if block:
            tag = block.get(TAG_RETURNS)
        else:
            tag = None
        self._apply_annotations_param_ret_common(parent, return_, tag)

    def _apply_annotations_params(self, parent, params, block):
        allparams = []
        if parent.instance_parameter:
            allparams.append(parent.instance_parameter.argname)
        for param in params:
            if block:
                tag = block.get(param.argname)
            else:
                tag = None
            self._apply_annotations_param(parent, param, tag)
            allparams.append(param.argname)

        if not block:
            return
        docparams = block.params[:]
        for doc_name in docparams:
            if doc_name in allparams:
                continue
            if len(allparams) == 0:
                text = ''
            elif len(allparams) == 1:
                text = ', should be %r' % (allparams[0], )
            else:
                text = ', should be one of %s' % (
                ', '.join(repr(p) for p in allparams), )

            message.warn(
                '%s: unknown parameter %r in documentation comment%s' % (
                block.name, doc_name, text))

    def _apply_annotations_callable(self, node, chain, block):
        self._apply_annotations_annotated(node, block)
        self._apply_annotations_params(node, node.parameters, block)
        self._apply_annotations_return(node, node.retval, block)

    def _check_arg_annotations(self, parent, params, block):
        if block is None:
            return
        for tag in block.tags.keys():
            if tag == TAG_RETURNS:
                continue
            for param in params:
                if param.argname == tag:
                    break
            else:
                message.warn(
                    "Annotation for '%s' refers to unknown argument '%s'"
                    % (parent.name, tag))

    def _apply_annotations_field(self, parent, block, field):
        if not block:
            return
        tag = block.get(field.name)
        if not tag:
            return
        t = tag.options.get('type')
        if not t:
            return
        field.type = self._transformer.create_type_from_user_string(t.one())

    def _apply_annotations_property(self, parent, prop):
        prefix = self._get_annotation_name(parent)
        block = self._blocks.get('%s:%s' % (prefix, prop.name))
        self._apply_annotations_annotated(prop, block)
        if not block:
            return
        transfer_tag = block.get(TAG_TRANSFER)
        if transfer_tag is not None:
            prop.transfer = transfer_tag.value
        else:
            prop.transfer = self._get_transfer_default(parent, prop)
        type_tag = block.get(TAG_TYPE)
        if type_tag:
            prop.type = self._resolve(type_tag.value, prop.type)

    def _apply_annotations_signal(self, parent, signal):
        prefix = self._get_annotation_name(parent)
        block = self._blocks.get('%s::%s' % (prefix, signal.name))
        self._apply_annotations_annotated(signal, block)
        # We're only attempting to name the signal parameters if
        # the number of parameter tags (@foo) is the same or greater
        # than the number of signal parameters
        if block and len(block.tags) > len(signal.parameters):
            names = block.tags.items()
        else:
            names = []
        for i, param in enumerate(signal.parameters):
            if names:
                name, tag = names[i+1]
                param.name = name
                options = getattr(tag, 'options', {})
                param_type = options.get(OPT_TYPE)
                if param_type:
                    param.type = self._resolve(param_type.one(), param.type)
            else:
                tag = None
            self._apply_annotations_param(signal, param, tag)
        self._apply_annotations_return(signal, signal.retval, block)

    def _pass_read_annotations2(self, node, chain):
        if isinstance(node, ast.Function):
            self._apply_annotations2_function(node, chain)
        return True

    def _apply_annotations2_function(self, node, chain):
        block = self._blocks.get(node.symbol)

        self._apply_annotation_rename_to(node, chain, block)

        # Handle virtual invokers
        parent = chain[-1] if chain else None
        if not (block and parent):
            return
        virtual = block.get(TAG_VFUNC)
        if not virtual:
            return
        invoker_name = virtual.value
        matched = False
        for vfunc in parent.virtual_methods:
            if vfunc.name == invoker_name:
                matched = True
                vfunc.invoker = node.name
                # Also merge in annotations
                self._apply_annotations_callable(vfunc, [parent], block)
                break
        if not matched:
            message.warn_node(node,
                "Virtual slot %r not found for %r annotation" % (invoker_name, TAG_VFUNC))

    def _resolve_and_filter_type_list(self, typelist):
        """Given a list of Type instances, return a new list of types with
the ones that failed to resolve removed."""
        # Create a copy we'll modify
        new_typelist = list(typelist)
        for typeval in typelist:
            resolved = self._transformer.resolve_type(typeval)
            if not resolved:
                new_typelist.remove(typeval)
        return new_typelist

    def _pass_type_resolution(self, node, chain):
        if isinstance(node, ast.Alias):
            self._transformer.resolve_type(node.target)
        if isinstance(node, ast.Callable):
            for parameter in node.parameters:
                self._transformer.resolve_type(parameter.type)
            self._transformer.resolve_type(node.retval.type)
        if isinstance(node, ast.Constant):
            self._transformer.resolve_type(node.value_type)
        if isinstance(node, (ast.Class, ast.Interface, ast.Record, ast.Union)):
            for field in node.fields:
                if field.anonymous_node:
                    pass
                else:
                    self._transformer.resolve_type(field.type)
        if isinstance(node, (ast.Class, ast.Interface)):
            resolved_parent = None
            for parent in node.parent_chain:
                try:
                    self._transformer.resolve_type(parent)
                except ValueError, e:
                    continue
                target = self._transformer.lookup_typenode(parent)
                if target:
                    node.parent = parent
                    break
            else:
                if isinstance(node, ast.Interface) or not node.fundamental:
                    node.parent = ast.Type(target_giname='GObject.Object')
                else:
                    node.parent = None
            for prop in node.properties:
                self._transformer.resolve_type(prop.type)
            for sig in node.signals:
                for param in sig.parameters:
                    self._transformer.resolve_type(param.type)
        if isinstance(node, ast.Class):
            node.interfaces = self._resolve_and_filter_type_list(node.interfaces)
        if isinstance(node, ast.Interface):
            node.prerequisites = self._resolve_and_filter_type_list(node.prerequisites)
        return True

    def _pair_quarks_with_enums(self):
        # self._uscore_type_names is an authoritative mapping of types
        # to underscored versions, since it is based on get_type() methods;
        # but only covers enums that are registered as GObject enums.
        # Create a fallback mapping based on all known enums in this module.
        uscore_enums = {}
        for enum in self._namespace.itervalues():
            if not isinstance(enum, ast.Enum):
                continue
            type_name = enum.ctype
            uscored = to_underscores(type_name).lower()

            uscore_enums[uscored] = enum

            try:
                no_uscore_prefixed = self._transformer.strip_identifier(type_name)
            except TransformerException, e:
                message.warn(e)
                no_uscore_prefixed = None

            if no_uscore_prefixed not in uscore_enums:
                uscore_enums[no_uscore_prefixed] = enum

        for node in self._namespace.itervalues():
            if not isinstance(node, ast.Function):
                continue
            if node.retval.type.target_giname != 'GLib.Quark':
                continue
            short = node.symbol[:-len('_quark')]
            if short == "g_io_error":
                # Special case; GIOError was already taken forcing GIOErrorEnum
                assert self._namespace.name == 'Gio'
                enum = self._namespace.get('IOErrorEnum')
            else:
                enum = self._uscore_type_names.get(short)
                if enum is None:
                    enum = uscore_enums.get(short)
            if enum is not None:
                enum.error_quark = node.symbol
            else:
                message.warn_node(node,
                    """%s: Couldn't find corresponding enumeration""" % (node.symbol, ))

    def _split_uscored_by_type(self, uscored):
        """'uscored' should be an un-prefixed uscore string.  This
function searches through the namespace for the longest type which
prefixes uscored, and returns (type, suffix).  Example, assuming
namespace Gtk, type is TextBuffer:

_split_uscored_by_type(text_buffer_try_new) -> (ast.Class(TextBuffer), 'try_new')"""
        node = None
        count = 0
        prev_split_count = -1
        while True:
            components = uscored.rsplit('_', count)
            if len(components) == prev_split_count:
                return None
            prev_split_count = len(components)
            type_string = components[0]
            node = self._uscore_type_names.get(type_string)
            if node:
                return (node, '_'.join(components[1:]))
            count += 1

    def _pair_function(self, func):
        """Check to see whether a toplevel function should be a
method or constructor of some type."""
        if func.symbol.endswith('_get_type') or func.symbol.startswith('_'):
            return
        (ns, subsymbol) = self._transformer.split_csymbol(func.symbol)
        assert ns == self._namespace
        if self._pair_constructor(func, subsymbol):
            return
        elif self._pair_method(func, subsymbol):
            return
        elif self._pair_static_method(func, subsymbol):
            return

    def _uscored_identifier_for_type(self, typeval):
        """Given a Type(target_giname='Foo.BarBaz'), return 'bar_baz'."""
        name = typeval.get_giname()
        return to_underscores_noprefix(name).lower()

    def _pair_method(self, func, subsymbol):
        if not func.parameters:
            return False
        first = func.parameters[0]
        target = self._transformer.lookup_typenode(first.type)
        if not isinstance(target, (ast.Class, ast.Interface,
                                   ast.Record, ast.Union,
                                   ast.Boxed)):
            return False
        if target.namespace != self._namespace:
            return False

        # A quick hack here...in the future we should catch C signature/GI signature
        # mismatches in a general way in finaltransformer
        if first.type.ctype.count('*') != 1:
            return False

        uscored = self._uscored_identifier_for_type(first.type)
        if not subsymbol.startswith(uscored):
            return False
        func.instance_parameter = func.parameters.pop(0)
        subsym_idx = func.symbol.find(subsymbol)
        self._namespace.float(func)
        func.name = func.symbol[(subsym_idx + len(uscored) + 1):]
        target.methods.append(func)
        func.is_method = True
        return True

    def _pair_static_method(self, func, subsymbol):
        split = self._split_uscored_by_type(subsymbol)
        if split is None:
            return False
        (node, funcname) = split

        # We actually should treat static methods on a wider class of objects:
        #  ast.Class, ast.Interface, ast.Record, ast.Union, ast.Boxed
        # But we stick to ast.Class for now for compatibility with existing code.
        #
        # See https://bugzilla.gnome.org/show_bug.cgi?id=572408
        #
        if not isinstance(node, ast.Class):
            return False

        self._namespace.float(func)
        func.name = funcname
        node.static_methods.append(func)

    def _pair_constructor(self, func, subsymbol):
        if not (func.symbol.find('_new_') >= 0 or func.symbol.endswith('_new')):
            return False
        target = self._transformer.lookup_typenode(func.retval.type)
        if not (isinstance(target, ast.Class)
                or (isinstance(target, (ast.Record, ast.Union, ast.Boxed))
                    and (target.get_type is not None or target.foreign))):
            return False

        split = self._split_uscored_by_type(subsymbol)
        if split is None:
            # TODO - need a e.g. (method) annotation
            message.warn_node(func,
                "Can't find matching type for constructor; symbol=%r" % (func.symbol, ))
            return False
        (origin_node, funcname) = split
        # Some sanity checks; only objects and boxeds can have ctors
        if not (isinstance(origin_node, ast.Class)
                or (isinstance(origin_node, (ast.Record, ast.Union, ast.Boxed))
                    and (origin_node.get_type is not None or origin_node.foreign))):
            return False
        # Verify the namespace - don't want to append to foreign namespaces!
        if origin_node.namespace != self._namespace:
            return False
        # If it takes the object as a first arg, it's not a constructor
        if len(func.parameters) > 0:
            first_arg = self._transformer.lookup_typenode(func.parameters[0].type)
            if (first_arg is not None) and first_arg.gi_name == origin_node.gi_name:
                return False

        if isinstance(target, ast.Class):
            parent = origin_node
            while parent and (not parent.gi_name == 'GObject.Object'):
                if parent == target:
                    break
                if parent.parent:
                    parent = self._transformer.lookup_typenode(parent.parent)
                else:
                    parent = None
                if parent is None or parent.gi_name == 'GObject.Object':
                    message.warn_node(func,
                        "Return value is not superclass for constructor; "
                        "symbol=%r constructed=%r return=%r" % (
                        func.symbol,
                        str(origin_node.create_type()),
                        str(func.retval.type)))
                    return False
        else:
            if origin_node != target:
                message.warn_node(func,
                    "Constructor return type mismatch symbol=%r "
                    "constructed=%r return=%r" % (
                    func.symbol,
                    str(origin_node.create_type()),
                    str(func.retval.type)))
                return False
        self._namespace.float(func)
        func.name = funcname
        func.is_constructor = True
        origin_node.constructors.append(func)
        # Constructors have default return semantics
        if not func.retval.transfer:
            func.retval.transfer = self._get_transfer_default_return(func, func.retval)
        return True

    def _pair_class_virtuals(self, node):
        """Look for virtual methods from the class structure."""
        if not node.glib_type_struct:
            message.warn_node(node,
                "Failed to find class structure for %r" % (node.name, ))
            return

        node_type = node.create_type()
        class_struct = self._transformer.lookup_typenode(node.glib_type_struct)

        # Object class fields are assumed to be read-only
        # (see also _introspect_object and transformer.py)
        for field in class_struct.fields:
            if isinstance(field, ast.Field):
                field.writable = False

        # Loop through fields to determine which are virtual
        # functions and which are signal slots by
        # assuming everything that doesn't share a name
        # with a known signal is a virtual slot.
        for field in class_struct.fields:
            if not isinstance(field.anonymous_node, ast.Callback):
                continue
            callback = field.anonymous_node
            # Check the first parameter is the object
            if len(callback.parameters) == 0:
                continue
            firstparam_type = callback.parameters[0].type
            if firstparam_type != node_type:
                continue
            # Also double check we don't have a signal with this
            # name.
            matched_signal = False
            for signal in node.signals:
                if signal.name.replace('-', '_') == callback.name:
                    matched_signal = True
                    break
            if matched_signal:
                continue
            vfunc = ast.VFunction.from_callback(callback)
            vfunc.instance_parameter = callback.parameters[0]
            vfunc.inherit_file_positions(callback)
            node.virtual_methods.append(vfunc)

        # Take the set of virtual methods we found, and try
        # to pair up with any matching methods using the
        # name+signature.
        for vfunc in node.virtual_methods:
            for method in node.methods:
                if method.name != vfunc.name:
                    continue
                if method.retval.type != vfunc.retval.type:
                    continue
                if len(method.parameters) != len(vfunc.parameters):
                    continue
                for i in xrange(len(method.parameters)):
                    m_type = method.parameters[i].type
                    v_type = vfunc.parameters[i].type
                    if m_type != v_type:
                        continue
                vfunc.invoker = method.name
                # Apply any annotations we have from the invoker to
                # the vfunc
                block = self._blocks.get(method.symbol)
                self._apply_annotations_callable(vfunc, [], block)
                break

    def _pass3(self, node, chain):
        """Pass 3 is after we've loaded GType data and performed type
        closure."""
        if isinstance(node, ast.Callable):
            self._pass3_callable_callbacks(node)
            self._pass3_callable_throws(node)
        return True

    def _pass3_callable_callbacks(self, node):
        """Check to see if we have anything that looks like a
        callback+user_data+GDestroyNotify set."""

        params = node.parameters

        # First, do defaults for well-known callback types
        for i, param in enumerate(params):
            argnode = self._transformer.lookup_typenode(param.type)
            if isinstance(argnode, ast.Callback):
                if param.type.target_giname in ('Gio.AsyncReadyCallback',
                                                'GLib.DestroyNotify'):
                    param.scope = ast.PARAM_SCOPE_ASYNC
                    param.transfer = ast.PARAM_TRANSFER_NONE

        callback_param = None
        for i, param in enumerate(params):
            argnode = self._transformer.lookup_typenode(param.type)
            is_destroynotify = False
            if isinstance(argnode, ast.Callback):
                if param.type.target_giname == 'GLib.DestroyNotify':
                    is_destroynotify = True
                else:
                    callback_param = param
                    continue
            if callback_param is None:
                continue
            if is_destroynotify:
                callback_param.destroy_name = param.argname
                callback_param.scope = ast.PARAM_SCOPE_NOTIFIED
                callback_param.transfer = ast.PARAM_TRANSFER_NONE
            elif (param.type.is_equiv(ast.TYPE_ANY) and
                  param.argname is not None and
                  param.argname.endswith('data')):
                callback_param.closure_name = param.argname

    def _pass3_callable_throws(self, node):
        """Check to see if we have anything that looks like a
        callback+user_data+GDestroyNotify set."""
        if not node.parameters:
            return
        last_param = node.parameters[-1]
        # Checking type.name=='GLib.Error' generates false positives
        # on methods that take a 'GError *'
        if last_param.type.ctype == 'GError**':
            node.parameters.pop()
            node.throws = True
