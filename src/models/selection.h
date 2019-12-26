//============================================================================
// @name        : start.h
// @author      : Thomas Dooms
// @date        : 12/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "object.h"

namespace model
{
    // this model just keeps track of the current choice at the start
    class Selection : public Object
    {
    public:
        Selection(std::filesystem::path base, std::vector<std::string> ships) : base(std::move(base)), ships(std::move(ships)) {}

        void update([[maybe_unused]] core::World& world) override {}

        void choose(size_t index)
        {
            choice = index;
            send(Event::valueChanged);
        }

        void confirm()
        {
            confirmed = true;
        }

        [[nodiscard]] bool isConfirmed() const
        {
            return confirmed;
        }
        [[nodiscard]] size_t getChoice() const
        {
            return choice;
        }
        [[nodiscard]] size_t getNum() const
        {
            return ships.size();
        }

        [[nodiscard]] std::filesystem::path getPath() const
        {
            auto res = base / ships[choice];
            res.replace_extension("json");
            return res;
        }

    private:
        size_t choice = 0;
        bool confirmed = false;

        std::filesystem::path base{};
        std::vector<std::string> ships;
    };
}