#!/usr/bin/env python

import sys
import traceback
from os.path import split

from PyQt4.QtCore import *
from PyQt4.QtGui import *

from roomeditor import RoomEditor
from roommanagerlistwidget import RoomManager
from structdata import Room
from structdata import g_project
from utils import g_ptransform
from undoredo import g_undoredo
from engine import startEngine


from openfilerooms import openFileRooms
from savefilerooms import saveFileRooms


def handleException(exc_type, exc_value, exc_traceback):

    """
    funzione per la gestione delle eccezioni. Quando viene lanciata
    un'eccezione stampa a video l'eccezione stessa e poi termina il programma
    """

    from StringIO import StringIO
    m = StringIO()
    traceback.print_exception(exc_type, exc_value, exc_traceback, file=m)
    sys.stdout.flush()
    QApplication.exit()

class StartEngineButton(QToolButton):

    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, icon_path, parent=None):
        super(StartEngineButton, self).__init__(parent)
        self.setIcon(QIcon(icon_path))
        self.setIconSize(QSize(30, 30))

class OpenProjectButton(QToolButton):

    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(OpenProjectButton, self).__init__(parent)
        self.setIcon(QIcon("image/open_project.gif"))
        self.setIconSize(QSize(30, 30))

class SaveProjectButton(QToolButton):

    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(SaveProjectButton, self).__init__(parent)
        self.setIcon(QIcon("image/save_project.png"))
        self.setIconSize(QSize(30, 30))

class PlayBGMButton(QToolButton):

    def sizeHint(self):
        return QSize(30, 30)

    def __init__(self, icon_path, room, parent=None):
        super(PlayBGMButton, self).__init__(parent)
        self.room = room
        self.icon_path = icon_path
        self.icon = QPixmap(self.icon_path).scaled(30, 30,
                                                       Qt.KeepAspectRatio,
                                                       Qt.SmoothTransformation)
    def paintEvent(self, event=None):
        super(PlayBGMButton, self).paintEvent(event)
        p = QPainter(self)
        p.setOpacity(self.getOpacity())
        p.drawPixmap(QPoint(0, 0), self.icon)

    def getOpacity(self):
        """
        funzione che ritorna il valore di opacita' per l'immagine che deve
        essere disegnata sul bottone. Se la room associata al bottone ha
        settato il parametro corrispondente al bottone la funzione torna 1.
        altrimenti 0.5
        """
        if self.room is not None and self.room.bgm:
            return 1.
        return 0.5

    def setRoom(self, room):
        """
        funzione per settare la room associata al bottone, da utilizzare
        quando cambia la room in fase di editing
        """
        self.room = room

class UndoButton(QToolButton):
    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(UndoButton, self).__init__(parent)
        self.icon = QPixmap("image/Undo-icon.png").scaled(30, 30,
                                                       Qt.KeepAspectRatio,
                                                       Qt.SmoothTransformation)

    def paintEvent(self, event=None):
        super(UndoButton, self).paintEvent(event)
        p = QPainter(self)
        p.setOpacity(self.getOpacity())
        p.drawPixmap(QPoint(0, 0), self.icon)

    def getOpacity(self):
        if self.isEnabled():
            return 1.
        return 0.5

    def updateData(self):
        self.setEnabled(g_undoredo.moreUndo())

class RedoButton(QToolButton):
    def sizeHint(self):
        return QSize(30, 30)
    def __init__(self, parent=None):
        super(RedoButton, self).__init__(parent)
        self.icon = QPixmap("image/Redo-icon.png").scaled(30, 30,
                                                       Qt.KeepAspectRatio,
                                                       Qt.SmoothTransformation)

    def paintEvent(self, event=None):
        super(RedoButton, self).paintEvent(event)
        p = QPainter(self)
        p.setOpacity(self.getOpacity())
        p.drawPixmap(QPoint(0, 0), self.icon)

    def getOpacity(self):
        if self.isEnabled():
            return 1.
        return 0.5

    def updateData(self):
        self.setEnabled(g_undoredo.moreRedo())

