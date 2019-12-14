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
#include <optional>

namespace core { class Game; }

namespace model
{
    struct RemoveData
    {
        RemoveData(bool gameOver, int scoreChange) : gameOver(gameOver), scoreChange(scoreChange) {}
        bool gameOver;
        int scoreChange;
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