//============================================================================
// @name        : game.h
// @author      : Thomas Dooms
// @date        : 11/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <chrono>
#include <memory>
#include <unordered_set>

#include "../controllers/abstract.h"
#include "../controllers/world.h"
#include "entities.h"

using namespace std::chrono_literals;

namespace core
{

    enum class Stage
    {
        start,
        game,
        over,
        victory
    };

class Game
{
public:

    template<typename Entity, typename... ModelArgs, typename... ViewArgs, typename... ControllerArgs>
    size_t addEntity(std::tuple<ModelArgs...>&& modelArgs = {}, std::tuple<ViewArgs...>&& viewArgs = {}, std::tuple<ControllerArgs...>&& controllerArgs = {})
    {
        // we need lambda functions to wrap the make shared template function, this way it doesn't stay in the way of template argument resolution for std::apply
        const auto modelmaker = [](auto... args){ return std::make_shared<typename Entity::model>(args...); };
        const auto viewmaker = [](auto... args){ return std::make_shared<typename Entity::view>(args...); };
        const auto controllermaker = [](auto... args){ return std::make_shared<typename Entity::controller>(args...); };

        // we call apply to apply the tuple arguments to the lambda's to make our unique pointers
        auto model = std::apply(modelmaker, std::tuple_cat(std::make_tuple(Entity::type::value, Entity::side::value), modelArgs));
        auto view = std::apply(viewmaker, std::tuple_cat(std::make_tuple(model), viewArgs));
        auto controller = std::apply(controllermaker, std::tuple_cat(std::make_tuple(model, view), controllerArgs));

        if(Entity::side::value == model::Entity::Side::enemy and Entity::type::value == model::Entity::Type::spaceship)
        {
            enemies.emplace(currId);
        }

        model->addObserver(view);

        worldModel->emplace(currId, std::move(model));
        worldView->emplace(currId, std::move(view));
        worldController->emplace(currId, std::move(controller));

        return currId++;
    }

    template<typename View, typename... ViewArgs>
    void addViewToEntity(size_t id, ViewArgs&&... args)
    {
        auto model = worldModel->find(id)->second;
        auto view = std::make_shared<View>(model, std::forward<ViewArgs>(args)...);

        model->addObserver(view);
        worldView->emplace(id, std::move(view));
    }


    template<typename Object, typename... ModelArgs, typename... ViewArgs>
    void addObject(std::tuple<ModelArgs...>&& modelArgs = {}, std::tuple<ViewArgs...>&& viewArgs = {})
    {
        const auto modelmaker = [](auto... args){ return std::make_shared<typename Object::model>(args...); };
        const auto viewmaker = [](auto... args){ return std::make_shared<typename Object::view>(args...); };

        auto model = std::apply(modelmaker, modelArgs);
        auto view = std::apply(viewmaker, std::tuple_cat(std::make_tuple(model), viewArgs));

        model->addObserver(view);

        worldModel->emplace(currId, std::move(model));
        worldView->emplace(currId, std::move(view));
    }

    void tryRemoveEntities();

    void tryLoadLevel();

    // The engine works on a fixed update collision, where each update is 'frameTime' seconds of time.
    // Because of this, there can be a situation where there is, for instance, a fixed update of 16ms,
    // but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
    // stored in unprocessedTime, and then the engine processes as much time as it can. Any
    // unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
    void start();

private:
    std::shared_ptr<model::World> worldModel;
    std::shared_ptr<view::World> worldView;
    std::shared_ptr<controller::World> worldController;

    std::unordered_set<size_t> enemies;
    Stage stage = Stage::game;

    size_t currId = 1;
    size_t score = 0;

    bool gameOverAdded = false;
};


}