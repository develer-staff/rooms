#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4.QtCore import *

from structdata import g_project

from areaeditor import AreaEditor
from roommanager import RoomManager

class ResizeButton(QPushButton):

    def sizeHint(self):
        return QSize(10, 10)
    def __init__(self, parent=None):
        super(ResizeButton, self).__init__(parent)
        self.setStyleSheet("background-color:"
                                           "rgba( 255, 255, 255, 100% );")

class AreaResize(QWidget):

    def __init__(self, area, bg_width, bg_height, parent=None):
        super(AreaResize, self).__init__(parent)
        self.in_resize = False
        self.moving_area = False
        self.area_start = None
        self.area_cur = None
        self.show_resize_buttons = False
        self.mouse_on_area_resize = False
        self.bg_width = bg_width
        self.bg_height = bg_height
        self.area = area
        self.resize(QSize(float(self.area.width),
                          float(self.area.height)))
        self.vl = QVBoxLayout()
        self.vl.setContentsMargins(0, 0, 0, 0)
        self.area_editor = None
        self.signal_mapper_pressed = QSignalMapper(self)
        self.resize_buttons = []
        horizontal = QHBoxLayout()
        horizontal.setContentsMargins(0, 0, 0, 0)
        for i in range(8):
            button = ResizeButton(self)
            button.setVisible(False)
            if i == 0 or i == 7:
                button.setCursor(Qt.SizeFDiagCursor)
            elif i == 5 or i == 2:
                button.setCursor(Qt.SizeBDiagCursor)
            elif i == 1 or i == 6:
                button.setCursor(Qt.SizeVerCursor)
            else:
                button.setCursor(Qt.SizeHorCursor)
            horizontal.addWidget(button)
            if i not in [2, 4, 7]:
                horizontal.addStretch()
            else:
                self.vl.addLayout(horizontal)
                if i != 7:
                    self.vl.addStretch()
                    horizontal = QHBoxLayout()
                    horizontal.setContentsMargins(0, 0, 0, 0)
            self.connect(button, SIGNAL("pressed()"),
                         self.signal_mapper_pressed, SLOT("map()"))
            self.signal_mapper_pressed.setMapping(button, i)
            self.resize_buttons.append(button)
        self.setLayout(self.vl)
        self.connect(self.signal_mapper_pressed, SIGNAL("mapped(int)"),
                     self.startTrack)

    def mouseMoveEvent(self, event=None):
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton and self.in_resize:
            self.resizeAreaResize(event.x(), event.y())
        if (event.buttons() and Qt.LeftButton) == Qt.LeftButton and self.moving_area:
            self.area_cur = event.pos()
            self.changeAreaPosition()

    def resizeAreaResize(self, x, y):
        """
        funzione per il ridimensionamento dell'AreaResize. I paramtri passati
        sono le coordinate su cui viene fatto il ridimensionamento
        """
        #uso per non superare i bordi laterali dello sfondo
        x = min(x, self.bg_width - self.x()) if x + self.x() > 0\
                                             else max(0, x)
