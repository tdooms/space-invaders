//============================================================================
// @name        : types.h
// @author      : Thomas Dooms
// @date        : 12/3/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

// we make an exception for textures because they are not cheap to change
enum class Event
{
    valueChanged,
    textureChanged
};
