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
#include "../models/abstract.h"

namespace inheritable
{
    enum class Wall
    {
        right, left, bottom, top
    };

    struct BounceBox
    {
        BounceBox(double right, double left, double bottom, double top) :
        right(right), left(left), bottom(bottom), top(top) {}

        double right;
        double left;
        double bottom;
        double top;
    };

    // all the data the collision system needs
    struct CollideData
    {
        CollideData(Vec2d pos, Vec2d vel, Vec2d dim, double rotation, double damage, double mass, model::Type type, model::Side side)
        : pos(pos), vel(vel), dim(dim), rotation(rotation), damage(damage), mass(mass), type(type), side(side) {}

        Vec2d pos;
        Vec2d vel;
        Vec2d dim;

        double rotation;
        double damage;
        double mass;

        model::Type type;
        model::Side side;
    };

    // all the data a collision needs, impact and the data of the other object
    using CollisionData = std::pair<Vec2d, CollideData>;

    struct Collidable
    {
        Collidable() = default;
        virtual ~Collidable() = default;

        [[nodiscard]] virtual CollideData getCollideData() const noexcept = 0;
        virtual void collide(CollisionData data) noexcept = 0;
        virtual void bounce(BounceBox box, Wall wall) noexcept = 0;
    };
}
