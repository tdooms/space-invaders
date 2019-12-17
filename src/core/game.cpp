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
#include <fstream>
#include <SFML/Graphics.hpp>

#include "../parsers/json.h"
#include "../parsers/parser.h"

#include <chrono>
#include <memory>
#include <unordered_set>

using namespace std::chrono;


namespace core
{

void Game::startGame()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

    // we initialize some variables used in the main game loop
    bool shouldRender = false;
    bool shouldRun = true;

    size_t frames = 0;
    constexpr std::chrono::duration<double> frameTime(1.0 / 60.0);

    duration<double> unprocessedTime(0);
    duration<double> previousTime = std::chrono::system_clock::now().time_since_epoch();
    duration<double> frameCounter(0);

    // read the player config data
    parser::loadAndAddPlayer("res/players/duo.json", world);
    parser::loadAndAddShield("res/shields/shield-config.json", world);

//    parser::loadAndAddSelection("res/players", start);

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
            const auto stage = world.update();

            if(stage == Stage::victory)
            {
                parser::loadAndAddLevel("res/levels/level0.json", world);
            }

            if(stage == Stage::defeat and not gameOverAdded)
            {
                gameOverAdded = true;
                world.addObject<objects::Text>(std::tuple("game over", Vec2d(0, 0), 100));
            }

            if(not window.isOpen()) shouldRun = false;
            shouldRender = true;
            unprocessedTime -= frameTime;
        }
        if(shouldRender)
        {
            // game render logic
            window.clear();
            world.draw(window);
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