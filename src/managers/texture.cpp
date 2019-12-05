//============================================================================
// @name        : texture.cpp
// @author      : Thomas Dooms
// @date        : 11/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "texture.h"

namespace manager
{
    std::shared_ptr<sf::Texture> Texture::get(const std::string& name)
    {
        const auto iter = textures.find(name);
        if(iter == textures.end())
        {
            const auto path = location(name);
            auto texture = std::make_shared<sf::Texture>();

            bool success = texture->loadFromFile(path);
            if(not success) throw std::runtime_error("could not load texture: " + path.string());

            textures.emplace(name, texture);
            return texture;
        }
        else
        {
            return iter->second;
        }
    }

    std::filesystem::path Texture::location(const std::string& name)
    {
        static std::filesystem::path path = "textures";
        const auto file = path / name;
        if(!std::filesystem::exists(file))
        {
            throw std::runtime_error("texture with name: " + name + " not found");
        }
        else return file;
    }
}