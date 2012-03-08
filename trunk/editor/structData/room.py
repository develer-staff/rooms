#!/usr/bin/env python
import area

class Room(object):

    def __init__(self, name, bg, height=None, width=None, bgm=None):
        self.name = name
        self.bg = bg
        self.areas = []
        self.bgm = bgm
        self.width = width
        self.height = height

    def addArea(self, area):
        self.areas.append(area)

    def getAreas(self):
        return self.areas
