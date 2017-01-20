#!/usr/bin/env python
from distutils.core import setup
from distutils.extension import Extension
import commands

def pkgconfig(*packages, **kw):
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    for token in commands.getoutput("pkg-config --libs --cflags %s" % ' '.join(packages)).split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

setup(
    name = "libttp229",
    version='0.1.0',
    ext_modules=[
        Extension("libttp229", ["libttp229.c"], **pkgconfig('glib-2.0')),
    ],
)