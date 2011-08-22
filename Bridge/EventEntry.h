#pragma once
/**
 * These entries are packets in the per-frame stack SharedStuff::EventStack
 */

#include "SharedStuff.h"

#include <BWDI\UnitEvent.h>

#include <Util\TypeHead.h>

namespace Bridge
{
  namespace EventEntry
  {
#pragma pack(push, 1)
#define UNIQUE_ID __LINE__
    struct PlayerLeave : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::PlayerID player;
    };
#undef UNIQUE_ID
#pragma pack(pop)
  }
}
