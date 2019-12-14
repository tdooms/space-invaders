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
#include "../views/spaceship.h"

namespace controller
{
class Player : public controller::Abstract
{
public:
    Player(std::shared_ptr<model::Spaceship> model, std::shared_ptr<view::Spaceship> view) : Abstract(std::move(model), std::move(view)) {}

    void update() override
    {
        auto& model = dynamic_cast<model::Spaceship&>(*this->model);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            model.accelerate(Vec2d(-0.001, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            model.accelerate(Vec2d(0.001, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            model.accelerate(Vec2d(0, -0.001));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            model.accelerate(Vec2d(0, 0.001));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            model.shoot();
        }
    }

};

}