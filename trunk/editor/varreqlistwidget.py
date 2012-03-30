#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from varslistwidget import VarsListWidget

class VarReqListWidget(VarsListWidget):
    """
    classe che deriva da VarsListWidget ed e' specifica per lavorare con
    action di tipo VAR_REQ
    """
    def secondColumnItem(self, id_item):
        for requirement in self.event.requirements:
            if requirement.tag_name.upper() == "VAR_REQ":
                if requirement.id == id_item:
                    return requirement.value
        return ""
