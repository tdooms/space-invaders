//============================================================================
// @name        : objects.h
// @author      : Thomas Dooms
// @date        : 12/15/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "../controllers/text.h"
#include "../controllers/particles.h"
#include "../controllers/selection.h"

namespace objects
{
    struct Text
    {
        using model = model::Text;
        using view = view::Text;
        using controller = controller::Text;
    };

    struct Particles
    {
        using model = model::Particles;
        using view = view::Particles;
        using controller = controller::Particles;
    };

    struct Selection
    {
        using model = model::Selection;
        using view = view::Selection;
        using controller = controller::Selection;
    };
}