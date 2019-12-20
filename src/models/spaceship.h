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
#include "../util/color.h"

#include "../inheritables/collidable.h"
#include "../inheritables/explodable.h"
#include "entity.h"

namespace model
{

    struct BulletData
    {
        std::string texture;
        util::Color color;

        std::chrono::milliseconds cooldownTime;
        double speed;
        Vec2d dim;
        double damage;
        size_t pierce;

        double shootAngle;
        double spreadAngle;
        size_t numBullets;
    };

    class Spaceship : public Entity , public inheritable::Collidable, public inheritable::Explodable
    {
    public:
        explicit Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double lives, util::Color startColor, util::Color deathColor, std::string texture, BulletData info);

        void update(core::World& world) override;

        [[nodiscard]] inheritable::CollideData getCollideData() const noexcept override;

        [[nodiscard]] inheritable::ExplodeData getExplodeData() const noexcept override;

        void collide(inheritable::CollisionData data) noexcept override;

        void bounce(inheritable::BounceBox box, inheritable::Wall wall) noexcept override;

        void accelerate(Vec2d acceleration) noexcept;

        void shoot() noexcept;

        [[nodiscard]] Vec2d getDimensions() const noexcept;

        [[nodiscard]] Vec2d getPosition() const noexcept;

        [[nodiscard]] Vec2d getVelocity() const noexcept;

        [[nodiscard]] double getLives() const noexcept;

        [[nodiscard]] double getMaxLives() const noexcept;

        [[nodiscard]] const util::Cooldown& getCooldown() const noexcept;

        [[nodiscard]] std::chrono::milliseconds getCooldownDuration() const noexcept;

        [[nodiscard]] std::string getTexture() const noexcept;

        [[nodiscard]] util::Color getColor() const noexcept;

    private:
        Vec2d pos;
        Vec2d vel;
        Vec2d dim;

        double lives;
        double maxLives;

        util::Color startColor;
        util::Color deathColor;
        std::string tex;

        bool shouldShoot = false;
        BulletData bulletInfo;
        util::Cooldown shootCooldown;
    };
}