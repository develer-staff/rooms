#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *


class ChangeBGButton(QPushButton):

    def __init__(self, parent=None):
        super(ChangeBGButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("PageTurn.jpg"))
        self.setIconSize(QSize(30, 30))




