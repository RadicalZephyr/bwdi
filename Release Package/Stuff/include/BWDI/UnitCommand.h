#pragma once

#include "UnitCommandTypeID.h"

#include <BWDI\TechTypeID.h>
#include <BWDI\UpgradeTypeID.h>
#include <BWDI\UnitTypeID.h>

/**
 * UnitOrder contains a single whole order
 */

namespace BWDI
{
  struct UnitCommand
  {
    UnitCommandTypeID commandID;
    int unitIndex;
    Util::Point<s32> position;  //position or tile position, depending on order type
    int targetIndex;            //target unit linear index, if applicable
    union   // depending on command type
    {
      int extra;
      TechTypeID tech;
      UpgradeTypeID upgrade;
      UnitTypeID unitType;
    };
  };
}