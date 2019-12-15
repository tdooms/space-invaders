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
#include <cmath>

#include "../parsers/json.h"
#include "../core/game.h"
#include "../views/playerInfo.h"
#include "../core/entities.h"
#include "../util/random.h"

model::BulletInfo parseBulletInfo(const nlohmann::json& json)
{
    model::BulletInfo result;
    result.texture = json["texture"];
    result.cooldownTime = std::chrono::milliseconds(json["cooldownTime"]);

    result.speed = json["speed"];
    result.size = json["size"];
    result.damage = json["damage"];

    result.shootAngle = json["shootAngle"].get<double>() * (M_PI / 180.0);
    result.spreadAngle = json["spreadAngle"].get<double>() * (M_PI / 180.0);
    result.numBullets = json["numBullets"];

    return result;
}

namespace manager
{
    struct Shield
    {
        static bool read(core::Game& game)
        {
            if(not std::filesystem::exists(path)) return false;

            std::ifstream file(path);
            if(not file.is_open()) return false;
            const auto json = nlohmann::json::parse(file);

            try
            {
                for(const auto& elem : json["shields"])
                {
                    const auto posititon = Vec2d(elem["posX"], elem["posY"]);
                    const auto dimensions = Vec2d(elem["dimX"], elem["dimY"]);
                    const double lives = elem["lives"];
                    const auto texture = elem["texture"];

                    game.addEntity<entities::Shield>(std::tuple(posititon, dimensions, lives, texture));
                }
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            return true;
        }

        static inline std::filesystem::path path = "levels/shield-config.json";
    };

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
                const auto texture = json["stats"]["texture"];

                const auto bulletInfo = parseBulletInfo(json["bullets"]);

                auto id = game.addEntity<entities::Player>(std::tuple(start, velocity, size, lives, texture, bulletInfo));
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
                const std::vector<std::string> textures = json["stats"]["textures"];
                const auto bulletInfo = parseBulletInfo(json["bullets"]);

                auto curr = start + Vec2d(size, size);

                for(size_t i = 0; i < numEnemies; i++)
                {
                    const auto& texture = textures[0];
                    game.addEntity<entities::Enemy>(std::tuple(curr, velocity, size, lives, texture, bulletInfo));

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

