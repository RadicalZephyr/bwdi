#pragma once

#include "BWDI\UnitTypeID.h"
#include <Util\StaticString.h>

namespace BWDI
{
  struct Race
  {
    int id;
    Util::StaticString<32> name;
    UnitTypeID worker;
    UnitTypeID center;
    UnitTypeID refinery;
    UnitTypeID transport;
    UnitTypeID supplyProvider;
  };
}
