#!/usr/bin/env python

from origin import OriginData
from project import g_project

class Event(OriginData):
    tag_name = 'event'
    def __init__(self, id):
        super(Event, self).__init__()
        self.id = id
        self.requirements = []
        self.actions = []

    def setName(self, name):
        self.id = name
        g_project.notify()

    @staticmethod
    def create():
        number_of_event = 0
        for key in g_project.data['events'].keys():
            if key.startswith('new_event_'):
                number_of_event += 1
        event = Event("new_event_%d" % (number_of_event + 1))
        return event
