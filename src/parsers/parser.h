//============================================================================
// @name        : parser.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once


#include "../models/spaceship.h"
#include <filesystem>

namespace parser
{
    nlohmann::json openJson(const std::filesystem::path& path);

    model::BulletData parseBulletInfo(const nlohmann::json& json);

    std::vector<std::pair<size_t, std::string>> loadLeaderboard(const std::filesystem::path& path);

    void storeLeaderboard(const std::filesystem::path& path, const std::vector<std::pair<size_t, std::string>>& scores);


    bool loadAndAddPlayer(const std::filesystem::path& path, core::World& world);

    bool loadAndAddShield(const std::filesystem::path& path, core::World& world);

    bool loadAndAddPreview(const nlohmann::json& json, core::World& world, Vec2d pos);

    size_t loadAndAddSelection(const std::filesystem::path& path, core::World& world);

    bool loadAndAddLevel(const std::filesystem::path& path, core::World& world);

    bool loadAndAddScore(const std::filesystem::path& path, core::World& world);

    bool loadAndAddLeaderBoard(std::filesystem::path path, core::World& world, size_t score);
}
