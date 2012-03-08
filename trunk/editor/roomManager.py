#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structData.room import Room

class RoomList(QWidget):

    def __init__(self, parent=None, list_of_image=list()):

        super(RoomList, self).__init__(parent)
        self.list_of_image = list_of_image
        for img in self.list_of_image:
            self.addImage(img)

    def addImage(self, (name, path_image)):
        self.list_of_image.append((name, path_image))
        self.update()

    def paintEvent(self, event):
        print "entro"
        vertical = QVBoxLayout(self)
        for image in self.list_of_image:
            self.scroll_area = QScrollArea(self)
            self.scroll_area.setMinimumSize(260, 260)
            self.scroll_area.setSizePolicy(QSizePolicy.Fixed,
                                           QSizePolicy.Fixed)
            #self.scroll_area.setBackgroundRole(QPalette.Dark)
            self.scroll_area.setAlignment(Qt.AlignCenter)
            self.image_label = QLabel()
            image = QImage(image[1]).scaled(250, 250)
            self.image_label.setPixmap(QPixmap.fromImage(image))
            self.scroll_area.setWidget(self.image_label)
            vertical.addWidget(self.scroll_area, Qt.AlignCenter)


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
        self.room_list = RoomList(self, rooms)
        #vertical_scroll.setAlignment(Qt.Vertical)
        self.vertical_scroll.setWidget(self.room_list)

