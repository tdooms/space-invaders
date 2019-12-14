//============================================================================
// @name        : collision.h
// @author      : Thomas Dooms
// @date        : 12/5/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "collidable.h"
#include <set>

//if(std::abs(lhs.position.x - rhs.position.x) < lhs.dimensions.x + rhs.dimensions.x and
//        std::abs(lhs.position.y - rhs.position.y) < lhs.dimensions.y + rhs.dimensions.y)
//{
//  return lerp(lhs.position, rhs.position, 0.5);
//}
//else
//{
//  return std::nullopt;
//}

namespace collision
{
    static std::optional<Vec2d> collideCircles(CollidableData lhs, CollidableData rhs)
    {
        const auto collide = dist(lhs.position, rhs.position) < (lhs.dimensions + rhs.dimensions).length();

        if(collide) return lerp(lhs.position, rhs.position, 0.5);
        else return std::nullopt;
    }

    static std::optional<Vec2d> collideRects(CollidableData lhs, CollidableData rhs)
    {
        if(std::abs(lhs.position.x - rhs.position.x) < lhs.dimensions.x + rhs.dimensions.x and
           std::abs(lhs.position.y - rhs.position.y) < lhs.dimensions.y + rhs.dimensions.y)
        {
          return lerp(lhs.position, rhs.position, 0.5);
        }
        else
        {
          return std::nullopt;
        }
    }

    // we need to detect every object first before acting on it.
    // if objects a and b, collide and objects b, c also.
    // if we remove a and b, and we remove them, c wouldn't be removed, which it should be.
    static void detect(std::shared_ptr<model::World>& world)
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

        for(const auto& [id, collidable] : collidables)
        {
            const auto data = collidable->getCollidableData();

            if(data.position.x + data.dimensions.x > 4)
            {
                collidable->bounce(box, Wall::right);
            }
            else if(data.position.x - data.dimensions.x < -4)
            {
                collidable->bounce(box, Wall::left);
            }

            if(data.position.y + data.dimensions.y > 3)
            {
                collidable->bounce(box, Wall::bottom);
            }
            else if(data.position.y - data.dimensions.y < -3)
            {
                collidable->bounce(box, Wall::top);
            }
        }

        for(size_t i = 0; i < collidables.size(); i++)
        {
            auto data0 = collidables[i].second->getCollidableData();

            for(size_t j = i + 1; j < collidables.size(); j++)
            {
                const auto data1 = collidables[j].second->getCollidableData();

                const auto res = collideRects(data0, data1);
                if(not res.has_value()) continue;

                toResolve.emplace_back(i, std::make_pair(res.value(), data1));
                toResolve.emplace_back(j, std::make_pair(res.value(), data0));
            }
        }


        for(const auto& [index, data] : toResolve)
        {
            collidables[index].second->collide(data);
        }
    }
}