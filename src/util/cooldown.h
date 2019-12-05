//============================================================================
// @name        : cooldown.h
// @author      : Thomas Dooms
// @date        : 12/4/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "stopwatch.h"

namespace util
{
    struct Cooldown
    {
    public:
        Cooldown() = default;

        void start(std::chrono::seconds duration)
        {
            dur = duration;
            begin = Stopwatch::get().time();
        }

        void start(std::chrono::milliseconds duration)
        {
            dur = duration;
            begin = Stopwatch::get().time();
        }

        bool neverStarted()
        {
            return begin == std::chrono::system_clock::time_point();
        }

        bool done()
        {
            const auto diff = Stopwatch::get().time() - begin;
            return diff > dur;
        }

    private:
        std::chrono::system_clock::time_point begin;
        std::chrono::duration<size_t, std::milli> dur;
    };
}