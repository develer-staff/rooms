#!/usr/bin/env python

from itemslistwidget import ItemsListWidget

class ItemReqListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item_req
    """

    def changeSelection(self, row, column):
        selection = self.table.selectedRanges()
        for sel in selection:
            if (sel.bottomRow() == row and sel.columnCount() == 2):
                index = selection.index(sel)
                selection.pop(index)
                self.table.setRangeSelected(selection)
                break
            elif sel.bottomRow() == row and sel.columnCount() == 1 and\
                 sel.leftColumn() == column:
                self.table.selectRow(row)
                break
