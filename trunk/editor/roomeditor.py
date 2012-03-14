#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project
from structdata.area import Area

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room_name = room.id if room else ""
        self.area_x_start = -1
        self.area_y_start = -1
        self.area_x_stop = -1
        self.area_y_stop = -1
        self.setSizePolicy(QSizePolicy(QSizePolicy.Expanding,
                                       QSizePolicy.Expanding))
        self.setMinimumSize(1000, 900)
        self.label = QLabel()
        #self.label.setMinimumSize(860, 860)
        #self.label.setSizePolicy(QSizePolicy.Fixed,
                                 #QSizePolicy.Fixed)
        self.scroll_area = QScrollArea(self)
        self.scroll_area.setMinimumSize(900, 900)
        #self.scroll_area.setSizePolicy(QSizePolicy.Expanding,
         #                              QSizePolicy.Expanding)
        self.scroll_area.setBackgroundRole(QPalette.Dark)
        self.scroll_area.setAlignment(Qt.AlignCenter)

        self.change_room_name = QLineEdit(self)
        self.change_room_bgm = QPushButton(self)
        self.change_room_bg = QPushButton(self)

        self.setRoom(room)
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_name.move(self.scroll_area.width() / 2,
                                   self.scroll_area.height())


        self.scroll_area.setWidget(self.label)
        self.change_room_bgm.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.change_room_bgm.move(self.label.mapFrom(parent,
                                                     QPoint(self.label.rect().\
                                                            topLeft().x(),
                                                            self.label.rect().\
                                                            topLeft().y())))
        self.change_room_bgm.setIcon(QIcon("musical_note.png"))
        self.change_room_bgm.setIconSize(QSize(30, 30))
        self.change_room_bg.setStyleSheet("background-color:"
                                          " rgba( 255, 255, 255, 0% );")
        self.change_room_bg.setIcon(QIcon("PageTurn.jpg"))
        self.change_room_bg.setIconSize(QSize(30, 30))
        self.change_room_bg.setFixedSize(QSize(30, 30))
        self.change_room_bg.move(self.label.mapFrom(parent,
                                                    QPoint(self.label.rect().\
                                                           topRight().x() - 15,
                                                            self.label.rect().\
                                                            topRight().y() + \
                                                             10)))
        self.connect(self.change_room_name,
                     SIGNAL("textEdited(const QString &)"),
                     self.setRoomName)
        self.connect(self.change_room_bgm, SIGNAL("clicked()"),
                     self.setRoomBgm)
        self.connect(self.change_room_bg, SIGNAL("clicked()"),
                     self.setRoomBg)

    def closeEvent(self, event):
        g_project.unsubscribe(self)


    def setRoomBg(self):
        file_open = QFileDialog()
        path_file = file_open.getOpenFileName()
        if path_file:
            g_project.data['rooms'][self.room_name].bg = str(path_file)
            g_project.notify()

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
            image = QPixmap(room.bg)
            self.label.setMinimumSize(image.width(), image.height())
            self.label.setPixmap(image)
            self.label.setMask(image.mask())
            self.scroll_area.setMinimumSize(image.width() + 20,
                                            image.height() + 20)
            self.change_room_name.setText(room.id)

    def changeCurrentRoom(self, room_id):
        self.room_name = str(room_id)
        if self.room_name:
            self.label.setPixmap(QPixmap(g_project.data['rooms']\
                                         [self.room_name].bg))
            self.change_room_name.setText(room_id)

    def mousePressEvent(self, event):

        if (0 <= event.pos().x() - 10 <= self.label.width()
            and 0 <= event.pos().y() - 10 <= self.label.height()):
            self.area_x_start = event.pos().x() - 10
            self.area_y_start = event.pos().y() - 10

    def mouseReleaseEvent(self, event):
        if self.area_x_start > -1:
            if(0 <= event.pos().x() - 10 <= self.label.width()
            and 0 <= event.pos().y() - 10 <= self.label.height()):
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
                self.update()
                g_project.notify()

    def paintEvent(self, event=None):
        if self.area_x_start > -1 and self.area_x_stop > -1:
            pixmap = self.label.pixmap()
            painter = QPainter(pixmap)
            painter.setPen(Qt.blue)
            rect = QRect(QPoint(self.area_x_start + 10,
                                self.area_y_start + 10),
                         QPoint(self.area_x_stop + 10,
                                self.area_y_stop + 10))
            painter.drawRect(rect)
            self.label.setPixmap(pixmap)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor()
    rm.show()
    app.exec_()
