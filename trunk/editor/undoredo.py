#!/usr/bin/env python

from structdata import g_project
from openfilerooms import openRooms
from savefilerooms import saveRooms, saveFileRooms
from os import mkdir
from os.path import exists
from os import remove


class UndoRedo(object):


    def __init__(self):
        g_project.subscribe(self)
        self._list_of_project = []
        self._add_element = True
        self._list_index = -1
        self._list_of_room = []
        self._subscibers = set()


    def undo(self):
        self._list_index -= 1
        self._add_element = False
        openRooms(self._list_of_project[self._list_index ])

    def redo(self):
        self._add_element = False
        openRooms(self._list_of_project[self._list_index])
        self._list_index += 1

    def getCurrentRoom(self):
        room_id = self._list_of_room[self._list_index]
        room = g_project.data['rooms'][room_id]
        return room

    def addSelectedRoom(self, room=None):
        if room is not None:
            self._list_of_room.append(room.id)
        else:
            self._list_of_room.append("")

    def moreUndo(self):
        if len(self._list_of_project) == 0:
            return False
        return (self._list_index > 0)

    def moreRedo(self):
        return (self._list_index < len(self._list_of_project))

    def updateData(self):

        if self._add_element:
            self._list_index += 1
            if len(self._list_of_project):
                self._list_of_project = self._list_of_project[:self._list_index + 1]
                self._list_of_room = self._list_of_room[:self._list_index + 1]
            self._list_of_project.append(saveRooms())
        self._add_element = True
        self.notify()



g_undoredo = UndoRedo()
