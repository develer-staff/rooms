#!/usr/bin/env python

from origin import OriginData

class Requirement(OriginData):

    def __init__(self, id, value):
        super(Requirement, self).__init__()
        self.id = id
        self.value = value
