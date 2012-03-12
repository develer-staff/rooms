#!/usr/bin/env python

try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from origin import OriginData
from subject import Subject

class World(OriginData, Subject):
    tag_name = "world"
    def __init__(self):
        super(OriginData, self).__init__()
        super(Subject, self).__init__()
        self.informations = None
        self.images = {}
        self.items = OrderedDict()
        self.vars = {}
        self.events = OrderedDict()
        self.rooms = OrderedDict()
        self.selected_room = None

g_world = World()

