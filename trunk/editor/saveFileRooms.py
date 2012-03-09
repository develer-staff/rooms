#!/usr/bin/env python

from xml.dom import minidom
from xml.etree import ElementTree

#to use OrderedDict in python < 2.7
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

def saveData(top, tag, dictionary):
    tag_dict = {}
    dict_todo = []
    for key, value in dictionary.items():
        if not isinstance(value, list):
            tag_dict[key] = value
        else:
            dict_todo.append(value)
    father_tag = ElementTree.SubElement(top, tag, tag_dict)
    for el in dict_todo:
        for single_el in el:
            saveData(father_tag, single_el.tag_name, single_el.dictionary())

def saveFileRooms(path_file, struct_information):

    top = ElementTree.Element("world",
                        struct_information['informations'].dictionary())
    for key_information in struct_information:
        if key_information != "informations":
            father = ElementTree.SubElement(top, key_information)
            for key in struct_information[key_information]:
                saveData(father, struct_information[key_information][key].tag_name,
                         struct_information[key_information][key].dictionary())
    write_file = open(path_file, 'w')
    write_file.write(prettify(top))
