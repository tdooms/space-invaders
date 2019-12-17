//============================================================================
// @name        : entities.h
// @author      : Thomas Dooms
// @date        : 12/11/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../controllers/player.h"
#include "../controllers/enemy.h"
#include "../controllers/projectile.h"
#include "../controllers/shield.h"

#include "../models/entity.h"


namespace entities
{
    using namespace model;

    struct Player
    {
        using model = model::Spaceship;
        using view = view::Spaceship;
        using controller = controller::Player;

        using type = std::integral_constant<Type, Type::spaceship>;
        using side = std::integral_constant<Side, Side::player>;
    };

    struct Enemy
    {
        using model = model::Spaceship;
        using view = view::Spaceship;
        using controller = controller::Enemy;

        using type = std::integral_constant<Type, Type::spaceship>;
        using side = std::integral_constant<Side, Side::enemy>;
    };

    struct Shield
    {
        using model = model::Shield;
        using view = view::Shield;
        using controller = controller::Shield;

        using type = std::integral_constant<Type, Type::shield>;
        using side = std::integral_constant<Side, Side::neutral>;
    };

    struct PlayerProjectile
    {
        using model = model::Projectile;
        using view = view::Projectile;
        using controller = controller::Projectile;

        using type = std::integral_constant<Type, Type::projectile>;
        using side = std::integral_constant<Side, Side::player>;
    };

    struct EnemyProjectile
    {
        using model = model::Projectile;
        using view = view::Projectile;
        using controller = controller::Projectile;

        using type = std::integral_constant<Type, Type::projectile>;
        using side = std::integral_constant<Side, Side::enemy>;
    };

}