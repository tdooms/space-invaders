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

#include <unordered_map>
#include <memory>


namespace controller
{
    class World : public controller::Abstract
    {
    public:
        World(std::shared_ptr<model::World> model, std::shared_ptr<view::World> view) : Abstract(std::move(model), std::move(view)) {}

        void update() override
        {
            for(auto& controller : controllers) controller.second->update();
        }

        void emplace(size_t id, std::shared_ptr<controller::Abstract> controller)
        {
            controllers.emplace(id, std::move(controller));
        }

        void erase(size_t id)
        {
            controllers.erase(id);
        }

        void clear()
        {
            controllers.clear();
        }

    private:
        // this needs to be a multimap to allow multiple controllers, controlling the same model
        std::unordered_multimap<size_t, std::shared_ptr<controller::Abstract>> controllers;

    };

}

