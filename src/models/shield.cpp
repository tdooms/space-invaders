//============================================================================
// @name        : shield.cpp
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "shield.h"

namespace model
{
using namespace inheritable;

    Shield::Shield(Type type, Side side, Vec2d pos, Vec2d dim, double lives, util::Color color, std::string texture) :
        Entity(type, side), pos(pos), dim(dim), lives(lives), color(color), texture(std::move(texture)) {}

CollideData Shield::getCollideData() const noexcept
{
    CollideData data;
    data.pos = pos;
    data.vel = Vec2d();
    data.dim = dim;
    data.rotation = 0;
    data.damage = 0;
    data.mass = std::numeric_limits<double>::infinity();
    data.type = type;
    data.side = side;

    return data;
}

ExplodeData Shield::getExplodeData() const noexcept
{
    ExplodeData data;
    data.pos = pos;
    data.vel = Vec2d();
    data.dim = dim;

    data.color = util::White;
    data.num = 20;

    data.minSize = 0.0;
    data.maxSize = 0.3;

    return data;
}

void Shield::update([[maybe_unused]] core::World& world)
{
    setWorld(world);
}

void Shield::collide([[maybe_unused]] CollisionData data) noexcept
{
    lives -= data.second.damage;
    if(lives <= 0)
    {
        explode();
        reaction = Reaction::remove;
    }
}

void Shield::bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept
{
}

[[nodiscard]] Vec2d Shield::getPosition() const noexcept
{
    return pos;
}

[[nodiscard]] Vec2d Shield::getDimensions() const noexcept
{
    return dim;
}

[[nodiscard]] std::string Shield::getTexture() const noexcept
{
    return texture;
}

[[nodiscard]] util::Color Shield::getColor() const noexcept
{
    return color;
}

}

