//============================================================================
// @name        : texture.h
// @author      : Thomas Dooms
// @date        : 11/24/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <unordered_map>
#include <memory>
#include <filesystem>

#include <SFML/Graphics.hpp>

namespace manager
{
class Texture
{
public:
    static std::shared_ptr<sf::Texture> get(const std::string& name);

private:
    static std::filesystem::path location(const std::string& name);

    static inline std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures {};
};
}