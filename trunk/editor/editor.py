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

from openfilerooms import openFileRooms, OpenFileError
from savefilerooms import saveFileRooms

class OpenProjectButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(OpenProjectButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("open_project.gif"))
        self.setIconSize(QSize(30, 30))

class SaveProjectButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(SaveProjectButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("save_project.png"))
        self.setIconSize(QSize(30, 30))

class Editor(QWidget):

    def __init__(self, parent=None):
        super(Editor, self).__init__(parent)
        self.dirty = False
        g_project.subscribe(self)
        grid_layout = QGridLayout(self)
        openFileRooms("dummy.rooms")
        self.room = g_project.data['rooms'][g_project.data['world'].start]
        room_editor = RoomEditor(self.room, self)
        room_manager = RoomManager(self.room, self)
        open_project_button = OpenProjectButton(self)
        save_project_button = SaveProjectButton(self)
        new_room_button = QPushButton("New room")
        grid_layout.addWidget(open_project_button, 0, 0)
        grid_layout.addWidget(save_project_button, 0, 1)
        grid_layout.addWidget(new_room_button, 0, 2)
        grid_layout.addWidget(room_manager, 1, 0, 1, 3)
        grid_layout.addWidget(room_editor, 1, 3, 2, 1)
        self.connect(room_manager,
                     SIGNAL("currentRoomChanged(const QString &)"),
                     room_editor.changeCurrentRoom)
        self.connect(new_room_button, SIGNAL("clicked()"), Room.create)
        self.connect(open_project_button, SIGNAL("clicked()"),
                     self.open_project)
        self.connect(save_project_button, SIGNAL("clicked()"),
                     self.save_project)

    def update_data(self):
        self.dirty = True

    def open_project(self):
        if self.dirty:
            result = self.save_project()
            self.dirty = False
        if not self.dirty or result:
            file_open = QFileDialog()
            self.path_file = file_open.getOpenFileName(filter="*.rooms")
            if self.path_file:
                try:
                    openFileRooms(self.path_file)
                    self.room = g_project.data['rooms'][g_project.data['world'].start]
                except OpenFileError as err:
                    print err
                g_project.notify()
                self.dirty = False

    def save_project(self):
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
                        return False
                    else:
                        g_project.unsubscribe(self)
                        self.dirty = False
            elif ret == QMessageBox.Cancel:
                return False
        return True

    def closeEvent(self, event):
        if not self.save_project():
            event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    app.exec_()
