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

        void start(std::chrono::seconds duration)
        {
            started = true;
            dur = duration;
            begin = Stopwatch::get().time();
        }

        void start(std::chrono::milliseconds duration)
        {
            started = true;
            dur = duration;
            begin = Stopwatch::get().time();
        }

        bool neverStarted()
        {
            return begin == std::chrono::system_clock::time_point();
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

        void printUntilDone()
        {
            std::cout << "diff: " << std::chrono::duration_cast<std::chrono::milliseconds>(Stopwatch::get().time() - begin).count() << "ms\n";
            std::cout << "duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << "ms\n\n";
        }

    private:
        std::chrono::system_clock::time_point begin;
        std::chrono::duration<size_t, std::milli> dur;
        bool started = false;
    };
}