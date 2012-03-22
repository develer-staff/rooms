#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structdata.project import g_project

class ActionButton(QPushButton):

    def __init__(self, action=None, parent=None):
        super(ActionButton, self).__init__(parent)
        self.action = action
        self.createButton()

    def createButton(self):
        if self.action is not None:
            line = self.action.id
            for param in self.action.params:
                line = "%s %s" % (line, param.value)
            self.setText(line)
        else:
            self.setText("+")
            menu = QMenu()
            menu.addAction("ROOM_GOTO")
            menu.addAction("ITEM_MOVE")
            menu.addAction("VAR_SET")
            self.setMenu(menu)

class RequirementButton(QPushButton):
    def __init__(self, requirement=None, parent=None):
        super(RequirementButton, self).__init__(parent)
        self.requirement = requirement
        self.createButton()

    def createButton(self):
        if self.requirement is not None:
            line = "%s %s %s" % (self.requirement.tag_name.upper(),
                                 self.requirement.id, self.requirement.value)
            self.setText(line)
        else:
            self.setText("+")
            menu = QMenu()
            menu.addAction("ITEM_REQ")
            menu.addAction("VAR_REQ")
            self.setMenu(menu)

class MinusButton(QToolButton):
    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, parent=None):
        super(MinusButton, self).__init__(parent)
        self.setText("-")
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
        self.signal_minus_mapper = QSignalMapper()
        self.requirements = []
        self.actions = []
        if self.area.event in g_project.data['events'].keys():
            self.requirements = g_project.data['events'][self.area.event].requirements
            self.actions = g_project.data['events'][self.area.event].actions
        self.gl.addWidget(QLabel("Actions"), 0, 0)
        row = self.createButtons(ActionButton, self.actions, 1)
        self.gl.addWidget(QLabel("Requirements"), row, 0)
        row += 1
        row = self.createButtons(RequirementButton, self.requirements,
                                   row)
        self.connect(self.signal_minus_mapper, SIGNAL("mapped(int)"),
                     self.removeElements)

    def createButtons(self, button_type, items, row_start):
        row = row_start
        for item in items:
            minus_button = MinusButton()
            button = button_type(item, self)
            self.gl.addWidget(minus_button, row , 1)
            self.gl.addWidget(button, row, 0)
            self.connect(minus_button, SIGNAL("clicked()"),
                         self.signal_minus_mapper, SLOT("map()"))
            self.signal_minus_mapper.setMapping(minus_button, row)
            row += 1
        self.add_action = ActionButton(parent=self)
        self.gl.addWidget(self.add_action, row, 0)
        row += 1
        self.connect(self.add_action.menu(), SIGNAL("triggered(QAction *)"),
                     self.printa)
        return row

    def printa(self, a):
        print a.text()

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

