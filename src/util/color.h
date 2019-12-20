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
        Color() : r(0), g(0), b(0) {}
        Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        uint8_t r;
        uint8_t g;
        uint8_t b;

        static Color lerp(Color lhs, Color rhs, double a)
        {
            if(a > 1) a = 1;
            else if(a < 0) a = 0;

            uint8_t r = lhs.r + a * (rhs.r - lhs.r);
            uint8_t g = lhs.g + a * (rhs.g - lhs.g);
            uint8_t b = lhs.b + a * (rhs.b - lhs.b);
            return Color(r, g, b);
        }

        static sf::Color toSfColor(Color color) noexcept
        {
            return sf::Color(color.r, color.g, color.b);
        }

        static Color fromJson(const nlohmann::json& json)
        {
            return Color(json[0], json[1], json[2]);
        }


    };
    static inline Color White = Color(255, 255, 255);
    static inline Color Black = Color(0, 0, 0);

}