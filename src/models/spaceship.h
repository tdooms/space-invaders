//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../util/color.h"
#include "../util/cooldown.h"

#include "../inheritables/collidable.h"
#include "../inheritables/explodable.h"
#include "entity.h"

namespace model {
// contains all the data to initialize spaceship bullet stats
struct BulletData {
  std::string texture;
  util::Color color;

  std::chrono::milliseconds cooldownTime;
  double speed;
  Vec2d dim;
  double damage;
  size_t pierce;

  double shootAngle;
  double spreadAngle;
  size_t numBullets;
};

// the main model for the player and the enemies
class Spaceship : public Entity,
                  public inheritable::Collidable,
                  public inheritable::Explodable {
public:
  explicit Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim,
                     double speed, double lives, util::Color color,
                     std::string texture, BulletData info);

  void update(core::World &world) override;

  [[nodiscard]] inheritable::CollideData getCollideData() const
      noexcept override;

  [[nodiscard]] inheritable::ExplodeData getExplodeData() const
      noexcept override;

  void collide(inheritable::CollisionData data) noexcept override;

  void bounce(inheritable::BounceBox box,
              inheritable::Wall wall) noexcept override;

  void accelerate(Vec2d acceleration) noexcept;

  void right() noexcept;

  void left() noexcept;

  void shoot() noexcept;

  [[nodiscard]] Vec2d getDimensions() const noexcept;

  [[nodiscard]] Vec2d getPosition() const noexcept;

  [[nodiscard]] Vec2d getVelocity() const noexcept;

  [[nodiscard]] double getLives() const noexcept;

  [[nodiscard]] double getMaxLives() const noexcept;

  [[nodiscard]] const util::Cooldown &getCooldown() const noexcept;

  [[nodiscard]] std::chrono::milliseconds getCooldownDuration() const noexcept;

  [[nodiscard]] std::string getTexture() const noexcept;

  [[nodiscard]] util::Color getColor() const noexcept;

private:
  Vec2d pos;
  Vec2d vel;
  Vec2d dim;
  double speed;

  double lives;
  double maxLives;

  util::Color color;
  std::string tex;

  bool shouldShoot = false;
  BulletData bulletInfo;
  util::Cooldown shootCooldown;
};
} // namespace model