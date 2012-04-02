#!/usr/bin/env python


from misc.odict import OrderedDict

from subject import Subject

class Project(Subject):
    def __init__(self):
        super(Project, self).__init__()
        self.data = OrderedDict()
        self.data['world'] = None
        self.data['images'] = {}
        self.data['items'] = OrderedDict()
        self.data['vars'] = {}
        self.data['events'] = OrderedDict()
        self.data['rooms'] = OrderedDict()


    def changeImage(self, old_image, new_image):
        image = self.data['images'].pop(old_image)
        image.file = new_image
        self.data['images'][new_image] = image
        self.notify()

    def changeEventName(self, old_name, new_name):
        event = self.data['events'].pop(old_name)
        event.setName(new_name)
        self.data['events'][event.id] = event
        self.notify()

    def changeStartRoom(self, new_start_room_name):
        self.data['world'].start = new_start_room_name
        self.notify()

    def changeRoomName(self, old_room_name, new_room_name):
        room = self.data['rooms'].pop(old_room_name)
        self.data['rooms'][new_room_name] = room
        if self.data['world'].start == old_room_name:
            self.changeStartRoom(new_room_name)
        room.setName(new_room_name)
        self.notify()

    def removeRoom(self, room_name):
        self.data['rooms'].pop(room_name)
        if self.data['world'].start == room_name:
            if g_project.data['rooms']:
                new_start_room_name = g_project.data['rooms'].keys()[0]
            else:
                new_start_room_name = ""
            self.changeStartRoom(new_start_room_name)
        self.notify()

g_project = Project()

