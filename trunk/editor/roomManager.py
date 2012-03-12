#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *


from structData.room import Room
from structData.world import g_world

class RoomManager(QWidget):

    def __init__(self, parent=None):
        super(RoomManager, self).__init__(parent)
        g_world.subscribe(self)
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
        self.selected_room = g_world.informations.start
        self.rooms_list.setAlternatingRowColors(True)
        for key, value in g_world.rooms.items():
            image = QImage(value.bg)
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(image)),
                                        value.id)
            self.rooms_list.addItem(room_item)
            room_item.setForeground(Qt.black)
            if value.id == self.selected_room:
                room_item.setSelected(True)
                room_item.setBackgroundColor(Qt.yellow)
        #vertical_scroll.setAlignment(Qt.Vertical)
        #self.vertical_scroll.setWidget(rooms_list)
        self.connect(self.rooms_list,
                     SIGNAL("currentTextChanged(const QString &)"),
                     SIGNAL("currentRoomChanged(const QString &)"))

    def setRoomSelected(self, room_name):
        item = self.rooms_list.findItems(room_name, Qt.MatchFixedString)
        if item:
            item[0].setSelected(True)

    def contextMenuEvent(self, event):
        selected_item = self.rooms_list.selectedItems()[0]
        if self.selected_room != selected_item.text():
            selected_item.setBackground(Qt.yellow)
            self.rooms_list.findItems(self.selected_room,
                                      Qt.MatchFixedString)[0].setBackground(Qt.white)
        else:
            list_color = [Qt.white, Qt.yellow]
            color = list_color[(list_color.index(selected_item.background()) + 1) % 2]
            selected_item.setBackground(color)
        self.selected_room = selected_item.text()
        g_world.informations.start = str(self.selected_room)
        g_world.notify()


    def update(self):
        list_lenght = self.rooms_list.count()
        while list_lenght:
            self.rooms_list.takeItem(0)
            list_lenght -= 1
        for key, value in g_world.rooms.items():
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(QImage(value.bg))),
                                        key)
            self.rooms_list.addItem(room_item)
            if room_item.text() == g_world.informations.start:
                room_item.setBackgroundColor(Qt.yellow)
        item = self.rooms_list.findItems(self.selected_room,
                                  Qt.MatchFixedString)[0].setSelected(True)
