//============================================================================
// @name        : score.h
// @author      : Thomas Dooms
// @date        : 12/20/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/score.h"
#include "../views/score.h"

namespace controller
{
    class Score : public controller::Abstract
    {
    public:
        Score(std::shared_ptr<model::Score> model, std::shared_ptr<view::Score> view) : Abstract(std::move(model), std::move(view)) {}

        void update() override {}
    };

}