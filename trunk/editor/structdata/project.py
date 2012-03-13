#!/usr/bin/env python

try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from subject import Subject
from room import Room

class Project(Subject):
    def __init__(self):
        super(Project, self).__init__()
        self.data = OrderedDict()
        self.data['world'] = None
        self.data['images'] = {}
        self.data['items'] = OrderedDict()
        self.data['vars'] = {}
        self.data['events'] = OrderedDict()
        self.data['rooms'] = OrderedDict()

    def addNewRoom(self):
        number_of_new_room = 0
        for key in self.data['rooms'].keys():
            if key.find("new_room") != -1:
                number_of_new_room += 1
        room = Room("new_room_%d" % (number_of_new_room + 1), "", "")
        self.data['rooms'][room.id] = room
        self.notify()

g_project = Project()

