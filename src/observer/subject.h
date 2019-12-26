//============================================================================
// @name        : subject.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include "observer.h"

#include <memory>
#include <vector>

class Subject
{
public:
    Subject() = default;

    void addObserver(std::shared_ptr<Observer> observer) noexcept
    {
        observers.emplace_back(std::move(observer));
    }

    void send(Event type)
    {
        // sends a message for all observers to receive
        for(auto& observer : observers)
        {
            observer->receive(type);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};
