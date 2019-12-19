//============================================================================
// @name        : color.h
// @author      : Thomas Dooms
// @date        : 12/17/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/Color.hpp>
#include <tuple>
#include "../parsers/json.h"

namespace util
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        static Color lerp(Color lhs, Color rhs, double a)
        {
            uint8_t r = lhs.r * a + rhs.r * (1.0 - a);
            uint8_t g = lhs.g * a + rhs.g * (1.0 - a);
            uint8_t b = lhs.b * a + rhs.b * (1.0 - a);
            return {r, g, b};
        }

        static sf::Color toSfColor(Color color) noexcept
        {
            return sf::Color(color.r, color.g, color.b);
        }

        static Color fromJson(const nlohmann::json& json)
        {
            return {json[0], json[1], json[2]};
        }
    };


}