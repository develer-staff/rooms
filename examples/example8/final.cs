### 1, "final.csd"

sfondo_gioco: "./data/stanza_centrale.png", fullscreen, show
sfondo_fine: "./data/end.png", fullscreen, hide
nero: "./cs/nero.jpeg", fullscreen, hide
landscape1: "./cs/l1.jpeg", left_screen, hide
landscape2: "./cs/l2.jpeg", right_screen, hide
landscape3: "./cs/l3.jpeg", left_screen, hide
landscape4: "./cs/l4.jpeg", right_screen, hide
office1: "./cs/i1.jpeg", fullscreen, hide
office2: "./cs/i2.jpeg", fullscreen, hide
molo1: "./cs/d1.jpeg", fullscreen, hide
molo2: "./cs/d2.jpeg", x:0, y:0, width:1.2, height:1, hide

player: "./cs/p1.png", player_initial_position, hide, width:0.25, height:0.45
player_pistola: "./cs/p2.png", x:-0.1, y:0.3, hide, width:0.25, height:0.45

player_text1: "pronto, qui l'omino dell'ufficio", text_out
player_text2: "Che cosa??", text_out
---

-> comparsa
2000
sfondo_gioco: hide
nero: show
2000
landscape1: show
2000
landscape2: show
2000
landscape1: hide
2000
landscape3: show
2000
landscape2: hide
landscape4: show
2000
2000
landscape3: hide
landscape4: hide
office1: show
1000
player: show
1000
player_text1: text_in

-> ufficio, comparsa
1000
office1: hide
office2: show
1000
500
player_text1: text_out
player: hide
0
player: width:0.5, height:0.9, x:0.5, y:0.3
1000
player_text2: text_in
player: show
5000
1000
player_text2: text_out
1000
office2: hide
player: hide

-> molo, ufficio
2000
2000
molo1: show
2000
molo1:hide
1000
molo2: show
player_pistola: show
4000
molo2: x:-0.2
player_pistola: x:0
500
1000
molo2: hide
player_pistola: hide

-> fine, molo
1000
nero: hide
sfondo_fine: show
