//============================================================================
// @name        : spaceship.cpp
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "spaceship.h"

#include <utility>
#include "../core/game.h"
#include "../core/entities.h"

namespace model
{

using namespace inheritable;

Spaceship::Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, Vec2d dim, double speed, double lives, util::Color color, std::string texture, BulletData bulletInfo) :
Entity(type, side), pos(pos), vel(vel), dim(dim), speed(speed), lives(lives), maxLives(lives), color(color), tex(std::move(texture)), bulletInfo(std::move(bulletInfo)) {}

void Spaceship::update(core::World& world)
{
    if(shouldShoot and shootCooldown.done())
    {
        double angle = bulletInfo.shootAngle;
        if(bulletInfo.numBullets != 1) angle -= bulletInfo.spreadAngle;

        for(size_t i = 0; i < bulletInfo.numBullets; i++)
        {
            const auto startPos = pos + Vec2d::fromPolar(dim.y + bulletInfo.dim.y, angle);
            const auto startVel = Vec2d::fromPolar(bulletInfo.speed, angle);
            auto&& args = std::tuple(startPos, startVel, bulletInfo.dim, bulletInfo.damage, bulletInfo.pierce, bulletInfo.color, bulletInfo.texture);

            if(side == Side::player) world.addEntity<entities::PlayerProjectile>(std::move(args));
            else if(side == Side::enemy) world.addEntity<entities::EnemyProjectile>(std::move(args));

            angle += (2.0 * bulletInfo.spreadAngle) / (bulletInfo.numBullets - 1.0);
        }

        shootCooldown.start(bulletInfo.cooldownTime);
    }

    setWorld(world);
    shouldShoot = false;
    pos += vel;
    send(Event::valueChanged);
}

CollideData Spaceship::getCollideData() const noexcept
{
    return CollideData(pos, vel, dim, 0.0, 1.0, 1.0, type, side);
}

ExplodeData Spaceship::getExplodeData() const noexcept
{
    const auto num = (side == Side::player) ? 200 : 50;
    return ExplodeData(pos, vel, dim, getColor(), num, 0.0, 0.03);
}

void Spaceship::collide(CollisionData data) noexcept
{
    auto& other = data.second;
    if(side == other.side)
    {
        if(other.type == Type::spaceship)
        {
            vel.x = other.vel.x;
            if(pos.x > other.pos.x)
            {
                pos.x = other.pos.x + other.dim.x + dim.x;
            }
            else
            {
                pos.x = other.pos.x - (other.dim.x + dim.x);
            }
        }
    }
    else if(side != other.side)
    {
        if(lives - other.damage < 0) explode();
        if(side == Side::player and other.damage > 0) explode();
        lives -= other.damage;
    }

    if(lives <= 0)
    {
        if(side == Side::player)
        {
            reaction = Reaction::defeat;
        }
        else
        {
            reaction = Reaction::remove;
            scoreChange += 10;
        }
    }
}

void Spaceship::bounce(BounceBox box, Wall wall) noexcept
{
    if(side == Side::player)
    {
        switch(wall)
        {
            case Wall::right:
                pos.x = box.right - dim.x;
                vel.x *= -1;
                break;

            case Wall::left:
                pos.x = box.left + dim.x;
                vel.x *= -1;
                break;

            case Wall::top:
                pos.y = box.top + dim.y;
                vel.y *= -1;
                break;

            case Wall::bottom:
                pos.y = box.bottom - dim.y;
                vel.y *= -1;
                break;
        }
    }
    else if(side == Side::enemy)
    {
        switch(wall)
        {
            case Wall::right:
                pos.x = box.right - dim.x;
                vel.x *= -1;
                break;

            case Wall::left:
                pos.x = box.left + dim.x;
                vel.x *= -1;
                break;

            case Wall::top:
                pos.y = box.top + dim.y;
                vel.y *= -1;
                break;

            case Wall::bottom:
                reaction = Reaction::defeat;
                break;
        }
    }
}

void Spaceship::accelerate(Vec2d acceleration) noexcept
{
    vel += acceleration;
}

void Spaceship::right() noexcept
{
    vel.x += speed;
}

void Spaceship::left() noexcept
{
    vel.x -= speed;
}

void Spaceship::shoot() noexcept
{
    shouldShoot = true;
}

[[nodiscard]] Vec2d Spaceship::getDimensions() const noexcept
{
    return dim;
}

[[nodiscard]] Vec2d Spaceship::getPosition() const noexcept
{
    return pos;
}

[[nodiscard]] Vec2d Spaceship::getVelocity() const noexcept
{
    return vel;
}

[[nodiscard]] double Spaceship::getLives() const noexcept
{
    return lives;
}

[[nodiscard]] double Spaceship::getMaxLives() const noexcept
{
    return maxLives;
}

[[nodiscard]] const util::Cooldown& Spaceship::getCooldown() const noexcept
{
    return shootCooldown;
}

[[nodiscard]] std::chrono::milliseconds Spaceship::getCooldownDuration() const noexcept
{
    return bulletInfo.cooldownTime;
}

[[nodiscard]] std::string Spaceship::getTexture() const noexcept
{
    return tex;
}

[[nodiscard]] util::Color Spaceship::getColor() const noexcept
{
    return util::Color::lerp(util::Black, color, lives / maxLives);
}
}