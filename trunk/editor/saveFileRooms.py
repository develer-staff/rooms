#!/usr/bin/env python

from xml.dom import minidom
from xml.etree import ElementTree

#to use OrderedDict in python < 2.7
try:
    from collections import OrderedDict
except ImportError:
    from misc.dict import OrderedDict

from structData.world import g_world

def prettify(content):
    """
    Return a pretty-printed XML string for the Element.
    """
    rough_string = ElementTree.tostring(content, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

def saveData(top, tag, dictionary):
    tag_dict = {}
    dict_todo = []
    #cicla su tutti gli elementi del dizionario
    #se trova delle liste le salva per poi richiamare se stessa
    #su questi per poter memorizzare i dati
    for key, value in dictionary.items():
        if not isinstance(value, list):
            tag_dict[key] = value
        else:
            dict_todo.append(value)
    father_tag = ElementTree.SubElement(top, tag, tag_dict)
    for el in dict_todo:
        for single_el in el:
            saveData(father_tag, single_el.tag_name, single_el.dictionary())

def saveFileRooms(path_file):
    """
    funzione che salva la struttura dati su un file .rooms
    prende in ingresso il path del file e la struttura che contiene tutti i dati
    da salvare
    """
    top = ElementTree.Element("world",
                              g_world.informations.dictionary())
    for key_information in g_world.dictionary():
        if key_information != "informations":
            father = ElementTree.SubElement(top, key_information)
            for key in g_world.__dict__[key_information]:
                saveData(father, g_world.__dict__[key_information][key].tag_name,
                         g_world.__dict__[key_information][key].dictionary())
    write_file = open(path_file, 'w')
    write_file.write(prettify(top))
