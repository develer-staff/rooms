#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from roomslistwidget import RoomsListWidget

class RoomItemListWidget(RoomsListWidget):

    icon_size = None

    def __init__(self, event, item, parent=None):
        super(RoomItemListWidget, self).__init__(event, item, parent)
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.changeSelection)

    def changeSelection(self, row, column):
        self.table.selectRow(row)

    def firstColumn(self):
        raise NotImplementedError

    def getSecondColumnItem(self, id_item):
        second_column_item = self.secondColumnItem(id_item)
        return second_column_item

    def getIconImage(self, id_item):
        raise NotImplementedError

    def secondColumnItem(self, id_item):
        self.table.setIconSize(self.icon_size)
        second_item = QTableWidgetItem()
        second_item.setSizeHint(QSize(self.icon_size.width() + 10,
                                      self.icon_size.height() + 10))
        icon = QIcon(self.getIconImage(id_item))
        self.table.setRowHeight(self.table.rowCount() - 1,
                                second_item.sizeHint().height())
        second_item.setIcon(icon)
        return second_item

    def verticalHeader(self):
        raise NotImplementedError

    def createSignals(self):
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.signal)

    def signal(self, row, col):
        raise NotImplementedError
