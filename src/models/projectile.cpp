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
#include "../core/entities.h"

namespace model
{

Projectile::Projectile(Type type, Side side, Vec2d pos, Vec2d vel, double radius, double damage, std::string texture)
        : Entity(type, side), pos(pos), vel(vel), radius(radius), damage(damage), texture(std::move(texture)) {}

void Projectile::update([[maybe_unused]] core::Game &game)
{
    pos +=
    vel;
    send(Event::valueChanged);
}

[[nodiscard]] CollidableData Projectile::getCollidableData() const noexcept
{
    CollidableData data;
    data.position = pos;
    data.velocity = vel;
    data.dimensions = Vec2d(radius, radius);
    data.rotation = 0;
    data.damage = damage;
    data.mass = 1;
    data.type = type;
    data.side = side;

    return data;
}

void Projectile::collide([[maybe_unused]] CollisionData data) noexcept
{
    if(side != data.second.side)
    {
        removeData = RemoveData(0, Flags::particles, pos, vel, Vec2d(radius, radius), 10);
    }
}

void Projectile::bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept
{
    removeData = RemoveData(0);
}

[[nodiscard]] double Projectile::getRadius() const noexcept
{
    return radius;
}

[[nodiscard]] Vec2d Projectile::getPosition() const noexcept
{
    return pos;
}

std::string Projectile::getTexture() const noexcept
{
    return texture;
}

}