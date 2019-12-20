//============================================================================
// @name        : explodable.h
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../core/world.h"
#include "../core/objects.h"

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

        void setWorld(core::World& w)
        {
            world = &w;
        }
        void explode()
        {
            if(world == nullptr) return;
            world->addObject<objects::Particles>(std::tuple(getExplodeData()));
        }

    private:
        core::World* world = nullptr;
    };
}