//============================================================================
// @name        : level.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <filesystem>
#include <fstream>
#include <SFML/System/Vector2.hpp>

#include "json.h"
#include "../core/game.h"

namespace parsers
{

    struct Level
    {
        static bool read(core::Game& game, const std::filesystem::path& path)
        {
            std::ifstream file(path);
            if(not file.is_open()) return false;

            const auto json = nlohmann::json::parse(file);

            for(const auto& enemy : json["enemies"])
            {
                auto modelArgs = std::tuple(sf::Vector2f(enemy["posx"], enemy["posy"]));
                auto controllerArgs = std::tuple(json["speed"], json["movetime"]);
                game.addObject<core::enemy>(std::move(modelArgs), std::tuple(), std::move(controllerArgs));
            }
            return true;
        }
    };

}

