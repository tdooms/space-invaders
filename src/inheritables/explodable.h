//============================================================================
// @name        : explodable.h
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../util/color.h"
#include "../util/vec.h"

namespace inheritable {
struct ExplodeData {
  ExplodeData(Vec2d pos, Vec2d vel, Vec2d dim, util::Color color, size_t num,
              double minSize, double maxSize)
      : pos(pos), vel(vel), dim(dim), color(color), num(num), minSize(minSize),
        maxSize(maxSize) {}

  Vec2d pos;
  Vec2d vel;
  Vec2d dim;

  util::Color color;
  size_t num;

  double minSize;
  double maxSize;
};

class Explodable {
public:
  Explodable() = default;
  virtual ~Explodable() = default;

  [[nodiscard]] virtual ExplodeData getExplodeData() const noexcept = 0;

  void setWorld(core::World &w);
  void explode();

private:
  // the only use of a raw pointer, this is not unique nor shared
  // c++20's std::observer_ptr would do the trick but alas we can't use it.
  core::World *world = nullptr;
};
} // namespace inheritable