#pragma once

#include "RaceID.h"
#include "ForceID.h"
#include "PlayerTypeID.h"
#include "Position.h"

#include <Util\StaticString.h>
#include <Util\StaticSet.h>

namespace BWDI
{
  struct Player
  {
    ForceID force;
    PlayerTypeID type;
    RaceID race;
    s32 minerals;
    s32 gas;
    s32 cumulativeMinerals;
    s32 cumulativeGas;
    s32 suppliesAvailable[3];
    s32 suppliesUsed[3];

    s32 allUnitCount[228];
    s32 completedUnitCount[228];
    s32 deadUnitCount[228];
    s32 killedUnitCount[228];

    s32 upgradeLevel[66];
    bool isUpgrading[66];
    bool hasResearched[44];
    bool isResearching[44];

    Util::StaticString<25> name;  // size as BW memory

    bool alliance[12];       // index is playerID
    bool isVictorious;
    bool isDefeated;

    // helper functions
    int inline getOwnRaceAvailableSupplies() const
    {
      return suppliesAvailable[race];
    }

    int inline getOwnRaceUsedSupplies() const
    {
      return suppliesUsed[race];
    }
  };
}
