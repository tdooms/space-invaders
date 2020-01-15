//============================================================================
// @name        : Abstract.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/abstract.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace view {
class Abstract : public Observer {
public:
  explicit Abstract(std::shared_ptr<model::Abstract> model)
      : model(std::move(model)) {}
  ~Abstract() override = default;

  virtual void draw(sf::RenderWindow &window) const = 0;
  void receive([[maybe_unused]] Event event) override = 0;

protected:
  std::shared_ptr<model::Abstract> model;
};
} // namespace view