//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"

#include "../util/cooldown.h"
#include "../collision/collidable.h"

namespace model
{
    class Spaceship : public model::Abstract , public Collidable
    {
    public:
        explicit Spaceship(Entity::Type type, Vec2d pos, Vec2d vel, double radius, double lives, double shootAngle, std::chrono::milliseconds cooldownTime, std::string texture);

        void update(core::Game& game) override;

        [[nodiscard]] CollidableData getCollidableData() const noexcept override;

        void collide(CollisionData data) noexcept override;

        void bounce(BounceBox box, Wall wall) noexcept override;

        void accelerate(Vec2d acceleration) noexcept;

        void shoot() noexcept;

        [[nodiscard]] double getRadius() const noexcept;

        [[nodiscard]] Vec2d getPosition() const noexcept;

        [[nodiscard]] Vec2d getVelocity() const noexcept;

        [[nodiscard]] double getLives() const noexcept;

        [[nodiscard]] std::string getTexture() const noexcept;

    private:
        Entity::Type type;
        Vec2d pos;
        Vec2d vel;
        double radius;
        double lives;
        double shootAngle;
        std::chrono::milliseconds cooldownTime;
        std::string tex;

        bool shouldShoot = false;
        util::Cooldown shootCooldown;
    };
}