#!/usr/bin/env python


from contextlib import contextmanager

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from roomlistwidget import RoomListWidget

@contextmanager
def blockedSignals(widget):
    widget.blockSignals(True)
    try:
        yield
    finally:
        widget.blockSignals(False)

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
        g_project.subscribe(self)
        self.highlightStartRoom()

    def setSelectRoom(self, room):
        self.selected_room = room.id

    def getInitialItemToSelect(self):
        return self.selected_room

    def closeEvent(self, event=None):
        g_project.unsubscribe(self)

    def highlightStartRoom(self):
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
        self.start_room = g_project.data['rooms']\
                          [g_project.data['world'].start]
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
        self.changeStartRoom()

    def changeStartRoom(self):
        """
        funzione per il cambio della room di partenza del progetto
        """
        selected_item = self.table.selectedItems()[0]
        item = self.table.item(selected_item.row(), 0)
        g_project.data['world'].start = str(item.text())
        self.start_room = g_project.data['rooms'][str(item.text())]
        g_project.notify()

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
        self.selected_room = str(self.table.item(item.row(), 0).text())


