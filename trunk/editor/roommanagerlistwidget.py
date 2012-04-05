#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from roomlistwidget import RoomListWidget

from utils import blockedSignals

class RoomManager(RoomListWidget):

    """
    classe utilizzata per visualizzare la lista di tutte le room del modello
    deriva da RoomListWidget, reimplementa la funzione signal
    """
    icon_size = QSize(150, 150)

    def sizeHint(self):
        return QSize(400, 800)

    def getIconSize(self):
        return QSize(150, 150)

    def __init__(self, event=None, item=None, parent=None):
        self.start_room = g_project.data['rooms']\
                          [g_project.data['world'].start]
        self.selected_room = self.start_room.id
        super(RoomManager, self).__init__(event, item, parent)
        self.highlightStartRoom()

    def setSelectRoom(self, room):
        if room is not None:
            self.selected_room = room.id

    def getInitialItemToSelect(self):
        return self.selected_room

    def highlightStartRoom(self):
        if self.start_room:
            item = self.table.findItems(self.start_room.id, Qt.MatchExactly)
            if item:
                row = item[0].row()
                item[0].setBackground(Qt.yellow)
                item = self.table.item(row, 1)
                item.setBackground(Qt.yellow)

    def changeCurrentRoomName(self, new_name):
        """
        funzione per settare il nome della room correntemente selezionata
        qualora il nome venga modificato
        """
        self.selected_room = new_name

    def updateData(self):
        if self.selected_room not in g_project.data['rooms'].keys():
            self.selected_room = ""
        if g_project.data['world'].start:
            self.start_room = g_project.data['rooms']\
                              [g_project.data['world'].start]
        else:
            self.start_room = ""
        with blockedSignals(self.table):
            self.table.clear()
            self.table.setRowCount(0)
            self.createTable()
        self.highlightStartRoom()

    def contextMenuEvent(self, event=None):
        """
        gestione dell'evento di pressione del tasto destro del mouse. Quando
        viene premuto si cambia la room di partenza del progetto
        """
        self.updateStartRoom()

    def updateStartRoom(self):
        """
        funzione per il cambio della room di partenza del progetto
        """
        selected_item = self.table.selectedItems()[0]
        item = self.table.item(selected_item.row(), 0)
        room_name = unicode(item.text())
        self.start_room = room_name
        g_project.changeStartRoom(self.start_room)

    def firstColumnKeys(self):
        """
        funzione che ritorna le chiavi delle room che servono per costruire
        la tabella per la visualizzazione delle room. La funzione elimina 
        le room logiche (le room che cominciano con !)
        """
        key_list = []
        for key in g_project.data['rooms'].keys():
            if not key.startswith("!"):
                key_list.append(key)
        return key_list

    def changeSelection(self, row, column):
        """
        reimplementazione della funzione in nella classe base
        RoomItemListWidget. In questa versione viene anche salvata la 
        room che e' stata selezionata
        """
        super(RoomManager, self).changeSelection(row, column)
        item = self.table.selectedItems()[0]
        self.selected_room = unicode(self.table.item(item.row(), 0).text())


