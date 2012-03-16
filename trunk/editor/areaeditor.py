#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata.project import g_project

class AreaEditor(QWidget):

    def __init__(self, area, parent=None):
        super(AreaEditor, self).__init__(parent)
        self.area = area
        self.setMinimumSize(self.toAbsolute(self.area.width, 'x'),
                            self.toAbsolute(self.area.height, 'y'))

        #horizontal = QHBoxLayout()
        ##horizontal.addStretch()
        #horizontal.addWidget(QPushButton(self))
        #self.setLayout(horizontal)

    def eventEnter(self, event=None):
        print "a"

    def toAbsolute(self, value, direction):
        if direction == 'x':
            w = float(g_project.data['world'].width)
            return float(value) * w
        elif direction == 'y':
            h = float(g_project.data['world'].height)
            return float(value) * h

    def paintEvent(self, event):
        p = QPainter(self)
        p.fillRect(self.rect(), QBrush(Qt.blue))
