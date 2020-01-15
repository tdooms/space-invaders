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

namespace inheritables {
struct CollideData;
}

namespace model {
class World;
}

namespace collision {
// simple collision detection for rectangles
std::optional<Vec2d> collideRects(const inheritables::CollideData &lhs,
                                  const inheritables::CollideData &rhs);

// we need to detect every object first before acting on it.
// if objects a and b, collide and objects b, c also.
// if we remove a and b, and we remove them, c wouldn't be removed, which it
// should be.
void detect(std::shared_ptr<model::World> &world);
} // namespace collision