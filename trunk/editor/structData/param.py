#!/usr/bin/env python

class Param(object):

    def __init__(self, name, value=None, start_value=None):
        self.name = name
        self.start_value = start_value
        self.value = value
