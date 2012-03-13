#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *


from structdata.room import Room
from structdata.project import g_project

class RoomManager(QWidget):

    def __init__(self, selected_room=None, parent=None):
        super(RoomManager, self).__init__(parent)
        self.selected_room = selected_room
        g_project.subscribe(self)
        self.setMinimumSize(300, 1000)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed,
                                       QSizePolicy.Fixed))
        self.vertical_scroll = QScrollArea(self)
        self.vertical_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.vertical_scroll.setWidgetResizable(False)
        self.vertical_scroll.setMinimumSize(300, 1000)
        self.vertical_scroll.setAlignment(Qt.AlignVCenter)
        self.rooms_list = QListWidget(self)
        self.rooms_list.setMinimumSize(300, 1000)
        self.rooms_list.setIconSize(QSize(150, 150))
        self.rooms_list.setAlternatingRowColors(True)
        for key, value in g_project.data['rooms'].items():
            image = QImage(value.bg)
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(image)),
                                        value.id)
            self.rooms_list.addItem(room_item)
            room_item.setForeground(Qt.black)
            if value.id == self.selected_room.id:
                room_item.setSelected(True)
                room_item.setBackgroundColor(Qt.yellow)
        #vertical_scroll.setAlignment(Qt.Vertical)
        #self.vertical_scroll.setWidget(rooms_list)
        self.connect(self.rooms_list,
                     SIGNAL("currentTextChanged(const QString &)"),
                     SIGNAL("currentRoomChanged(const QString &)"))

    def contextMenuEvent(self, event):
        self.rooms_list.findItems(self.selected_room.id,
                                  Qt.MatchFixedString)[0].setBackground(Qt.white)
        selected_item = self.rooms_list.selectedItems()[0]
        selected_item.setBackground(Qt.yellow)
        self.selected_room = g_project.data['rooms'][str(selected_item.text())]
        g_project.data['world'].start = str(self.selected_room.id)
        g_project.notify()


    def update_data(self):
        list_lenght = self.rooms_list.count()
        while list_lenght:
            self.rooms_list.takeItem(0)
            list_lenght -= 1
        for key, value in g_project.data['rooms'].items():
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(QImage(value.bg))),
                                        key)
            self.rooms_list.addItem(room_item)
            if room_item.text() == self.selected_room.id:
                room_item.setBackgroundColor(Qt.yellow)
        self.rooms_list.findItems(self.selected_room.id,
                                  Qt.MatchFixedString)[0].setSelected(True)
