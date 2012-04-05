#!/usr/bin/env python

from origin import OriginData
from project import g_project

class Dialog(OriginData):

    tag_name = 'dialog'

    def __init__(self, dialog, start):
        self.dialog = dialog
        self.start = start
        self.steps = []
