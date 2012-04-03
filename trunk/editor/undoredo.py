#!/usr/bin/env python

from structdata import g_project
from openfilerooms import openRooms
from savefilerooms import saveRooms
from os import mkdir
from os.path import exists
from os import remove


class UndoRedo(object):


    def __init__(self):
        self._list_of_project = []
        self._add_element = True
        self._list_index = 0
        g_project.subscribe(self)

    def undo(self):
        if self.moreUndo():
            self._list_index -= 1
            self._add_element = False
            openRooms(self._list_of_project[self._list_index - 1])
            g_project.notify("undoredo")

    def moreUndo(self):
        return self._list_index > -1

    def updateData(self):
        if self._add_element:
            self._list_index += 1
            self._list_of_project = self._list_of_project[:self._list_index]
            self._list_of_project.append(saveRooms())
        self._add_element = True

g_undoredo = UndoRedo()
