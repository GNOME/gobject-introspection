# GObject-Introspection - a framework for introspecting GObject libraries
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
import shlex
import subprocess


class PkgConfigError(Exception):
    pass


def check_output(flags, command=None):
    if command is None:
        command = [os.environ.get('PKG_CONFIG', 'pkg-config')]
    argv = command[:]
    argv.extend(flags)
    try:
        return subprocess.check_output(argv, universal_newlines=True)
    except subprocess.CalledProcessError as e:
        raise PkgConfigError('pkg-config: %s' % e)
    except OSError as e:
        raise PkgConfigError('pkg-config: error executing command %s: %s' % (argv, e))


def cflags(packages, msvc_syntax=False, command=None):
    flags = ['--msvc-syntax'] if msvc_syntax else []
    flags.append('--cflags')
    flags.extend(packages)
    out = check_output(flags, command)
    return shlex.split(out)


def libs(packages, msvc_syntax=False, command=None):
    flags = ['--msvc-syntax'] if msvc_syntax else []
    flags.append('--libs')
    flags.extend(packages)
    out = check_output(flags, command)
    return shlex.split(out)