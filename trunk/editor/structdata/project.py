#!/usr/bin/env python


from misc.odict import OrderedDict

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

