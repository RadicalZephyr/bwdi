#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers

#include "Engine.h"
#include "UnitMirror.h"
#include "BulletMirror.h"
#include "KnownUnitMirror.h"
#include "KnownBulletMirror.h"
#include "BridgeServer.h"
#include "Shape.h"
#include "UnitChainID.h"
#include "BulletChainID.h"

#include "ResourceFreer.h"

#include <DLLMain.h>

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <stdexcept>

#include <Util\Version.h>
#include <Util\Exceptions.h>
#include <Util\Strings.h>
#include <Util\Foreach.h>
#include <Util\Gnu.h>
#include <Util\FlagArray.h>
#include <Util\LookupTable.h>
#include <Util\TypedPacketSwitch.h>

#include <BW\Detours.h>
#include <BW\CodePatch.h>
#include <BW\Broodwar.h>
#include <BW\Unit.h>
#include <BW\UnitArray.h>
#include <BW\Offsets.h>
#include <BW\UnitID.h>
#include <BW\Command.h>
#include <BW\Latency.h>
#include <BW\TileType.h>
#include <BW\TileSet.h>
#include <BW\UnitTypeID.h>
#include <BW\GameTypeID.h>
#include <BW\WeaponID.h>
#include <BW\CheatType.h>
#include <BW\RaceID.h>
#include <BW\OrderID.h>
#include <BW\UnitPrototypeFlags.h>
#include <BW\Map.h>
#include <BW\PlayerID.h>
#include <BW\Bullet.h>

#include <BWDI.h>

#include <Bridge\PipeMessage.h>
#include <Bridge\SharedStuff.h>
#include <Bridge\Constants.h>

#include <BWDatabase\UnitTypes.h>
#include <BWDatabase\TechTypes.h>
#include <BWDatabase\UpgradeTypes.h>
#include <BWDatabase\WeaponTypes.h>
#include <BWDatabase\DamageTypes.h>
#include <BWDatabase\ExplosionTypes.h>
#include <BWDatabase\Races.h>
#include <BWDatabase\UnitSizeTypes.h>
#include <BWDatabase\PlayerTypes.h>

#include <Bridge\SessionListing.h>

#include "Debug.h"

#ifdef _DEBUG
//#define USE_TRACER
#endif

namespace BWDI
{
  namespace Engine
  {
//private:
    //----------------------------------- ENGINE STATE --------------------------------
    // broodwar game state
    enum GameState
    {
      Startup,
      InMenu,
      InMatch
    };
    GameState gameState = Startup;
    GameState lastState = Startup;

    // match state TODO: move some things to ::Map
    int frameCount;
    BW::Unit* savedSelectionStates[13];

    // reflects needed states from last frame to detect add and remove events.
    // is index correlated with BWDATA_UnitNodeTable and BWDATA_BulletNodeTable
    UnitMirror    bwUnitArrayMirror   [BW::UNIT_ARRAY_MAX_LENGTH];
    BulletMirror  bwBulletArrayMirror [BW::BULLET_ARRAY_MAX_LENGTH];

    // index correlated with the sighting array as found in StaticGameData.
    // holds private data that the AI mustn't to know about
    // hold when the known unit is invalid
    KnownUnitMirror   knownUnitArrayMirror  [BWDI::unitMaxCount];
    KnownBulletMirror knownBulletArrayMirror[BWDI::bulletMaxCount];

    // BWDI state
    bool flags[Flags::count];

    // error handling

    //------------------------------- -------------------------------------------------
    // TODO: enlist all private functions defined in Engine here
    //------------------------------- -------------------------------------------------
    void init();
    bool parseText(const char* text);

