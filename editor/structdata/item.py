#!/usr/bin/env python

from origin import OriginData

class Item(OriginData):

    tag_name = 'item'

    def __init__(self, id, x, y, height, width, room, image, event):
        super(Item, self).__init__()
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.room = room
        self.image = image
        self.event = event
