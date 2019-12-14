//============================================================================
// @name        : collidable.h
// @author      : Thomas Dooms
// @date        : 12/5/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../util/vec.h"

namespace Entity { enum Type : size_t; }

// all the data the collision system needs
struct CollidableData
{
    Vec2d position;
    Vec2d velocity;
    Vec2d dimensions;
    double rotation;
    double damage;
    double mass;
    Entity::Type type;
};

enum class Wall
{
    right, left, bottom, top
};

struct BounceBox
{
    double right;
    double left;
    double bottom;
    double top;
};

// all the data a collision needs, impact and the data of the other object
using CollisionData = std::pair<Vec2d, CollidableData>;


struct Collidable
{
    Collidable() = default;
    virtual ~Collidable() = default;

    [[nodiscard]] virtual CollidableData getCollidableData() const noexcept = 0;
    virtual void collide(CollisionData data) noexcept = 0;
    virtual void bounce(BounceBox box, Wall wall) noexcept = 0;
};