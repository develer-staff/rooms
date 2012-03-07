#!/usr/bin/env python

class Area(object):

    def __init__(self, id, x, y, height, width, event_name, event=None):
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.event_name = event_name
        self.event = event
