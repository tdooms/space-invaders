### Thomas Dooms s0181389

# space invaders

## design choices
### mvc / observer
I chose to implement the mvc pattern with the observer pattern. Every model is subject with (maybe) multiple views observing it, when a model changes it can send events to the views `send(Event::valueChanged);`. 

### entities
I split the notion of *GameObject* into 2 concepts

An **Entity** is more of a meta-class, describing of which model/view/controller it uses.
An  **Object** is almost the same, but this only has a model and a view and is used for static objects such as text.

### collidables
collision and physics are widely used in space invaders, to make this system as flexible as possible I used an abstract class with 2 functions **getCollidableData()** and **collide()**, the former asks the object the data needed for collision detection such as position, velocity. Once we detect there is a collision we call the **collide()** function, where the object itself can handle how it handles the collision. A simplified implementation of **Spaceship.collide()** is: `if(other.type == type){ bounce(); } else { lives -= damage; }`

### architecture
Every thing starts with the **Game** object, this class contains all the functions and data for the game to run. Three of these are the **view::World**, **model::World** and **controller::World**, these represent the data of the game and are updated in the main game loop.

### example
The **manager::Level** reads in the data for a level from a json file and adds it to the game. If it wants to add an enemy it can simply do `game.addEntity<Entity::Enemy>(modelArgs, viewArgs, controllerArgs);` Where `modelArgs` is a tuple of which arguments the model needs.

The game then handles the rest. It makes each model/view and controller and adds it to the world.

## extending the game
the main theme of the project was to make it as extensible as possible. I achieved this goal using templates and lots of abstraction. I will give some examples of how to extend the game in some ways.

### adding multiplayer
This only requires 3 simple changes:
- adding a new controller to allow other keys to be used for the other player.
- adding a new entity **Entity::player2** with the new controller.
- **manager::Player** will need to be called twice in **Game** to construct 2 players instead of one.

### power ups
This is also quite easy:
- Make enemies drop a power up when they die, this is done by calling `game.addEntity`.
- Write a model and view (as controller you can probably use **controller::Empty**)
- add a new **model::Type**, to distinguish a power up from other types.
- add an if statement in **Spaceship.collide()** that handles what happens when it takes a power up.
