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

// these are a collection of functions which related to parsing and adding stuff
// to the world

// as IO exceptions are very important most of the time I make a distinction
// between recoverable and non-recoverable errors.

// sometimes i just throw, and sometime i catch the errors and return false to
// indicate something has failed. in the case of a level loading error, the game
// can stop and we say you 'finished' the game.

namespace parser {
nlohmann::json openJson(const std::filesystem::path &path);

model::BulletData parseBulletInfo(const nlohmann::json &json);

std::vector<std::pair<size_t, std::string>>
loadLeaderboard(const std::filesystem::path &path);

void storeLeaderboard(
    const std::filesystem::path &path,
    const std::vector<std::pair<size_t, std::string>> &scores);

bool loadAndAddPlayer(const std::filesystem::path &path, core::World &world);

bool loadAndAddShield(const std::filesystem::path &path, core::World &world);

bool loadAndAddPreview(const nlohmann::json &json, core::World &world,
                       Vec2d pos);

size_t loadAndAddSelection(const std::filesystem::path &path,
                           core::World &world);

bool loadAndAddLevel(const std::filesystem::path &path, core::World &world);

bool loadAndAddScore(const std::filesystem::path &path, core::World &world);

bool loadAndAddLeaderBoard(const std::filesystem::path &path,
                           core::World &world, size_t score);
} // namespace parser
