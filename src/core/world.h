//============================================================================
// @name        : world.h
// @author      : Thomas Dooms
// @date        : 12/16/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../collision/detector.h"
#include "../controllers/world.h"
#include <unordered_set>

namespace core {
enum class Stage { start, normal, defeat, victory };

class World {
public:
  World();

  auto findModel(size_t id) { return worldModel->find(id); }

  Stage update();

  size_t getScore();

  void draw(sf::RenderWindow &window);

  // these templated functions probably seem very complicated becaause they need
  // to be very general. in essence all they do is take the parameters for the
  // model view and controllers and use them to construct and add them to the
  // world.
  template <typename Object, typename... ModelArgs, typename... ViewArgs,
            typename... ControllerArgs>
  size_t addObject(std::tuple<ModelArgs...> &&modelArgs = {},
                   std::tuple<ViewArgs...> &&viewArgs = {},
                   std::tuple<ControllerArgs...> &&controllerArgs = {});

  template <typename Entity, typename... ModelArgs, typename... ViewArgs,
            typename... ControllerArgs>
  size_t addEntity(std::tuple<ModelArgs...> &&modelArgs = {},
                   std::tuple<ViewArgs...> &&viewArgs = {},
                   std::tuple<ControllerArgs...> &&controllerArgs = {});

  template <typename View, typename... ViewArgs>
  void addViewToEntity(size_t id, ViewArgs &&... args);

private:
  void tryRemoveEntities();

  std::shared_ptr<model::World> worldModel;
  std::shared_ptr<view::World> worldView;
  std::shared_ptr<controller::World> worldController;

  std::unordered_set<size_t> enemies;
  std::unordered_set<size_t> players;

  size_t currId = 0;
  size_t score = 0;

  Stage stage = Stage::start;
};

template <typename Object, typename... ModelArgs, typename... ViewArgs,
          typename... ControllerArgs>
size_t World::addObject(std::tuple<ModelArgs...> &&modelArgs,
                        std::tuple<ViewArgs...> &&viewArgs,
                        std::tuple<ControllerArgs...> &&controllerArgs) {
  // we need lambda functions to wrap the make shared template function, this
  // way it doesn't stay in the way of template argument resolution for
  // std::apply
  const auto modelmaker = [](auto... args) {
    return std::make_shared<typename Object::model>(args...);
  };
  const auto viewmaker = [](auto... args) {
    return std::make_shared<typename Object::view>(args...);
  };
  const auto controllermaker = [](auto... args) {
    return std::make_shared<typename Object::controller>(args...);
  };

  // we call apply to apply the tuple arguments to the lambda's to make our
  // shared pointers
  auto model = std::apply(modelmaker, modelArgs);
  auto view =
      std::apply(viewmaker, std::tuple_cat(std::make_tuple(model), viewArgs));
  auto controller =
      std::apply(controllermaker,
                 std::tuple_cat(std::make_tuple(model, view), controllerArgs));

  model->addObserver(view);

  worldModel->emplace(currId, std::move(model));
  worldView->emplace(currId, std::move(view));
  worldController->emplace(currId, std::move(controller));

  return currId++;
}

template <typename Entity, typename... ModelArgs, typename... ViewArgs,
          typename... ControllerArgs>
size_t World::addEntity(std::tuple<ModelArgs...> &&modelArgs,
                        std::tuple<ViewArgs...> &&viewArgs,
                        std::tuple<ControllerArgs...> &&controllerArgs) {
  const auto tuple = std::make_tuple(Entity::type::value, Entity::side::value);
  const auto id = addObject<Entity>(
      std::tuple_cat(tuple, modelArgs),
      std::forward<std::tuple<ViewArgs...>>(viewArgs),
      std::forward<std::tuple<ControllerArgs...>>(controllerArgs));

  if (Entity::type::value == model::Type::spaceship) {
    if (Entity::side::value == model::Side::enemy)
      enemies.emplace(id);
    else if (Entity::side::value == model::Side::player)
      players.emplace(id);
  }
  return id;
}

template <typename View, typename... ViewArgs>
void World::addViewToEntity(size_t id, ViewArgs &&... args) {
  auto model = worldModel->find(id)->second;
  auto view = std::make_shared<View>(model, std::forward<ViewArgs>(args)...);

  model->addObserver(view);
  worldView->emplace(id, std::move(view));
}
} // namespace core