#include "BWDI.h"
#include "BridgeClient.h"

#include <Util\Version.h>
#include <Util\Types.h>
#include <Util\HandleFactory.h>

#include <Bridge\SharedStuff.h>
#include <Bridge\EventEntry.h>
#include <Bridge\CommandEntry.h>

#include <BWDatabase\UnitTypes.h>
#include <BWDatabase\TechTypes.h>
#include <BWDatabase\UpgradeTypes.h>
#include <BWDatabase\WeaponTypes.h>
#include <BWDatabase\DamageTypes.h>
#include <BWDatabase\ExplosionTypes.h>
#include <BWDatabase\Races.h>
#include <BWDatabase\UnitSizeTypes.h>
#include <BWDatabase\PlayerTypes.h>

namespace BWDI
{
  //private:
  BWDI_FUNCTION void BWDI_APIENTRY BetaRelease()
  {
  }
  //public:
  //----------------------------------- GET VERSION -----------------------------------------------
  int BWDI_APIENTRY BWDIGetVersion()
  {
    return SVN_REV;
  }
  //----------------------------------- CONNECT ---------------------------------------------------
  SessionHandle BWDI_APIENTRY BWDICreate(SessionInfo *moduleInfo)
  {
    if(!moduleInfo)
      return NULL;
    return NULL;
  }
  //----------------------------------- WAIT FOR EVENT --------------------------------------------
  SessionState BWDI_APIENTRY BWDIWaitForNextEvent()
  {
    while(true)
    {
      try
      {
        while(!BridgeClient::isConnected())
        {
          Sleep(1000);
          BridgeClient::connect();
        }
      }
      catch(...)
      {
        return SessionState_InternalError;
      }

      try
      {
        BridgeClient::waitForEvent();
      }
      catch(...)
      {
        return SessionState_InternalError;
      }

      // react upon bridge state
      BridgeClient::RpcState rpcState = BridgeClient::getCurrentRpc();

      switch(rpcState)
      {
      case BridgeClient::OnFrame:
        {
          if(BridgeClient::gameData->isOnMatchStart)
          {
            // init database
            UnitTypes::init();
            TechTypes::init();
            UpgradeTypes::init();
            WeaponTypes::init();
            DamageTypes::init();
            ExplosionTypes::init();
            Races::init();
            UnitSizeTypes::init();
            return SessionState_MatchStart;
          }
        }return SessionState_MatchFrame;
      }
    }
  }
  //----------------------------------- GET STATIC GAME DATA --------------------------------------
  StaticGameData* BWDI_APIENTRY BWDIGetStaticGameData()
  {
    if(!BridgeClient::isConnected())
      return NULL;
    StaticGameData *retval = BridgeClient::gameData;
    return retval;
  }
  //----------------------------------- DESTROY ---------------------------------------------------
  BWDI_FUNCTION bool BWDI_APIENTRY BWDIDestroy()
  {
    return true;
  }
  //----------------------------------- POLL FOR NEXT EVENT ---------------------------------------
  BWDI_FUNCTION bool BWDI_APIENTRY BWDIPollForNextEvent()
  {
    return false;
  }
  //----------------------------------- MESSAGE ---------------------------------------------------
  BWDI_FUNCTION void BWDI_APIENTRY BWDIMessage(const char* text)
  {
    BridgeClient::pushSendText(false, text);
  }
  //----------------------------------- DRAWING FUNCTIONS -----------------------------------------
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawText(BWDI::Position pos, const char* text, int size, BWDI::CoordinateBase base)
  {
    BridgeClient::pushDrawText(base, pos, text, size);
  }
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawLine(BWDI::Position from, BWDI::Position to, BWDI::ColorID color, BWDI::CoordinateBase base)
  {
    BridgeClient::pushDrawLine(base, from, to, color);
  }
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawCircle(BWDI::Position pos, float radius, BWDI::ColorID color, bool solid, BWDI::CoordinateBase base)
  {
    BridgeClient::pushDrawCircle(base, pos, radius, color, solid);
  }
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawRectangle(BWDI::Position pos1, BWDI::Position pos2, BWDI::ColorID color, bool solid, BWDI::CoordinateBase base)
  {
    BridgeClient::pushDrawRectangle(base, pos1, pos2-pos1, color, solid);
  }
}
