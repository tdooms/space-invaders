//============================================================================
// @name        : abstract.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../observer/subject.h"
#include <optional>

namespace core {
class World;
}

namespace model {
// type indicating the type of the entity model
enum class Type { spaceship, projectile, shield };

// type indicating the side of the entity model)
enum class Side { player, enemy, neutral };

// type indicating how the world should react to the model
enum class Reaction { none, remove, victory, defeat };

class Abstract : public Subject {
public:
  Abstract() = default;
  virtual ~Abstract() = default;

  [[nodiscard]] Reaction getReaction() { return reaction; }
  [[nodiscard]] int getScoreChange() { return scoreChange; }

  virtual void update(core::World &world) = 0;

protected:
  Reaction reaction = Reaction::none;
  int scoreChange = 0;
};
} // namespace model