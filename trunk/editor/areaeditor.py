#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structdata import g_project
from structdata.requirement import Requirement
from structdata import Action

class EditorButton(QPushButton):

    def __init__(self, item=None, parent=None):
        super(EditorButton, self).__init__(parent)
        self.item = item
        self.createButton()

    def createButton(self):
        pass

class ActionButton(EditorButton):

    def __init__(self, action=None, parent=None):
        super(ActionButton, self).__init__(action, parent)

    def createButton(self):
        action = self.item
        if action is not None:
            line = action.id
            for param in action.params:
                line = "%s %s" % (line, param.value)
            self.setText(line)
        else:
            self.setText("+")
            menu = QMenu()
            menu.addAction("ROOM_GOTO")
            menu.addAction("ITEM_MOVE")
            menu.addAction("VAR_SET")
            self.setMenu(menu)

class RequirementButton(EditorButton):
    def __init__(self, requirement=None, parent=None):
        super(RequirementButton, self).__init__(requirement, parent)

    def createButton(self):
        requirement = self.item
        if requirement is not None:
            line = "%s %s %s" % (requirement.tag_name.upper(),
                                 requirement.id, requirement.value)
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

    def __init__(self, item, parent=None):
        super(MinusButton, self).__init__(parent)
        self.item = item
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
        i = 0
        while (self.gl.itemAt(0)):
            item = self.gl.itemAt(0)
            item.widget().deleteLater()
            self.gl.removeItem(item)
        self.signal_minus_mapper.deleteLater()
        self.createList()

    def createList(self):
        self.signal_minus_mapper = QSignalMapper(self)
        self.minus_buttons = []
        if self.area.event in g_project.data['events'].keys():
            self.requirements = g_project.data['events'][self.area.event].requirements
            self.actions = g_project.data['events'][self.area.event].actions
        self.gl.addWidget(QLabel("Actions", parent=self), 0, 0)
        row, i = self.createButtons(ActionButton, self.actions, 1, 0)
        self.gl.addWidget(QLabel("Requirements", parent=self), row, 0)
        row += 1
        i = 0
        row, i = self.createButtons(RequirementButton, self.requirements,
                                 row, i)
        self.connect(self.signal_minus_mapper, SIGNAL("mapped(int)"),
                     self.removeElement)

    def createButtons(self, button_type, items, row_start, mapper_start_index):
        row = row_start
        i = mapper_start_index
        for item in items:
            button = button_type(item, self)
            minus_button = MinusButton(item)
            self.minus_buttons.append(minus_button)
            self.gl.addWidget(minus_button, row , 1)
            self.gl.addWidget(button, row, 0)
            self.connect(minus_button, SIGNAL("clicked()"),
                         self.signal_minus_mapper, SLOT("map()"))
            self.signal_minus_mapper.setMapping(minus_button, i)
            row += 1
            i += 1
        self.add_button = button_type(parent=self)
        self.gl.addWidget(self.add_button, row, 0)
        row += 1
        self.connect(self.add_button.menu(), SIGNAL("triggered(QAction *)"),
                     self.printa)
        return row, i

    def printa(self, a):
        print a.text()

    def removeElement(self, index):
        item = self.minus_buttons[index].item
        if isinstance(item, Action):
            index = self.findItem(item,
                                  g_project.data['events']\
                                  [self.area.event].actions)
            g_project.data['events'][self.area.event].actions.pop(index)
        else:
            index = self.findItem(item,
                                  g_project.data['events']\
                                  [self.area.event].requirements)
            g_project.data['events'][self.area.event].requirements.pop(index)
        g_project.notify()

    def findItem(self, item, items):
        i = 0
        for it in items:
            if it.id == item.id:
                return i
            i += 1

    def changeName(self):
        self.area.id = str(self.change_name.text())
        g_project.notify()

if __name__ == "__main__":
    from openfilerooms import openFileRooms
    from savefilerooms import saveFileRooms
    openFileRooms('world.rooms')

    app = QApplication([])
    area = AreaEditor(g_project.data['rooms']['Locanda'].areas[0])

    area.show()
    app.exec_()
    saveFileRooms("a.rooms")

