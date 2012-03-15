#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project
from structdata.area import Area

from changebgbutton import ChangeBGButton
from changebgmbutton import ChangeBGMButton

from roombgimage import RoomBGImage

from areaeditor import AreaEditor

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room_name = room.id if room else ""

        self.room_bg = RoomBGImage()
        self.change_room_name = QLineEdit(self)
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_bgm = ChangeBGMButton()
        self.change_room_bg = ChangeBGButton()
        self.setRoom(room)
        self.setMouseTracking(True)
        self.room_bg.setMouseTracking(True)
        horizontal_button_layout = QHBoxLayout()
        horizontal_button_layout.addWidget(self.change_room_bgm)
        horizontal_button_layout.addStretch()
        horizontal_button_layout.addWidget(self.change_room_bg)
        vertical_layout = QVBoxLayout(self)
        vertical_layout.addLayout(horizontal_button_layout)
        vertical_layout.addWidget(self.room_bg)
        horizontal = QHBoxLayout()
        horizontal.setAlignment(Qt.AlignCenter)
        horizontal.addStretch()
        horizontal.addWidget(self.change_room_name)
        horizontal.addStretch()
        vertical_layout.addLayout(horizontal)
        vertical_layout.addStretch()
        self.setLayout(vertical_layout)
        self.connect(self.change_room_name,
                     SIGNAL("textChanged(const QString &)"),
                     self.setRoomName)
        self.connect(self.room_bg, SIGNAL("areaEdited"), self.createArea)


    def createArea(self, x_start, y_start, x_stop, y_stop):
        area = g_project.data['rooms'][self.room_name].\
        addArea(*self.createAreaParameter(x_start, y_start, x_stop, y_stop))
        g_project.notify()
        new_area = AreaEditor(area, self)
        new_area.show()

    def createAreaParameter(self, x_start, y_start, x_stop, y_stop):
        w = float(g_project.data['world'].width)
        h = float(g_project.data['world'].height)
        rel_x = round(min(x_start, x_stop) / w, 3)
        rel_y = round(min(y_start, y_stop) / h, 3)
        rel_width = round(abs(x_stop - x_start) / w, 3)
        rel_height = round(abs(y_stop - y_start) / h, 3)
        return (rel_x, rel_y, rel_width, rel_height)


    def closeEvent(self, event):
        g_project.unsubscribe(self)

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
            image = QPixmap(room.bg)
            self.room_bg.setMinimumSize(image.width(), image.height())
            self.room_bg.setPixmap(image)
            self.change_room_name.setText(room.id)

    def changeCurrentRoom(self, room_id):
        self.room_name = str(room_id)
        if self.room_name:
            self.room_bg.setPixmap(QPixmap(g_project.data['rooms']\
                                         [self.room_name].bg))
            self.change_room_name.setText(room_id)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor(None)
    rm.show()
    app.exec_()
