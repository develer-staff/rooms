Flashback cutscene
### 1, "defaults.csd"

img: "1locanda", "./data/locanda.png", zoom, show, x:-1, y:0
img: "2locandiera", "./data/locandiera.png", p_out_left, show, width:0.25, height:0.45
txt: "3frase_giocatore", "Ho sentito un rumore in cantina", text_out
txt: "4frase_locandiera", "...ha ha ha...", text_out
---

-> "pan_bg", 5000
"1locanda": x:0, y:-0.5, width:1.5, height:1.5

-> "show_gamer_txt", 2000
"3frase_giocatore": text_in

-> "nothing", 2000, "show_gamer_txt"

-> "hide_gamer_txt", 500, "nothing"
"3frase_giocatore": text_out

-> "show_locandiera", 1000, "pan_bg"
"2locandiera": x:-0.05
"4frase_locandiera": text_in

-> "nothing2", 3000, "show_locandiera"

-> "end", 2000, "nothing2"
"1locanda": hide
"2locandiera": p_out_left, hide
"4frase_locandiera": text_out

