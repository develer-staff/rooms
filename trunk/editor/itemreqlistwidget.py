#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from itemslistwidget import ItemsListWidget

class ItemReqListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item nel caso in cui
    si stia lavorando con un requirement di tipo item_req
    """

    def setRowSelected(self, id_item):
        if self.item is not None:
            item = self.table.findItems(id_item, Qt.MatchExactly)
            if item:
                row = item[0].row()
                self.table.selectRow(row)
