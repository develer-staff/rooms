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

    """
    classe per trasformare il path di un file da relativo ad assoluto, questo
    per recuperare file che si trovano in una directory diversa da quella
    dell'editor. La classe mette a disposizione una variabile globale
    g_ptransform per implemetare il template singleton.
    Nel momento che si cambia il path del file .rooms su cui si lavora si
    deve settare la variabile path_file
    """
    def __init__(self):
        self.path_file = None

    def relativeToAbsolute(self, path_file):
        """
        funzione per la conversione del path da relativo ad assoluto.
        Se non e' stato settato il path del file .rooms viene lanciata
        un'eccezione di tipo AssertError
        """
        assert self.path_file is not None
        path = join(self.path_file, path_file)
        return normpath(path)

g_ptransform = PathTransform()








