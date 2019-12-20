//============================================================================
// @name        : score.cpp
// @author      : Thomas Dooms
// @date        : 12/20/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "score.h"
#include "../core/world.h"

namespace model
{
    Score::Score(Vec2d position, size_t fontSize) : string("0"), position(position), fontSize(fontSize) {}

    void Score::update([[maybe_unused]] core::World& world)
    {
        string = std::to_string(world.getScore());
        send(Event::valueChanged);
    }

    [[nodiscard]] const std::string& Score::getString() noexcept
    {
        return string;
    }

    [[nodiscard]] Vec2d Score::getPosition() noexcept
    {
        return position;
    }

    [[nodiscard]] size_t Score::getFontSize() noexcept
    {
        return fontSize;
    }
}