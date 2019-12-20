//============================================================================
// @name        : collision.h
// @author      : Thomas Dooms
// @date        : 12/5/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../util/vec.h"
#include <memory>
#include <optional>

namespace inheritables { struct CollideData; }

namespace model { class World; }

namespace collision
{
    std::optional<Vec2d> collideRects(inheritables::CollideData lhs, inheritables::CollideData rhs);

    void detect(std::shared_ptr<model::World>& world);
}