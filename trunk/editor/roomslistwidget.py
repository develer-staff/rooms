#!/usr/bin/env python

from contextlib import contextmanager

from PyQt4.QtGui import *
from PyQt4.QtCore import *

@contextmanager
def blockedSignals(widget):
    widget.blockSignals(True)
    try:
        yield
    finally:
        widget.blockSignals(False)

class RoomsListWidget(QWidget):
    """
    classe base utilizzata per mostare elementi del modello in una tabella
    alcune funzioni devono essere reimplementate dalle classi che la ereditano
    a seconda di cosa si vuole mostrare
    I parametri in ingresso sono l'evento a cui viene associata, l'item a cui
    si riferisce
    """

    def __init__(self, event, item, parent=None):
        super(RoomsListWidget, self).__init__(parent)
        self.setMinimumSize(300, 300)
        self.event = event
        self.item = item
        self.substring = ""
        self.search_line = QLineEdit(self)
        self.gl = QGridLayout()
        self.gl.addWidget(self.search_line, 0, 0)
        self.table = QTableWidget(self)
        self.createSignals()
        with blockedSignals(self.table):
            self.createTable()
        self.setLayout(self.gl)
        self.connect(self.search_line, SIGNAL("textEdited(const QString &)"),
                     self.changeTable)

    def changeTable(self, substring):
        self.substring = str(substring)
        with blockedSignals(self.table):
            self.table.clear()
            self.table.setRowCount(0)
            self.createTable()

    def createTable(self):
        i = 0
        self.table.setSortingEnabled(False)
        self.table.setColumnCount(2)
        self.table.setHorizontalHeaderLabels(self.verticalHeader())

        for item in self.firstColumn():
            if self.substring in item:
                self.table.setRowCount(self.table.rowCount() + 1)
                self.table.setCellWidget(i, 0, QLabel(item))
                second_item = self.getSecondColumnItem(item)
                self.table.setItem(i, 1, second_item)
                self.table.setVerticalHeaderItem(i, QTableWidgetItem(""))
                i += 1
        self.table.resizeColumnsToContents()
        self.gl.addWidget(self.table, 1, 0, 1, 2)

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
