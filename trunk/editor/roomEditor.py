#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *
from structData.world import g_world

class RoomEditor(QWidget):

    def __init__(self, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room = g_world.rooms[g_world.informations.start]
        self.setSizePolicy(QSizePolicy(QSizePolicy.Expanding,
                                       QSizePolicy.Expanding))
        self.setMinimumSize(1000, 1000)
        self.label = QLabel()
        self.scroll_area = QScrollArea(self)
        self.scroll_area.setMinimumSize(900, 900)
        self.scroll_area.setSizePolicy(QSizePolicy.Expanding,
                                       QSizePolicy.Expanding)
        self.scroll_area.setBackgroundRole(QPalette.Dark)
        self.scroll_area.setAlignment(Qt.AlignCenter)
        self.change_room_name = QLineEdit(self)
        self.change_room_name.setText("Room name")
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_name.move(self.scroll_area.height() / 2,
                                   self.scroll_area.width())
        image = QPixmap(self.room.bg)
        self.label.setPixmap(image)
        self.scroll_area.setWidget(self.label)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor()
    rm.show()
    app.exec_()
