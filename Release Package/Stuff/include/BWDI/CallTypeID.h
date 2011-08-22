#pragma once

/**
 *  When BWDI calls the AI module, it's for one of these purposes
 */

namespace BWDI
{
  namespace CallTypeIDs
  {
    enum Enum
    {
      OnDisconnect,
      OnFrame,
      OnMatchStart
    };
  } typedef CallTypeIDs::Enum CallTypeID;
}
