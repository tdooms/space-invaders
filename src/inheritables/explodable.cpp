//============================================================================
// @name        : collidable.cpp
// @author      : Thomas Dooms
// @date        : 12/26/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "../core/world.h"
#include "../core/objects.h"

#include "explodable.h"

namespace inheritable
{
    void Explodable::setWorld(core::World& w)
    {
        world = &w;
    }
    void Explodable::explode()
    {
        // we add the explosion particles to the world
        if(world == nullptr) return;
        world->addObject<objects::Particles>(std::tuple(getExplodeData()));
    }
}
