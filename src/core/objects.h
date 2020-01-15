//============================================================================
// @name        : objects.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../controllers/leaderboard.h"
#include "../controllers/particles.h"
#include "../controllers/score.h"
#include "../controllers/selection.h"
#include "../controllers/text.h"

namespace objects {
// again, these are metaclasses used for adding objects with addObject()
struct Text {
  using model = model::Text;
  using view = view::Text;
  using controller = controller::Text;
};

struct Score {
  using model = model::Score;
  using view = view::Score;
  using controller = controller::Score;
};

struct Particles {
  using model = model::Particles;
  using view = view::Particles;
  using controller = controller::Particles;
};

struct Selection {
  using model = model::Selection;
  using view = view::Selection;
  using controller = controller::Selection;
};

struct Leaderboard {
  using model = model::Leaderboard;
  using view = view::Leaderboard;
  using controller = controller::Leaderboard;
};
} // namespace objects