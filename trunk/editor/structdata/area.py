#!/usr/bin/env python

from origin import OriginData

class Area(OriginData):
    tag_name = 'area'
    def __init__(self, id, x, y, width, height, event):
        super(Area, self).__init__()
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.event = event

    @staticmethod
    def create(room, x, y, width, height, event=""):
        number_of_new_area = 0
        for area in room.areas:
            if area.id.find("new_area") != -1:
                number_of_new_area += 1
        area = Area("new_area_%d" % (number_of_new_area + 1), str(x), str(y),
                    str(width), str(height), event)
        room.areas.append(area)
        return area

