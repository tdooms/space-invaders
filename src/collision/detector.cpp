//============================================================================
// @name        : detector.cpp
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "detector.h"
#include "../inheritables/collidable.h"
#include "../models/world.h"
#include <set>

namespace collision
{
    using namespace inheritable;

    std::optional<Vec2d> collideRects(CollideData lhs, CollideData rhs)
    {
        if(std::abs(lhs.pos.x - rhs.pos.x) < lhs.dim.x + rhs.dim.x and
           std::abs(lhs.pos.y - rhs.pos.y) < lhs.dim.y + rhs.dim.y)
        {
            return lerp(lhs.pos, rhs.pos, 0.5);
        }
        else
        {
            return std::nullopt;
        }
    }


    void detect(std::shared_ptr<model::World>& world)
    {
        // id, and collidable
        std::vector<std::pair<size_t, Collidable*>> collidables;

        // id, index and the collision data
        std::vector<std::pair<size_t, CollisionData>> toResolve;

        for(const auto& [id, object] : *world)
        {
            const auto collidable = dynamic_cast<Collidable*>(object.get());
            if(collidable != nullptr) collidables.emplace_back(id, collidable);
        }

        const BounceBox box = {4, -4, 3, -3};

        // check if they bounced
        for(const auto& [id, collidable] : collidables)
        {
            const auto data = collidable->getCollideData();

            if(data.pos.x + data.dim.x > 4)
            {
                collidable->bounce(box, Wall::right);
            }
            else if(data.pos.x - data.dim.x < -4)
            {
                collidable->bounce(box, Wall::left);
            }

            if(data.pos.y + data.dim.y > 3)
            {
                collidable->bounce(box, Wall::bottom);
            }
            else if(data.pos.y - data.dim.y < -3)
            {
                collidable->bounce(box, Wall::top);
            }
        }

        // check if they collided
        for(size_t i = 0; i < collidables.size(); i++)
        {
            auto data0 = collidables[i].second->getCollideData();

            for(size_t j = i + 1; j < collidables.size(); j++)
            {
                const auto data1 = collidables[j].second->getCollideData();

                const auto res = collideRects(data0, data1);
                if(not res.has_value()) continue;

                toResolve.emplace_back(i, std::make_pair(res.value(), data1));
                toResolve.emplace_back(j, std::make_pair(res.value(), data0));
            }
        }

        // notify them they have collided
        for(const auto& [index, data] : toResolve)
        {
            collidables[index].second->collide(data);
        }
    }
}