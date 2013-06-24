#!/usr/bin/env python

import os

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomitemlistwidget import RoomItemListWidget

from structdata import g_project
from utils import g_ptransform

class RoomListWidget(RoomItemListWidget):

    """
    Classe generica per la visualizzazione delle room. Eredita dalla classe
    RoomItemListWidget e implementa i metodi specifici necessari per la
    visualizzazione delle room. Le classi derivate devono andare a implementare
    la funzione getRowSelected che indica quale riga della tabella deve essere
    selezionata appena la tabella viene mostrata
    """


    horizontal_header = ["Room", ""]

    def firstColumn(self):
        return self.firstColumnKeys()

    def firstColumnKeys(self):
        """
        funzione che ritorna le chiavi per la costruzione della tabella
        se un oggetto derivato deve filtrare in qualche modo le chiavi
        ritornate deve reimplementare questa funzione
        """
        return g_project.data['rooms'].keys()

    def getIconImage(self, id_item):
        room_bg_path = g_project.data["rooms"][id_item].bg
        if os.path.exists(room_bg_path):
            return room_bg_path
        else:
            return g_ptransform.relativeToAbsolute(g_project.data["rooms"][id_item].bg)

    def getItemSize(self, id_item):
        if g_project.data['rooms'][id_item].bg:
            return QSize(self.icon_size.width() + 10,
                         self.icon_size.height() + 10)
        return QSize(0, 25)
