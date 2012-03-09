#!/usr/bin/env python

from origin import OriginData

class Action(OriginData):
    tag_name = 'action'

    def __init__(self, id):
        super(Action, self).__init__()
        self.name = id
        self.params = []
