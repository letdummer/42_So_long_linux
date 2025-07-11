<h1 align="center"> so_long.c </h1>

<p align="center">wow, a game!  ✨ 🎮 ✨ </p>

<p align="center">
<img alt="so_long" src="https://github.com/letdummer/42_So_long_linux/blob/main/preview/so_long_record.gif">
<h5 align="center"> This project is in constant development. </h3>  


**Next steps:** 
- Implement enemy and death system
- Victory/loss image displayed directly in the graphics window

## Index
* [How to play](#how-to-play)
* [Requirements](#requirements)
    * [Map Rules](#map_rules)
    * [Map Composition](#map_composition)
* [Graphic Management](#graphic_management)

<h2 align="center" id="how-to-play"> How to play? </h2>

- LINUX
```sh
    git clone https://github.com/letdummer/42_So_long_linux.git
```

- MACOS
```sh
  git clone https://github.com/letdummer/42_So_long_macos.git
```

**Compile and run:**
```sh
  make &&  ./so_long ./maps/valid/map1.ber
```

<h2 align="center" id="requirements"> Requirements </h2>
<h3 id="map_rules" align="left"> Map Rules </h3> 

- Only *.ber* file
- Must be surrounded by walls
- Must be rectangular and the path must be valid
- At least one collectible, one exit, one starting position.

<h3 id="map_composition" align="left"> Map Composition </h3> 

**The map can be composed of only these 5 characters:**
- 0 for an empty space,
- 1 for a wall,
- C for a collectible,
- E for a map exit,
- P for the player’s starting position.


<h3 id="graphic_management" align="left"> Graphic Management </h3> 

- Pressing ESC must close the window and quit the program
- Clicking on the cross on the window’s frame must close the window and quit the
program
- At every move, the current number of movements must be displayed in the shell

<h2 align="center"> Assets Credits to Starmixu and Utaskuas ✨💖🐰✨</h2>

<a href="https://starmixu.itch.io/little-dreamyland-asset-pack?download" target="_blank" > Little Dreamyland </a> </p>
