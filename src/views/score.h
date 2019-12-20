//============================================================================
// @name        : score.h
// @author      : Thomas Dooms
// @date        : 12/20/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/Text.hpp>
#include "abstract.h"
#include "../util/transform.h"
#include "../managers/manager.h"
#include "../models/text.h"

namespace view
{
    class Score final : public view::Abstract
    {
    public:
        explicit Score(std::shared_ptr<model::Score> model) : Abstract(std::move(model)), text()
        {
            text.setFont(*SfManager::getFont("LemonMilk.otf"));
            receive(Event::valueChanged);
        }

        void receive(Event type) override
        {
            if(type != Event::valueChanged) return;

            auto& model = dynamic_cast<model::Score&>(*this->model);
            text.setString(model.getString());
            text.setFillColor(sf::Color::White);
            text.setPosition(util::Transform::get().transform(model.getPosition()));
            text.setCharacterSize(model.getFontSize());
            text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
        }

        void draw(sf::RenderWindow& window) const override
        {
            window.draw(text);
        }

    private:
        sf::Text text;
    };
}