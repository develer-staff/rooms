#!/usr/bin/env python

import os
import unittest
from xml.etree import ElementTree

from openfilerooms import openFileRooms
from savefilerooms import saveFileRooms

class Test(unittest.TestCase):
    test_output = "a.rooms"

    def test1(self):
        fpath = os.path.abspath(__file__)
        path, _ = os.path.split(fpath)
        source = os.path.join(path, "..", "examples", "example1", "world.rooms")
        source = os.path.normpath(source)
        dest = self.test_output
        openFileRooms(source)
        saveFileRooms(dest)
        xml_file_world = ElementTree.fromstring(open(source, 'rb').read())
        xml_file_a = ElementTree.fromstring(open(dest, 'rb').read())
        diff = []
        for line in xml_file_world.getiterator():
            difference = self.findDiff(line, xml_file_a)
            if difference:
                diff.append(difference)
        self.assertEqual(diff, [], diff)


    def findDiff(self, line, xml_file_a):
        find = False
        for line_a in xml_file_a.getiterator(line.tag):
            if line.tag == line_a.tag:
                if line.attrib == line_a.attrib:
                    find = True
                    break
        if not find:
            return line, line_a
        return None

    def tearDown(self):
        # Cleanup the temporary file used for test purposes
        os.unlink(self.test_output)

if __name__ == "__main__":
    unittest.main()

