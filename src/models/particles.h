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
#include "../util/color.h"
#include "../util/random.h"

#include "object.h"

namespace inheritable { struct ExplodeData; }


namespace model
{
    struct Particle
    {
        Vec2d position;
        Vec2d velocity;
        util::Color color;
        double radius;
    };

    class Particles : public Object
    {
    public:
        Particles(inheritable::ExplodeData data);

        void update(core::World& world) override;

        [[nodiscard]] const std::vector<Particle>& getParticles() const noexcept;

    private:
        std::vector<Particle> particles;

        size_t frames = 100;
    };
}