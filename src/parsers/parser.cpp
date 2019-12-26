//============================================================================
// @name        : parser.cpp
// @author      : Thomas Dooms
// @date        : 12/26/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "../core/entities.h"
#include "../views/playerInfo.h"
#include "../core/world.h"
#include "../core/objects.h"

#include <fstream>

namespace parser
{
    nlohmann::json openJson(const std::filesystem::path& path)
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

    model::BulletData parseBulletInfo(const nlohmann::json& json)
    {
        model::BulletData result;
        result.texture = json["texture"];
        result.color = util::Color::fromJson(json["color"]);
        result.cooldownTime = std::chrono::milliseconds(json["cooldownTime"]);

        const double size = json["size"];

        result.speed = json["speed"];
        result.dim = Vec2d(size, size * 2.0);
        result.damage = json["damage"];
        result.pierce = json["pierce"];

        // I cannot yet use c++20's std::numbers::pi sadly
        result.shootAngle = json["shootAngle"].get<double>() * (M_PI / 180.0);
        result.spreadAngle = json["spreadAngle"].get<double>() * (M_PI / 180.0);
        result.numBullets = json["numBullets"];

        return result;
    }

    std::vector<std::pair<size_t, std::string>> loadLeaderboard(const std::filesystem::path& path)
    {
        const auto json = openJson(path);
        std::vector<std::pair<size_t, std::string>> scores;

        scores.resize(json.size());
        for(size_t i = 0; i < json.size(); i++)
        {
            scores[i] = std::make_pair(json[i]["score"], json[i]["name"]);
        }

        return scores;
    }

    void storeLeaderboard(const std::filesystem::path& path, const std::vector<std::pair<size_t, std::string>>& scores)
    {
        nlohmann::json json;
        size_t i = 0;
        for(const auto& [score, name] : scores)
        {
            json[i]["score"] = score;
            json[i]["name"] = name;
            i++;
        }
        std::ofstream file(path);
        file << json;
    }


    bool loadAndAddPlayer(const std::filesystem::path& path, core::World& world)
    {
        try
        {
            const auto json = openJson(path);

            const auto start = Vec2d(json["stats"]["startX"], json["stats"]["startY"]);
            const auto velocity = Vec2d();
            const auto dim = Vec2d(json["stats"]["size"], json["stats"]["size"]);
            const auto speed = json["stats"]["speed"];
            const auto lives = json["stats"]["lives"];
            const auto color = util::Color::fromJson(json["stats"]["color"]);
            const auto texture = json["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(json["bullets"]);

            const auto id = world.addEntity<entities::Player>(std::tuple(start, velocity, dim, speed, lives, color, texture, bulletInfo));
            world.addViewToEntity<view::PlayerInfo>(id);
        }
        catch(std::exception& e)
        {
            return false;
        }
        return true;
    }

    bool loadAndAddShield(const std::filesystem::path& path, core::World& world)
    {
        try
        {
            const auto json = openJson(path);
            const auto dimensions = Vec2d(json["stats"]["dimX"], json["stats"]["dimY"]);
            const double lives = json["stats"]["lives"];
            const auto color = util::Color::fromJson(json["stats"]["color"]);
            const auto texture = json["stats"]["texture"];


            for(const auto& elem : json["shields"])
            {
                const auto posititon = Vec2d(elem["posX"], elem["posY"]);
                world.addEntity<entities::Shield>(std::tuple(posititon, dimensions, lives, color, texture));
            }
        }
        catch(std::exception& e)
        {
            return false;
        }
        return true;
    }

    bool loadAndAddPreview(const nlohmann::json& json, core::World& world, Vec2d pos)
    {
        try
        {
            const auto start = pos;
            const auto velocity = Vec2d();
            const auto dim = Vec2d(json["stats"]["size"], json["stats"]["size"]);
            const auto speed = 0.0;
            const auto lives = json["stats"]["lives"];
            const auto color = util::Color::fromJson(json["stats"]["color"]);
            const auto texture = json["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(json["bullets"]);

            world.addEntity<entities::Enemy>(std::tuple(start, velocity, dim, speed, lives, color, texture, bulletInfo));
        }
        catch(std::exception& e)
        {
            return false;
        }
        return true;
    }

    size_t loadAndAddSelection(const std::filesystem::path& path, core::World& world)
    {
        std::vector<nlohmann::json> choices;

        if(not std::filesystem::is_directory(path))
        {
            throw std::runtime_error("player folder directory does not exist");
        }
        for(const auto& elem : std::filesystem::directory_iterator(path.string()))
        {
            if(elem.path().filename().string()[0] == '.') continue;

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

    bool loadAndAddLevel(const std::filesystem::path& path, core::World& world)
    {
        try
        {
            const auto json = openJson(path);
            const auto start = Vec2d(-3.9, -2.9);

            const auto numEnemies = json["level"]["numEnemies"];
            const auto enemyJson = openJson("res/enemies/" + json["level"]["type"].get<std::string>() + ".json");

            const auto velocity = Vec2d(enemyJson["stats"]["horizontalSpeed"], enemyJson["stats"]["downSpeed"]);
            const auto dim = Vec2d(enemyJson["stats"]["size"], enemyJson["stats"]["size"]);
            const auto speed = enemyJson["stats"]["horizontalSpeed"];
            const auto lives = enemyJson["stats"]["lives"];

            const auto color = util::Color::fromJson(enemyJson["stats"]["color"]);

            const auto texture = enemyJson["stats"]["texture"];
            const auto bulletInfo = parseBulletInfo(enemyJson["bullets"]);

            auto curr = start + dim;

            for(size_t i = 0; i < numEnemies; i++)
            {
                world.addEntity<entities::Enemy>(std::tuple(curr, velocity, dim, speed, lives, color, texture, bulletInfo));

                // calculate next position
                if(curr.x > 2)
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
            return false;
        }
        return true;
    }

    bool loadAndAddScore(const std::filesystem::path& path, core::World& world)
    {
        const auto json = openJson(path);
        world.addObject<objects::Score>(std::tuple(Vec2d(json["x"], json["y"]), json["size"]));
        return true;
    }

    bool loadAndAddLeaderBoard(std::filesystem::path path, core::World& world, size_t score)
    {
        world.addObject<objects::Leaderboard>(std::tuple(std::move(path), score));
        return true;
    }
}
