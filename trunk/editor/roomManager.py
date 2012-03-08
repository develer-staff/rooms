#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structData.room import Room

class RoomManager(QWidget):

    def __init__(self, parent=None, rooms=list()):
        super(RoomManager, self).__init__(parent)
        self.setMinimumSize(300, 1000)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed,
                                       QSizePolicy.Fixed))
        self.vertical_scroll = QScrollArea(self)
        self.vertical_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.vertical_scroll.setWidgetResizable(False)
        self.vertical_scroll.setMinimumSize(300, 1000)
        self.vertical_scroll.setAlignment(Qt.AlignVCenter)
        rooms_list = QListWidget(self)
        rooms_list.setIconSize(QSize(150, 150))
        for room in rooms:
            print room[0]
            image = QImage(room[1])
            room_item = QListWidgetItem(QIcon(QPixmap.fromImage(image)), room[0])
            rooms_list.addItem(room_item)
        #vertical_scroll.setAlignment(Qt.Vertical)
        self.vertical_scroll.setWidget(rooms_list)

