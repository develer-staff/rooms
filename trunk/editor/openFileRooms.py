#!/usr/bin/env python
from xml.etree import ElementTree

from structData.area import Area
from structData.requirement import Requirement
from structData.action import Action
from structData.param import Param
from structData.item import Item
from structData.event import Event
from structData.room import Room

from upgradeVersion import upgradeVersion

def loadRooms(xml_file):
    rooms = {}
    room = None
    for line in xml_file.find("rooms").iter():
        if line.tag == "room":
            room = Room(line.attrib["id"], line.attrib["bg"],
                            line.attrib["bgm"])
            rooms[room.name] = room
        elif line.tag == "area":
            area = Area(line.attrib["id"],
                            line.attrib["x"],
                            line.attrib["y"],
                            line.attrib["height"],
                            line.attrib["width"],
                            line.attrib["event"])
            room.addArea(area)
    return rooms

def loadEvents(xml_file):
    events = {}
    event = None
    var_name = ""
    var_start_set = {}
    for line in xml_file.find("vars").iter():
        if line.tag == "var":
            var_start_set[line.attrib['id']] = line.attrib['value']
    for line in xml_file.find("events").iter():
        if line.tag == "event":
            event = Event(line.attrib["id"])
            events[event.name] = event
        if line.tag == "item_req" or line.tag == "var_req":
            requirement = Requirement(line.attrib['id'], line.attrib['value'], line.tag)
            event.addRequirement(requirement)
        if line.tag == "action":
            action = Action(line.attrib['id'])
            event.addAction(action)
        if line.tag == "param":
            if action.name == "VAR_SET":
                if not var_name:
                    var_name = line.attrib['value']
                    continue
                else:
                    set_value = line.attrib['value']
                param = Param(var_name, set_value)
                if var_name in var_start_set.keys():
                    param.start_value = var_start_set[var_name]
                action.addParam(param)
                var_name = ""
            else:
                param = Param(line.attrib['value'], line.attrib['value'])
                action.addParam(param)
    return events

def loadItems(xml_file):
    items = {}
    for line in xml_file.find("items").iter():
        if line.tag == "item":
            item = Item(line.attrib['id'],
                            line.attrib["x"],
                            line.attrib["y"],
                            line.attrib["height"],
                            line.attrib["width"],
                            line.attrib["room"],
                            line.attrib["image"])
            items[item.name] = item
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
    rooms = loadRooms(xml_file)
    events = loadEvents(xml_file)
    items = loadItems(xml_file)
    return informations, rooms, events, items, images
