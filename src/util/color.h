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

namespace util
{
    struct Color
    {
        std::tuple<uint8_t, uint8_t, uint8_t> data;

        static sf::Color toSfColor(Color color) noexcept
        {
            return sf::Color(std::get<0>(color.data), std::get<1>(color.data), std::get<2>(color.data));
        }
    };


}