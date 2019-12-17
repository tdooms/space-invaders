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
#include "../managers/manager.h"
#include "../models/spaceship.h"
#include "../util/transform.h"
#include "../util/color.h"


namespace view
{
    class Spaceship final : public view::Abstract
    {
    public:
        explicit Spaceship(std::shared_ptr<model::Spaceship> model) : Abstract(std::move(model))
        {
            receive(Event::valueChanged);
            receive(Event::textureChanged);
        }

        void receive(Event type) override
        {
            auto& model = dynamic_cast<model::Spaceship&>(*this->model);

            if(type == Event::textureChanged)
            {
                shape.setTexture(SfManager::getTexture(model.getTexture()).get());
            }
            else
            {
                const auto dim = util::Transform::get().scale(model.getDimensions());
                const auto pos = util::Transform::get().transform(model.getPosition());
                const auto color = model.getColor();

                shape.setPosition(pos);
                shape.setSize(sf::Vector2f(dim.x * 2.f, dim.y * 2.f));
                shape.setOrigin(dim);
                shape.setFillColor(util::Color::toSfColor(color));
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
