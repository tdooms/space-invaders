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
#include "../views/playerInfo.h"

#include "json.h"
#include <chrono>
#include <fstream>


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

    static bool loadAndAddPlayer(const std::filesystem::path& path, core::World& world)
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
            world.addViewToEntity<view::PlayerInfo>(id);
        }
        catch(std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }
        return true;
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

    static bool loadAndAddPreview(const nlohmann::json& json, core::World& world, Vec2d pos)
    {
        try
        {
            const auto start = pos;
            const auto velocity = Vec2d();
            const auto dim = Vec2d(json["stats"]["size"], json["stats"]["size"]);
            const double lives = json["stats"]["lives"];
            const util::Color color = {std::make_tuple(json["stats"]["color"][0], json["stats"]["color"][1], json["stats"]["color"][2])};
            const std::string texture = json["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(json["bullets"]);

            world.addEntity<entities::Enemy>(std::tuple(start, velocity, dim, lives, color, texture, bulletInfo));
        }
        catch(std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }
        return true;
    }

    static size_t loadAndAddSelection(const std::filesystem::path& path, core::World& world)
    {
        std::vector<nlohmann::json> choices;

        if(not std::filesystem::is_directory(path))
        {
            throw std::runtime_error("player folder directory does not exist");
        }
        for(const auto& elem : std::filesystem::directory_iterator(path.string()))
        {
            std::fstream file(elem.path());
            auto json = nlohmann::json::parse(file);
            choices.emplace_back(std::move(json));
        }

        if(choices.empty())
        {
            throw std::runtime_error("no players in the player folder");
        }

        std::vector<std::string> names;

        for(const auto& elem : choices)
        {
            names.emplace_back(elem["info"]["name"]);
        }

        const auto id = world.addObject<objects::Selection>(std::tuple(path, std::move(names)));

        const auto offset = 8.0 / static_cast<double>(choices.size());

        auto currPos = Vec2d(-4.0 + 0.5 * offset, 1);
        for(const auto& choice : choices)
        {
            loadAndAddPreview(choice, world, currPos + Vec2d(0, -0.4));
            world.addObject<objects::Text>(std::tuple(choice["info"]["name"], currPos, 20));
            world.addObject<objects::Text>(std::tuple(choice["info"]["description"], currPos + Vec2d(0, 0.3), 11));
            currPos.x += offset;
        }

        return id;
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
            const util::Color color = util::Color::fromJson(enemyJson["stats"]["color"]);

            const std::string texture = enemyJson["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(enemyJson["bullets"]);

            auto curr = start + dim;

            for(size_t i = 0; i < numEnemies; i++)
            {
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