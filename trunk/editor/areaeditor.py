#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

class AreaEditor(QWidget):

    def __init__(self, x, y, width, height, parent=None):
        super(AreaEditor, self).__init__(parent)
        self.setMinimumSize(width, height)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed))
        horizontal = QHBoxLayout(self)
        self.setLayout(horizontal)
        #self.move(QPoint(x, y))
