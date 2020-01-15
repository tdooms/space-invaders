//============================================================================
// @name        : particles.cpp
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../external/random.hpp"
#include "../util/color.h"
#include "../util/vec.h"

#include "object.h"

namespace inheritable {
struct ExplodeData;
}

namespace model {
// contains all the data for a particle
struct Particle {
  Particle(Vec2d pos, Vec2d vel, util::Color color, double radius)
      : pos(pos), vel(vel), color(color), radius(radius) {}

  Vec2d pos;
  Vec2d vel;
  util::Color color;
  double radius;
};

class Particles : public Object {
public:
  explicit Particles(const inheritable::ExplodeData &data);

  void update(core::World &world) override;

  [[nodiscard]] const std::vector<Particle> &getParticles() const noexcept;

private:
  std::vector<Particle> particles;

  size_t frames = 100;
};
} // namespace model