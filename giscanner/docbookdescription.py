
TAG_PROGRAM_LISTING = '<programlisting'
TAG_CDATA = '<![CDATA['
TAGS = {TAG_PROGRAM_LISTING, TAG_CDATA, ']]>', '</programlisting>'}

def get_formatted_description(description):
    desc = description.replace("|[", "<informalexample><programlisting>") \
                          .replace("]|", "</programlisting></informalexample>")

    desc = "<para>%s</para>" % desc

# we still need to handle this case
#    # Handle "#include <xxxxx>"
#    $text =~ s/#include(\s+)<([^>]+)>/#include$1&lt;$2&gt;/g;

    formatted_desc = ""

    inside_tags = []
    last_offset = 0
    for start, end, tag in _find_xml_tag_matches(desc):
        if len(inside_tags) == 0:
            new_desc = "\n</para>\n<para>\n".join(desc[last_offset:start].split('\n\n'))
        else:
            new_desc = desc[last_offset:start]

        if TAG_CDATA not in inside_tags:
            new_desc = _escape_non_cdata_section(new_desc)

        formatted_desc += new_desc
        formatted_desc += tag
        if tag == TAG_PROGRAM_LISTING:
            formatted_desc += '>'

        if tag in (TAG_CDATA, TAG_PROGRAM_LISTING):
            inside_tags.append(tag)
        else:
            try:
                inside_tags.pop()
            except IndexError:
                print "Error: mismatched tag:", tag
        last_offset = end

    formatted_desc += _escape_non_cdata_section(desc[last_offset:])
    return formatted_desc

def _find_xml_tag_matches(string):
    offset = 0
    while True:
        indexes = []
        for tag in TAGS:
            pos = string.find(tag, offset)
            if pos != -1:
                indexes.append((tag, pos))

        if indexes:
            tag, first = min(indexes, key=lambda x: x[1])
            if tag == TAG_PROGRAM_LISTING:
                end = string.find('>', first + len(tag) - 1) + 1
            else:
                end = first + len(tag)
            offset = end
            yield first, end, tag
        else:
            return

def _escape_non_cdata_section(string):
    string = _escape_ampersand_not_in_entity(string)
    string = _escape_lt_not_in_xml_tag(string)
    return _escape_gt_not_in_xml_tag(string)

def _escape_ampersand_not_in_entity(string):
    parts = string.split('&')

    output = parts[0]
    for part in parts[1:]:
        end = part.find(';')
        if end == -1 or not part[:end].isalpha():
            output += "&amp;"
        else:
            output += "&"
        output += part

    return output

def _is_valid_xml_tag_name(name):
    if len(name) < 1:
        return False
    elif name.isalpha() or (name[0].isalpha() and name[1:].isalnum()):
        return True

def _is_valid_xml_tag(string):
    # handle case where line end is between tag name and first argument.
    # ie. <link\nlinkend="link-id">My Link</link>
    string = string.replace('\n', ' ')

    if string[-1] == '/':
        string = string[:-1]

    # string is the inner part of the tag, without < and >
    if string[0] == '/' and _is_valid_xml_tag_name(string[1:]):
        #valid end tag
        return True
    elif _is_valid_xml_tag_name(string):
        #valid start tag with not params
        return True
    elif " " in string:
        # we are looking for: <tagname arg="value" arg2="value2">
        # TODO: handle spaces in values (between quotations)
        tagname, rest = string.split(" ", 1)
        if not _is_valid_xml_tag_name(tagname):
            return False

        while rest.strip():
            rest = rest.lstrip()

            if not '=' in rest:
                return False
            argname, rest = rest.split('=', 1)
            if not _is_valid_xml_tag_name(argname):
                return False
            if rest[0] != '"':
                return False
            value, rest = rest[1:].split('"', 1)

        return True

def _escape_lt_not_in_xml_tag(string):
    parts = string.split('<')

    output = parts[0]
    for part in parts[1:]:
        end = part.find('>')
        if end == -1 or not _is_valid_xml_tag(part[:end]):
            output += "&lt;"
        else:
            output += "<"
        output += part

    return output

def _escape_gt_not_in_xml_tag(string):
    parts = string.split('>')

    output = parts[0]
    for part in parts[1:]:
        start = output.rfind('<')
        if start == -1 or not _is_valid_xml_tag(output[start+1:]):
            output += "&gt;"
        else:
            output += ">"
        output += part

    return output


def test():
    assert _is_valid_xml_tag_name('a')
    assert _is_valid_xml_tag_name('refsect1')
    assert not _is_valid_xml_tag_name('1refsect')
    assert not _is_valid_xml_tag_name('1')

    assert _is_valid_xml_tag('/a')
    assert _is_valid_xml_tag('/refsect1')
    assert not _is_valid_xml_tag('/1')
    assert _is_valid_xml_tag('link')
    assert _is_valid_xml_tag('link linkend="value"')
    assert _is_valid_xml_tag('link  linkend="value"')
    assert _is_valid_xml_tag('link/')
    assert _is_valid_xml_tag('link linkend="value"/')
    assert _is_valid_xml_tag('link linkend="value" arg23="anothervalue"')
    assert _is_valid_xml_tag('link linkend="value" arg23="anothervalue with spaces"')
    assert not _is_valid_xml_tag('link linkend="value arg23="anothervalue with spaces"')
    assert not _is_valid_xml_tag('link linkend')
    assert _is_valid_xml_tag('link\nlinkend="link-id"')
    assert _is_valid_xml_tag('xref linkend="gtkstylecontext-classes"/')

    assert _is_valid_xml_tag('a href="http://www.gtk.org" title="&lt;i&gt;Our&lt;/i&gt; website"')
    assert _is_valid_xml_tag('ulink \nurl="http://www.freedesktop.org/Standards/wm-spec"')

    string = 'gtk_label_set_markup (label, "Go to the <a href="http://www.gtk.org" ' \
        + 'title="&lt;i&gt;Our&lt;/i&gt; website">GTK+ website</a> for more...");'
    assert _escape_lt_not_in_xml_tag(string) == string

if __name__ == '__main__':
    test()
