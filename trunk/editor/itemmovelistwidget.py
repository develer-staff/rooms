#!/usr/bin/env python


from itemslistwidget import ItemsListWidget

class ItemMoveListWidget(ItemsListWidget):

    """
    classe utilizzata per la visualizzazione degli item_move
    """

    def changeSelection(self, row, column):
        self.table.setSelection([])
        self.table.selectRow(row)

    def setRowSelected(self, id_item):
        row = self.table.rowCount() - 1
        for action in self.event.actions:
            if action.id.upper() == "ITEM_MOVE":
                for param in action.params:
                    if param.value == id_item:
                        self.table.selectRow(row)
                        return

