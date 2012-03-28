#!/usr/bin/env python

from origin import OriginData
from structdata.project import g_project

class Area(OriginData):
    """
    Area gestisce coordinate e dimensione fisiche. Nell'xml le informazioni
    sono in coordinate logiche; al momento del caricamento del progetto viene 
    fatta la conversione
    """
    tag_name = 'area'
    def __init__(self, id, x, y, width, height, event):
        super(Area, self).__init__()
        self.id = id
        self.x = str(float(x) * float(g_project.data['world'].width))
        self.y = str(float(y) * float(g_project.data['world'].height))
        self.height = str(float(height) * float(g_project.data['world'].height))
        self.width = str(float(width) * float(g_project.data['world'].width))
        self.event = event


    def valueForKey(self, key, value):
        if key == "x" or key == "width":
            return str(round(float(value) / float(g_project.data['world'].width), 2))
        elif key == "y" or key == "height":
            return str(round(float(value) / float(g_project.data['world'].height), 2))
        else:
            return value

    @staticmethod
    def create(room, x, y, width, height, event=""):
        number_of_new_area = 0
        for area in room.areas:
            if area.id.startswith("new_area_") != -1:
                number_of_new_area += 1
        area = Area("new_area_%d" % (number_of_new_area + 1),
                    str(x / float(g_project.data['world'].width)),
                    str(y / float(g_project.data['world'].height)),
                    str(width / float(g_project.data['world'].width)),
                    str(height / float(g_project.data['world'].height)),
                    event)
        room.areas.append(area)
        return area

