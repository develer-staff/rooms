#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from itemslistwidget import ItemsListWidget

class ItemReqListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item nel caso in cui
    si stia lavorando con un requirement di tipo item_req
    """

    def getInitialItemToSelect(self):
        if self.item is not None:
            return self.item.id
        return None
