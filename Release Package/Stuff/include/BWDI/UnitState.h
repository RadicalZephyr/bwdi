#pragma once

#include "Position.h"
#include "UnitTypeID.h"
#include "UnitID.h"
#include "PlayerID.h"
#include "Order.h"
#include "Target.h"
#include "TechTypeID.h"
#include "UpgradeTypeID.h"

#include <Util\StaticVector.h>

namespace BWDI
{
  // access for a unit the agent has knowledge of
  typedef int ClearanceLevel;
  namespace ClearanceLevels
  {
    enum
    {
      None = 0,     // when a unit is removed, the slot is marked with this value
      Noticed = 1,  // unit is cloacked and not detected, but a human player would see the transparent effect
      Visible = 2,  // unit is visible/detected
      Full = 3      // unit belongs to you
    };
  }
  // Unit's state the AI knows about, depending on clearance level
  struct UnitStateNoticed
  {
    // basic data
    ClearanceLevel clearanceLevel;
    int sightingID;
    int removeTimer;
    
    // position is noticable
    Position position;
    bool isAccelerating;
    bool isMoving;
    bool isIdle;
    double angle;
    Util::Point<double> velocity;

    // position related stuff is noticable too
    bool isUnderStorm;

    // a human could well guess the type
    UnitTypeID type;

    // debug value
    int _debug;
  };
  struct UnitStateVisible : UnitStateNoticed
  {
    PlayerID player;
    int hitPoints;
    int shield;
    int energy;
    int resources;
    int killCount;
    bool isBeingConstructed;
    bool isBeingGathered;
    bool isBeingHealed;
    bool isBlind;
    bool isBraking;
    bool isBurrowed;
    bool isCarryingGas;
    bool isCarryingMinerals;
    bool isCloaked;
    bool isCompleted;
    bool isConstructing;
    bool isDefenseMatrixed;
    bool isEnsnared;
    bool isFollowing;
    bool isGatheringGas;
    bool isGatheringMinerals;
    bool isIrradiated;
    bool isLifted;
    bool isLockedDown;
    bool isMaelstrommed;
    bool isMorphing;
    bool isParasited;
    bool isPatrolling;
    bool isPlagued;
    bool isRepairing;
    bool isResearching;
    bool isSelected;
    bool isSieged;
    bool isStasised;
    bool isStimmed;
    bool isTraining;
    bool isUnpowered;
    bool isUpgrading;

    UnitID buildUnit;   // bidirectional
    UnitID addon;       // Could be bidirectional
    UnitID child;

    int buildTimer;

    int groundWeaponCooldown;
    int airWeaponCooldown;
    int spellCooldown;
  };
  struct UnitStateFull : UnitStateVisible
  {
    // strategic private data
    bool isHallucination;
    bool isLoaded;
    int defenseMatrixPoints;

    // connected units
    union
    {
      UnitID  hatchery;
      UnitID  nuclearMissile;
      UnitID  ghost;
    };
    Util::StaticVector<UnitID, 8> loadedUnits;
    int interceptorInHangarCount;
    int interceptorOutOfHangarCount;
    UnitID transport;

    // container
    int scarabCount;
    int spiderMineCount;

    // timers
    int defenseMatrixTimer;
    int ensnareTimer;
    int irradiateTimer;
    int lockdownTimer;
    int maelstromTimer;
    int plagueTimer;
    int stasisTimer;
    int stimTimer;
    int trainTimer;
    union
    {
      int researchTimer;
      int upgradeTimer;
    };
    // unit's orders
    Order order;
    Order secondaryOrder;
    Util::StaticVector<UnitID, 5> trainingQueue;
    Position rallyPosition;
    UnitID rallyUnit;
    TechTypeID tech;
    UpgradeTypeID upgrade;

    // Broodwar's unit movement engine
    UnitID movementTargetUnit;
    Position movementTargetPosition;

    // this is Broodwar pathfinding system's next shortstep.
    Position movementNextWaypoint;
  };
  typedef UnitStateFull UnitState;      // all states unified

}
