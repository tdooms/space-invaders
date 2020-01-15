//============================================================================
// @name        : shield.cpp
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "shield.h"

namespace model {
using namespace inheritable;

Shield::Shield(Type type, Side side, Vec2d pos, Vec2d dim, double lives,
               util::Color color, std::string texture)
    : Entity(type, side), pos(pos), dim(dim), lives(lives), maxLives(lives),
      color(color), texture(std::move(texture)) {}

CollideData Shield::getCollideData() const noexcept {
  const auto inf = std::numeric_limits<double>::infinity();
  return CollideData(pos, Vec2d(), dim, 0, 0, inf, type, side);
}

ExplodeData Shield::getExplodeData() const noexcept {
  return ExplodeData(pos, Vec2d(), dim, util::White, 20, 0.0, 0.05);
}

void Shield::update([[maybe_unused]] core::World &world) { setWorld(world); }

void Shield::collide([[maybe_unused]] CollisionData data) noexcept {
  if (lives - data.second.damage <= 0) {
    explode();
    reaction = Reaction::remove;
  }
  lives -= data.second.damage;
  send(Event::valueChanged);
}

void Shield::bounce([[maybe_unused]] BounceBox box,
                    [[maybe_unused]] Wall wall) noexcept {}

[[nodiscard]] Vec2d Shield::getPosition() const noexcept { return pos; }

[[nodiscard]] Vec2d Shield::getDimensions() const noexcept { return dim; }

[[nodiscard]] std::string Shield::getTexture() const noexcept {
  return texture;
}

[[nodiscard]] util::Color Shield::getColor() const noexcept {
  return util::Color::lerp(util::Black, color, lives / maxLives);
}

} // namespace model
