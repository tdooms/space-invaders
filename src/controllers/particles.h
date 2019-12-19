//============================================================================
// @name        : text.h
// @author      : Thomas Dooms
// @date        : 12/18/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/particles.h"
#include "../views/particles.h"

namespace controller
{
    class Particles : public controller::Abstract
    {
    public:
        Particles(std::shared_ptr<model::Particles> model, std::shared_ptr<view::Particles> view) : Abstract(std::move(model), std::move(view)) {}

        void update() override {}
    };

}