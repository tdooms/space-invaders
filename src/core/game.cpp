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
#include <chrono>

#include <SFML/Graphics.hpp>

#include "../parsers/parser.h"
#include "entities.h"
#include "objects.h"

using namespace std::chrono;


namespace core
{

void Game::setup()
{
    id = parser::loadAndAddSelection("res/players", worlds[WorldType::start]);
}

void Game::update(Stage stage)
{
    if(current == WorldType::start)
    {
        const auto& selector = dynamic_cast<model::Selection&>(*worlds[current].findModel(id)->second);
        if(selector.isConfirmed())
        {
            current = WorldType::main;

            parser::loadAndAddPlayer(selector.getPath(), worlds[current]);
            parser::loadAndAddShield("res/shields/shield-config.json", worlds[current]);
            parser::loadAndAddLevel("res/levels/level" + std::to_string(level++) + ".json", worlds[current]);
            worlds[WorldType::main].addObject<objects::Score>(std::tuple(Vec2d(3.6, -2.8), 30));
        }
    }
    if(current == WorldType::main)
    {
        if(stage == Stage::victory)
        {
            parser::loadAndAddLevel("res/levels/level" + std::to_string(level++) + ".json", worlds[current]);
        }
        if(stage == Stage::defeat)
        {
            current = WorldType::end;
            worlds[end].addObject<objects::Leaderboard>(std::tuple("res/data/leaderboard.json", worlds[WorldType::main].getScore()));
        }
    }
}

void Game::startGame()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "space invaders", sf::Style::Titlebar | sf::Style::Close);
    setup();

    // we initialize some variables used in the main game loop
    bool shouldRender = false;
    bool shouldRun = true;

    size_t frames = 0;
    constexpr std::chrono::duration<double> frameTime(1.0 / 60.0);

    duration<double> unprocessedTime(0);
    duration<double> previousTime = std::chrono::system_clock::now().time_since_epoch();
    duration<double> frameCounter(0);

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
            const auto stage = worlds[current].update();
            update(stage);

            // misc update logic
            if(not window.isOpen()) shouldRun = false;
            shouldRender = true;
            unprocessedTime -= frameTime;
        }
        if(shouldRender)
        {
            // game render logic
            window.clear();
            worlds[current].draw(window);
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