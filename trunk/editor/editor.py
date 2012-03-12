#!/usr/bin/env python

import sys
from xml.etree import ElementTree
from xml.dom import minidom

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomEditor import RoomEditor
from roomManager import RoomManager

from structData.area import Area
from structData.requirement import Requirement
from structData.action import Action
from structData.param import Param
from structData.item import Item
from structData.event import Event
from structData.world import g_world

from openFileRooms import openFileRooms
from saveFileRooms import saveFileRooms

class Editor(QWidget):

    def __init__(self, parent=None):
        super(Editor, self).__init__(parent)
        self.struct_data_dictionary = {}

        grid_layout = QGridLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        openFileRooms(self.path_file)
        #self.selected_room = g_world.informations.start
        room_editor = RoomEditor(self)
        room_manager = RoomManager(self)
        #room_manager.setRoomSelected(g_world.informations.start)
        new_room_button = QPushButton("New room")
        grid_layout.addWidget(new_room_button, 0, 0)
        grid_layout.addWidget(room_manager, 1, 0)
        grid_layout.addWidget(room_editor, 0, 1, 2, 1)
        self.connect(room_manager,
                     SIGNAL("currentRoomChanged(const QString &)"),
                     room_editor.changeCurrentRoom)
        #self.selected_room_name = self.connect(room_manager,
         #                                      SIGNAL("changeRoomSelected(QString)"),
          #                                     self.changeRoom)
        #self.changeRoom(self.selected_room_name)
        file_open = QFileDialog()
        self.path_file = ""
        self.path_file = file_open.getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
        if self.path_file:
            saveFileRooms(self.path_file[0])


if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
