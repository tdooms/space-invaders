//============================================================================
// @name        : spaceship.cpp
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "spaceship.h"
#include "../core/game.h"
#include "../core/entities.h"


namespace model
{
Spaceship::Spaceship(Type type, Side side, Vec2d pos, Vec2d vel, double radius, double lives, std::string texture, BulletInfo bulletInfo) :
Entity(type, side), pos(pos), vel(vel), radius(radius), lives(lives), tex(std::move(texture)), bulletInfo(std::move(bulletInfo)) {}

void Spaceship::update(core::Game& game)
{
    if(shouldShoot and shootCooldown.done())
    {
        double angle = bulletInfo.shootAngle;
        if(bulletInfo.numBullets != 1) angle -= bulletInfo.spreadAngle;

        for(size_t i = 0; i < bulletInfo.numBullets; i++)
        {
            const auto startPos = pos + Vec2d::fromPolar(radius + bulletInfo.size, angle);
            const auto startVel = Vec2d::fromPolar(bulletInfo.speed, angle);
            auto args = std::tuple(startPos, startVel, bulletInfo.size, bulletInfo.damage, bulletInfo.texture);

            if(side == Side::player) game.addEntity<entities::PlayerProjectile>(std::move(args));
            else if(side == Side::enemy) game.addEntity<entities::EnemyProjectile>(std::move(args));

            angle += (2.0 * bulletInfo.spreadAngle) / (bulletInfo.numBullets - 1.0);
        }

        shootCooldown.start(bulletInfo.cooldownTime);
    }
    
    shouldShoot = false;
    pos += vel;
    send(Event::valueChanged);
}

CollidableData Spaceship::getCollidableData() const noexcept
{
    CollidableData data;
    data.position = pos;
    data.velocity = vel;
    data.dimensions = Vec2d(radius, radius);
    data.rotation = 0.0;
    data.damage = 1.0;
    data.mass = 1.0;
    data.type = type;
    data.side = side;

    return data;
}

void Spaceship::collide(CollisionData data) noexcept
{
    if(side == data.second.side)
    {
        if(data.second.type == Type::spaceship)
        {
            vel.x = data.second.velocity.x;
        }
    }
    else if(side != data.second.side)
    {
        lives -= data.second.damage;
    }

    if(lives <= 0)
    {
        const auto dim = Vec2d(radius, radius);
        if (side == Side::player) removeData = RemoveData(0, Flags::gameOver | Flags::particles, pos, dim, vel, 100);
        else removeData = RemoveData(10, Flags::particles, pos, dim, vel, 20);
    }
}

void Spaceship::bounce(struct BounceBox box, enum Wall wall) noexcept
{
    if(side == Side::player)
    {
        switch(wall)
        {
            case Wall::right:
                pos.x = box.right - radius;
                vel.x *= -1;
                break;

            case Wall::left:
                pos.x = box.left + radius;
                vel.x *= -1;
                break;

            case Wall::top:
                pos.y = box.top + radius;
                vel.y *= -1;
                break;

            case Wall::bottom:
                pos.y = box.bottom - radius;
                vel.y *= -1;
                break;
        }
    }
    else if(side == Side::enemy)
    {
        switch(wall)
        {
            case Wall::right:
                pos.x = box.right - radius;
                vel.x *= -1;
                break;

            case Wall::left:
                pos.x = box.left + radius;
                vel.x *= -1;
                break;

            case Wall::top:
                pos.y = box.top + radius;
                vel.y *= -1;
                break;

            case Wall::bottom:
                removeData = RemoveData(0, Flags::gameOver);
                break;
        }
    }
}

void Spaceship::accelerate(Vec2d acceleration) noexcept
{
    vel += acceleration;
}

void Spaceship::shoot() noexcept
{
    shouldShoot = true;
}

[[nodiscard]] double Spaceship::getRadius() const noexcept
{
    return radius;
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

[[nodiscard]] std::string Spaceship::getTexture() const noexcept
{
    return tex;
}
}