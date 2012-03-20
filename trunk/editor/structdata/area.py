#!/usr/bin/env python

from origin import OriginData
from structdata.project import g_project

class Area(OriginData):
    tag_name = 'area'
    def __init__(self, id, x, y, width, height, event):
        super(Area, self).__init__()
        self.id = id
        self.x = str(float(x) * int(g_project.data['world'].width))
        self.y = str(float(y) * int(g_project.data['world'].height))
        self.height = str(float(height) * int(g_project.data['world'].height))
        self.width = str(float(width) * int(g_project.data['world'].width))
        self.event = event

    def dictionary(self):
        attribute_dictionary = {}
        for key, value in self.__dict__.items():
            if key.startswith("_"):
                continue
            else:
                if key == "x" or key == "width":
                    attribute_dictionary[key] = str(float(value) / \
                                                float(g_project.data['world'].width))
                elif key == "y" or key == "height":
                    attribute_dictionary[key] = str(float(value) / \
                                                float(g_project.data['world'].height))
        return attribute_dictionary

    @staticmethod
    def create(room, x, y, width, height, event=""):
        number_of_new_area = 0
        for area in room.areas:
            if area.id.find("new_area") != -1:
                number_of_new_area += 1
        area = Area("new_area_%d" % (number_of_new_area + 1), str(x), str(y),
                    str(width), str(height), event)
        room.areas.append(area)
        return area

