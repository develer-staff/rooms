#!/usr/bin/env python

class Param(object):

    def __init__(self, name, value=0, start_value=0):
        self.name = name
        self.start_value = start_value
        self.value = value
