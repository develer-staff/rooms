#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomslistwidget import RoomsListWidget
from varslistwidget import VarsListWidget
from varsetlistwidget import VarSetListWidget

from structdata import Action
from structdata import Param
from structdata.requirement import Requirement
from structdata.project import g_project

class EventEditor(QDialog):

    def __init__(self, event, item=None, tag_name=None, parent=None):
        super(EventEditor, self).__init__(parent)
        self.event = event
        self.item = item
        if tag_name is not None:
            self.tag_name = tag_name
        else:
            self.tag_name = self.getTag()
        self.list_widget = None
        if self.tag_name == "VAR_REQ" or self.tag_name == "VAR_SET":
            self.createVarList()
            self.list_widget = VarsListWidget(event, item, self)
            self.connect(self.list_widget,
                         SIGNAL("editedElement(QString, QString)"),
                         self.change_var_data)

    def createVarList(self):
        if self.tag_name == "VAR_REQ":
            self.list_widget = VarsListWidget(self.event, self.item, self)
        else:
            self.list_widget = VarSetListWidget(self.event, self.item, self)

    def getTag(self):
        if isinstance(self.item, Action):
            return self.item.id
        elif isinstance(self.item, Requirement):
            return self.item.tag_name


    def searchParamIndex(self, var):
        i = 0
        for param in self.item.params:
            if param.value == var:
                return i
            i += 1

    def change_var_data(self, var, value):
        if self.item is not None:
            if value:
                if isinstance(self.item, Action):
                    index = self.searchParamIndex(var)
                    self.item.params[index + 1].value = value
                else:
                    pass
            else:
                if isinstance(self.item, Action):
                    index = self.searchParamIndex(var)
                    self.item.params.pop(index)
                    self.item.params.pop(index)
                    if len(self.item.params) == 0:
                        action_index = self.event.actions.index(self.item)
                        self.event.actions.pop(action_index)
            g_project.notify()
        else:
            if self.tag_name == "VAR_REQ":
                pass
            else:
                if value:
                    action = Action(str(self.tag_name))
                    action.params.append(Param(str(var)))
                    action.params.append(Param(str(value)))
                    self.item = action
                    self.event.actions.append(action)
                    g_project.notify()
                else:
                    index = self.event.actions.index(self.item)
                    self.event.actions.pop(index)
                    g_project.notify()

