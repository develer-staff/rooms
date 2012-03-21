#!/usr/bin/env python

from origin import OriginData
from project import g_project

class World(OriginData):

    tag_name = 'world'

    def __init__(self, version, name, width, height, start):
        self.version = version
        self.name = name
        self.width = width
        self.height = height
        self.start = start

    @staticmethod
    def create(version, name, width, height, start):
        return World(version, name, width, height, start)
