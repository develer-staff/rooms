#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project

from roomslistwidget import RoomsListWidget

class VarsListWidget(RoomsListWidget):

    def firstColumn(self):
        return g_project.data['vars'].keys()

    def getSecondColumnItem(self, id_item):
        if self.item:
            second_column_item = QTableWidgetItem(self.item.value)
        else:
            second_column_item = QTableWidgetItem("")
        return second_column_item

    def createSignals(self):
        self.connect(self.table, SIGNAL("itemChanged(QTableWidgetItem *)"),
                     self.signal)

    def signal(self, item):
        print self.table.cellWidget(item.row(), 0).text()
        self.emit(SIGNAL("editedElement(QString, QString)"),
                  self.table.cellWidget(item.row(), 0).text(),
                  item.text())

    def verticalHeader(self):
        return ["Name", "Value"]
