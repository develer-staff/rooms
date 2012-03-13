#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room_name = room.id if room else ""
        self.setSizePolicy(QSizePolicy(QSizePolicy.Expanding,
                                       QSizePolicy.Expanding))
        self.setMinimumSize(1000, 1000)
        self.label = QLabel()
        #self.label.setMinimumSize(860, 860)
        #self.label.setSizePolicy(QSizePolicy.Fixed,
                                 #QSizePolicy.Fixed)
        self.scroll_area = QScrollArea(self)
        self.scroll_area.setMinimumSize(900, 900)
        self.scroll_area.setSizePolicy(QSizePolicy.Expanding,
                                       QSizePolicy.Expanding)
        self.scroll_area.setBackgroundRole(QPalette.Dark)
        self.scroll_area.setAlignment(Qt.AlignCenter)
        self.change_room_name = QLineEdit(self)
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_name.move(self.scroll_area.width() / 2,
                                   self.scroll_area.height())
        self.change_room_bgm = QPushButton(self)
        self.setRoom(room)
        self.scroll_area.setWidget(self.label)
        self.change_room_bgm.setStyleSheet("background-color: rgba( 255, 255, 255, 0% );")
        self.change_room_bgm.move(self.label.mapToGlobal(self.label.rect().topLeft()).x() + 50,
                                 (self.scroll_area.height() -
                                  self.label.height()) / 2)
        self.change_room_bgm.setIcon(QIcon("musical_note.png"))
        self.change_room_bgm.setIconSize(QSize(30, 30))
        self.connect(self.change_room_name,
                     SIGNAL("textEdited(const QString &)"),
                     self.setRoomName)
        self.connect(self.change_room_bgm, SIGNAL("clicked()"),
                     self.setRoomBgm)

    def closeEvent(self, event):
        g_project.unsubscribe(self)


    def setRoomBgm(self):
        file_open = QFileDialog()
        path_file = file_open.getOpenFileName()
        if path_file:
            g_project.data['rooms'][self.room_name].bgm = str(path_file)
            g_project.notify()

    def setRoomName(self, new_room_name):
        old_room = self.room_name
        if g_project.data['world'].start == old_room:
            g_project.data['world'].start = str(new_room_name)
        room = g_project.data['rooms'][old_room]
        room.id = str(new_room_name)
        del g_project.data['rooms'][old_room]
        g_project.data['rooms'][room.id] = room
        g_project.notify()

    def setRoom(self, room):
        if room:
            self.room_name = room.id
            self.label.setPixmap(QPixmap(room.bg))
            self.change_room_name.setText(room.id)

    def changeCurrentRoom(self, room_id):
        self.room_name = str(room_id)
        if self.room_name:
            self.label.setPixmap(QPixmap(g_project.data['rooms']\
                                         [self.room_name].bg))
            self.change_room_name.setText(room_id)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor()
    rm.show()
    app.exec_()
