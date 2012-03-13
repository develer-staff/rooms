#!/usr/bin/env python

class OriginData(object):
    """
    classe base da cui derivano tutte le classi del modello. Questa dipendenza
    e' fatta per la serializzazione nel momento del salvataggio.
    I dati che vengono serializzati sono tutti gli attributi pubblici che non 
    cominciano con underscore e hanno nome uguale ai tag che vengono salvati 
    nel file XML nel file .rooms
    Gli attributi di tipo lista verranno poi serializzati nuovamente
    """

    def dictionary(self):
        attributes_dictionary = {}
        for key, value in self.__dict__.items():
            if key.startswith("_"):
                continue
            else:
                attributes_dictionary[key] = value

        return attributes_dictionary
