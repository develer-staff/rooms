#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomReqListWidget(RoomListWidget):


    def getIconSize(self):
        return QSize(100, 100)

    def setRowSelected(self, id_item):
        if self.item is not None:
            item = self.table.findItems(id_item, Qt.MatchExactly)
            if item:
                row = item[0].row()
                self.table.selectRow(row)
