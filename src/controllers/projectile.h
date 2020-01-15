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

#include "../models/projectile.h"
#include "../views/projectile.h"
#include "abstract.h"

namespace controller {
class Projectile : public controller::Abstract {
public:
  Projectile(std::shared_ptr<model::Projectile> model,
             std::shared_ptr<view::Projectile> view)
      : Abstract(std::move(model), std::move(view)) {}

  void update() override {}
};

} // namespace controller