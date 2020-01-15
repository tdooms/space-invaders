//============================================================================
// @name        : observer.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "events.h"

// doesn't do much but has the ability to receive events
class Observer {
public:
  Observer() = default;
  virtual ~Observer() = default;

  virtual void receive(Event type) = 0;
};