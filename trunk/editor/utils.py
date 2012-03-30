#!/usr/bin/env python

from contextlib import contextmanager

@contextmanager
def blockedSignals(widget):
    widget.blockSignals(True)
    try:
        yield
    finally:
        widget.blockSignals(False)
