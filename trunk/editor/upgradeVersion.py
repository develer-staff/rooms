#!/usr/bin/env python

last_version = 3
from xml.etree import ElementTree

def from1To2(xml_file):
    xml_file.set('version', '2')
    for node in xml_file.iter('world'):
        width = int(node.get('width'))
        height = int(node.get('height'))
    for node in xml_file.find('items').iter():
        if node.tag == "item":
            node.set('x', str(round(float(node.get('x')) / width, 3)))
            node.set('y', str(round(float(node.get('y')) / height, 3)))
            node.set('width', str(round(float(node.get('width')) / width, 3)))
            node.set('height', str(round(float(node.get('height')) / height, 3)))
    for node in xml_file.find('rooms').iter():
        if node.tag == 'area':
            node.set('x', str(round(float(node.get('x')) / width, 3)))
            node.set('y', str(round(float(node.get('y')) / height, 3)))
            node.set('width', str(round(float(node.get('width')) / width, 3)))
            node.set('height', str(round(float(node.get('height')) / height, 3)))
    return xml_file

def from2To3(xml_file):
    xml_file.set('version', '3')
    for node in xml_file.find('rooms').iter():
        if node.tag == 'room':
            node.set('bgm', '')
    return xml_file

def upgradeVersion(path_file):
    upgrade_function = [from1To2, from2To3]
    xml_file = ElementTree.fromstring(open(path_file, 'rb').read())
    version = int(xml_file.get('version'))
    while version < last_version:
        xml_file = upgrade_function[version - 1](xml_file)
        version += 1
    return xml_file


if __name__ == "__main__":
    upgradeVersion('world.rooms')
