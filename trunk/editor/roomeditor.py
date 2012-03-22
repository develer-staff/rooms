#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project
from structdata import Area

from arearesize import AreaResize
from Tkconstants import SEL

class ChangeBGMButton(QToolButton):
    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(ChangeBGMButton, self).__init__(parent)
        self.setIcon(QIcon("musical_note.png"))
        self.setIconSize(QSize(30, 30))

class ChangeBGButton(QToolButton):
    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(ChangeBGButton, self).__init__(parent)

        self.setIcon(QIcon("PageTurn.jpg"))
        self.setIconSize(QSize(30, 30))

class ChangeRoomName(QLineEdit):
    pass

class RoomEditor(QWidget):

    def __init__(self, room=None, parent=None):
        super(RoomEditor, self).__init__(parent)
        self.room = room
        self.room_bg = QPixmap(room.bg)
        self.setMinimumSize(self.room_bg.width(), self.room_bg.height())
        self.setSizePolicy(QSizePolicy(QSizePolicy.Preferred,
                                       QSizePolicy.Preferred))
        g_project.subscribe(self)

        self.area_drag_start = None
        self.area_drag_curr = None
        self.resize_areas = []

        self.change_room_name = ChangeRoomName()
        self.change_room_name.setAlignment(Qt.AlignCenter)
        self.change_room_bgm = ChangeBGMButton()
        self.change_room_bg = ChangeBGButton()
        self.setRoom(self.room)
        self.setMouseTracking(True)

        horizontal_button_layout = QHBoxLayout()
        horizontal_button_layout.addWidget(self.change_room_bgm)
        horizontal_button_layout.addStretch()
        horizontal_button_layout.addWidget(self.change_room_bg)

        vertical_layout = QVBoxLayout()
        vertical_layout.addLayout(horizontal_button_layout)
        vertical_layout.addStretch()
        horizontal = QHBoxLayout()
        horizontal.setAlignment(Qt.AlignCenter)
        horizontal.addStretch()
        horizontal.addWidget(self.change_room_name)
        horizontal.addStretch()
        vertical_layout.addLayout(horizontal)

        self.setLayout(vertical_layout)

        self.createAllAreaResize()

        self.connect(self.change_room_name,
                     SIGNAL("returnPressed()"),
                     self.setRoomName)
        self.connect(self.change_room_bg, SIGNAL("clicked()"), self.setRoomBg)
        self.connect(self.change_room_bgm, SIGNAL("clicked()"), self.setRoomBgm)


    def createAllAreaResize(self):
        """
        funzione che mostra tutte le aree mediante AreaResize
        nella room corrente
        """
        self.resize_areas = []
        for area in self.room.areas:
            self.createAreaResize(area)

    def createAreaResize(self, area):
        area_resize = AreaResize(area, self.room_bg.width(),
                                     self.room_bg.height(), self)
        area_resize.move(float(area.x), float(area.y))
        self.resize_areas.append(area_resize)
        area_resize.show()

    def setRoomBg(self):
        """funzione per settare il background della room"""
        file_open = QFileDialog()
        path_file = file_open.getOpenFileName()
        if path_file:
            self.room.bg = str(path_file)
            g_project.notify()

    def setRoomBgm(self):
        """funzione per settare la background music della room"""
        file_open = QFileDialog()
        path_file = file_open.getOpenFileName()
        if path_file:
            self.room.bgm = str(path_file)
            g_project.notify()

    def createArea(self, x_start, y_start, x_stop, y_stop):
        area = Area.create(self.room, max(0, x_start), max(0, y_start),
                           min(x_stop, self.room_bg.width()),
                           min(y_stop, self.room_bg.height()))
        g_project.notify()
        self.createAreaResize(area)


    def mousePressEvent(self, event=None):
        if 0 <= event.pos().x() <= self.room_bg.width() and\
           0 <= event.pos().y() <= self.room_bg.height():
            self.area_drag_start = event.pos()
            self.area_drag_curr = event.pos()
            self.update()

    def keyPressEvent(self, event=None):
        if event.key() == Qt.Key_Escape:
            self.area_drag_start = None
            self.area_drag_curr = None
            self.update()


    def mouseMoveEvent(self, e):
        if self.area_drag_start is None:
            return
        #controllo di essere nell'area dell'mmagine di sfondo
        x = self.clamp(e.x(), self.room_bg.width())
        y = self.clamp(e.y(), self.room_bg.height())
        self.area_drag_curr = QPoint(x, y)
        self.update()

    def clamp(self, value, maximium):
        return min(value, maximium) if value > 0 else maximium(0, value)

    def mouseReleaseEvent(self, e):
        if self.area_drag_curr is None:
            return
        x = min(self.area_drag_start.x(), self.area_drag_curr.x())
        y = min(self.area_drag_start.y(), self.area_drag_curr.y())
        width = abs(self.area_drag_curr.x() - self.area_drag_start.x())
        height = abs(self.area_drag_curr.y() - self.area_drag_start.y())
        self.createArea(x, y, width, height)

        self.area_drag_start = None
        self.area_drag_curr = None

        self.update()

    def paintEvent(self, e):
        QWidget.paintEvent(self, e)

        p = QPainter(self)
        p.drawPixmap(QPoint(0, 0), self.room_bg)
        p.setPen(Qt.blue)
        # Draw currently painted area
        if self.area_drag_start is not None and self.area_drag_curr is not None:
            p.drawRect(QRect(self.area_drag_start.x(),
                             self.area_drag_start.y(),
                       self.area_drag_curr.x() - self.area_drag_start.x(),
                       self.area_drag_curr.y() - self.area_drag_start.y()))

    def closeEvent(self, event):
        g_project.unsubscribe(self)

    def setRoomName(self):
        """funzione per il cambio del nome della room"""
        new_room_name = str(self.change_room_name.text())
        if g_project.data['world'].start == self.room.id:
            g_project.data['world'].start = new_room_name
        for key, item in g_project.data['items'].items():
            if item.room == self.room.id:
                item.room = new_room_name
        del g_project.data['rooms'][self.room.id]
        self.room.id = new_room_name
        g_project.data['rooms'][self.room.id] = self.room
        g_project.notify()

    def setRoom(self, room):
        if room:
            self.room = room
            self.change_room_name.setText(self.room.id)
            self.room_bg = QPixmap(self.room.bg)

    def changeCurrentRoom(self, room_id):
        """
        funzione per cambiare la room visualizzata, prende in ingresso
        l'id della room che deve essere visualizzata
        """
        self.room = g_project.data['rooms'][str(room_id)]
        if self.room:
            self.room_bg = QPixmap(self.room.bg)
            self.change_room_name.setText(self.room.id)
            for resize_area in self.resize_areas:
                resize_area.deleteLater()
            self.createAllAreaResize()
            self.update()

    def updateData(self):
        self.setRoom(self.room)
        self.setMinimumSize(int(g_project.data['world'].width),
                          int(g_project.data['world'].height))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor(None)
    rm.show()
    app.exec_()
