//============================================================================
// @name        : selection.h
// @author      : Thomas Dooms
// @date        : 12/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"

namespace view
{
class Selection final : public view::Abstract
{
public:
    explicit Selection(std::shared_ptr<model::Selection> model) : Abstract(std::move(model))
    {
        const auto dim = util::Transform::get().scale(Vec2d(0.3, 0.3));
        arrow.setTexture(util::SfManager::getTexture("arrow").get());
        arrow.setSize(dim);
        arrow.setOrigin(dim.x / 2.0f, dim.y / 2.0f);

        info.setFont(*util::SfManager::getFont("LemonMilk"));
        info.setString("press enter to choose");
        info.setCharacterSize(30);
        info.setOrigin(info.getLocalBounds().width / 2.0f, info.getLocalBounds().height / 2.0f);
        info.setPosition(util::Transform::get().transform(Vec2d(0, 2.5)));

        receive(Event::valueChanged);
    }

    void receive([[maybe_unused]] Event event) override
    {
        if(event != Event::valueChanged) return;
        const auto& model = dynamic_cast<model::Selection&>(*this->model);

        const auto offset = 8.0 / static_cast<double>(model.getNum());
        const auto start = Vec2d(-4.0 + 0.5 * offset, 1.6);
        const auto pos = start + Vec2d(model.getChoice() * offset, 0);

        arrow.setPosition(util::Transform::get().transform(pos));
    }

    void draw([[maybe_unused]] sf::RenderWindow& window) const override
    {
        const auto oldPos = arrow.getPosition();
        const float offset = util::Transform::get().scale(offsetY);

        arrow.setPosition(oldPos.x, oldPos.y + offset);

        if(up) offsetY += 0.005;
        else offsetY -= 0.005;

        if(offsetY > maxJump) up = false;
        if(offsetY < 0) up = true;

        window.draw(arrow);
        window.draw(info);

        arrow.setPosition(oldPos);
    }

private:
    sf::Text info;
    mutable sf::RectangleShape arrow;

    mutable double offsetY = 0;
    mutable bool up = true;

    double maxJump = 0.1;
};
}