#!/usr/bin/env python

class Item(object):

    def __init__(self, id, x, y, height, width, room, image):
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.room = room
        self.image = image
