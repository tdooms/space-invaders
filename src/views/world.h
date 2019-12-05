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

namespace view
{
    class World : public view::Abstract
    {
    public:
        explicit World(std::shared_ptr<model::World> model) : Abstract(std::move(model)) {}

        void draw(sf::RenderWindow& window) const override
        {
            for(const auto& view : views) view->draw(window);
        }

        void add(std::shared_ptr<view::Abstract> view)
        {
            views.emplace_back(std::move(view));
        }

        void receive([[maybe_unused]] Type type) override {}

    private:
        std::vector<std::shared_ptr<view::Abstract>> views;
    };
}
