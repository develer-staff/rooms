#!/usr/bin/env python

from origin import OriginData

class Param(OriginData):

    tag_name = 'param'

    def __init__(self, value):
        super(Param, self).__init__()
        self.value = value
