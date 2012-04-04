#!/usr/bin/env python

from structdata import g_project
from openfilerooms import openRooms
from savefilerooms import saveRooms, saveFileRooms
from os import mkdir
from os.path import exists
from os import remove


class UndoRedo(object):


    def __init__(self):
        self._list_of_project = []
        self._add_element = True
        self._list_index = 0
        self._list_of_room = []
        g_project.subscribe(self)

    def undo(self):
        self._list_index -= 1
        self._add_element = False
        openRooms(self._list_of_project[self._list_index - 1])
        g_project.notify()

    def getCurrentRoom(self):
        room_id = self._list_of_room[self._list_index - 1]
        room = g_project.data['rooms'][room_id]
        return room

    def addSelectedRoom(self, room=None):
        if room is None:
            room = self._list_of_room[self._list_index - 1]
        self._list_of_room.append(room.id)

    def moreUndo(self):
        return (self._list_index > 1)

    def updateData(self):
        if self._add_element:
            self._list_index += 1
            self._list_of_project = self._list_of_project[:self._list_index]
            self._list_of_room = self._list_of_room[:self._list_index]
            self._list_of_project.append(saveRooms())
            self._add_element = True

g_undoredo = UndoRedo()
