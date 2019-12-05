//============================================================================
// @name        : world.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/world.h"
#include "../views/world.h"

#include <vector>
#include <memory>


namespace controller
{
    class World : public controller::Abstract
    {
    public:
        World(std::shared_ptr<model::World> model, std::shared_ptr<view::World> view) : Abstract(std::move(model), std::move(view)) {}

        void update() override
        {
            for(auto& controller : controllers) controller->update();
        }

        void add(std::shared_ptr<controller::Abstract> controller)
        {
            controllers.emplace_back(std::move(controller));
        }

    private:
        std::vector<std::shared_ptr<controller::Abstract>> controllers;

    };

}

