#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomslistwidget import RoomsListWidget
from varslistwidget import VarsListWidget

from structdata import Action
from structdata import Param
from structdata.project import g_project

class EventEditor(QDialog):

    def __init__(self, event_name, item=None, tag_name=None, parent=None):
        super(EventEditor, self).__init__(parent)
        self.event_name = event_name
        self.item = item
        self.tag_name = tag_name
        self.list_widget = None
        if self.tag_name == "VAR_REQ" or self.tag_name == "VAR_SET":
            self.list_widget = VarsListWidget(event_name, item, self)
            self.connect(self.list_widget,
                         SIGNAL("editedElement(QString, QString)"),
                         self.change_var_data)

    def change_var_data(self, var, value):
        if self.tag_name == "VAR_REQ":
            pass
        else:
            if value:
                action = Action(str(self.tag_name))
                action.params.append(Param(str(var)))
                action.params.append(Param(str(value)))
                self.item = action
                g_project.data['events'][self.event_name].actions.append(action)
                g_project.notify()
            else:
                index = g_project.data['events'][self.event_name].actions.index(self.item)
                g_project.data['events'][self.event_name].actions.pop(index)
                g_project.notify()

