#!/usr/bin/env python
from origin import OriginData

from project import g_project

class Room(OriginData):

    tag_name = 'room'
    def __init__(self, id, bg, bgm):
        super(Room, self).__init__()
        self.id = id
        self.bg = bg
        self.areas = []
        self.bgm = bgm

    def setName(self, name):
        self.id = name
        g_project.notify()

    @staticmethod
    def create():
        number_of_new_room = 0
        for key in g_project.data['rooms'].keys():
            if key.startswith("new_room_"):
                number_of_new_room += 1
        room = Room("new_room_%d" % (number_of_new_room + 1), "", "")
        g_project.data['rooms'][room.id] = room
        g_project.notify()
        return room
