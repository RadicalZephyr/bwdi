#pragma once
/**
 *  AddEvent and RemoveEvent parameters
 */

#include "UnitID.h"

namespace BWDI
{
  namespace UnitAddEventTypeIDs
  {
    enum Enum
    {
      Created,
      Unfogged,
      Noticed,
      Unloaded
    };
  }
  typedef UnitAddEventTypeIDs::Enum UnitAddEventTypeID;
  struct UnitAddEvent
  {
    UnitID unitID;
    UnitAddEventTypeID type;
  };

  namespace UnitRemoveEventTypeIDs
  {
    enum Enum
    {
      Died,
      Fogged,
      Loaded
    };
  }
  typedef UnitRemoveEventTypeIDs::Enum UnitRemoveEventTypeID;
  struct UnitRemoveEvent
  {
    UnitID unitID;
    UnitRemoveEventTypeID type;
  };
}
