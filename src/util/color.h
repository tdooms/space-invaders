//============================================================================
// @name        : color.h
// @author      : Thomas Dooms
// @date        : 12/17/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <json.hpp>

namespace util {
// very simple color class with some helper functions
struct Color {
  Color() noexcept : r(0), g(0), b(0), a(255) {}
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
      : r(r), g(g), b(b), a(a) {}

  static Color lerp(Color lhs, Color rhs, double a) {
    if (a > 1)
      a = 1;
    else if (a < 0)
      a = 0;

    auto r = static_cast<uint8_t>(lhs.r + a * (rhs.r - lhs.r));
    auto g = static_cast<uint8_t>(lhs.g + a * (rhs.g - lhs.g));
    auto b = static_cast<uint8_t>(lhs.b + a * (rhs.b - lhs.b));
    return Color(r, g, b);
  }

  static Color addAlpha(Color color, uint8_t a) noexcept {
    return Color(color.r, color.g, color.b, a);
  }

  static sf::Color toSfColor(Color color) noexcept {
    return sf::Color(color.r, color.g, color.b, color.a);
  }

  static Color fromJson(const nlohmann::json &json) {
    return Color(json[0], json[1], json[2]);
  }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};
static inline Color White = Color(255, 255, 255);
static inline Color Black = Color(0, 0, 0);
} // namespace util
