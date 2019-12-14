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
Spaceship::Spaceship(Entity::Type type, Vec2d pos, Vec2d vel, double radius, double lives, double shootAngle, std::chrono::milliseconds cooldownTime, std::string texture) :
type(type), pos(pos), vel(vel), radius(radius), lives(lives), shootAngle(shootAngle), cooldownTime(cooldownTime), tex(std::move(texture)) {}

void Spaceship::update(core::Game& game)
{
    if(shouldShoot and shootCooldown.done())
    {
        game.addEntity<Entity::Projectile>(std::tuple(pos + Vec2d(0, -0.41), vel + Vec2d(0, -0.04), 0.07));
        shootCooldown.start(cooldownTime);
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

    return data;
}

void Spaceship::collide(CollisionData data) noexcept
{
    if(data.second.type == type)
    {
        vel.x = data.second.velocity.x;
    }
    else
    {
        lives -= data.second.damage;
        if(lives <= 0)
        {
            if (type == Entity::Type::player) removeData = RemoveData(true, 0);
            else removeData = RemoveData(false, 10);
        }
    }
}

void Spaceship::bounce(struct BounceBox box, enum Wall wall) noexcept
{
    if(type == Entity::Type::player)
    {
        switch(wall)
        {
            case Wall::right:
                pos.x = pos.x - 8 + 2 * radius;
                break;

            case Wall::left:
                pos.x = pos.x + 8 - 2 * radius;
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
    else
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
                removeData = RemoveData(true, 0);
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