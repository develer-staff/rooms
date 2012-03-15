#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from structdata.project import g_project

class ChangeBGButton(QPushButton):

    def __init__(self, parent=None):
        super(ChangeBGButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("PageTurn.jpg"))
        self.setIconSize(QSize(30, 30))
        self.connect(self, SIGNAL("clicked()"),
                     self.setRoomBg)

    def setRoomBg(self):
        file_open = QFileDialog()
        path_file = file_open.getOpenFileName()
        if path_file:
            g_project.data['rooms'][self.room_name].bg = str(path_file)
            g_project.notify()
