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

#include "../parsers/json.h"
#include "../core/game.h"
#include "../views/playerInfo.h"
#include "../core/entities.h"
#include "../util/random.h"

namespace manager
{
    struct Player
    {
        static bool read(core::Game& game)
        {
            if(not std::filesystem::exists(path)) return false;

            std::ifstream file(path);
            if(not file.is_open()) return false;
            const auto json = nlohmann::json::parse(file);

            try
            {
                const auto start = Vec2d(json["stats"]["startX"], json["stats"]["startY"]);
                const auto velocity = Vec2d();
                const auto size = json["stats"]["size"];
                const auto lives = json["stats"]["lives"];
                const auto cooldown = std::chrono::milliseconds(json["bullets"]["cooldown"]);
                const auto texture = json["stats"]["texture"];

                auto id = game.addEntity<Entity::Player>(std::tuple(start, velocity, size, lives, cooldown, texture));
                game.addViewToEntity<view::PlayerInfo>(id);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            return true;
        }

        static inline std::filesystem::path path = "levels/player-config.json";
    };

    struct Level
    {
        static bool read(core::Game& game)
        {
            std::filesystem::path path = base + std::to_string(num);
            path.replace_extension(extension);
            if(not std::filesystem::exists(path)) return false;

            // open and parse file
            std::ifstream file(path);
            if(not file.is_open()) return false;
            const auto json = nlohmann::json::parse(file);

            try
            {
                static const auto start = Vec2d(-3.9, -2.9);

                const size_t numEnemies = json["level"]["numEnemies"];
                const size_t numRows = json["level"]["numRows"];
                const size_t enemiesPerRow = numEnemies / numRows;

                const auto velocity = Vec2d(json["stats"]["horizontalSpeed"], json["stats"]["downSpeed"]);
                const double size = json["stats"]["size"];
                const double lives = json["stats"]["lives"];
                const auto cooldown = std::chrono::milliseconds(json["bullets"]["cooldown"]);
                const std::vector<std::string> textures = json["stats"]["textures"];

                auto curr = start + Vec2d(size, size);

                for(size_t i = 0; i < numEnemies; i++)
                {
                    const auto& texture = textures[0];
                    game.addEntity<Entity::Enemy>(std::tuple(curr, velocity, size, lives, cooldown, texture));

                    // calculate next position
                    if(i + 1 == enemiesPerRow)
                    {
                         curr.x = start.x + util::Random::get().between(0.1, 0.2);
                         curr.y += 2*size + 0.05;
                    }
                    else
                    {
                        curr.x += 2*size + util::Random::get().between(0.1, 0.2);
                    }
                }
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }

            num++;
            return true;
        }
        static inline size_t num = 0;
        static inline std::string base = "levels/level";
        static inline std::string extension = "json";
    };

}

