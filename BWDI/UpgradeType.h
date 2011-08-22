#pragma once
#include "RaceID.h"
#include "UnitTypeID.h"

#include <string>
#include <set>

#include <Util\StaticString.h>

namespace BWDI
{
  struct UpgradeType
  {
    int id;
    Util::StaticString<32> name;
    int mineralPriceBase;
    int mineralPriceFactor;
    int gasPriceBase;
    int gasPriceFactor;
    int upgradeTimeBase;
    int upgradeTimeFactor;
    UnitTypeID whatUpgrades;
    RaceID race;
    int maxRepeats;
    bool valid;
  };
}
