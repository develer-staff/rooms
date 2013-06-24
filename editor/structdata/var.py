#!/usr/bin/env python

from origin import OriginData

class Var(OriginData):

    tag_name = 'var'
    def __init__(self, id, value):
        super(Var, self).__init__()
        self.id = id
        self.value = value
