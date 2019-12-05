//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/System/Vector2.hpp>
#include "abstract.h"

#include "../core/game.h"
#include "../util/cooldown.h"

namespace model
{
    class Spaceship : public model::Abstract
    {
    public:
        explicit Spaceship(sf::Vector2f pos = {}, sf::Vector2f vel = {}) : pos(pos), vel(vel) {}

        void update(core::Game& game) override
        {
            if(shouldShoot and shootCooldown.done())
            {
                game.addObject<core::projectile>(std::tuple(pos, vel + sf::Vector2f(0, -4)));
                shootCooldown.start(100ms);
            }
            shouldShoot = false;

            pos += vel;
            send(Type::valueChanged);
        }

        [[nodiscard]] sf::Vector2f position() const noexcept
        {
            return pos;
        }

        void accelerate(sf::Vector2f acceleration) noexcept
        {
            vel += acceleration;
        }
        void shoot() noexcept
        {
            shouldShoot = true;
        }

    private:
        sf::Vector2f pos;
        sf::Vector2f vel;

        bool shouldShoot = false;
        util::Cooldown shootCooldown;
    };
}