//============================================================================
// @name        : text.h
// @author      : Thomas Dooms
// @date        : 12/13/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../models/text.h"
#include "../util/manager.h"
#include "../util/transform.h"
#include "abstract.h"
#include <SFML/Graphics/Text.hpp>

namespace view {
class Text final : public view::Abstract {
public:
  explicit Text(const std::shared_ptr<model::Text>& model)
      : Abstract(model), text() {
    text.setFont(*util::SfManager::getFont("LemonMilk.otf"));
    receive(Event::valueChanged);
  }

  void receive(Event type) override {
    if (type != Event::valueChanged)
      return;

    auto &model = dynamic_cast<model::Text &>(*this->model);
    text.setString(model.getString());
    text.setFillColor(sf::Color::White);
    text.setPosition(util::Transform::get().transform(model.getPosition()));
    text.setCharacterSize(static_cast<unsigned int>(model.getFontSize()));
    text.setOrigin(text.getLocalBounds().width / 2.0f,
                   text.getLocalBounds().height / 2.0f);
  }

  void draw(sf::RenderWindow &window) const override { window.draw(text); }

private:
  sf::Text text;
};
} // namespace view