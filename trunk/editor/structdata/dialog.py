#!/usr/bin/env python

from origin import OriginData
from project import g_project

class Dialog(OriginData):

    tag_name = 'dialog'

    def __init__(self, id, start):
        self.id = id
        self.start = start
        self.steps = []
