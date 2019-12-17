//============================================================================
// @name        : bullet.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../models/structs.h"
#include "../util/vec.h"
#include "../util/random.h"
#include "json.h"
#include "../views/playerInfo.h"
#include <chrono>


namespace parser
{
    static nlohmann::json openJson(const std::filesystem::path& path)
    {
        if(not std::filesystem::exists(path))
        {
            throw std::runtime_error("file with path: " + path.string() + " does not exist");
        }
        std::ifstream file(path);

        if(not file.is_open())
        {
            throw std::runtime_error("file with path: " + path.string() + " could not be read");
        }

        return nlohmann::json::parse(file);
    }

    static model::BulletInfo parseBulletInfo(const nlohmann::json& json)
    {
        model::BulletInfo result;
        result.texture = json["texture"];
        result.color = {std::make_tuple(json["color"][0], json["color"][1], json["color"][2])};
        result.cooldownTime = std::chrono::milliseconds(json["cooldownTime"]);

        const double size = json["size"];

        result.speed = json["speed"];
        result.dim = Vec2d(size, size * 2.0);
        result.damage = json["damage"];
        result.pierce = json["pierce"];

        result.shootAngle = json["shootAngle"].get<double>() * (M_PI / 180.0);
        result.spreadAngle = json["spreadAngle"].get<double>() * (M_PI / 180.0);
        result.numBullets = json["numBullets"];

        return result;
    }

    static bool loadAndAddShield(const std::filesystem::path& path, core::World& world)
    {
        try
        {
            const auto json = openJson(path);
            for(const auto& elem : json["shields"])
            {
                const auto posititon = Vec2d(elem["posX"], elem["posY"]);
                const auto dimensions = Vec2d(elem["dimX"], elem["dimY"]);
                const double lives = elem["lives"];
                const auto texture = elem["texture"];

                world.addEntity<entities::Shield>(std::tuple(posititon, dimensions, lives, texture));
            }
        }
        catch(std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }
        return true;
    }

    static bool loadAndAddPlayer(const std::filesystem::path& path, core::World& world, bool addPlayerInfo = true)
    {
        try
        {
            const auto json = openJson(path);

            const auto start = Vec2d(json["stats"]["startX"], json["stats"]["startY"]);
            const auto velocity = Vec2d();
            const auto dim = Vec2d(json["stats"]["size"], json["stats"]["size"]);
            const double lives = json["stats"]["lives"];
            const util::Color color = {std::make_tuple(json["stats"]["color"][0], json["stats"]["color"][1], json["stats"]["color"][2])};
            const std::string texture = json["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(json["bullets"]);

            const auto id = world.addEntity<entities::Player>(std::tuple(start, velocity, dim, lives, color, texture, bulletInfo));
            if(addPlayerInfo) world.addViewToEntity<view::PlayerInfo>(id);
        }
        catch(std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }
        return true;
    }

    static bool loadAndAddSelection(const std::filesystem::path& path, core::World& world)
    {
        std::vector<nlohmann::json> choices;

        if(not std::filesystem::is_directory(path))
        {
            throw std::runtime_error("player folder directory does not exist");
        }
        for(const auto& elem : std::filesystem::directory_iterator(path.string()))
        {
            choices.emplace_back(elem.path());
        }

        if(choices.empty())
        {
            throw std::runtime_error("no players in the player folder");
        }

        std::vector<std::pair<std::string, std::string>> data;
        for(const auto& elem : choices)
        {
            data.emplace_back(elem["name"], elem["description"]);
        }

        constexpr double firstRowHeight = 1;
        constexpr double secondRowHeight = -1;

        size_t numOnFirstRow = data.size() / 2;
        size_t numOnSecondRow = data.size() - numOnFirstRow;

        double firstSpace = 8.0 / static_cast<double>(numOnFirstRow + 1);
        double secondSpace = 8.0 / static_cast<double>(numOnSecondRow + 1);

        auto currPos = Vec2d(firstSpace, firstRowHeight);
        for(size_t i = 0; i < data.size(); i++)
        {
            world.addObject<objects::Text>(std::tuple(data[i].first, currPos, 20));
            world.addObject<objects::Text>(std::tuple(data[i].second, currPos + Vec2d(0, 0.3), 12));

            if(i == numOnFirstRow) currPos = Vec2d(secondSpace, secondRowHeight);
            else if(i < numOnFirstRow) currPos.x += firstSpace;
            else currPos.x += secondSpace;
        }

        return true;
    }

    static bool loadAndAddLevel(const std::filesystem::path& path, core::World& world)
    {
        try
        {
            const auto json = openJson(path);
            static const auto start = Vec2d(-3.9, -2.9);

            const size_t numEnemies = json["level"]["numEnemies"];
            const size_t numRows = json["level"]["numRows"];
            const size_t enemiesPerRow = numEnemies / numRows;

            const auto enemyJson = openJson("res/enemies/" + json["level"]["type"].get<std::string>() + ".json");

            const auto velocity = Vec2d(enemyJson["stats"]["horizontalSpeed"], enemyJson["stats"]["downSpeed"]);
            const auto dim = Vec2d(enemyJson["stats"]["size"], enemyJson["stats"]["size"]);
            const double lives = enemyJson["stats"]["lives"];
            const util::Color color = {std::make_tuple(enemyJson["stats"]["color"][0], enemyJson["stats"]["color"][1], enemyJson["stats"]["color"][2])};

            const std::vector<std::string> textures = enemyJson["stats"]["textures"];
            const auto bulletInfo = parseBulletInfo(enemyJson["bullets"]);

            auto curr = start + dim;

            for(size_t i = 0; i < numEnemies; i++)
            {
                const auto& texture = textures[0];
                world.addEntity<entities::Enemy>(std::tuple(curr, velocity, dim, lives, color, texture, bulletInfo));

                // calculate next position
                if(i + 1 == enemiesPerRow)
                {
                    curr.x = start.x + util::Random::get().between(0.1, 0.2);
                    curr.y += 2 * dim.y + 0.05;
                }
                else
                {
                    curr.x += 2 * dim.x + util::Random::get().between(0.1, 0.2);
                }
            }
        }
        catch(std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }
        return true;
    }
}