#!/usr/bin/env python

class Subject(object):


    def __init__(self):
        self._observers = []

    def subscribe(self, observer):
        self._observers.append(observer)

    def unsubscribe(self, observer):
        self._observers.remove(observer)


    def notify(self):
        for observer in self._observers:
            observer.updateData()
