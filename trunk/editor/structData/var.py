#!/usr/bin/env python

from origin import OriginData

class Var(OriginData):

    tag_name = 'var'
    def __init__(self, id, start_value):
        super(Var, self).__init__()
        self.name = id
        self.start_value = start_value