    void simulateUnitCommand(const BWDI::UnitCommand &simulatedCommand, BWDI::UnitState &stateToAlter);
    void executeUnitCommand(const BWDI::UnitCommand& command);
    //---------------------------------------------- INITIALIZATION --------------------------------------------
    void init()
    {
      try
      {
        // create log handles
        // iterate through unit types and create UnitType for each
        /*
        for (int i = 0; i < BW::UNIT_TYPE_COUNT; i++)
          unitTypes.insert(BW::UnitType((u16)i));
        */
      }
      catch (GeneralException& exception)
      {
        FILE *f;
        fopen_s(&f, "bwapi-error", "a+");
        fprintf(f, "Exception caught inside Game constructor: %s", exception.getMessage());
        fclose(f);
      }
    }
    //--------------------------------------------- SAVE SELECTED ----------------------------------------------
    void saveSelected()
    {
      memcpy(&savedSelectionStates, BW::BWDATA_ClientSelectionGroup, 4*12);
      savedSelectionStates[12] = NULL;
    }
    //--------------------------------------------- LOAD SELECTED ----------------------------------------------
    void loadSelected()
    {
/*      int unitCount = 0;
      while (savedSelectionStates[unitCount] != NULL)
        unitCount++;
      BW::selectUnits(unitCount, savedSelectionStates);*/
      memcpy(BW::BWDATA_ClientSelectionGroup, &savedSelectionStates, 4*12);
    }
    //-------------------------- COMMAND ENTRY HANDLERS -----------------------------------------
    int handleCommandSendText(Bridge::CommandEntry::SendText& packet, Util::MemoryFrame dynamicData)
    {
      // check for correctness of received c string
      if(dynamicData.endAs<char>()[-1] != 0)
        throw GeneralException("received CommandEntry::SendText's text data is not null terminated");

      if(packet.printOnly)
        BW::printf(packet.text);
      else
        BW::sendText(packet.text);

      return true;
    }
    int handleCommandStartGame(Bridge::CommandEntry::StartGame& packet)
    {
      BW::issueCommand(BW::Command::StartGame());
      return false;
    }
    int handleCommandPauseGame(Bridge::CommandEntry::PauseGame& packet)
    {
      BW::issueCommand(BW::Command::PauseGame());
      return false;
    }
    int handleCommandResumeGame(Bridge::CommandEntry::ResumeGame& packet)
    {
      BW::issueCommand(BW::Command::ResumeGame());
      return false;
    }
    int handleCommandLeaveGame(Bridge::CommandEntry::LeaveGame& packet)
    {
      /*
      *BW::BWDATA_GameState = 0;
      *BW::BWDATA_GamePosition = 6;
      */
      return false;
    }
    int handleCommandRestartGame(Bridge::CommandEntry::RestartGame& packet)
    {
      /*
      *BW::BWDATA_GameState = 0;
      *BW::BWDATA_GamePosition = 5;
      */
      return false;
    }
    int handleCommandSetLocalSpeed(Bridge::CommandEntry::SetLocalSpeed& packet)
    {
      BW::setLocalSpeed(packet.speed);
      return true;
    }
    int handleCommandChangeRace(Bridge::CommandEntry::ChangeRace& packet)
    {
      BW::changeRace(packet.race);
      return true;
    }
    int handleCommandEnableFlag(Bridge::CommandEntry::EnableFlag& packet)
    {
      int flag = packet.flag;
      // Enable the specified flag
      if (flag >= Flags::count)
      {
        BW::sendText("Invalid flag (%d).", flag);
      }
      else
      {
        // Modify flag state
        flags[flag] = true;
        switch(flag)
        {
        case Flags::CompleteMapInformation:
          BW::sendText("Enabled Flag CompleteMapInformation");
          break;
        case Flags::UserInput:
          BW::sendText("Enabled Flag UserInput");
          break;
        }
      }
      return true;
    }
    int handleCommandPingMinimap(Bridge::CommandEntry::PingMinimap& packet)
    {
      BW::issueCommand(BW::Command::MinimapPing(packet.pos));
      return true;
    }
    int handleCommandSetScreenPosition(Bridge::CommandEntry::SetScreenPosition& packet)
    {
      BW::setScreenPosition(packet.pos);
      return true;
    }
    std::vector<Bridge::CommandEntry::UnitOrder*> commandOrderEntries;
    int handleCommandOrderUnit(Bridge::CommandEntry::UnitOrder& packet)
    {
      // for later processing in tighter loops
      commandOrderEntries.push_back(&packet);
      return true;
    }
    //------------------------------ ADD KNOWN UNIT ----------------------------------------------
    int shareAddKnownUnit(UnitState **out_pKnownUnit, UnitAddEventTypeID reason, int bwUnitID)
    {
      // check prerequisites
      _ASSERT(BridgeServer::isAgentConnected());

      // insert new known unit into the shared set
      int index = BridgeServer::addKnownUnit(out_pKnownUnit, reason);

      // init the mirror (index correlated)
      knownUnitArrayMirror[index].bwUnitID = bwUnitID;

      return index;
    }
    //------------------------------ REMOVE KNOWN UNIT -------------------------------------------
    void shareRemoveKnownUnit(int knownUnitID, UnitRemoveEventTypeID reason)
    {
      // remove the known unit from shared memory
      BridgeServer::removeKnownUnit(knownUnitID, reason);

      // mark the backreferenced bwUnitID as invalid
      knownUnitArrayMirror[knownUnitID].bwUnitID = -1;
    }
    //----------------------------------- SHARE CLEAR FRAME BY FRAME BUFFERS -----------------------------------
    void shareClearFrameByFrameBuffers()
    {
      // any data that gets accumulated over the frame and presented to the AI has
      // to be cleaned out, so the accumulation in the next frame can begin.
      BridgeServer::gameData->userInput.set("");
    }
    //----------------------------------- SHARE EACH BW UNIT ---------------------------------------------------
    void shareEachBwUnit(BW::Unit &bwUnit, UnitChainID currentChain, bool isOnMatchStart)
    {
      // get corresponding index and mirror entry
      int bwUnitIndex = BW::getUnitIndexByPointer(&bwUnit); // get linear index
      UnitMirror &bwUnitMirror = bwUnitArrayMirror[bwUnitIndex];

      // process the chain states
      UnitChainID lastChain = bwUnitMirror.chain;     // we need these values for this iteration
      bwUnitMirror.chain = currentChain;              // init the value for next iteration

      // classify slot state
      bool isUsed = currentChain != UnitChainIDs::Unused;
      bool wasUsed = lastChain != UnitChainIDs::Unused;

      // if this slot is not used, it is not longer interesting
      if(!isUsed)
      {
        if(wasUsed)
        {
          // unit perished. If it had a known Unit associated with it, remove the
          // known unit too
          if(bwUnitMirror.knownUnit)
          {
            shareRemoveKnownUnit(bwUnitMirror.knownUnitIndex, UnitRemoveEventTypeIDs::Died);
            bwUnitMirror.knownUnit = NULL;
            bwUnitMirror.knownUnitIndex = -1;
          }
          return;
        }
        // this is a !wasUsed entry in a NotUsed Chain
        return;
      }

      // ASSUMPTION: the slot is being used
      _ASSERT(isUsed);

      if(!wasUsed)
      {
        // unit did not exist before. init the reflection for this unit
        bwUnitMirror.isDying = false;
        bwUnitMirror.isNoticed = false;
        bwUnitMirror.knownUnit = NULL;
        bwUnitMirror.knownUnitIndex = -1;
        bwUnitMirror.position = bwUnit.position;
      }

      // find out if the unit is dying
      bool isDying = false; //!bwUnit.sprite || (bwUnit.mainOrderType == BW::OrderIDs::Die && bwUnit.mainOrderState == 1);
      bool wasDying = bwUnitMirror.isDying;
      bwUnitMirror.isDying = isDying;
      if(!isDying && wasDying)
      {
        // the unit is not dying anymore? It's a new one
        // remove known unit if associated, tell its dead.
        if(bwUnitMirror.knownUnit)
        {
          shareRemoveKnownUnit(bwUnitMirror.knownUnitIndex, UnitRemoveEventTypeIDs::Died);
          bwUnitMirror.knownUnit = NULL;
          bwUnitMirror.knownUnitIndex = -1;
          bwUnitMirror.position = bwUnit.position;
        }
      }

      // calculate clearance level
      ClearanceLevel clearance = ClearanceLevels::None;

      do //while(false)
      {
        // the unit is fully accessible if it's yours
        if(BW::isInReplay() || bwUnit.playerID == *BW::BWDATA_selfPlayerID)
        {
          clearance = ClearanceLevels::Full;
          break;
        }

        // unit does not belong to you

        // visibility overrides
        bool isInVisibleArea = isOnMatchStart || flags[Flags::CompleteMapInformation];

        if(!isInVisibleArea)
        {
          // visibility of the unit
          BW::Position buildPosition = bwUnit.position / 32;
          isInVisibleArea = BW::Map::isVisible(buildPosition.x, buildPosition.y, *BW::BWDATA_selfPlayerID);
        }

        // handle noticed state
        if(isInVisibleArea)
        {
          // notice the unit if it moves
          if(bwUnitMirror.position != bwUnit.position)
            bwUnitMirror.isNoticed = true;
        }
        else
        {
          bwUnitMirror.isNoticed = false;
        }

        // only known if its in the visible area
        if(!isInVisibleArea)
          break;

        bool isCloacked = bwUnit.status.getBit<BW::StatusFlags::Cloaked>();

        if(!isCloacked)
        {
          clearance = ClearanceLevels::Visible;
          break;
        }

        bool isDetected = false;
        if(bwUnit.sprite)
        {
          if(BW::isInReplay())
            isDetected = bwUnit.sprite->visibilityFlags > 0;
          else
            // TODO: find a isDetected expression that works, this one just returns if the unit is in visible area
            isDetected = !!(bwUnit.sprite->visibilityFlags & (1 << *BW::BWDATA_selfPlayerID));
        }

        if(isDetected)
        {
          // visible if it's detected
          clearance = ClearanceLevels::Visible;
          break;
        }
        
        if(bwUnitMirror.isNoticed)
        {
          // can be noticed if not already detected
          clearance = ClearanceLevels::Noticed;
          break;
        }
      } while(false);

      // handle noticed state
      bwUnitMirror.position = bwUnit.position;

      // classify clarance level
      bool isKnown = clearance != ClearanceLevels::None;

      // if knownability changed
      if(!!bwUnitMirror.knownUnit != isKnown)
      {
        if(isKnown) // unit becomes known
        {
          // reserve a KnownUnitEntry and store it's address so it gets filled
          bwUnitMirror.knownUnitIndex = shareAddKnownUnit((UnitState**)&bwUnitMirror.knownUnit, UnitAddEventTypeIDs::Created, bwUnitIndex);
        }
        else // unit becomes not known
        {
          // release KnownUnit address
          shareRemoveKnownUnit(bwUnitMirror.knownUnitIndex, UnitRemoveEventTypeIDs::Died);
          bwUnitMirror.knownUnit = NULL;
          bwUnitMirror.knownUnitIndex = -1;
        }
      }

      if(!isKnown)
        return;

      // transfer recent data about this particular BW unit
      UnitState &knownUnit = *bwUnitMirror.knownUnit;

      // TODO: implement clearance limit
      int unitTypeInt = bwUnit.unitType;
      if (unitTypeInt==0xB1 || unitTypeInt==0xB2) unitTypeInt=0xB0;
      UnitTypeID type = (UnitTypeID)unitTypeInt;
      UnitType& typeData = UnitTypes::unitTypeData[type];

      knownUnit.clearanceLevel          = clearance;
      knownUnit._debug                  = bwUnit.sprite->visibilityFlags;

      knownUnit.position                = Position(bwUnit.position);
      knownUnit.type                    = type;
      knownUnit.velocity                = Util::Point<double>(bwUnit.current_speedX, bwUnit.current_speedY) / 256.0;
      {
        int d = bwUnit.currentDirection;
        // turn so zero faces  east
        d -= 64;
        if (d < 0) d += 256;
        // convert to radians
        double a = (double)d*3.14159265358979323846/128.0;
        // store
        knownUnit.angle                 = a;
      }

//              knownUnit                      = (int)&knownUnit;
      knownUnit.player                  = bwUnit.playerID;
      knownUnit.hitPoints               = bwUnit.healthPoints/256;
      knownUnit.shield                  = bwUnit.shieldPoints/256;
      knownUnit.energy                  = bwUnit.energy/256;
      if  (type == BW::UnitTypeIDs::Resource_MineralPatch1
        || type == BW::UnitTypeIDs::Resource_MineralPatch2
        || type == BW::UnitTypeIDs::Resource_MineralPatch3
        || type == BW::UnitTypeIDs::Resource_VespeneGeyser
        || type == BW::UnitTypeIDs::Terran_Refinery
        || type == BW::UnitTypeIDs::Protoss_Assimilator
        || type == BW::UnitTypeIDs::Zerg_Extractor)
        knownUnit.resources             = bwUnit.unitUnion1.unitUnion1Sub.resourceUnitUnionSub.resourceContained;
      knownUnit.killCount               = bwUnit.killCount;
      knownUnit.groundWeaponCooldown    = bwUnit.groundWeaponCooldown;
      knownUnit.airWeaponCooldown       = bwUnit.airWeaponCooldown;
      knownUnit.spellCooldown           = bwUnit.spellCooldown;
      knownUnit.defenseMatrixPoints     = bwUnit.defenseMatrixDamage/256;

      knownUnit.defenseMatrixTimer      = bwUnit.defenseMatrixTimer;
      knownUnit.ensnareTimer            = bwUnit.ensnareTimer;
      knownUnit.irradiateTimer          = bwUnit.irradiateTimer;
      knownUnit.lockdownTimer           = bwUnit.lockdownTimer;
      knownUnit.maelstromTimer          = bwUnit.maelstromTimer;
      knownUnit.plagueTimer             = bwUnit.plagueTimer;
      knownUnit.removeTimer             = bwUnit.removeTimer;
      knownUnit.stasisTimer             = bwUnit.stasisTimer;
      knownUnit.stimTimer               = bwUnit.stimTimer;

      bool isCompleted                  = bwUnit.status.getBit<BW::StatusFlags::Completed>();
      knownUnit.isCompleted             = isCompleted;
      knownUnit.isAccelerating          = bwUnit.movementFlags.getBit<BW::MovementFlags::Accelerating>();
      if(!isCompleted)
      {
        if(typeData.isBuilding)
          knownUnit.isBeingConstructed  = bwUnit.currentBuildUnit != NULL || typeData.race != RaceIDs::Terran;
        else
        if(type == UnitTypeIDs::Zerg_Egg
        || type == UnitTypeIDs::Zerg_Lurker_Egg
        || type == UnitTypeIDs::Zerg_Cocoon)
          knownUnit.isBeingConstructed  = true;
      }
      if(typeData.isResourceContainer)
        knownUnit.isBeingGathered       = bwUnit.unitUnion1.unitUnion1Sub.resourceUnitUnionSub.isBeingGathered != 0;
      else
        knownUnit.isBeingGathered       = false;
      knownUnit.isBeingHealed           = bwUnit.isBeingHealed != 0;
      knownUnit.isBlind                 = bwUnit.isBlind != 0;
      knownUnit.isBraking               = bwUnit.movementFlags.getBit<BW::MovementFlags::Braking>();
      knownUnit.isBurrowed              = bwUnit.status.getBit<BW::StatusFlags::Burrowed>();
      if(!typeData.isWorker)
      {
        knownUnit.isCarryingGas         = bwUnit.resourceType == 1;
        knownUnit.isCarryingMinerals    = bwUnit.resourceType == 2;
        knownUnit.isGatheringGas        = false;  // TODO: copy these, warning they;re big ones
        knownUnit.isGatheringMinerals   = false;
      }
      else
      {
        knownUnit.isCarryingGas         = false;
        knownUnit.isCarryingMinerals    = false;
        knownUnit.isGatheringGas        = false;
        knownUnit.isGatheringMinerals   = false;
      }
      knownUnit.isCloaked               = bwUnit.status.getBit<BW::StatusFlags::Cloaked>();

      BW::OrderID orderID = bwUnit.orderID;
      knownUnit.isConstructing          =  orderID == BW::OrderIDs::ConstructingBuilding
                                        || orderID == BW::OrderIDs::BuildTerran
                                        || orderID == BW::OrderIDs::DroneBuild
                                        || orderID == BW::OrderIDs::DroneStartBuild
                                        || orderID == BW::OrderIDs::DroneLand
                                        || orderID == BW::OrderIDs::BuildProtoss1
                                        || orderID == BW::OrderIDs::BuildProtoss2;

      knownUnit.isDefenseMatrixed       = bwUnit.defenseMatrixTimer > 0;
      knownUnit.isEnsnared              = bwUnit.ensnareTimer > 0;
      knownUnit.isFollowing             = orderID == BW::OrderIDs::Follow;

      knownUnit.isHallucination         = bwUnit.status.getBit<BW::StatusFlags::IsHallucination>();
      bool isResearching                = orderID == BW::OrderIDs::ResearchTech;
      knownUnit.isResearching           = isResearching;
      bool hasEmptyBuildQueue           =  bwUnit.buildQueueSlot < 5
                                        && bwUnit.buildQueue[bwUnit.buildQueueSlot] == BW::UnitTypeIDs::None;
      bool isTraining                   = (  type == UnitTypeIDs::Terran_Nuclear_Silo
                                          && bwUnit.secondaryOrderID == BW::OrderIDs::Train)
                                        || ( typeData.canProduce
                                          && !hasEmptyBuildQueue);
      knownUnit.isTraining              = isTraining;
      bool isUpgrading                  = orderID == BW::OrderIDs::Upgrade;
      knownUnit.isUpgrading             = isUpgrading;
      if (isTraining || isResearching || isUpgrading)
        knownUnit.isIdle                = false;
      else
        knownUnit.isIdle                =  orderID == BW::OrderIDs::PlayerGuard
                                        || orderID == BW::OrderIDs::Guard
                                        || orderID == BW::OrderIDs::Stop
                                        || orderID == BW::OrderIDs::Pickup1
                                        || orderID == BW::OrderIDs::Nothing2
                                        || orderID == BW::OrderIDs::Medic
                                        || orderID == BW::OrderIDs::Carrier
                                        || orderID == BW::OrderIDs::Critter
                                        || orderID == BW::OrderIDs::NukeTrain
                                        || orderID == BW::OrderIDs::Larva;
      knownUnit.isIrradiated            = bwUnit.irradiateTimer > 0;
      knownUnit.isLifted                = bwUnit.status.getBit<BW::StatusFlags::InAir>() && typeData.isBuilding;
      bool isLoaded                     =  bwUnit.status.getBit<BW::StatusFlags::InTransport>()
                                        || bwUnit.status.getBit<BW::StatusFlags::InBuilding>()
                                        ||
                                        ( //if
                                            (type == UnitTypeIDs::Protoss_Interceptor
                                          || type == UnitTypeIDs::Protoss_Scarab)
                                          &&
                                          (
                                            bwUnit.childUnitUnion3.inHanger != 0
                                          )
                                        );
      knownUnit.isLoaded                = isLoaded;
      knownUnit.isLockedDown            = bwUnit.lockdownTimer > 0;
      knownUnit.isMaelstrommed          = bwUnit.maelstromTimer > 0;
      knownUnit.isMorphing              =  orderID == BW::OrderIDs::Morph1
                                        || orderID == BW::OrderIDs::Morph2
                                        || orderID == BW::OrderIDs::ZergBuildSelf;
      knownUnit.isMoving                = bwUnit.movementFlags.getBit<BW::MovementFlags::Moving>();
      knownUnit.isParasited             = bwUnit.parasiteFlags.value != 0;
      knownUnit.isPatrolling            = orderID == BW::OrderIDs::Patrol;
      knownUnit.isPlagued               = bwUnit.plagueTimer > 0;
      knownUnit.isRepairing             =  orderID == BW::OrderIDs::Repair1
                                        || orderID == BW::OrderIDs::Repair2;
     if(flags[Flags::CompleteMapInformation])
        knownUnit.isSelected            = false;  // TODO: implement this into the bw unit mirror
      knownUnit.isSieged                = type == UnitTypeIDs::Terran_Siege_Tank_Siege_Mode;
      knownUnit.isStasised              = bwUnit.stasisTimer > 0;
      knownUnit.isStimmed               = bwUnit.stimTimer > 0;

      knownUnit.isUnderStorm            = bwUnit.isUnderStorm != 0;
      knownUnit.isUnpowered             =  typeData.race == RaceIDs::Protoss
                                        && typeData.isBuilding
                                        && bwUnit.status.getBit<BW::StatusFlags::DoodadStatesThing>();

      // fill order
      {
        BW::Unit* bwTargetUnit          = bwUnit.orderTargetUnit;
        if(bwTargetUnit)
        {
          int targetUnitIndex           = BW::getUnitIndexByPointer(bwTargetUnit);
          knownUnit.order.targetUnit    = bwUnitArrayMirror[targetUnitIndex].knownUnitIndex;
        }
        else
          knownUnit.order.targetUnit    = -1;
        knownUnit.order.targetPosition  = bwUnit.orderTargetPos;
        knownUnit.order.type            = (OrderTypeID)bwUnit.orderID;
        knownUnit.order.timer           = bwUnit.mainOrderTimer;
        knownUnit.secondaryOrder.type   = (OrderTypeID)bwUnit.secondaryOrderID;
      }
      {
        BW::Unit* bwTargetUnit          = bwUnit.targetUnit;
        if(bwTargetUnit)
        {
          int targetUnitIndex           = BW::getUnitIndexByPointer(bwTargetUnit);
          knownUnit.movementTargetUnit  = bwUnitArrayMirror[targetUnitIndex].knownUnitIndex;
        }
        else
          knownUnit.movementTargetUnit  = -1;
      }
      knownUnit.movementTargetPosition  = bwUnit.moveToPos;
      knownUnit.movementNextWaypoint    = bwUnit.nextWaypoint;

      {
        BW::Unit* bwBuildUnit           = bwUnit.currentBuildUnit;
        if(bwBuildUnit)
        {
          int buildUnitIndex            = BW::getUnitIndexByPointer(bwBuildUnit);
          knownUnit.buildUnit           = bwUnitArrayMirror[buildUnitIndex].knownUnitIndex;
          knownUnit.trainTimer          = bwBuildUnit->remainingBuildTime;
        }
        else
        {
          knownUnit.buildUnit           = -1;
          knownUnit.trainTimer          = 0;
        }
      }
      knownUnit.buildTimer              = bwUnit.remainingBuildTime;

      // container union
      knownUnit.scarabCount             = (type == UnitTypeIDs::Protoss_Reaver)
                                        ? (bwUnit.childUnitUnion2.unitIsNotScarabInterceptor.subChildUnitUnion1.scarabCount)
                                        : (0);
      knownUnit.spiderMineCount         = (type == UnitTypeIDs::Terran_Vulture)
                                        ? (bwUnit.childInfoUnion.vultureBikeMines.spiderMineCount)
                                        : (0);

      if(type != UnitTypeIDs::Protoss_Carrier)
      {
        knownUnit.interceptorInHangarCount = 0;
        knownUnit.interceptorOutOfHangarCount = 0;
      }
      else
      {
        knownUnit.interceptorInHangarCount = bwUnit.childUnitUnion2.unitIsNotScarabInterceptor.subChildUnitUnion1.interceptorCountInHangar;
        knownUnit.interceptorOutOfHangarCount = bwUnit.childUnitUnion2.unitIsNotScarabInterceptor.subChildUnitUnion2.interceptorCountOutOfHangar;
      }

      knownUnit.researchTimer           = (isResearching || isUpgrading)
                                          ?(bwUnit.childUnitUnion1.unitIsBuilding.upgradeResearchTime)
                                          :(0);
      //knownUnit.upgradeTimer;

      knownUnit.tech                    = (TechTypeID)bwUnit.childUnitUnion2.unitIsNotScarabInterceptor.subChildUnitUnion1.techID;
      knownUnit.upgrade                 = (UpgradeTypeID)bwUnit.childUnitUnion2.unitIsNotScarabInterceptor.subChildUnitUnion2.upgradeID;

      // addon
      knownUnit.addon                   = -1;
      if (typeData.isBuilding)
      {
        if (bwUnit.currentBuildUnit != NULL)
        {
          if(BW::BWDATA_Unit_PrototypeFlags[bwUnit.currentBuildUnit->unitType] & BW::UnitPrototypeFlags::Addon)
          {
            int bwAddonUnitIndex        = BW::getUnitIndexByPointer(bwUnit.currentBuildUnit);
            knownUnit.addon             = bwUnitArrayMirror[bwAddonUnitIndex].knownUnitIndex;
          }
        }
        else if (bwUnit.childInfoUnion.childUnit1 != NULL)
        {
          int bwAddonUnitIndex          = BW::getUnitIndexByPointer(bwUnit.childInfoUnion.childUnit1);
          knownUnit.addon               = bwUnitArrayMirror[bwAddonUnitIndex].knownUnitIndex;
        }
      }
      knownUnit.child                   = -1;
      if (bwUnit.childInfoUnion.childUnit1 != NULL)
      {
        int bwChildUnitIndex            = BW::getUnitIndexByPointer(bwUnit.childInfoUnion.childUnit1);
        knownUnit.child                 = bwUnitArrayMirror[bwChildUnitIndex].knownUnitIndex;
      }

      // transport
      if(isLoaded)
      {
        if (type == UnitTypeIDs::Protoss_Interceptor || type == UnitTypeIDs::Protoss_Scarab)
        {
          int bwTransportUnitIndex      = BW::getUnitIndexByPointer(bwUnit.childInfoUnion.parentUnit);
          knownUnit.transport           = bwUnitArrayMirror[bwTransportUnitIndex].knownUnitIndex;
        }
        else
        {
          int bwTransportUnitIndex      = BW::getUnitIndexByPointer(bwUnit.connectedUnit);
          knownUnit.transport           = bwUnitArrayMirror[bwTransportUnitIndex].knownUnitIndex;
        }
      }
      else
        knownUnit.transport             = -1;

      // rally
      if(typeData.canProduce)
      {
        knownUnit.rallyPosition         = Position(bwUnit.rallyPsiProviderUnion.rally.rallyPosX, bwUnit.rallyPsiProviderUnion.rally.rallyPosY);
        BW::Unit* bwRallyUnit           = bwUnit.rallyPsiProviderUnion.rally.rallyUnit;
        if(bwRallyUnit)
        {
          int rallyUnitIndex            = BW::getUnitIndexByPointer(bwRallyUnit);
          knownUnit.rallyUnit           = bwUnitArrayMirror[rallyUnitIndex].knownUnitIndex;
        }
        else
          knownUnit.rallyUnit           = -1;
      }

      // fill training queue
      {
        knownUnit.trainingQueue.clear();
        int index = bwUnit.buildQueueSlot;
        int count = 0;
        while(count < 5)
        {
          BW::UnitTypeID unitType = bwUnit.buildQueue[index];
          if(unitType == BW::UnitTypeIDs::None)
            break;
          knownUnit.trainingQueue.push_back((UnitTypeID)unitType);
          index = (index + 1) % 5;
          count++;
        }
      }

      // fill loaded units
      knownUnit.loadedUnits.clear();
      BW::UnitID *loadedUnits = bwUnit.loadedUnitIndex;
      for(int i = 0; i < 8; i++)
      {
        if (loadedUnits[i].isNull())
          continue;
        int bwLoadedUnitIndex = loadedUnits[i].getIndex();
        UnitID knownLoadedUnit = bwUnitArrayMirror[bwLoadedUnitIndex].knownUnitIndex;
        if(knownLoadedUnit == -1)
          continue;
        knownUnit.loadedUnits.push_back(knownLoadedUnit);
      }
      return;
    }
    //----------------------------------- SHARE EACH BW BULLET -------------------------------------------------
    void shareEachBwBullet(BW::Bullet &bwUnit, BulletChainID bulletChain, bool isOnMatchStart)
    {
      
    }
    //----------------------------------- SHARE MATCH FRAME ----------------------------------------------------
    void shareMatchFrame(bool isOnMatchStart)
    {
      // shareMatchFrame:
      // - convert data to AI
      // - wait till AI is ready
      // - convert-back commands from AI

      // ---------------------------- FRAME DATA ---------------------------------

      // fill buffers with recent world state data
      {
        BWDI::StaticGameData &staticData = *BridgeServer::gameData;

        // match data
        {
          staticData.getLatency     = BW::getLatency();
          staticData.frameCount     = frameCount;
          staticData.isPaused       = BW::isPaused();
        }

        // latency
        {
          CAPS caps;
          caps.dwSize = sizeof(CAPS);
          SNetGetProviderCaps(&caps);

          DWORD dwCallDelay = 1;
          if ( *BW::BWDATA_NetMode )
          {
            dwCallDelay = caps.dwCallDelay;
            if ( dwCallDelay > 8 )
              dwCallDelay = 8;
            else if ( dwCallDelay < 2 )
              dwCallDelay = 2;
          }
          staticData.framesPerTurn          = BW::BWDATA_LatencyFrames[*BW::BWDATA_GameSpeed];
          staticData.commandLatencyTurns    = dwCallDelay;
          staticData.framesToTurnEnd        = 0;
          staticData.commandExecutionFrame  = 0;
        }

        // user input data
        {
          staticData.mousePosition  = Position(BW::getMouseX(), BW::getMouseY());
          staticData.screenPosition = Position(BW::getScreenX(), BW::getScreenY());
          staticData.screenSize     = Position(640, 480);

          int selfPlayerID = *BW::BWDATA_selfPlayerID;
          for (int x = 0 ;x < BW::Map::getWidth() ;x++)
          {
            for (int y = 0 ;y < BW::Map::getHeight() ;y++)
            {
              // TODO: implement high-speed version
              staticData.isVisible[y][x] = BW::Map::isVisible(x, y, selfPlayerID);
              staticData.isExplored[y][x] = BW::Map::isExplored(x, y, selfPlayerID);
              staticData.hasCreep[y][x] = BW::Map::hasCreep(x, y) && BW::Map::isVisible(x, y, selfPlayerID);
            }
          }
        }

        // fresh player data
        for each(int playerID in staticData.players)
        {
          // players container is index correlated with bw's playerids
          int bwPlayerID = playerID;
          Player& player = staticData.players[playerID];

          if(BW::isInReplay()
             || BW::BWDATA_Alliance[*BW::BWDATA_selfPlayerID].player[bwPlayerID] != 0
             || flags[Flags::CompleteMapInformation])
          {
            player.minerals           = BW::BWDATA_PlayerResources->minerals          [bwPlayerID];
            player.gas                = BW::BWDATA_PlayerResources->gas               [bwPlayerID];
            player.cumulativeMinerals = BW::BWDATA_PlayerResources->cumulativeMinerals[bwPlayerID];
            player.cumulativeGas      = BW::BWDATA_PlayerResources->cumulativeGas     [bwPlayerID];
            // for all 3 races
            for(int r = 0; r < 3; r++)
            {
              player.suppliesAvailable[r] = BW::BWDATA_AllScores->supplies[r].available[bwPlayerID];
              player.suppliesUsed[r]      = BW::BWDATA_AllScores->supplies[r].used     [bwPlayerID];
            }
            for(int i=0;i<BW::UNIT_TYPE_COUNT;i++)
            {
              player.allUnitCount[i]      = BW::BWDATA_AllScores->unitCounts.all[i][bwPlayerID];
              player.completedUnitCount[i]= BW::BWDATA_AllScores->unitCounts.completed[i][bwPlayerID];
              player.deadUnitCount[i]     = BW::BWDATA_AllScores->unitCounts.dead[i][bwPlayerID];
              player.killedUnitCount[i]   = BW::BWDATA_AllScores->unitCounts.killed[i][bwPlayerID];
            }

            for(int i=0;i<BW::TECH_TYPE_COUNT;i++)
            {
              Util::BitMask<u64>* techs = (Util::BitMask<u64>*) (BW::BWDATA_ResearchProgress + bwPlayerID * 6);
              player.isResearching[i]=techs->getBit(1 << i);
              if (i < 0x18)
                player.hasResearched[i]=(*((u8*)(BW::BWDATA_TechResearchSC + bwPlayerID * 0x18 + i)) == 1);
              else
                player.hasResearched[i]=(*((u8*)(BW::BWDATA_TechResearchBW + bwPlayerID * 0x14 + i - 0x18)) == 1);
            }
            for(int i=0;i<BW::UPGRADE_TYPE_COUNT;i++)
            {
              player.isUpgrading[i]= (BW::BWDATA_UpgradeProgress->player[bwPlayerID].getBit(1 << i));
              if (i < 46)
                player.upgradeLevel[i]= (int)(*((u8*)(BW::BWDATA_UpgradeLevelSC + bwPlayerID * 46 + i)));
              else
                player.upgradeLevel[i]= (int)(*((u8*)(BW::BWDATA_UpgradeLevelBW + bwPlayerID * 15 + i - 46)));
            }
            player.isVictorious = (bwPlayerID < 8 &&  BW::BWDATA_PlayerVictory[bwPlayerID] == 3);
            player.isDefeated   = (bwPlayerID < 8 && (BW::BWDATA_PlayerVictory[bwPlayerID] == 1 ||
                                                      BW::BWDATA_PlayerVictory[bwPlayerID] == 2 ||
                                                      BW::BWDATA_PlayerVictory[bwPlayerID] == 4 ||
                                                      BW::BWDATA_PlayerVictory[bwPlayerID] == 6));
          }
          {
            // for all other players
            for each(int otherPlayerID in staticData.players)
            {
              int bwOtherPlayerID = otherPlayerID;
              player.alliance[otherPlayerID] = BW::BWDATA_Alliance[bwPlayerID].player[bwOtherPlayerID] != 0;
            }
          }
        }

        // traverse all broodwar's unit chains
        for(BW::Unit *bwUnit = *BW::BWDATA_UnitNodeChain_Unused_First; bwUnit; bwUnit = bwUnit->nextUnit)
        {
          shareEachBwUnit(*bwUnit, UnitChainIDs::Unused, isOnMatchStart);
        }
        for(BW::Unit *bwUnit = *BW::BWDATA_UnitNodeChain_Visible_First; bwUnit; bwUnit = bwUnit->nextUnit)
        {
          shareEachBwUnit(*bwUnit, UnitChainIDs::Visible, isOnMatchStart);
        }
        for(BW::Unit *bwUnit = *BW::BWDATA_UnitNodeChain_ScannerSweep_First; bwUnit; bwUnit = bwUnit->nextUnit)
        {
          shareEachBwUnit(*bwUnit, UnitChainIDs::ScannerSweep, isOnMatchStart);
        }
        for(BW::Unit *bwUnit = *BW::BWDATA_UnitNodeChain_Hidden_First; bwUnit; bwUnit = bwUnit->nextUnit)
        {
          shareEachBwUnit(*bwUnit, UnitChainIDs::Hidden, isOnMatchStart);
        }

        // traverse all broodwars bullet chains
        for(BW::Bullet *bwBullet = *BW::BWDATA_BulletNodeChain_Visible_First; bwBullet; bwBullet = bwBullet->nextBullet)
        {
          shareEachBwBullet(*bwBullet, BulletChainIDs::Visible, isOnMatchStart);
        }
        for(BW::Bullet *bwBullet = *BW::BWDATA_BulletNodeChain_Unused_First; bwBullet; bwBullet = bwBullet->nextBullet)
        {
          shareEachBwBullet(*bwBullet, BulletChainIDs::Unused, isOnMatchStart);
        }

        // save selection group
        staticData.selectedUnits.clear();
        for(BW::Unit** bwUnitRunner = BW::BWDATA_ClientSelectionGroup; *bwUnitRunner; bwUnitRunner++)
        {
          int bwUnitIndex = BW::getUnitIndexByPointer(*bwUnitRunner);
          UnitID knownUnitIndex = bwUnitArrayMirror[bwUnitIndex].knownUnitIndex;
          // if no known unit associated
          if(knownUnitIndex == -1)
            continue;
          staticData.selectedUnits.push_back(knownUnitIndex);
        }
      } //fill buffers with recend world state data

      // ------------------------- SYNCHRONISATION -------------------------

      // update remote shared memory
      BridgeServer::updateRemoteSharedMemory();

      // call OnFrame RPC
      BridgeServer::invokeOnFrame();

      // frame by frame data lifetime expired now
      shareClearFrameByFrameBuffers();

      // ------------------------- COMMANDS --------------------------------

      // iterate over commands that were issued this frame
      // sort them into the correspondant command entry arrays
      {
        // callback based handling, bool indicates whether to proceed
        static Util::TypedPacketSwitch<int> packetSwitch;
        if(!packetSwitch.getHandlerCount())
        {
          // init packet switch
          packetSwitch.addHandler(handleCommandSendText);
          packetSwitch.addHandler(handleCommandStartGame);
          packetSwitch.addHandler(handleCommandPauseGame);
          packetSwitch.addHandler(handleCommandLeaveGame);
          packetSwitch.addHandler(handleCommandResumeGame);
          packetSwitch.addHandler(handleCommandRestartGame);
          packetSwitch.addHandler(handleCommandSetLocalSpeed);
          packetSwitch.addHandler(handleCommandChangeRace);
          packetSwitch.addHandler(handleCommandEnableFlag);
          packetSwitch.addHandler(handleCommandPingMinimap);
          packetSwitch.addHandler(handleCommandSetScreenPosition);

          packetSwitch.addHandler(handleCommandOrderUnit);
        }
        // clear containers to receive next batch
        commandOrderEntries.clear();

        for(Bridge::SharedStuff::CommandStack::Index index = BridgeServer::sharedStuff.commands.begin();
            index.isValid();
            index = BridgeServer::sharedStuff.commands.getNext(index))
        {
          bool proceed = !!packetSwitch.handlePacket(BridgeServer::sharedStuff.commands.get(index));
          if(!proceed)
            break;
        }
      }

      // process issued unit commands
      {
        // execute and recruit new commands into the latency simulation queue
        {
          saveSelected();

          for each(Bridge::CommandEntry::UnitOrder* order in commandOrderEntries)
          {
            BWDI::UnitCommand& command = order->unitCommand;

            // TODO: validate command before executing it
            executeUnitCommand(command);
          }

          loadSelected();
        }
      }
    }
    //-------------------------------------- ON GAME START -----------------------------------------------------
    void onAppStart()
    {
      try
      {
        BridgeServer::initConnectionServer();
        SessionListing::init();
      }
      catch(GeneralException &e)
      {
        e.append("initializing bridge server");
        throw;
      }
    }
    //----------------------------------- SHARE MATCH START ----------------------------------------------------
    void shareMatchStart(bool fromStart)
    {
      // set all the flags to the default of disabled
      for (int i = 0; i < Flags::count; i++)
        flags[i] = false;

      // reset known unit container and its mirror
      BridgeServer::gameData->units.clear();
      for each(KnownUnitMirror &mirror in knownUnitArrayMirror)
      {
        mirror.bwUnitID = -1;
      }

      // fill the const part of static data, for the rest of the match
      BWDI::StaticGameData &staticData = *BridgeServer::gameData;

      // fill the map data
      for (int x = 0 ;x < BW::Map::getWidth() * 4 ;x++)
      {
        for (int y = 0 ;y < BW::Map::getHeight() * 4 ;y++)
        {
          staticData.groundHeight[y][x] = BW::Map::groundHeight(x, y);
          staticData.isWalkable[y][x] = BW::Map::isWalkable(x, y);
        }
      }
      for (int x = 0 ;x < BW::Map::getWidth() ;x++)
      {
        for (int y = 0 ;y < BW::Map::getHeight() ;y++)
        {
          staticData.isBuildable[y][x] = BW::Map::isBuildable(x, y);
        }
      }

      staticData.mapFilename.set(BW::BWDATA_CurrentMapFileName);

      staticData.mapName.set(BW::BWDATA_CurrentMapName);

      staticData.mapSize       = BuildPosition(BW::Map::getWidth(), BW::Map::getHeight());
      staticData.mapHash       = BW::Map::getHash();

      // get the start locations
      {
        BridgeServer::gameData->startLocations.clear();

        BW::Position* posptr = BW::BWDATA_startPositions;
        while (posptr->x != 0 || posptr->y != 0)
        {
          BridgeServer::gameData->startLocations.push_back(Position(
            posptr->x - BW::TILE_SIZE*2,
            posptr->y - (int)(BW::TILE_SIZE*1.5)) / 32);
          posptr++;
        }
      }

      // init all 4 forces
//      BridgeServer::gameData->forces.clear();
      for(int i = 0; i < 4; i++)
      {
        Force &force = BridgeServer::gameData->forces[i];
        force.name.set(BW::BWDATA_ForceNames[i].name);
      }

      // find all players
      staticData.self = *BW::BWDATA_selfPlayerID;
      staticData.players.clear();
      for (int i = 0; i < BW::PLAYER_COUNT; i++)
      {
        BW::PlayerInfo &bwPlayer = BW::BWDATA_Players[i];

        // is this a valid player slot?
        // The id of player 11 is 0 in replays, so we must check for neutral here
        if(!bwPlayer.isValid() && i!=11)
          continue;

        // transfer data
        Player &player = BridgeServer::gameData->players.allocate(i);
        player.force = bwPlayer.force;
        player.type = (PlayerTypeID)bwPlayer.type;
        player.name.set(bwPlayer.name);
        player.race = (RaceID)bwPlayer.race;
      }

      // match proterties
      staticData.isMultiplayer = BW::isMultiplayer();
      staticData.isReplay      = BW::isInReplay();

      // fill in the database
      for(int i = 0; i < UnitTypeIDs::count; i++)
        memcpy_s(&staticData.unitTypes[i], sizeof(UnitType), &UnitTypes::unitTypeData[i], sizeof(UnitType));
      for(int i = 0; i < TechTypeIDs::count; i++)
        memcpy_s(&staticData.techTypes[i], sizeof(TechType), &TechTypes::techTypeData[i], sizeof(TechType));
      for(int i = 0; i < UpgradeTypeIDs::count; i++)
        memcpy_s(&staticData.upgradeTypes[i], sizeof(UpgradeType), &upgradeTypeData[i], sizeof(UpgradeType));
      for(int i = 0; i < WeaponTypeIDs::count; i++)
        memcpy_s(&staticData.weaponTypes[i], sizeof(WeaponType), &WeaponTypes::weaponTypeData[i], sizeof(WeaponType));
      for(int i = 0; i < DamageTypeIDs::count; i++)
        memcpy_s(&staticData.damageTypes[i], sizeof(DamageType), &DamageTypes::damageTypeData[i], sizeof(DamageType));
      for(int i = 0; i < ExplosionTypeIDs::count; i++)
        memcpy_s(&staticData.explosionTypes[i], sizeof(ExplosionType), &ExplosionTypes::explosionTypeData[i], sizeof(ExplosionType));
      for(int i = 0; i < RaceIDs::count; i++)
        memcpy_s(&staticData.races[i], sizeof(Race), &Races::raceData[i], sizeof(Race));
      for(int i = 0; i < UnitSizeTypeIDs::count; i++)
        memcpy_s(&staticData.unitSizeTypes[i], sizeof(UnitSizeType), &UnitSizeTypes::unitSizeTypeData[i], sizeof(UnitSizeType));

      // fill pathing info
      if(!BW::BWDATA_SAIPathing)
        throw GeneralException(__FUNCTION__ ": BWDATA_SAIPathing not initialized");
      for(int y = 0; y < 1024; y++)
      {
        for(int x = 0; x < 1024; x++)
        {
          u16 regionID = BW::BWDATA_SAIPathing->mapTileRegionId[y/4][x/4];
          // there is chance regionID is a splitTileID
          if(regionID & 0x2000)
          {
            BW::split splitTile = BW::BWDATA_SAIPathing->splitTiles[regionID & 0x1FFF];
            int minitileShift = (x%4) + (y%4)*4;
            regionID = splitTile.rgnID[(splitTile.minitileMask >> minitileShift) & 1];
          }
          staticData.regionID[y][x] = regionID;
        }
      }
      if(BW::BWDATA_SAIPathing->regionCount > 5000)
        throw GeneralException(__FUNCTION__ ": more than 5000 regions?");
      staticData.region.clear();
      for(u32 i = 0; i < BW::BWDATA_SAIPathing->regionCount; i++)
      {
        BW::region &bwRegion = BW::BWDATA_SAIPathing->regions[i];

        // map bottom
        //if(bwRegion.properties & 0x100)

        Region &region = staticData.region.push_back();
        region.center             = bwRegion.getCenter();
        region.tileCount          = bwRegion.tileCount;
        region.topLeftLimiter     = BWDI::Position(bwRegion.rgnBox.left , bwRegion.rgnBox.top   );
        region.rightBottomLimiter = BWDI::Position(bwRegion.rgnBox.right, bwRegion.rgnBox.bottom);
        region.flags              = bwRegion.accessabilityFlags;
        region.neighbors.clear();
        if(bwRegion.neighborCount <= region.neighbors.size)
        {
          for(int n = 0; n < bwRegion.neighborCount; n++)
          {
            region.neighbors.push_back(bwRegion.neighbors[n]);
          }
        }
      }

      // clear frame by frame data, since this is the first frame
      shareClearFrameByFrameBuffers();

      // invoke onFrame RPC, but with match-start flags
      {
        staticData.isOnMatchStart = true;
        staticData.isFromBeginning = fromStart;
        shareMatchFrame(true);
        staticData.isOnMatchStart = false;
      }
    }
    //-------------------------------------- ON MATCH FRAME FIRST ----------------------------------------------
    void onMatchFrameFirst()
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

