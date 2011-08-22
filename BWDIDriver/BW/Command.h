#pragma once

#include <Util/Types.h>

#include "PositionUnitID.h"
#include "RaceID.h"
#include "SlotID.h"
#include "OrderID.h"
#include "SlotStateID.h"
#include "UnitTypeID.h"
#include "TechID.h"
#include "UpgradeID.h"
#include "BuildPosition.h"

#pragma pack(1)
namespace BW
{
  // Set of classes that can pass to IssueCommand function. 
  namespace Command
  {
    //------------------------------------------------
    // Wrapper for typed classures
    //------------------------------------------------
    template<int TYPEID>
      struct TypeHead
      {
        u8 _type;

        TypeHead() : _type(TYPEID) {};
        static const int _typeId = TYPEID;
      };
    // Attack Location command in bw, can target either location or target. 
    class Attack : TypeHead<0x15> // 0x15 = Attack Location command-code in bw 
    {
      public :
        // Attack Location on position. 
        Attack(const BW::Position& target, BW::OrderID order);
        // Attack Location on unit. 
        Attack(BW::UnitID unit, BW::OrderID order);
        // Attack Location on general target. 
        Attack(const PositionUnitID& target, BW::OrderID order);
      private :
        BW::PositionUnitID target;
        u16 always0xe4;
        BW::OrderID order;
        u8 type;
    };
    // Right click command in bw, can target either location or target. 
    class RightClick : TypeHead<0x14> // 0x14 = Rightclick command-code in bw 
    {
      public :
        // Right-click on position. 
        RightClick(const BW::Position& target);
        // Right-click on unit. 
        RightClick(BW::UnitID target);
        // Right-click on general target. 
        RightClick(const PositionUnitID& target);
      private :
        BW::PositionUnitID target;
        u8 always0xe4;
        u16 alwaysZero;
    };
    // Selection command in bw
    class Select : TypeHead<0x09>  // 0x09 = Select command-code in bw 
    {
      public :
        Select(BW::UnitID *units, unsigned int count);
        u8         targCount;
        BW::UnitID targets[12];
        u32        size;
    };
    // Train unit command in bw. 
    class TrainUnit : TypeHead<0x1f>  // 0x1f = Train Command-code in bw 
    {
      public :
        TrainUnit(BW::UnitTypeID type);
        // Type of unit to train 
        BW::UnitTypeID type;
    };
    // Train unit command in bw. 
    class TrainFighter : TypeHead<0x27>  // 0x27 = Train fighter Command-code in bw 
    {
      public :
        TrainFighter();
    };
    // Make building. 
    class MakeBuilding : TypeHead<0x0c>  // 0x0c = make building Command-code in bw 
    {
      public :
        MakeBuilding(BW::BuildPosition position, BW::UnitTypeID type);
        // Specifies race of builder: zerg = 0x19, terran = 1e, toss = 1f 
        u8 raceDependant;
        BW::BuildPosition position;
        // Type of building to make 
        BW::UnitTypeID type;
    };

    // Invent tech. 
    class Invent : TypeHead<0x30>  // 0x30 = invent tech Command-code in bw 
    {
      public :
        Invent(BW::TechID type);
        // Type of tech to invent 
        BW::TechID tech;
    };
    class Upgrade : TypeHead<0x32>  // 0x32 = upgrade Command-code in bw 
    {
      public :
        Upgrade(BW::UpgradeID upgrade);
        
        // Type of upgrade 
        BW::UpgradeID upgrade;
    };
    class MakeAddon : TypeHead<0x0c>   // 0x0c = make building Command-code in bw 
    {
      public :
        MakeAddon(BW::BuildPosition position, BW::UnitTypeID type);
       
        // 1e for terran 1f for protoss
        u8 always0x24;
        BW::BuildPosition position;
        // Type of building to make 
        BW::UnitTypeID type;
    };
    // Change slot command in bw. 
    class ChangeSlot : TypeHead<0x44>  // 0x44 = Change slot command-code in bw 
    {
      public :
        ChangeSlot(SlotID slotId, SlotStateID slotStateId);
      private :
        // Order of the slot to change (0 for the 1st slot) 
        SlotID slotId;
        // Target slot state. 
        SlotStateID slotStateId;
    };
    // Change race command in bw. 
    class ChangeRace : TypeHead<0x41>  // 0x41 = Command code for change race in bw. 
    {
      public :
        ChangeRace(SlotID slotId, RaceID raceId);
      private :
        
        // Order of the slot to change (0 for the 1st slot). 
        SlotID slotId;
        // Target slot race. 
        RaceID raceId;
    };
    // Starts game in the pre-game lobby. 
    class StartGame : TypeHead<0x3c>  // 0x3c = Command code for start game. 
    {
      public :
        StartGame();
    };
    // Pauses the game. 
    class PauseGame : TypeHead<0x10>  // 0x10 = Command code for pause game. 
    {
      public :
        PauseGame();
    };
    class ResumeGame : TypeHead<0x11>  // 0x11 = Command code for unpause game. 
    {
      public :
        ResumeGame();
    };
    class LeaveGame : TypeHead<0x57>  // 0x57 = Command code for unpause game. 
    {
      public :
        LeaveGame(u8 type);
        u8 type;
    };

