#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project

class CornerButton(QPushButton):

    def sizeHint(self):
        return QSize(10, 10)
    def __init__(self, parent=None):
        super(CornerButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 100% );")
        self.setFixedHeight(10)
        self.setFixedWidth(10)
        self.setCursor(Qt.SizeAllCursor)

class AreaEditor(QWidget):

    def __init__(self, area, parent=None):
        super(AreaEditor, self).__init__(parent)
        self.visible = False
        self.in_resize = False
        self.area = area
        self.resize(QSize(self.toAbsolute(self.area.width, 'x'),
                            self.toAbsolute(self.area.height, 'y')))
        self.setSizePolicy(QSizePolicy(QSizePolicy.Preferred,
                                       QSizePolicy.Preferred))
        self.change_area_name = QLabel()
        self.change_area_name.setText(self.area.id)
        self.vl = QVBoxLayout()
        self.vl.setAlignment(Qt.AlignCenter)
        self.vl.addStretch()
        self.vl.addWidget(self.change_area_name)
        self.setLayout(self.vl)
        self.top_left = CornerButton(self)
        self.buttom_right = CornerButton(self)
        self.signal_mapper_pressed = QSignalMapper(self)
        self.signal_mapper_released = QSignalMapper(self)
        self.corner_buttons = []
        for i in range(4):
            button = CornerButton(self)
            button.move(self.change_position(i))
            self.connect(button, SIGNAL("pressed()"),
                         self.signal_mapper_pressed, SLOT("map()"))
            self.signal_mapper_pressed.setMapping(button, i)
            self.corner_buttons.append(button)
        self.connect(self.signal_mapper_pressed, SIGNAL("mapped(int)"),
                     self.start_track)

    def change_position(self, index):
        pos = [QPoint(self.x(), 0), QPoint(self.width() - 10, 0),
             QPoint(0, self.height() - 10),
             QPoint(self.width() - 10, self.height() - 10)]
        return pos[index]

    def start_track(self, index):
        self.in_resize = True
        self.index = index
        print self.index

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton and self.in_resize:
            x = event.pos().x()
            y = event.pos().y()
            x_widget = self.x()
            y_widget = self.y()

            if self.index == 0:
                self.move(x_widget + x, y_widget + y)
                self.resize(QSize(self.width() - x, self.height() - y))
            elif self.index == 1:
                self.move(self.x(), y_widget - y)
                self.resize(QSize(self.width() - x, self.height() - y))
                print self.x()

            for i in range(4):
                self.corner_buttons[i].move(self.change_position(i))


    def mouseReleaseEvent(self, event=None):
        self.in_resize = False

    def enterEvent(self, event=None):
        self.visible = True
        self.update()

    def leaveEvent(self, *args, **kwargs):
        self.visible = False
        self.update()

    def toAbsolute(self, value, direction):
        if direction == 'x':
            w = float(g_project.data['world'].width)
            return float(value) * w
        elif direction == 'y':
            h = float(g_project.data['world'].height)
            return float(value) * h

    def paintEvent(self, event):
        self.change_area_name.setVisible(self.visible)
        p = QPainter(self)
        p.setPen(Qt.blue)
        p.drawRect(0, 0, self.width() - 1, self.height() - 1)
