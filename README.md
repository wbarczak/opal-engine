# Opal Engine  
This is heavily a work in progress  
Our goal is a raycasting engine with easily swappable backends that allows for making a multitude of raycasted games ranging from shooters to rpg's, and allows online play  

The goal is to provide an editor that has:  
- custom tiles/entities  
- interactables *(levers, doors etc.)* and devices
- modifying player attributes  
- custom effects *(fire, poison, etc.)*  
- scripting hooks *(for tiles, entities, interactibles etc.)* in lua  
- level creation tool  

All would be stored in json/lua files and shipped along with an engine exe  

# Todo soon
- resolving colisions of entities vs world  
- spliting world into client and server versions  
- creating a simple editor for levels
- wrapping raylib's input so it's backend agnostic

# Style guides
This list is not extensive and probably will grow with time  
**vid** hyperlinks are meant to provide a better explanation for certain points  
- for type names and enumerators use **PascalCase**  
- for function/method/variable names use **camelCase**  
- prefix global consts with k_ like `k_WindowName`  
- prefix private member variables with m_ like `m_Length`  
- never abbreviate unless the abbreviation is **very** obvious like `Vec2` is a 2d Vector  
- don't use one letter variable names unless the variable is an iterator, a mathematical variable or disposable [vid](https://m.youtube.com/watch?v=-J3wNP6u5YU)  
- use variable names to explain how code works instead of comments [vid](https://m.youtube.com/watch?v=Bf7vDBBOBUA)  
- don't nest to heavily [vid](https://m.youtube.com/watch?v=CFRhGnuXG-4)  