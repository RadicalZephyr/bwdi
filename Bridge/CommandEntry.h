#pragma once
/**
 * These entries are packets in the per-frame stack SharedStuff::CommandStack
 * Messages that are sent from client to driver.
 */

#include <BWDI\UnitCommand.h>

// zero sized arrays are FINE! It's the C++ standart who's being crazy here
#pragma warning(disable:4200)

namespace Bridge
{
  namespace CommandEntry
  {
// do not align the structures
#pragma pack(push, 1)

// automatic generation of unique numbers
#define UNIQUE_ID __LINE__

    struct SendText : Util::TypeHead<UNIQUE_ID>
    {
      bool printOnly;
      char text[0];
    };

    struct UnitOrder : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::UnitCommand unitCommand;
    };

    struct StartGame : Util::TypeHead<UNIQUE_ID>
    {
    };

    struct PauseGame : Util::TypeHead<UNIQUE_ID>
    {
    };

    struct LeaveGame : Util::TypeHead<UNIQUE_ID>
    {
    };

    struct ResumeGame : Util::TypeHead<UNIQUE_ID>
    {
    };

    struct RestartGame : Util::TypeHead<UNIQUE_ID>
    {
    };

    struct SetLocalSpeed : Util::TypeHead<UNIQUE_ID>
    {
      u32 speed;
    };

    struct ChangeRace : Util::TypeHead<UNIQUE_ID>
    {
      u32 race;
    };
    struct PingMinimap : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::Position pos;
    };

    struct EnableFlag : Util::TypeHead<UNIQUE_ID>
    {
      int flag;
    };

    struct SetScreenPosition : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::Position pos;
    };
#undef UNIQUE_ID
#pragma pack(pop)
  }
}
