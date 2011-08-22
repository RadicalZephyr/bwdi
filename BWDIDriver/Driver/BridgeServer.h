#pragma once

#include <Bridge\SharedStuff.h>
#include <Bridge\DrawShape.h>
#include <Bridge\CommandEntry.h>

#include <BWDI\StaticGameData.h>
#include <BWDI\UnitEvent.h>

#include <Util\MemoryFrame.h>

#include <string>
#include <deque>

namespace Bridge {}

namespace BWDI
{
  // see it as a singleton class.
  namespace BridgeServer
  {
  //public:
    extern Bridge::SharedStuff sharedStuff;
    extern StaticGameData* gameData;

    extern void initConnectionServer();
    extern void acceptIncomingConnections();
    extern void disconnect();
    extern bool exportSharedMemory();
    extern bool releaseSharedMemory();
    extern void updateRemoteSharedMemory();
    extern void invokeOnFrame();
    extern void invokeOnStartMatch(bool fromBeginning);

    // returns the index of the new unit
    extern int addKnownUnit(UnitState **out_pKnownUnit, UnitAddEventTypeID reason);
    extern void removeKnownUnit(int index, UnitRemoveEventTypeID reason);

    extern bool isAgentConnected();               // true when pipe connection works
    extern bool isBridgeInitialized();            // true once initBridge called

    typedef void (*DrawShapeCallback)(Util::MemoryFrame packet);
    extern void enumAllDrawShapes(DrawShapeCallback);
  }
}
