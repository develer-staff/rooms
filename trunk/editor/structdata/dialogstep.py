#!/usr/bin/env python

from origin import OriginData
from project import g_project

class Step(OriginData):

    tag_name = "step"

    def __init__(self, id, text):
        self.id = id
        self.text = text
        self.requirements = []
        self.actions = []
        self.links = []

