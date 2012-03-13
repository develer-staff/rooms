#!/usr/bin/env python

class OriginData(object):

    def dictionary(self):
        attributes_dictionary = {}
        for key, value in self.__dict__.items():
            if key.startswith("_"):
                continue
            else:
                attributes_dictionary[key] = value

        return attributes_dictionary
