//============================================================================
// @name        : elship.h
// @author      : Thomas Dooms
// @date        : 11/24/19
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

class Player : public view::Abstract
{
public:
    explicit Player(std::shared_ptr<model::Spaceship> model) : Abstract(std::move(model))
    {
        const auto texture = manager::Texture::get("els.jpg");
        shape.setTexture(texture.get());
        shape.setRadius(100.f);
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