#!/usr/bin/env python

import sys
from xml.etree import ElementTree
from xml.dom import minidom

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomEditor import RoomEditor
from roomManager import RoomManager

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structData.area import Area
from structData.requirement import Requirement
from structData.action import Action
from structData.param import Param
from structData.item import Item
from structData.event import Event

from openFileRooms import openFileRooms
from saveFileRooms import saveFileRooms

class Editor(QWidget):

    def __init__(self, parent=None):
        super(Editor, self).__init__(parent)
        self.version = None
        self.width_rooms = None
        self.height_rooms = None
        self.selected_room_name = None
        self.adventure_name = None
        self.start_room = None

        horizontal = QHBoxLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        self.informations, self.rooms, self.events, self.items, self.images = openFileRooms(self.path_file)
        self.selected_room_name = "Locanda"
        rooms_list = list()
        for key in self.rooms.keys():
            rooms_list.append((key, self.rooms[key].bg))
        room_editor = RoomEditor(parent=self, room=self.rooms[self.selected_room_name])
        room_manager = RoomManager(self, rooms=rooms_list)
        room_manager.setRoomSelected(self.selected_room_name)
        horizontal.addWidget(room_manager)
        horizontal.addWidget(room_editor)

        #self.selected_room_name = self.connect(room_manager,
         #                                      SIGNAL("changeRoomSelected(QString)"),
          #                                     self.changeRoom)
        #self.changeRoom(self.selected_room_name)
        file_open = QFileDialog()
        self.path_file = ""
        self.path_file = file_open.getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
        if self.path_file:
            saveFileRooms(self.path_file[0], self.rooms, self.events,
                          self.items, self.informations, self.images)

    def searchEvent(self, id):
        for event in self.events:
            if event.id == id:
                return event
        return None


if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
