//============================================================================
// @name        : random.h
// @author      : Thomas Dooms
// @date        : 12/12/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <random>

namespace util
{
    // A simple random class with some special utilities.
    class Random
    {
    public:
        // get singleton
        [[nodiscard]] static Random& get() noexcept
        {
            static Random instance;
            return instance;
        }

        template<typename Type = double>
        [[nodiscard]] Type between(Type min, Type max) noexcept
        {
            if constexpr (std::is_floating_point_v<Type>)
            {
                std::uniform_real_distribution<Type> distribution(min, max);
                return distribution(twister);
            }
            else if constexpr (std::is_integral_v<Type>)
            {
                std::uniform_int_distribution<Type> distribution(min, max);
                return distribution(twister);
            }
            else
            {
                static_assert(std::is_arithmetic_v<Type>, "random values between non-arithmetic types is nonsensical");
            }
        }

        // delete unnecessary operators/constructors
        Random(const Random&) = delete;
        void operator=(const Random&) = delete;
        Random(Random&&) = delete;
        void operator=(Random&&) = delete;

    private:
        explicit Random()
        {
            std::random_device device;
            twister = std::mt19937(device());
        }
        std::mt19937 twister;
    };
}