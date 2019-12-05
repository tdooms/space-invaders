//============================================================================
// @name        : enemy.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/spaceship.h"
#include "../views/player.h"

namespace controller
{
    enum class Direction {left, right};

    class Enemy : public controller::Abstract
    {
    public:
        Enemy(std::shared_ptr<model::Spaceship> model, std::shared_ptr<view::Enemy> view, double speed = 2, size_t movetime = 3)
            : Abstract(std::move(model), std::move(view)), speed(speed), movetime(movetime) {}

        void update() override
        {
            auto& model = dynamic_cast<model::Spaceship&>(*this->model);

            if(cooldown.neverStarted())
            {
                model.accelerate(sf::Vector2f(2, 0));
                direction = Direction ::right;
                cooldown.start(seconds(movetime));
            }

            if(cooldown.done())
            {
                if(direction == Direction::left)
                {
                    model.accelerate(sf::Vector2f(4, 0));
                    direction = Direction::right;
                }
                else if(direction == Direction::right)
                {
                    model.accelerate(sf::Vector2f(-4, 0));
                    direction = Direction::left;
                }
                else throw std::runtime_error("unknown direction");
                cooldown.start(3s);
            }
        }

    private:
        util::Cooldown cooldown;
        Direction direction;

        double speed;
        std::chrono::seconds movetime;
    };

}