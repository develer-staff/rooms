#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomlistwidget import RoomListWidget

class RoomReqListWidget(RoomListWidget):

    def getIconSize(self):
        return QSize(100, 100)

    def setRowSelected(self, id_room):
        if self.item is not None:
            for requirement in self.event.requirements:
                if requirement.tag_name == "var_req" and\
                   requirement.value == id_room:
                    item = self.table.findItems(id_room, Qt.MatchExactly)
                    if item:
                        row = item[0].row()
                        self.table.selectRow(row)
                        break
