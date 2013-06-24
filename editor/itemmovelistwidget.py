#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from itemslistwidget import ItemsListWidget

class ItemMoveListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item_move
    """

    def getInitialItemToSelect(self):
        if self.item is not None:
            return self.item.params[0].value
        return None
