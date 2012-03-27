#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project

from roomslistwidget import RoomsListWidget

class VarsListWidget(RoomsListWidget):

    """
    classe che eredita da RoomListWidget, serve per mostrare le VARS nel modello
    dei dati. Per generalizzare rispetto a requirement e a action sulle
    variabili le classi derivate devono reimplementare la funzione 
    secondColumnItem
    """

    horizontal_header = ["Name", "Value"]

    def firstColumn(self):
        return g_project.data['vars'].keys()

    def getSecondColumnItem(self, id_item):
        second_column_item = QTableWidgetItem(self.secondColumnItem(id_item))
        return second_column_item

    def getInitialItemToSelect(self):
        return None

    def secondColumnItem(self, id_item):
        raise NotImplementedError

    def createSignals(self):
        self.connect(self.table, SIGNAL("itemChanged(QTableWidgetItem *)"),
                     self.signal)

    def signal(self, item):
        self.emit(SIGNAL("editedElement(QString, QString)"),
                  self.table.item(item.row(), 0).text(),
                  item.text())


