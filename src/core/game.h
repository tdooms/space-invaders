//============================================================================
// @name        : game.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "world.h"

namespace core {
enum WorldType : size_t { begin, main, end };

class Game {
public:
  // The engine works on a fixed update system, where each update is 'frameTime'
  // seconds of time. Because of this, there can be a situation where there is,
  // for instance, a fixed update of 16ms, but 20ms of actual time has passed.
  // To ensure all time is accounted for, all passed time is stored in
  // unprocessedTime, and then the engine processes as much time as it can. Any
  // unaccounted time can then be processed later, since it will remain stored
  // in unprocessedTime.

  // Game engine design ideas stolen from https://github.com/BennyQBD/CGFX5
  int start();

private:
  // these functions are to separate the main loop from the game logic itself
  void setup();
  void update(Stage stage);

  std::array<World, 3> worlds;
  WorldType current = begin;

  size_t id = 0;
  size_t level = 0;
};

} // namespace core