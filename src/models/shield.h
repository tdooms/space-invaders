//============================================================================
// @name        : shield.h
// @author      : Thomas Dooms
// @date        : 12/14/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../inheritables/collidable.h"
#include "../inheritables/explodable.h"
#include "entity.h"

namespace model
{
    class Shield : public Entity, public inheritable::Collidable, public inheritable::Explodable
    {
    public:
        Shield(Type type, Side side, Vec2d pos, Vec2d dim, double lives, util::Color color, std::string texture);

        [[nodiscard]] inheritable::CollideData getCollideData() const noexcept override;

        [[nodiscard]] inheritable::ExplodeData getExplodeData() const noexcept override;

        void update([[maybe_unused]] core::World& world) override;

        void collide([[maybe_unused]] inheritable::CollisionData data) noexcept override;

        void bounce([[maybe_unused]] inheritable::BounceBox box, [[maybe_unused]] inheritable::Wall wall) noexcept override;

        [[nodiscard]] Vec2d getPosition() const noexcept;

        [[nodiscard]] Vec2d getDimensions() const noexcept;

        [[nodiscard]] std::string getTexture() const noexcept;

        [[nodiscard]] util::Color getColor() const noexcept;

    private:
        Vec2d pos;
        Vec2d dim;

        double lives;

        util::Color color;
        std::string texture;
    };

}