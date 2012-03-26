#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from roomslistwidget import RoomsListWidget

class RoomItemListWidget(RoomsListWidget):

    def __init__(self, event, item, parent=None):
        super(RoomItemListWidget, self).__init__(event, item, parent)
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.changeSelection)

    def changeSelection(self, row, column):
        self.table.selectRow(row)

    def firstColumn(self):
        raise NotImplementedError

    def getSecondColumnItem(self, id_item):
        second_column_item = QTableWidgetItem(self.secondColumnItem(id_item))
        return second_column_item

    def getIconSize(self):
        raise NotImplementedError

    def getIconImage(self, id_item):
        raise NotImplementedError

    def secondColumnItem(self, id_item):
        self.table.setIconSize(self.getIconSize())
        second_item = QTableWidgetItem()
        second_item.setSizeHint(QSize(self.table.iconSize().width() + 10,
                                self.table.iconSize().height() + 10))
        icon = QIcon(self.getIconImage(id_item))
        self.table.setRowHeight(self.table.rowCount() - 1,
                                second_item.sizeHint().height())
        second_item.setIcon(icon)
        self.setRowSelected(id_item)
        return second_item

    def setRowSelected(self, id_item):
        raise NotImplementedError

    def verticalHeader(self):
        raise NotImplementedError

    def createSignals(self):
        self.connect(self.table, SIGNAL("cellChanged(int, int)"),
                     self.signal)

    def signal(self, row, col):
        raise NotImplementedError
