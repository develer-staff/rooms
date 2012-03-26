#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project

from roomslistwidget import RoomsListWidget


class ItemsListWidget(RoomsListWidget):

    """
    Classe che eredita da RoomsListWidget, serve per mostrare gli ITEMS nel
    modello dei dati. Per generalizzare rispetto a ITEM_REQ e a ITEM_MOVE
    le classi derivate devono definire la funzione changeSelection che
    implementa la selezione degli elementi
    """


    def __init__(self, event, item, parent=None):
        super(ItemsListWidget, self).__init__(event, item, parent)
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.changeSelection)

    def changeSelection(self, row, column):
        raise NotImplementedError


    def firstColumn(self):
        return g_project.data['items'].keys()

    def getSecondColumnItem(self, id_item):
        second_column_item = QTableWidgetItem(self.secondColumnItem(id_item))
        return second_column_item

    def secondColumnItem(self, id_item):
        self.table.setIconSize(QSize(50, 50))
        second_item = QTableWidgetItem()
        second_item.setSizeHint(QSize(60, 60))
        icon = QIcon(g_project.data["items"][id_item].image)
        self.table.setRowHeight(self.table.rowCount() - 1,
                                second_item.sizeHint().height())
        second_item.setIcon(icon)

        return second_item

    def verticalHeader(self):
        return ["Item", ""]

    def createSignals(self):
        pass


