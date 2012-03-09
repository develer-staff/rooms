#!/usr/bin/env python

from origin import OriginData

class Event(OriginData):
    tag_name = 'event'
    def __init__(self, id):
        super(Event, self).__init__()
        self.id = id
        self.requirements = []
        self.actions = []
