#!/usr/bin/env python

from contextlib import contextmanager
from os.path import join
from os.path import normpath

@contextmanager
def blockedSignals(widget):
    widget.blockSignals(True)
    try:
        yield
    finally:
        widget.blockSignals(False)


class PathTransform(object):

    def __init__(self):
        self.path_file = None

    def relativeToAbsolute(self, path_file):
        assert self.path_file is not None
        path = join(self.path_file, path_file)
        return normpath(path)

g_ptransform = PathTransform()


