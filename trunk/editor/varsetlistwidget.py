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
        index = self.searchParamIndex(id_item)
        if index:
            return self.item.params[index + 1].value
        return ""

    def searchParamIndex(self, param_value):
        i = 0
        for param in self.item.params:
            if param.value == param_value:
                return i
            i += 1
        return None

