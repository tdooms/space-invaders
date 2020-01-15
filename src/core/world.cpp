//============================================================================
// @name        : world.cpp
// @author      : Thomas Dooms
// @date        : 12/26/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#include "world.h"

namespace core {
World::World() {
  worldModel = std::make_shared<model::World>();
  worldView = std::make_shared<view::World>(worldModel);
  worldController = std::make_shared<controller::World>(worldModel, worldView);

  enemies = {};
}

Stage World::update() {
  stage = Stage::normal;

  worldController->update();
  worldModel->update(*this);

  collision::detect(worldModel);
  tryRemoveEntities();

  return stage;
}

size_t World::getScore() { return score; }

void World::draw(sf::RenderWindow &window) { worldView->draw(window); }

void World::tryRemoveEntities() {
  std::vector<std::pair<size_t, size_t>> toRemove;
  for (const auto &[id, model] : *worldModel) {
    if (model->getReaction() == model::Reaction::remove) {
      toRemove.emplace_back(id, model->getScoreChange());
    } else if (model->getReaction() == model::Reaction::defeat) {
      stage = Stage::defeat;
    } else if (model->getReaction() == model::Reaction::victory) {
      stage = Stage::victory;
    }
  }

  for (const auto &[id, scoreChange] : toRemove) {
    score += scoreChange;

    worldModel->erase(id);
    worldView->erase(id);
    worldController->erase(id);

    enemies.erase(id);
  }

  if (enemies.empty())
    stage = Stage::victory;
}
} // namespace core