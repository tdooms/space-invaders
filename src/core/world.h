//============================================================================
// @name        : world.h
// @author      : Thomas Dooms
// @date        : 12/16/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once


#include <unordered_set>
#include "../collision/detector.h"
#include "game.h"

namespace core
{
    enum class Stage
    {
        start,
        normal,
        defeat,
        done
    };

    class World
    {
    public:
        World()
        {
            worldModel = std::make_shared<model::World>();
            worldView = std::make_shared<view::World>(worldModel);
            worldController = std::make_shared<controller::World>(worldModel, worldView);

            enemies = {};
        }

        Stage update()
        {
            worldController->update();
            worldModel->update(*this);

            collision::detect(worldModel);
            tryRemoveEntities();

            if(enemies.empty()) stage = Stage::done;
            else stage = Stage::normal;

            return stage;
        }

        size_t getScore()
        {
            return score;
        }

        auto findModel(size_t id)
        {
            return worldModel->find(id);
        }

        void draw(sf::RenderWindow& window)
        {
            worldView->draw(window);
        }

        template<typename Entity, typename... ModelArgs, typename... ViewArgs, typename... ControllerArgs>
        size_t addEntity(std::tuple<ModelArgs...>&& modelArgs = {}, std::tuple<ViewArgs...>&& viewArgs = {}, std::tuple<ControllerArgs...>&& controllerArgs = {})
        {
            const auto tuple = std::make_tuple(Entity::type::value, Entity::side::value);
            const auto id = addObject<Entity>(std::tuple_cat(tuple, modelArgs), std::forward<std::tuple<ViewArgs...>>(viewArgs), std::forward<std::tuple<ControllerArgs...>>(controllerArgs));

            if(Entity::type::value == model::Type::spaceship)
            {
                if(Entity::side::value == model::Side::enemy) enemies.emplace(currId);
                else if(Entity::side::value == model::Side::player) players.emplace(currId);
            }
            return id;
        }

        template<typename View, typename... ViewArgs>
        void addViewToEntity(size_t id, ViewArgs&&... args)
        {
            auto model = worldModel->find(id)->second;
            auto view = std::make_shared<View>(model, std::forward<ViewArgs>(args)...);

            model->addObserver(view);
            worldView->emplace(id, std::move(view));
        }


        template<typename Object, typename... ModelArgs, typename... ViewArgs, typename... ControllerArgs>
        size_t addObject(std::tuple<ModelArgs...>&& modelArgs = {}, std::tuple<ViewArgs...>&& viewArgs = {}, std::tuple<ControllerArgs...>&& controllerArgs = {})
        {
            // we need lambda functions to wrap the make shared template function, this way it doesn't stay in the way of template argument resolution for std::apply
            const auto modelmaker = [](auto... args){ return std::make_shared<typename Object::model>(args...); };
            const auto viewmaker = [](auto... args){ return std::make_shared<typename Object::view>(args...); };
            const auto controllermaker = [](auto... args){ return std::make_shared<typename Object::controller>(args...); };

            // we call apply to apply the tuple arguments to the lambda's to make our unique pointers
            auto model = std::apply(modelmaker, modelArgs);
            auto view = std::apply(viewmaker, std::tuple_cat(std::make_tuple(model), viewArgs));
            auto controller = std::apply(controllermaker, std::tuple_cat(std::make_tuple(model, view), controllerArgs));

            model->addObserver(view);

            worldModel->emplace(currId, std::move(model));
            worldView->emplace(currId, std::move(view));
            worldController->emplace(currId, std::move(controller));

            return currId++;
        }

    private:

        void tryRemoveEntities()
        {
            std::vector<std::pair<size_t, model::RemoveData>> toRemove;
            for(const auto& [id, model] : *worldModel)
            {
                const auto data = model->getRemoveData();
                if(data.has_value()) toRemove.emplace_back(id, data.value());
            }

            for(const auto [id, data] : toRemove)
            {
                if(data.isGameOver()) stage = Stage::defeat;
                score += data.scoreChange;

                if(data.isParticles())
                {
                    addObject<objects::Particles>(std::tuple(data.pos, data.dim, data.vel, data.numParticles));
                }

                worldModel->erase(id);
                worldView->erase(id);
                worldController->erase(id);

                enemies.erase(id);
            }
        }

        std::shared_ptr<model::World> worldModel;
        std::shared_ptr<view::World> worldView;
        std::shared_ptr<controller::World> worldController;

        std::unordered_set<size_t> enemies;
        std::unordered_set<size_t> players;

        size_t currId = 0;
        size_t score = 0;

        Stage stage = Stage::start;
    };
}