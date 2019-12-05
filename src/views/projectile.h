//============================================================================
// @name        : projectile.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "abstract.h"
#include "../managers/texture.h"
#include "../models/projectile.h"

namespace view
{
    class Projectile : public view::Abstract
    {
    public:
        explicit Projectile(std::shared_ptr<model::Projectile> model) : Abstract(std::move(model))
        {
            const auto texture = manager::Texture::get("tom.jpg");
            shape.setTexture(texture.get());
            shape.setRadius(20.f);
        }

        void receive(Type type) override
        {
            if(type != Type::valueChanged) return;
            auto& model = dynamic_cast<model::Projectile&>(*this->model);
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