#!/usr/bin/env python
from xml.etree import ElementTree
from misc.odict import OrderedDict

from structdata import Area
from structdata import Action
from structdata import Param
from structdata import Item
from structdata import Event
from structdata import Room
from structdata import Var
from structdata import Image
from structdata import World
from structdata import VarRequirement
from structdata import ItemRequirement
from structdata import g_project
from structdata import class_tag

from upgradeversion import upgradeVersion

class OpenFileError(Exception):

    def __init__(self, file_path):
        self.file_path = file_path

    def __str__(self):
        return "Error opening file %s", self.file_path

def loadRooms(xml_file):
    rooms = OrderedDict()
    room = None
    for line in list(xml_file.find("rooms")):
            room = class_tag[line.tag](**line.attrib)
            for child in line:
                area = class_tag[child.tag](**child.attrib)
                room.areas.append(area)
            rooms[room.id] = room
    return rooms

def loadEvents(xml_file):
    events = OrderedDict()
    event = None
    for line in list(xml_file.find("events")):
        event = class_tag[line.tag](**line.attrib)
        events[event.id] = event
        for child in line:
            if child.tag == "item_req" or child.tag == "var_req":
                requirement = class_tag[child.tag](**child.attrib)
                event.requirements.append(requirement)
            else:
                action = Action(child.attrib['id'])
                event.actions.append(action)
                for second_child in child:
                        param = class_tag[second_child.tag](**second_child.attrib)
                        action.params.append(param)
    return events

def loadItems(xml_file):
    items = OrderedDict()
    for line in list(xml_file.find("items")):
        item = class_tag[line.tag](**line.attrib)
        items[item.id] = item
    return items

def loadInformation(xml_file):
    informations = None
    for node in xml_file.getiterator('world'):
        informations = class_tag[node.tag](**node.attrib)
    return informations

def loadImages(xml_file):
    images = {}
    for line in list(xml_file.find("images")):
        images[line.attrib['file']] = class_tag[line.tag](**line.attrib)
    return images

def loadVars(xml_file):
    variable = {}
    for line in list(xml_file.find("vars")):
        variable[line.attrib['id']] = class_tag[line.tag](**line.attrib)
    return variable

def openFileRooms(file_path):
    """
    funzione per il caricamento dei dati salvati da un file .rooms
    prende in ingresso il path del file da controllare
    Si suppone che nel momento che il file viene passato alle funzioni per
    ottenere le informazioni del progetto il file sia in un formato corretto
    Se il caricamento va a buon fine memorizza nella variabile globale g_project
    tutte le informazioni altrimenti lancia un eccezione di tipo OpenFileRoom
    la funzione puo' prendere anche un file .rooms che ha una versione
    precedente all'ultima realizzata
    """
    try:
        from xml.etree.ElementTree import ParseError as XMLError
    except ImportError:
        # Python < 2.7
        from xml.parsers.expat import ExpatError as XMLError

    try:
        xml_file = upgradeVersion(file_path)
    except XMLError:
        raise OpenFileError(file_path)
    try:
        world = loadInformation(xml_file)
        g_project.data['world'] = world
        images = loadImages(xml_file)
        items = loadItems(xml_file)
        variables = loadVars(xml_file)
        events = loadEvents(xml_file)
        rooms = loadRooms(xml_file)
    except ValueError:
        raise OpenFileError(file_path)
    else:
        g_project.data['world'] = world
        g_project.data['images'] = images
        g_project.data['items'] = items
        g_project.data['vars'] = variables
        g_project.data['events'] = events
        g_project.data['rooms'] = rooms
