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

    def valueForKey(self, key, value):
        """
        Template method da ridefinire in classe derivata per personalizzare
        la serializzazione di alcuni dati.
        """
        return value

    def dictionary(self):
        """
        Metodo di serializzazione, non ridefinire ma eventualmente
        personalizzare tramite valueForKey.
        """
        attributes_dictionary = {}
        for key, value in self.__dict__.items():
            if key.startswith("_"):
                continue
            else:
                attributes_dictionary[key] = self.valueForKey(key, value)

        return attributes_dictionary
