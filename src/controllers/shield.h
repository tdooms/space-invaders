//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include <memory>

#include "../models/shield.h"
#include "../views/shield.h"
#include "abstract.h"

namespace controller {
class Shield : public controller::Abstract {
public:
  Shield(std::shared_ptr<model::Shield> model,
         std::shared_ptr<view::Shield> view)
      : Abstract(std::move(model), std::move(view)) {}

  void update() override {}
};

} // namespace controller