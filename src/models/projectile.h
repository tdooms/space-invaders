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
class Projectile : public model::Abstract , public Collidable
{

public:
    explicit Projectile(Entity::Type type, Vec2d pos, Vec2d vel, double radius) : type(type), pos(pos), vel(vel), radius(radius) {}

    void update([[maybe_unused]] core::Game& game) override
    {
        pos += vel;
        send(Event::valueChanged);
    }

    [[nodiscard]] CollidableData getCollidableData() const noexcept override
    {
        CollidableData data;
        data.position = pos;
        data.velocity = vel;
        data.dimensions = Vec2d(radius, radius);
        data.rotation = 0;
        data.damage = 10;

        return data;
    }

    void collide([[maybe_unused]] CollisionData data) noexcept override
    {
        removeData = RemoveData(false, 0);
    }

    void bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept override
    {
        removeData = RemoveData(false, 0);
    }

    [[nodiscard]] double getRadius() const noexcept
    {
        return radius;
    }

    [[nodiscard]] Vec2d getPosition() const noexcept
    {
        return pos;
    }


private:
    Entity::Type type;
    Vec2d pos;
    Vec2d vel;
    double radius;
};

}