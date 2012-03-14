#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

class AreaEditor(QWidget):

    def __init__(self, x, y, width, height, parent=None):
        super(AreaEditor, self).__init__(parent)
        horizontal = QHBoxLayout(self)
        horizontal.setGeometry(QRect(x, y, x + width, y + height))
        button = QPushButton("ciao")
        horizontal.addWidget(button)
        self.setLayout(horizontal)
        self.setMinimumSize(width, height)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed))
        self.move(QPoint(x, y))
