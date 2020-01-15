//============================================================================
// @name        : projectile.cpp
// @author      : Thomas Dooms
// @date        : 12/14/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "projectile.h"

#include "../core/game.h"

namespace model {
using namespace inheritable;

Projectile::Projectile(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim,
                       double damage, size_t pierce, util::Color color,
                       std::string texture)
    : Entity(type, side), pos(pos), vel(vel), dim(dim), damage(damage),
      pierce(pierce + 1), color(color), texture(std::move(texture)) {}

void Projectile::update([[maybe_unused]] core::World &world) {
  setWorld(world);
  pos += vel;
  send(Event::valueChanged);
}

[[nodiscard]] CollideData Projectile::getCollideData() const noexcept {
  return CollideData(pos, vel, dim, 0, damage, 1, type, side);
}

ExplodeData Projectile::getExplodeData() const noexcept {
  return ExplodeData(pos, vel, dim, getColor(), 10, 0.0, 0.02);
}

void Projectile::collide(CollisionData data) noexcept {
  if (side != data.second.side) {
    pierce--;
  }
  if (pierce == 0) {
    explode();
    reaction = Reaction::remove;
  }
}

void Projectile::bounce([[maybe_unused]] BounceBox box,
                        [[maybe_unused]] Wall wall) noexcept {
  reaction = Reaction ::remove;
}

Vec2d Projectile::getDimensions() const noexcept { return dim; }

Vec2d Projectile::getPosition() const noexcept { return pos; }

std::string Projectile::getTexture() const noexcept { return texture; }

util::Color Projectile::getColor() const noexcept { return color; }

} // namespace model