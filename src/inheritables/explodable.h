//============================================================================
// @name        : explodable.h
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#pragma once

#include "../util/vec.h"
#include "../util/color.h"

namespace inheritable
{
    struct ExplodeData
    {
        Vec2d pos;
        Vec2d vel;
        Vec2d dim;

        util::Color color;
        size_t num;

        double minSize;
        double maxSize;
    };

    class Explodable
    {
    public:
        Explodable() = default;
        virtual ~Explodable() = default;

        virtual ExplodeData getExplodeData() const noexcept = 0;

        void setWorld(core::World& w);
        void explode();

    private:
        core::World* world = nullptr;
    };
}