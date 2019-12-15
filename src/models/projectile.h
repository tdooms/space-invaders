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
#include "../managers/collidable.h"

namespace model
{

class Projectile : public Entity , public Collidable
{

public:
    explicit Projectile(Type type, Side side, Vec2d pos, Vec2d vel, double radius, double damage, std::string texture);

    void update([[maybe_unused]] core::Game& game) override;

    [[nodiscard]] CollidableData getCollidableData() const noexcept override;

    void collide([[maybe_unused]] CollisionData data) noexcept override;

    void bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept override;

    [[nodiscard]] double getRadius() const noexcept;

    [[nodiscard]] Vec2d getPosition() const noexcept;

    [[nodiscard]] std::string getTexture() const noexcept;


private:
    Vec2d pos;
    Vec2d vel;
    double radius;
    double damage;
    std::string texture;
};

}