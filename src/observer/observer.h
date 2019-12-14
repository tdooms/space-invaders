//============================================================================
// @name        : observer.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "events.h"

class Observer
{
public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void receive(Event type) = 0;
};