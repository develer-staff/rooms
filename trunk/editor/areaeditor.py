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

    def toAbsolute(self, value, dir):
        if dir == 'x':
            w = float(g_project.data['world'].width)
            return float(value) * w
        elif dir == 'y':
            h = float(g_project.data['world'].height)
            return float(value) * h
