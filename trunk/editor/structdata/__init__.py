"""Package in cui sono inserite tutte le classi necessarie per i dati.
   Le classi base per rappresentare i dati sono:
   - Room
   - Area
   - Event
   - Image
   - Item
   - ItemRequest
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
