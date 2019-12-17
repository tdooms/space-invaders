//============================================================================
// @name        : enemy.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/spaceship.h"
#include "../views/spaceship.h"
#include "../util/random.h"

namespace controller
{
    class Enemy : public controller::Abstract
    {
    public:
        Enemy(std::shared_ptr<model::Spaceship> model, std::shared_ptr<view::Spaceship> view) : Abstract(std::move(model), std::move(view)) {}

        void update() override
        {
            auto& model = dynamic_cast<model::Spaceship&>(*this->model);

            if(neverStarted)
            {
                const size_t temp = model.getCooldownDuration().count();
                const auto time = util::Random::get().between(0ul, temp);
                cooldown.start(std::chrono::milliseconds(time));
                neverStarted = false;
            }
            if(cooldown.done())
            {
                model.shoot();
            }
        }
    private:
        util::Cooldown cooldown;
        bool neverStarted = true;
    };

}