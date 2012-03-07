#!/usr/bin/env python
from Param import Param

class Action(object):

    def __init__(self, id):
        self.id = id
        self.params = list()

    def addParam(self, param):
        self.params.append(param)

    def getParams(self):
        return self.params
