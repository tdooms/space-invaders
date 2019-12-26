//============================================================================
// @name        : clock.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <chrono>

namespace util
{
    // singleton pattern stopwatch
    class Stopwatch
    {
    public:
        // get singleton
        [[nodiscard]] static Stopwatch& get() noexcept
        {
            static Stopwatch instance;
            return instance;
        }

        [[nodiscard]] auto time() const noexcept
        {
            return std::chrono::system_clock::now();
        }

        Stopwatch() noexcept = default;

        // delete unnecessary operators/constructors
        Stopwatch(const Stopwatch&) = delete;
        void operator=(const Stopwatch&) = delete;
        Stopwatch(Stopwatch&&) = delete;
        void operator=(Stopwatch&&) = delete;
    };
}





