//============================================================================
// @name        : vec.h
// @author      : Thomas Dooms
// @date        : 12/5/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <array>
#include <cmath>

struct Vec2d
{
    Vec2d();
    Vec2d(double first, double second);

    static Vec2d fromPolar(double length, double angle) noexcept;

    Vec2d& normalize() noexcept;
    [[nodiscard]] Vec2d normalized() const noexcept;

    [[nodiscard]] double length() const noexcept;

    Vec2d& operator*=(double scalar) noexcept;
    Vec2d& operator/=(double scalar) noexcept;
    Vec2d& operator+=(Vec2d rhs) noexcept;
    Vec2d& operator-=(Vec2d rhs) noexcept;

    friend Vec2d operator+(Vec2d lhs, Vec2d rhs) noexcept;
    friend Vec2d operator-(Vec2d lhs, Vec2d rhs) noexcept;

    friend Vec2d operator*(Vec2d lhs, double scalar) noexcept;
    friend Vec2d operator*(double scalar, Vec2d rhs) noexcept;

    friend Vec2d operator/(Vec2d lhs, double scalar) noexcept;
    friend Vec2d operator/(double scalar, Vec2d rhs) noexcept;

    friend double dot(Vec2d lhs, Vec2d rhs) noexcept;
    friend double dist(Vec2d lhs, Vec2d rhs) noexcept;
    friend Vec2d lerp(Vec2d lhs, Vec2d rhs, double a) noexcept;

    double x;
    double y;
};







