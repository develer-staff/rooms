#!/usr/bin/env python

from action import Action

class Event(object):
    def __init__(self, id):
        self.id = id
        self.requests = list()
        self.actions = list()

    def __setattr__(self, attr, value):
        self.__dict__[attr] = value

    def getRequest(self):
        return self.requests

    def addRequest(self, request):
        self.requests.append(request)

    def addAction(self, action):
        self.actions.append(action)

    def getActions(self):
        return self.actions
