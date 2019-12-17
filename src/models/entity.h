//============================================================================
// @name        : entity.h
// @author      : Thomas Dooms
// @date        : 12/14/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"

namespace model
{
    class Entity : public model::Abstract
    {
    public:
        Entity(Type type, Side side) : type(type), side(side) {}

    protected:
        Type type;
        Side side;
    };
}