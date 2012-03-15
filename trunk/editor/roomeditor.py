#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project
from structdata.area import Area

from changebgbutton import ChangeBGButton
from changebgmbutton import ChangeBGMButton

from areaeditor import AreaEditor

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room_name = room.id if room else ""
        self.area_x_start = -1
        self.area_y_start = -1
        self.area_x_stop = -1
        self.area_y_stop = -1
        self.released = False
        self.room_bg = QLabel(self)
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
        #self.setLayout(vertical_layout)
        self.connect(self.change_room_name,
                     SIGNAL("editingFinished()"),
                     self.setRoomName)


    def closeEvent(self, event):
        g_project.unsubscribe(self)

    def setRoomName(self):
        old_room = self.room_name
        new_room_name = self.change_room_name.text()
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
            self.room_bg.setMask(image.mask())
            self.change_room_name.setText(room.id)

    def changeCurrentRoom(self, room_id):
        self.room_name = str(room_id)
        if self.room_name:
            self.room_bg.setPixmap(QPixmap(g_project.data['rooms']\
                                         [self.room_name].bg))
            self.change_room_name.setText(room_id)

    def mousePressEvent(self, event):
        if (0 <= event.pos().x() - 10 <= self.room_bg.width()
            and 0 <= event.pos().y() - 10 <= self.room_bg.height()):
            self.area_x_start = event.pos().x() - 10
            self.area_y_start = event.pos().y() - 10
            self.released = False

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton:
            if self.area_x_start > -1:
                if(0 <= event.pos().x() - 10 <= self.room_bg.width()
                and 0 <= event.pos().y() - 10 <= self.room_bg.height()):
                    self.area_x_stop = event.pos().x() - 10
                    self.area_y_stop = event.pos().y() - 10
                    self.update()
        else:
            h = float(g_project.data['world'].height)
            w = float(g_project.data['world'].width)
            mouse_pos_x = float(event.pos().x() - 10)
            mouse_pos_y = float(event.pos().y() - 10)
            for area in g_project.data['rooms'][self.room_name].areas:
                if (float(area.x) <= mouse_pos_x / w <= (float(area.x) +
                                                              float(area.width))) and\
                   (float(area.y) <= mouse_pos_y / h <= (float(area.y) +
                                                         float(area.height))):
                    self.area_x_start = float(area.x) * w
                    self.area_x_stop = (float(area.x) + float(area.width)) * w
                    self.area_y_start = float(area.y) * h
                    self.area_y_stop = (float(area.y) + float(area.height)) * h
                    self.released = False
                    self.update()
                    break
                else:
                    self.released = True
                    self.update()

    def mouseReleaseEvent(self, event):
        if self.area_x_start > -1:
            if(0 <= event.pos().x() - 10 <= self.room_bg.width()
            and 0 <= event.pos().y() - 10 <= self.room_bg.height()):
                self.area_x_stop = event.pos().x() - 10
                self.area_y_stop = event.pos().y() - 10
                h = float(g_project.data['world'].height)
                w = float(g_project.data['world'].width)
                area_x = round(self.area_x_start / w, 3)
                area_y = round(self.area_y_start / h, 3)
                area_widht = round((self.area_x_stop - self.area_x_start) / w,
                                   3)
                area_height = round((self.area_y_stop - self.area_y_start) / h,
                                    3)
                g_project.data['rooms'][self.room_name].addArea(area_x,
                                                                area_y,
                                                                area_widht,
                                                                area_height)
                self.released = True
#                area = AreaEditor(self.area_x_start, self.area_y_start,
#                                      (self.area_x_stop - self.area_x_start),
#                                      (self.area_y_stop - self.area_y_start),
#                                      self)
#                area.show()
                self.update()
                g_project.notify()

    def paintEvent(self, event=None):
        painter = QPainter(self)
        if (self.area_x_start > -1 and self.area_x_stop > -1):
            if not self.released:
                painter.setPen(Qt.blue)
                rect = QRect(QPoint(self.area_x_start,
                                    self.area_y_start),
                             QPoint(self.area_x_stop ,
                                    self.area_y_stop))
                painter.drawRect(rect)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor(None)
    rm.show()
    app.exec_()
