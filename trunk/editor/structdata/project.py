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

    def changeEventName(self, old_name, new_name):
        event = self.data['events'].pop(old_name)
        event.setName(new_name)
        self.data['events'][event.id] = event
        self.notify()

g_project = Project()

