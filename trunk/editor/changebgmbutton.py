#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata.project import g_project

class ChangeBGMButton(QPushButton):

    def __init__(self, parent=None):
        super(ChangeBGMButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("musical_note.png"))
        self.setIconSize(QSize(30, 30))



