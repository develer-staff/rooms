#!/usr/bin/env python

import sys
from xml.etree import ElementTree
from xml.dom import minidom

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomeditor import RoomEditor
from roommanager import RoomManager

from structdata import Area
from structdata import Action
from structdata import Param
from structdata import Item
from structdata import Event
from structdata import Room
from structdata import g_project

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

    def __init__(self, file_name, parent=None):
        super(Editor, self).__init__(parent)
        self.dirty = False
        g_project.subscribe(self)
        grid_layout = QGridLayout(self)

        openFileRooms(file_name)

        self.room = g_project.data['rooms'][g_project.data['world'].start]
        room_editor = RoomEditor(self.room, self)
        room_manager = RoomManager(self.room, self)
        open_project_button = OpenProjectButton(self)
        self.save_project_button = SaveProjectButton(self)
        self.save_project_button.setEnabled(False)
        new_room_button = QPushButton("New room")
        grid_layout.addWidget(open_project_button, 0, 0)
        grid_layout.addWidget(self.save_project_button, 0, 1)
        grid_layout.addWidget(new_room_button, 0, 2)
        grid_layout.addWidget(room_manager, 1, 0, 1, 3)
        grid_layout.addWidget(room_editor, 1, 3, 2, 1)
        self.connect(room_manager,
                     SIGNAL("currentRoomChanged(const QString &)"),
                     room_editor.changeCurrentRoom)
        self.connect(new_room_button, SIGNAL("clicked()"), Room.create)
        self.connect(open_project_button, SIGNAL("clicked()"),
                     self.openProject)
        self.connect(self.save_project_button, SIGNAL("clicked()"),
                     self.saveProject)

    def updateData(self):
        self.save_project_button.setEnabled(True)
        self.dirty = True

    def openProject(self):
        if self.dirty:
            ret = QMessageBox.question(self, "Save", "Do you want save the file?",
                                       QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
            if ret == QMessageBox.Yes:
                if not self.save_project():
                    return
            elif ret == QMessageBox.Cancel:
                return
        if not self.dirty or ret:
            file_open = QFileDialog()
            self.path_file = file_open.getOpenFileName(filter="*.rooms")
            if self.path_file:
                g_project.unsubscribe(self)
                openFileRooms(self.path_file)
                g_project.subscribe(self)
                self.room = g_project.data['rooms'][g_project.data['world'].start]
                g_project.notify()
                #self.save_project_button.setEnabled(False)
                self.dirty = False
            return

    def saveProject(self):
        if self.dirty:
            self.path_file = QFileDialog().getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
            if self.path_file and self.path_file[0]:
                try:
                    saveFileRooms(self.path_file[0])
                except ValueError:
                    print "Unable to save file"
                    return False
                else:
                    g_project.unsubscribe(self)
                    self.dirty = False
                    self.save_project_button.setEnabled(False)
                return True
            else:
                return False

    def closeEvent(self, event):
        if self.dirty:
            ret = QMessageBox.question(self, "Save", "Do you want save the file?",
                                       QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
            if ret == QMessageBox.Yes:
                if not self.save_project():
                    event.ignore()
            elif ret == QMessageBox.Cancel:
                event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    file_name = "world.rooms"
    if len(sys.argv) == 2:
        file_name = str(sys.argv[1])
    editor = Editor(file_name)
    editor.show()
    app.exec_()
