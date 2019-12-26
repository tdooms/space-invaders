# Space invaders
**Made by:** Thomas Dooms s0181389
## File structure overview
Most folders in **res** are quite self explanatory. If you add a new level file in the folder, it will automatically play it after the last one, (it does need to be of the form level`x`.json though). When a new file is added (or unhidden) in the player folder, it automatically adds it as a choice (try removing the `.` from `.cheat.json`) .

The **src** has a little more, like the models.views and controllers and some more interesting folders.

- **core folder:** most files that are tied to the game are in this folder, like **entities** and **game** itself.
- **inheritables folder:** for the lack of a better name, this contains **explodable** and **collidable**.
- **util folder:** contains **vec2d**, **Stopwatch**, and other useful classes.
- **parsers folder:** contains the nlohmann json file and my parsing logic.

Almost every constant or variable can be read in from files. this way it is easy to change/balance and add new enemies/features.

## Design choices
I chose to implement the MVC pattern using the observer pattern. Every model is subject with (maybe) multiple views observing it, when a model changes it can send events to the views `send(Event::valueChanged);`. 

I split the notion of *GameObject* into 2 concepts:
An **Entity** is a meta-class, describing of which model/view/controller it uses and extra info.
An **Object** is almost the same, but has less info and is used for static things such as text.

Collision and physics are widely used in space invaders, to make this system as flexible as possible I used an abstract class with 2 functions **getCollideData()** and **collide()**, the former asks the object the data needed for collision detection such as position, velocity. Once we detect there is a collision we call the **collide()** function, where the object itself can handle how it handles the collision. 

A simplified implementation of **Spaceship.collide()** is: 

    if(other.side == side) bounce(); 
    else lives -= other.damage; 
    
    if(lives <= 0) explode();


if a **Collidable** object is added to a world it is automatically checked for collision.

**Explodables** are used for the particles effects and are almost the same as collidables, but use **getExplodeData()**. Furthermore **explode()** is defined in the abstract class itself.

## Architecture
A **World** is a collection of entities and/or objects with some helper functions like from **addEntity()**. A world has an **update()** and a **draw()** function, to enable separation of logic and frame rate. A world also has a **stage** to inform the caller of **update()** how it should respond if needed.

The 'highest level' class is **Game** class. Which is a collection of worlds and handles how they should work. 
- **start()** is public and contains the main game loop and logic, this is called to start the game.
- **setup()** is called in **start()** before the game loop, here the user can write how their game should be set up.
- **update()** handles how the game should run and how the world work together.

These last two functions are the only hard-coded game logic, here is a part of the update logic.

     if(stage == Stage::defeat)  
     {  
	   current = WorldType::end;  
	   parser::loadAndAddLeaderBoard("res/data/leaderboard.json", worlds[current], score);  
     }
	

## Extending the game
The main theme of the project was to make it as extensible as possible. I achieved this goal using templates and lots of abstraction. I will give some examples of how to extend the game in some ways.

**adding local multiplayer** only requires 3 simple changes:
- adding a new controller to allow other keys to be used for the other player.
- adding a new entity **entities::player2** with the new controller.
- you will need to add another world to game where player 2 can choose their ship.

**adding power ups** is also quite easy:
- Make enemies drop a power up when they die, this could be done by extending **Explodable**.
- Write a model, view and controller for a power up.
- add a new **model::Type**, to distinguish a power up from other types.
- add an if statement in **Spaceship.collide()** that handles what happens when it takes a power up.
