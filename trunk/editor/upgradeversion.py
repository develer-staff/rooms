#!/usr/bin/env python

last_version = 3
from xml.etree import ElementTree

def from1To2(xml_file):
    """
    funzione per il passaggio dalla versione 1 alla versione 2 del file
    imposta le coordinate da assolute a relative
    """
    xml_file.set('version', '2')
    for node in xml_file.iter('world'):
        width = int(node.get('width'))
        height = int(node.get('height'))
    for node in xml_file.find('items').getiterator():
        if node.tag == "item":
            node.set('x', str(round(float(node.get('x')) / width, 3)))
            node.set('y', str(round(float(node.get('y')) / height, 3)))
            node.set('width', str(round(float(node.get('width')) / width, 3)))
            node.set('height', str(round(float(node.get('height')) / height, 3)))
    for node in xml_file.find('rooms').getiterator():
        if node.tag == 'area':
            node.set('x', str(round(float(node.get('x')) / width, 3)))
            node.set('y', str(round(float(node.get('y')) / height, 3)))
            node.set('width', str(round(float(node.get('width')) / width, 3)))
            node.set('height', str(round(float(node.get('height')) / height, 3)))
    return xml_file

def from2To3(xml_file):
    """
    funzione per il passaggio dalla versione 2 alla versione 3 del file
    inserisce in tutte le room il campo bgm (background music)
    """
    xml_file.set('version', '3')
    for node in xml_file.find('rooms').getiterator():
        if node.tag == 'room':
            node.set('bgm', '')
    return xml_file

def upgradeVersion(path_file):
    """
    funzione per portare un qualsiasi file .rooms all'ultima versione
    corrente
    prende in ingresso il path del file di cui fare l'upgrade
    ritorna un xml.etree.Element del contenuto del file aggiornato all'ultima
    versione disponibile
    """
    upgrade_function = [from1To2, from2To3]
    xml_file = ElementTree.fromstring(open(path_file, 'rb').read())
    version = int(xml_file.get('version'))
    while version < last_version:
        xml_file = upgrade_function[version - 1](xml_file)
        version += 1
    return xml_file


if __name__ == "__main__":
    upgradeVersion('world.rooms')
