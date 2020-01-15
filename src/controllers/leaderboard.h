//============================================================================
// @name        : leaderboard.h
// @author      : Thomas Dooms
// @date        : 12/20/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/leaderboard.h"
#include "../views/leaderboard.h"
#include "abstract.h"

namespace controller {
class Leaderboard : public controller::Abstract {
public:
  Leaderboard(std::shared_ptr<model::Leaderboard> model,
              std::shared_ptr<view::Leaderboard> view)
      : Abstract(std::move(model), std::move(view)) {}

  void update() override {
    using namespace std::literals::chrono_literals;

    auto &model = dynamic_cast<model::Leaderboard &>(*this->model);
    if (not model.getShowName())
      return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      model.complete();
    }

    if (not cooldown.done())
      return;

    // set a small cooldown every time a key was pressed to prevent multiple
    // presses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      cooldown.start(200ms);
      model.nextChar();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      cooldown.start(200ms);
      model.prevChar();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      cooldown.start(200ms);
      model.appendChar();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
      cooldown.start(200ms);
      model.popChar();
    }
  }

private:
  util::Cooldown cooldown;
};
} // namespace controller