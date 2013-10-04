Flashback cutscene
### 1, "defaults.csd"

img: "locanda", "./data/locanda.png", zoom, show, x:-1, y:0
img: "locandiera", "./data/locandiera.png", p_out_left, show, width:0.25, height:0.45
txt: "frase_giocatore", "Ho sentito un rumore in cantina", text_out
txt: "frase_locandiera", "...ha ha ha...", text_out
---

-> "pan_bg", 5000
"locanda": x:0, y:-0.5, width:1.5, height:1.5

-> "show_gamer_txt", 2000
"frase_giocatore": text_in

-> "nothing", 2000, "show_gamer_txt"

-> "hide_gamer_txt", 500, "nothing"
"frase_giocatore": text_out

-> "show_locandiera", 1000, "pan_bg"
"locandiera": x:-0.05
"frase_locandiera": text_in

-> "nothing2", 3000, "show_locandiera"

-> "end", 2000, "nothing2"
"locanda": hide
"locandiera": p_out_left, hide
"frase_locandiera": text_out

