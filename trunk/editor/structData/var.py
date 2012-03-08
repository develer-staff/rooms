#!/usr/bin/env python

class Var(object):

    def __init__(self, name, start_value, set_value=None):
        self.name = name
        self.start_value = start_value
        self.set_value = set_value
