#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

class RoomManager(QWidget):

    def __init__(self, parent=None):
        super(RoomManager, self).__init__(parent)
        self.bottone1 = QPushButton("Locanda")
        self.bottone2 = QPushButton("Stanza Centrale")
        vertical = QVBoxLayout(self)
        vertical.addWidget(self.bottone1)
        vertical.addWidget(self.bottone2)