class Editor(QWidget):

    def __init__(self, file_name, parent=None):
        super(Editor, self).__init__(parent)
        g_project.subscribe(self)
        self.engine = None
        self.redo_undo_button_press = False
        self.redo_undo_button_press = False
        self.grid_layout = QGridLayout(self)
        openFileRooms(file_name)
        g_ptransform.path_file = split(file_name)[0]
        self.room = g_project.data['rooms'][g_project.data['world'].start]
        self.createEditorInterface()
        self.createEditorButtons()
        g_project.notify()
        self.setDirty(False)

    def createEditorButtons(self):
        """
        funzione che crea i bottoni dell'editor e le connessioni dei segnali
        dei bottoni stessi
        """
        self.open_project_button = OpenProjectButton(self)
        self.save_project_button = SaveProjectButton(self)
        self.new_room_button = QPushButton("New room", self)
        self.remove_room_button = QPushButton("Remove room", self)
        self.play_bgm_button = PlayBGMButton("image/play.png", self.room, self)
        self.start_engine_button = StartEngineButton("image/start_engine.gif",
                                                     self)
        self.undo_button = UndoButton(self)
        self.undo_button.setEnabled(g_undoredo.moreUndo())
        self.redo_button = RedoButton(self)
        self.redo_button.setEnabled(g_undoredo.moreRedo())
        g_undoredo.subscribe(self.undo_button)
        g_undoredo.subscribe(self.redo_button)
        horizontal_button = QHBoxLayout()
        horizontal_button.addWidget(self.open_project_button)
        horizontal_button.addWidget(self.save_project_button)
        horizontal_button.addWidget(self.new_room_button)
        horizontal_button.addWidget(self.remove_room_button)
        horizontal_button.addWidget(self.play_bgm_button)
        horizontal_button.addWidget(self.start_engine_button)
        horizontal_button.addWidget(self.undo_button)
        horizontal_button.addWidget(self.redo_button)
        self.grid_layout.addLayout(horizontal_button, 0, 0)

        self.connect(self.new_room_button, SIGNAL("clicked()"), Room.create)
        self.connect(self.open_project_button, SIGNAL("clicked()"),
                     self.openProject)
        self.connect(self.save_project_button, SIGNAL("clicked()"),
                     self.saveProject)
        self.connect(self.remove_room_button, SIGNAL("clicked()"),
                     self.removeRoom)
        self.connect(self.play_bgm_button, SIGNAL("clicked()"),
                     self.playMusic)
        self.connect(self.start_engine_button, SIGNAL("clicked()"),
                     self.startEngine)
        self.connect(self.undo_button, SIGNAL("clicked()"),
                     self.undo)
        self.connect(self.redo_button, SIGNAL("clicked()"),
                     self.redo)

    def createEditorInterface(self):
        """
        funzione che crea l'interfaccia di modifica e selezione delle room
        dell'editor e collega i segnali degli oggetti creati
        """
        self.room_manager = RoomManager(parent=self)
        self.grid_layout.addWidget(self.room_manager, 1, 0)
        self.room_editor = RoomEditor(self.room, self)
        self.grid_layout.addWidget(self.room_editor, 1, 1)
        g_project.subscribe(self.room_editor)
        g_project.subscribe(self.room_manager)
        self.connect(self.room_editor,
                     SIGNAL("currentRoomNameChanged(QString)"),
                     self.room_manager.changeCurrentRoomName)
        self.connect(self.room_manager,
             SIGNAL("changeSelectedItem(QString)"),
             self.room_editor.changeCurrentRoom)
        self.connect(self.room_manager,
                     SIGNAL("changeSelectedItem(QString)"),
                     self.changeCurrentRoom)
        self.connect(self.room_manager,
                     SIGNAL("changeSelectedItem(QString)"),
                     self.enableRemoveRoomButton)

    def clearEditor(self):
        """
        funzione per cancellare l'interfaccia dell'editor. Desottorscrive gli
        oggetti che sono observer o del modello dei dati o del sistema di 
        undo/redo
        """
        children = self.findChildren(QWidget)
        for child in children:
            if child.parent() == self:
                if isinstance(child, (RoomManager, RoomEditor)):
                    g_project.unsubscribe(child)
                if isinstance(child, (UndoButton, RedoButton)):
                    g_undoredo.unsubscribe(child)
                child.setParent(None)

    def resetEditor(self):
        self.clearEditor()
        self.createEditorButtons()
        self.createEditorInterface()

    def redo(self):
        """
        funzione per l'implementazione della funzione di redo. Ricrea
        l'interfaccia dell'editor
        """
        self.redo_undo_button_press = True
        g_undoredo.redo()
        self.room = g_project.data['rooms'][g_project.data['world'].start]
        self.resetEditor()
        g_project.notify()
        self.redo_button.setEnabled(g_undoredo.moreRedo())
        self.redo_undo_button_press = False

    def undo(self):
        """
        funzione per l'implementazione della funzione di undo. Ricrea
        l'interfaccia dell'editor
        """
        self.redo_undo_button_press = True
        g_undoredo.undo()
        self.room = g_project.data['rooms'][g_project.data['world'].start]
        self.resetEditor()
        g_project.notify()
        self.undo_button.setEnabled(g_undoredo.moreUndo())
        self.redo_undo_button_press = False


    def startEngine(self):
        self.engine = startEngine(self.engine)

    def playMusic(self):
        if self.music_player is None:
            self.music_player = QSound(self.room.bgm, self)
            self.music_player.play()
        else:
            if self.music_player.isFinished():
                self.music_player.play
            else:
                self.music_player.stop()

    def enableRemoveRoomButton(self):
        self.remove_room_button.setEnabled(True)

    def changeCurrentRoom(self, room_name):
        """
        funzione per la gestione del cambio della room selezionata
        """
        name = unicode(room_name)
        self.room = g_project.data['rooms'][name]
        self.play_bgm_button.setRoom(self.room)

    def removeRoom(self):
        """
        funzione per la gestione della rimozione di una room
        """
        self.redo_undo_button_press = True
        g_project.removeRoom(self.room.id)
        if g_project.data['world'].start:
            self.room = g_project.data['rooms'][g_project.data['world'].start]
        else:
            self.room = None
        self.resetEditor()
        g_undoredo.addSelectedRoom(self.room)
        self.undo_button.setEnabled(g_undoredo.moreUndo())

    def setDirty(self, value):
        self.dirty = value
        self.save_project_button.setEnabled(value)

    def updateData(self):
        if not self.redo_undo_button_press:
            self.setDirty(True)
            g_undoredo.addSelectedRoom(self.room)
        self.redo_undo_button_press = False


    def openProject(self):
        if self.dirty:
            ret = QMessageBox.question(self, "Save", "Do you want save the file?",
                                       QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel)
            if ret == QMessageBox.Yes:
                if not self.saveProject():
                    return
            elif ret == QMessageBox.Cancel:
                return
        if not self.dirty or ret:
            file_open = QFileDialog()
            self.path_file = unicode(file_open.getOpenFileName(filter="*.rooms"))
            if self.path_file:
                g_undoredo.reset()
                openFileRooms(self.path_file)
                if g_project.data['world'].start:
                    self.room = g_project.data['rooms'][g_project.data['world'].start]
                    self.remove_room_button.setEnabled(True)
                else:
                    self.room = None
                    self.remove_room_button.setEnabled(False)
                self.resetEditor()
                g_ptransform.path_file = split(self.path_file)[0]
                g_project.notify()
                self.setDirty(False)

    def saveProject(self):
        if self.dirty:
            self.path_file = QFileDialog().getSaveFileNameAndFilter(parent=self,
                                                            filter="*.rooms")
            if self.path_file and self.path_file[0]:
                try:
                    saveFileRooms(self.path_file[0])
                except ValueError:
                    print "Unable to save file"
                    return False
                else:
                    self.setDirty(False)
                return True
            else:
                return False

    def closeEvent(self, event):
        if self.dirty:
            ret = QMessageBox.question(self,
                                       "Save", "Do you want save the file?",
                                       QMessageBox.Yes | \
                                       QMessageBox.No | QMessageBox.Cancel)
            if ret == QMessageBox.Yes:
                if not self.saveProject():
                    event.ignore()
            elif ret == QMessageBox.Cancel:
                event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    file_name = "../examples/example5/world.rooms"
    if len(sys.argv) == 2:
        file_name = str(sys.argv[1])
    sys.excepthook = handleException
    editor = Editor(file_name)
    editor.show()
    editor.move(QPoint(150, 150))
    app.exec_()
