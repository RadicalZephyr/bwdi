#pragma once

#include "UnitCommand.h"
#include "UnitState.h"
#include "BulletState.h"
#include "UnitEvent.h"
#include "Player.h"
#include "Force.h"
#include "Position.h"
#include "BuildPosition.h"
#include "UnitID.h"
#include "Region.h"

// databases
#include "UnitType.h"
#include "TechType.h"
#include "UpgradeType.h"
#include "WeaponType.h"
#include "DamageType.h"
#include "ExplosionType.h"
#include "Race.h"
#include "UnitSizeType.h"

#include <Util\StaticVector.h>
#include <Util\StaticSet.h>
#include <Util\StaticString.h>

#pragma pack(1)
namespace BWDI
{
  const int unitMaxCount = 1800;
  const int bulletMaxCount = 200;

  typedef Util::StaticSet<Player, 12> PlayerArray;
  typedef Util::StaticVector<BuildPosition, 8> StartLocationArray;
  typedef Util::StaticSet<UnitState, unitMaxCount> UnitArray;
  typedef Util::StaticSet<BulletState, bulletMaxCount> BulletArray;

  struct StaticGameData
  {
    int frameCount;

    // session
    bool isOnMatchStart;
    bool isFromBeginning;

    // latency
    int framesToTurnEnd;
    int commandExecutionFrame;
    int framesPerTurn;
    int commandLatencyTurns;

    // user input
    Position mousePosition;
    Position screenPosition;
	  Position screenSize;
    Util::StaticString<256> userInput;    // size based on experiments. 78 in bw, 119 in mp chat room, 255 in bnet
    Util::StaticVector<UnitID, 12> selectedUnits;

    // map
    BuildPosition mapSize;
    Util::StaticString<260> mapFilename;  //size based on broodwar memory
    Util::StaticString<32>  mapName;      //size based on broodwar memory
    int mapHash;
    u8 groundHeight[1024][1024];
    bool8 isWalkable[1024][1024];
    bool8 isBuildable[256][256];
    bool8 isVisible[256][256];
    bool8 isExplored[256][256];
    bool8 hasCreep[256][256];

    // match mode
    bool isMultiplayer;
    bool isReplay;
    bool isPaused;
    int getLatency;

    // players
    PlayerArray players;
    PlayerID self;
    StartLocationArray startLocations;
    Force forces[4];

    // units
    UnitArray units;
    Util::StaticVector<UnitRemoveEvent, unitMaxCount> unitsRemoved;
    Util::StaticVector<UnitAddEvent, unitMaxCount> unitsAdded;

    // bullets
    BulletArray bullets;
    Util::StaticVector<UnitRemoveEvent, bulletMaxCount> bulletsRemoved;
    Util::StaticVector<UnitAddEvent, bulletMaxCount> bulletsAdded;

    // scenario database
    UnitType      unitTypes[UnitTypeIDs::count];
    TechType      techTypes[TechTypeIDs::count];
    UpgradeType   upgradeTypes[UpgradeTypeIDs::count];
    WeaponType    weaponTypes[WeaponTypeIDs::count];
    DamageType    damageTypes[DamageTypeIDs::count];
    ExplosionType explosionTypes[DamageTypeIDs::count];
    Race          races[RaceIDs::count];
    UnitSizeType  unitSizeTypes[UnitSizeTypeIDs::count];

    // pathing
    u16 regionID[1024][1024];
    Util::StaticVector<Region, 5000> region;

  };
}
#pragma pack()
