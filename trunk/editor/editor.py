#!/usr/bin/env python

import sys
from xml.etree import ElementTree
from xml.dom import minidom

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomeditor import RoomEditor
from roommanager import RoomManager

from structdata.area import Area
from structdata.requirement import Requirement
from structdata.action import Action
from structdata.param import Param
from structdata.item import Item
from structdata.event import Event
from structdata.room import Room
from structdata.project import g_project

from openfilerooms import openFileRooms
from savefilerooms import saveFileRooms

class Editor(QWidget):

    def __init__(self, parent=None):
        super(Editor, self).__init__(parent)
        g_project.subscribe(self)
        grid_layout = QGridLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        openFileRooms(self.path_file)
        self.room = g_project.data['rooms'][g_project.data['world'].start]
        room_editor = RoomEditor(self.room, self)
        room_manager = RoomManager(self.room, self)
        new_room_button = QPushButton("New room")
        grid_layout.addWidget(new_room_button, 0, 0)
        grid_layout.addWidget(room_manager, 1, 0)
        grid_layout.addWidget(room_editor, 0, 1, 2, 1)
        self.connect(room_manager,
                     SIGNAL("currentRoomChanged(const QString &)"),
                     room_editor.changeCurrentRoom)
        self.connect(new_room_button, SIGNAL("clicked()"), self.addNewRoom)

    def addNewRoom(self):
        number_of_new_room = 0
        for key in g_project.data['rooms'].keys():
            if key.find("new_room") != -1:
                number_of_new_room += 1
        room = Room("new_room_%d" % (number_of_new_room + 1), "", "")
        g_project.data['rooms'][room.id] = room
        g_project.notify()

    def update_data(self):
        pass

    def closeEvent(self, event):
        ret = QMessageBox.question(self, "Save", "Do you want save the file?",
                                   QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
        if ret == QMessageBox.Yes:
            self.path_file = QFileDialog().getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
            if self.path_file:
                saveFileRooms(self.path_file[0])
        elif ret == QMessageBox.Cancel:
            event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
