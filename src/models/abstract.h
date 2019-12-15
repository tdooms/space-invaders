//============================================================================
// @name        : abstract.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../observer/subject.h"
#include "../util/vec.h"
#include <optional>

namespace core { class Game; }

namespace model
{
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

    class Abstract : public Subject
    {
    public:
        Abstract() = default;
        virtual ~Abstract() = default;

        std::optional<RemoveData> getRemoveData() noexcept { return removeData; }
        virtual void update(core::Game& game) = 0;

    protected:
        std::optional<RemoveData> removeData;
    };
}