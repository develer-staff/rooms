#!/usr/bin/env python
from param import Param
from var import Var

class Action(object):

    def __init__(self, name):
        self.name = name
        self.params = []
        self.variables = []
