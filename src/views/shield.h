//============================================================================
// @name        : shield.h
// @author      : Thomas Dooms
// @date        : 12/14/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/shield.h"
#include "../util/manager.h"
#include "../util/transform.h"
#include "abstract.h"

namespace view {
class Shield final : public view::Abstract {
public:
  explicit Shield(std::shared_ptr<model::Shield> model)
      : Abstract(std::move(model)) {
    receive(Event::valueChanged);
    receive(Event::textureChanged);
  }

  void receive(Event event) override {
    auto &model = dynamic_cast<model::Shield &>(*this->model);

    if (event == Event::valueChanged) {
      const auto dimensions =
          util::Transform::get().scale(model.getDimensions());
      const auto position =
          util::Transform::get().transform(model.getPosition());
      const auto color = util::Color::toSfColor(model.getColor());

      shape.setPosition(position);
      shape.setOrigin(dimensions);
      shape.setSize(dimensions * 2.0f);
      shape.setFillColor(color);
    } else if (event == Event::textureChanged) {
      shape.setTexture(util::SfManager::getTexture(model.getTexture()).get());
    }
  }

  void draw(sf::RenderWindow &window) const override { window.draw(shape); }

private:
  sf::RectangleShape shape;
};
} // namespace view