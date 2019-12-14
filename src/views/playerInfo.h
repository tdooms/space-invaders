//============================================================================
// @name        : playerInfo.h
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/Text.hpp>
#include "abstract.h"

#include "../models/spaceship.h"
#include "../managers/manager.h"

namespace view
{
class PlayerInfo : public view::Abstract
{
public:
    explicit PlayerInfo(std::shared_ptr<model::Abstract> model) : Abstract(std::move(model)), text()
    {
        text.setFont(*SfManager::getFont("LemonMilk.otf"));
    }

    void receive(Event type) override
    {
        if(type != Event::valueChanged) return;
        auto& model = dynamic_cast<model::Spaceship&>(*this->model);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << model.getLives();

        text.setString("lives: "+ stream.str());
        text.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) const override
    {
        window.draw(text);
    }

private:
    sf::Text text;
};
}