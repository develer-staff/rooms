#!/usr/bin/env python
from origin import OriginData

from area import Area

class Room(OriginData):

    tag_name = 'room'
    def __init__(self, id, bg, bgm):
        super(Room, self).__init__()
        self.id = id
        self.bg = bg
        self.areas = []
        self.bgm = bgm

    def addArea(self, x, y, width, height, event=""):
        number_of_new_area = 0
        for area in self.areas:
            if area.id.find("new_area") != -1:
                number_of_new_area += 1
        area = Area("new_area_%d" % (number_of_new_area + 1), str(x), str(y),
                    str(width), str(height), event)
        self.areas.append(area)
        return area
