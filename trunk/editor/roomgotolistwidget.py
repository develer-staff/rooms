#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomGotoListWidget(RoomListWidget):

    """
    Classe per visualizzare le room nel caso che si stia visualizzando 
    la scelta della stanza in cui spostarsi con l'action ROOM_GOTO
    """

    icon_size = QSize(150, 150)

    def sizeHint(self):
        return QSize(350, 500)

    def getInitialItemToSelect(self):
        if self.item is not None:
            return self.item.params[0].value
        return None
