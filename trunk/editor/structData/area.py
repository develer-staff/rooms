#!/usr/bin/env python

class Area(object):

    def __init__(self, name, x, y, height, width, event_name, event=None):
        self.name = name
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.event_name = event_name
        self.event = event
