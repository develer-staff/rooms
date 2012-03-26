#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project
from structdata import Param

from varslistwidget import VarsListWidget

class VarSetListWidget(VarsListWidget):

    """
    classe che deriva da VarsListWidget ed e' specifica per lavorare con
    action di tipo VAR_SET
    """
    def secondColumnItem(self, id_item):
        for action in self.event.actions:
            if action.id == "VAR_SET":
                if action.params[0].value == id_item:
                    return action.params[1].value
        return ""

