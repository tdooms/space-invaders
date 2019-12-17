//============================================================================
// @name        : game.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../controllers/abstract.h"
#include "../controllers/world.h"
#include "entities.h"
#include "objects.h"
#include "world.h"

using namespace std::chrono_literals;

namespace core
{

class Game
{
public:
    // The engine works on a fixed update system, where each update is 'frameTime' seconds of time.
    // Because of this, there can be a situation where there is, for instance, a fixed update of 16ms,
    // but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
    // stored in unprocessedTime, and then the engine processes as much time as it can. Any
    // unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
    void startGame();

private:
    World world;
//    World start;

    bool gameOver = false;
    bool gameOverAdded = false;
};


}