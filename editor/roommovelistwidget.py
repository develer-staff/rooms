#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomMoveListWidget(RoomListWidget):

    """
    Classe per visualizzare le room nel caso che si stia visualizzando 
    la scelta di item e room nel caso di ITEM_MOVE
    """

    icon_size = QSize(100, 100)

    def getInitialItemToSelect(self):
        if self.item is not None:
            return self.item.params[1].value

