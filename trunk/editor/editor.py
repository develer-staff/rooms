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
        self.struct_data_dictionary = {}

        horizontal = QHBoxLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        self.struct_data_dictionary = openFileRooms(self.path_file)
        self.selected_room = self.struct_data_dictionary['rooms']\
                                 [self.struct_data_dictionary['informations']['start']]
        room_editor = RoomEditor(parent=self, room=self.selected_room)
        room_manager = RoomManager(parent=self, rooms=self.struct_data_dictionary['rooms'])
        room_manager.setRoomSelected(self.selected_room.name)
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
            saveFileRooms(self.path_file[0], self.struct_data_dictionary)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
