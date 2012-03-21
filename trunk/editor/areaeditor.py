#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structdata.project import g_project

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

    def __init__(self, area, parent=None):
        super(AreaEditor, self).__init__(parent)
        self.gl = QGridLayout(self)
        self.signal_plus_mapper = QSignalMapper(self)
        self.area = area
        self.event = g_project.data['events'][self.area.event]
        i = 0
        for action in self.event.actions:
            minus_button = MinusButton()
            line = action.id
            for param in action.params:
                line = "%s %s" % (line, param.value)
            line_edit = QLineEdit()
            line_edit.setText(line)
            self.gl.addWidget(minus_button, i , 0)
            self.gl.addWidget(line_edit, i, 1)
            self.connect(minus_button, SIGNAL("clicked()"),
                         self.signal_plus_mapper, SLOT("map()"))
            self.signal_plus_mapper.setMapping(minus_button, i)
            i += 1
        plus_button = PlusButton()
        self.gl.addWidget(plus_button, i, 0)
        self.setLayout(self.gl)


if __name__ == "__main__":
    app = QApplication([])
    area = AreaEditor()
    area.show()
    app.exec_()

