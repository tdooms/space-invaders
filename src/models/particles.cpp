//============================================================================
// @name        : particles.cpp
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "particles.h"
#include "object.h"

#include "../external/random.hpp"
#include "../inheritables/explodable.h"

namespace model {
// a lot of random generation to make the particles, doesn't do anything else
// really
Particles::Particles(const inheritable::ExplodeData &data) {
  for (size_t i = 0; i < data.num; i++) {
    using Random = effolkronium::random_static;
    const auto randomX =
        Random::get(data.pos.x - data.dim.x, data.pos.x + data.dim.x);
    const auto randomY =
        Random::get(data.pos.y - data.dim.y, data.pos.y + data.dim.y);
    const auto randomVel = Random::get(0.0, 0.02);
    const auto randomRadius = Random::get(data.minSize, data.maxSize);
    const auto alpha = Random::get(200, 255);
    const auto color =
        util::Color::addAlpha(data.color, static_cast<uint8_t>(alpha));

    particles.emplace_back(Vec2d(randomX, randomY),
                           data.vel + (Vec2d::randomUnit() * randomVel), color,
                           randomRadius);
  }
}

void Particles::update([[maybe_unused]] core::World &world) {
  for (auto &particle : particles) {
    particle.pos += particle.vel;
    if (particle.color.a != 0)
      particle.color.a -= 1;
  }
  if (--frames == 0)
    reaction = Reaction::remove;

  send(Event::valueChanged);
}

[[nodiscard]] const std::vector<Particle> &Particles::getParticles() const
    noexcept {
  return particles;
}

} // namespace model