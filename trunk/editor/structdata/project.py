#!/usr/bin/env python

try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from subject import Subject

class Project(Subject):
    def __init__(self):
        super(Project, self).__init__()
        self.data = OrderedDict()
        self.data['world'] = None
        self.data['images'] = {}
        self.data['items'] = OrderedDict()
        self.data['vars'] = {}
        self.data['events'] = OrderedDict()
        self.data['rooms'] = OrderedDict()

g_project = Project()

