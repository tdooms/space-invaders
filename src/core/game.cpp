//============================================================================
// @name        : game.cpp
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "game.h"

#include <thread>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../util/stopwatch.h"

#include "../views/world.h"
#include "../controllers/world.h"
#include "../models/world.h"

#include "../views/player.h"
#include "../views/enemy.h"

#include "../controllers/player.h"
#include "../controllers/enemy.h"

#include "../models/spaceship.h"

#include "../views/projectile.h"
#include "../controllers/projectile.h"
#include "../models/projectile.h"
#include "../parsers/level.h"

namespace core
{

struct player
{
    using model = model::Spaceship;
    using view = view::Player;
    using controller = controller::Player;
};

struct enemy
{
    using model = model::Spaceship;
    using view = view::Enemy;
    using controller = controller::Enemy;
};

struct projectile
{
    using model = model::Projectile;
    using view = view::Projectile;
    using controller = controller::Projectile;
};


// scary stuff
template<typename Object, typename... ModelArgs, typename... ViewArgs, typename... ControllerArgs>
void Game::addObject(std::tuple<ModelArgs...>&& modelArgs, std::tuple<ViewArgs...>&& viewArgs, std::tuple<ControllerArgs...>&& controllerArgs)
{
    // we need lambda functions to wrap the make shared template function, this way it doesn't stay in the way of template argument resolution for std::apply
    const auto modelmaker = [](auto... args){ return std::make_shared<typename Object::model>(args...); };
    const auto viewmaker = [](auto... args){ return std::make_shared<typename Object::view>(args...); };
    const auto controllermaker = [](auto... args){ return std::make_shared<typename Object::controller>(args...); };

    // we call apply to apply the tuple arguments to the lambda's to make our unique pointers
    auto model = std::apply(modelmaker, modelArgs);
    auto view = std::apply(viewmaker, std::tuple_cat(std::make_tuple(model), viewArgs));
    auto controller = std::apply(controllermaker, std::tuple_cat(std::make_tuple(model, view), controllerArgs));

    model->addObserver(view);

    worldModel->add(model);
    worldView->add(view);
    worldController->add(controller);
}

void Game::start()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    // these a re the top level models, views and controllers that represent the world
    worldModel = std::make_shared<model::World>();
    worldView = std::make_shared<view::World>(worldModel);
    worldController = std::make_shared<controller::World>(worldModel, worldView);

    addObject<player>();
    parsers::Level::read(*this, "levels/level0.json");

    bool shouldRun = true;
    bool shouldRender = false;

    size_t frames = 0;

    constexpr std::chrono::duration<double> frameTime(1.0 / 60.0);

    duration<double> unprocessedTime(0);
    duration<double> previousTime = std::chrono::system_clock::now().time_since_epoch();
    duration<double> frameCounter(0);

    // main game loop
    while(shouldRun)
    {
        const auto currentTime = std::chrono::system_clock::now().time_since_epoch();
        const auto passedTime = currentTime - previousTime;
        previousTime = currentTime;

        unprocessedTime += passedTime;
        frameCounter += passedTime;

        // used for printing fps
        if(frameCounter >= 1s)
        {
            std::cout << static_cast<double>(frames) / duration_cast<seconds>(frameCounter).count() << " fps\n";
            frameCounter -= 1s;
            frames = 0;
        }

        while(unprocessedTime > frameTime)
        {
            // game update logic
            sf::Event event {};
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed) window.close();
            }

            worldController->update();
            worldModel->update(*this);

            shouldRun = window.isOpen();
            shouldRender = true;
            unprocessedTime -= frameTime;
        }
        if(shouldRender)
        {
            // game render logic
            window.clear();
            worldView->draw(window);
            window.display();

            frames++;
            shouldRender = false;
        }
        else
        {
            std::this_thread::sleep_for(1ms);
        }
    }
}


}