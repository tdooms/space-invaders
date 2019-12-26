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
#include "../util/vec.h"

namespace model
{
// this is the model for the score widget you can see
class Score : public Object
{
public:
    explicit Score(Vec2d position, size_t fontSize);

    void update([[maybe_unused]] core::World& world) override;

    [[nodiscard]] const std::string& getString() noexcept;

    [[nodiscard]] Vec2d getPosition() noexcept;

    [[nodiscard]] size_t getFontSize() noexcept;

private:
    std::string string;
    Vec2d position;
    size_t fontSize;
};
}