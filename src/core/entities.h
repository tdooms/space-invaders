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
#include "../controllers/empty.h"

#include "../models/text.h"
#include "../views/text.h"


namespace Object
{
    struct Text
    {
        using model = model::Text;
        using view = view::Text;
    };
}

namespace Entity
{
    enum Type : size_t
    {
        player, enemy, playerProjectile, enemyProjectile
    };

    struct Player
    {
        using model = model::Spaceship;
        using view = view::Spaceship;
        using controller = controller::Player;
        using type = std::integral_constant<Type, Type::player>;
    };

    struct Enemy
    {
        using model = model::Spaceship;
        using view = view::Spaceship;
        using controller = controller::Enemy;
        using type = std::integral_constant<Type, Type::enemy>;
    };

    struct PlayerProjectile
    {
        using model = model::Projectile;
        using view = view::Projectile;
        using controller = controller::Projectile;
        using type = std::integral_constant<Type, Type::playerProjectile>;
    };

    struct EnemyProjectile
    {
        using model = model::Projectile;
        using view = view::Projectile;
        using controller = controller::Projectile;
        using type = std::integral_constant<Type, Type::enemyProjectile>;
    };

}