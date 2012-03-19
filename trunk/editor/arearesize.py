#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project

class ResizeButton(QPushButton):

    def sizeHint(self):
        return QSize(10, 10)
    def __init__(self, parent=None):
        super(ResizeButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 100% );")
        self.setFixedHeight(10)
        self.setFixedWidth(10)

class AreaEditor(QWidget):

    def sizeHint(self):
        return QSize(self.current_width, self.current_height)

    def __init__(self, area, bg_width, bg_height, parent=None):
        super(AreaEditor, self).__init__(parent)
        self.in_resize = False
        self.bg_width = bg_width
        self.bg_height = bg_height
        self.area = area
        self.resize(QSize(self.toAbsolute(self.area.width, 'x'),
                            self.toAbsolute(self.area.height, 'y')))
        self.current_width = self.width()
        self.current_height = self.height()
        self.setSizePolicy(QSizePolicy(QSizePolicy.Preferred,
                                       QSizePolicy.Preferred))
        self.change_area_name = QLabel(self)
        self.change_area_name.setText(self.area.id)
        self.vl = QVBoxLayout()
        self.vl.setAlignment(Qt.AlignCenter)
        self.vl.addStretch()
        self.vl.addWidget(self.change_area_name)
        self.setLayout(self.vl)
        self.signal_mapper_pressed = QSignalMapper(self)
        self.resize_buttons = []
        for i in range(8):
            button = ResizeButton(self)
            button.setVisible(True)
            if i == 0 or i == 3:
                button.setCursor(Qt.SizeFDiagCursor)
            elif i == 1 or i == 2:
                button.setCursor(Qt.SizeBDiagCursor)
            elif i == 4 or i == 5:
                button.setCursor(Qt.SizeVerCursor)
            else:
                button.setCursor(Qt.SizeHorCursor)
            button.move(self.change_position(i))
            self.connect(button, SIGNAL("pressed()"),
                         self.signal_mapper_pressed, SLOT("map()"))
            self.signal_mapper_pressed.setMapping(button, i)
            self.resize_buttons.append(button)
        self.connect(self.signal_mapper_pressed, SIGNAL("mapped(int)"),
                     self.start_track)

    def change_position(self, index):
        pos = [QPoint(0, 0), QPoint(self.width() - 10, 0),
             QPoint(0, self.height() - 10),
             QPoint(self.width() - 10, self.height() - 10),
             QPoint(self.width() / 2, 0),
             QPoint(self.width() / 2, self.height() - 10),
             QPoint(0, self.height() / 2),
             QPoint(self.width() - 10, self.height() / 2)]
        return pos[index]

    def start_track(self, index):
        self.in_resize = True
        self.index = index

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton and self.in_resize:
            x = event.pos().x()
            #uso per non superare i bordi laterali dello sfondo
            x = min(x, self.bg_width - self.x()) if x + self.x() > 0\
                                                 else max(0, x)
            y = event.pos().y()
            #uso per non superare i bordi superiore e inferiore dello sfondo
            y = min(y, self.bg_height - self.y()) if y + self.y() > 0\
                                                  else max(0, y)
            x_widget = self.x()
            y_widget = self.y()
            #top left button
            if self.index == 0:
                self.move(x_widget + x, y_widget + y)
                self.current_width = self.width() - x
                self.current_height = self.height() - y
                self.resize(self.sizeHint())
            #top right button
            elif self.index == 1:
                self.move(self.x(), y_widget + y)
                self.current_width = x
                self.current_height = self.height() - y
                self.resize(self.sizeHint())
            #bottom left button
            elif self.index == 2:
                self.move(x_widget + x, self.y())
                self.current_width = self.width() - x
                self.current_height = y
                self.resize(self.sizeHint())
            #bottom right button 
            elif self.index == 3:
                self.current_height = y + 5
                self.current_width = x + 5
                self.resize(self.sizeHint())
            #top button
            elif self.index == 4:
                self.move(x_widget, y_widget + y)
                self.current_height = self.height() - y
                self.resize(self.sizeHint())
            #bottom button
            elif self.index == 5:
                self.current_height = y
                self.resize(self.sizeHint())
            #left button
            elif self.index == 6:
                self.move(x_widget + x, y_widget)
                self.current_width = self.width() - x
                self.resize(self.sizeHint())
            #right button
            else:
                self.current_width = x
                self.resize(self.sizeHint())
            i = 0
            for button in self.resize_buttons:
                button.move(self.change_position(i))
                i += 1
            self.area.x = str(self.toLogical(self.x(), 'x'))
            self.area.y = str(self.toLogical(self.y(), 'y'))
            self.area.width = str(self.toLogical(self.width(), 'x'))
            self.area.height = str(self.toLogical(self.height(), 'y'))
            self.update()

    def mouseReleaseEvent(self, event=None):
        self.in_resize = False
        self.update()

    def enterEvent(self, event=None):
        self.change_area_name.setVisible(True)
        for cb in self.resize_buttons:
            cb.setVisible(True)
        self.update()

    def leaveEvent(self, event=None):
        self.change_area_name.setVisible(False)
        for cb in self.resize_buttons:
            cb.setVisible(False)
        self.update()

    def toAbsolute(self, value, direction):
        """converte le coordinate in assolute prendendo in ingresso
           il valore e la direzione della dimensione"""
        if direction == 'x':
            w = float(g_project.data['world'].width)
            return float(value) * w
        elif direction == 'y':
            h = float(g_project.data['world'].height)
            return float(value) * h

    def toLogical(self, value, direction):
        """converte le coordinate in logico prendendo in ingresso
           il valore e la direzione della dimensione"""
        if direction == 'x':
            w = float(g_project.data['world'].width)
            return round(float(value) / w, 3)
        else:
            h = float(g_project.data['world'].height)
            return round(float(value) / h, 3)

    def paintEvent(self, event=None):
        QWidget.paintEvent(self, event)
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)
        p.setPen(Qt.blue)
        p.drawRect(0, 0, self.width(), self.height())
