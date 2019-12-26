//============================================================================
// @name        : text.h
// @author      : Thomas Dooms
// @date        : 12/18/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "abstract.h"
#include "../models/text.h"
#include "../views/text.h"

namespace controller
{
    class Text : public controller::Abstract
    {
    public:
        Text(const std::shared_ptr<model::Text>& model, const std::shared_ptr<view::Text>& view) : Abstract(model, view) {}

        void update() override {}
    };

}