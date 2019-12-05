//============================================================================
// @name        : Abstract.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "../models/abstract.h"

namespace view
{
    class Abstract : public Observer
    {
    public:
        explicit Abstract(std::shared_ptr<model::Abstract> model) : model(std::move(model)) {}
        virtual ~Abstract() = default;

        virtual void draw(sf::RenderWindow& window) const = 0;

    protected:
        std::shared_ptr<model::Abstract> model;
    };
}