#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.world import g_world

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
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
        self.change_room_name.setText(g_world.selected_room)
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_name.move(self.scroll_area.height() / 2,
                                   self.scroll_area.width())
        image = QPixmap(g_world.rooms[g_world.selected_room].bg)
        self.label.setPixmap(image)
        self.scroll_area.setWidget(self.label)
        self.connect(self.change_room_name,
                     SIGNAL("textEdited(const QString &)"),
                     self.setRoomName)

    def setRoomName(self, new_room_name):
        old_room = g_world.selected_room
        if g_world.informations.start == g_world.selected_room:
            g_world.informations.start = str(new_room_name)
        g_world.selected_room = str(new_room_name)
        room = g_world.rooms[old_room]
        room.id = str(new_room_name)
        del g_world.rooms[old_room]
        g_world.rooms[room.id] = room
        g_world.notify()

    def changeCurrentRoom(self, room_id):
        self.room = str(room_id)
        self.label.setPixmap(QPixmap(g_world.rooms[self.room].bg))
        self.change_room_name.setText(room_id)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor()
    rm.show()
    app.exec_()
