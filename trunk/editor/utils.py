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

    instance = None
    path_file = ""

    def __new__(self):
        if self.instance is None:
            self.instance = super(PathTransform, self).__new__(self)
        return self.instance

    def relativeToAbsolute(self, path_file):
        path = join(self.path_file, path_file)
        return normpath(path)
