"""Package in cui sono inserite tutte le classi necessarie per i dati.
   Le classi base per rappresentare i dati sono:
   - Room
   - Area
   - Event
   - Image
   - Item
   - ItemRequirement
   - Param
   - Var
   - VarRequirement
   Ogni classe rappresenta un tag necessario per rappresentare l'informazione.
   Nella classe Origin si ha la funzione dictionary che ritorna un dizionario 
   le cui coppie (chiave, valore) sono rispettivamente gli attributi i valori
   di ogni tag. In ogni classe si ha una variabile di classe che da il nome 
   del tag che la classe rappresenta.
   Le informazioni di tutto il progetto sono contenute nella classe Project. 
   Importando il modulo project.py si puo' utilizzare la variabile globale
   g_project che contiene tutte le informazioni
   g_project e' un singleton che punta sempre al progetto corrente e esiste
   sempre un solo progetto corrente
   E' possibile utilizzare un dizionario chiamato class_tag in cui tutti gli
   elementi sono le classi del progetto. In particolare la coppia chiave valore
   del dizionario e' data da (tag_name_classe, classe)
   E' possibile importare le singole classi del progetto direttamente da
   struct data
"""

class_tag = {}

__all__ = [class_tag, "Room", "Area", "Action", "Image", "Item",
           "ItemRequirement", "Param", "Var", "VarRequirement", "World",
           "Step", "Dialog", "Link", "g_project"]

from origin import OriginData
from action import Action
from area import Area
from event import Event
from image import Image
from item import Item
from itemRequirement import ItemRequirement
from param import Param
from room import Room
from var import Var
from varRequirement import VarRequirement
from world import World
from dialog import Dialog
from link import Link
from step import Step
from project import g_project
from inspect import isclass

for key, cls in globals().items():
    if isclass(cls) and issubclass(cls, OriginData) and cls != OriginData:
        class_tag[cls.tag_name] = cls
