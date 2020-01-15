//============================================================================
// @name        : start.h
// @author      : Thomas Dooms
// @date        : 12/18/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/selection.h"
#include "../util/cooldown.h"
#include "../views/selection.h"
#include "abstract.h"

namespace controller {
class Selection : public controller::Abstract {
public:
  Selection(const std::shared_ptr<model::Selection> &model,
            const std::shared_ptr<view::Selection> &view)
      : Abstract(model, view) {}

  void update() override {
    using namespace std::literals::chrono_literals;

    auto &model = dynamic_cast<model::Selection &>(*this->model);
    const auto num = model.getNum();
    const auto curr = model.getChoice();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      model.confirm();
    }

    if (not cooldown.done())
      return;

    // set a small cooldown every time a key was pressed to prevent multiple
    // presses
    if (curr != 0 and sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      cooldown.start(200ms);
      model.choose(curr - 1);
    } else if (curr != num - 1 and
               sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      cooldown.start(200ms);
      model.choose(curr + 1);
    }
  }

private:
  util::Cooldown cooldown;
};

} // namespace controller