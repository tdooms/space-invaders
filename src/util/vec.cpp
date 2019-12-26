//============================================================================
// @name        : vec.cpp
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================

#include "vec.h"
#include <random.hpp>

Vec2d::Vec2d() : x(0), y(0) {}
Vec2d::Vec2d(double first, double second) : x(first), y(second) {}

Vec2d Vec2d::fromPolar(double length, double angle) noexcept
{
    return Vec2d(std::cos(angle), std::sin(angle)) * length;
}

Vec2d Vec2d::randomUnit() noexcept
{
    using Random = effolkronium::random_static;
    return fromPolar(1, Random::get(0.0, M_PI));
}

Vec2d& Vec2d::normalize() noexcept
{
    return *this /= length();
}
Vec2d Vec2d::normalized() const noexcept
{
    return *this / length();
}
double Vec2d::length() const noexcept
{
    return std::sqrt(x*x + y*y);
}

Vec2d& Vec2d::operator*=(double scalar) noexcept
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}
Vec2d& Vec2d::operator/=(double scalar) noexcept
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Vec2d& Vec2d::operator+=(Vec2d rhs) noexcept
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}
Vec2d& Vec2d::operator-=(Vec2d rhs) noexcept
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vec2d operator+(Vec2d lhs, Vec2d rhs) noexcept
{
    return Vec2d(lhs.x + rhs.x, lhs.y + rhs.y);
}
Vec2d operator-(Vec2d lhs, Vec2d rhs) noexcept
{
    return Vec2d(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2d operator*(Vec2d lhs, double scalar) noexcept
{
    return lhs *= scalar;
}
Vec2d operator*(double scalar, Vec2d rhs) noexcept
{
    return rhs *= scalar;
}
Vec2d operator/(Vec2d lhs, double scalar) noexcept
{
    return lhs /= scalar;
}
Vec2d operator/(double scalar, Vec2d rhs) noexcept
{
    return rhs /= scalar;
}

double dot(Vec2d lhs, Vec2d rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double dist(Vec2d lhs, Vec2d rhs) noexcept
{
    return (rhs - lhs).length();
}

Vec2d lerp(Vec2d lhs, Vec2d rhs, double a) noexcept
{
    return lhs + (rhs - lhs) * a;
}
