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
    Selection(std::shared_ptr<model::Selection> model) : Abstract(std::move(model))
    {
        text.setFont(*SfManager::getFont("LemonMilk"));
        text.setString("current choice");
        text.setCharacterSize(18);
        text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);

        info.setFont(*SfManager::getFont("LemonMilk"));
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
        const auto start = Vec2d(-4.0 + 0.5 * offset, 1.5);
        const auto pos = start + Vec2d(model.getChoice() * offset, 0);

        text.setPosition(util::Transform::get().transform(pos));
    }

    void draw([[maybe_unused]] sf::RenderWindow& window) const override
    {
        window.draw(text);
        window.draw(info);
    }

private:
    sf::Text text;
    sf::Text info;
};
}