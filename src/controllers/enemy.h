//============================================================================
// @name        : enemy.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/spaceship.h"
#include "../views/spaceship.h"
#include "abstract.h"

#include <random.hpp>

namespace controller {
class Enemy : public controller::Abstract {
public:
  Enemy(std::shared_ptr<model::Spaceship> model,
        std::shared_ptr<view::Spaceship> view)
      : Abstract(std::move(model), std::move(view)) {}

  void update() override {
    auto &model = dynamic_cast<model::Spaceship &>(*this->model);

    // apply a random start offset
    if (neverStarted) {
      using Random = effolkronium::random_static;
      const auto temp = model.getCooldownDuration().count();
      const auto time = Random::get(0l, temp);
      cooldown.start(std::chrono::milliseconds(time));
      neverStarted = false;
    }

    // always try to shoot
    if (cooldown.done()) {
      model.shoot();
    }
  }

private:
  util::Cooldown cooldown;
  bool neverStarted = true;
};

} // namespace controller