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
#include "../collision/collidable.h"
#include "structs.h"
#include "entity.h"

namespace model
{
    class Spaceship : public Entity , public Collidable
    {
    public:
        explicit Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double lives, util::Color color, std::string texture, BulletInfo info);

        void update(core::World& world) override;

        [[nodiscard]] CollidableData getCollidableData() const noexcept override;

        void collide(CollisionData data) noexcept override;

        void bounce(BounceBox box, Wall wall) noexcept override;

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

        util::Color color;
        std::string tex;

        bool shouldShoot = false;
        BulletInfo bulletInfo;
        util::Cooldown shootCooldown;
    };
}