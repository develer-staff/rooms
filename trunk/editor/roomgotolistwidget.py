#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomGotoListWidget(RoomListWidget):

    """
    Classe per visualizzare le room nel caso che si stia visualizzando 
    la scelta della stanza in cui spostarsi con l'action ROOM_GOTO
    """

    def sizeHint(self):
        return QSize(350, 300)

    def getIconSize(self):
        return QSize(150, 150)

    def setRowSelected(self, id_room):
        if self.item is not None:
            if id_room == self.item.params[0].value:
                item = self.table.findItems(id_room, Qt.MatchExactly)
                if item:
                    row = item[0].row()
                    self.table.selectRow(row)
