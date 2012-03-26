#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from itemslistwidget import ItemsListWidget

class ItemMoveListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item_move
    """

    def setRowSelected(self, id_item):
        if self.item is not None:
            for param in self.item.params:
                if param.value == id_item:
                    item = self.table.findItems(id_item, Qt.MatchExactly)
                    if item:
                        row = item[0].row()
                        self.table.selectRow(row)
                        break
        return
