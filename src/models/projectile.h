//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================


#pragma once

#include "abstract.h"
#include "../collision/collidable.h"

namespace model
{

class Projectile : public Entity , public Collidable
{

public:
    explicit Projectile(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double damage, size_t pierce, util::Color color, std::string texture);

    void update([[maybe_unused]] core::World& world) override;

    [[nodiscard]] CollidableData getCollidableData() const noexcept override;

    void collide([[maybe_unused]] CollisionData data) noexcept override;

    void bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept override;

    [[nodiscard]] Vec2d getDimensions() const noexcept;

    [[nodiscard]] Vec2d getPosition() const noexcept;

    [[nodiscard]] std::string getTexture() const noexcept;

    [[nodiscard]] util::Color getColor() const noexcept;

private:
    Vec2d pos;
    Vec2d vel;
    Vec2d dim;

    double damage;
    size_t pierce;

    util::Color color;
    std::string texture;
};

}