//============================================================================
// @name        : empty.h
// @author      : Thomas Dooms
// @date        : 12/13/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"

namespace controller
{
    class Empty : public controller::Abstract
    {
    public:
        Empty() : Abstract(nullptr, nullptr) {}

        void update() override {}
    };
}