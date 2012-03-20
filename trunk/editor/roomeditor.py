#!/usr/bin/env python

import sys
from xml.etree.ElementTree import ElementTree

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project
from structdata.area import Area

from arearesize import AreaResize

class ChangeBGMButton(QPushButton):
    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(ChangeBGMButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("musical_note.png"))
        self.setIconSize(QSize(30, 30))

class ChangeBGButton(QPushButton):
    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(ChangeBGButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
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
        self.area_drag_stop = None
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

        self.showAllArea()

        self.connect(self.change_room_name,
                     SIGNAL("returnPressed()"),
                     self.setRoomName)
        self.connect(self.change_room_bg, SIGNAL("clicked()"), self.setRoomBg)
        self.connect(self.change_room_bgm, SIGNAL("clicked()"), self.setRoomBgm)


    def showAllArea(self):
        """funzione che mostra tutte le aree nella room corrente"""
        for area in self.room.areas:
            area_resize = AreaResize(area, self.room_bg.width(),
                                     self.room_bg.height(), self)
            area_resize.move(QPoint(self.logicalToAbsolute(area.x, 'x'),
                                    self.logicalToAbsolute(area.y, 'y')))
            self.resize_areas.append(area_resize)
            area_resize.show()

    def logicalToAbsolute(self, value, direction):
        if direction == 'x':
            w = float(g_project.data['world'].width)
            return float(value) * w
        elif direction == 'y':
            h = float(g_project.data['world'].height)
            return float(value) * h

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
        area = Area.create(self.room,
                           *self.createAreaParameter(max(0, x_start),
                                                     max(0, y_start),
                                                     min(x_stop,
                                                         self.room_bg.width()),
                                                     min(y_stop,
                                                         self.room_bg.height())
                                                    ))
        g_project.notify()
        area_resize = AreaResize(area, self.room_bg.width(),
                              self.room_bg.height(), self)
        area_resize.move(QPoint(x_start, y_start))
        self.resize_areas.append(area_resize)
        area_resize.show()

    def createAreaParameter(self, x_start, y_start, x_stop, y_stop):
        """funzione che trasforma le coordinate e le dimensioni definite
        nell'editing dell'area da assolute a logiche"""
        w = float(g_project.data['world'].width)
        h = float(g_project.data['world'].height)
        rel_x = round(min(x_start, x_stop) / w, 3)
        rel_y = round(min(y_start, y_stop) / h, 3)
        rel_width = round(abs(x_stop - x_start) / w, 3)
        rel_height = round(abs(y_stop - y_start) / h, 3)
        return (rel_x, rel_y, rel_width, rel_height)

    def mousePressEvent(self, e):
        self.area_drag_start = e.pos()
        self.area_drag_curr = e.pos()
        self.update()

    def mouseMoveEvent(self, e):
        if self.area_drag_start is None:
            return
        #controllo di essere nell'area dell'mmagine di sfondo
        x = self.clamp(e.x(), self.room_bg.width())
        y = self.clamp(e.y(), self.room_bg.height())
        self.area_drag_curr = QPoint(x, y)
        self.update()

    def clamp(self, position, dimension):
        return min(position, dimension) if position > 0 else max(0, position)

    def mouseReleaseEvent(self, e):
        if self.area_drag_start is None:
            return
        self.createArea(min(self.area_drag_start.x(), self.area_drag_curr.x()),
                        min(self.area_drag_start.y(), self.area_drag_curr.y()),
                        max(self.area_drag_curr.x(), self.area_drag_start.x()),
                        max(self.area_drag_curr.y(), self.area_drag_start.y()))

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
        del g_project.data['rooms'][self.room.id]
        self.room.id = str(new_room_name)
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
                resize_area.hide()
            self.showAllArea()
            self.update()

    def update_data(self):
        self.setRoom(self.room)
        self.setMinimumSize(int(g_project.data['world'].width),
                          int(g_project.data['world'].height))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    rm = RoomEditor(None)
    rm.show()
    app.exec_()
