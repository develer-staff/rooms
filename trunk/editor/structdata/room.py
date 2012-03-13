#!/usr/bin/env python
from origin import OriginData

class Room(OriginData):

    tag_name = 'room'
    def __init__(self, id, bg, bgm):
        super(Room, self).__init__()
        self.id = id
        self.bg = bg
        self.areas = []
        self.bgm = bgm
