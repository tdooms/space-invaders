//============================================================================
// @name        : objects.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../models/text.h"
#include "../views/text.h"

#include "../models/particles.h"
#include "../views/particles.h"

namespace objects
{
    struct Text
    {
        using model = model::Text;
        using view = view::Text;
    };

    struct Particles
    {
        using model = model::Particles;
        using view = view::Particles;
    };
}