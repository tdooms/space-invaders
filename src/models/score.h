//============================================================================
// @name        : text.h
// @author      : Thomas Dooms
// @date        : 12/7/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"

namespace model
{
    class Score : public model::Abstract
    {
    public:
        Score() = default;

        void update(core::Game& game) override
        {
            if(game.score() == score) return;
            score = game.score();
            send(Type::valueChanged);
        }
    private:
        size_t score;
    };
}