    class MergeDarkArchon : TypeHead<0x5A>  // 0x5A = Command code for Merge Dark Archon. 
    {
      public :
        MergeDarkArchon();
    };

    class MergeArchon : TypeHead<0x2A>   // 0x2A = Command code for Merge Archon. 
    {
      public :
        MergeArchon();
    };

    class MinimapPing : TypeHead<0x58>  // 0x58 = Command code for Minimap Ping. 
    {
      public :
        MinimapPing(BW::Position position);
        BW::Position position;
    };

    class UseStimPack : TypeHead<0x36>  // 0x36 = Command code for Stim 
    {
      public :
        UseStimPack();
    };

    class BuildingMorph : TypeHead<0x35>  // 0x35 = Building Morph for zerg 
    {
      public :
        BuildingMorph(BW::UnitTypeID type);

        // Type of unit to train 
        BW::UnitTypeID type;
    };

    class CancelAddon : TypeHead<0x34>  
    {
      public :
        CancelAddon();
    };

    class CancelUpgrade : TypeHead<0x33>  
    {
      public :
        CancelUpgrade();
    };

    class CancelResearch : TypeHead<0x31>  
    {
      public :
        CancelResearch();
    };

    class CancelNuke : TypeHead<0x2E>  
    {
      public :
        CancelNuke();
    };

    class Lift : TypeHead<0x2F>  
    {
      public :
        Lift();
      private :
        u32 unknown;
    };

    class Land : TypeHead<0x0C>  
    {
      public :
        Land(BW::BuildPosition position, BW::UnitTypeID type);
      private :
        u8 always0x47;
        BW::BuildPosition position;
        BW::UnitTypeID type;
    };

    class Burrow : TypeHead<0x2C>  
    {
      public :
        Burrow();
      private :
        u8 unused;
    };

    class Unburrow : TypeHead<0x2D>  
    {
      public :
        Unburrow();
      private :
        u8 unused;
    };

    class HoldPosition : TypeHead<0x2B>  
    {
      public :
        HoldPosition(u8 type);
      private :
        u8 type;
    };

    class UnloadUnit : TypeHead<0x29>  // 0x29 = Unload Unit 
    {
      public :
        UnloadUnit(BW::UnitID unload);
        
        // The unit to unload bw index 
        UnitID target;
    };

    class UnloadAll : TypeHead<0x28>  
    {
      public :
        UnloadAll();
      private :
        u8 unused;
    };

    class Siege : TypeHead<0x26>  
    {
      public :
        Siege();
      private :
        u8 unused;
    };

    class Unsiege : TypeHead<0x25>  
    {
      public :
        Unsiege();
      private :
        u8 unused;
    };

    class UnitMorph : TypeHead<0x23>  // 0x23 = Unit Morph (Zerg) Command-code in bw 
    {
      public :
        UnitMorph(BW::UnitTypeID type);
        
        // Type of unit to train 
        BW::UnitTypeID type;
    };

    class Cloak : TypeHead<0x21>  
    {
      public :
        Cloak();
      private :
        u8 unused;
    };

    class Decloak : TypeHead<0x22>  
    {
      public :
        Decloak();
      private :
        u8 unused;
    };

    class ReturnCargo : TypeHead<0x1E>  
    {
      public :
        ReturnCargo(u8 type);
      private :
        u8 type;
    };

    class Stop : TypeHead<0x1A>  
    {
      public :
        Stop(u8 type);
      private :
        u8 type;
    };

    class ReaverStop : TypeHead<0x1C>  
    {
      public :
        ReaverStop();
    };

    class CarrierStop : TypeHead<0x1B>  
    {
      public :
        CarrierStop();
    };

    class CancelUnitMorph : TypeHead<0x19>  
    {
      public :
        CancelUnitMorph();
    };

    class CancelConstruction : TypeHead<0x18>  
    {
      public :
        CancelConstruction();
    };

    class SendText : TypeHead<0x5C>  
    {
      public :
        SendText(u8 playerID, const char* msg);
      private :
        u8 playerID;
        const char* msg;
    };
    class UseCheat : TypeHead<0x12>  
    {
      public :
        UseCheat(u32 flags);
      private :
        u32 flags;
    };

    class CancelTrain : TypeHead<0x20>  
    {
      public :
        CancelTrain(u8 slot);
      private :
        u8 slot;
        u8 unknown;
    };

    class CancelTrainLast : TypeHead<0x20>  
    {
      public :
        CancelTrainLast();
      private :
        u8 always0xFE;
        u8 unknown;
    };
  }
};
#pragma pack()
