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

namespace view { class World; }
namespace model { class World; }
namespace controller { class World; }

using namespace std::chrono_literals;
using namespace std::chrono;

namespace core
{

struct spaceship;
struct projectile;
struct enemy;

class Game
{
public:
    template<typename Object, typename... ViewArgs, typename... ModelArgs, typename... ControllerArgs>
    void addObject(std::tuple<ViewArgs...>&& viewArgs = {}, std::tuple<ModelArgs...>&& modelArgs = {}, std::tuple<ControllerArgs...>&& controllerArgs = {});

    // The engine works on a fixed update system, where each update is 'frameTime' seconds of time.
    // Because of this, there can be a situation where there is, for instance, a fixed update of 16ms,
    // but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
    // stored in unprocessedTime, and then the engine processes as much time as it can. Any
    // unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
    void start();

private:
    std::shared_ptr<view::World> worldView;
    std::shared_ptr<model::World> worldModel;
    std::shared_ptr<controller::World> worldController;
};


}