//============================================================================
// @name        : leaderboard.h
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "object.h"
#include "../parsers/json.h"

#include <fstream>
#include <filesystem>

namespace model
{
    class Leaderboard : public Object
    {
    public:
        explicit Leaderboard(const std::filesystem::path& path, size_t score) : path(path), score(score)
        {
            std::ifstream file(this->path);
            json = nlohmann::json::parse(file);
            scores.resize(json.size());

            for(size_t i = 0; i < json.size(); i++)
            {
                scores[i] = std::make_pair(json[i]["score"], json[i]["name"]);
            }
            sortScores();

            showName = highscore();
        }

        void update([[maybe_unused]] core::World& world) override {}

        bool highscore()
        {
            return score > scores.back().first;
        }

        void sortScores()
        {
            constexpr auto comp = [](const auto& lhs, const auto& rhs){ return lhs.first < rhs.first; };
            std::sort(scores.rbegin(), scores.rend(), comp);
        }

        void complete()
        {
            if(not highscore()) return;
            scores.back() = std::make_pair(score, name);
            sortScores();
            writeBack();

            showName = false;
            send(Event::valueChanged);
        }

        void writeBack()
        {
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

        [[nodiscard]] char getChar() const noexcept
        {
            return current;
        }
        [[nodiscard]] char getPrevChar() const noexcept
        {
            if(current == 'a') return 'z';
            else return static_cast<char>(current - 1);
        }
        [[nodiscard]] char getNextChar() const noexcept
        {
            if(current == 'z') return 'a';
            else return static_cast<char>(current + 1);
        }

        [[nodiscard]] const std::string& getName() const noexcept
        {
            return name;
        }

        [[nodiscard]] const auto& getScores() const noexcept
        {
            return scores;
        }

        void nextChar() noexcept
        {
            if(current == 'z') current = 'a';
            else current++;
            send(Event::valueChanged);
        }
        void prevChar() noexcept
        {
            if(current == 'a') current = 'z';
            else current--;
            send(Event::valueChanged);
        }

        void appendChar()
        {
            if(name.size() > 12) return;
            name += current;
            send(Event::valueChanged);
        }
        void popChar()
        {
            if(name.empty()) return;
            name.pop_back();
            send(Event::valueChanged);
        }

        bool getShowName() const noexcept
        {
            return showName;
        }

    private:
        std::filesystem::path path;
        nlohmann::json json;
        std::vector<std::pair<size_t, std::string>> scores;

        std::string name;
        size_t score;

        char current = 'a';

        bool showName;
    };
}