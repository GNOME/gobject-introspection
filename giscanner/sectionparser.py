# -*- Mode: Python -*-
# Copyright (C) 2013 Hat, Inc.
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

class SectionFile(object):
    def __init__(self, sections):
        self.sections = sections

class Section(object):
    def __init__(self):
        self.file = None
        self.title = None
        self.main_subsection = Subsection(None)
        self.subsections = []

class Subsection(object):
    def __init__(self, name):
        self.name = name
        self.symbols = []

def parse_sections_file(lines):
    sections = []
    current_section = None
    current_subsection = None

    for line in lines:
        line = line.rstrip()

        if not line or line.isspace():
            continue

        if line == "<SECTION>":
            current_section = Section()
            sections.append(current_section)
            current_subsection = current_section.main_subsection
            continue

        if line == "</SECTION>":
            current_section = None
            continue

        match = re.match(line, r"<FILE>(?P<contents>.*)</FILE>")
        if match:
            current_section.file = match.groupdict['contents']
            continue

        match = re.match(line, r"<TITLE>(?P<contents>.*)</TITLE>")
        if match:
            current_section.title = match.groupdict['contents']
            continue

        match = re.match(line, r"<SUBSECTION (?P<name>).*>")
        if match:
            current_subsection = Section(match.groupdict['name'])
            current_section.subsections.append(current_subsection)
            continue

        current_subsection.symbols.append(line)

    return SectionFile(sections)
