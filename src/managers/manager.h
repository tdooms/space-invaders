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


class SfManager
{
public:

    static std::shared_ptr<sf::Texture> getTexture(const std::string& name)
    {
        static const std::filesystem::path base = "textures";
        static const std::string extension = "jpg";

        const auto iter = textures.find(name);
        if(iter == textures.end())
        {
            const auto path = location(base, name, extension);
            auto texture = std::make_shared<sf::Texture>();

            bool success = texture->loadFromFile(path);
            if(not success) throw std::runtime_error("could not load texture: " + path.string());

            textures.emplace(name, texture);
            return texture;
        }
        else return iter->second;
    }

    static std::shared_ptr<sf::Font> getFont(const std::string& name)
    {
        static const std::filesystem::path base = "fonts";
        static const std::string extension = "otf";

        const auto iter = fonts.find(name);
        if(iter == fonts.end())
        {
            const auto path = location(base, name, extension);
            auto font = std::make_shared<sf::Font>();

            bool success = font->loadFromFile(path);
            if(not success) throw std::runtime_error("could not load texture: " + path.string());

            fonts.emplace(name, font);
            return font;
        }
        else return iter->second;
    }

private:

    static std::filesystem::path location(const std::filesystem::path& base, const std::string& name, const std::string& extension)
    {
        auto file = base / name;
        file.replace_extension(extension);

        if(!std::filesystem::exists(file))
        {
            throw std::runtime_error("object with path: " + base.string() + " and name: " + name + " not found");
        }
        else return file;
    }

    static inline std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures {};
    static inline std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts {};
};