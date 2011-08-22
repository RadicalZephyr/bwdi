#pragma once
/**
 *  DynamicGameData, the dynamic refers to data size.
 *
 *  We only fill the containers once each frame when handling the
 *  shared memory stacks. So since only push_back() and clear() are
 *  called on this containers, vectors should be used. A vector also
 *  gives reallocation advantage since it does not shrink, and it's
 *  linear storage has excelent caching qualities.
 */

#include <vector>
#include <BWDI\UnitEvent.h>

namespace BWDI
{
  class DynamicGameData
  {
  public:
  };
}
