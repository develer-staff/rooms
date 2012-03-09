#!/usr/bin/env python

class OriginData(object):

    def dictionary(self):
        attributes_dictionary = {}
        for key, value in self.__dict__.items():
            if key.startswith("_"):
                continue

#            if key == 'name':
#                attributes_dictionary['id'] = value
#            elif not isinstance(value, list):
#                attributes_dictionary[key] = ""
            else:
                attributes_dictionary[key] = value

        return attributes_dictionary
