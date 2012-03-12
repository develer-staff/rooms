#!/usr/bin/env python

from origin import OriginData
try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict


class World(OriginData):
    tag_name = "world"
    def __init__(self):
        self.informations = None
        self.images = {}
        self.items = OrderedDict()
        self.vars = {}
        self.events = OrderedDict()
        self.rooms = OrderedDict()

g_world = World()

