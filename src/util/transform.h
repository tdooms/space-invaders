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

        [[nodiscard]] sf::Vector2u transform(sf::Vector2f coordinates) const noexcept
        {
            return coordinates *= screenSize;
        }

        [[nodiscard]] sf::Vector2u getScreenSize() const noexcept
        {
            return screenSize;
        }

        Transform() noexcept = default;

        // delete unnecessary operators/constructors
        Transform(const Transform&) = delete;
        void operator=(const Transform&) = delete;
        Transform(Transform&&) = delete;
        void operator=(Transform&&) = delete;

    private:
        sf::Vector2u screenSize = {800, 600};
    };
}

