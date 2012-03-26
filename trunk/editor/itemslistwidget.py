#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project

from roomitemlistwidget import RoomItemListWidget


class ItemsListWidget(RoomItemListWidget):

    """
    Classe che eredita da RoomsListWidget, serve per mostrare gli ITEMS nel
    modello dei dati. Per generalizzare rispetto a ITEM_REQ e a ITEM_MOVE
    le classi derivate devono definire la funzione changeSelection che
    implementa la selezione degli elementi
    """

    def firstColumn(self):
        return g_project.data['items'].keys()

    def getIconSize(self):
        return QSize(50, 50)

    def getIconImage(self, id_item):
        return g_project.data["items"][id_item].image

    def verticalHeader(self):
        return ["Item", ""]

    def setRowSelected(self, id_item):
        raise NotImplementedError

    def signal(self, row, col):
        self.emit(SIGNAL("changeSelectedItem(QString, QString)"),
                  self.table.item(row, 0).text(),
                  "item")


