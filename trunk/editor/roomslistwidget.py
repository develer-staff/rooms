#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

class RoomsListWidget(QWidget):

    def sizeHint(self):
        return QSize(200, 200)

    def __init__(self, event_name, item, parent=None):
        super(RoomsListWidget, self).__init__(parent)
        self.setMinimumSize(300, 300)
        self.event_name = event_name
        self.item = item
        self.search_line = QLineEdit(self)
        self.gl = QGridLayout()
        self.gl.addWidget(self.search_line, 0, 0)
        self.table = QTableWidget(self)
        i = 0
        self.table.setSortingEnabled(False)
        self.table.setColumnCount(2)
        self.table.setHorizontalHeaderLabels(self.verticalHeader())
        for item in self.firstColumn():
            self.table.setRowCount(self.table.rowCount() + 1)
            self.table.setCellWidget(i, 0, QLabel(item))
            self.table.setItem(i, 1, self.getSecondColumnItem(item))
            self.table.setVerticalHeaderItem(i, QTableWidgetItem(""))
            i += 1
        self.gl.addWidget(self.table, 1, 0, 1, 2)
        self.setLayout(self.gl)
        self.createSignals()


    def createSignals(self):
        raise NotImplementedError

    def firstColumn(self):
        raise NotImplementedError

    def getSecondColumnItem(self, id_item):
        raise NotImplementedError

    def verticalHeader(self):
        raise NotImplementedError

if __name__ == "__main__":

    app = QApplication([])
    a = RoomsListWidget()
    a.show()
    app.exec_()
