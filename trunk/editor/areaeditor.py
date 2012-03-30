#!/usr/bin/env python

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from structdata import g_project
from structdata.requirement import Requirement
from structdata import Action
from eventeditor import EventEditor

class EditorButton(QPushButton):
    entries = None

    def __init__(self, item=None, parent=None):
        super(EditorButton, self).__init__(parent)
        self.item = item
        self.createButton()

    def createButton(self):
        if self.item is not None:
            self.setText(self.calcText(self.item))
        else:
            self.setText("+")
            menu = QMenu()
            for entry in self.entries:
                menu.addAction(entry)
            self.setMenu(menu)

    def calcText(self, item):
        raise NotImplementedError

class ActionButton(EditorButton):
    entries = ["ROOM_GOTO", "ITEM_MOVE", "VAR_SET"]

    def calcText(self, action):
        line = action.id
        for param in action.params:
            line = "%s %s" % (line, param.value)
        return line

class RequirementButton(EditorButton):
    entries = ["ITEM_REQ", "VAR_REQ"]

    def calcText(self, requirement):
        line = "%s %s %s" % (requirement.tag_name.upper(),
                             requirement.id, requirement.value)
        return line

class MinusButton(QPushButton):
    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, item, parent=None):
        super(MinusButton, self).__init__(parent)
        self.item = item
        self.setText("-")

class AreaEditor(QDialog):

    def __init__(self, area, parent=None):
        super(AreaEditor, self).__init__(parent)
        g_project.subscribe(self)
        self.area = area

        self.vl = QVBoxLayout(self)

        self.gl = QGridLayout()
        self.createList()

        self.vl.addLayout(self.gl)
        gl = QGridLayout()
        gl.addWidget(QLabel("Area name"), 0, 0)
        self.change_area_name = QLineEdit()
        self.change_area_name.setText(self.area.id)
        gl.addWidget(self.change_area_name, 0, 1)
        gl.addWidget(QLabel("Event name"), 1, 0)
        self.change_event_name = QLineEdit()
        self.change_event_name.setText(self.area.event)
        gl.addWidget(self.change_event_name, 1, 1)
        self.vl.addLayout(gl)
        self.vl.addStretch()
        self.vl.addWidget(QStatusBar(self))
        self.connect(self.change_area_name, SIGNAL("returnPressed()"),
                     self.changeAreaName)
        self.connect(self.change_event_name, SIGNAL("returnPressed()"),
                     self.changeEventName)

    def changeAreaName(self):
        """
        funzione che modifica il nome dell'area che si sta editando
        """
        area_name = unicode(self.change_area_name.text())
        if self.area.id != area_name:
            self.area.id = area_name
            g_project.notify()

    def changeEventName(self):
        """
        funzione che cambia il nome dell'evento associato all'area che si sta
        editando
        """
        event_name = unicode(self.change_event_name.text())
        if self.area.event != event_name:
            event = g_project.data['events'][self.area.event]
            del g_project.data['events'][event.id]
            event.id = event_name
            g_project.data['events'][event.id] = event
            self.area.event = event.id
            g_project.notify()

    def closeEvent(self, event=None):
        g_project.unsubscribe(self)

    def updateData(self):
        while (self.gl.itemAt(0)):
            item = self.gl.itemAt(0)
            item.widget().deleteLater()
            self.gl.removeItem(item)
        self.signal_minus_mapper.deleteLater()
        self.createList()

    def createList(self):
        """
        funzione che crea la lista dei bottoni per l'agigunta e la modifica
        di action e requirement
        """
        self.signal_minus_mapper = QSignalMapper(self)
        self.minus_buttons = []
        if self.area.event in g_project.data['events'].keys():
            self.event = g_project.data['events'][self.area.event]
        self.gl.addWidget(QLabel("Actions", parent=self), 0, 0)
        row, i = self.createButtons(ActionButton, self.event.actions, 1, 0)
        self.gl.addWidget(QLabel("Requirements", parent=self), row, 0)
        row += 1
        row, i = self.createButtons(RequirementButton, self.event.requirements,
                                 row, i)
        self.connect(self.signal_minus_mapper, SIGNAL("mapped(int)"),
                     self.removeElement)

    def createButtons(self, button_type, items, row_start, mapper_start_index):
        """
        funzione che crea tutti i bottoni per particolare insieme di dati.
        I parametri necessari sono il tipo di bottone che deve essere creato
        (button_type), l'elenco degli elementi da associare ai bottoni (items),
        la riga di partenza in cui inserire il bottone e l'indice da
        associare al QSignalMapper.
        La funzione ritorna la riga a cui e' arrivato nella costruzione e
        l'indice a cui e' arrivato il QSignalMapper
        """
        row = row_start
        i = mapper_start_index
        for item in items:
            button = button_type(item, self)
            button.setAutoDefault(False)
            minus_button = MinusButton(item)
            minus_button.setAutoDefault(False)
            self.minus_buttons.append(minus_button)
            self.gl.addWidget(minus_button, row , 1)
            self.gl.addWidget(button, row, 0)
            self.connect(minus_button, SIGNAL("clicked()"),
                         self.signal_minus_mapper, SLOT("map()"))
            self.signal_minus_mapper.setMapping(minus_button, i)
            self.connect(button, SIGNAL("clicked()"),
                         self.editEvent)
            row += 1
            i += 1
        self.add_button = button_type(parent=self)
        self.add_button.setAutoDefault(False)
        self.gl.addWidget(self.add_button, row, 0)
        row += 1
        self.connect(self.add_button.menu(), SIGNAL("triggered(QAction *)"),
                     self.createNewEvent)
        return row, i

    def editEvent(self):
        self.createEventEditor(item=self.sender().item)

    def createNewEvent(self, act):
        self.createEventEditor(tag=act.text())

    def createEventEditor(self, tag=None, item=None):
        """
        funzione che crea un EventEditor relativo all'evento associato
        all'area
        """
        self.event_editor = EventEditor(self.event, item, tag, self)
        self.event_editor.move(self.x() + self.width() + 50, self.y())
        self.event_editor.setModal(True)
        self.event_editor.show()

    def removeElement(self, index):
        """
        funzione che elimina un action o un requirement dall'event associato
        all'area. La funzione prende in ingresso l'indice relativo
        al bottone selezionato
        """
        item = self.minus_buttons[index].item
        if isinstance(item, Action):
            index = self.event.actions.index(item)
            g_project.data['events'][self.area.event].actions.pop(index)
        else:
            index = self.event.requirements.index(item)
            g_project.data['events'][self.area.event].requirements.pop(index)
        g_project.notify()

if __name__ == "__main__":
    from openfilerooms import openFileRooms
    from savefilerooms import saveFileRooms

    openFileRooms('world.rooms')

    app = QApplication([])
    room = g_project.data['rooms']['Stanza Stella']
    area = AreaEditor(room.areas[1])

    area.show()
    area.move(200, 200)
    app.exec_()
    saveFileRooms("a.rooms")

