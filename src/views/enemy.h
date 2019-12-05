//============================================================================
// @name        : enemy.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "abstract.h"
#include "../managers/texture.h"
#include "../models/spaceship.h"


namespace view
{
    class Enemy : public view::Abstract
    {
    public:
        explicit Enemy(std::shared_ptr<model::Spaceship> model) : Abstract(std::move(model))
        {
            const auto texture = manager::Texture::get("len.jpg");
            shape.setTexture(texture.get());
            shape.setRadius(30.f);
        }

        void receive(Type type) override
        {
            if(type != Type::valueChanged) return;
            auto& model = dynamic_cast<model::Spaceship&>(*this->model);
            shape.setPosition(model.position());
        }

        void draw(sf::RenderWindow& window) const override
        {
            window.draw(shape);
        }

    private:
        sf::CircleShape shape;
    };

}
