//============================================================================
// @name        : particles.cpp
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "object.h"
#include "../inheritables/explodable.h"

namespace model
{

    Particles::Particles(inheritable::ExplodeData data) : particles(data.num), color(data.color)
    {
        for(auto& particle : particles)
        {
            const auto randomX = util::Random::get().between(data.pos.x - data.dim.x, data.pos.x + data.dim.x);
            const auto randomY = util::Random::get().between(data.pos.y - data.dim.y, data.pos.y + data.dim.y);
            const auto randomVel = util::Random::get().between(0.0, 0.02);
            const auto randomRadius = util::Random::get().between(0.0, 0.015);

            particle.position = Vec2d(randomX, randomY);
            particle.velocity = data.vel + (Vec2d::randomUnit() * randomVel);
            particle.radius = randomRadius;
        }
    }

    void Particles::update([[maybe_unused]] core::World& world)
    {
        for(auto& particle : particles)
        {
            particle.position += particle.velocity;
        }
        if(--frames == 0) reaction = Reaction::remove;

        send(Event::valueChanged);
    }

    [[nodiscard]] const std::vector<Particle>& Particles::getParticles() const noexcept
    {
        return particles;
    }

    [[nodiscard]] util::Color Particles::getColor() const noexcept
    {
        return color;
    }

}