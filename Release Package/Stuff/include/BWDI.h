#pragma once

#include <BWDI\UnitState.h>
#include <BWDI\UnitEvent.h>
#include <BWDI\StaticGameData.h>
#include <BWDI\DynamicGameData.h>
#include <BWDI\CallTypeID.h>
#include <BWDI\Flag.h>

#include <BWDI\UnitType.h>
#include <BWDI\UnitTypeID.h>
#include <BWDI\TechType.h>
#include <BWDI\TechTypeID.h>
#include <BWDI\UpgradeType.h>
#include <BWDI\UpgradeTypeID.h>
#include <BWDI\WeaponType.h>
#include <BWDI\WeaponTypeID.h>
#include <BWDI\DamageType.h>
#include <BWDI\DamageTypeID.h>
#include <BWDI\ExplosionType.h>
#include <BWDI\ExplosionTypeID.h>
#include <BWDI\Race.h>
#include <BWDI\RaceID.h>
#include <BWDI\UnitSizeType.h>
#include <BWDI\UnitSizeTypeID.h>
#include <BWDI\PlayerType.h>
#include <BWDI\PlayerTypeID.h>
#include <BWDI\CoordinateBase.h>
#include <BWDI\ColorID.h>

#include <string>

#undef DrawText

#ifdef BWCLIENT_EXPORTS
#define BWDI_FUNCTION extern "C" __declspec(dllexport)
#define BWDI_APIENTRY __stdcall
#else
#define BWDI_FUNCTION extern "C" __declspec(dllimport)
#define BWDI_APIENTRY __stdcall
#endif

namespace BWDI
{
  typedef unsigned long SessionHandle;
  typedef unsigned char bool8;
  typedef enum : unsigned long
  {
    SessionState_InternalError = 0,
    SessionState_Intermediate = 1,  // PollForNextEvent is returning false or WaitForNextEvent still blocking.
                                    // obviously this value cannot be returned from WaitForNextEvent.
    SessionState_MatchFrame = 2,
    SessionState_MatchStart = 3,
    SessionState_MatchEnd = 4,
    SessionState_QuitRequest = 5
  } SessionState;

  struct SessionInfo
  {
    long usingBWDIVersion;          // checks if the BWDI installed is not too old for the AI. (only till full release, then everything's backwards compatible)
    char moduleName[32];            // Name displayed when choosing AI and at match start. may use color characters
    bool8 allowProtoss;             // AI can handle Protoss
    bool8 allowTerran;              // AI can handle Terran
    bool8 allowZerg;                // AI can handle Zerg
    bool8 allowMultipleSlots;       // AI can handle multiple starting positions
  };

  //----------------------------------- INITIALISING ------------------------------------
  // return BWDI.dll revision number
  // it has no real use, just for fun
  BWDI_FUNCTION int BWDI_APIENTRY BWDIGetVersion();

  // returns NULL if fails, always fails of no race is specified or the parameter is NULL
  BWDI_FUNCTION SessionHandle BWDI_APIENTRY BWDICreate(SessionInfo *moduleInfo);

  // returns true if the target was a valid interface
  BWDI_FUNCTION bool BWDI_APIENTRY BWDIDestroy();

  // blocks. returns when BWDIQueryState has something new
  BWDI_FUNCTION SessionState BWDI_APIENTRY BWDIWaitForNextEvent();

  // returns false if BWDIWaitForNextEvent would block
  BWDI_FUNCTION bool BWDI_APIENTRY BWDIPollForNextEvent();

  //----------------------------------- DATA QUERY --------------------------------------
  // information queries
  BWDI_FUNCTION StaticGameData* BWDI_APIENTRY BWDIGetStaticGameData();

  //----------------------------------- ACTIONS -----------------------------------------
  // send a message
  BWDI_FUNCTION void BWDI_APIENTRY BWDIMessage(const char* text);

  // drawing functions
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawText(BWDI::Position pos, const char* text, int size, BWDI::CoordinateBase base);
//  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawDot      (BWDI::Position *pointArray,
//                                                     int pointCount,      BWDI::ColorID color, BWDI::CoordinateBase base);
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawLine     (BWDI::Position pos1,
                                                     BWDI::Position pos2, BWDI::ColorID color, BWDI::CoordinateBase base);
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawRectangle(BWDI::Position pos1,
                                                     BWDI::Position pos2, BWDI::ColorID color, bool solid, BWDI::CoordinateBase base);
  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawCircle   (BWDI::Position pos1,
                                                     float radius       , BWDI::ColorID color, bool solid, BWDI::CoordinateBase base);
//  BWDI_FUNCTION void BWDI_APIENTRY BWDIDrawEllipse  (BWDI::Position pos1,
//                                                     double r1, double r2,
//                                                     double angle,        BWDI::ColorID color, BWDI::CoordinateBase base);

  // dummy function to make applications compiled for the beta versions of BWDI incompatible to the full release
  BWDI_FUNCTION void BWDI_APIENTRY BetaRelease();
}
