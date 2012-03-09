#!/usr/bin/env python

from origin import OriginData

class Information(OriginData):

    tag_name = 'world'

    def __init__(self, version, name, width, height, start):

        self.version = version
        self.name = name
        self.width = width
        self.height = height
        self.start = start
