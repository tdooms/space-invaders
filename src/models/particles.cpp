//============================================================================
// @name        : particles.cpp
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "object.h"
#include "particles.h"

#include "../inheritables/explodable.h"

namespace model
{

    Particles::Particles(inheritable::ExplodeData data) : particles(data.num)
    {
        for(auto& particle : particles)
        {
            const auto randomX = util::Random::get().between(data.pos.x - data.dim.x, data.pos.x + data.dim.x);
            const auto randomY = util::Random::get().between(data.pos.y - data.dim.y, data.pos.y + data.dim.y);
            const auto randomVel = util::Random::get().between(0.0, 0.02);
            const auto randomRadius = util::Random::get().between(data.minSize, data.maxSize);
            const auto alpha = util::Random::get().between(200, 255);

            particle.position = Vec2d(randomX, randomY);
            particle.velocity = data.vel + (Vec2d::randomUnit() * randomVel);
            particle.radius = randomRadius;
            particle.color = util::Color::addAlpha(data.color, static_cast<uint8_t>(alpha));
        }
    }

    void Particles::update([[maybe_unused]] core::World& world)
    {
        for(auto& particle : particles)
        {
            particle.position += particle.velocity;
            if(particle.color.a != 0) particle.color.a -= 1;
        }
        if(--frames == 0) reaction = Reaction::remove;

        send(Event::valueChanged);
    }

    [[nodiscard]] const std::vector<Particle>& Particles::getParticles() const noexcept
    {
        return particles;
    }

}