#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from roomitemlistwidget import RoomItemListWidget

from structdata import g_project

class RoomListWidget(RoomItemListWidget):

    """
    Classe generica per la visualizzazione delle room. Eredita dalla classe
    RoomItemListWidget e implementa i metodi specifici necessari per la
    visualizzazione delle room. Le classi derivate devono andare a implementare
    la funzione getRowSelected che indica quale riga della tabella deve essere
    selezionata appena la tabella viene mostrata
    """

    def firstColumn(self):
        return g_project.data['rooms'].keys()

    def getIconImage(self, id_item):
        return g_project.data["rooms"][id_item].bg

    def verticalHeader(self):
        return ["Room", ""]
