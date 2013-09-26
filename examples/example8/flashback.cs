Flashback cutscene
### 1, "defaults.csd"

img: "locanda", "data/locanda.png", s_doubled, visible, x:-1, y:0
img: "locandiera", "data/locandiera.png", p_out_left, visible, w:0.25, h:0.45
txt: "frase_giocatore", "Ho sentito un rumore in cantina", p_under, invisible,  w:1, h:0.2
txt: "frase_locandiera", "...ha ha ha...", p_out_left, invisible, w:1, h:0.2
---

-> "pan_bg", 5000
"locanda": x:0, y:0.5

-> "show_gamer_txt", 2000
"frase_giocatore": visible, x:0

-> "nothing", 1000, "show_gamer_txt"

-> "hide_gamer_txt", 500, "nothing"
"frase_giocatore": invisible

-> "show_locandiera", 1000, "pan_bg"
"locandiera": x:-0.05
"frase_locandiera": x:0, visible

-> "end", 2000, "show_locandiera"
"locanda": invisible
"locandiera": invisible
"frase_locandiera": invisible

