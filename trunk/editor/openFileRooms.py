#!/usr/bin/env python
from xml.etree import ElementTree
from twisted.python.formmethod import InputError
try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from structData.area import Area
from structData.requirement import Requirement
from structData.action import Action
from structData.param import Param
from structData.item import Item
from structData.event import Event
from structData.room import Room
from structData.var import Var

from upgradeVersion import upgradeVersion

def loadRooms(xml_file):
    rooms = OrderedDict()
    room = None
    for line in list(xml_file.find("rooms")):
        if line.tag == "room":
            room = Room(line.attrib["id"], line.attrib["bg"],
                            line.attrib["bgm"])
            for child in line:
                if child.tag == "area":
                    area = Area(line.attrib["id"],
                            child.attrib["x"],
                            child.attrib["y"],
                            child.attrib["height"],
                            child.attrib["width"],
                            child.attrib["event"])
                else:
                    raise InputError, "invalid tag %s in room" % child.tag
                room.areas.append(area)
            rooms[room.name] = room
        else:
            raise InputError, "invalid tag %s in rooms" % line.tag
    return rooms

def loadEvents(xml_file):
    events = OrderedDict()
    event = None
    for line in xml_file.find("events").iter():
        if line.tag == "event":
            event = Event(line.attrib["id"])
            events[event.name] = event
        if line.tag == "item_req" or line.tag == "var_req":
            requirement = Requirement(line.attrib['id'], line.attrib['value'],
                                      line.tag)
            event.requirements.append(requirement)
        if line.tag == "action":
            action = Action(line.attrib['id'])
            event.actions.append(action)
        if line.tag == "param":
            param = Param(line.attrib['value'])
            action.params.append(param)
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

def loadVars(xml_file):
    variable = []
    for line in xml_file.find("vars").iter():
        if line.tag == "var":
            variable.append(Var(line.attrib['id'], line.attrib['value']))
    return variable

def openFileRooms(path_file):
    """
    funzione per il caricamento dei dati salvati da un file .rooms
    prende in ingresso il path del file da controllare
    ritorna un dizionario con tutte le informazioni su rooms, events, items,
    images
    la funzione puo' prendere anche un file .rooms che ha una versione
    precedente all'ultima realizzata
    """
    xml_file = upgradeVersion(path_file)
    informations = loadInformation(xml_file)
    images = loadImages(xml_file)
    rooms = loadRooms(xml_file)
    events = loadEvents(xml_file)
    items = loadItems(xml_file)
    variables = loadVars(xml_file)
    return {'informations':informations, 'rooms':rooms,
            'events':events, 'items':items,
            'variables':variables, 'images':images}
