#!/usr/bin/env python

from origin import OriginData
from project import g_project

class Link(OriginData):

    tag_name = "link"

    def __init__(self, id, text):
        self.id = id
        self.text = text
