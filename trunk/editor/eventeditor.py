#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *



from structdata import Action
from structdata import Param
from structdata.requirement import Requirement
from structdata import VarRequirement
from structdata import ItemRequirement
from structdata.project import g_project

from varreqlistwidget import VarReqListWidget
from varsetlistwidget import VarSetListWidget
from itemreqlistwidget import ItemReqListWidget
from itemmovelistwidget import ItemMoveListWidget
from roommovelistwidget import RoomMoveListWidget
from roomreqlistwidget import RoomReqListWidget
from roomgotolistwidget import RoomGotoListWidget

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
        self.selected_room = None
        self.selected_item = None
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

            self.createItemList()
            self.connect(self.list_widget,
                         SIGNAL("changeSelectedItem(QString)"),
                         self.changeItemData)
            self.connect(self.room_list,
                         SIGNAL("changeSelectedItem(QString)"),
                         self.changeRoomData)
        elif self.tag_name == "ROOM_GOTO":
            self.createRoomList()
            self.connect(self.list_widget,
                         SIGNAL("changeSelectedItem(QString)"),
                         self.changeRoomData)


    def createRoomList(self):
        self.list_widget = RoomGotoListWidget(self.event, self.item, self)
        self.hl.addWidget(self.list_widget)
        self.setSelectedRoom()

    def changeRoomData(self, room):
        """
        funzione che setta il valore della room selezionata e se il tag e'
        ROOM_GOTO chiama la funzione di creazione o modifica dell'action.
        Se il tag invece e' ITEM_MOVE o ITEM_REQ controlla se e' stato scelto
        l'item associato alla room nell'evento e se si chiama la funzione di 
        modifica/creazione dell'action o requirement per l'evento considerato
        """
        self.selected_room = str(room)
        if self.selected_room is not None and self.selected_item is not None:
            self.changeEventItem()
        elif self.tag_name == "ROOM_GOTO" and self.selected_room is not None:
            self.changeEventRoom()

    def changeItemData(self, item):
        """
        funzione che setta il valore dell'item
        selezionato e se sono stati scelit l'item e la room chiama la funzione 
        per creare o modificare l'item corrente.
        La funzione prende come parametro in ingresso il nome dell'item
        """
        self.selected_item = str(item)
        if self.selected_room is not None and self.selected_item is not None:
            self.changeEventItem()

    def changeEventRoom(self):
        if self.item is None:
            action = Action("ROOM_GOTO")
            self.item = action
        self.item.params = []
        param = Param(self.selected_room)
        self.item.params.append(param)
        g_project.notify()

    def changeEventItem(self):

        """
        funzione che modifica l'action o il requirement 
        memorizzato nella classe
        """
        if self.tag_name == "ITEM_MOVE":
            if self.item is None:
                action = Action("ITEM_MOVE")
                self.event.actions.append(action)
                self.item = action
            self.item.params = []
            param = Param(self.selected_item)
            self.item.params.append(param)
            param = Param(self.selected_room)
            self.item.params.append(param)

        else:
            if self.item is None:
                requirement = ItemRequirement(self.selected_item,
                                          self.selected_room)
                self.item = requirement
                self.event.requirements.append(requirement)
            else:
                self.item.id = self.selected_item
                self.item.value = self.selected_room
        g_project.notify()

    def createItemList(self):
        """
        funzione per la creazione dell'oggetto per la visualizzazione di item
        e room nel caso dell'action ITEM_MOVE e del requirement item_req
        """
        if self.tag_name == "ITEM_MOVE":
            self.list_widget = ItemMoveListWidget(self.event, self.item, self)
            self.room_list = RoomMoveListWidget(self.event, self.item, self)
        else:
            self.list_widget = ItemReqListWidget(self.event, self.item, self)
            self.room_list = RoomReqListWidget(self.event, self.item, self)
        self.setSelectedRoom()
        self.setSelectedItem()
        self.hl.addWidget(self.list_widget)
        self.hl.addWidget(self.room_list)

    def setSelectedRoom(self):
        """
        funzione per settare il valore iniziale della room selezionata nel
        caso si tratti item_req o item_move
        """
        if self.item is not None:
            if self.tag_name == "ITEM_REQ":
                self.selected_room = self.item.value
            elif self.tag_name == "ITEM_MOVE":
                self.selected_room = self.item.params[1].value
            elif self.tag_name == "ROOM_GOTO":
                self.selected_room = self.item.params[0].value

    def setSelectedItem(self):
        """
        funzione per settare il valore iniziale dell'item selezionata nel
        caso si tratti item_req o item_move
        """
        if self.item is not None:
            if self.tag_name == "ITEM_REQ":
                self.selected_item = self.item.id
            else:
                self.selected_item = self.item.params[0].value

    def createVarList(self):
        """
        funzione per la creazione dell'oggetto per la visualizzazione delle
        variabili
        """

        if self.tag_name == "VAR_REQ":
            self.list_widget = VarReqListWidget(self.event, self.item, self)
        else:
            self.list_widget = VarSetListWidget(self.event, self.item, self)
        self.hl.addWidget(self.list_widget)

    def getTag(self):
        """
        funzione che dato l'item ritorna il tag corrispettivo
        """
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

    def searchVarRequirement(self, var):
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
                    requirement = self.searchVarRequirement(var)
                    if requirement is not None:
                        index = self.event.requirements.index(requirement)
                        self.event.requirements.pop(index)
        else:
            if self.tag_name == "VAR_REQ":
                if value:
                    requirement = VarRequirement(var, value)
                    self.event.requirements.append(requirement)
                else:
                    requirement = self.searchVarRequirement(var)
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

