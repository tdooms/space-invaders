//============================================================================
// @name        : Abstract.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../models/abstract.h"
#include "../views/abstract.h"

namespace controller
{
    class Abstract
    {
    public:
        Abstract(std::shared_ptr<model::Abstract> model, std::shared_ptr<view::Abstract> view) : model(std::move(model)), view(std::move(view)) {}

        virtual ~Abstract() = default;

        virtual void update() = 0;

    protected:
        std::shared_ptr<model::Abstract> model;
        std::shared_ptr<view::Abstract> view;
    };
}
