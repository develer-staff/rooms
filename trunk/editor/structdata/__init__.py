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
"""

class_tag = {}

__all__ = [class_tag]

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

class_tag['room'] = Room
class_tag['action'] = Action
class_tag['area'] = Area
class_tag['event'] = Event
class_tag['image'] = Image
class_tag['item'] = Item
class_tag['item_req'] = ItemRequirement
class_tag['param'] = Param
class_tag['var'] = Var
class_tag['var_req'] = VarRequirement
class_tag['world'] = World

#for cls in globals():
#    print cls
#    if inspect.isclass(cls) and issubclass(cls, OriginData) and cls != OriginData:
#        class_tag[cls.tag_name] = cls
