#!/usr/bin/env python


from PyQt4.QtGui import *
from PyQt4.QtCore import *

from utils import blockedSignals
from structdata.project import g_project


class RoomsListWidget(QWidget):
    """
    classe base utilizzata per mostare elementi del modello in una tabella
    alcune funzioni devono essere reimplementate dalle classi che la ereditano
    a seconda di cosa si vuole mostrare
    I parametri in ingresso sono l'evento a cui viene associata, l'item a cui
    si riferisce
    """


    horizontal_header = None

    def __init__(self, event, item, parent=None):
        super(RoomsListWidget, self).__init__(parent)
        self.setMinimumSize(300, 300)
        self.event = event
        self.item = item
        self.substring = ""
        self.search_line = QLineEdit(self)
        self.gl = QGridLayout()
        self.gl.addWidget(self.search_line, 0, 0)
        self.table = QTableWidget(self)
        self.createSignals()
        with blockedSignals(self.table):
            self.createTable()
        self.setLayout(self.gl)
        self.table.setFocus()
        self.connect(self.search_line, SIGNAL("textEdited(const QString &)"),
                     self.changeTable)

    def changeTable(self, substring):
        """
        funzione setta la stringa di ricerca per gli elementi che devono
        essere visualizzati nella tabella
        """
        self.substring = unicode(substring)
        with blockedSignals(self.table):
            self.table.clear()
            self.table.setRowCount(0)
            self.createTable()
            self.setInitialSelectRow(self.getInitialItemToSelect())

    def setInitialSelectRow(self, item_name):
        """
        funzione utilizzata per selezionare l'elemento in tabella una volta
        che questa e' stata creata
        """
        if item_name:
            item = self.table.findItems(item_name, Qt.MatchFixedString)
            row = item[0].row()
            self.table.selectRow(row)

    def createTable(self):
        i = 0
        self.table.setSortingEnabled(False)
        self.table.setColumnCount(2)
        self.table.setHorizontalHeaderLabels(self.horizontal_header)
        for item in self.firstColumn():
            #controllo per eseguire il filtraggio degli elementi della tabella
            if self.substring.lower() in item.lower():
                self.table.setRowCount(self.table.rowCount() + 1)
                name_item = QTableWidgetItem(item)
                name_item.setFlags(Qt.ItemIsSelectable | Qt.ItemIsEnabled)
                self.table.setItem(i, 0, name_item)
                second_item = self.getSecondColumnItem(item)
                self.table.setItem(i, 1, second_item)
                self.table.setVerticalHeaderItem(i, QTableWidgetItem(""))
                i += 1
        self.setInitialSelectRow(self.getInitialItemToSelect())
        self.table.resizeColumnsToContents()
        self.gl.addWidget(self.table, 1, 0, 1, 2)

    def getInitialItemToSelect(self):
        """
        funzione che ritorna il nome dell'item che deve essere selezionato
        una volta che e' stata costruita la tabella.
        Se non c'e' nessun elemento da selezionare torna None
        """

        raise NotImplementedError

    def createSignals(self):
        """
        funzione per la specifica dei segnali del widget. Deve essere
        implementata dalle classi derivate
        """
        raise NotImplementedError

    def firstColumn(self):
        """
        funzione che ritorna i valori da mettere in ogni riga della prima 
        colonna della tabella. Deve essere implementata dalle classi derivate
        """
        raise NotImplementedError

    def getSecondColumnItem(self, id_item):
        """
        funzione che ritorna, per ogni riga, l'item da inserire nella seconda 
        colonna. Alla funzione deve essere passato l'id dell'item che servira'
        come chiave per la ricerca. La funzione deve essere inplementata nelle
        classi derivate
        """
        raise NotImplementedError

    def verticalHeader(self):
        """
        Funzione che ritorna le intestazioni delle colonne della tabella.
        Deve essere implementata dalle classi derivate
        """
        raise NotImplementedError

if __name__ == "__main__":

    app = QApplication([])
    a = RoomsListWidget()
    a.show()
    app.exec_()
