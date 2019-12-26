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

namespace model
{
    // the world model, used in core::World
    class World : public model::Abstract
    {
    public:
        void update(core::World& world) override
        {
            for(const auto& model : models) model.second->update(world);
        }

        void emplace(size_t id, std::shared_ptr<model::Abstract> model)
        {
            models.emplace(id, std::move(model));
        }

        void erase(size_t id)
        {
            models.erase(id);
        }

        void clear()
        {
            models.clear();
        }

        auto begin() { return models.begin(); }
        auto end() { return models.end(); }
        auto find(size_t id) { return models.find(id); }

    private:
        std::unordered_map<size_t, std::shared_ptr<model::Abstract>> models;
    };

}

