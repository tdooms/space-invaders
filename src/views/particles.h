//============================================================================
// @name        : particles.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/particles.h"
#include "../util/transform.h"

namespace view
{
    class Particles final : public view::Abstract
    {
    public:
        explicit Particles(std::shared_ptr<model::Particles> model) : Abstract(std::move(model))
        {
            receive(Event::valueChanged);
        }

        void receive(Event event) override
        {
            if(event != Event::valueChanged) return;
            const auto& model = dynamic_cast<model::Particles&>(*this->model);

            const auto& particles = model.getParticles();
            if(particles.size() != shapes.size())
            {
                shapes = std::vector<sf::CircleShape>(particles.size());
            }

            for(size_t i = 0; i < particles.size(); i++)
            {
                const auto pos = util::Transform::get().transform(particles[i].position);
                const auto radius = util::Transform::get().scale(particles[i].radius);

                shapes[i].setPosition(pos);
                shapes[i].setRadius(radius);

                shapes[i].setFillColor(util::Color::toSfColor(model.getColor()));
            }
        }

        void draw(sf::RenderWindow& window) const override
        {
            for(const auto& shape : shapes)
            {
                window.draw(shape);
            }
        }

        std::vector<sf::CircleShape> shapes;
    };
}