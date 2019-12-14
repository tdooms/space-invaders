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
#include <iostream>

namespace util
{
    struct Cooldown
    {
    public:
        Cooldown() = default;

        void start(std::chrono::milliseconds duration)
        {
            started = true;
            dur = duration;
            begin = Stopwatch::get().time();
        }

        void start()
        {
            started = true;
            begin = Stopwatch::get().time();
        }

        bool done()
        {
            if(not started)
            {
                started = false;
                return true;
            }
            else
            {
                const auto diff = Stopwatch::get().time() - begin;
                return diff > dur;
            }
        }

    private:
        std::chrono::system_clock::time_point begin;
        std::chrono::duration<size_t, std::milli> dur;
        bool started = false;
    };
}