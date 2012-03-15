#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

class RoomBGImage(QLabel):

    def __init__(self, parent=None):
        super(RoomBGImage, self).__init__(parent)
        self.area_x_start = -1
        self.area_y_start = -1
        self.area_x_stop = -1
        self.area_y_stop = -1
        self.released = False

    def mousePressEvent(self, event):
        if (0 <= event.pos().x() <= self.width()
            and 0 <= event.pos().y() <= self.height()):
            self.area_x_start = event.pos().x()
            self.area_y_start = event.pos().y()
            self.released = False

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton:
            if self.area_x_start > -1:
                if(0 <= event.pos().x() <= self.width()
                and 0 <= event.pos().y() <= self.height()):
                    self.area_x_stop = event.pos().x()
                    self.area_y_stop = event.pos().y()
                    self.update()
        else:
            self.released = True
            self.update()

    def mouseReleaseEvent(self, event):
        if self.area_x_start > -1:
            if(0 <= event.pos().x() <= self.width()
            and 0 <= event.pos().y() <= self.height()):
                self.area_x_stop = event.pos().x()
                self.area_y_stop = event.pos().y()
                self.released = True
                self.update()
                self.emit(SIGNAL("areaEdited"),
                          self.area_x_start, self.area_y_start,
                          self.area_x_stop, self.area_y_stop)

    def paintEvent(self, event=None):
        super(RoomBGImage, self).paintEvent(event)
        painter = QPainter(self)
        if (self.area_x_start > -1 and self.area_x_stop > -1):
            if not self.released:
                painter.setPen(Qt.blue)
                rect = QRect(QPoint(self.area_x_start,
                                    self.area_y_start),
                             QPoint(self.area_x_stop ,
                                    self.area_y_stop))
                painter.drawRect(rect)
