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

namespace model
{
    class World : public model::Abstract
    {
    public:
        void update(core::Game& game) override
        {
            for(size_t i = 0; i < models.size(); i++) models[i]->update(game);
        }

        void add(std::shared_ptr<model::Abstract> model)
        {
            models.emplace_back(std::move(model));
        }

    private:
        std::vector<std::shared_ptr<model::Abstract>> models;
    };

}

