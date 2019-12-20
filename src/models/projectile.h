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
#include "../inheritables/collidable.h"
#include "../inheritables/explodable.h"
#include "entity.h"

namespace model
{

class Projectile : public Entity , public inheritable::Collidable, public inheritable::Explodable
{

public:
    explicit Projectile(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double damage, size_t pierce, util::Color color, std::string texture);

    void update(core::World& world) override;

    [[nodiscard]] inheritable::CollideData getCollideData() const noexcept override;

    [[nodiscard]] inheritable::ExplodeData getExplodeData() const noexcept override;

    void collide(inheritable::CollisionData data) noexcept override;

    void bounce(inheritable::BounceBox box, inheritable::Wall wall) noexcept override;

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