#            #uso per non superare i bordi superiore e inferiore dello sfondo
        y = min(y, self.bg_height - self.y()) if y + self.y() > 0\
                                              else max(0, y)
        x_widget = self.x()
        y_widget = self.y()
        #resize with top left button
        if self.index == 0:
            self.move(x_widget + x, y_widget + y)
            self.resize(QSize(self.width() - x, self.height() - y))
        #resize with top button
        elif self.index == 1:
            self.move(x_widget, y_widget + y)
            self.resize(QSize(self.width(), self.height() - y))
        #resize with top right button
        elif self.index == 2:
            self.move(self.x(), y_widget + y)
            self.resize(QSize(x, self.height() - y))
        #resize with left button
        elif self.index == 3:
            self.move(x_widget + x, y_widget)
            self.resize(QSize(self.width() - x, self.height()))
        #resize with right button
        elif self.index == 4:
            self.resize(QSize(x, self.height()))
        #resize with bottom left button
        elif self.index == 5:
            self.move(x_widget + x, self.y())
            self.resize(QSize(self.width() - x, y))
        #resize with bottom button
        elif self.index == 6:
            self.resize(QSize(self.width(), y))
        #resize with bottom right button 
        elif self.index == 7:
            self.resize(QSize(x + 5, y + 5))
        self.update()

    def mouseReleaseEvent(self, event=None):
        if self.in_resize or (self.moving_area and self.area_cur is not None):
            self.updateArea()
        else:
            self.area_start = None

    def mousePressEvent(self, event=None):
        self.moving_area = True
        self.area_start = event.pos()

    def changeAreaPosition(self):
        """
        funzione per il calcolo della nuova posizione dell'area nel momento 
        in cui viene cambiata la posizione dell'area
        """
        x_cur = self.area_cur.x()
        y_cur = self.area_cur.y()
        x_start = self.area_start.x()
        y_start = self.area_start.y()
        diff_x = x_cur - x_start
        diff_y = y_cur - y_start
        x_widget = self.x() + diff_x
        y_widget = self.y() + diff_y

        #controllo per non superare orizzontalmente i limiti dell'immagine
        if x_widget < 0:
            x_widget = 0
        elif x_widget + self.width() > self.bg_width:
            x_widget = x_widget - (x_widget + self.width() - self.bg_width)
        #controllo per non superare verticalmente i limiti dell'immagine
        if y_widget < 0:
            y_widget = 0
        elif y_widget + self.height() > self.bg_height:
            y_widget = y_widget - (y_widget + self.height() - self.bg_height)
        self.move(x_widget, y_widget)
        self.update()

    def updateArea(self):
        """
        funzione per il ridimensionamento e lo spostamento di un'area
        """
        if self.in_resize or self.moving_area:
            self.in_resize = False
            self.moving_area = False
            self.area_cur = None
            self.area_start = None
            self.area.x = str(self.x())
            self.area.y = str(self.y())
            self.area.width = str(self.width())
            self.area.height = str(self.height())
            g_project.notify()
            self.update()

    def mouseDoubleClickEvent(self, event=None):
        self.showAreaEditor()

    def showAreaEditor(self):
        self.area_editor = AreaEditor(self.area, self.parent())
        self.area_editor.exec_()

    def keyPressEvent(self, event=None):
        """
        gestione dell'evento di pressione di un tasto. Se il mouse e' sopra 
        l'oggetto e viene premuto il tasto Del l'area associata all'oggetto
        viene cancellata
        """
        if event.key() == Qt.Key_Delete and self.mouse_on_area_resize:
            self.cancelArea()

    def cancelArea(self):
        """
        funzione per la cancellazione dell'area associata all'oggetto
        la funzione si occupa anche di notificare l'avvenuto cambiamento
        del modello dei dati
        """
        room = self.searchRoomForArea()
        if room:
            index = room.areas.index(self.area)
            room.areas.pop(index)
            self.area = None
            g_project.notify()

    def searchRoomForArea(self):
        """
        funzione che cerca la room a cui appartiene l'area associata
        all'oggetto. Se non la trova torna None
        """
        for key, room in g_project.data['rooms'].items():
            if self.area in room.areas:
                return room
        return None

    def enterEvent(self, event=None):
        for cb in self.resize_buttons:
            cb.setVisible(True)
        self.mouse_on_area_resize = True
        self.setFocus()
        self.update()

    def leaveEvent(self, event=None):
        for cb in self.resize_buttons:
            cb.setVisible(False)
        self.mouse_on_area_resize = False
        self.clearFocus()
        self.update()

    def startTrack(self, index):
        self.in_resize = True
        self.index = index


    def drawActionIcon(self, p):
        """
        funzione che disegna le icone delle azioni definite nell'evento
        associato all'area che si sta rappresentando
        la funzione ha come parametro di ingresso un QPainter
        """
        action_to_draw = set()
        for action in g_project.data['events'][self.area.event].actions:
            action_to_draw.add(action.id)
        i = 0
        for action_id in action_to_draw:
            icon_path = "%s.png" % action_id
            icon = QPixmap(icon_path).scaled(20, 20, Qt.KeepAspectRatio,
                                             Qt.SmoothTransformation)
            p.drawPixmap(QPoint(self.width() - 25, i * 30 + 2), icon)
            i += 1

    def drawRequirementIcon(self, p):
        """
        funzione che disegna un icona se per attivare l'evento associato
        all'azione che si sta rappresentando sono necessari uno o piu'
        requirement
        la funzione ha come parametro di ingresso un QPainter
        """
        if len(g_project.data['events'][self.area.event].requirements):
            icon_path = "requirement.png"
            icon = QPixmap(icon_path).scaled(20, 20, Qt.KeepAspectRatio,
                                             Qt.SmoothTransformation)
            p.drawPixmap(QPoint(5, 0), icon)

    def paintEvent(self, event=None):
        QWidget.paintEvent(self, event)
        p = QPainter(self)

        # XXX: senza questo resta il trail dell'area mentre viene
        # ridimensionata: investigare
        p.setRenderHint(QPainter.Antialiasing)

        p.setPen(Qt.blue)
        p.drawRect(0, 0, self.width(), self.height())
        self.drawActionIcon(p)
        self.drawRequirementIcon(p)

