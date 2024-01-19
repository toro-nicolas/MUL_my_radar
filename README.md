# my_radar - TORO Nicolas - PGE 2028

### Project goal
In this project, you are asked to render a 2D visualization panel showing a simulation of air traffic (AT).
The air traffic is a complex system with very strict rules to manage a large number of aircrafts.
For this first version of the simulation, you have to consider 2 types of entity:    
- aircrafts
- control towers

### Maps
##### Legend of the maps
All values must be numbers to be loaded in the program.    
Values can be float but values can't be negative.    
Position X must be between 0 and 1920.    
Position Y must be between 0 and 1080.    
Radius must be between 0 and 100.    

Towers :
```
T  {position_x} {position_y}  {radius}
```

Planes : 
```
A  {start_position_x} {start_position_y}  {end_position_z} {end_direction_x}  {speed}  {delay}    
```

##### How to use map generator ?
map_generator.py - The official Epitech map generator    
map_generator_2.py - My own map generator -> Generates planes and towers at random position    
map_generator_3.py - My own map generator -> Generates towers and planes with positions based on tower positions    

map_generator_2.py :
```Shell
usage: map_generator_v2.py [-h] -p Planes -t Tower -pa Path
exemple: python map_generator_v2.py -p 1000 -t 10 -pa maps/0.radar
```

map_generator_3.py :
```Shell
usage: map_generator_v3.py [-h] -p Planes -t Tower -d Delay -pa Path
exemple: python map_generator_v3.py -p 1000 -t 10 -d 60 -pa maps/0.radar
```

Please use -h or --help for see help and options

##### Maps that I created
I've created a number of test maps that you can download [here](https://epitechfr-my.sharepoint.com/:f:/g/personal/nicolas_toro_epitech_eu/EiH9p1iCvOhGidkpgsBDlJ4B1krW4UO2WqlWYQtWl89lTQ?e=BSqczp).    
1 - PDF example    
2 - 0min with 30000 planes and 0 towers    
3 - Basic test 1min with 1000 and 10 towers    
4 - 2h with 1000000 and 20 towers    
5 - 1h with 500000 and 20 towers    
6 - 6min with 100000 and 50 towers    
7 - 0min with 100000 and 5 towers    
8 - 1min with 100000 and 5 towers    
9 - 0min with 1000 and 100 towers    
10 - 0min with 10000 and 1 big towers

### Project objective
##### Basics rules
- [x] Aircrafts fly from given places to other ones.
- [x] Aircrafts appear on the simulation panel when they take off.
- [x] Aircrafts disappear from the simulation panel when they land on.
- [x] Aircrafts move in a straight line at given constant speeds.
- [x] Aircrafts colliding with another one is destroyed and disappear from the simulation panel.
- [x] Control areas allow aircrafts to collide with each other without being destroyed and they can continue on their way.
- [x] Control towers don’t move and have control areas on the map.
- [x] Control towers appear on the simulation panel at launch.

##### Must conditions
- [x] The program must take exactly one parameter.
- [x] The program must accept any file path as argument.
- [x] It corresponds to the file containing the script for the simulation containing characters and integers.
- [x] The program must displayed an error message if the script is not found or incorrect.
- [x] Your window must be 1920x1080 pixels.
- [x] The window must be closed using events.
- [x] The program must display aircrafts’ hitbox and control towers’ areas.
- [x] The program must manage as many displayed entities as possible.
- [x] Aircrafts must have 20x20 square shaped hitboxes.
- [x] Aircrafts’ hitbox and sprite must be axis-aligned.
- [x] Control towers must have circled shaped control areas.

##### Should conditions

- [x] The program should display and update a timer in seconds at the top-right corner of the window.
- [x] The program should stop once all aircrafts have landed on or have been destroyed.
- [x] Aircrafts should be able to take off after a given delay.
- [x] Aircrafts and control towers should be displayed using sprites.
- [x] The program should accept the “-h” option, then display the usage.
- [x] The program should be able to switch visibility of hitboxes and areas by pressing the key ‘L’.
- [x] The program should be able to switch visibility of entities’ sprites by pressing the key ‘S’.
- [x] Possible user interactions should be explicitly displayed in the usage.

##### Could conditions
- [ ] Aircrafts’ hitbox and size could be in a 3D space.
- [x] Aircrafts could cross any side of a screen and appear on the opposite one.
- [ ] Aircrafts’ hitbox and sprite could rotate depending on the aircrafts’ direction.
- [ ] Aircrafts’ hitbox could follow the sprite boundary.
- [X] Aircrafts’ hitbox could have different sizes.
- [x] Control towers’ areas could cross any side of the screen and affect the opposite one.
- [x] The program could manage floating numbers coming from the script.
