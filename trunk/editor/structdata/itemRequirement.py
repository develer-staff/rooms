#!/usr/bin/env python

from requirement import Requirement
from origin import OriginData

class ItemRequirement(Requirement):

    tag_name = 'item_req'

    def __init__(self, id, value):
        super(ItemRequirement, self).__init__(id, value)
