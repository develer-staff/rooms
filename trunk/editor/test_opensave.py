#!/usr/bin/env python

import unittest
from xml.etree import ElementTree

from openFileRooms import openFileRooms
from saveFileRooms import saveFileRooms

class Test(unittest.TestCase):

    def test1(self):
        openFileRooms('world.rooms')
        saveFileRooms('a.rooms')
        xml_file_world = ElementTree.fromstring(open('world.rooms', 'rb').read())
        xml_file_a = ElementTree.fromstring(open('a.rooms', 'rb').read())
        diff = []
        for line in xml_file_world.iter():
            difference = self.findDiff(line, xml_file_a)
            if difference:
                diff.append(difference)
        self.assertEqual(diff, [], diff)


    def findDiff(self, line, xml_file_a):
        find = False
        for line_a in xml_file_a.iter(line.tag):
            if line.tag == line_a.tag:
                if line.attrib == line_a.attrib:
                    find = True
                    break
        if not find:
            return line, line_a
        return None


