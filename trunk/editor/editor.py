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
        self.dirty = False
        g_project.subscribe(self)
        grid_layout = QGridLayout(self)
        file_open = QFileDialog()
        self.path_file = file_open.getOpenFileName(filter="*.rooms")
        try:
            openFileRooms(self.path_file)
        except ValueError as val_err:
            print val_err
            self.room = None
        else:
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
        self.connect(new_room_button, SIGNAL("clicked()"), g_project.addNewRoom)

    def update_data(self):
        self.dirty = True

    def closeEvent(self, event):
        if self.dirty:
            ret = QMessageBox.question(self, "Save", "Do you want save the file?",
                                       QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
            if ret == QMessageBox.Yes:
                self.path_file = QFileDialog().getSaveFileNameAndFilter(parent=self,
                                                                filter="*.rooms")
                if self.path_file:
                    try:
                        saveFileRooms(self.path_file[0])
                    except ValueError:
                        print "Unable to save file"
                        event.ignore()
                    else:
                        g_project.unsubscribe(self)
                        self.dirty = False
            elif ret == QMessageBox.Cancel:
                event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
