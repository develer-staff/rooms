#!/usr/bin/env python

from xml.dom import minidom
from xml.etree import ElementTree

try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

def prettify(content):
    """
    Return a pretty-printed XML string for the Element.
    """
    rough_string = ElementTree.tostring(content, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

def createDictionary(start_dictionary):
    new_dict = {}
    for key in start_dictionary.keys():
        new_dict[key] = str(start_dictionary[key])
    return new_dict

def saveArea(areas, room_tag):
    for area in areas:
        ElementTree.SubElement(room_tag, 'area', {'id':area.name,
                                                  'x':str(area.x),
                                                  'y':str(area.y),
                                                  'width':str(area.width),
                                                  'height':str(area.height),
                                                  'event':str(area.event_name)})

def saveRooms(top, rooms):
    rooms_tag = ElementTree.SubElement(top, 'rooms')
    for room_key in rooms.keys():
        room_tag = ElementTree.SubElement(rooms_tag,
                                              'room',
                                              {'id': str(rooms[room_key].name),
                                               'bg': str(rooms[room_key].bg),
                                               'bgm': str(rooms[room_key].bgm)})
        saveArea(rooms[room_key].areas, room_tag)

def saveParam(params, action_tag):
    for param in params:
        ElementTree.SubElement(action_tag, 'param',
                                           {'value': str(param.name)})

def saveVar(variables, action_tag):
    for variable in variables:
        ElementTree.SubElement(action_tag, 'param',
                               {'value': str(variable.name), })
        ElementTree.SubElement(action_tag, 'param',
                               {'value':str(variable.start_value)})

def saveAction(actions, event_tag):
    for action in actions:
        action_tag = ElementTree.SubElement(event_tag, 'action', {'id':action.name})
        saveParam(action.params, action_tag)

def saveEventRequirements(requirements, event_tag):
    for requirement in requirements:
        ElementTree.SubElement(event_tag, requirement.type, {'id': requirement.name,
                                                         'value': str(requirement.value)})

def saveEvents(top, events):
    events_tag = ElementTree.SubElement(top, 'events')
    for key in events.keys():
        event_tag = ElementTree.SubElement(events_tag, 'event', {'id':key})
        saveEventRequirements(events[key].requirements, event_tag)
        saveAction(events[key].actions, event_tag)

def saveVars(top, variables):
    vars_tag = ElementTree.SubElement(top, 'vars')
    for variable in variables:
        ElementTree.SubElement(vars_tag, 'var', {'id':variable.name,
                                                 'value':str(variable.start_value)})


def saveItems(top, items):
    items_tag = ElementTree.SubElement(top, 'items')
    for key in items.keys():
        ElementTree.SubElement(items_tag, 'item', {'id': items[key].name,
                                                   'x':items[key].x,
                                                   'y':items[key].y,
                                                   'height':items[key].height,
                                                   'width':items[key].width,
                                                   'room':items[key].room,
                                                   'image':items[key].image})

def saveImages(top, images):
    if images:
        images_tag = ElementTree.SubElement(top, 'images')
        for image in images:
            ElementTree.SubElement(images_tag, 'img', {'file': image})

def saveFileRooms(path_file, struct_information):

    top = ElementTree.Element("world", createDictionary(struct_information['informations']))
    saveImages(top, struct_information['images'])
    saveItems(top, struct_information['items'])
    saveVars(top, struct_information['variables'])
    saveEvents(top, struct_information['events'])
    saveRooms(top, struct_information['rooms'])
    write_file = open(path_file, 'w')
    write_file.write(prettify(top))
