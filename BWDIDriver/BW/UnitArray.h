#pragma once
/***********************************************************************
 *  Direct maping of the unit node table in bw memory.
 *
 *******/

#include "Constants.h"
#include "Unit.h"

namespace BW { struct Unit; };

namespace BW
{
  int getUnitIndexByPointer(Unit* unit);
};
