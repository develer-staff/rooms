#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomslistwidget import RoomsListWidget
from varslistwidget import VarsListWidget
from varsetlistwidget import VarSetListWidget

from structdata import Action
from structdata import Param
from structdata.requirement import Requirement
from structdata import VarRequirement
from structdata.project import g_project
from varreqlistwidget import VarReqListWidget

class EventEditor(QDialog):
    """
    Classe che fornisce un'interfaccia grafica per la modifica degli eventi
    Viene passato l'evento a cui ci si riferisce, il requirement o l'action
    che si vuole modificare indicato come item (item puo' non essere passato
    nel caso in cui si stia creando un nuovo requirement/action); il tag_name
    (viene passato se si crea un nuovo item, altrimenti viene ricavato
    dall'item stesso)
    """
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
            self.connect(self.list_widget,
                         SIGNAL("editedElement(QString, QString)"),
                         self.changeVarData)

    def createVarList(self):
        if self.tag_name == "VAR_REQ":
            self.list_widget = VarReqListWidget(self.event, self.item, self)
        else:
            self.list_widget = VarSetListWidget(self.event, self.item, self)

    def getTag(self):
        if isinstance(self.item, Action):
            return self.item.id
        elif isinstance(self.item, Requirement):
            return self.item.tag_name.upper()

    def searchParamIndex(self, var):
        i = 0
        for param in self.item.params:
            if param.value == var:
                return i
            i += 1

    def changeVarData(self, var, value):
        """
        funzione che modifica i dati del modello (action o requirement)
        relativi alle variabili (VAR_SET e VAR_REQ)
        """
        if self.item is not None:
            """
            se item e' una istanza allora si deve andare a modificare l'item
            stesso anche togliendolo dal modello dei dati se cosi' scelto
            """
            if value:
                if isinstance(self.item, Action):
                    index = self.searchParamIndex(var)
                    self.item.params[index + 1].value = str(value)
                else:
                    self.item.value = str(value)
            else:
                if isinstance(self.item, Action):
                    index = self.searchParamIndex(var)
                    self.item.params.pop(index)
                    self.item.params.pop(index)
                    if len(self.item.params) == 0:
                        action_index = self.event.actions.index(self.item)
                        self.event.actions.pop(action_index)
                else:
                    index = self.event.requirements.index(self.item)
                    self.event.requirements.pop(index)
        else:
            if self.tag_name == "VAR_REQ":
                if value:
                    requirement = VarRequirement(str(var), str(value))
                    self.event.requirements.append(requirement)
                else:
                    index = self.event.requirements.index(self.item)
                    self.event.requirements.pop(index)
            else:
                if value:
                    action = Action(str(self.tag_name))
                    action.params.append(Param(str(var)))
                    action.params.append(Param(str(value)))
                    self.item = action
                    self.event.actions.append(action)
                else:
                    index = self.event.actions.index(self.item)
                    self.event.actions.pop(index)
        g_project.notify()

