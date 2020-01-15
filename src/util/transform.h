//============================================================================
// @name        : transform.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "vec.h"
#include <SFML/System/Vector2.hpp>

namespace util {
// singleton transform class with a few handy functions
class Transform {
public:
  // get singleton
  [[nodiscard]] static Transform &get() noexcept {
    static Transform instance;
    return instance;
  }

  [[nodiscard]] sf::Vector2f transform(Vec2d coordinates) const noexcept {
    return sf::Vector2f(
        static_cast<float>((coordinates.x + 4) * screenSize.x / 8.0),
        static_cast<float>((coordinates.y + 3) * screenSize.y / 6.0));
  }
  [[nodiscard]] sf::Vector2f scale(Vec2d coordinates) const noexcept {
    return sf::Vector2f(static_cast<float>(coordinates.x * screenSize.x / 8.0),
                        static_cast<float>(coordinates.y * screenSize.y / 6.0));
  }
  [[nodiscard]] sf::Vector2f scale(double xCoordinate, double yCoordinate) const
      noexcept {
    return sf::Vector2f(static_cast<float>(xCoordinate * screenSize.x / 8.0),
                        static_cast<float>(yCoordinate * screenSize.y / 6.0));
  }
  [[nodiscard]] float scale(double coordinate) const noexcept {
    return static_cast<float>(coordinate * screenSize.x / 8.0);
  }

  [[nodiscard]] sf::Vector2u getScreenSize() const noexcept {
    return sf::Vector2u(static_cast<unsigned int>(screenSize.x),
                        static_cast<unsigned int>(screenSize.y));
  }

  // delete unnecessary operators/constructors
  Transform(const Transform &) = delete;
  void operator=(const Transform &) = delete;
  Transform(Transform &&) = delete;
  void operator=(Transform &&) = delete;

private:
  Transform() = default;
  Vec2d screenSize = {800, 600};
};
} // namespace util
