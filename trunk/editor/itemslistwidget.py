#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import g_project

from roomslistwidget import RoomsListWidget


class ItemListWidget(RoomsListWidget):

    """
    Classe che eredita da RoomsListWidget, serve per mostrare gli ITEMS nel
    modello dei dati. Per generalizzare rispetto a ITEM_REQ e a ITEM_MOVE
    le classi derivate devono reimplementare la funzione secondColumnItem
    """



