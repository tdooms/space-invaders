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

namespace model
{
    class Projectile : public model::Abstract
    {
    public:
        explicit Projectile(sf::Vector2f pos = {}, sf::Vector2f vel = {}) : pos(pos), vel(vel) {}

        void update([[maybe_unused]] core::Game& game) override
        {
            pos += vel;
            send(Type::valueChanged);
        }

        [[nodiscard]] sf::Vector2f position() const noexcept
        {
            return pos;
        }

    private:
        sf::Vector2f pos;
        sf::Vector2f vel;
    };
}