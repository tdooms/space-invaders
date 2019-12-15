//============================================================================
// @name        : transform.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/System/Vector2.hpp>
#include "vec.h"

namespace util
{
    class Transform
    {
    public:
        // get singleton
        [[nodiscard]] static Transform& get() noexcept
        {
            static Transform instance;
            return instance;
        }

        [[nodiscard]] sf::Vector2f transform(Vec2d coordinates) const noexcept
        {
            return sf::Vector2f((coordinates.x + 4) * screenSize.x / 8.0, (coordinates.y + 3) * screenSize.y / 6.0);
        }
        [[nodiscard]] sf::Vector2f scale(Vec2d coordinates) const noexcept
        {
            return sf::Vector2f(coordinates.x * screenSize.x / 8.0, coordinates.y * screenSize.y / 6.0);
        }
        [[nodiscard]] double scale(double coordinate) const noexcept
        {
            return coordinate * screenSize.x / 8.0;
        }

        [[nodiscard]] sf::Vector2u getScreenSize() const noexcept
        {
            return sf::Vector2u(screenSize.x, screenSize.y);
        }

        // delete unnecessary operators/constructors
        Transform(const Transform&) = delete;
        void operator=(const Transform&) = delete;
        Transform(Transform&&) = delete;
        void operator=(Transform&&) = delete;

    private:
        Transform() = default;
        Vec2d screenSize = {800, 600};
    };
}

