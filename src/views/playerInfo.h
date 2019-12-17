//============================================================================
// @name        : playerInfo.h
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <SFML/Graphics/Text.hpp>
#include "abstract.h"

#include "../models/spaceship.h"
#include "../managers/manager.h"
#include "../util/transform.h"

namespace view
{
class PlayerInfo : public view::Abstract
{
public:
    explicit PlayerInfo(std::shared_ptr<model::Abstract> model) : Abstract(std::move(model))
    {
        const auto posY = util::Transform::get().scale(height + offset);

        backLiveRect.setPosition(0, 0);
        backLiveRect.setFillColor(sf::Color(151, 151, 151));

        liveRect.setPosition(0, 0);
        liveRect.setFillColor(sf::Color(151, 102, 102));

        backCooldownRect.setPosition(0, posY);
        backCooldownRect.setFillColor(sf::Color(151, 151, 151));

        cooldownRect.setPosition(0, posY);
        cooldownRect.setFillColor(sf::Color(102, 151, 151));
    }

    void receive(Event type) override
    {
        if(type != Event::valueChanged) return;

        const auto& model = dynamic_cast<model::Spaceship&>(*this->model);
        const auto& transform = util::Transform::get();
        const auto& cooldown = model.getCooldown();

        auto length = cooldownLength;
        if(cooldown.currentDuration().count() != 0)
        {
            length = cooldownLength * cooldown.msRemaining() / cooldown.currentDuration();
        }

        const auto backLiveSize = transform.scale(model.getMaxLives() / 3.0, height);
        const auto liveSize = transform.scale(model.getLives() / 3.0, height);

        const auto backCooldownSize = transform.scale(cooldownLength, height);
        const auto cooldownSize = transform.scale(length, height);

        backLiveRect.setSize(backLiveSize);
        liveRect.setSize(liveSize);

        backCooldownRect.setSize(backCooldownSize);
        cooldownRect.setSize(cooldownSize);
    }

    void draw(sf::RenderWindow& window) const override
    {
        window.draw(backLiveRect);
        window.draw(liveRect);

        window.draw(backCooldownRect);
        window.draw(cooldownRect);
    }

private:
    sf::RectangleShape backLiveRect;
    sf::RectangleShape liveRect;

    sf::RectangleShape backCooldownRect;
    sf::RectangleShape cooldownRect;

    const static inline double height = 0.2;
    const static inline double offset = 0.05;

    const static inline double cooldownLength = 1.0;
};
}