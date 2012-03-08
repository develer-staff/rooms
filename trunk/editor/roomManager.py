#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structData.room import Room

class RoomList(QWidget):

    def __init__(self, parent=None):
        super(RoomList, self).__init__(parent)
        vertical = QVBoxLayout(self)
        for key in parent.rooms.keys():
            self.scroll_area = QScrollArea(self)
            self.scroll_area.setMinimumSize(260, 260)
            self.scroll_area.setSizePolicy(QSizePolicy.Fixed,
                                           QSizePolicy.Fixed)
            #self.scroll_area.setBackgroundRole(QPalette.Dark)
            self.scroll_area.setAlignment(Qt.AlignCenter)
            if key == parent.selected_room_name:
                self.scroll_area.setBackgroundRole(QPalette.Dark)
            self.image_label = QLabel()

            image = QImage(parent.rooms[key].bg).scaled(250, 250)
            self.image_label.setPixmap(QPixmap.fromImage(image))
            self.scroll_area.setWidget(self.image_label)
            vertical.addWidget(self.scroll_area, Qt.AlignCenter)

class RoomManager(QWidget):

    def __init__(self, parent=None):
        super(RoomManager, self).__init__(parent)
        print "entro"
        self.setMinimumSize(300, 1000)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed,
                                       QSizePolicy.Fixed))
        vertical_scroll = QScrollArea(self)
        vertical_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        vertical_scroll.setWidgetResizable(False)
        vertical_scroll.setMinimumSize(300, 1000)
        vertical_scroll.setAlignment(Qt.AlignVCenter)
        self.room_list = RoomList(parent)
        #vertical_scroll.setAlignment(Qt.Vertical)
        vertical_scroll.setWidget(self.room_list)
            #verticalLayout.addWidget(self.scroll_area)
