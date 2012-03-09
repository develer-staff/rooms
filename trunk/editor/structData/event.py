#!/usr/bin/env python

from action import Action

class Event(object):
    def __init__(self, name):
        self.name = name
        self.requirements = []
        self.actions = []

    def addRequirement(self, requirements):
        self.requirements.append(requirements)

    def addAction(self, action):
        self.actions.append(action)

    def getActions(self):
        return self.actions
