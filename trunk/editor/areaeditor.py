#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structdata.project import g_project

class PlusButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(PlusButton, self).__init__(parent)
#        self.setStyleSheet("background-color:"
#                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("rounded_plus.jpg"))
        self.setIconSize(QSize(30, 30))

class MinusButton(QPushButton):

    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(MinusButton, self).__init__(parent)
#        self.setStyleSheet("background-color:"
#                                           "rgba( 255, 255, 255, 0% );")
        self.setIcon(QIcon("rounded_minus.jpg"))
        self.setIconSize(QSize(30, 30))

class AreaEditor(QDialog):

    def __init__(self, area, parent=None):
        super(AreaEditor, self).__init__(parent)
        g_project.subscribe(self)
        self.area = area
        self.gl = QGridLayout(self)
        self.createList()
        self.setLayout(self.gl)

    def updateData(self):
        pass

    def createList(self):
        self.signal_plus_mapper = QSignalMapper()
        self.requirements = []
        self.actions = []
        if self.area.event in g_project.data['events'].keys():
            self.requirements = g_project.data['events'][self.area.event].requirements
            self.actions = g_project.data['events'][self.area.event].actions
        i = 0
        for action in self.actions:
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
        for requirement in self.requirements:
            minus_button = MinusButton()
            line = requirement.tag_name
            line = "%s %s %s" % (line, requirement.id, requirement.value)
            line_edit = QLineEdit()
            line_edit.setText(line)
            self.gl.addWidget(minus_button, i, 0)
            self.gl.addWidget(line_edit, i, 1)
            self.connect(minus_button, SIGNAL("clicked()"),
                         self.signal_plus_mapper, SLOT("map()"))
            self.signal_plus_mapper.setMapping(minus_button, i)
            i += 1
        plus_button = PlusButton()
        self.gl.addWidget(plus_button, i, 0)
        self.change_name = QLineEdit()
        self.change_name.setText(self.area.id)
        self.gl.addWidget(self.change_name, i + 1, 0, 1, 2)
        self.connect(self.change_name, SIGNAL("editingFinished()"),
                     self.changeName)
        self.connect(self.signal_plus_mapper, SIGNAL("mapped(int)"),
                     self.removeElements)

    def removeElements(self, index):
        if index < len(self.actions):
            self.actions.pop(index)
        else:
            self.requirements.pop(index - len(self.actions) - 1)
        item = self.gl.itemAtPosition(index, 0)
        item.widget().deleteLater()
        self.gl.removeWidget(item.widget())
        item = self.gl.itemAtPosition(index, 1)
        item.widget().deleteLater()
        self.gl.removeWidget(item.widget())
        g_project.notify()

    def changeName(self):
        self.area.id = str(self.change_name.text())
        g_project.notify()

if __name__ == "__main__":
    from openfilerooms import openFileRooms
    openFileRooms('world.rooms')

    app = QApplication([])
    area = AreaEditor(g_project.data['rooms']['Locanda'].areas[0])

    area.show()
    app.exec_()

