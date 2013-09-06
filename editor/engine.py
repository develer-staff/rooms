#!/usr/bin/env python

import os
from shutil import rmtree
from os import mkdir
from subprocess import Popen
from os.path import split
from shutil import copy
import tempfile


from utils import g_ptransform
from savefilerooms import saveFileRooms
from structdata import g_project


def startEngine(engine):
    """
    funzione per far partire l'engine sul progetto che si sta editando
    prende in ingresso un 
    """
    if engine is not None and engine.poll() is None:
        engine.kill()
        engine = None

    path = tempfile.NamedTemporaryFile(suffix=".rooms",
                                       prefix="world", dir="temp/")
    saveFileRooms("temp/world.rooms")
    getRoomsImage()
    engine = Popen(["../../engine/qt5-frontend/engine.exe"], cwd="temp/")
    return engine

def getRoomsImage():
    """
    funzione per recuperare tutte le immagini. Le immagini vengono
    messe nella cartella temp/path_dell'immagine
    """
    for image in g_project.data['images'].keys():
        image_path = g_ptransform.relativeToAbsolute(image)
        directory = os.path.join("temp/", split(image)[0])
        directory += "/"
        if not os.path.exists(directory):
            os.makedirs(directory)
        copy(image_path, directory)
