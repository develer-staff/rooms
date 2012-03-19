#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

class PlusButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(PlusButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("rounded_plus.jpg"))
        self.setIconSize(QSize(30, 30))

class MinusButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(MinusButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("rounded_minus.jpg"))
        self.setIconSize(QSize(30, 30))

class AreaEditor(QWidget):

    def __init__(self, parent=None):
        super(AreaEditor, self).__init__(parent)
        vertical = QVBoxLayout(self)
        plus_button = PlusButton()
        minus_button = MinusButton()
        vertical.addWidget(plus_button)
        self.setLayout(vertical)


if __name__ == "__main__":
    app = QApplication([])
    area = AreaEditor()
    area.show()
    app.exec_()

