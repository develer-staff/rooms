#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *



from structdata import Action
from structdata import Param
from structdata.requirement import Requirement
from structdata import VarRequirement
from structdata.project import g_project

from varreqlistwidget import VarReqListWidget
from roomslistwidget import RoomsListWidget
from varsetlistwidget import VarSetListWidget
from itemreqlistwidget import ItemReqListWidget
from itemmovelistwidget import ItemMoveListWidget
from roommovelistwidget import RoomMoveListWidget
from roomreqlistwidget import RoomReqListWidget

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
        self.hl = QHBoxLayout(self)
        self.list_widget = None
        self.room_list = None
        if tag_name is not None:
            self.tag_name = tag_name
        else:
            self.tag_name = self.getTag()
        if self.tag_name == "VAR_REQ" or self.tag_name == "VAR_SET":
            self.createVarList()
            self.connect(self.list_widget,
                         SIGNAL("editedElement(QString, QString)"),
                         self.changeVarData)
        elif self.tag_name == "ITEM_REQ" or self.tag_name == "ITEM_MOVE":
            self.selected_room = None
            self.selected_item = None
            self.createItemList()
            self.connect(self.list_widget, SIGNAL("changeSelectedItem(QString, QString)"),
                         self.changeItemData)
            self.connect(self.room_list, SIGNAL("changeSelectedItem(QString, QString)"),
                         self.changeItemData)


    def changeItemData(self, item, item_type):
        print "entro"
        if item_type == "room":
            self.selected_room = str(item)
        else:
            self.selected_item = str(item)
        if self.selected_room is not None and self.selected_item is not None:
            self.changeEventItem()

    def changeEventItem(self):
        pass

    def createItemList(self):
        if self.tag_name == "ITEM_MOVE":
            self.list_widget = ItemMoveListWidget(self.event, self.item, self)
            self.room_list = RoomMoveListWidget(self.event, self.item, self)
        else:
            self.list_widget = ItemReqListWidget(self.event, self.item, self)
            self.room_list = RoomReqListWidget(self.event, self.item, self)
        self.hl.addWidget(self.list_widget)
        self.hl.addWidget(self.room_list)

    def createVarList(self):
        if self.tag_name == "VAR_REQ":
            self.list_widget = VarReqListWidget(self.event, self.item, self)
        else:
            self.list_widget = VarSetListWidget(self.event, self.item, self)
        self.hl.addWidget(self.list_widget)

    def getTag(self):
        if isinstance(self.item, Action):
            return self.item.id
        elif isinstance(self.item, Requirement):
            return self.item.tag_name.upper()

    def searchAction(self, var):
        for action in self.event.actions:
            if action.id == "VAR_SET":
                if action.params[0].value == var:
                    return action
        return None

    def searchRequirement(self, var):
        for requirement in self.event.requirements:
            if requirement.tag_name.upper() == "VAR_REQ":
                if requirement.id == var:
                    return requirement
        return None

    def changeVarData(self, var, value):
        """
        funzione che modifica i dati del modello (action o requirement)
        relativi alle variabili (VAR_SET e VAR_REQ)
        """
        var = str(var)
        value = str(value)
        if self.item is not None:
            """
            se item e' una istanza allora si deve andare a modificare l'item
            stesso anche togliendolo dal modello dei dati se il valore della
            variabile e' settato a stringa vuota
            """
            if value:
                if isinstance(self.item, Action):
                    action = self.searchAction(var)
                    #se trovo l'action sostituisco il valore, altrimenti ne 
                    #creo una nuova
                    if action is not None:
                        action.params[1].value = str(value)
                    else:
                        action = Action("VAR_SET")
                        action.params.append(Param(var))
                        action.params.append(Param(value))
                        self.event.actions.append(action)
                else:
                    #se trovo il requirement sostituisco il valore
                    #altrimenti ne creo uno nuovo
                    requirement = self.searchRequirement(var)
                    if requirement is not None:
                        requirement.value = value
                    else:
                        requirement = VarRequirement(var, value)
                        self.event.requirements.append(requirement)
            else:
                if isinstance(self.item, Action):
                    action = self.searchAction(var)
                    if action is not None:
                        index = self.event.actions.index(action)
                        self.event.actions.pop(index)
                else:
                    requirement = self.searchRequirement(var)
                    if requirement is not None:
                        index = self.event.requirements.index(requirement)
                        self.event.requirements.pop(index)
        else:
            if self.tag_name == "VAR_REQ":
                if value:
                    requirement = VarRequirement(var, value)
                    self.event.requirements.append(requirement)
                else:
                    requirement = self.searchRequirement(var)
                    if requirement is not None:
                        index = self.event.requirements.index(requirement)
                        self.event.requirements.pop(index)
            else:
                if value:
                    action = Action(str(self.tag_name))
                    action.params.append(Param(var))
                    action.params.append(Param(value))
                    self.item = action
                    self.event.actions.append(action)
                else:
                    action = self.searchAction(var)
                    if action is not None:
                        index = self.event.actions.index(action)
                        self.event.actions.pop(index)
        g_project.notify()

