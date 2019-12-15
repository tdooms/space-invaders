//============================================================================
// @name        : particles.cpp
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#pragma once

#include "../util/vec.h"
#include "object.h"
#include "../util/random.h"

namespace model
{
    struct Particle
    {
        Vec2d position;
        Vec2d velocity;
        double radius;
    };

    class Particles : public Object
    {
    public:
        Particles(Vec2d position, Vec2d dimensions, Vec2d velocity, size_t num)
        {
            particles = std::vector<Particle>(num);

            for(auto& particle : particles)
            {
                const auto randomX = util::Random::get().between(position.x - dimensions.x, position.x + dimensions.x);
                const auto randomY = util::Random::get().between(position.y - dimensions.y, position.y + dimensions.y);
                const auto randomVel = util::Random::get().between(0.0, 0.5);
                const auto randomRadius = util::Random::get().between(0.0, 0.05);

                particle.position = Vec2d(randomX, randomY);
                particle.velocity = velocity + (Vec2d::randomUnit() * randomVel);
                particle.radius = randomRadius;
            }
        }

        void update([[maybe_unused]] core::Game& game) override
        {
            for(auto& particle : particles)
            {
                particle.position += particle.velocity;
            }
            if(--frames == 0) removeData = RemoveData(0);

            send(Event::valueChanged);
        }

        [[nodiscard]] const std::vector<Particle>& getParticles() const noexcept
        {
            return particles;
        }

    private:
        std::vector<Particle> particles;
        size_t frames = 100;
    };
}