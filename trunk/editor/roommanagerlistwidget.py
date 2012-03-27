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

    def setRowSelected(self, id_room):
        item = self.table.findItems(self.selected_room, Qt.MatchExactly)
        if item:
            self.table.selectRow(item[0].row())

    def highlightStartRoom(self):
        item = self.table.findItems(self.start_room.id, Qt.MatchExactly)
        if item:
            row = item[0].row()
            item[0].setBackground(Qt.yellow)
            item = self.table.item(row, 1)
            item.setBackground(Qt.yellow)

    def signal(self, row, col):
        self.emit(SIGNAL("currentRoomChanged(const QString &)"),
                  self.table.item(row, 0).text())

    def changeCurrentRoomName(self, new_name):
        self.selected_room = new_name

    def updateData(self):
        with blockedSignals(self.table):
            self.table.clear()
            self.table.setRowCount(0)
            self.createTable()
        self.highlightStartRoom()
        self.setRowSelected("")

