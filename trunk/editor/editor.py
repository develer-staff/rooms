#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomEditor import RoomEditor
import sys
from room import Room
from roomManager import RoomManager
from xml.etree import ElementTree
from area import Area
from request import Request
from action import Action
from param import Param
from item import Item
from event import Event
from xml.dom import minidom
from openFileRooms import openFileRooms
from saveFileRooms import saveFileRooms

class Editor(QWidget):

    def __init__(self, parent=None):
        super(Editor, self).__init__(parent)
        self.version = 0
        self.width_rooms = 0
        self.height_rooms = 0
        self.selected_room_name = ""
        self.adventure_name = ""
        self.start_room = ""

        horizontal = QHBoxLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        self.informations, self.rooms, self.events, self.items, self.images = openFileRooms(self.path_file)
        room_editor = RoomEditor(self)
        room_manager = RoomManager(self)
        horizontal.addWidget(room_manager)
        horizontal.addWidget(room_editor)
        self.selected_room_name = "Locanda"
        self.connect(room_manager, SIGNAL("pressButton"), self.changeRoom)
        self.changeRoom(self.selected_room_name)
        file_open = QFileDialog()
        self.path_file = ""
        self.path_file = file_open.getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
        if self.path_file:
            saveFileRooms(self.path_file, self.rooms, self.events,
                          self.items, self.informations, self.images)

    def searchEvent(self, id):
        for event in self.events:
            if event.id == id:
                return event
        return None

    def changeRoom(self, name):
        self.emit(SIGNAL("roomChanged"), self.searchRoom(name))

    def addRoom(self, new_room):
        self.rooms.append(new_room)

    def searchRoom(self, id):
        return self.rooms[id]

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
