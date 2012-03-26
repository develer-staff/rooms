#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomitemlistwidget import RoomItemListWidget

from structdata import g_project

class RoomListWidget(RoomItemListWidget):

    def firstColumn(self):
        return g_project.data['rooms'].keys()

    def getIconImage(self, id_item):
        return g_project.data["rooms"][id_item].bg

    def verticalHeader(self):
        return ["Room", ""]

    def setRowSelected(self, id_item):
        raise NotImplementedError

    def signal(self, row, col):
        self.emit(SIGNAL("changeSelectedItem(QString, QString)"),
                  self.table.item(row, 0).text(),
                  "room")
