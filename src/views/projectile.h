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
#include "../managers/manager.h"
#include "../models/projectile.h"
#include "../util/transform.h"

namespace view
{
    class Projectile : public view::Abstract
    {
    public:
        explicit Projectile(std::shared_ptr<model::Projectile> model) : Abstract(std::move(model))
        {
            const auto texture = SfManager::getTexture("tom.jpg");
            const auto position = dynamic_cast<model::Projectile&>(*this->model).getPosition();

            shape.setTexture(texture.get());
            shape.setRadius(util::Transform::get().scale(.05f));
            shape.setPosition(util::Transform::get().transform(position));
        }

        void receive(Event type) override
        {
            if(type != Event::valueChanged) return;
            auto& model = dynamic_cast<model::Projectile&>(*this->model);
            const auto radius = util::Transform::get().scale(model.getRadius());

            shape.setPosition(util::Transform::get().transform(model.getPosition()));
            shape.setRadius(radius);
            shape.setOrigin(radius, radius);
        }

        void draw(sf::RenderWindow& window) const override
        {
            window.draw(shape);
        }

    private:
        sf::CircleShape shape;
    };
}