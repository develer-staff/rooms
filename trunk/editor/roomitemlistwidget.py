#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from roomslistwidget import RoomsListWidget

class RoomItemListWidget(RoomsListWidget):

    item_type = None

    icon_size = None

    def __init__(self, event, item, parent=None):
        super(RoomItemListWidget, self).__init__(event, item, parent)
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.changeSelection)

    def changeSelection(self, row, column):
        """
        funzione seleziona tutta la riga nella tabella dell'elemento che e' 
        stato selezionato
        """
        self.table.selectRow(row)

    def firstColumn(self):
        """
        funzione che ritorna i valori della prima colonna della tabella
        """
        raise NotImplementedError

    def getSecondColumnItem(self, id_item):
        """
        funzione che ritorna l'elemento della seconda colonna per l'elemento
        che ha l'id passato come parametro
        """
        second_column_item = self.secondColumnItem(id_item)
        return second_column_item

    def getIconImage(self, id_item):
        """
        funzione che ritorna l'icona da associare all'item
        """
        raise NotImplementedError

    def getItemSize(self, id_item):
        """
        Funzione che ritorna la dimensione dell'item. Deve essere implementata
        nelle classe derivate. Serve per dare altezza minore alle righe della
        tabella che sono associate a item o room che non hanno un'immagine
        associata
        """
        raise NotImplementedError

    def secondColumnItem(self, id_item):
        """
        funzione che ritorna un QtableWidgetItem della seconda colonna
        """
        self.table.setIconSize(self.icon_size)
        second_item = QTableWidgetItem()
        second_item.setSizeHint(self.getItemSize(id_item))
        icon = QIcon(self.getIconImage(id_item))
        self.table.setRowHeight(self.table.rowCount() - 1,
                                second_item.sizeHint().height())
        second_item.setIcon(icon)
        return second_item

    def verticalHeader(self):
        raise NotImplementedError

    def createSignals(self):
        self.connect(self.table, SIGNAL("cellClicked(int, int)"),
                     self.signal)

    def signal(self, row, col):
        self.emit(SIGNAL("changeSelectedItem(QString)"),
                  self.table.item(row, 0).text())
