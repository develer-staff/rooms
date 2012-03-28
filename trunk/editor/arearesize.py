#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from areaeditor import AreaEditor

class ResizeButton(QPushButton):

    def sizeHint(self):
        return QSize(10, 10)
    def __init__(self, parent=None):
        super(ResizeButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 100% );")

class AreaResize(QWidget):

    def __init__(self, area, bg_width, bg_height, parent=None):
        super(AreaResize, self).__init__(parent)
        self.in_resize = False
        self.bg_width = bg_width
        self.bg_height = bg_height
        self.area = area
        self.resize(QSize(float(self.area.width),
                          float(self.area.height)))
        self.vl = QVBoxLayout()
        self.vl.setContentsMargins(0, 0, 0, 0)
        self.area_editor = None
        self.signal_mapper_pressed = QSignalMapper(self)
        self.resize_buttons = []
        horizontal = QHBoxLayout()
        horizontal.setContentsMargins(0, 0, 0, 0)
        for i in range(8):
            button = ResizeButton(self)
            button.setVisible(False)
            if i == 0 or i == 7:
                button.setCursor(Qt.SizeFDiagCursor)
            elif i == 5 or i == 2:
                button.setCursor(Qt.SizeBDiagCursor)
            elif i == 1 or i == 6:
                button.setCursor(Qt.SizeVerCursor)
            else:
                button.setCursor(Qt.SizeHorCursor)
            horizontal.addWidget(button)
            if i not in [2, 4, 7]:
                horizontal.addStretch()
            else:
                self.vl.addLayout(horizontal)
                if i != 7:
                    self.vl.addStretch()
                    horizontal = QHBoxLayout()
                    horizontal.setContentsMargins(0, 0, 0, 0)
            self.connect(button, SIGNAL("pressed()"),
                         self.signal_mapper_pressed, SLOT("map()"))
            self.signal_mapper_pressed.setMapping(button, i)
            self.resize_buttons.append(button)
        self.setLayout(self.vl)
        self.connect(self.signal_mapper_pressed, SIGNAL("mapped(int)"),
                     self.startTrack)

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton and self.in_resize:
            x = event.pos().x()
            #uso per non superare i bordi laterali dello sfondo

            x = min(x, self.bg_width - self.x()) if x + self.x() > 0\
                                                 else max(0, x)
            y = event.pos().y()
#            #uso per non superare i bordi superiore e inferiore dello sfondo
            y = min(y, self.bg_height - self.y()) if y + self.y() > 0\
                                                  else max(0, y)
            x_widget = self.x()
            y_widget = self.y()
            #resize with top left button
            if self.index == 0:
                self.move(x_widget + x, y_widget + y)
                self.resize(QSize(self.width() - x, self.height() - y))
            #resize with top button
            elif self.index == 1:
                self.move(x_widget, y_widget + y)
                self.resize(QSize(self.width(), self.height() - y))
            #resize with top right button
            elif self.index == 2:
                self.move(self.x(), y_widget + y)
                self.resize(QSize(x, self.height() - y))
            #resize with left button
            elif self.index == 3:
                self.move(x_widget + x, y_widget)
                self.resize(QSize(self.width() - x, self.height()))
            #resize with right button
            elif self.index == 4:
                self.resize(QSize(x, self.height()))
            #resize with bottom left button
            elif self.index == 5:
                self.move(x_widget + x, self.y())
                self.resize(QSize(self.width() - x, y))
            #resize with bottom button
            elif self.index == 6:
                self.resize(QSize(self.width(), y))
            #resize with bottom right button 
            elif self.index == 7:
                self.resize(QSize(x + 5, y + 5))
            self.update()

    def mouseReleaseEvent(self, event=None):
        self.resizeArea()

    def resizeArea(self):
        """
        funzione per il ridimensionamento di un'area
        """
        if self.in_resize:
            self.in_resize = False
            self.area.x = str(self.x())
            self.area.y = str(self.y())
            self.area.width = str(self.width())
            self.area.height = str(self.height())
            g_project.notify()
            self.update()

    def mouseDoubleClickEvent(self, event=None):
        self.showAreaEditor()

    def showAreaEditor(self):
        self.area_editor = AreaEditor(self.area, self.parent())
        self.area_editor.exec_()

    def enterEvent(self, event=None):
        for cb in self.resize_buttons:
            cb.setVisible(True)
        self.update()

    def leaveEvent(self, event=None):
        for cb in self.resize_buttons:
            cb.setVisible(False)
        self.update()

    def startTrack(self, index):
        self.in_resize = True
        self.index = index

    def paintEvent(self, event=None):
        QWidget.paintEvent(self, event)
        p = QPainter(self)

        # XXX: senza questo resta il trail dell'area mentre viene
        # ridimensionata: investigare
        p.setRenderHint(QPainter.Antialiasing)

        p.setPen(Qt.blue)
        p.drawRect(0, 0, self.width(), self.height())
