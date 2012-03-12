#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *


from structData.room import Room
from structData.world import g_world

class RoomManager(QWidget):

    def __init__(self, parent=None):
        super(RoomManager, self).__init__(parent)
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
        for key, value in g_world.rooms.items():
            image = QImage(value.bg)
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(image)),
                                        value.id)
            self.rooms_list.addItem(room_item)
            if value.id == self.selected_room:
                room_item.setSelected(True)

        #vertical_scroll.setAlignment(Qt.Vertical)
        #self.vertical_scroll.setWidget(rooms_list)
        self.connect(self.rooms_list,
                     SIGNAL("currentTextChanged(const QString &)"),
                     SIGNAL("currentRoomChanged(const QString &)"))

    def setRoomSelected(self, room_name):
        item = self.rooms_list.findItems(room_name, Qt.MatchFixedString)
        if item:
            item[0].setSelected(True)
