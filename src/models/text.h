//============================================================================
// @name        : text.h
// @author      : Thomas Dooms
// @date        : 12/13/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <string>
#include "object.h"

namespace model
{
class Text : public Object
{
public:
    explicit Text(std::string string, Vec2d position, size_t fontSize) : string(std::move(string)), position(position), fontSize(fontSize) {}

    void update([[maybe_unused]] core::Game& game) override {}

    [[nodiscard]] const std::string& getString() noexcept { return string; }

    [[nodiscard]] Vec2d getPosition() noexcept { return position; }

    [[nodiscard]] size_t getFontSize() noexcept { return fontSize; }

private:
    std::string string;
    Vec2d position;
    size_t fontSize;
};
}