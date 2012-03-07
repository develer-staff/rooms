#!/usr/bin/env python
from xml.etree import ElementTree
from area import Area
from request import Request
from action import Action
from param import Param
from item import Item
from event import Event
from room import Room
from upgradeVersion import upgradeVersion

def loadRoom(xml_file):
    rooms = {}
    new_room = None
    for line in xml_file.find("rooms").iter():
        if line.tag == "room":
            new_room = Room(line.attrib["id"], line.attrib["bg"],
                            line.attrib["bgm"])
            rooms[new_room.id] = new_room
        if line.tag == "area":
            new_area = Area(line.attrib["id"],
                            line.attrib["x"],
                            line.attrib["y"],
                            line.attrib["height"],
                            line.attrib["width"],
                            line.attrib["event"])
            new_room.addArea(new_area)
    return rooms

def loadEvents(xml_file):
    events = {}
    new_event = None
    var_name = ""
    var_start_set = {}
    for line in xml_file.find("vars").iter():
        if line.tag == "var":
            var_start_set[line.attrib['id']] = line.attrib['value']
    for line in xml_file.find("events").iter():
        if line.tag == "event":
            new_event = Event(line.attrib["id"])
            events[new_event.id] = new_event
        if line.tag == "item_req" or line.tag == "var_req":
            new_request = Request(line.attrib['id'], line.attrib['value'], line.tag)
            new_event.addRequest(new_request)
        if line.tag == "action":
            new_action = Action(line.attrib['id'])
            new_event.addAction(new_action)
        if line.tag == "param":
            if new_action.id == "VAR_SET":
                if not var_name:
                    var_name = line.attrib['value']
                    continue
                else:
                    set_value = line.attrib['value']
                new_param = Param(var_name, set_value)
                if var_name in var_start_set.keys():
                    new_param.start_value = var_start_set[var_name]
                new_action.addParam(new_param)
                var_name = ""
            else:
                new_param = Param(line.attrib['value'], line.attrib['value'])
                new_action.addParam(new_param)
    return events

def loadItems(xml_file):
    items = {}
    for line in xml_file.find("items").iter():
        if line.tag == "item":
            new_item = Item(line.attrib['id'],
                            line.attrib["x"],
                            line.attrib["y"],
                            line.attrib["height"],
                            line.attrib["width"],
                            line.attrib["room"],
                            line.attrib["image"])
            items[new_item.id] = new_item
    return items

def loadInformation(xml_file):
    informations = {}
    for node in xml_file.iter('world'):
        informations['version'] = int(node.attrib['version'])
        informations['width'] = int(node.attrib['width'])
        informations['height'] = int(node.attrib['height'])
        informations['start'] = node.attrib['start']
        informations['name'] = node.attrib['name']
    return informations

def loadImages(xml_file):
    images = []
    for line in xml_file.find("images").iter():
        if line.tag == "img":
            images.append(line.attrib['file'])
    return images

def openFileRooms(path_file):
    xml_file = upgradeVersion(path_file)
    informations = loadInformation(xml_file)
    images = loadImages(xml_file)
    rooms = loadRoom(xml_file)
    events = loadEvents(xml_file)
    items = loadItems(xml_file)
    return informations, rooms, events, items, images
