#!/usr/bin/env python

from contextlib import contextmanager

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata import Room
from structdata import g_project

@contextmanager
def blockedSignals(widget):
    widget.blockSignals(True)
    try:
        yield
    finally:
        widget.blockSignals(False)

class RoomManager(QWidget):

    def __init__(self, selected_room=None, parent=None):
        super(RoomManager, self).__init__(parent)
        self.selected_room = selected_room
        g_project.subscribe(self)
        self.setMinimumSize(300, 900)
        self.vertical_scroll = QScrollArea(self)
        self.vertical_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.vertical_scroll.setWidgetResizable(False)
        self.vertical_scroll.setMinimumSize(300, 900)
        self.vertical_scroll.setAlignment(Qt.AlignVCenter)
        self.rooms_list = QListWidget(self)
        self.rooms_list.setMinimumSize(300, 900)
        self.rooms_list.setIconSize(QSize(150, 150))
        if selected_room:
            for key, value in g_project.data['rooms'].items():
                room_item = QListWidgetItem(QIcon(QPixmap.\
                                                  fromImage(QImage(value.bg))),
                                            value.id)
                self.rooms_list.addItem(room_item)
                room_item.setForeground(Qt.black)
                if value.id == self.selected_room.id:
                    room_item.setSelected(True)
                    room_item.setBackgroundColor(Qt.yellow)
            self.connect(self.rooms_list,
                         SIGNAL("currentTextChanged(const QString &)"),
                         SIGNAL("currentRoomChanged(const QString &)"))
            self.connect(self.rooms_list,
                         SIGNAL("currentTextChanged(const QString &)"),
                         self.updateRoomSelected)


    def updateRoomSelected(self, room_name):
        if room_name:
            self.selected_room = g_project.data['rooms'][str(room_name)]

    def contextMenuEvent(self, event):
        self.changeStartRoom()

    def changeStartRoom(self):
        """function to change the start room in g_project"""
        start_item = self.rooms_list.findItems(g_project.data['world'].start,
                                  Qt.MatchFixedString)[0]
        start_item.setBackground(Qt.white)
        selected_item = self.rooms_list.selectedItems()[0]
        selected_item.setBackground(Qt.yellow)
        self.selected_room = g_project.data['rooms'][str(selected_item.text())]
        g_project.data['world'].start = self.selected_room.id
        g_project.notify()

    def closeEvent(self, event):
        g_project.unsubscribe(self)

    def update_data(self):
        self.updateRoomList()

    def updateRoomList(self):
        """function to update the room list"""
        with blockedSignals(self.rooms_list):
            self.rooms_list.clear()
        for key, value in g_project.data['rooms'].items():
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(QImage(value.bg))),
                                        key)
            self.rooms_list.addItem(room_item)
            if room_item.text() == g_project.data['world'].start:
                room_item.setBackgroundColor(Qt.yellow)
        try:
            current_room = self.rooms_list.findItems(self.selected_room.id,
                                                     Qt.MatchFixedString)[0]
        except IndexError:
            current_room = self.rooms_list.findItems(g_project.data['world'].\
                                                     start,
                                                     Qt.MatchFixedString)[0]
        current_room.setSelected(True)
        self.emit(SIGNAL("currentRoomChanged(const QString &)"),
                  current_room.text())
