#!/usr/bin/env python
from param import Param

class Action(object):

    def __init__(self, name):
        self.name = name
        self.params = []

    def addParam(self, param):
        self.params.append(param)

    def getParams(self):
        return self.params
