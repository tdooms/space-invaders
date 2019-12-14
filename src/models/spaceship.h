//============================================================================
// @name        : spaceship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once


#include "../util/cooldown.h"
#include "../managers/collidable.h"

#include "entity.h"

namespace model
{
    struct BulletInfo
    {
        std::string texture;
        std::chrono::milliseconds cooldownTime;
        double speed;
        double size;
        double damage;

        double shootAngle;
        double spreadAngle;
        size_t numBullets;
    };

    class Spaceship : public Entity , public Collidable
    {
    public:
        explicit Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, double radius, double lives, std::string texture, BulletInfo info);

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
        Vec2d pos;
        Vec2d vel;
        double radius;
        double lives;
        std::string tex;

        bool shouldShoot = false;
        BulletInfo bulletInfo;
        util::Cooldown shootCooldown;
    };
}