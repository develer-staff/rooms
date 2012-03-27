#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomMoveListWidget(RoomListWidget):

    """
    Classe per visualizzare le room nel caso che si stia visualizzando 
    la scelta di item e room nel caso di ITEM_MOVE
    """

    def getIconSize(self):
        return QSize(100, 100)

    def setRowSelected(self, id_room):
        if self.item is not None:
            for param in self.item.params:
                if param.value == id_room:
                    item = self.table.findItems(id_room, Qt.MatchExactly)
                    if item:
                        row = item[0].row()
                        self.table.selectRow(row)
                        break
