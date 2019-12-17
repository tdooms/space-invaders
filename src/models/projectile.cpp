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

namespace model
{

Projectile::Projectile(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double damage, size_t pierce, util::Color color, std::string texture)
        : Entity(type, side), pos(pos), vel(vel), dim(dim), damage(damage), pierce(pierce + 1), color(color), texture(std::move(texture)) {}

void Projectile::update([[maybe_unused]] core::World& world)
{
    pos += vel;
    send(Event::valueChanged);
}

[[nodiscard]] CollidableData Projectile::getCollidableData() const noexcept
{
    CollidableData data;
    data.position = pos;
    data.velocity = vel;
    data.dimensions = dim;
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
        pierce--;
    }
    if(pierce == 0)
    {
        removeData = RemoveData(0, Flags::particles, pos, dim, vel, 5);
    }
}

void Projectile::bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept
{
    removeData = RemoveData(0);
}

Vec2d Projectile::getDimensions() const noexcept
{
    return dim;
}

Vec2d Projectile::getPosition() const noexcept
{
    return pos;
}

std::string Projectile::getTexture() const noexcept
{
    return texture;
}

util::Color Projectile::getColor() const noexcept
{
    return color;
}

}