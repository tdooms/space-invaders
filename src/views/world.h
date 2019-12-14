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
#include <unordered_map>
#include "../models/world.h"

namespace view
{
    class World : public view::Abstract
    {
    public:
        explicit World(std::shared_ptr<model::World> model) : Abstract(std::move(model)) {}

        void draw(sf::RenderWindow& window) const override
        {
            for(const auto& view : views) view.second->draw(window);
        }

        void emplace(size_t id, std::shared_ptr<view::Abstract> view)
        {
            views.emplace(id, std::move(view));
        }

        void erase(size_t id)
        {
            views.erase(id);
        }

        void clear()
        {
            views.clear();
        }

        void receive([[maybe_unused]] Event type) override {}

    private:
        // this needs to be a multimap to support multiple views to the same model
        std::unordered_multimap<size_t, std::shared_ptr<view::Abstract>> views;
    };
}
