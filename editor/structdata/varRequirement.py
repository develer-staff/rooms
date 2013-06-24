#!/usr/bin/env python

from requirement import Requirement
from origin import OriginData

class VarRequirement(Requirement):
    tag_name = 'var_req'

    def __init__(self, id, value):
        super(VarRequirement, self).__init__(id, value)
