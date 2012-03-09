#!/usr/bin/env python

from origin import OriginData

class Area(OriginData):
    tag_name = 'area'
    def __init__(self, id, x, y, height, width, event_name):
        super(Area, self).__init__()
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.event_name = event_name
