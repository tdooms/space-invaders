//============================================================================
// @name        : structs.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <chrono>
#include "../util/color.h"

namespace model
{
    struct BulletInfo
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

    enum Flags
    {
        none = 0,
        gameOver = 1,
        particles = 2,

    };
    struct RemoveData
    {
        RemoveData(int scoreChange, uint8_t flags = Flags::none, Vec2d pos = Vec2d(), Vec2d dim = Vec2d(), Vec2d vel = Vec2d(), size_t numParticles = 0) :
                scoreChange(scoreChange), flags(flags), pos(pos), dim(dim), vel(vel), numParticles(numParticles) {}

        bool isGameOver() const noexcept { return flags & gameOver; }
        bool isParticles() const noexcept { return flags & particles; }

        int scoreChange;
        uint8_t flags;

        Vec2d pos;
        Vec2d dim;
        Vec2d vel;
        size_t numParticles;
    };

    enum class Type
    {
        spaceship, projectile, shield
    };

    enum class Side
    {
        player, enemy, neutral
    };
}