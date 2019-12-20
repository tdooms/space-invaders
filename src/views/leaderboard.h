//============================================================================
// @name        : Leaderboard.h
// @author      : Thomas Dooms
// @date        : 12/20/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/leaderboard.h"

namespace view
{
    class Leaderboard : public view::Abstract
    {
    public:
        explicit Leaderboard(std::shared_ptr<model::Leaderboard> model) : Abstract(std::move(model))
        {
            const auto pos = util::Transform::get().transform(Vec2d(0, 2.5));
            const auto offsetX = util::Transform::get().scale(Vec2d(0.4, 0));
            const auto offsetY = util::Transform::get().scale(Vec2d(0, 0.05));

            curr.setPosition(pos - offsetY);
            next.setPosition(pos + offsetX);
            prev.setPosition(pos - offsetX);

            name.setPosition(util::Transform::get().transform(Vec2d(0, 0)));
            info.setPosition(util::Transform::get().transform(Vec2d(0, -2.5)));
            result.setPosition(util::Transform::get().transform(Vec2d(0, -2.5)));

            const auto font = SfManager::getFont("LemonMilk");
            curr.setFont(*font);
            next.setFont(*font);
            prev.setFont(*font);
            name.setFont(*font);
            info.setFont(*font);
            result.setFont(*font);

            next.setFillColor(sf::Color(153, 153, 153));
            prev.setFillColor(sf::Color(153, 153, 153));

            curr.setCharacterSize(40);
            next.setCharacterSize(25);
            prev.setCharacterSize(25);
            name.setCharacterSize(50);
            info.setCharacterSize(50);
            result.setCharacterSize(70);

            info.setString("please enter your name");
            result.setString("game over");

            centerText(info);
            centerText(result);

            const auto& scores = dynamic_cast<model::Leaderboard&>(*this->model).getScores();
            const auto& transform = util::Transform::get();

            auto current = Vec2d(0, -1.5);

            leaderboard.resize(scores.size());
            for(size_t i = 0; i < scores.size(); i++)
            {
                leaderboard[i][0].setPosition(transform.transform(current - Vec2d(2, 0)));
                leaderboard[i][1].setPosition(transform.transform(current));
                leaderboard[i][2].setPosition(transform.transform(current + Vec2d(2, 0)));

                leaderboard[i][0].setFont(*font);
                leaderboard[i][1].setFont(*font);
                leaderboard[i][2].setFont(*font);
                current += Vec2d(0, 0.5);
            }


            receive(Event::valueChanged);
        }

        void receive(Event event) override
        {
            if(event != Event::valueChanged) return;

            const auto& model = dynamic_cast<model::Leaderboard&>(*this->model);
            showName = model.getShowName();

            if(showName)
            {
                prev.setString(model.getPrevChar());
                curr.setString(model.getChar());
                next.setString(model.getNextChar());
                name.setString(model.getName());

                centerText(curr);
                centerText(next);
                centerText(prev);
                centerText(name);

                result.setString("new highscore");
                centerText(result);
            }
            else
            {
                const auto& scores = model.getScores();
                for(size_t i = 0; i < scores.size(); i++)
                {
                    leaderboard[i][0].setString(std::to_string(i + 1));
                    leaderboard[i][1].setString(scores[i].second);
                    leaderboard[i][2].setString(std::to_string(scores[i].first));

                    centerText(leaderboard[i][0]);
                    centerText(leaderboard[i][1]);
                    centerText(leaderboard[i][2]);
                }
            }
        }

        void centerText(sf::Text& text)
        {
            text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
        }

        void draw(sf::RenderWindow& window) const override
        {
            if(showName)
            {
                window.draw(prev);
                window.draw(curr);
                window.draw(next);

                window.draw(name);
                window.draw(info);
            }
            else
            {
                for(const auto& elem : leaderboard)
                {
                    window.draw(elem[0]);
                    window.draw(elem[1]);
                    window.draw(elem[2]);
                }
                window.draw(result);
            }
        }

    private:
        sf::Text prev;
        sf::Text curr;
        sf::Text next;

        sf::Text name;
        sf::Text info;

        bool showName = false;
        sf::Text result;
        std::vector<std::array<sf::Text, 3>> leaderboard;
    };
}
