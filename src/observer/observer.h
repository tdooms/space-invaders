//============================================================================
// @name        : observer.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "types.h"

class Observer
{
public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void receive(Type type) = 0;
};