      // reset frame count
      frameCount = 0;

      // init bwUnitTableMirror
      {
        // mark all array as unused
        for(int i = 0; i < BW::UNIT_ARRAY_MAX_LENGTH; i++)
        {
          UnitMirror& mirror = bwUnitArrayMirror[i];
          mirror.chain          = UnitChainIDs::Unused;
          mirror.isDying        = false;
          mirror.isNoticed      = false;
          mirror.knownUnit      = NULL;
          mirror.knownUnitIndex = -1;
        }
      }

      // init shared memory, if agent is connected during the first match frame
      if(BridgeServer::isAgentConnected())
        shareMatchStart(true);

      // debug: set the userinput flag
      flags[BWDI::Flags::UserInput] = true;
    }
    //-------------------------------------- HANDLE AGENT CONNECTION -------------------------------------------
    void acceptIncomingConnections()
    {
      if(BridgeServer::isBridgeInitialized()
        && !BridgeServer::isAgentConnected())
      {
        BridgeServer::acceptIncomingConnections();
        if(BridgeServer::isAgentConnected() && gameState == InMatch)
        {
          // in the event of the agent connecting during a match
          shareMatchStart(false);
        }
      }
    }
    //---------------------------------------------- ON MENU FRAME ---------------------------------------------
    void onMenuFrame()
    {
      lastState = gameState;
      gameState = InMenu;

      // events
      if(lastState != InMenu)
      {
        if(lastState == Startup)
          onAppStart();
      }

      acceptIncomingConnections();
    }
    //---------------------------------------------- ON MATCH FRAME --------------------------------------------
    void onMatchFrame()
    {
      lastState = gameState;
      gameState = InMatch;

      // events
      if(lastState != InMatch)
      {
        onMatchFrameFirst();
      }

      acceptIncomingConnections();

      if(BridgeServer::isAgentConnected())
      {
        if(lastState != InMatch)
          BW::printf("BWDI r" SVN_REV_STR ", connected module");
        shareMatchFrame(false);
      }
      else
      {
        if(lastState != InMatch)
          BW::printf("BWDI r" SVN_REV_STR " standby");
      }
#ifdef USE_TRACER
      Tracer::onMatchFrame();
#endif

      // count frames
      frameCount++;

      // debug
      if(false)
      {
        int acount = 0;
        int bcount = 0;
        for(BW::Bullet *bwBullet = *BW::BWDATA_BulletNodeChain_Visible_First; bwBullet; bwBullet = bwBullet->nextBullet)
        {
          acount++;
        }
        for(BW::Bullet *bwBullet = *BW::BWDATA_BulletNodeChain_Visible_First; bwBullet; bwBullet = bwBullet->nextBullet)
        {
          bcount++;
        }

        // debug output
        {
          HDC screen = GetDC(NULL);
          char tbuffer[2000];
          sprintf_s(tbuffer, 2000, "A: %d  ", acount);
          TextOut(screen, 0, 0, tbuffer, strlen(tbuffer));
          sprintf_s(tbuffer, 2000, "B: %d  ", bcount);
          TextOut(screen, 0, 16, tbuffer, strlen(tbuffer));
          ReleaseDC(NULL, screen);
        }
      }
    }
    //---------------------------------------- ON MATCH END ----------------------------------------------------
    void onMatchEnd()
    {
      // we're not technically in match anymore.
      // This is needed to reinit a match when restarting a game, since then
      // onMenuFrame is not called
      gameState = InMenu;
    }
    //---------------------------------------- ON MESSAGE INTERCEPTED ------------------------------------------
    void onMessageIntercepted(const char* text)
    {
      if (parseText(text))
        return;

      if(BridgeServer::isAgentConnected())
      {
        if(!flags[Flags::UserInput])
          return;

        // save text as userInput
        BridgeServer::gameData->userInput.set(text);
      }
      else
      {
        BW::sendText("%s", text);
      }
    }
    //---------------------------------------- EACH DRAW SHAPE -------------------------------------------------
    Position inline translateFromBase(Position pos, CoordinateBase base)
    {
      switch(base)
      {
      case CoordinateBases::Map:
        return pos - BW::getScreenPos();
      case CoordinateBases::Screen:
        return pos;
      case CoordinateBases::Mouse:
        return pos + BW::getMousePos();
      }
      throw GeneralException("invalid coordinate base specfied");
    }
    void eachDrawShape(Util::MemoryFrame shapePacket)
    {
      // get first int from the packet
      int type = shapePacket.getAs<s32>();
      if(type == Bridge::DrawShape::Text::_typeID)
      {
        // get packet header
        Bridge::DrawShape::Text text;
        shapePacket.readTo(text);

        // validate rest of the packet
        if(!shapePacket.size())
        {
          // packet too small
          throw GeneralException(__FUNCTION__ ": text shape packet too small for text");
        }
        if(shapePacket.endAs<char>()[-1] != 0)
        {
          // not null terminated
          throw GeneralException(__FUNCTION__ ": text shape packet text not null terminated");
        }

        // draw text on screen
        Position pos = translateFromBase(text.pos, text.base);
        BW::drawText(pos.x, pos.y, shapePacket.beginAs<char>(), text.size);
      }
      if(type == Bridge::DrawShape::Line::_typeID)
      {
        Bridge::DrawShape::Line line;
        shapePacket.readTo(line);
        Position from = translateFromBase(line.from, line.base);
        Position to = translateFromBase(line.to, line.base);
        drawLine(from.x, from.y, to.x, to.y, line.color);
      }
      if(type == Bridge::DrawShape::Rectangle::_typeID)
      {
        Bridge::DrawShape::Rectangle rect;
        shapePacket.readTo(rect);
        Position pos = translateFromBase(rect.pos, rect.base);
        drawRectangle(pos.x, pos.y, rect.size.x, rect.size.y, rect.color, rect.isSolid);
      }
      if(type == Bridge::DrawShape::Circle::_typeID)
      {
        Bridge::DrawShape::Circle circle;
        shapePacket.readTo(circle);
        Position center = translateFromBase(circle.center, circle.base);
        drawCircle(center.x, center.y, circle.radius, circle.color, circle.isSolid);
      }
      if(type == Bridge::DrawShape::Ellipse::_typeID)
      {
        Bridge::DrawShape::Ellipse ellipse;
        shapePacket.readTo(ellipse);
        Position pos = translateFromBase(ellipse.pos, ellipse.base);
        drawEllipse(pos.x, pos.y, ellipse.sizex, ellipse.sizey, ellipse.color, ellipse.isSolid);
      }
      if(type == Bridge::DrawShape::Dot::_typeID)
      {
        Bridge::DrawShape::Dot dot;
        shapePacket.readTo(dot);
        Position pos = translateFromBase(dot.pos, dot.base);
        BW::drawDot(pos.x, pos.y, dot.color);
      }
      if(type == Bridge::DrawShape::Triangle::_typeID)
      {
        Bridge::DrawShape::Triangle triangle;
        shapePacket.readTo(triangle);
        Position posa = translateFromBase(triangle.posa, triangle.base);
        Position posb = translateFromBase(triangle.posb, triangle.base);
        Position posc = translateFromBase(triangle.posc, triangle.base);
        drawTriangle(posa.x, posa.y, posb.x, posb.y, posc.x, posc.y, triangle.color, triangle.isSolid);
      }
    }
    //---------------------------------------- ON MATCH DRAW HIGH ----------------------------------------------
    void onMatchDrawHigh()
    {
      if(BridgeServer::isAgentConnected())
        BridgeServer::enumAllDrawShapes(eachDrawShape);
#ifdef _DEBUG
      dbgDraw();
#endif
    }
    //---------------------------------------------- GLOBAL EXCEPTION HANDLER ----------------------------------
    void onException(const char* text)
    {
      bool wasConnected = BridgeServer::isAgentConnected();
      BridgeServer::disconnect();
      if(BW::isInGame())
      {
        if(wasConnected)
          BW::printf("disconnected: %s\n", text);
        else
          BW::printf("exception: %s\n", text);
      }
    }
    //---------------------------------------------- HOOK HANDLERS ---------------------------------------------
    bool onIssueCommand(Util::MemoryFrame command)
    {
      int commandID = command.getAs<u8>();
      //decide if we should let the command go through
      if ( !BridgeServer::isAgentConnected() || flags[Flags::UserInput]
        || !BW::isInGame() || BW::isInReplay())
      {
        return true;
      }
        //If user input is disabled, only allow the following commands to go through:
      if ( commandID == 0x00 // Game Chat
        || commandID == 0x05 // Keep Alive
        || commandID == 0x06 // Save Game
        || commandID == 0x07 // Load Game
        || commandID == 0x08 // Restart Game
        || commandID == 0x09 // Select         example: BW::Command::SelectSingle::_typeID
        || commandID == 0x0A // Shift Select
        || commandID == 0x10 // Pause Game
        || commandID == 0x11 // Resume Game
        || commandID == 0x37 // Game Hash
        || commandID == 0x3C // Start Game
        || commandID == 0x3D // Map Download %
        || commandID == 0x3E // Game Slot Modification
        || commandID == 0x3F // Unknown
        || commandID == 0x40 // Join Game
        || commandID == 0x41 // Race Change
        || commandID == 0x42 // Melee Force Change
        || commandID == 0x43 // UMS   Force Change
        || commandID == 0x44 // Slot Change
        || commandID == 0x45 // Swap Players
        || commandID == 0x48 // Game Init (Random Seed)
        || commandID == 0x49 // Info Request
        || commandID == 0x4A // Force Data Transfer
        || commandID == 0x4B // Force Name Transfer
        || commandID == 0x4C // Lobby Chat
        || commandID == 0x4E // Boot Player
        || commandID == 0x4F // Map Transfer
        || commandID == 0x54 // Mission Briefing Start
        || commandID == 0x55 // Set Latency
        || commandID == 0x56 // Change Replay Speed
        || commandID == 0x57 // Leave Game
        || commandID == 0x58 // Minimap Ping
        || commandID == 0x5B // Make Game Public
        || commandID == 0x5C // Replay Game Chat
        )
      {
        return true;
      }
      return false;
    }
    //------------------------------------------------- ON DLL LOAD --------------------------------------------
    void onDllLoad() throw()
    {
      // stop!!!
      // please reconsider, this thread is not the starcraft thread. hardly foreseeable future bugs can
      // be avoided altogether by moving initialisation code to update()
      // throw anything here to unload the dll and signal dll initialisation as failed
      ApplyCodePatches();
    }
    //----------------------------------------------- PARSE TEXT -----------------------------------------------
    bool parseText(const char* text)
    {
      /* analyze the string */
      std::string message = text;
      std::vector<std::string> parsed = Util::Strings::splitString(message, " ");

      /* fix for bad referencing */
      while (parsed.size() < 5)
        parsed.push_back("");

      /* commands list */
      if (parsed[0] == "/leave")
      {
        BW::leaveGame();
        return true;
      }
      else if (parsed[0] == "/latency")
      {
        BW::printf("latency: %d", BW::getLatency());
        return true;
      }
      else if (parsed[0] == "/speed")
      {
        if (parsed[1] != "")
          BW::setLocalSpeed(atoi(parsed[1].c_str()));
        else
          BW::resetLocalSpeed();
        return true;
      }
      else if (parsed[0] == "/restart")
      {
        BW::restartGame();
        return true;
      }
#ifdef USE_TRACER
      else if (parsed[0] == "/tracer")
      {
        if(!Tracer::command(parsed))
        {
          BW::printf("unknown tracer command");
        }
        return true;
      }
#endif
      return false;
    }
    //---------------------------------------- ORDER EXECUTION -------------------------------------------------
    void executeSelectOrder(int bwUnitIndex)
    {
      BW::Unit* select;
      select = &BW::BWDATA_UnitNodeTable[bwUnitIndex];
      BW::selectUnits(1, &select);
    }
    int findBwIndexByKnownUnitIndex(UnitID knownUnitID)
    {
      // lookup the bwunit index in the reflected knownunit entry
      int bwUnitIndex = knownUnitArrayMirror[knownUnitID].bwUnitID;
      if(bwUnitIndex == -1)
        throw GeneralException("Executing order on not existing unit id");

      // do a check
      _ASSERT(knownUnitID == bwUnitArrayMirror[bwUnitIndex].knownUnitIndex);

      return bwUnitIndex;
    }
    void executeUnitAttackPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(command.position, BW::OrderIDs::AttackMove));
    }
    void executeUnitAttackUnit(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), BW::OrderIDs::Attack1));
    }
    void executeUnitRightClickPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::RightClick(command.position));
    }
    void executeUnitRightClickUnit(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::RightClick(findBwIndexByKnownUnitIndex(command.targetIndex)));
    }
    void executeUnitTrain(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      BW::UnitTypeID type = (BW::UnitTypeID)command.unitType;
      executeSelectOrder(bwUnitIndex);
      if (bwUnit.unitType == BW::UnitTypeIDs::Zerg_Larva ||
          bwUnit.unitType == BW::UnitTypeIDs::Zerg_Mutalisk ||
          bwUnit.unitType == BW::UnitTypeIDs::Zerg_Hydralisk)
      {
        BW::issueCommand(BW::Command::UnitMorph(type));
      }
      else if (bwUnit.unitType == BW::UnitTypeIDs::Zerg_Hatchery ||
               bwUnit.unitType == BW::UnitTypeIDs::Zerg_Lair ||
               bwUnit.unitType == BW::UnitTypeIDs::Zerg_Spire ||
               bwUnit.unitType == BW::UnitTypeIDs::Zerg_CreepColony)
      {
        BW::issueCommand(BW::Command::BuildingMorph(type));
      }
      else if (bwUnit.unitType == BW::UnitTypeIDs::Protoss_Carrier ||
               bwUnit.unitType == BW::UnitTypeIDs::Protoss_Reaver)
      {
        BW::issueCommand(BW::Command::TrainFighter());
      }
      else
      {
        BW::issueCommand(BW::Command::TrainUnit(type));
      }
    }
    void executeUnitBuild(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      BW::UnitTypeID type((BW::UnitTypeID)command.unitType);
      executeSelectOrder(bwUnitIndex);
      if (BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Addon)
        BW::issueCommand(BW::Command::MakeAddon(command.position, type));
      else
        BW::issueCommand(BW::Command::MakeBuilding(command.position, type));
    }
    void executeUnitBuildAddon(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if( !(BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Addon) )
        return;
      executeUnitBuild(bwUnitIndex, bwUnit, command);
    }
    void executeUnitResearch(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      u8 techenum = (u8)command.tech;
      BW::issueCommand(BW::Command::Invent(BW::TechID(techenum)));
    }
    void executeUnitUpgrade(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      u8 upgradeenum = (u8)command.upgrade;
      BW::issueCommand(BW::Command::Upgrade(BW::UpgradeID(upgradeenum)));
    }
    void executeUnitStop(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      if (bwUnit.unitType == BW::UnitTypeIDs::Protoss_Reaver)
        BW::issueCommand(BW::Command::ReaverStop());
      else if (bwUnit.unitType == BW::UnitTypeIDs::Protoss_Carrier)
        BW::issueCommand(BW::Command::CarrierStop());
      else
        BW::issueCommand(BW::Command::Stop(0));
    }
    void executeUnitHoldPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::HoldPosition(0));
    }
    void executeUnitPatrol(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), BW::OrderIDs::Patrol));
    }
    void executeUnitFollow(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), BW::OrderIDs::Follow));
    }
    void executeUnitSetRallyPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(command.position, BW::OrderIDs::RallyPoint2));
    }
    void executeUnitSetRallyUnit(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), BW::OrderIDs::RallyPoint1));
    }
    void executeUnitRepair(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), BW::OrderIDs::Repair1));
    }
    void executeUnitReturnCargo(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::ReturnCargo(0));
    }
    void executeUnitMorph(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::UnitTypeID rawtype((BW::UnitTypeID)command.unitType);
      if( BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Building ) // bwUnit.unitType.isBuilding()
        BW::issueCommand(BW::Command::BuildingMorph(rawtype));
      else
        BW::issueCommand(BW::Command::UnitMorph(rawtype));
    }
    void executeUnitBurrow(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (!bwUnit.status.getBit<BW::StatusFlags::Burrowed>())
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Burrow());
      }
    }
    void executeUnitUnburrow(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (bwUnit.status.getBit<BW::StatusFlags::Burrowed>())
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Unburrow());
      }
    }
    void executeUnitSiege(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (bwUnit.unitType == BW::UnitTypeIDs::Terran_SiegeTankTankMode)
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Siege());
      }
    }
    void executeUnitUnsiege(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (bwUnit.unitType == BW::UnitTypeIDs::Terran_SiegeTankSiegeMode)
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Unsiege());
      }
    }
    void executeUnitCloak(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (!bwUnit.status.getBit<BW::StatusFlags::Cloaked>())
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Cloak());
      }
    }
    void executeUnitDecloak(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if (bwUnit.status.getBit<BW::StatusFlags::Cloaked>())
      {
        executeSelectOrder(bwUnitIndex);
        BW::issueCommand(BW::Command::Decloak());
      }
    }
    void executeUnitLift(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if( BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Building ) // bwUnit.unitType.isBuilding()
      {
        if (!bwUnit.status.getBit<BW::StatusFlags::InAir>())
        {
          executeSelectOrder(bwUnitIndex);
          BW::issueCommand(BW::Command::Lift());
        }
      }
    }
    void executeUnitLand(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      if( BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Building ) // bwUnit.unitType.isBuilding()
      {
        if (bwUnit.status.getBit<BW::StatusFlags::InAir>())
        {
          executeSelectOrder(bwUnitIndex);
          BW::issueCommand(BW::Command::Land(command.position,bwUnit.unitType));
        }
      }
    }
    void executeUnitLoad(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);

      int bwTargetUnitIndex = findBwIndexByKnownUnitIndex(command.targetIndex);
      const BW::Unit& bwTargetUnit = BW::BWDATA_UnitNodeTable[bwTargetUnitIndex];

      if (bwUnit.unitType == BW::UnitTypeIDs::Terran_Bunker)
        BW::issueCommand(BW::Command::Attack(bwTargetUnitIndex, BW::OrderIDs::Pickup3));
      else if (bwUnit.unitType == BW::UnitTypeIDs::Terran_Dropship ||
               bwUnit.unitType == BW::UnitTypeIDs::Protoss_Shuttle ||
               bwUnit.unitType == BW::UnitTypeIDs::Zerg_Overlord)
        BW::issueCommand(BW::Command::Attack(bwTargetUnitIndex, BW::OrderIDs::Pickup2));
      else if (bwTargetUnit.unitType == BW::UnitTypeIDs::Terran_Bunker ||
               bwTargetUnit.unitType == BW::UnitTypeIDs::Terran_Dropship ||
               bwTargetUnit.unitType == BW::UnitTypeIDs::Protoss_Shuttle ||
               bwTargetUnit.unitType == BW::UnitTypeIDs::Zerg_Overlord)
        BW::issueCommand(BW::Command::RightClick(bwTargetUnitIndex));
    }
    void executeUnitUnload(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::UnloadUnit(findBwIndexByKnownUnitIndex(command.targetIndex)));
    }
    void executeUnitUnloadAll(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::UnloadAll());
    }
    void executeUnitUnloadAllPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Attack(command.position,BW::OrderIDs::MoveUnload));
    }
    void executeUnitCancelConstruction(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelConstruction());
    }
    void executeUnitHaltConstruction(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::Stop(0));
    }
    void executeUnitCancelMorph(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      if( BW::BWDATA_Unit_PrototypeFlags[bwUnit.unitType] & BW::UnitPrototypeFlags::Building ) // bwUnit.unitType.isBuilding()
        BW::issueCommand(BW::Command::CancelConstruction());
      else
        BW::issueCommand(BW::Command::CancelUnitMorph());
    }
    void executeUnitCancelTrain(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelTrainLast());
    }
    void executeUnitCancelTrainSlot(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelTrain(command.extra));
    }
    void executeUnitCancelAddon(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelAddon());
    }
    void executeUnitCancelResearch(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelResearch());
    }
    void executeUnitCancelUpgrade(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      BW::issueCommand(BW::Command::CancelUpgrade());
    }
    void executeUnitUseTech(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);
      switch (command.tech)
      {
      case BW::TechIDs::Stimpacks:
        BW::issueCommand(BW::Command::UseStimPack());
        break;
      case BW::TechIDs::TankSiegeMode:
        if (bwUnit.unitType == BW::UnitTypeIDs::Terran_SiegeTankSiegeMode)
          executeUnitUnsiege(bwUnitIndex, bwUnit, command);
        else
          executeUnitSiege(bwUnitIndex, bwUnit, command);
        break;
      case BW::TechIDs::PersonnelCloaking:
      case BW::TechIDs::CloakingField:
        if(bwUnit.status.getBit<BW::StatusFlags::Cloaked>())
          executeUnitDecloak(bwUnitIndex, bwUnit, command);
        else
          executeUnitCloak(bwUnitIndex, bwUnit, command);
        break;
      case BW::TechIDs::Burrowing:
        if(bwUnit.status.getBit<BW::StatusFlags::Burrowed>())
          executeUnitUnburrow(bwUnitIndex, bwUnit, command);
        else
          executeUnitBurrow(bwUnitIndex, bwUnit, command);
        break;
      case BW::TechIDs::ArchonWarp:
        BW::issueCommand(BW::Command::MergeArchon());
        break;
      case BW::TechIDs::DarkArchonMeld:
        BW::issueCommand(BW::Command::MergeDarkArchon());
        break;
      default:
        return;
      }
    }
    void executeUnitUseTechPosition(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);

      BW::OrderID attackSubOrder;

      switch (command.tech)
      {
      case BW::TechIDs::DarkSwarm:
        attackSubOrder = BW::OrderIDs::DarkSwarm;
        break;
      case BW::TechIDs::DisruptionWeb:
        attackSubOrder = BW::OrderIDs::CastDisruptionWeb;
        break;
      case BW::TechIDs::EMPShockwave:
        attackSubOrder = BW::OrderIDs::EmpShockwave;
        break;
      case BW::TechIDs::Ensnare:
        attackSubOrder = BW::OrderIDs::Ensnare;
        break;
      case BW::TechIDs::Maelstorm:
        attackSubOrder = BW::OrderIDs::CastMaelstrom;
        break;
      case BW::TechIDs::NuclearStrike:
        attackSubOrder = BW::OrderIDs::NukePaint;
        break;
      case BW::TechIDs::Plague:
        attackSubOrder = BW::OrderIDs::Plague;
        break;
      case BW::TechIDs::PsionicStorm:
        attackSubOrder = BW::OrderIDs::PsiStorm;
        break;
      case BW::TechIDs::Recall:
        attackSubOrder = BW::OrderIDs::Teleport;
        break;
      case BW::TechIDs::ScannerSweep:
        attackSubOrder = BW::OrderIDs::PlaceScanner;
        break;
      case BW::TechIDs::SpiderMines:
        attackSubOrder = BW::OrderIDs::PlaceMine;
        break;
      case BW::TechIDs::StasisField:
        attackSubOrder = BW::OrderIDs::StasisField;
        break;
      default:
        return;
      }

      BW::issueCommand(BW::Command::Attack(command.position, attackSubOrder));
    }
    void executeUnitUseTechUnit(int bwUnitIndex, const BW::Unit& bwUnit, const BWDI::UnitCommand& command)
    {
      executeSelectOrder(bwUnitIndex);

      BW::OrderID attackSubOrder;

      switch (command.tech)
      {
      case BW::TechIDs::Consume:
        attackSubOrder = BW::OrderIDs::Consume;
        break;
      case BW::TechIDs::DefensiveMatrix:
        attackSubOrder = BW::OrderIDs::DefensiveMatrix;
        break;
      case BW::TechIDs::Feedback:
        attackSubOrder = BW::OrderIDs::CastFeedback;
        break;
      case BW::TechIDs::Hallucination:
        attackSubOrder = BW::OrderIDs::Hallucination1;
        break;
      case BW::TechIDs::Healing:
        attackSubOrder = BW::OrderIDs::MedicHeal1;
        break;
      case BW::TechIDs::Infestation:
        attackSubOrder = BW::OrderIDs::InfestMine2;
        break;
      case BW::TechIDs::Irradiate:
        attackSubOrder = BW::OrderIDs::Irradiate;
        break;
      case BW::TechIDs::Lockdown:
        attackSubOrder = BW::OrderIDs::MagnaPulse;
        break;
      case BW::TechIDs::MindControl:
        attackSubOrder = BW::OrderIDs::CastMindControl;
        break;
      case BW::TechIDs::OpticalFlare:
        attackSubOrder = BW::OrderIDs::CastOpticalFlare;
        break;
      case BW::TechIDs::Parasite:
        attackSubOrder = BW::OrderIDs::CastParasite;
        break;
      case BW::TechIDs::Restoration:
        attackSubOrder = BW::OrderIDs::Restoration;
        break;
      case BW::TechIDs::SpawnBroodlings:
        attackSubOrder = BW::OrderIDs::SummonBroodlings;
        break;
      case BW::TechIDs::YamatoGun:
        attackSubOrder = BW::OrderIDs::FireYamatoGun1;
        break;
      default:
        return;
      }

      BW::issueCommand(BW::Command::Attack(findBwIndexByKnownUnitIndex(command.targetIndex), attackSubOrder));
    }
    void executeUnknownUnitCommand(int bwUnitIndex, const BW::Unit&, const BWDI::UnitCommand& command)
    {
      throw GeneralException("Executing unknown unit command " + Util::Strings::intToString(command.commandID));
    }
    void executeUnitCommand(const BWDI::UnitCommand& command)
    {
      typedef void(*EXECUTOR)(int unitID, const BW::Unit& bwUnit, const BWDI::UnitCommand&);
      static Util::LookupTable<EXECUTOR> executors;
      static bool isExecutorsTableInitialized = false;

      // initialize lookup table
      if(!isExecutorsTableInitialized)
      {
        executors.setDefaultValue(&executeUnknownUnitCommand);
        executors.setValue(UnitCommandTypeIDs::AttackPosition,      &executeUnitAttackPosition);
        executors.setValue(UnitCommandTypeIDs::AttackUnit,          &executeUnitAttackUnit);
        executors.setValue(UnitCommandTypeIDs::RightClickPosition,  &executeUnitRightClickPosition);
        executors.setValue(UnitCommandTypeIDs::RightClickUnit,      &executeUnitRightClickUnit);
        executors.setValue(UnitCommandTypeIDs::Train,               &executeUnitTrain);
        executors.setValue(UnitCommandTypeIDs::Build,               &executeUnitBuild);
        executors.setValue(UnitCommandTypeIDs::BuildAddon,          &executeUnitBuildAddon);
        executors.setValue(UnitCommandTypeIDs::Research,            &executeUnitResearch);
        executors.setValue(UnitCommandTypeIDs::Upgrade,             &executeUnitUpgrade);
        executors.setValue(UnitCommandTypeIDs::Stop,                &executeUnitStop);
        executors.setValue(UnitCommandTypeIDs::HoldPosition,        &executeUnitHoldPosition);
        executors.setValue(UnitCommandTypeIDs::Patrol,              &executeUnitPatrol);
        executors.setValue(UnitCommandTypeIDs::Follow,              &executeUnitFollow);
        executors.setValue(UnitCommandTypeIDs::SetRallyPosition,    &executeUnitSetRallyPosition);
        executors.setValue(UnitCommandTypeIDs::SetRallyUnit,        &executeUnitSetRallyUnit);
        executors.setValue(UnitCommandTypeIDs::Repair,              &executeUnitRepair);
        executors.setValue(UnitCommandTypeIDs::ReturnCargo,         &executeUnitReturnCargo);
        executors.setValue(UnitCommandTypeIDs::Morph,               &executeUnitMorph);
        executors.setValue(UnitCommandTypeIDs::Burrow,              &executeUnitBurrow);
        executors.setValue(UnitCommandTypeIDs::Unburrow,            &executeUnitUnburrow);
        executors.setValue(UnitCommandTypeIDs::Siege,               &executeUnitSiege);
        executors.setValue(UnitCommandTypeIDs::Unsiege,             &executeUnitUnsiege);
        executors.setValue(UnitCommandTypeIDs::Cloak,               &executeUnitCloak);
        executors.setValue(UnitCommandTypeIDs::Decloak,             &executeUnitDecloak);
        executors.setValue(UnitCommandTypeIDs::Lift,                &executeUnitLift);
        executors.setValue(UnitCommandTypeIDs::Land,                &executeUnitLand);
        executors.setValue(UnitCommandTypeIDs::Load,                &executeUnitLoad);
        executors.setValue(UnitCommandTypeIDs::Unload,              &executeUnitUnload);
        executors.setValue(UnitCommandTypeIDs::UnloadAll,           &executeUnitUnloadAll);
        executors.setValue(UnitCommandTypeIDs::UnloadAllPosition,   &executeUnitUnloadAllPosition);
        executors.setValue(UnitCommandTypeIDs::CancelConstruction,  &executeUnitCancelConstruction);
        executors.setValue(UnitCommandTypeIDs::HaltConstruction,    &executeUnitHaltConstruction);
        executors.setValue(UnitCommandTypeIDs::CancelMorph,         &executeUnitCancelMorph);
        executors.setValue(UnitCommandTypeIDs::CancelTrain,         &executeUnitCancelTrain);
        executors.setValue(UnitCommandTypeIDs::CancelTrainSlot,     &executeUnitCancelTrainSlot);
        executors.setValue(UnitCommandTypeIDs::CancelAddon,         &executeUnitCancelAddon);
        executors.setValue(UnitCommandTypeIDs::CancelResearch,      &executeUnitCancelResearch);
        executors.setValue(UnitCommandTypeIDs::CancelUpgrade,       &executeUnitCancelUpgrade);
        executors.setValue(UnitCommandTypeIDs::UseTech,             &executeUnitUseTech);
        executors.setValue(UnitCommandTypeIDs::UseTechPosition,     &executeUnitUseTechPosition);
        executors.setValue(UnitCommandTypeIDs::UseTechUnit,         &executeUnitUseTechUnit);
        isExecutorsTableInitialized = true;
      }

      // get command simulator function
      EXECUTOR executor = executors.lookUp(command.commandID);

      // find out the unitID.
      int bwUnitIndex = findBwIndexByKnownUnitIndex(command.unitIndex);

      const BW::Unit& bwUnit = BW::BWDATA_UnitNodeTable[bwUnitIndex];

      bool isUnitOwnedBySelf = bwUnit.playerID == *BW::BWDATA_selfPlayerID;
      if(!isUnitOwnedBySelf)
        return;

      executor(bwUnitIndex, bwUnit, command);
    }
    //---------------------------------------- -----------------------------------------------------------------
  }
};
