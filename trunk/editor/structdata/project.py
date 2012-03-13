#!/usr/bin/env python

try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from subject import Subject

class Project(Subject):
    def __init__(self):
        super(Project, self).__init__()
        self.informations = None
        self.images = {}
        self.items = OrderedDict()
        self.vars = {}
        self.events = OrderedDict()
        self.rooms = OrderedDict()
        self.selected_room = None

g_project = Project()

