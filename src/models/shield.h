//============================================================================
// @name        : shield.h
// @author      : Thomas Dooms
// @date        : 12/14/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../collision/collidable.h"

namespace model
{
    class Shield : public Entity, public Collidable
    {
    public:
        Shield(Type type, Side side, Vec2d position, Vec2d dimensions, double lives, std::string texture) : Entity(type, side), position(position), dimensions(dimensions), lives(lives), texture(std::move(texture)) {}

        [[nodiscard]] CollidableData getCollidableData() const noexcept override
        {
            CollidableData data;
            data.position = position;
            data.velocity = Vec2d();
            data.dimensions = dimensions;
            data.rotation = 0;
            data.damage = 0;
            data.mass = std::numeric_limits<double>::infinity();
            data.type = type;
            data.side = side;

            return data;
        }

        void update([[maybe_unused]] core::World& world) override {}

        void collide([[maybe_unused]] CollisionData data) noexcept override
        {
            lives -= data.second.damage;
            if(lives <= 0) removeData = RemoveData(0, Flags::particles, position, dimensions, Vec2d(0,0), 20);
        }

        void bounce([[maybe_unused]] BounceBox box, [[maybe_unused]] Wall wall) noexcept override {}

        [[nodiscard]] Vec2d getPosition() const noexcept
        {
            return position;
        }

        [[nodiscard]] Vec2d getDimensions() const noexcept
        {
            return dimensions;
        }

        [[nodiscard]] std::string getTexture() const noexcept
        {
            return texture;
        }

    private:
        Vec2d position;
        Vec2d dimensions;
        double lives;
        std::string texture;
    };

}