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
    class Projectile final : public view::Abstract
    {
    public:
        explicit Projectile(std::shared_ptr<model::Projectile> model) : Abstract(std::move(model))
        {
            receive(Event::valueChanged);
            receive(Event::textureChanged);
        }

        void receive(Event event) override
        {
            auto& model = dynamic_cast<model::Projectile&>(*this->model);

            if(event == Event::valueChanged)
            {
                const auto dimensions = util::Transform::get().scale(model.getDimensions());
                const auto color = model.getColor();

                shape.setPosition(util::Transform::get().transform(model.getPosition()));
                shape.setSize(sf::Vector2f(dimensions.x * 2.0f, dimensions.y * 2.0f));
                shape.setOrigin(dimensions);
                shape.setFillColor(util::Color::toSfColor(color));
            }
            else if(event == Event::textureChanged)
            {
                shape.setTexture(SfManager::getTexture(model.getTexture()).get());
            }
        }

        void draw(sf::RenderWindow& window) const override
        {
            window.draw(shape);
        }

    private:
        sf::RectangleShape shape;
    };
}