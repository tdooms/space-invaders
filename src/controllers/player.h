//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include "abstract.h"
#include "../models/spaceship.h"
#include "../views/player.h"

namespace controller
{
class Player : public controller::Abstract
{
public:
    Player(std::shared_ptr<model::Spaceship> model, std::shared_ptr<view::Player> view) : Abstract(std::move(model), std::move(view)) {}

    void update() override
    {
        auto& model = dynamic_cast<model::Spaceship&>(*this->model);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            model.accelerate(sf::Vector2f(-0.1, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            model.accelerate(sf::Vector2f(0.1, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            model.accelerate(sf::Vector2f(0, -0.1));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            model.accelerate(sf::Vector2f(0, 0.1));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            model.shoot();
        }
    }

};

}