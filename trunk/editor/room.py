#!/usr/bin/env python
import area

class Room(object):

    def __init__(self, id, bg, height=0, width=0, bgm=""):
        self.id = id
        self.bg = bg
        self.areas = list()
        self.bgm = bgm
        self.width = width
        self.height = height

    def addArea(self, area):
        self.areas.append(area)

    def getAreas(self):
        return self.areas
