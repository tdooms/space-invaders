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
#include "../util/vec.h"
#include "structs.h"
#include <optional>

namespace core { class World; }

namespace model
{
    class Abstract : public Subject
    {
    public:
        Abstract() = default;
        virtual ~Abstract() = default;

        std::optional<RemoveData> getRemoveData() noexcept { return removeData; }
        virtual void update(core::World& world) = 0;

    protected:
        std::optional<RemoveData> removeData;
    };
}