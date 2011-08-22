#pragma once

#include <Util\Types.h>

namespace BWDI
{
#pragma pack(1)
  struct BulletState
  {
    // identity
    u32 sightingID;
    PlayerID player;

    // positioning
    Position position;
    Position velocity;
    double angle;
    UnitID source;
    UnitID targetUnit;
    Position targetPos;

    // lifetime
    u32 removeTimer;

  };
#pragma pack()
}
