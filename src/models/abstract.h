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
#include "../core/game.h"

namespace model
{
    class Abstract : public Subject
    {
    public:
        Abstract() = default;
        virtual ~Abstract() = default;
        virtual void update(core::Game& game) = 0;
    };
}