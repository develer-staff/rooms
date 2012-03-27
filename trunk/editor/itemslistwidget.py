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
    icon_size = QSize(50, 50)

    def firstColumn(self):
        return g_project.data['items'].keys()

    def getIconImage(self, id_item):
        return g_project.data["items"][id_item].image

    def verticalHeader(self):
        return ["Item", ""]

    def setRowSelected(self, id_item):
        raise NotImplementedError
