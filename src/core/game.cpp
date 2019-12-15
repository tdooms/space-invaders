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

#include "../managers/level.h"
#include "../managers/detector.h"

using namespace std::chrono;


namespace core
{

void Game::tryRemoveEntities()
{
    std::vector<std::pair<size_t, model::RemoveData>> toRemove;
    for(const auto& [id, model] : *worldModel)
    {
        const auto data = model->getRemoveData();
        if(data.has_value()) toRemove.emplace_back(id, data.value());
    }

    for(const auto [id, data] : toRemove)
    {
        if(data.isGameOver()) stage = Stage::over;
        score += data.scoreChange;

        if(data.isParticles())
        {
            addObject<objects::Particles>(std::tuple(data.pos, data.dim, data.vel, data.numParticles));
        }

        worldModel->erase(id);
        worldView->erase(id);
        worldController->erase(id);

        enemies.erase(id);
    }
}

void Game::tryLoadLevel()
{
    if(enemies.empty() and stage == Stage::game)
    {
        if(manager::Level::read(*this)) return;

        std::cout << "next level could not be loaded\n";
        stage = Stage ::victory;
    }
}

void Game::start()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

    // these a re the top level models, views and controllers that represent the world
    worldModel = std::make_shared<model::World>();
    worldView = std::make_shared<view::World>(worldModel);
    worldController = std::make_shared<controller::World>(worldModel, worldView);

    // we initialize some variables used in the main game loop
    bool shouldRender = false;
    bool shouldRun = true;

    size_t frames = 0;
    constexpr std::chrono::duration<double> frameTime(1.0 / 60.0);

    duration<double> unprocessedTime(0);
    duration<double> previousTime = std::chrono::system_clock::now().time_since_epoch();
    duration<double> frameCounter(0);

    // read the player config data
    manager::Player::read(*this);
    manager::Shield::read(*this);

    // main game loop
    while(shouldRun)
    {
        // update time parameters
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
            // update and poll SFML events
            sf::Event event {};
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed) window.close();
            }

            // game update logic
            worldController->update();
            worldModel->update(*this);

            collision::detect(worldModel);

            tryRemoveEntities();
            tryLoadLevel();

            if(stage == Stage::over and not gameOverAdded)
            {
                gameOverAdded = true;
                addObject<objects::Text>(std::tuple("game over", Vec2d(0, 0), 100));
            }

            if(not window.isOpen()) shouldRun = false;
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