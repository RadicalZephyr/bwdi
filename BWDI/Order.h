#pragma once

#include "OrderTypeID.h"
#include "UnitID.h"
#include "Position.h"

namespace BWDI
{
  struct Order
  {
    OrderTypeID type;
    UnitID targetUnit;
    Position targetPosition;
    int timer;
  };
}
