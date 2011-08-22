#pragma once

#include "Position.h"

#include <Util\StaticVector.h>

namespace BWDI
{
  struct Region
  {
    BWDI::Position center;
    u32 tileCount;
    BWDI::Position topLeftLimiter;
    BWDI::Position rightBottomLimiter;
    Util::StaticVector<u16, 16> neighbors;
    u32 flags;
  };
};
